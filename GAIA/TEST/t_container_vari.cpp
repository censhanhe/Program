#include "preheader.h"
#include "t_header.h"

namespace GAIA_TEST
{
	extern GAIA::N32 t_container_vari(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt)
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

		return nRet;
	}
};