/*
    Copyright 2015 Dario Casalinuovo. All rights reserved.

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

#include "WrapperDefs.h"


LIB_EXPORT void
jack_port_set_latency(jack_port_t* port, jack_nframes_t frames)
{
	UNIMPLEMENTED();
}


LIB_EXPORT jack_nframes_t
jack_port_get_latency(jack_port_t* port)
{
	UNIMPLEMENTED();
	return -1;
}


LIB_EXPORT jack_nframes_t
jack_port_get_total_latency(jack_client_t* client, jack_port_t* port)
{
	UNIMPLEMENTED();
	return -1;
}


LIB_EXPORT int
jack_port_tie(jack_port_t* source, jack_port_t* dest)
{
	UNIMPLEMENTED();
	return -1;
}


LIB_EXPORT int
jack_port_untie(jack_port_t* port)
{
	UNIMPLEMENTED();
	return -1;
}


LIB_EXPORT int
jack_recompute_total_latency(jack_client_t* client, jack_port_t* port)
{
	UNIMPLEMENTED();
	return -1;
}


LIB_EXPORT jack_client_t*
jack_client_new(const char* name)
{
	UNIMPLEMENTED();
	return NULL;
}


LIB_EXPORT int
jack_internal_client_new(const char* name,
	const char* name, const char* init)
{
	UNIMPLEMENTED();
	return -1;
}


LIB_EXPORT void
jack_internal_client_close(const char* name)
{
	UNIMPLEMENTED();
}


LIB_EXPORT int
jack_engine_takeover_timebase(jack_client_t* client)
{
	UNIMPLEMENTED();
	return -1;
}
