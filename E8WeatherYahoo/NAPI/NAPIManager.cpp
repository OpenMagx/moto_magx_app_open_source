/*
 * Copyright (C) 2009  Serge Gridassov
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <qsocket.h>
#include "NAPIManager.h"
#include "NAPILink.h"
#include "./../header/napi.h"
#include "./../header/ZDataSessionManager.h"

NAPIManager::NAPIManager(QObject *parent) : QObject(parent) {
	int socket = NAPI_Init(0);

	eventsSocket = new QSocket(this);
	eventsSocket->setSocket(socket);
	connect(eventsSocket, SIGNAL(readyRead()), this, SLOT(haveEvent()));

}

NAPIManager::~NAPIManager() {
	NAPI_Fini();
}

void NAPIManager::haveEvent() {
	QByteArray dataPacket = eventsSocket->readAll();

	switch(dataPacket[0]) {
	case 16:
		NAPI_DnsResolverConfig(lastLink);
		emit connected();
		break;

	default:
		fprintf(stderr, "Unknown event %d\n", dataPacket[0]);
		break;
	}
}

QStringList NAPIManager::getProfiles() {
	UINT32 profiles = NAPI_GetMaxProfiles();

	if(profiles == -1) 
		return QStringList();

	char *buf = new char[NAPI_MAX_PROFILE_NAME_LENGTH * profiles];

	if(NAPI_ListAllProfile((INT8*)buf, &profiles) == -1) 
		return QStringList();

	char *prof_ptr = buf;

	QStringList ret;

	for(int i = 0; i < profiles; i++, prof_ptr = buf + i * NAPI_MAX_PROFILE_NAME_LENGTH) {
		ret.append(QString(prof_ptr));
	}

	delete buf;

	return ret;
}

NAPILink *NAPIManager::openLink(QString profile) 
{
	if(profile.isEmpty())
	{
        	if( getProfileNamebySelect(profile) != 0)
        	{	
			return 0;	
		}
	}

	if(profile.isEmpty())
	{	
		return 0;
	}

	int linkId = NAPI_OpenLink((INT8*)profile.latin1());

	if(linkId == -1)
		return NULL;

	lastLink = linkId;

	return new NAPILink(linkId, this);
}

