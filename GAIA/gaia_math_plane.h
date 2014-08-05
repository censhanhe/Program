#ifndef		__GAIA_MATH_PLANE_H__
#define		__GAIA_MATH_PLANE_H__

namespace GAIA
{
	namespace MATH
	{
		template<typename _DataType> class PLANE : public GAIA::Entity
		{
		public:
		public:
			_DataType a, b, c, d;
		};
	};
};

#endif