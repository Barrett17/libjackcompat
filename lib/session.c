/*
    Copyright 2013 Dario Casalinuovo. All rights reserved.

    This file is part of libjackcompat.

    libjackcompat is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    libjackcompat is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with libjackcompat.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "jack/session.h"

void jack_session_event_free (jack_session_event_t *event)
{
}


int jack_session_reply (jack_client_t* client,
	jack_session_event_t *event)
{
}

int jack_set_session_callback (jack_client_t* client,
	JackSessionCallback session_callback,
	void* arg)
{

}
