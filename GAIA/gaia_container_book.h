#ifndef		__GAIA_CONTAINER_BOOK_H__
#define		__GAIA_CONTAINER_BOOK_H__

namespace GAIA
{
	namespace CTN
	{
		template<typename _DataType> class Book : public BasicBook<_DataType, GAIA::SIZE, GAIA::ALGO::TwiceSizeIncreaser<GAIA::SIZE> >{public:};
	};
};

#endif