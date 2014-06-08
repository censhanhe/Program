#ifndef		__GAIA_CONTAINER_STACKQUEUE_H__
#define		__GAIA_CONTAINER_STACKQUEUE_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template<typename _DataType, GAIA::SIZE _Size> class StackQueue : public BasicStackQueue<_DataType, GAIA::SIZE, _Size>{public:};
	};
};

#endif
