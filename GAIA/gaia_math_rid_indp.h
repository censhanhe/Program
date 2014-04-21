#ifndef 	__GAIA_MATH_RID_INDP_H__
#define 	__GAIA_MATH_RID_INDP_H__

#if GAIA_OS == GAIA_OS_WINDOWS
#	define NOMINMAX
#	include <winsock2.h>
#	include <ws2tcpip.>
#	include <windows.h>
#else
#	include <uuid/uuid.h>
#endif

namespace GAIA
{
	namespace MATH
	{
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::GVOID RID128::uuid()
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			::CoCreateGuid((GUID*)u);
		#else
			uuid_generate(*(uuid_t*)u);
		#endif
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::GVOID RID64::uuid()
		{
			GAIA::U8 ut[16];
		#if GAIA_OS == GAIA_OS_WINDOWS
			::CoCreateGuid((GUID*)ut);
		#else
			uuid_generate(*(uuid_t*)ut);
		#endif
			u64_0 = *(GAIA::U64*)ut;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::GVOID RID32::uuid()
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
