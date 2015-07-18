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

#include "jack/intclient.h"


LIB_EXPORT jack_intclient_t
jack_internal_client_load(jack_client_t* client,
	const char* client_name, jack_options_t options,
	jack_status_t* status, ...)
{
	UNIMPLEMENTED();
	return -1;
}


LIB_EXPORT jack_status_t
jack_internal_client_unload(jack_client_t* client,
	jack_intclient_t intclient)
{
	UNIMPLEMENTED();
	return -1;
}


LIB_EXPORT char
jack_get_internal_client_name(jack_client_t* client,
	jack_intclient_t intclient)
{
	UNIMPLEMENTED();
	return "";
}


LIB_EXPORT jack_intclient_t
	jack_internal_client_handle(jack_client_t* client,
	const char* client_name, jack_status_t* status)
{
	UNIMPLEMENTED();
	return -1;
}
