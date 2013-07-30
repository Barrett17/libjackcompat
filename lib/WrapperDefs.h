/*
 * Copyright 2013 Dario Casalinuovo. All rights reserved.
 * Distributed under the terms of the GPL License.
 */
#ifndef _WRAPPERDEFS_H_
#define _WRAPPERDEFS_H_

#define LIB_EXPORT __attribute__((visibility("default")))

// Sizes constants
#define WRAPPER_CLIENT_NAME_SIZE 64
#define WRAPPER_PORT_NAME_SIZE 64


// Preferred values (those should be set by a config gui or 
// a settings file.

#define WRAPPER_PREFERRED_BUF_SIZE 4410;

#define WRAPPER_PREFERRED_FORMAT media_raw_audio_format::B_AUDIO_FLOAT

#endif	// _WRAPPERDEFS_H_
