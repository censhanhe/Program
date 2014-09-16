#ifndef		__GAIA_CONTAINER_BITSET_H__
#define		__GAIA_CONTAINER_BITSET_H__

namespace GAIA
{
	namespace CTN
	{
		class Bitset : public BasicBitset<GAIA::SIZE, GAIA::ALGO::TwiceSizeIncreaser<GAIA::SIZE> >{public:};
	};
};

#endif
