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

#include "jack/statistics.h"


LIB_EXPORT float
jack_get_xrun_delayed_usecs(jack_client_t* client)
{
	return -1;
}


LIB_EXPORT float
jack_get_max_delayed_usecs(jack_client_t* client)
{
	return -1;
}


LIB_EXPORT void
jack_reset_max_delayed_usecs(jack_client_t* client)
{
	return -1;
}
