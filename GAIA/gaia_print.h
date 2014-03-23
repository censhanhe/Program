#ifndef		__GAIA_PRINT_H__
#define		__GAIA_PRINT_H__

namespace GAIA
{
	namespace PRINT
	{
		class Print : public GAIA::Base
		{
		public:
			GINL Print(){}
			GINL ~Print(){}

			GAIA_DEBUG_CODEPURE_MEMFUNC Print& operator << (GAIA::BL t);
			GAIA_DEBUG_CODEPURE_MEMFUNC Print& operator << (GAIA::NM t);
			GAIA_DEBUG_CODEPURE_MEMFUNC Print& operator << (GAIA::UM t);
			GAIA_DEBUG_CODEPURE_MEMFUNC Print& operator << (GAIA::N8 t);
			GAIA_DEBUG_CODEPURE_MEMFUNC Print& operator << (GAIA::N16 t);
			GAIA_DEBUG_CODEPURE_MEMFUNC Print& operator << (GAIA::N32 t);
			GAIA_DEBUG_CODEPURE_MEMFUNC Print& operator << (const GAIA::N64& t);
			GAIA_DEBUG_CODEPURE_MEMFUNC Print& operator << (GAIA::U8 t);
			GAIA_DEBUG_CODEPURE_MEMFUNC Print& operator << (GAIA::U16 t);
			GAIA_DEBUG_CODEPURE_MEMFUNC Print& operator << (GAIA::U32 t);
			GAIA_DEBUG_CODEPURE_MEMFUNC Print& operator << (const GAIA::U64& t);
			GAIA_DEBUG_CODEPURE_MEMFUNC Print& operator << (GAIA::F32 t);
			GAIA_DEBUG_CODEPURE_MEMFUNC Print& operator << (const GAIA::F64& t);
			GAIA_DEBUG_CODEPURE_MEMFUNC Print& operator << (const GAIA::GWCH& t);
			GAIA_DEBUG_CODEPURE_MEMFUNC Print& operator << (const GAIA::GCH* p);
			GAIA_DEBUG_CODEPURE_MEMFUNC Print& operator << (const GAIA::GWCH* p);
			GAIA_DEBUG_CODEPURE_MEMFUNC Print& operator << (const GAIA::X128& t);

			GAIA_DEBUG_CODEPURE_MEMFUNC Print& operator >> (GAIA::BL& t);
			GAIA_DEBUG_CODEPURE_MEMFUNC Print& operator >> (GAIA::NM& t);
			GAIA_DEBUG_CODEPURE_MEMFUNC Print& operator >> (GAIA::UM& t);
			GAIA_DEBUG_CODEPURE_MEMFUNC Print& operator >> (GAIA::N8& t);
			GAIA_DEBUG_CODEPURE_MEMFUNC Print& operator >> (GAIA::N16& t);
			GAIA_DEBUG_CODEPURE_MEMFUNC Print& operator >> (GAIA::N32& t);
			GAIA_DEBUG_CODEPURE_MEMFUNC Print& operator >> (GAIA::N64& t);
			GAIA_DEBUG_CODEPURE_MEMFUNC Print& operator >> (GAIA::U8& t);
			GAIA_DEBUG_CODEPURE_MEMFUNC Print& operator >> (GAIA::U16& t);
			GAIA_DEBUG_CODEPURE_MEMFUNC Print& operator >> (GAIA::U32& t);
			GAIA_DEBUG_CODEPURE_MEMFUNC Print& operator >> (GAIA::U64& t);
			GAIA_DEBUG_CODEPURE_MEMFUNC Print& operator >> (GAIA::F32& t);
			GAIA_DEBUG_CODEPURE_MEMFUNC Print& operator >> (GAIA::F64& t);
			GAIA_DEBUG_CODEPURE_MEMFUNC Print& operator >> (GAIA::GWCH& t);
			GAIA_DEBUG_CODEPURE_MEMFUNC Print& operator >> (GAIA::GCH* p);
			GAIA_DEBUG_CODEPURE_MEMFUNC Print& operator >> (GAIA::GWCH* p);
			GAIA_DEBUG_CODEPURE_MEMFUNC Print& operator >> (GAIA::X128& t);
		};
	};
};

#ifndef GAIA_DEBUG_CODEPURE
#	include "gaia_print_indp.h"
#endif

#endif