#ifndef		__GAIA_CONTAINER_STACK_H__
#define		__GAIA_CONTAINER_STACK_H__

namespace GAIA
{
	namespace CTN
	{
		template<typename _DataType> class Stack : public BasicStack<_DataType, GAIA::SIZE, GAIA::ALGO::TwiceSizeIncreaser<GAIA::SIZE> >{public:};
	};
};

#endif
