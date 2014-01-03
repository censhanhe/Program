#ifndef		__GAIA_ERROR_H__
#define		__GAIA_ERROR_H__

namespace GAIA
{
	namespace ERROR_MANAGEMENT
	{
		#define GAIA_DECL_ERRORNUM(num, info) \
					template <GAIA::UM _ErrorNumber##num> class ERRORNUM##num\
					{\
					public:\
						const GAIA::GTCH* GetErrorInfoW() const{return L##info;}\
						const GAIA::GTCH* GetErrorInfoA() const{return info;}\
					};

		ENUM_BEGIN(ERROR_MODE)
			ERROR_MODE_LAST			= 0x00000001,
			ERROR_MODE_STACK		= 0x00000002,
			ERROR_MODE_QUEUE		= 0x00000004,
			ERROR_MODE_MULTITHREAD	= 0x00000008,
		ENUM_END

		GINL GAIA::GVOID	SetErrorMode(ERROR_MODE eMode);
		GINL ERROR_MODE		GetErrorMode();
		GINL GAIA::GVOID	RaiseError(const GAIA::UM& errornumber);
		GINL const GAIA::UM&PeekError();
		GINL GAIA::GVOID	PopError();
		
	};
};

#endif