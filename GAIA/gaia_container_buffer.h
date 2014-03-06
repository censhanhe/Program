#ifndef		__GAIA_CONTAINER_BUFFER_H__
#define		__GAIA_CONTAINER_BUFFER_H__

namespace GAIA
{
	namespace CONTAINER
	{
		class Buffer : public BasicBuffer<GAIA::NM, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::NM>>{public:};
	};
};

#endif