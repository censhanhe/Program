#ifndef		__GAIA_CONTAINER_QUEUE_H__
#define		__GAIA_CONTAINER_QUEUE_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template <typename _DataType> class Queue : public BasicQueue<_DataType, GAIA::UM, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::UM> >
		{
		public:
		};
	};
};

#endif