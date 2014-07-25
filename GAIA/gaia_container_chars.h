#ifndef 	__GAIA_CONTAINER_CHARS_H__
#define 	__GAIA_CONTAINER_CHARS_H__

namespace GAIA
{
	namespace CONTAINER
	{
		typedef BasicChars<GAIA::CH, GAIA::SIZE, 512> AChars;
		typedef BasicChars<GAIA::WCH, GAIA::SIZE, 512> WChars;
	};
};

#endif
