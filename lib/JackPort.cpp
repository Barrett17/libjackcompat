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

#include <string.h>

#include "JackPort.h"


JackPort::JackPort(const char *port_name,
	const char *port_type, unsigned long flags,
	unsigned long buffer_size, JackClient* owner)
	:
	fOwner(owner),
	fType(port_type),
	fFlags(flags),
	fBufferSize(buffer_size)
{
	fOwner = owner;
	fName = port_name;
	fConnected = false;
	fEnabled = false;
	fInput = new media_input();
	fOutput = new media_output();
	fCurrentBuf = NULL;
}


JackPort::~JackPort()
{
	delete fInput;
	delete fOutput;
}


JackClient*
JackPort::Owner() const
{
	return fOwner;
}


const char*
JackPort::Name() const
{
	return fName;
}


const char*
JackPort::Type() const
{
	return fType;
}


unsigned long
JackPort::Flags() const
{
	return fFlags;
}


unsigned long
JackPort::BufferSize() const
{
	return fBufferSize;
}


BBuffer*
JackPort::CurrentBuffer()
{
	return fCurrentBuf;
}


void
JackPort::SetProcessingBuffer(BBuffer* buf)
{
	fCurrentBuf = buf;
}


void
JackPort::SetMediaInput(media_input dest)
{
	*fInput = dest;
}


void
JackPort::SetMediaOutput(media_output dest)
{
	*fOutput = dest;
}


media_input*
JackPort::MediaInput() const
{
	return fInput;
}


media_output*
JackPort::MediaOutput() const
{
	return fOutput;
}

void
JackPort::SetConnected(bool connected)
{
	fConnected = connected;
}


bool
JackPort::IsConnected() const
{
	return fConnected;
}


void
JackPort::SetEnabled(bool enabled)
{
	fEnabled = enabled;
}


bool
JackPort::IsEnabled() const
{
	return fEnabled;
}
