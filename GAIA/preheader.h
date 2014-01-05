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
#	if GAIA_OS == GAIA_OS_WINDOWS
#		define NOMINMAX
#		include <windows.h>
#	else
#		include <pthread.h>
#	endif
#endif
#include "gaia.h"

#endif
