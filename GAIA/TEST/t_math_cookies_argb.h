#ifndef		__T_MATH_COOKIES_ARGB_H__
#define		__T_MATH_COOKIES_ARGB_H__

namespace GAIATEST
{
	GINL GAIA::N32 t_math_cookies_argb(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;

		typedef GAIA::MATH::ARGB<GAIA::REAL> __ARGBType;
		typedef GAIA::MATH::ARGB<GAIA::N16> __ARGBN16Type;

		__ARGBType argb;
		argb.a = 1;
		argb.r = 2;
		argb.g = 3;
		argb.b = 4;
		__ARGBType argb1;
		argb1 = __ARGBType(1, 2, 3, 4);
		if(argb != argb1)
		{
			GTLINE2("ARGB constructor error!");
			++nRet;
		}
		__ARGBN16Type argbn16;
		argbn16 = __ARGBN16Type(1, 2, 3, 4);
		argb = (__ARGBN16Type::_datatype*)&argbn16;
		if(argb != argb1)
		{
			GTLINE2("ARGB construct error!");
			++nRet;
		}
		if(!GAIA::MATH::xequal(argb.lengthsq(), 2 * 2 + 3 * 3 + 4 * 4))
		{
			GTLINE2("ARGB lengthsq error!");
			++nRet;
		}
		if(!GAIA::MATH::xequal(argb.length(), GAIA::MATH::xsqrt(GAIA::REAL(2 * 2 + 3 * 3 + 4 * 4))))
		{
			GTLINE2("ARGB length error!");
			++nRet;
		}
		if(argb.avg_argb() != (__ARGBType::_datatype)2.5)
		{
			GTLINE2("ARGB avg_argb error!");
			++nRet;
		}
		if(argb.avg_rgb() != (__ARGBType::_datatype)3)
		{
			GTLINE2("ARGB avg_rgb error!");
			++nRet;
		}
		if(argb.max_argb() != (__ARGBType::_datatype)4)
		{
			GTLINE2("ARGB max_argb error!");
			++nRet;
		}
		if(argb.min_argb() != (__ARGBType::_datatype)1)
		{
			GTLINE2("ARGB min_argb error!");
			++nRet;
		}
		if(argb.max_rgb() != (__ARGBType::_datatype)4)
		{
			GTLINE2("ARGB max_rgb error!");
			++nRet;
		}
		if(argb.min_rgb() != (__ARGBType::_datatype)2)
		{
			GTLINE2("ARGB min_rgb error!");
			++nRet;
		}
		argbn16 = __ARGBN16Type(1, 2, 3, 4);
		argb = (__ARGBN16Type::_datatype*)&argbn16;
		if(!(argb == argbn16))
		{
			GTLINE2("ARGB operator == error!");
			++nRet;
		}
		if(argb != argbn16)
		{
			GTLINE2("ARGB operator != error!");
			++nRet;
		}
		if(!(argb >= argbn16))
		{
			GTLINE2("ARGB operator >= error!");
			++nRet;
		}
		if(!(argb <= argbn16))
		{
			GTLINE2("ARGB operator <= error!");
			++nRet;
		}
		if(argb > argbn16)
		{
			GTLINE2("ARGB operator > error!");
			++nRet;
		}
		if(argb > argbn16)
		{
			GTLINE2("ARGB operator < error!");
			++nRet;
		}
		argb = 1;
		if(argb == argb1)
		{
			GTLINE2("ARGB operator == error!");
			++nRet;
		}
		if(!(argb != argb1))
		{
			GTLINE2("ARGB operator != error!");
			++nRet;
		}
		if(argb >= argb1)
		{
			GTLINE2("ARGB operator >= error!");
			++nRet;
		}
		if(!(argb <= argb1))
		{
			GTLINE2("ARGB operator <= error!");
			++nRet;
		}
		if(argb > argb1)
		{
			GTLINE2("ARGB operator > error!");
			++nRet;
		}
		if(!(argb < argb1))
		{
			GTLINE2("ARGB operator < error!");
			++nRet;
		}
		argb = __ARGBType(1, 2, 3, 4);
		if(argb[0] != (__ARGBType::_datatype)1)
		{
			GTLINE2("ARGB operator [] error!");
			++nRet;
		}
		if(argb[1] != (__ARGBType::_datatype)2)
		{
			GTLINE2("ARGB operator [] error!");
			++nRet;
		}
		if(argb[2] != (__ARGBType::_datatype)3)
		{
			GTLINE2("ARGB operator [] error!");
			++nRet;
		}
		if(argb[3] != (__ARGBType::_datatype)4)
		{
			GTLINE2("ARGB operator [] error!");
			++nRet;
		}
		argb = 0.0F;
		if(argb != 0.0F)
		{
			GTLINE2("ARGB operator = value error!");
			++nRet;
		}
		if(!argb.iszero())
		{
			GTLINE2("ARGB operator = value error!");
			++nRet;
		}
		if(!argb.isfinited())
		{
			GTLINE2("ARGB isfinited error!");
			++nRet;
		}
		argb /= 0.0F;
		if(argb.isfinited())
		{
			GTLINE2("ARGB isfinited error!");
			++nRet;
		}

		return nRet;
	}
};

#endif
