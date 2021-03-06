#ifndef 	__GAIA_CONTAINER_CHARS_H__
#define 	__GAIA_CONTAINER_CHARS_H__

namespace GAIA
{
	namespace CTN
	{
		typedef BasicChars<GAIA::CH, GAIA::SIZE, 512> AChars;
		typedef BasicChars<GAIA::WCH, GAIA::SIZE, 512> WChars;
		typedef BasicChars<GAIA::TCH, GAIA::SIZE, 512> TChars;
	};
};

#endif
