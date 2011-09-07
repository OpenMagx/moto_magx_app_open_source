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

#include "NAPILink.h"
#include "./../header/napi.h"

NAPILink::NAPILink(int linkId, QObject *parent) : QObject(parent) {
	this->linkId = linkId;
	isOpen = true;
}

NAPILink::~NAPILink() {
	if(isOpen)
		close();
}

bool NAPILink::close() {
	if(isOpen) {
		return NAPI_CloseLink(linkId) != -1;
	}

	return false;
}

bool NAPILink::bindSocket(int fd) {
	return NAPI_BindSocket2Link(fd, linkId);
}
