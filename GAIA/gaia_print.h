#ifndef		__GAIA_PRINT_H__
#define		__GAIA_PRINT_H__

namespace GAIA
{
	namespace PRINT
	{
		class Print : public GAIA::Base
		{
		public:
			GINL Print(){this->init();}
			GINL ~Print(){}

			GINL GAIA::GVOID enable_write(GAIA::BL bEnable){m_bEnableWrite = bEnable;}
			GINL GAIA::BL enable_write() const{return m_bEnableWrite;}
			GINL GAIA::GVOID enable_read(GAIA::BL bEnable){m_bEnableRead = bEnable;}
			GINL GAIA::BL enable_read() const{return m_bEnableRead;}

			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::GVOID clear_screen();

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

			GAIA_DEBUG_CODEPURE_MEMFUNC Print& operator >> (PrintFormat& pf);
			GAIA_DEBUG_CODEPURE_MEMFUNC Print& operator << (const PrintFormat& pf);

			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::GVOID flush();

		private:
			GINL GAIA::GVOID init()
			{
				m_bEnableWrite = GAIA::True;
				m_bEnableRead = GAIA::True;
			}

		private:
			PrintFormat m_pf;
			GAIA::U8 m_bEnableWrite : 1;
			GAIA::U8 m_bEnableRead : 1;
		};
	};
};

#ifndef GAIA_DEBUG_CODEPURE
#	include "gaia_print_indp.h"
#endif

#endif