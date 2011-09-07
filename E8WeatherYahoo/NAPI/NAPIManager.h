/*
 * zJabber - Jabber Client for MOTOMAGX
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

#ifndef _NAPIMANAGER_H
#define _NAPIMANAGER_H

#include <qobject.h>

class QSocket;
class NAPILink;

class NAPIManager: public QObject {
	Q_OBJECT

public:
	NAPIManager(QObject *parent = 0);
	virtual ~NAPIManager();

	QStringList getProfiles();

	NAPILink *openLink(QString profile);

private slots:
	void haveEvent();

signals:
	void connected();

private:
	int lastLink;
	QSocket *eventsSocket;
};

#endif

