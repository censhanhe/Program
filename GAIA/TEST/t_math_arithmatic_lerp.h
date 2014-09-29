#ifndef		__T_MATH_ARITHMATIC_LERP_H__
#define		__T_MATH_ARITHMATIC_LERP_H__

namespace GAIA_TEST
{
	GINL GAIA::N32 t_math_arithmatic_lerp(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;

		GAIA::F32 f32 = GAIA::MATH::lerp(0.0F, 1, 1.0);
		if(f32 != 1.0F)
		{
			GTLINE2("lerp error!");
			++nRet;
		}
		GAIA::F64 f64 = GAIA::MATH::lerp_cosfactor(1.0);
		if(f64 != 1.0)
		{
			GTLINE2("lerp_cosfactor error!");
			++nRet;
		}

		return nRet;
	}
};

#endif