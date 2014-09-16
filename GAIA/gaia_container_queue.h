#ifndef		__GAIA_CONTAINER_QUEUE_H__
#define		__GAIA_CONTAINER_QUEUE_H__

namespace GAIA
{
	namespace CTN
	{
		template<typename _DataType> class Queue : public BasicQueue<_DataType, GAIA::SIZE, GAIA::ALGO::TwiceSizeIncreaser<GAIA::SIZE> >{public:};
	};
};

#endif
