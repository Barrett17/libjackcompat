/*
    Copyright 2013-2015 Dario Casalinuovo. All rights reserved.

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

#include "jack/transport.h"

#include "WrapperDefs.h"


int
jack_release_timebase(jack_client_t* client) 
{
	UNIMPLEMENTED();
	return -1;
}


int
jack_set_sync_callback(jack_client_t* client, JackSyncCallback callback,
	void* cookie)
{
	UNIMPLEMENTED();
	return -1;
}


int
jack_set_sync_timeout(jack_client_t* client, jack_time_t timeout)
{
	UNIMPLEMENTED();
	return -1;
}


int
jack_set_timebase_callback(jack_client_t* client, int conditional,
	JackTimebaseCallback callback, void* cookie)
{
	UNIMPLEMENTED();
	return -1;
}


int
jack_transport_locate(jack_client_t* client, jack_nframes_t frame)
{
	UNIMPLEMENTED();
	return -1;
}


jack_transport_state_t
jack_transport_query(const jack_client_t* client, jack_position_t* position)
{
	UNIMPLEMENTED();
	return -1;
}


jack_nframes_t
jack_get_current_transport_frame(const jack_client_t* client)
{
	UNIMPLEMENTED();
	return -1;
}


int
jack_transport_reposition(jack_client_t* client,
	const jack_position_t* position) 
{
	UNIMPLEMENTED();
	return -1;
}


void
jack_transport_start(jack_client_t* client) 
{
	UNIMPLEMENTED();
}


void
jack_transport_stop(jack_client_t* client) 
{
	UNIMPLEMENTED();
}


void
jack_get_transport_info(jack_client_t* client, jack_transport_info_t* info) 
{
	UNIMPLEMENTED();
}


void
jack_set_transport_info(jack_client_t* client, jack_transport_info_t* info) 
{
	UNIMPLEMENTED();
}
