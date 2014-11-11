#include "preheader.h"
#include "t_header.h"

namespace GAIA_TEST
{
	extern GAIA::N32 t_math_cookies_vec3(GAIA::FSYS::File& file, GAIA::STREAM::StreamBase& prt)
	{
		GAIA::N32 nRet = 0;

		typedef GAIA::MATH::VEC3<GAIA::REAL> __RealVecType;
		typedef GAIA::MATH::VEC3<GAIA::NM> __NMVecType;

		__RealVecType rv, rv1;
		__NMVecType nmv;
		if(rv.size() != 3)
		{
			GTLINE2("VEC3 size error!");
			++nRet;
		}
		rv = 10.0F;
		if(rv != 10.0F)
		{
			GTLINE2("VEC3 operator = value error!");
			++nRet;
		}
		if(rv != rv)
		{
			GTLINE2("VEC3 != self error!");
			++nRet;
		}
		rv = rv;
		if(rv != 10.0F)
		{
			GTLINE2("VEC3 != const error!");
			++nRet;
		}
		if(rv != 10)
		{
			GTLINE2("VEC3 != const error!");
			++nRet;
		}
		if(rv != rv)
		{
			GTLINE2("VEC3 != self error!");
			++nRet;
		}

		rv.x = 1.0F;
		rv.y = 2.0F;
		rv.z = 0.0F;
		nmv = rv;
		if(nmv.x != 1 || nmv.y != 2 || nmv.z != 0)
		{
			GTLINE2("VEC3 set value error!");
			++nRet;
		}
		if(!(rv == nmv))
		{
			GTLINE2("VEC3 set value error!");
			++nRet;
		}
		if(rv != nmv)
		{
			GTLINE2("VEC3 set value error!");
			++nRet;
		}
		if(!(rv >= nmv))
		{
			GTLINE2("VEC3 set value error!");
			++nRet;
		}
		if(!(rv <= nmv))
		{
			GTLINE2("VEC3 set value error!");
			++nRet;
		}
		if(rv > nmv)
		{
			GTLINE2("VEC3 set value error!");
			++nRet;
		}
		if(rv < nmv)
		{
			GTLINE2("VEC3 set value error!");
			++nRet;
		}

		rv.x = 1.0F;
		rv.y = 2.0F;
		rv.z = 0.0F;
		nmv = rv;
		rv.x = 3.0F;
		rv.y = 4.0F;
		rv.z = 5.0F;
		rv = static_cast<const __NMVecType::_datatype*>(nmv);
		if(rv.x != 1.0F || rv.y != 2.0F || rv.z != 0.0F)
		{
			GTLINE2("VEC3 set pointer error!");
			++nRet;
		}
		if(!(rv == nmv))
		{
			GTLINE2("VEC3 set pointer error!");
			++nRet;
		}
		if(rv != nmv)
		{
			GTLINE2("VEC3 set pointer error!");
			++nRet;
		}
		if(!(rv >= nmv))
		{
			GTLINE2("VEC3 set pointer error!");
			++nRet;
		}
		if(!(rv <= nmv))
		{
			GTLINE2("VEC3 set pointer error!");
			++nRet;
		}
		if(rv > nmv)
		{
			GTLINE2("VEC3 set pointer error!");
			++nRet;
		}
		if(rv < nmv)
		{
			GTLINE2("VEC3 set pointer error!");
			++nRet;
		}

		rv.x = 3.0F;
		rv.y = 4.0F;
		rv.z = 0.0F;
		if(rv.length() != 5.0F)
		{
			GTLINE2("VEC3 length error!");
			++nRet;
		}
		if(rv.lengthsq() != 25.0F)
		{
			GTLINE2("VEC3 lengthsq error!");
			++nRet;
		}

		nmv = rv;
		if(nmv.length() != 5)
		{
			GTLINE2("VEC3 length error!");
			++nRet;
		}
		if(nmv.lengthsq() != 25)
		{
			GTLINE2("VEC3 lengthsq error!");
			++nRet;
		}

		if(rv.minimize() != 0.0F)
		{
			GTLINE2("VEC3 get minimize value error!");
			++nRet;
		}
		if(rv.maximize() != 4.0F)
		{
			GTLINE2("VEC3 get maximize value error!");
			++nRet;
		}

		if(nmv.minimize() != 0)
		{
			GTLINE2("VEC3 get minimize value error!");
			++nRet;
		}
		if(nmv.maximize() != 4)
		{
			GTLINE2("VEC3 get maximize value error!");
			++nRet;
		}

		rv.x = 1.0F;
		rv.y = 2.0F;
		rv.z = 3.0F;
		nmv.x = 0;
		nmv.y = 4;
		nmv.z = 5;
		rv.maximize(nmv);
		if(rv.minimize() != 1.0F)
		{
			GTLINE2("VEC3 minimize error!");
			++nRet;
		}
		if(rv.maximize() != 5.0F)
		{
			GTLINE2("VEC3 maximize error!");
			++nRet;
		}

		rv.x = 1.0F;
		rv.y = 2.0F;
		rv.z = 3.0F;
		nmv.x = 0;
		nmv.y = 4;
		nmv.z = 5;
		rv.minimize(nmv);
		if(rv.minimize() != 0.0F)
		{
			GTLINE2("VEC3 minimize error!");
			++nRet;
		}
		if(rv.maximize() != 3.0F)
		{
			GTLINE2("VEC3 maximize error!");
			++nRet;
		}

		rv.x = 1.0F;
		rv.y = 2.0F;
		rv.z = 3.0F;
		nmv.x = 0;
		nmv.y = 4;
		nmv.z = 5;
		nmv.maximize(rv);
		if(nmv.minimize() != 1)
		{
			GTLINE2("VEC3 minimize error!");
			++nRet;
		}
		if(nmv.maximize() != 5)
		{
			GTLINE2("VEC3 maximize error!");
			++nRet;
		}

		rv.x = 1.0F;
		rv.y = 2.0F;
		rv.z = 3.0F;
		nmv.x = 0;
		nmv.y = 4;
		nmv.z = 5;
		nmv.minimize(rv);
		if(nmv.minimize() != 0)
		{
			GTLINE2("VEC3 minimize error!");
			++nRet;
		}
		if(nmv.maximize() != 3)
		{
			GTLINE2("VEC3 maximize error!");
			++nRet;
		}

		rv.x = 3.0F;
		rv.y = 4.0F;
		rv.z = 0.0F;
		if(rv.isnormalized())
		{
			GTLINE2("VEC3 isnormalized error!");
			++nRet;
		}
		rv.normalize();
		if(!rv.isnormalized())
		{
			GTLINE2("VEC3 normalize error error!");
			++nRet;
		}

		rv = 0;
		if(!rv.iszero())
		{
			GTLINE2("VEC3 iszero error!");
			++nRet;
		}
		rv = 1.0F;
		if(rv.iszero())
		{
			GTLINE2("VEC3 iszero error!");
			++nRet;
		}

		rv = 4.0F;
		rv.inverse();
		if(rv != 1.0F / 4.0F)
		{
			GTLINE2("VEC3 inverse error!");
			++nRet;
		}

		rv.x = 1.0F;
		rv.y = 2.0F;
		rv.z = 3.0F;
		nmv.x = 4;
		nmv.y = 5;
		nmv.z = 6;
		__RealVecType::_datatype dotr = rv.dot(nmv);
		if(dotr != 32.0F)
		{
			GTLINE2("VEC3 dot error!");
			++nRet;
		}

		rv1 = rv.num(nmv);
		if(rv1.x != 4.0F || rv1.y != 10.0F || rv1.z != 18.0F)
		{
			GTLINE2("VEC3 num error!");
			++nRet;
		}

		rv.x = 1.0F;
		rv.y = 2.0F;
		rv.z = 3.0F;
		rv1.x = 4.0F;
		rv1.y = 5.0F;
		rv1.z = 6.0F;
		nmv = rv + rv1;
		if(nmv.x != 5 || nmv.y != 7 || nmv.z != 9)
		{
			GTLINE2("VEC3 operator + error!");
			++nRet;
		}
		nmv = rv - rv1;
		if(nmv.x != -3 || nmv.y != -3 || nmv.z != -3)
		{
			GTLINE2("VEC3 operator - error!");
			++nRet;
		}
		nmv = rv * rv1;
		if(nmv.x != 4 || nmv.y != 10 || nmv.z != 18)
		{
			GTLINE2("VEC3 operator * error!");
			++nRet;
		}
		nmv = rv / rv1;
		if(nmv.x != 0 || nmv.y != 0)
		{
			GTLINE2("VEC3 operator / error!");
			++nRet;
		}

		rv.x = 1.0F;
		rv.y = 2.0F;
		rv.z = 3.0F;
		nmv.x = 4;
		nmv.y = 5;
		nmv.z = 6;
		rv += nmv;
		if(rv.x != 5.0F || rv.y != 7.0F || rv.z != 9.0F)
		{
			GTLINE2("VEC3 operator += error!");
			++nRet;
		}
		rv.x = 1.0F;
		rv.y = 2.0F;
		rv.z = 3.0F;
		nmv.x = 4;
		nmv.y = 5;
		nmv.z = 6;
		rv -= nmv;
		if(rv.x != -3.0F || rv.y != -3.0F || rv.z != -3.0F)
		{
			GTLINE2("VEC3 operator -= error!");
			++nRet;
		}
		rv.x = 1.0F;
		rv.y = 2.0F;
		rv.z = 3.0F;
		nmv.x = 4;
		nmv.y = 5;
		nmv.z = 6;
		rv *= nmv;
		if(rv.x != 4.0F || rv.y != 10.0F || rv.z != 18.0F)
		{
			GTLINE2("VEC3 operator *= error!");
			++nRet;
		}
		rv.x = 1.0F;
		rv.y = 2.0F;
		rv.z = 3.0F;
		nmv.x = 4;
		nmv.y = 5;
		nmv.z = 6;
		rv /= nmv;
		if(rv.x != 1.0F / 4.0F || rv.y != 2.0F / 5.0F || rv.z != 3.0F / 6.0F)
		{
			GTLINE2("VEC3 operator /= error!");
			++nRet;
		}

		rv.x = 1.0F;
		rv.y = 2.0F;
		rv.z = 3.0F;
		if(rv == 1.0F)
		{
			GTLINE2("VEC3 operator == value error!");
			++nRet;
		}
		if(!(rv != 1.0F))
		{
			GTLINE2("VEC3 operator != value error!");
			++nRet;
		}
		if(!(rv >= 1.0F))
		{
			GTLINE2("VEC3 operator >= value error!");
			++nRet;
		}
		if(rv <= 1.0F)
		{
			GTLINE2("VEC3 operator <= value error!");
			++nRet;
		}
		if(!(rv > 1))
		{
			GTLINE2("VEC3 operator >= value error!");
			++nRet;
		}
		if(rv < 1)
		{
			GTLINE2("VEC3 operator <= value error!");
			++nRet;
		}

		rv.x = 1.0F;
		rv.y = 2.0F;
		rv.z = 3.0F;
		if(rv[0] != 1.0F || rv[1] != 2.0F || rv[2] != 3.0F)
		{
			GTLINE2("VEC3 operator [] error!");
			++nRet;
		}

		rv = 0.0F;
		if(rv != 0.0F)
		{
			GTLINE2("VEC3 operator = value error!");
			++nRet;
		}
		if(!rv.isfinited())
		{
			GTLINE2("VEC3 isfinited error!");
			++nRet;
		}
		rv /= 0.0F;
		if(rv.isfinited())
		{
			GTLINE2("VEC3 isfinited error!");
			++nRet;
		}

		return nRet;
	}
};
