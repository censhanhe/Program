#ifndef		__T_MATH_COOKIES_AABR_H__
#define		__T_MATH_COOKIES_AABR_H__

namespace GAIATEST
{
	GINL GAIA::N32 t_math_cookies_aabr(GAIA::FILESYSTEM::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;

		typedef GAIA::MATH::AABR<GAIA::REAL> __AABRType;
		typedef GAIA::MATH::AABR<GAIA::N16> __AABRTypeN16;
		__AABRType aabr;
		aabr.identity();
		if(!aabr.isidentity())
		{
			GTLINE2("AABR identity error!");
			++nRet;
		}
		__AABRType::_vectype center = aabr.center();
		if(center != (__AABRType::_datatype)0)
		{
			GTLINE2("AABR center error!");
			++nRet;
		}
		__AABRType::_vectype size = aabr.size();
		if(size != (__AABRType::_datatype)-2)
		{
			GTLINE2("AABR size error!");
			++nRet;
		}
		aabr.expand((__AABRType::_vectype)+10);
		aabr.expand((__AABRType::_vectype)-10);
		center = aabr.center();
		if(center != (__AABRType::_datatype)0)
		{
			GTLINE2("AABR center error!");
			++nRet;
		}
		size = aabr.size();
		if(size != (__AABRType::_datatype)20)
		{
			GTLINE2("AABR size error!");
			++nRet;
		}
		if(aabr.long_radius() != GAIA::MATH::xsqrt(200.0))
		{
			GTLINE2("AABR long_radius error!");
			++nRet;
		}
		if(aabr.short_radius() != (__AABRType::_datatype)10)
		{
			GTLINE2("AABR short error!");
			++nRet;
		}
		if(aabr.width() != (__AABRType::_datatype)20)
		{
			GTLINE2("AABR width error!");
			++nRet;
		}
		if(aabr.height() != (__AABRType::_datatype)20)
		{
			GTLINE2("AABR height error!");
			++nRet;
		}
		aabr += (__AABRType::_vectype)10;
		if(aabr.pmin != (__AABRType::_vectype)0)
		{
			GTLINE2("AABR += error!");
			++nRet;
		}
		aabr -= (__AABRType::_vectype)10;
		aabr *= (__AABRType::_vectype)10;
		aabr /= (__AABRType::_vectype)10;
		center = aabr.center();
		if(center != (__AABRType::_datatype)0)
		{
			GTLINE2("AABR += or -= or *= or /= error!");
			++nRet;
		}
		size = aabr.size();
		if(size != (__AABRType::_datatype)20)
		{
			GTLINE2("AABR += or -= or *= or /= error!");
			++nRet;
		}
		if(aabr.long_radius() != GAIA::MATH::xsqrt(200.0))
		{
			GTLINE2("AABR += or -= or *= or /= error!");
			++nRet;
		}
		if(aabr.short_radius() != (__AABRType::_datatype)10)
		{
			GTLINE2("AABR += or -= or *= or /= error!");
			++nRet;
		}
		if(aabr.width() != (__AABRType::_datatype)20)
		{
			GTLINE2("AABR += or -= or *= or /= error!");
			++nRet;
		}
		if(aabr.height() != (__AABRType::_datatype)20)
		{
			GTLINE2("AABR += or -= or *= or /= error!");
			++nRet;
		}
		aabr = aabr + (__AABRType::_vectype)10;
		if(aabr.pmin != (__AABRType::_vectype)0)
		{
			GTLINE2("AABR + error!");
			++nRet;
		}
		aabr = aabr - (__AABRType::_vectype)10;
		aabr = aabr * (__AABRType::_vectype)10;
		aabr = aabr / (__AABRType::_vectype)10;
		center = aabr.center();
		if(center != (__AABRType::_datatype)0)
		{
			GTLINE2("AABR += or -= or *= or /= error!");
			++nRet;
		}
		size = aabr.size();
		if(size != (__AABRType::_datatype)20)
		{
			GTLINE2("AABR += or -= or *= or /= error!");
			++nRet;
		}
		if(aabr.long_radius() != GAIA::MATH::xsqrt(200.0))
		{
			GTLINE2("AABR += or -= or *= or /= error!");
			++nRet;
		}
		if(aabr.short_radius() != (__AABRType::_datatype)10)
		{
			GTLINE2("AABR += or -= or *= or /= error!");
			++nRet;
		}
		if(aabr.width() != (__AABRType::_datatype)20)
		{
			GTLINE2("AABR += or -= or *= or /= error!");
			++nRet;
		}
		if(aabr.height() != (__AABRType::_datatype)20)
		{
			GTLINE2("AABR += or -= or *= or /= error!");
			++nRet;
		}
		__AABRTypeN16 aabr16 = aabr;
		if(!(aabr16 == aabr))
		{
			GTLINE2("AABR operator == error!");
			++nRet;
		}
		if(aabr16 != aabr)
		{
			GTLINE2("AABR operator != error!");
			++nRet;
		}
		if(!(aabr16 <= aabr))
		{
			GTLINE2("AABR operator <= error!");
			++nRet;
		}
		if(!(aabr16 >= aabr))
		{
			GTLINE2("AABR operator >= error!");
			++nRet;
		}
		if(aabr16 < aabr)
		{
			GTLINE2("AABR operator < error!");
			++nRet;
		}
		if(aabr16 > aabr)
		{
			GTLINE2("AABR operator > error!");
			++nRet;
		}
		aabr16 = 10;
		if(aabr16 == aabr)
		{
			GTLINE2("AABR operator == error!");
			++nRet;
		}
		if(!(aabr16 != aabr))
		{
			GTLINE2("AABR operator != error!");
			++nRet;
		}
		if(aabr16 <= aabr)
		{
			GTLINE2("AABR operator <= error!");
			++nRet;
		}
		if(!(aabr16 >= aabr))
		{
			GTLINE2("AABR operator >= error!");
			++nRet;
		}
		if(aabr16 < aabr)
		{
			GTLINE2("AABR operator < error!");
			++nRet;
		}
		if(!(aabr16 > aabr))
		{
			GTLINE2("AABR operator > error!");
			++nRet;
		}
		aabr16 = (__AABRType::_datatype*)&aabr;
		if(!(aabr16 == aabr))
		{
			GTLINE2("AABR operator == error!");
			++nRet;
		}
		if(aabr16 != aabr)
		{
			GTLINE2("AABR operator != error!");
			++nRet;
		}
		if(!(aabr16 <= aabr))
		{
			GTLINE2("AABR operator <= error!");
			++nRet;
		}
		if(!(aabr16 >= aabr))
		{
			GTLINE2("AABR operator >= error!");
			++nRet;
		}
		if(aabr16 < aabr)
		{
			GTLINE2("AABR operator < error!");
			++nRet;
		}
		if(aabr16 > aabr)
		{
			GTLINE2("AABR operator > error!");
			++nRet;
		}
		if(aabr[0] != (__AABRType::_datatype)-10)
		{
			GTLINE2("AABR operator [] error!");
			++nRet;
		}
		if(aabr[1] != (__AABRType::_datatype)-10)
		{
			GTLINE2("AABR operator [] error!");
			++nRet;
		}
		if(aabr[2] != (__AABRType::_datatype)+10)
		{
			GTLINE2("AABR operator [] error!");
			++nRet;
		}
		if(aabr[3] != (__AABRType::_datatype)+10)
		{
			GTLINE2("AABR operator [] error!");
			++nRet;
		}

		return nRet;
	}
};

#endif