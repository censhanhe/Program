#include "preheader.h"
#include "t_header.h"

namespace GAIA_TEST
{
	extern GAIA::N32 t_math_cookies_aabb(GAIA::FSYS::File& file, GAIA::STREAM::StreamBase& stm)
	{
		GAIA::N32 nRet = 0;

		typedef GAIA::MATH::AABB<GAIA::REAL> __AABBType;
		typedef GAIA::MATH::AABB<GAIA::N16> __AABBTypeN16;
		__AABBType aabb;
		if(aabb.size() != 6)
		{
			GTLINE2("AABB size error!");
			++nRet;
		}
		aabb.identity();
		if(!aabb.isidentity())
		{
			GTLINE2("AABB identity error!");
			++nRet;
		}
		__AABBType::_vectype center = aabb.center();
		if(center != (__AABBType::_datatype)0)
		{
			GTLINE2("AABB center error!");
			++nRet;
		}
		__AABBType::_vectype long_size = aabb.long_size();
		if(long_size != (__AABBType::_datatype)-2)
		{
			GTLINE2("AABB long_size error!");
			++nRet;
		}
		aabb.expand((__AABBType::_vectype)+10);
		aabb.expand((__AABBType::_vectype)-10);
		center = aabb.center();
		if(center != (__AABBType::_datatype)0)
		{
			GTLINE2("AABB center error!");
			++nRet;
		}
		long_size = aabb.long_size();
		if(long_size != (__AABBType::_datatype)20)
		{
			GTLINE2("AABB long_size error!");
			++nRet;
		}
		if(!GAIA::MATH::xequal(aabb.long_radius(), GAIA::MATH::xsqrt(300.0)))
		{
			GTLINE2("AABB long_radius error!");
			++nRet;
		}
		if(aabb.short_radius() != (__AABBType::_datatype)10)
		{
			GTLINE2("AABB short error!");
			++nRet;
		}
		if(aabb.width() != (__AABBType::_datatype)20)
		{
			GTLINE2("AABB width error!");
			++nRet;
		}
		if(aabb.height() != (__AABBType::_datatype)20)
		{
			GTLINE2("AABB height error!");
			++nRet;
		}
		if(aabb.depth() != (__AABBType::_datatype)20)
		{
			GTLINE2("AABB depth error!");
			++nRet;
		}
		aabb += (__AABBType::_vectype)10;
		if(aabb.pmin != (__AABBType::_vectype)0)
		{
			GTLINE2("AABB += error!");
			++nRet;
		}
		aabb -= (__AABBType::_vectype)10;
		aabb *= (__AABBType::_vectype)10;
		aabb /= (__AABBType::_vectype)10;
		center = aabb.center();
		if(center != (__AABBType::_datatype)0)
		{
			GTLINE2("AABB += or -= or *= or /= error!");
			++nRet;
		}
		long_size = aabb.long_size();
		if(long_size != (__AABBType::_datatype)20)
		{
			GTLINE2("AABB += or -= or *= or /= error!");
			++nRet;
		}
		if(!GAIA::MATH::xequal(aabb.long_radius(), GAIA::MATH::xsqrt(300.0)))
		{
			GTLINE2("AABB += or -= or *= or /= error!");
			++nRet;
		}
		if(aabb.short_radius() != (__AABBType::_datatype)10)
		{
			GTLINE2("AABB += or -= or *= or /= error!");
			++nRet;
		}
		if(aabb.width() != (__AABBType::_datatype)20)
		{
			GTLINE2("AABB += or -= or *= or /= error!");
			++nRet;
		}
		if(aabb.height() != (__AABBType::_datatype)20)
		{
			GTLINE2("AABB += or -= or *= or /= error!");
			++nRet;
		}
		if(aabb.depth() != (__AABBType::_datatype)20)
		{
			GTLINE2("AABB += or -= or *= or /= error!");
			++nRet;
		}
		aabb = aabb + (__AABBType::_vectype)10;
		if(aabb.pmin != (__AABBType::_vectype)0)
		{
			GTLINE2("AABB + error!");
			++nRet;
		}
		aabb = aabb - (__AABBType::_vectype)10;
		aabb = aabb * (__AABBType::_vectype)10;
		aabb = aabb / (__AABBType::_vectype)10;
		center = aabb.center();
		if(center != (__AABBType::_datatype)0)
		{
			GTLINE2("AABB += or -= or *= or /= error!");
			++nRet;
		}
		long_size = aabb.long_size();
		if(long_size != (__AABBType::_datatype)20)
		{
			GTLINE2("AABB += or -= or *= or /= error!");
			++nRet;
		}
		if(!GAIA::MATH::xequal(aabb.long_radius(), GAIA::MATH::xsqrt(300.0)))
		{
			GTLINE2("AABB += or -= or *= or /= error!");
			++nRet;
		}
		if(aabb.short_radius() != (__AABBType::_datatype)10)
		{
			GTLINE2("AABB += or -= or *= or /= error!");
			++nRet;
		}
		if(aabb.width() != (__AABBType::_datatype)20)
		{
			GTLINE2("AABB += or -= or *= or /= error!");
			++nRet;
		}
		if(aabb.height() != (__AABBType::_datatype)20)
		{
			GTLINE2("AABB += or -= or *= or /= error!");
			++nRet;
		}
		if(aabb.depth() != (__AABBType::_datatype)20)
		{
			GTLINE2("AABB += or -= or *= or /= error!");
			++nRet;
		}
		__AABBTypeN16 aabb16 = aabb;
		if(!(aabb16 == aabb))
		{
			GTLINE2("AABB operator == error!");
			++nRet;
		}
		if(aabb16 != aabb)
		{
			GTLINE2("AABB operator != error!");
			++nRet;
		}
		if(!(aabb16 <= aabb))
		{
			GTLINE2("AABB operator <= error!");
			++nRet;
		}
		if(!(aabb16 >= aabb))
		{
			GTLINE2("AABB operator >= error!");
			++nRet;
		}
		if(aabb16 < aabb)
		{
			GTLINE2("AABB operator < error!");
			++nRet;
		}
		if(aabb16 > aabb)
		{
			GTLINE2("AABB operator > error!");
			++nRet;
		}
		aabb16 = 10;
		if(aabb16 == aabb)
		{
			GTLINE2("AABB operator == error!");
			++nRet;
		}
		if(!(aabb16 != aabb))
		{
			GTLINE2("AABB operator != error!");
			++nRet;
		}
		if(aabb16 <= aabb)
		{
			GTLINE2("AABB operator <= error!");
			++nRet;
		}
		if(!(aabb16 >= aabb))
		{
			GTLINE2("AABB operator >= error!");
			++nRet;
		}
		if(aabb16 < aabb)
		{
			GTLINE2("AABB operator < error!");
			++nRet;
		}
		if(!(aabb16 > aabb))
		{
			GTLINE2("AABB operator > error!");
			++nRet;
		}
		aabb16 = (__AABBType::_datatype*)&aabb.pmin;
		if(!(aabb16 == aabb))
		{
			GTLINE2("AABB operator == error!");
			++nRet;
		}
		if(aabb16 != aabb)
		{
			GTLINE2("AABB operator != error!");
			++nRet;
		}
		if(!(aabb16 <= aabb))
		{
			GTLINE2("AABB operator <= error!");
			++nRet;
		}
		if(!(aabb16 >= aabb))
		{
			GTLINE2("AABB operator >= error!");
			++nRet;
		}
		if(aabb16 < aabb)
		{
			GTLINE2("AABB operator < error!");
			++nRet;
		}
		if(aabb16 > aabb)
		{
			GTLINE2("AABB operator > error!");
			++nRet;
		}
		if(aabb[0] != (__AABBType::_datatype)-10)
		{
			GTLINE2("AABB operator [] error!");
			++nRet;
		}
		if(aabb[1] != (__AABBType::_datatype)-10)
		{
			GTLINE2("AABB operator [] error!");
			++nRet;
		}
		if(aabb[2] != (__AABBType::_datatype)-10)
		{
			GTLINE2("AABB operator [] error!");
			++nRet;
		}
		if(aabb[3] != (__AABBType::_datatype)+10)
		{
			GTLINE2("AABB operator [] error!");
			++nRet;
		}
		if(aabb[4] != (__AABBType::_datatype)+10)
		{
			GTLINE2("AABB operator [] error!");
			++nRet;
		}
		if(aabb[5] != (__AABBType::_datatype)+10)
		{
			GTLINE2("AABB operator [] error!");
			++nRet;
		}
		aabb = 0.0F;
		if(aabb != 0.0F)
		{
			GTLINE2("AABB operator = value error!");
			++nRet;
		}
		if(!aabb.iszero())
		{
			GTLINE2("AABB operator = value error!");
			++nRet;
		}
		if(!aabb.isfinited())
		{
			GTLINE2("AABB isfinited error!");
			++nRet;
		}
		aabb.pmax /= 0.0F;
		if(aabb.isfinited())
		{
			GTLINE2("AABB isfinited error!");
			++nRet;
		}

		return nRet;
	}
};
