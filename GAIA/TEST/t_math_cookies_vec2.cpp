#include "preheader.h"
#include "t_header.h"

namespace GAIA_TEST
{
	extern GAIA::N32 t_math_cookies_vec2(GAIA::FSYS::File& file, GAIA::STREAM::StreamBase& stm)
	{
		GAIA::N32 nRet = 0;

		typedef GAIA::MATH::VEC2<GAIA::REAL> __RealVecType;
		typedef GAIA::MATH::VEC2<GAIA::NM> __NMVecType;

		__RealVecType rv, rv1;
		__NMVecType nmv;
		if(rv.size() != 2)
		{
			GTLINE2("VEC2 size error!");
			++nRet;
		}
		rv = 10.0F;
		if(rv != 10.0F)
		{
			GTLINE2("VEC2 operator = value error!");
			++nRet;
		}
		if(rv != rv)
		{
			GTLINE2("VEC2 != self error!");
			++nRet;
		}
		rv = rv;
		if(rv != 10.0F)
		{
			GTLINE2("VEC2 != const error!");
			++nRet;
		}
		if(rv != 10)
		{
			GTLINE2("VEC2 != const error!");
			++nRet;
		}
		if(rv != rv)
		{
			GTLINE2("VEC2 != self error!");
			++nRet;
		}

		rv.x = 1.0F;
		rv.y = 2.0F;
		nmv = rv;
		if(nmv.x != 1 || nmv.y != 2)
		{
			GTLINE2("VEC2 set value error!");
			++nRet;
		}
		if(!(rv == nmv))
		{
			GTLINE2("VEC2 set value error!");
			++nRet;
		}
		if(rv != nmv)
		{
			GTLINE2("VEC2 set value error!");
			++nRet;
		}
		if(!(rv >= nmv))
		{
			GTLINE2("VEC2 set value error!");
			++nRet;
		}
		if(!(rv <= nmv))
		{
			GTLINE2("VEC2 set value error!");
			++nRet;
		}
		if(rv > nmv)
		{
			GTLINE2("VEC2 set value error!");
			++nRet;
		}
		if(rv < nmv)
		{
			GTLINE2("VEC2 set value error!");
			++nRet;
		}

		rv.x = 1.0F;
		rv.y = 2.0F;
		nmv = rv;
		rv.x = 3.0F;
		rv.y = 4.0F;
		rv = static_cast<const __NMVecType::_datatype*>(nmv);
		if(rv.x != 1.0F || rv.y != 2.0F)
		{
			GTLINE2("VEC2 set pointer error!");
			++nRet;
		}
		if(!(rv == nmv))
		{
			GTLINE2("VEC2 set pointer error!");
			++nRet;
		}
		if(rv != nmv)
		{
			GTLINE2("VEC2 set pointer error!");
			++nRet;
		}
		if(!(rv >= nmv))
		{
			GTLINE2("VEC2 set pointer error!");
			++nRet;
		}
		if(!(rv <= nmv))
		{
			GTLINE2("VEC2 set pointer error!");
			++nRet;
		}
		if(rv > nmv)
		{
			GTLINE2("VEC2 set pointer error!");
			++nRet;
		}
		if(rv < nmv)
		{
			GTLINE2("VEC2 set pointer error!");
			++nRet;
		}

		rv.x = 3.0F;
		rv.y = 4.0F;
		if(rv.length() != 5.0F)
		{
			GTLINE2("VEC2 length error!");
			++nRet;
		}
		if(rv.lengthsq() != 25.0F)
		{
			GTLINE2("VEC2 lengthsq error!");
			++nRet;
		}

		nmv = rv;
		if(nmv.length() != 5)
		{
			GTLINE2("VEC2 length error!");
			++nRet;
		}
		if(nmv.lengthsq() != 25)
		{
			GTLINE2("VEC2 lengthsq error!");
			++nRet;
		}

		if(rv.minimize() != 3.0F)
		{
			GTLINE2("VEC2 get minimize value error!");
			++nRet;
		}
		if(rv.maximize() != 4.0F)
		{
			GTLINE2("VEC2 get maximize value error!");
			++nRet;
		}

		if(nmv.minimize() != 3)
		{
			GTLINE2("VEC2 get minimize value error!");
			++nRet;
		}
		if(nmv.maximize() != 4)
		{
			GTLINE2("VEC2 get maximize value error!");
			++nRet;
		}

		rv.x = 1.0F;
		rv.y = 2.0F;
		nmv.x = 0;
		nmv.y = 3;
		rv.maximize(nmv);
		if(rv.minimize() != 1.0F)
		{
			GTLINE2("VEC2 minimize error!");
			++nRet;
		}
		if(rv.maximize() != 3.0F)
		{
			GTLINE2("VEC2 maximize error!");
			++nRet;
		}

		rv.x = 1.0F;
		rv.y = 2.0F;
		nmv.x = 0;
		nmv.y = 3;
		rv.minimize(nmv);
		if(rv.minimize() != 0.0F)
		{
			GTLINE2("VEC2 minimize error!");
			++nRet;
		}
		if(rv.maximize() != 2.0F)
		{
			GTLINE2("VEC2 maximize error!");
			++nRet;
		}

		nmv.x = 1;
		nmv.y = 2;
		rv.x = 0.0F;
		rv.y = 3.0F;
		nmv.maximize(rv);
		if(nmv.minimize() != 1)
		{
			GTLINE2("VEC2 minimize error!");
			++nRet;
		}
		if(nmv.maximize() != 3)
		{
			GTLINE2("VEC2 maximize error!");
			++nRet;
		}

		nmv.x = 1;
		nmv.y = 2;
		rv.x = 0.0F;
		rv.y = 3.0F;
		nmv.minimize(rv);
		if(nmv.minimize() != 0)
		{
			GTLINE2("VEC2 minimize error!");
			++nRet;
		}
		if(nmv.maximize() != 2)
		{
			GTLINE2("VEC2 maximize error!");
			++nRet;
		}

		rv.x = 3.0F;
		rv.y = 4.0F;
		if(rv.isnormalized())
		{
			GTLINE2("VEC2 isnormalized error!");
			++nRet;
		}
		rv.normalize();
		if(!rv.isnormalized())
		{
			GTLINE2("VEC2 normalize error error!");
			++nRet;
		}

		rv = 0;
		if(!rv.iszero())
		{
			GTLINE2("VEC2 iszero error!");
			++nRet;
		}
		rv = 1.0F;
		if(rv.iszero())
		{
			GTLINE2("VEC2 iszero error!");
			++nRet;
		}

		rv = 4.0F;
		rv.inverse();
		if(rv != 1.0F / 4.0F)
		{
			GTLINE2("VEC2 inverse error!");
			++nRet;
		}

		rv.x = 1.0F;
		rv.y = 2.0F;
		nmv.x = 3;
		nmv.y = 4;
		__RealVecType::_datatype dotr = rv.dot(nmv);
		if(dotr != 11.0F)
		{
			GTLINE2("VEC2 dot error!");
			++nRet;
		}

		rv1 = rv.num(nmv);
		if(rv1.x != 3.0F || rv1.y != 8.0F)
		{
			GTLINE2("VEC2 num error!");
			++nRet;
		}

		rv.x = 1.0F;
		rv.y = 2.0F;
		rv1.x = 3.0F;
		rv1.y = 4.0F;
		nmv = rv + rv1;
		if(nmv.x != 4 || nmv.y != 6)
		{
			GTLINE2("VEC2 operator + error!");
			++nRet;
		}
		nmv = rv - rv1;
		if(nmv.x != -2 || nmv.y != -2)
		{
			GTLINE2("VEC2 operator - error!");
			++nRet;
		}
		nmv = rv * rv1;
		if(nmv.x != 3 || nmv.y != 8)
		{
			GTLINE2("VEC2 operator * error!");
			++nRet;
		}
		nmv = rv / rv1;
		if(nmv.x != 0 || nmv.y != 0)
		{
			GTLINE2("VEC2 operator / error!");
			++nRet;
		}

		rv.x = 1.0F;
		rv.y = 2.0F;
		nmv.x = 3;
		nmv.y = 4;
		rv += nmv;
		if(rv.x != 4.0F || rv.y != 6.0F)
		{
			GTLINE2("VEC2 operator += error!");
			++nRet;
		}
		rv.x = 1.0F;
		rv.y = 2.0F;
		nmv.x = 3;
		nmv.y = 4;
		rv -= nmv;
		if(rv.x != -2.0F || rv.y != -2.0F)
		{
			GTLINE2("VEC2 operator -= error!");
			++nRet;
		}
		rv.x = 1.0F;
		rv.y = 2.0F;
		nmv.x = 3;
		nmv.y = 4;
		rv *= nmv;
		if(rv.x != 3.0F || rv.y != 8.0F)
		{
			GTLINE2("VEC2 operator *= error!");
			++nRet;
		}
		rv.x = 1.0F;
		rv.y = 2.0F;
		nmv.x = 3;
		nmv.y = 4;
		rv /= nmv;
		if(rv.x != 1.0F / 3.0F || rv.y != 2.0F / 4.0F)
		{
			GTLINE2("VEC2 operator /= error!");
			++nRet;
		}

		rv.x = 1.0F;
		rv.y = 2.0F;
		if(rv == 1.0F)
		{
			GTLINE2("VEC2 operator == value error!");
			++nRet;
		}
		if(!(rv != 1.0F))
		{
			GTLINE2("VEC2 operator != value error!");
			++nRet;
		}
		if(!(rv >= 1.0F))
		{
			GTLINE2("VEC2 operator >= value error!");
			++nRet;
		}
		if(rv <= 1.0F)
		{
			GTLINE2("VEC2 operator <= value error!");
			++nRet;
		}
		if(!(rv > 1))
		{
			GTLINE2("VEC2 operator >= value error!");
			++nRet;
		}
		if(rv < 1)
		{
			GTLINE2("VEC2 operator <= value error!");
			++nRet;
		}

		rv.x = 1.0F;
		rv.y = 2.0F;
		if(rv[0] != 1.0F || rv[1] != 2.0F)
		{
			GTLINE2("VEC2 operator [] error!");
			++nRet;
		}

		rv = 0.0F;
		if(rv != 0.0F)
		{
			GTLINE2("VEC2 operator = value error!");
			++nRet;
		}
		if(!rv.isfinited())
		{
			GTLINE2("VEC2 isfinited error!");
			++nRet;
		}
		rv /= 0.0F;
		if(rv.isfinited())
		{
			GTLINE2("VEC2 isfinited error!");
			++nRet;
		}

		return nRet;
	}
};
