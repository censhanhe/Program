#ifndef		__GAIA_CONTAINER_CHARSSTRING_H__
#define		__GAIA_CONTAINER_CHARSSTRING_H__

namespace GAIA
{
	namespace CTN
	{
		typedef GAIA::CTN::BasicCharsString<GAIA::CH, GAIA::SIZE, 512> ACharsString;
		typedef GAIA::CTN::BasicCharsString<GAIA::WCH, GAIA::SIZE, 512> WCharsString;
		typedef GAIA::CTN::BasicCharsString<GAIA::TCH, GAIA::SIZE, 512> TCharsString;
	};
};

#endif