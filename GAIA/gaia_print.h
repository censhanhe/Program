#ifndef		__GAIA_PRINT_H__
#define		__GAIA_PRINT_H__

namespace GAIA
{
	namespace PRINT
	{
		class PrintBase : public GAIA::Entity
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
			virtual PrintBase& operator << (const GAIA::WCH& t) = 0;
			virtual PrintBase& operator << (const GAIA::CH* p) = 0;
			virtual PrintBase& operator << (const GAIA::WCH* p) = 0;
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
			virtual PrintBase& operator >> (GAIA::WCH& t) = 0;
			virtual PrintBase& operator >> (GAIA::CH* p) = 0;
			virtual PrintBase& operator >> (GAIA::WCH* p) = 0;
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

			virtual GINL GAIA::GVOID clear_screen();

			virtual GINL Print& operator << (GAIA::BL t);
			virtual GINL Print& operator << (GAIA::NM t);
			virtual GINL Print& operator << (GAIA::UM t);
			virtual GINL Print& operator << (GAIA::N8 t);
			virtual GINL Print& operator << (GAIA::N16 t);
			virtual GINL Print& operator << (GAIA::N32 t);
			virtual GINL Print& operator << (const GAIA::N64& t);
			virtual GINL Print& operator << (GAIA::U8 t);
			virtual GINL Print& operator << (GAIA::U16 t);
			virtual GINL Print& operator << (GAIA::U32 t);
			virtual GINL Print& operator << (const GAIA::U64& t);
			virtual GINL Print& operator << (GAIA::F32 t);
			virtual GINL Print& operator << (const GAIA::F64& t);
			virtual GINL Print& operator << (const GAIA::WCH& t);
			virtual GINL Print& operator << (const GAIA::CH* p);
			virtual GINL Print& operator << (const GAIA::WCH* p);
			virtual GINL Print& operator << (const GAIA::X128& t);

			virtual GINL Print& operator >> (GAIA::BL& t);
			virtual GINL Print& operator >> (GAIA::NM& t);
			virtual GINL Print& operator >> (GAIA::UM& t);
			virtual GINL Print& operator >> (GAIA::N8& t);
			virtual GINL Print& operator >> (GAIA::N16& t);
			virtual GINL Print& operator >> (GAIA::N32& t);
			virtual GINL Print& operator >> (GAIA::N64& t);
			virtual GINL Print& operator >> (GAIA::U8& t);
			virtual GINL Print& operator >> (GAIA::U16& t);
			virtual GINL Print& operator >> (GAIA::U32& t);
			virtual GINL Print& operator >> (GAIA::U64& t);
			virtual GINL Print& operator >> (GAIA::F32& t);
			virtual GINL Print& operator >> (GAIA::F64& t);
			virtual GINL Print& operator >> (GAIA::WCH& t);
			virtual GINL Print& operator >> (GAIA::CH* p);
			virtual GINL Print& operator >> (GAIA::WCH* p);
			virtual GINL Print& operator >> (GAIA::X128& t);

			virtual GINL Print& operator >> (PrintFormat& pf);
			virtual GINL Print& operator << (const PrintFormat& pf);

			virtual GINL GAIA::GVOID flush();

		private:
			GINL GAIA::GVOID init()
			{
				m_pf.reset();
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

#include "gaia_print_indp.h"

#endif
