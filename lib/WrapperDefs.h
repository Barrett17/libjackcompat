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

#ifndef _LIBJACKCOMPAT_DEFS_H_
#define _LIBJACKCOMPAT_DEFS_H_

#define LIB_EXPORT __attribute__((visibility("default")))

// Sizes constants
#define WRAPPER_CLIENT_NAME_SIZE 64
#define WRAPPER_PORT_NAME_SIZE 64

// Preferred values (those should be set by a config gui or 
// a settings file.

#define WRAPPER_PREFERRED_FRAMERATE 44100.0

#define WRAPPER_PREFERRED_BUF_SIZE 1024

#define WRAPPER_PREFERRED_FORMAT media_raw_audio_format::B_AUDIO_FLOAT

#endif
