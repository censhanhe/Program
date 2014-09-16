#ifndef		__GAIA_CONTAINER_BUFFER_H__
#define		__GAIA_CONTAINER_BUFFER_H__

namespace GAIA
{
	namespace CTN
	{
		class Buffer : public BasicBuffer<GAIA::SIZE, GAIA::ALGO::TwiceSizeIncreaser<GAIA::SIZE> >{public:};
	};
};

#endif
