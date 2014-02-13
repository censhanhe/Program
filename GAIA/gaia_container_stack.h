#ifndef		__GAIA_CONTAINER_STACK_H__
#define		__GAIA_CONTAINER_STACK_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template<typename _DataType> class Stack : public BasicStack<_DataType, GAIA::UM, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::UM>>{public:};
	};
};

#endif