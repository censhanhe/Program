#include "preheader.h"
#include "t_header.h"

namespace GAIA_TEST
{
	extern GAIA::N32 t_math_cookies_nrgb(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;

		typedef GAIA::MATH::NRGB<GAIA::REAL> __NRGBType;
		typedef GAIA::MATH::NRGB<GAIA::N16> __NRGBN16Type;

		__NRGBType nrgb;
		if(nrgb.size() != 3)
		{
			GTLINE2("NRGB size error!");
			++nRet;
		}
		nrgb.r = 2;
		nrgb.g = 3;
		nrgb.b = 4;
		__NRGBType nrgb1;
		nrgb1 = __NRGBType(2, 3, 4);
		if(nrgb != nrgb1)
		{
			GTLINE2("NRGB constructor error!");
			++nRet;
		}
		__NRGBN16Type nrgbn16;
		nrgbn16 = __NRGBN16Type(2, 3, 4);
		nrgb = (__NRGBN16Type::_datatype*)&nrgbn16;
		if(nrgb != nrgb1)
		{
			GTLINE2("NRGB construct error!");
			++nRet;
		}
		if(!GAIA::MATH::xequal(nrgb.lengthsq(), 2 * 2 + 3 * 3 + 4 * 4))
		{
			GTLINE2("NRGB lengthsq error!");
			++nRet;
		}
		if(!GAIA::MATH::xequal(nrgb.length(), GAIA::MATH::xsqrt(GAIA::REAL(2 * 2 + 3 * 3 + 4 * 4))))
		{
			GTLINE2("NRGB length error!");
			++nRet;
		}
		if(nrgb.avg_rgb() != (__NRGBType::_datatype)3)
		{
			GTLINE2("NRGB avg_rgb error!");
			++nRet;
		}
		if(nrgb.max_rgb() != (__NRGBType::_datatype)4)
		{
			GTLINE2("NRGB max_rgb error!");
			++nRet;
		}
		if(nrgb.min_rgb() != (__NRGBType::_datatype)2)
		{
			GTLINE2("NRGB min_rgb error!");
			++nRet;
		}
		nrgbn16 = __NRGBN16Type(2, 3, 4);
		nrgb = (__NRGBN16Type::_datatype*)&nrgbn16;
		if(!(nrgb == nrgbn16))
		{
			GTLINE2("NRGB operator == error!");
			++nRet;
		}
		if(nrgb != nrgbn16)
		{
			GTLINE2("NRGB operator != error!");
			++nRet;
		}
		if(!(nrgb >= nrgbn16))
		{
			GTLINE2("NRGB operator >= error!");
			++nRet;
		}
		if(!(nrgb <= nrgbn16))
		{
			GTLINE2("NRGB operator <= error!");
			++nRet;
		}
		if(nrgb > nrgbn16)
		{
			GTLINE2("NRGB operator > error!");
			++nRet;
		}
		if(nrgb > nrgbn16)
		{
			GTLINE2("NRGB operator < error!");
			++nRet;
		}
		nrgb = 1;
		if(nrgb == nrgb1)
		{
			GTLINE2("NRGB operator == error!");
			++nRet;
		}
		if(!(nrgb != nrgb1))
		{
			GTLINE2("NRGB operator != error!");
			++nRet;
		}
		if(nrgb >= nrgb1)
		{
			GTLINE2("NRGB operator >= error!");
			++nRet;
		}
		if(!(nrgb <= nrgb1))
		{
			GTLINE2("NRGB operator <= error!");
			++nRet;
		}
		if(nrgb > nrgb1)
		{
			GTLINE2("NRGB operator > error!");
			++nRet;
		}
		if(!(nrgb < nrgb1))
		{
			GTLINE2("NRGB operator < error!");
			++nRet;
		}
		nrgb = __NRGBType(2, 3, 4);
		if(nrgb[2] != (__NRGBType::_datatype)2)
		{
			GTLINE2("NRGB operator [] error!");
			++nRet;
		}
		if(nrgb[1] != (__NRGBType::_datatype)3)
		{
			GTLINE2("NRGB operator [] error!");
			++nRet;
		}
		if(nrgb[0] != (__NRGBType::_datatype)4)
		{
			GTLINE2("NRGB operator [] error!");
			++nRet;
		}
		nrgb = 0.0F;
		if(nrgb != 0.0F)
		{
			GTLINE2("NRGB operator = value error!");
			++nRet;
		}
		if(!nrgb.iszero())
		{
			GTLINE2("NRGB operator = value error!");
			++nRet;
		}
		if(!nrgb.isfinited())
		{
			GTLINE2("NRGB isfinited error!");
			++nRet;
		}
		nrgb /= 0.0F;
		if(nrgb.isfinited())
		{
			GTLINE2("NRGB isfinited error!");
			++nRet;
		}

		return nRet;
	}
};
