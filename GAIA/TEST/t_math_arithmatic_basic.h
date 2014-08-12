#ifndef		__T_MATH_ARITHMATIC_BASIC_H__
#define		__T_MATH_ARITHMATIC_BASIC_H__

namespace GAIATEST
{
	GINL GAIA::N32 t_math_arithmatic_basic(GAIA::FILESYSTEM::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;

		if(GAIA::MATH::xabs(-1.23456F) != 1.23456F)
		{
			GTLINE2("xabs negative float error!");
			++nRet;
		}
		if(GAIA::MATH::xabs(1.23456F) != 1.23456F)
		{
			GTLINE2("xabs float error!");
			++nRet;
		}
		if(GAIA::MATH::xabs(-1) != 1)
		{
			GTLINE2("xabs int error!");
			++nRet;
		}
		if(GAIA::MATH::xsign(-1.23456F) != -1.0F)
		{
			GTLINE2("xsign negative float error!");
			++nRet;
		}
		if(GAIA::MATH::xsign(1.23456F) != 1.0F)
		{
			GTLINE2("xsign float error!");
			++nRet;
		}
		if(GAIA::MATH::xsign(-1) != -1)
		{
			GTLINE2("xsign negative int error!");
			++nRet;
		}
		if(GAIA::MATH::xsign(1) != 1)
		{
			GTLINE2("xsign int error!");
			++nRet;
		}
		if(GAIA::MATH::xclamp(0.5F, 0.0F, 1.0F) != 0.5F)
		{
			GTLINE2("xclamp float error!");
			++nRet;
		}
		if(GAIA::MATH::xclamp(-0.5F, 0.0F, 1.0F) != 0.0F)
		{
			GTLINE2("xclamp float error!");
			++nRet;
		}
		if(GAIA::MATH::xclamp(1.5F, 0.0F, 1.0F) != 1.0F)
		{
			GTLINE2("xclamp float error!");
			++nRet;
		}
		if(GAIA::MATH::xsaturate(0.5F) != 0.5F)
		{
			GTLINE2("xsaturate float error!");
			++nRet;
		}
		if(GAIA::MATH::xsaturate(-0.5F) != 0.0F)
		{
			GTLINE2("xsaturate float error!");
			++nRet;
		}
		if(GAIA::MATH::xsaturate(1.5F) != 1.0F)
		{
			GTLINE2("xsaturate float error!");
			++nRet;
		}
		if(GAIA::MATH::xfloor(0.5F) != 0.0F)
		{
			GTLINE2("xfloor error!");
			++nRet;
		}
		if(GAIA::MATH::xfloor(1.1F) != 1.0F)
		{
			GTLINE2("xfloor float error!");
			++nRet;
		}
		if(GAIA::MATH::xfloor(0) != 0)
		{
			GTLINE2("xfloor float error!");
			++nRet;
		}
		if(GAIA::MATH::xfloor(1) != 1)
		{
			GTLINE2("xfloor int error!");
			++nRet;
		}
		if(GAIA::MATH::xfloor(-1) != -1)
		{
			GTLINE2("xfloor negative int error!");
			++nRet;
		}
		if(GAIA::MATH::xceil(0.5F) != 1.0F)
		{
			GTLINE2("xceil error!");
			++nRet;
		}
		if(GAIA::MATH::xceil(1.1F) != 2.0F)
		{
			GTLINE2("xceil float error!");
			++nRet;
		}
		if(GAIA::MATH::xceil(0) != 0)
		{
			GTLINE2("xceil float error!");
			++nRet;
		}
		if(GAIA::MATH::xceil(1) != 1)
		{
			GTLINE2("xceil int error!");
			++nRet;
		}
		if(GAIA::MATH::xceil(-1) != -1)
		{
			GTLINE2("xceil negative int error!");
			++nRet;
		}
		if(!GAIA::MATH::xequal(-1, -1))
		{
			GTLINE2("xequal negative int error!");
			++nRet;
		}
		if(!GAIA::MATH::xequal(-1.234567F, -1.234567))
		{
			GTLINE2("xequal negative float and double error!");
			++nRet;
		}
		if(!GAIA::MATH::xequal(-1.234567F, -1.234567F))
		{
			GTLINE2("xequal negative float and float error!");
			++nRet;
		}
		if(!GAIA::MATH::xequal(-1.23456789F, -1.23456788F))
		{
			GTLINE2("xequal negative float and float error!");
			++nRet;
		}
		if(!GAIA::MATH::xequal(-1, -1, 0.00001F))
		{
			GTLINE2("xequal negative int error!");
			++nRet;
		}
		if(!GAIA::MATH::xequal(-1.234567F, -1.234567, 0.00001F))
		{
			GTLINE2("xequal negative float and double error!");
			++nRet;
		}
		if(!GAIA::MATH::xequal(-1.234567F, -1.234567F, 0.00001F))
		{
			GTLINE2("xequal negative float and float error!");
			++nRet;
		}
		if(!GAIA::MATH::xequal(-1.23456789F, -1.23456788F, 0.00001F))
		{
			GTLINE2("xequal negative float and float error!");
			++nRet;
		}

		return nRet;
	}
};

#endif