#ifndef		__GAIA_TYPE_INDP_H__
#define		__GAIA_TYPE_INDP_H__

#if GAIA_OS == GAIA_OS_WINDOWS
#	define NOMINMAX
#	include <winsock2.h>
#	include <ws2tcpip.h>
#	include <windows.h>
#else
#endif

namespace GAIA
{
	GINL GAIA::NM RefObject::Reference()
	{
		return ::InterlockedIncrement(&m_nRef);
	}
	GINL GAIA::NM RefObject::Release()
	{
		GAIA::NM nNew = ::InterlockedIncrement(&m_nRef);
		if(nNew == 0 && !m_bDestructing)
		{
			m_bDestructing = true;
			this->Destruct();
			delete this;
		}
		return nNew;
	}
};

#endif