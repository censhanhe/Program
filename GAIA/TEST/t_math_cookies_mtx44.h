#ifndef		__T_MATH_COOKIES_MTX44_H__
#define		__T_MATH_COOKIES_MTX44_H__

namespace GAIA_TEST
{
	GINL GAIA::N32 t_math_cookies_mtx44(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;

		typedef GAIA::REAL __DataType;
		typedef GAIA::MATH::VEC3<__DataType> __VecType;
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
			GTLINE2("MTX44 size error!");
			++nRet;
		}
		if(mtx.isidentity())
		{
			GTLINE2("New MTX44 is identity!");
			++nRet;
		}
		mtx.identity();
		if(!mtx.isfinited())
		{
			GTLINE2("MTX44 is finited after identity!");
			++nRet;
		}
		if(!mtx.isidentity())
		{
			GTLINE2("MTX44 is not identity after identity!");
			++nRet;
		}

		mtx = GAIA::MATH::xsqrt(-1.0F);
		if(mtx.isfinited())
		{
			GTLINE2("MTX44 isfinite error!");
			++nRet;
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
			GTLINE2("MTX44 operator = data pointer error!");
			++nRet;
		}
		mtx.transpose();
		if(mtx != DATA_LIST)
		{
			GTLINE2("MTX44 transpose error!");
			++nRet;
		}

		mtx.identity();
		mtx.rotatex(1.0F);
		mtx.rotatey(2.0F);
		mtx.rotatez(3.0F);
		mtx.rotate(__VecType(1.23F), 4.56F);
		if(mtx.isidentity())
		{
			GTLINE2("MTX44 rotate error!");
			++nRet;
		}
		__VecType pos = mtx.position();
		if(pos != 0.0F)
		{
			GTLINE2("MTX44 rotate error!");
			++nRet;
		}

		return nRet;
	}
};

#endif