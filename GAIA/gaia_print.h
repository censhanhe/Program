#ifndef		__GAIA_PRINT_H__
#define		__GAIA_PRINT_H__

namespace GAIA
{
	namespace PRINT
	{
		class PrintBase : public GAIA::Base
		{
		public:
			virtual GAIA::GVOID enable_write(GAIA::BL bEnable) = 0;
			virtual GAIA::BL enable_write() const = 0;
			virtual GAIA::GVOID enable_read(GAIA::BL bEnable) = 0;
			virtual GAIA::BL enable_read() const = 0;

			virtual GAIA::GVOID clear_screen() = 0;

			virtual PrintBase& operator << (GAIA::BL t) = 0;
			virtual PrintBase& operator << (GAIA::NM t) = 0;
			virtual PrintBase& operator << (GAIA::UM t) = 0;
			virtual PrintBase& operator << (GAIA::N8 t) = 0;
			virtual PrintBase& operator << (GAIA::N16 t) = 0;
			virtual PrintBase& operator << (GAIA::N32 t) = 0;
			virtual PrintBase& operator << (const GAIA::N64& t) = 0;
			virtual PrintBase& operator << (GAIA::U8 t) = 0;
			virtual PrintBase& operator << (GAIA::U16 t) = 0;
			virtual PrintBase& operator << (GAIA::U32 t) = 0;
			virtual PrintBase& operator << (const GAIA::U64& t) = 0;
			virtual PrintBase& operator << (GAIA::F32 t) = 0;
			virtual PrintBase& operator << (const GAIA::F64& t) = 0;
			virtual PrintBase& operator << (const GAIA::GWCH& t) = 0;
			virtual PrintBase& operator << (const GAIA::GCH* p) = 0;
			virtual PrintBase& operator << (const GAIA::GWCH* p) = 0;
			virtual PrintBase& operator << (const GAIA::X128& t) = 0;

			virtual PrintBase& operator >> (GAIA::BL& t) = 0;
			virtual PrintBase& operator >> (GAIA::NM& t) = 0;
			virtual PrintBase& operator >> (GAIA::UM& t) = 0;
			virtual PrintBase& operator >> (GAIA::N8& t) = 0;
			virtual PrintBase& operator >> (GAIA::N16& t) = 0;
			virtual PrintBase& operator >> (GAIA::N32& t) = 0;
			virtual PrintBase& operator >> (GAIA::N64& t) = 0;
			virtual PrintBase& operator >> (GAIA::U8& t) = 0;
			virtual PrintBase& operator >> (GAIA::U16& t) = 0;
			virtual PrintBase& operator >> (GAIA::U32& t) = 0;
			virtual PrintBase& operator >> (GAIA::U64& t) = 0;
			virtual PrintBase& operator >> (GAIA::F32& t) = 0;
			virtual PrintBase& operator >> (GAIA::F64& t) = 0;
			virtual PrintBase& operator >> (GAIA::GWCH& t) = 0;
			virtual PrintBase& operator >> (GAIA::GCH* p) = 0;
			virtual PrintBase& operator >> (GAIA::GWCH* p) = 0;
			virtual PrintBase& operator >> (GAIA::X128& t) = 0;

			virtual PrintBase& operator >> (PrintFormat& pf) = 0;
			virtual PrintBase& operator << (const PrintFormat& pf) = 0;

			virtual GAIA::GVOID flush() = 0;
		};

		class Print : public PrintBase
		{
		public:
			GINL Print(){this->init();}
			GINL ~Print(){}

			virtual GAIA::GVOID enable_write(GAIA::BL bEnable){m_bEnableWrite = bEnable;}
			virtual GAIA::BL enable_write() const{return m_bEnableWrite;}
			virtual GAIA::GVOID enable_read(GAIA::BL bEnable){m_bEnableRead = bEnable;}
			virtual GAIA::BL enable_read() const{return m_bEnableRead;}

			GAIA_DEBUG_CODEPURE_VIRTUALFUNCDECL GAIA::GVOID clear_screen();

