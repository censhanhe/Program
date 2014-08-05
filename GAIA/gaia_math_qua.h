#ifndef		__GAIA_MATH_QUA_H__
#define		__GAIA_MATH_QUA_H__

namespace GAIA
{
	namespace QUA
	{
		template<typename _DataType> class QUA : public GAIA::Entity
		{
		public:
			_DataType x, y, z, w;
		};
	};
};

#endif