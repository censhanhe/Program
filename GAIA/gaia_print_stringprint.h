#ifndef		__GAIA_PRINT_STRINGPRINT_H__
#define		__GAIA_PRINT_STRINGPRINT_H__

namespace GAIA
{
	namespace PRINT
	{
		class StringPrint : public PrintBase
		{
		public:
			typedef GAIA::TCH __CharType;
			typedef GAIA::CTN::TString __StringType;

		public:
			GINL StringPrint(){this->init();}
			GINL ~StringPrint(){}

			virtual GINL GAIA::GVOID enable_write(GAIA::BL bEnable);
			virtual GINL GAIA::BL enable_write() const;
			virtual GINL GAIA::GVOID enable_read(GAIA::BL bEnable);
			virtual GINL GAIA::BL enable_read() const;

			virtual GINL StringPrint& operator << (GAIA::BL t);
			virtual GINL StringPrint& operator << (GAIA::NM t);
			virtual GINL StringPrint& operator << (GAIA::UM t);
			virtual GINL StringPrint& operator << (GAIA::N8 t);
			virtual GINL StringPrint& operator << (GAIA::N16 t);
			virtual GINL StringPrint& operator << (GAIA::N32 t);
			virtual GINL StringPrint& operator << (const GAIA::N64& t);
			virtual GINL StringPrint& operator << (GAIA::U8 t);
			virtual GINL StringPrint& operator << (GAIA::U16 t);
			virtual GINL StringPrint& operator << (GAIA::U32 t);
			virtual GINL StringPrint& operator << (const GAIA::U64& t);
			virtual GINL StringPrint& operator << (GAIA::F32 t);
			virtual GINL StringPrint& operator << (const GAIA::F64& t);
			virtual GINL StringPrint& operator << (const GAIA::WCH& t);
			virtual GINL StringPrint& operator << (const GAIA::CH* p);
			virtual GINL StringPrint& operator << (const GAIA::WCH* p);
			virtual GINL StringPrint& operator << (const GAIA::X128& t);

			virtual GINL StringPrint& operator >> (GAIA::BL& t);
			virtual GINL StringPrint& operator >> (GAIA::NM& t);
			virtual GINL StringPrint& operator >> (GAIA::UM& t);
			virtual GINL StringPrint& operator >> (GAIA::N8& t);
			virtual GINL StringPrint& operator >> (GAIA::N16& t);
			virtual GINL StringPrint& operator >> (GAIA::N32& t);
			virtual GINL StringPrint& operator >> (GAIA::N64& t);
			virtual GINL StringPrint& operator >> (GAIA::U8& t);
			virtual GINL StringPrint& operator >> (GAIA::U16& t);
			virtual GINL StringPrint& operator >> (GAIA::U32& t);
			virtual GINL StringPrint& operator >> (GAIA::U64& t);
			virtual GINL StringPrint& operator >> (GAIA::F32& t);
			virtual GINL StringPrint& operator >> (GAIA::F64& t);
			virtual GINL StringPrint& operator >> (GAIA::WCH& t);
			virtual GINL StringPrint& operator >> (GAIA::CH* p);
			virtual GINL StringPrint& operator >> (GAIA::WCH* p);
			virtual GINL StringPrint& operator >> (GAIA::X128& t);

			virtual GINL StringPrint& operator >> (PrintFormat& pf);
			virtual GINL StringPrint& operator << (const PrintFormat& pf);

			virtual GINL GAIA::GVOID flush();

			GINL GAIA::GVOID SetString(const __CharType* p){m_str = p;}
			GINL const __CharType* GetString() const{return m_str.front_ptr();}

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
			__StringType m_str;
		};
	};
};

#include "gaia_print_stringprint_indp.h"

#endif