			GAIA_DEBUG_CODEPURE_VIRTUALFUNCDECL Print& operator << (GAIA::BL t);
			GAIA_DEBUG_CODEPURE_VIRTUALFUNCDECL Print& operator << (GAIA::NM t);
			GAIA_DEBUG_CODEPURE_VIRTUALFUNCDECL Print& operator << (GAIA::UM t);
			GAIA_DEBUG_CODEPURE_VIRTUALFUNCDECL Print& operator << (GAIA::N8 t);
			GAIA_DEBUG_CODEPURE_VIRTUALFUNCDECL Print& operator << (GAIA::N16 t);
			GAIA_DEBUG_CODEPURE_VIRTUALFUNCDECL Print& operator << (GAIA::N32 t);
			GAIA_DEBUG_CODEPURE_VIRTUALFUNCDECL Print& operator << (const GAIA::N64& t);
			GAIA_DEBUG_CODEPURE_VIRTUALFUNCDECL Print& operator << (GAIA::U8 t);
			GAIA_DEBUG_CODEPURE_VIRTUALFUNCDECL Print& operator << (GAIA::U16 t);
			GAIA_DEBUG_CODEPURE_VIRTUALFUNCDECL Print& operator << (GAIA::U32 t);
			GAIA_DEBUG_CODEPURE_VIRTUALFUNCDECL Print& operator << (const GAIA::U64& t);
			GAIA_DEBUG_CODEPURE_VIRTUALFUNCDECL Print& operator << (GAIA::F32 t);
			GAIA_DEBUG_CODEPURE_VIRTUALFUNCDECL Print& operator << (const GAIA::F64& t);
			GAIA_DEBUG_CODEPURE_VIRTUALFUNCDECL Print& operator << (const GAIA::GWCH& t);
			GAIA_DEBUG_CODEPURE_VIRTUALFUNCDECL Print& operator << (const GAIA::GCH* p);
			GAIA_DEBUG_CODEPURE_VIRTUALFUNCDECL Print& operator << (const GAIA::GWCH* p);
			GAIA_DEBUG_CODEPURE_VIRTUALFUNCDECL Print& operator << (const GAIA::X128& t);

			GAIA_DEBUG_CODEPURE_VIRTUALFUNCDECL Print& operator >> (GAIA::BL& t);
			GAIA_DEBUG_CODEPURE_VIRTUALFUNCDECL Print& operator >> (GAIA::NM& t);
			GAIA_DEBUG_CODEPURE_VIRTUALFUNCDECL Print& operator >> (GAIA::UM& t);
			GAIA_DEBUG_CODEPURE_VIRTUALFUNCDECL Print& operator >> (GAIA::N8& t);
			GAIA_DEBUG_CODEPURE_VIRTUALFUNCDECL Print& operator >> (GAIA::N16& t);
			GAIA_DEBUG_CODEPURE_VIRTUALFUNCDECL Print& operator >> (GAIA::N32& t);
			GAIA_DEBUG_CODEPURE_VIRTUALFUNCDECL Print& operator >> (GAIA::N64& t);
			GAIA_DEBUG_CODEPURE_VIRTUALFUNCDECL Print& operator >> (GAIA::U8& t);
			GAIA_DEBUG_CODEPURE_VIRTUALFUNCDECL Print& operator >> (GAIA::U16& t);
			GAIA_DEBUG_CODEPURE_VIRTUALFUNCDECL Print& operator >> (GAIA::U32& t);
			GAIA_DEBUG_CODEPURE_VIRTUALFUNCDECL Print& operator >> (GAIA::U64& t);
			GAIA_DEBUG_CODEPURE_VIRTUALFUNCDECL Print& operator >> (GAIA::F32& t);
			GAIA_DEBUG_CODEPURE_VIRTUALFUNCDECL Print& operator >> (GAIA::F64& t);
			GAIA_DEBUG_CODEPURE_VIRTUALFUNCDECL Print& operator >> (GAIA::GWCH& t);
			GAIA_DEBUG_CODEPURE_VIRTUALFUNCDECL Print& operator >> (GAIA::GCH* p);
			GAIA_DEBUG_CODEPURE_VIRTUALFUNCDECL Print& operator >> (GAIA::GWCH* p);
			GAIA_DEBUG_CODEPURE_VIRTUALFUNCDECL Print& operator >> (GAIA::X128& t);

			GAIA_DEBUG_CODEPURE_VIRTUALFUNCDECL Print& operator >> (PrintFormat& pf);
			GAIA_DEBUG_CODEPURE_VIRTUALFUNCDECL Print& operator << (const PrintFormat& pf);

			GAIA_DEBUG_CODEPURE_VIRTUALFUNCDECL GAIA::GVOID flush();

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