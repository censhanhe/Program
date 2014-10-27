#ifndef		__T_MATH_COOKIES_VEC4_H__
#define		__T_MATH_COOKIES_VEC4_H__

namespace GAIA_TEST
{
	GINL GAIA::N32 t_math_cookies_vec4(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;

		typedef GAIA::MATH::VEC4<GAIA::REAL> __RealVecType;
		typedef GAIA::MATH::VEC4<GAIA::NM> __NMVecType;

		__RealVecType rv, rv1;
		__NMVecType nmv;
		if(rv.size() != 4)
		{
			GTLINE2("VEC4 size error!");
			++nRet;
		}
		rv = 10.0F;
		if(rv != 10.0F)
		{
			GTLINE2("VEC4 operator = value error!");
			++nRet;
		}
		if(rv != rv)
		{
			GTLINE2("VEC4 != self error!");
			++nRet;
		}
		rv = rv;
		if(rv != 10.0F)
		{
			GTLINE2("VEC4 != const error!");
			++nRet;
		}
		if(rv != 10)
		{
			GTLINE2("VEC4 != const error!");
			++nRet;
		}
		if(rv != rv)
		{
			GTLINE2("VEC4 != self error!");
			++nRet;
		}

		rv.x = 1.0F;
		rv.y = 2.0F;
		rv.z = 0.0F;
		rv.w = 3.0F;
		nmv = rv;
		if(nmv.x != 1 || nmv.y != 2 || nmv.z != 0 || nmv.w != 3.0F)
		{
			GTLINE2("VEC4 set value error!");
			++nRet;
		}
		if(!(rv == nmv))
		{
			GTLINE2("VEC4 set value error!");
			++nRet;
		}
		if(rv != nmv)
		{
			GTLINE2("VEC4 set value error!");
			++nRet;
		}
		if(!(rv >= nmv))
		{
			GTLINE2("VEC4 set value error!");
			++nRet;
		}
		if(!(rv <= nmv))
		{
			GTLINE2("VEC4 set value error!");
			++nRet;
		}
		if(rv > nmv)
		{
			GTLINE2("VEC4 set value error!");
			++nRet;
		}
		if(rv < nmv)
		{
			GTLINE2("VEC4 set value error!");
			++nRet;
		}

		rv.x = 1.0F;
		rv.y = 2.0F;
		rv.z = 0.0F;
		rv.w = 3.0F;
		nmv = rv;
		rv.x = 3.0F;
		rv.y = 4.0F;
		rv.z = 5.0F;
		rv.w = 6.0F;
		rv = static_cast<const __NMVecType::_datatype*>(nmv);
		if(rv.x != 1.0F || rv.y != 2.0F || rv.z != 0.0F || rv.w != 3.0F)
		{
			GTLINE2("VEC4 set pointer error!");
			++nRet;
		}
		if(!(rv == nmv))
		{
			GTLINE2("VEC4 set pointer error!");
			++nRet;
		}
		if(rv != nmv)
		{
			GTLINE2("VEC4 set pointer error!");
			++nRet;
		}
		if(!(rv >= nmv))
		{
			GTLINE2("VEC4 set pointer error!");
			++nRet;
		}
		if(!(rv <= nmv))
		{
			GTLINE2("VEC4 set pointer error!");
			++nRet;
		}
		if(rv > nmv)
		{
			GTLINE2("VEC4 set pointer error!");
			++nRet;
		}
		if(rv < nmv)
		{
			GTLINE2("VEC4 set pointer error!");
			++nRet;
		}

		rv.x = 3.0F;
		rv.y = 4.0F;
		rv.z = 0.0F;
		rv.w = 1.0F;
		if(rv.length() != 5.0F)
		{
			GTLINE2("VEC4 length error!");
			++nRet;
		}
		if(rv.lengthsq() != 25.0F)
		{
			GTLINE2("VEC4 lengthsq error!");
			++nRet;
		}

		nmv = rv;
		if(nmv.length() != 5)
		{
			GTLINE2("VEC4 length error!");
			++nRet;
		}
		if(nmv.lengthsq() != 25)
		{
			GTLINE2("VEC4 lengthsq error!");
			++nRet;
		}

		if(rv.minimize() != 0.0F)
		{
			GTLINE2("VEC4 get minimize value error!");
			++nRet;
		}
		if(rv.maximize() != 4.0F)
		{
			GTLINE2("VEC4 get maximize value error!");
			++nRet;
		}

		if(nmv.minimize() != 0)
		{
			GTLINE2("VEC4 get minimize value error!");
			++nRet;
		}
		if(nmv.maximize() != 4)
		{
			GTLINE2("VEC4 get maximize value error!");
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
			GTLINE2("VEC4 minimize error!");
			++nRet;
		}
		if(rv.maximize() != 5.0F)
		{
			GTLINE2("VEC4 maximize error!");
			++nRet;
		}

		rv.x = 1.0F;
		rv.y = 2.0F;
		rv.z = 3.0F;
		rv.w = 4.0F;
		nmv.x = 0;
		nmv.y = 5;
		nmv.z = 6;
		nmv.w = 7;
		rv.minimize(nmv);
		if(rv.minimize() != 0.0F)
		{
			GTLINE2("VEC4 minimize error!");
			++nRet;
		}
		if(rv.maximize() != 4.0F)
		{
			GTLINE2("VEC4 maximize error!");
			++nRet;
		}

		rv.x = 1.0F;
		rv.y = 2.0F;
		rv.z = 3.0F;
		rv.w = 4.0F;
		nmv.x = 0;
		nmv.y = 5;
		nmv.z = 6;
		nmv.w = 7;
		nmv.maximize(rv);
		if(nmv.minimize() != 1)
		{
			GTLINE2("VEC4 minimize error!");
			++nRet;
		}
		if(nmv.maximize() != 7)
		{
			GTLINE2("VEC4 maximize error!");
			++nRet;
		}

		rv.x = 1.0F;
		rv.y = 2.0F;
		rv.z = 3.0F;
		rv.w = 4.0F;
		nmv.x = 0;
		nmv.y = 5;
		nmv.z = 6;
		nmv.w = 7;
		nmv.minimize(rv);
		if(nmv.minimize() != 0)
		{
			GTLINE2("VEC4 minimize error!");
			++nRet;
		}
		if(nmv.maximize() != 4)
		{
			GTLINE2("VEC4 maximize error!");
			++nRet;
		}

		rv.x = 3.0F;
		rv.y = 4.0F;
		rv.z = 0.0F;
		rv.w = 1.0F;
		if(rv.isnormalized())
		{
			GTLINE2("VEC4 isnormalized error!");
			++nRet;
		}
		rv.normalize();
		if(!rv.isnormalized())
		{
			GTLINE2("VEC4 normalize error error!");
			++nRet;
		}

		rv = 0;
		if(!rv.iszero())
		{
			GTLINE2("VEC4 iszero error!");
			++nRet;
		}
		rv = 1.0F;
		if(rv.iszero())
		{
			GTLINE2("VEC4 iszero error!");
			++nRet;
		}

		rv = 4.0F;
		rv.inverse();
		if(rv != 1.0F / 4.0F)
		{
			GTLINE2("VEC4 inverse error!");
			++nRet;
		}

		rv.x = 1.0F;
		rv.y = 2.0F;
		rv.z = 3.0F;
		rv.w = 4.0F;
		nmv.x = 5;
		nmv.y = 6;
		nmv.z = 7;
		nmv.w = 8;
		__RealVecType::_datatype dotr = rv.dot(nmv);
		if(dotr != 1216.0F)
		{
			GTLINE2("VEC4 dot error!");
			++nRet;
		}

		rv1 = rv.num(nmv);
		if(rv1.x != 5.0F || rv1.y != 12.0F || rv1.z != 21.0F || rv1.w != 32.0F)
		{
			GTLINE2("VEC4 num error!");
			++nRet;
		}

		rv.x = 1.0F;
		rv.y = 2.0F;
		rv.z = 3.0F;
		rv.w = 4.0F;
		rv1.x = 5.0F;
		rv1.y = 6.0F;
		rv1.z = 7.0F;
		rv1.w = 8.0F;
		nmv = rv + rv1;
		if(nmv.x != 6 || nmv.y != 8 || nmv.z != 10 || nmv.w != 12)
		{
			GTLINE2("VEC4 operator + error!");
			++nRet;
		}
		nmv = rv - rv1;
		if(nmv.x != -4 || nmv.y != -4 || nmv.z != -4 || nmv.w != -4)
		{
			GTLINE2("VEC4 operator - error!");
			++nRet;
		}
		nmv = rv * rv1;
		if(nmv.x != 5 || nmv.y != 12 || nmv.z != 21 || nmv.w != 32)
		{
			GTLINE2("VEC4 operator * error!");
			++nRet;
		}
		nmv = rv / rv1;
		if(nmv.x != 0 || nmv.y != 0)
		{
			GTLINE2("VEC4 operator / error!");
			++nRet;
		}

		rv.x = 1.0F;
		rv.y = 2.0F;
		rv.z = 3.0F;
		rv.w = 4.0F;
		nmv.x = 5;
		nmv.y = 6;
		nmv.z = 7;
		nmv.w = 8;
		rv += nmv;
		if(rv.x != 6.0F || rv.y != 8.0F || rv.z != 10.0F || rv.w != 12.0F)
		{
			GTLINE2("VEC4 operator += error!");
			++nRet;
		}
		rv.x = 1.0F;
		rv.y = 2.0F;
		rv.z = 3.0F;
		rv.w = 4.0F;
		nmv.x = 5;
		nmv.y = 6;
		nmv.z = 7;
		nmv.w = 8;
		rv -= nmv;
		if(rv.x != -4.0F || rv.y != -4.0F || rv.z != -4.0F || rv.w != -4.0F)
		{
			GTLINE2("VEC4 operator -= error!");
			++nRet;
		}
		rv.x = 1.0F;
		rv.y = 2.0F;
		rv.z = 3.0F;
		rv.w = 4.0F;
		nmv.x = 5;
		nmv.y = 6;
		nmv.z = 7;
		nmv.w = 8;
		rv *= nmv;
		if(rv.x != 5.0F || rv.y != 12.0F || rv.z != 21.0F || rv.w != 32.0F)
		{
			GTLINE2("VEC4 operator *= error!");
			++nRet;
		}
		rv.x = 1.0F;
		rv.y = 2.0F;
		rv.z = 3.0F;
		rv.w = 4.0F;
		nmv.x = 5;
		nmv.y = 6;
		nmv.z = 7;
		nmv.w = 8;
		rv /= nmv;
		if(rv.x != 1.0F / 5.0F || rv.y != 2.0F / 6.0F || rv.z != 3.0F / 7.0F || rv.w != 4.0F / 8.0F)
		{
			GTLINE2("VEC4 operator /= error!");
			++nRet;
		}

		rv.x = 1.0F;
		rv.y = 2.0F;
		rv.z = 3.0F;
		rv.w = 4.0F;
		if(rv == 1.0F)
		{
			GTLINE2("VEC4 operator == value error!");
			++nRet;
		}
		if(!(rv != 1.0F))
		{
			GTLINE2("VEC4 operator != value error!");
			++nRet;
		}
		if(!(rv >= 1.0F))
		{
			GTLINE2("VEC4 operator >= value error!");
			++nRet;
		}
		if(rv <= 1.0F)
		{
			GTLINE2("VEC4 operator <= value error!");
			++nRet;
		}
		if(!(rv > 1))
		{
			GTLINE2("VEC4 operator >= value error!");
			++nRet;
		}
		if(rv < 1)
		{
			GTLINE2("VEC4 operator <= value error!");
			++nRet;
		}

		rv.x = 1.0F;
		rv.y = 2.0F;
		rv.z = 3.0F;
		rv.w = 4.0F;
		if(rv[0] != 1.0F || rv[1] != 2.0F || rv[2] != 3.0F || rv[3] != 4.0F)
		{
			GTLINE2("VEC4 operator [] error!");
			++nRet;
		}

		rv = 0.0F;
		if(rv != 0.0F)
		{
			GTLINE2("VEC4 operator = value error!");
			++nRet;
		}
		if(!rv.isfinited())
		{
			GTLINE2("VEC4 isfinited error!");
			++nRet;
		}
		rv /= 0.0F;
		if(rv.isfinited())
		{
			GTLINE2("VEC4 isfinited error!");
			++nRet;
		}

		return nRet;
	}
};

#endif
