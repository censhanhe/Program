#include "preheader.h"
#include "t_header.h"

namespace GAIA_TEST
{
	extern GAIA::N32 t_container_vari(GAIA::FSYS::File& file, GAIA::STREAM::StreamBase& prt)
	{
		GAIA::N32 nRet = 0;

		typedef GAIA::CTN::Vari __VariType;

		__VariType v1, v2;
		v1.reset();
		if(v1.check())
		{
			GTLINE2("Vari reset or check error!");
			++nRet;
		}
		v2 = v1;
		if(v2.check())
		{
			GTLINE2("Vari reset or check error!");
			++nRet;
		}

		/* NM. */
		v1 = GSCAST(GAIA::NM)(1);
		if(v1.type() != GAIA::TYPEID_NM || !v1.check())
		{
			GTLINE2("Vari operator = error!");
			++nRet;
		}
		v2 = v1;
		if(v2.type() != GAIA::TYPEID_NM || !v2.check())
		{
			GTLINE2("Vari operator = error!");
			++nRet;
		}
		if(v1.type() != GAIA::TYPEID_NM || v2.type() != GAIA::TYPEID_NM)
		{
			GTLINE2("Vari type error!");
			++nRet;
		}
		if((GAIA::NM)v1 != 1 || (GAIA::NM)v2 != 1)
		{
			GTLINE2("Vari convert to value error!");
			++nRet;
		}

		/* UM. */
		v1 = GSCAST(GAIA::UM)(1);
		if(v1.type() != GAIA::TYPEID_UM || !v1.check())
		{
			GTLINE2("Vari operator = error!");
			++nRet;
		}
		v2 = v1;
		if(v2.type() != GAIA::TYPEID_UM || !v2.check())
		{
			GTLINE2("Vari operator = error!");
			++nRet;
		}
		if(v1.type() != GAIA::TYPEID_UM || v2.type() != GAIA::TYPEID_UM)
		{
			GTLINE2("Vari type error!");
			++nRet;
		}
		if((GAIA::UM)v1 != 1 || (GAIA::UM)v2 != 1)
		{
			GTLINE2("Vari convert to value error!");
			++nRet;
		}

		/* BL. */
		v1 = GAIA::True;
		if(v1.type() != GAIA::TYPEID_BL || !v1.check())
		{
			GTLINE2("Vari operator = error!");
			++nRet;
		}
		v2 = v1;
		if(v2.type() != GAIA::TYPEID_BL || !v2.check())
		{
			GTLINE2("Vari operator = error!");
			++nRet;
		}
		if(v1.type() != GAIA::TYPEID_BL || v2.type() != GAIA::TYPEID_BL)
		{
			GTLINE2("Vari type error!");
			++nRet;
		}
		if((GAIA::BL)v1 != GAIA::True || (GAIA::BL)v2 != GAIA::True)
		{
			GTLINE2("Vari convert to value error!");
			++nRet;
		}

		/* N8. */
		v1 = GSCAST(GAIA::N8)(1);
		if(v1.type() != GAIA::TYPEID_N8 || !v1.check())
		{
			GTLINE2("Vari operator = error!");
			++nRet;
		}
		v2 = v1;
		if(v2.type() != GAIA::TYPEID_N8 || !v2.check())
		{
			GTLINE2("Vari operator = error!");
			++nRet;
		}
		if(v1.type() != GAIA::TYPEID_N8 || v2.type() != GAIA::TYPEID_N8)
		{
			GTLINE2("Vari type error!");
			++nRet;
		}
		if((GAIA::N8)v1 != 1 || (GAIA::N8)v2 != 1)
		{
			GTLINE2("Vari convert to value error!");
			++nRet;
		}

		/* N16. */
		v1 = GSCAST(GAIA::N16)(1);
		if(v1.type() != GAIA::TYPEID_N16 || !v1.check())
		{
			GTLINE2("Vari operator = error!");
			++nRet;
		}
		v2 = v1;
		if(v2.type() != GAIA::TYPEID_N16 || !v2.check())
		{
			GTLINE2("Vari operator = error!");
			++nRet;
		}
		if(v1.type() != GAIA::TYPEID_N16 || v2.type() != GAIA::TYPEID_N16)
		{
			GTLINE2("Vari type error!");
			++nRet;
		}
		if((GAIA::N16)v1 != 1 || (GAIA::N16)v2 != 1)
		{
			GTLINE2("Vari convert to value error!");
			++nRet;
		}

		/* N32. */
		v1 = GSCAST(GAIA::N32)(1);
		if(v1.type() != GAIA::TYPEID_N32 || !v1.check())
		{
			GTLINE2("Vari operator = error!");
			++nRet;
		}
		v2 = v1;
		if(v2.type() != GAIA::TYPEID_N32 || !v2.check())
		{
			GTLINE2("Vari operator = error!");
			++nRet;
		}
		if(v1.type() != GAIA::TYPEID_N32 || v2.type() != GAIA::TYPEID_N32)
		{
			GTLINE2("Vari type error!");
			++nRet;
		}
		if((GAIA::N32)v1 != 1 || (GAIA::N32)v2 != 1)
		{
			GTLINE2("Vari convert to value error!");
			++nRet;
		}

		/* N64. */
		v1 = GSCAST(GAIA::N64)(1);
		if(v1.type() != GAIA::TYPEID_N64 || !v1.check())
		{
			GTLINE2("Vari operator = error!");
			++nRet;
		}
		v2 = v1;
		if(v2.type() != GAIA::TYPEID_N64 || !v2.check())
		{
			GTLINE2("Vari operator = error!");
			++nRet;
		}
		if(v1.type() != GAIA::TYPEID_N64 || v2.type() != GAIA::TYPEID_N64)
		{
			GTLINE2("Vari type error!");
			++nRet;
		}
		if((GAIA::N64)v1 != 1 || (GAIA::N64)v2 != 1)
		{
			GTLINE2("Vari convert to value error!");
			++nRet;
		}

		/* U8. */
		v1 = GSCAST(GAIA::U8)(1);
		if(v1.type() != GAIA::TYPEID_U8 || !v1.check())
		{
			GTLINE2("Vari operator = error!");
			++nRet;
		}
		v2 = v1;
		if(v2.type() != GAIA::TYPEID_U8 || !v2.check())
		{
			GTLINE2("Vari operator = error!");
			++nRet;
		}
		if(v1.type() != GAIA::TYPEID_U8 || v2.type() != GAIA::TYPEID_U8)
		{
			GTLINE2("Vari type error!");
			++nRet;
		}
		if((GAIA::U8)v1 != 1 || (GAIA::U8)v2 != 1)
		{
			GTLINE2("Vari convert to value error!");
			++nRet;
		}

		/* U16. */
		v1 = GSCAST(GAIA::U16)(1);
		if(v1.type() != GAIA::TYPEID_U16 || !v1.check())
		{
			GTLINE2("Vari operator = error!");
			++nRet;
		}
		v2 = v1;
		if(v2.type() != GAIA::TYPEID_U16 || !v2.check())
		{
			GTLINE2("Vari operator = error!");
			++nRet;
		}
		if(v1.type() != GAIA::TYPEID_U16 || v2.type() != GAIA::TYPEID_U16)
		{
			GTLINE2("Vari type error!");
			++nRet;
		}
		if((GAIA::U16)v1 != 1 || (GAIA::U16)v2 != 1)
		{
			GTLINE2("Vari convert to value error!");
			++nRet;
		}

		/* U32. */
		v1 = GSCAST(GAIA::U32)(1);
		if(v1.type() != GAIA::TYPEID_U32 || !v1.check())
		{
			GTLINE2("Vari operator = error!");
			++nRet;
		}
		v2 = v1;
		if(v2.type() != GAIA::TYPEID_U32 || !v2.check())
		{
			GTLINE2("Vari operator = error!");
			++nRet;
		}
		if(v1.type() != GAIA::TYPEID_U32 || v2.type() != GAIA::TYPEID_U32)
		{
			GTLINE2("Vari type error!");
			++nRet;
		}
		if((GAIA::U32)v1 != 1 || (GAIA::U32)v2 != 1)
		{
			GTLINE2("Vari convert to value error!");
			++nRet;
		}

		/* U64. */
		v1 = GSCAST(GAIA::U64)(1);
		if(v1.type() != GAIA::TYPEID_U64 || !v1.check())
		{
			GTLINE2("Vari operator = error!");
			++nRet;
		}
		v2 = v1;
		if(v2.type() != GAIA::TYPEID_U64 || !v2.check())
		{
			GTLINE2("Vari operator = error!");
			++nRet;
		}
		if(v1.type() != GAIA::TYPEID_U64 || v2.type() != GAIA::TYPEID_U64)
		{
			GTLINE2("Vari type error!");
			++nRet;
		}
		if((GAIA::U64)v1 != 1 || (GAIA::U64)v2 != 1)
		{
			GTLINE2("Vari convert to value error!");
			++nRet;
		}

		/* F32. */
		v1 = GSCAST(GAIA::F32)(1);
		if(v1.type() != GAIA::TYPEID_F32 || !v1.check())
		{
			GTLINE2("Vari operator = error!");
			++nRet;
		}
		v2 = v1;
		if(v2.type() != GAIA::TYPEID_F32 || !v2.check())
		{
			GTLINE2("Vari operator = error!");
			++nRet;
		}
		if(v1.type() != GAIA::TYPEID_F32 || v2.type() != GAIA::TYPEID_F32)
		{
			GTLINE2("Vari type error!");
			++nRet;
		}
		if((GAIA::F32)v1 != 1 || (GAIA::F32)v2 != 1)
		{
			GTLINE2("Vari convert to value error!");
			++nRet;
		}

		/* F64. */
		v1 = GSCAST(GAIA::F64)(1);
		if(v1.type() != GAIA::TYPEID_F64 || !v1.check())
		{
			GTLINE2("Vari operator = error!");
			++nRet;
		}
		v2 = v1;
		if(v2.type() != GAIA::TYPEID_F64 || !v2.check())
		{
			GTLINE2("Vari operator = error!");
			++nRet;
		}
		if(v1.type() != GAIA::TYPEID_F64 || v2.type() != GAIA::TYPEID_F64)
		{
			GTLINE2("Vari type error!");
			++nRet;
		}
		if((GAIA::F64)v1 != 1 || (GAIA::F64)v2 != 1)
		{
			GTLINE2("Vari convert to value error!");
			++nRet;
		}

		/* Pointer. */
		GAIA::GVOID* p = GNIL;
		v1 = p;
		if(v1.type() != GAIA::TYPEID_POINTER || !v1.check())
		{
			GTLINE2("Vari operator = error!");
			++nRet;
		}
		v2 = v1;
		if(v2.type() != GAIA::TYPEID_POINTER || !v2.check())
		{
			GTLINE2("Vari operator = error!");
			++nRet;
		}
		if(v1.type() != GAIA::TYPEID_POINTER || v2.type() != GAIA::TYPEID_POINTER)
		{
			GTLINE2("Vari type error!");
			++nRet;
		}
		if((GAIA::GVOID*)v1 != GNIL || (GAIA::GVOID*)v2 != GNIL)
		{
			GTLINE2("Vari convert to value error!");
			++nRet;
		}

		/* ConstPointer. */
		const GAIA::GVOID* cp = GNIL;
		v1 = cp;
		if(v1.type() != GAIA::TYPEID_CONSTPOINTER || !v1.check())
		{
			GTLINE2("Vari operator = error!");
			++nRet;
		}
		v2 = v1;
		if(v2.type() != GAIA::TYPEID_CONSTPOINTER || !v2.check())
		{
			GTLINE2("Vari operator = error!");
			++nRet;
		}
		if(v1.type() != GAIA::TYPEID_CONSTPOINTER || v2.type() != GAIA::TYPEID_CONSTPOINTER)
		{
			GTLINE2("Vari type error!");
			++nRet;
		}
		if((const GAIA::GVOID*)v1 != GNIL || (const GAIA::GVOID*)v2 != GNIL)
		{
			GTLINE2("Vari convert to value error!");
			++nRet;
		}

		return nRet;
	}
};