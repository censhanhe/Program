#ifndef		__T_MATH_COOKIES_MTX44_H__
#define		__T_MATH_COOKIES_MTX44_H__

namespace GAIA_TEST
{
	GINL GAIA::N32 t_math_cookies_mtx44(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;

		typedef GAIA::REAL __DataType;
		typedef GAIA::MATH::MTX44<__DataType> __MtxType;

		static const __DataType DATA_LIST[] = 
		{
			0.0F, 1.0F, 2.0F, 3.0F,
			4.0F, 5.0F, 6.0F, 7.0F, 
			8.0F, 9.0F, 10.0F, 11.0F,
			12.0F, 13.0F, 14.0F, 15.0F,
		};

		__MtxType mtx, mtx1;
		if(mtx.size() != 16)
		{
		}
		if(!mtx.isfinited())
		{
		}
		if(mtx.isidentity())
		{
		}
		if(mtx.isidentity())
		{
		}
		if(mtx.isfinited())
		{
		}
		if(!mtx.isidentity())
		{
		}
		mtx = 10.0F;
		for(GAIA::SIZE x = 0; x < mtx.size(); ++x)
		{
			if(mtx[x] != 10.0F)
			{
				GTLINE2("MTX44 operator = const value error!");
				++nRet;
				break;
			}
		}
		mtx1 = mtx;
		for(GAIA::SIZE x = 0; x < mtx1.size(); ++x)
		{
			if(mtx1[x] != 10.0F)
			{
				GTLINE2("MTX44 operator = const value error!");
				++nRet;
				break;
			}
		}
		mtx = DATA_LIST;
		for(GAIA::SIZE x = 0; x < sizeofarray(DATA_LIST); ++x)
		{
			if(mtx[x] != DATA_LIST[x])
			{
				GTLINE2("MTX44 operator = const datapointer error!");
				++nRet;
				break;
			}
		}
		mtx1 = mtx;
		for(GAIA::SIZE x = 0; x < sizeofarray(DATA_LIST); ++x)
		{
			if(mtx1[x] != DATA_LIST[x])
			{
				GTLINE2("MTX44 operator = const datapointer error!");
				++nRet;
				break;
			}
		}
		mtx = DATA_LIST;
		mtx.transpose();
		if(mtx == DATA_LIST)
		{
		}
		mtx.transpose();
		if(mtx != DATA_LIST)
		{
		}

		return nRet;
	}
};

#endif