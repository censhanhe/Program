#ifndef		__GAIA_CONTAINER_BUFFER_H__
#define		__GAIA_CONTAINER_BUFFER_H__

namespace GAIA
{
	namespace CONTAINER
	{
		class Buffer : public BasicBuffer<GAIA::SIZE, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::SIZE> >{public:};
	};
};

#endif