#ifndef		__GAIA_CONTAINER_BITSET_H__
#define		__GAIA_CONTAINER_BITSET_H__

namespace GAIA
{
	namespace CONTAINER
	{
		class Bitset : public BasicBitset<GAIA::SIZE, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::SIZE> >{public:};
	};
};

#endif
