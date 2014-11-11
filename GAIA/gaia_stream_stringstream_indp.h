#ifndef		__GAIA_STREAM_STRINGSTREAM_INDP_H__
#define		__GAIA_STREAM_STRINGSTREAM_INDP_H__

namespace GAIA
{
	namespace STREAM
	{
		GINL GAIA::GVOID StringStream::enable_write(GAIA::BL bEnable){m_bEnableWrite = bEnable;}
		GINL GAIA::BL StringStream::enable_write() const{return m_bEnableWrite;}
		GINL GAIA::GVOID StringStream::enable_read(GAIA::BL bEnable){m_bEnableRead = bEnable;}
		GINL GAIA::BL StringStream::enable_read() const{return m_bEnableRead;}
		GINL StringStream& StringStream::operator << (GAIA::BL t)
		{
			if(t)
				m_str += _T("1");
			else
				m_str += _T("0");
			return *this;
		}
		GINL StringStream& StringStream::operator << (GAIA::NM t)
		{
			__CharType szTemp[64];
			GAIA::ALGO::value_cast(t, szTemp, 64);
			m_str += szTemp;
			return *this;
		}
		GINL StringStream& StringStream::operator << (GAIA::UM t)
		{
			__CharType szTemp[64];
			GAIA::ALGO::value_cast(t, szTemp, 64);
			m_str += szTemp;
			return *this;
		}
		GINL StringStream& StringStream::operator << (GAIA::N8 t)
		{
			__CharType szTemp[64];
			GAIA::ALGO::value_cast(t, szTemp, 64);
			m_str += szTemp;
			return *this;
		}
		GINL StringStream& StringStream::operator << (GAIA::N16 t)
		{
			__CharType szTemp[64];
			GAIA::ALGO::value_cast(t, szTemp, 64);
			m_str += szTemp;
			return *this;
		}
		GINL StringStream& StringStream::operator << (GAIA::N32 t)
		{
			__CharType szTemp[64];
			GAIA::ALGO::value_cast(t, szTemp, 64);
			m_str += szTemp;
			return *this;
		}
		GINL StringStream& StringStream::operator << (const GAIA::N64& t)
		{
			__CharType szTemp[64];
			GAIA::ALGO::value_cast(t, szTemp, 64);
			m_str += szTemp;
			return *this;
		}
		GINL StringStream& StringStream::operator << (GAIA::U8 t)
		{
			__CharType szTemp[64];
			GAIA::ALGO::value_cast(t, szTemp, 64);
			m_str += szTemp;
			return *this;
		}
		GINL StringStream& StringStream::operator << (GAIA::U16 t)
		{
			__CharType szTemp[64];
			GAIA::ALGO::value_cast(t, szTemp, 64);
			m_str += szTemp;
			return *this;
		}
		GINL StringStream& StringStream::operator << (GAIA::U32 t)
		{
			__CharType szTemp[64];
			GAIA::ALGO::value_cast(t, szTemp, 64);
			m_str += szTemp;
			return *this;
		}
		GINL StringStream& StringStream::operator << (const GAIA::U64& t)
		{
			__CharType szTemp[64];
			GAIA::ALGO::value_cast(t, szTemp, 64);
			m_str += szTemp;
			return *this;
		}
		GINL StringStream& StringStream::operator << (GAIA::F32 t)
		{
			__CharType szTemp[64];
			GAIA::ALGO::value_cast(t, szTemp, 64);
			m_str += szTemp;
			return *this;
		}
		GINL StringStream& StringStream::operator << (const GAIA::F64& t)
		{
			__CharType szTemp[64];
			GAIA::ALGO::value_cast(t, szTemp, 64);
			m_str += szTemp;
			return *this;
		}
		GINL StringStream& StringStream::operator << (const GAIA::WCH& t)
		{
			__CharType szTemp[64];
			GAIA::ALGO::value_cast((GAIA::N64)t, szTemp, 64);
			m_str += szTemp;
			return *this;
		}
		GINL StringStream& StringStream::operator << (const GAIA::CH* p)
		{
			m_str += p;
			return *this;
		}
		GINL StringStream& StringStream::operator << (const GAIA::WCH* p)
		{
			m_str += p;
			return *this;
		}
		GINL StringStream& StringStream::operator << (const GAIA::X128& t)
		{
			__CharType szTemp[64];
			t.tostring(szTemp);
			m_str += szTemp;
			return *this;
		}
		GINL StringStream& StringStream::operator >> (GAIA::BL& t)
		{
			return *this;
		}
		GINL StringStream& StringStream::operator >> (GAIA::NM& t)
		{
			return *this;
		}
		GINL StringStream& StringStream::operator >> (GAIA::UM& t)
		{
			return *this;
		}
		GINL StringStream& StringStream::operator >> (GAIA::N8& t)
		{
			return *this;
		}
		GINL StringStream& StringStream::operator >> (GAIA::N16& t)
		{
			return *this;
		}
		GINL StringStream& StringStream::operator >> (GAIA::N32& t)
		{
			return *this;
		}
		GINL StringStream& StringStream::operator >> (GAIA::N64& t)
		{
			return *this;
		}
		GINL StringStream& StringStream::operator >> (GAIA::U8& t)
		{
			return *this;
		}
		GINL StringStream& StringStream::operator >> (GAIA::U16& t)
		{
			return *this;
		}
		GINL StringStream& StringStream::operator >> (GAIA::U32& t)
		{
			return *this;
		}
		GINL StringStream& StringStream::operator >> (GAIA::U64& t)
		{
			return *this;
		}
		GINL StringStream& StringStream::operator >> (GAIA::F32& t)
		{
			return *this;
		}
		GINL StringStream& StringStream::operator >> (GAIA::F64& t)
		{
			return *this;
		}
		GINL StringStream& StringStream::operator >> (GAIA::WCH& t)
		{
			return *this;
		}
		GINL StringStream& StringStream::operator >> (GAIA::CH* p)
		{
			return *this;
		}
		GINL StringStream& StringStream::operator >> (GAIA::WCH* p)
		{
			return *this;
		}
		GINL StringStream& StringStream::operator >> (GAIA::X128& t)
		{
			return *this;
		}
		GINL StringStream& StringStream::operator >> (StreamFormat& pf)
		{
			return *this;
		}
		GINL StringStream& StringStream::operator << (const StreamFormat& pf)
		{
			return *this;
		}
		GINL GAIA::GVOID StringStream::flush()
		{
		}
	};
};

#endif