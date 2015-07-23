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

#include "jack/control.h"

#include "WrapperDefs.h"


LIB_EXPORT bool
jackctl_server_start(jackctl_server_t* server)
{
	UNIMPLEMENTED();

	return false;
}


LIB_EXPORT bool
jackctl_server_stop(jackctl_server_t* server)
{
	UNIMPLEMENTED();

	return false;
}


LIB_EXPORT bool
jackctl_server_close(jackctl_server_t* server)
{
	UNIMPLEMENTED();

	return NULL;
}


jackctl_server_t* 
jackctl_server_create(bool(* acquire_callback)(const char* name),
	void(* release_callback)(const char* name))
{
	UNIMPLEMENTED();

	return NULL;
}


LIB_EXPORT void
jackctl_server_destroy(jackctl_server_t* server)
{
	UNIMPLEMENTED();
}


LIB_EXPORT bool
jackctl_server_open(jackctl_server_t* server,
	jackctl_driver_t* driver)
{
	UNIMPLEMENTED();

	return false;
}


jackctl_sigmask_t* 
jackctl_setup_signals(unsigned int flags)
{
	UNIMPLEMENTED();

	return NULL;
}


LIB_EXPORT void
jackctl_wait_signals(jackctl_sigmask_t* signals)
{
	UNIMPLEMENTED();
}


const JSList* 
jackctl_server_get_drivers_list(jackctl_server_t* server)
{
	UNIMPLEMENTED();

	return NULL;
}



const JSList* 
jackctl_server_get_parameters(jackctl_server_t* server)
{
	UNIMPLEMENTED();

	return NULL;
}


const JSList* 
jackctl_server_get_internals_list(jackctl_server_t* server)
{
	UNIMPLEMENTED();

	return NULL;
}


LIB_EXPORT bool jackctl_server_load_internal(jackctl_server_t* server,
	jackctl_internal_t* internal)
{
	UNIMPLEMENTED();

	return false;
}


LIB_EXPORT bool
jackctl_server_unload_internal(jackctl_server_t* server,
    jackctl_internal_t* internal)
{
	UNIMPLEMENTED();

	return false;
}


LIB_EXPORT bool
jackctl_server_add_slave(jackctl_server_t* server,
	jackctl_driver_t* driver)
{
	UNIMPLEMENTED();

	return false;
}


LIB_EXPORT bool
jackctl_server_remove_slave(jackctl_server_t* server,
	jackctl_driver_t* driver)
{
	UNIMPLEMENTED();

	return false;
}


LIB_EXPORT bool
jackctl_server_switch_master(jackctl_server_t* server,
	jackctl_driver_t* driver)
{
	UNIMPLEMENTED();

	return false;
}


LIB_EXPORT LIB_EXPORT const char* 
jackctl_driver_get_name(jackctl_driver_t* driver)
{
	UNIMPLEMENTED();

	return NULL;
}


jackctl_driver_type_t
jackctl_driver_get_type(jackctl_driver_t* driver)
{
	UNIMPLEMENTED();

	return -1;
}


const JSList* 
jackctl_driver_get_parameters(jackctl_driver_t* driver)
{
	UNIMPLEMENTED();

	return NULL;
}


int
jackctl_driver_params_parse(jackctl_driver_t* driver,
	int argc, char* argv)
{
	UNIMPLEMENTED();

	return NULL;
}


LIB_EXPORT const char* 
jackctl_internal_get_name(jackctl_internal_t* internal)
{
	UNIMPLEMENTED();

	return NULL;
}


const JSList* 
jackctl_internal_get_parameters(jackctl_internal_t* internal)
{
	UNIMPLEMENTED();

	return NULL;
}


LIB_EXPORT const char* 
jackctl_parameter_get_name(jackctl_parameter_t* param)
{
	UNIMPLEMENTED();

	return NULL;
}


LIB_EXPORT const char* 
jackctl_parameter_get_short_description(jackctl_parameter_t* param)
{
	UNIMPLEMENTED();

	return NULL;
}


LIB_EXPORT const char* 
jackctl_parameter_get_long_description(jackctl_parameter_t* param)
{
	UNIMPLEMENTED();

	return NULL;
}


jackctl_param_type_t
jackctl_parameter_get_type(jackctl_parameter_t* param)
{
	UNIMPLEMENTED();

	return -1;
}


char
jackctl_parameter_get_id(jackctl_parameter_t* param)
{
	UNIMPLEMENTED();

	return 0;
}


LIB_EXPORT bool
jackctl_parameter_is_set(jackctl_parameter_t*  parameter)
{
	UNIMPLEMENTED();

	return false;
}


LIB_EXPORT bool
jackctl_parameter_reset(jackctl_parameter_t* param)
{
	UNIMPLEMENTED();

	return false;
}


union jackctl_parameter_value
jackctl_parameter_get_value(jackctl_parameter_t* param)
{
	UNIMPLEMENTED();

	return 0;
}


LIB_EXPORT bool
jackctl_parameter_set_value(jackctl_parameter_t* param,
	const union jackctl_parameter_value* value_ptr)
{
	UNIMPLEMENTED();

	return false;
}


union jackctl_parameter_value
jackctl_parameter_get_default_value(jackctl_parameter_t* param)
{
	UNIMPLEMENTED();

	return 0;
}


LIB_EXPORT bool
jackctl_parameter_has_range_constraint(jackctl_parameter_t* param)
{
	UNIMPLEMENTED();

	return false;
}


LIB_EXPORT bool
jackctl_parameter_has_enum_constraint(jackctl_parameter_t* param)
{
	UNIMPLEMENTED();

	return false;
}


uint32_t
jackctl_parameter_get_enum_constraints_count jackctl_parameter_t* param)
{
	UNIMPLEMENTED();

	return 0;
}


union jackctl_parameter_value
jackctl_parameter_get_enum_constraint_value(jackctl_parameter_t* param,
	uint32_t index)
{
	UNIMPLEMENTED();

	return 0;
}


LIB_EXPORT const char* 
jackctl_parameter_get_enum_constraint_description(
	jackctl_parameter_t* param, uint32_t index)
{
	UNIMPLEMENTED();

	return NULL;
}


LIB_EXPORT void
jackctl_parameter_get_range_constraint(jackctl_parameter_t* param,
	union jackctl_parameter_value* min_ptr,
	union jackctl_parameter_value* max_ptr)
{
	UNIMPLEMENTED();
}


LIB_EXPORT bool
jackctl_parameter_constraint_is_strict(jackctl_parameter_t* param)
{
	UNIMPLEMENTED();

	return NULL;
}


LIB_EXPORT bool
jackctl_parameter_constraint_is_fake_value(jackctl_parameter_t* param)
{
	UNIMPLEMENTED();

	return false;
}


LIB_EXPORT void
jack_error(const char* format, ...)
{
	UNIMPLEMENTED();
}


LIB_EXPORT void
jack_info(const char* format, ...)
{
	UNIMPLEMENTED();
}


LIB_EXPORT void
jack_log(const char* format, ...)
{
	UNIMPLEMENTED();
}
