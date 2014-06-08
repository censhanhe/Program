#ifndef		__PRE_HEADER_H__
#define		__PRE_HEADER_H__

/*
*	!WARNING!
*		Only cpp(*.cpp *.c) file can include this file.
*		The header file(*.h *.hh *.hpp) cannot include this file!
*
*	!WARNING!
*		This file can only been used in GAIA system.
*		Any other project will use itself's preheader file.
*/

#include "gaia_sysconfig.h"
#ifdef GAIA_DEBUG_CODEPURE
#	undef bool
#	undef true
#	undef false
#	undef char
#	undef short
#	undef int
#	undef long
#	undef float
#	undef double
#	undef wchar_t
#	undef __wchar_t
#	undef unsigned

#	include <math.h>
#	include <stdio.h>
#	include <stdlib.h>
#	include <iostream>
#	if GAIA_OS == GAIA_OS_WINDOWS
#		define NOMINMAX
#		include <winsock2.h>
#		include <ws2tcpip.h>
#		include <windows.h>
#		include <time.h>
#	else
#		include <unistd.h>
#		include <uuid/uuid.h>
#		include <pthread.h>
#		include <time.h>
#		include <sys/time.h>
#		include <sys/errno.h>
#		include <sys/fcntl.h>
#		include <sys/types.h>
#		include <sys/socket.h>
#		include <netinet/in.h>
#		include <netdb.h>
#		include <sys/stat.h>
#		include <sys/dir.h>
#		include <dirent.h>
#		if GAIA_OS == GAIA_OS_OSX || GAIA_OS == GAIA_OS_IOS
#			include <libkern/OSAtomic.h>
#		else
#			include <asm/atomic.h>
#		endif
#	endif
#endif
#include "gaia.h"

#endif
