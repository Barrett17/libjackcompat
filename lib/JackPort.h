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

#ifndef _HAIKU_JACKPORT_H_
#define _HAIKU_JACKPORT_H_

#include <Locker.h>
#include <MediaDefs.h>
#include <ObjectList.h>

#include "JackClient.h"
#include "WrapperDefs.h"

class JackClient;


class JackPort
{
public:
					JackPort(const char *port_name,
						const char *port_type, unsigned long flags,
						unsigned long buffer_size, JackClient* owner);

					~JackPort();

	JackClient*		Owner() const;
	const char*		Name() const;
	const char*		Type() const;
	unsigned long	Flags() const;
	unsigned long	BufferSize() const;

	void			SetProcessingBuffer(BBuffer* buffer);
	BBuffer*		CurrentBuffer();

	void			SetMediaInput(media_input dest);
	void			SetMediaOutput(media_output dest);

	media_input*	MediaInput() const;
	media_output*	MediaOutput() const;

	void			SetConnected(bool connected);
	bool			IsConnected() const;

	void			SetEnabled(bool enabled);
	bool			IsEnabled() const;

private:
	const char*		fType;
	unsigned long	fFlags;
	unsigned long	fBufferSize;
	BBuffer*		fCurrentBuf;

	const char*		fName;
	JackClient*		fOwner;

	bool			fConnected;
	bool			fEnabled;

	media_input*	fInput;
	media_output*	fOutput;
};


#endif	// _JACKPORT_H_
