#ifndef		__GAIA_CONTAINER_ARRAY_H__
#define		__GAIA_CONTAINER_ARRAY_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template<typename _DataType, GAIA::SIZE _Size> class Array : public BasicArray<_DataType, GAIA::SIZE, _Size>{public:};
	};
};

#endif
