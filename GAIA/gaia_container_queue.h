#ifndef		__GAIA_CONTAINER_QUEUE_H__
#define		__GAIA_CONTAINER_QUEUE_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template<typename _DataType> class Queue : public BasicQueue<_DataType, GAIA::SIZE, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::SIZE> >{public:};
	};
};

#endif
