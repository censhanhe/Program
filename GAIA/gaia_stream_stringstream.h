#ifndef		__GAIA_STREAM_STRINGSTREAM_H__
#define		__GAIA_STREAM_STRINGSTREAM_H__

namespace GAIA
{
	namespace STREAM
	{
		class StringStream : public StreamBase
		{
		public:
			typedef GAIA::TCH __CharType;
			typedef GAIA::CTN::TString __StringType;

		public:
			GINL StringStream(){this->init();}
			GINL ~StringStream(){}

			virtual GINL GAIA::GVOID enable_write(GAIA::BL bEnable);
			virtual GINL GAIA::BL enable_write() const;
			virtual GINL GAIA::GVOID enable_read(GAIA::BL bEnable);
			virtual GINL GAIA::BL enable_read() const;

			virtual GINL StringStream& operator << (GAIA::BL t);
			virtual GINL StringStream& operator << (GAIA::NM t);
			virtual GINL StringStream& operator << (GAIA::UM t);
			virtual GINL StringStream& operator << (GAIA::N8 t);
			virtual GINL StringStream& operator << (GAIA::N16 t);
			virtual GINL StringStream& operator << (GAIA::N32 t);
			virtual GINL StringStream& operator << (const GAIA::N64& t);
			virtual GINL StringStream& operator << (GAIA::U8 t);
			virtual GINL StringStream& operator << (GAIA::U16 t);
			virtual GINL StringStream& operator << (GAIA::U32 t);
			virtual GINL StringStream& operator << (const GAIA::U64& t);
			virtual GINL StringStream& operator << (GAIA::F32 t);
			virtual GINL StringStream& operator << (const GAIA::F64& t);
			virtual GINL StringStream& operator << (const GAIA::WCH& t);
			virtual GINL StringStream& operator << (const GAIA::CH* p);
			virtual GINL StringStream& operator << (const GAIA::WCH* p);
			virtual GINL StringStream& operator << (const GAIA::X128& t);

			virtual GINL StringStream& operator >> (GAIA::BL& t);
			virtual GINL StringStream& operator >> (GAIA::NM& t);
			virtual GINL StringStream& operator >> (GAIA::UM& t);
			virtual GINL StringStream& operator >> (GAIA::N8& t);
			virtual GINL StringStream& operator >> (GAIA::N16& t);
			virtual GINL StringStream& operator >> (GAIA::N32& t);
			virtual GINL StringStream& operator >> (GAIA::N64& t);
			virtual GINL StringStream& operator >> (GAIA::U8& t);
			virtual GINL StringStream& operator >> (GAIA::U16& t);
			virtual GINL StringStream& operator >> (GAIA::U32& t);
			virtual GINL StringStream& operator >> (GAIA::U64& t);
			virtual GINL StringStream& operator >> (GAIA::F32& t);
			virtual GINL StringStream& operator >> (GAIA::F64& t);
			virtual GINL StringStream& operator >> (GAIA::WCH& t);
			virtual GINL StringStream& operator >> (GAIA::CH* p);
			virtual GINL StringStream& operator >> (GAIA::WCH* p);
			virtual GINL StringStream& operator >> (GAIA::X128& t);

			virtual GINL StringStream& operator >> (StreamFormat& pf);
			virtual GINL StringStream& operator << (const StreamFormat& pf);

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
			StreamFormat m_pf;
			GAIA::U8 m_bEnableWrite : 1;
			GAIA::U8 m_bEnableRead : 1;
			__StringType m_str;
		};
	};
};

#include "gaia_stream_stringstream_indp.h"

#endif