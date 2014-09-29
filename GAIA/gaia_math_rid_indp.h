#ifndef 	__GAIA_MATH_RID_INDP_H__
#define 	__GAIA_MATH_RID_INDP_H__

#if GAIA_OS == GAIA_OS_WINDOWS
#	include <winsock2.h>
#	include <ws2tcpip.h>
#	include <windows.h>
#else
#	include <uuid/uuid.h>
#endif

namespace GAIA
{
	namespace MATH
	{
		GINL GAIA::GVOID RID128::uuid()
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			::CoCreateGuid(GRCAST(GUID*)(u));
		#else
			uuid_generate(*GRCAST(uuid_t*)(u));
		#endif
		}
		GINL GAIA::GVOID RID64::uuid()
		{
			GAIA::U8 ut[16];
		#if GAIA_OS == GAIA_OS_WINDOWS
			::CoCreateGuid((GUID*)ut);
		#else
			uuid_generate(*(uuid_t*)ut);
		#endif
			u64_0 = *(GAIA::U64*)ut;
		}
		GINL GAIA::GVOID RID32::uuid()
		{
			GAIA::U8 ut[16];
		#if GAIA_OS == GAIA_OS_WINDOWS
			::CoCreateGuid((GUID*)ut);
		#else
			uuid_generate(*(uuid_t*)ut);
		#endif
			u0 = *(GAIA::U32*)ut;
		}
	};
};

#endif
