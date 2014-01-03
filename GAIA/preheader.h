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
#endif
#include "gaia.h"

#endif