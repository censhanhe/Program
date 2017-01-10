#ifndef		__DWARFS_TEXT_FILE_H__
#define		__DWARFS_TEXT_FILE_H__

namespace DWARFS_MISC
{
	class TextFile : public GAIA::Entity
	{
	public:
		typedef GAIA::CTN::TString __StringType;
		typedef __StringType::_datatype __CharType;
		typedef GAIA::CTN::Buffer __BufferType;
	public:
		GINL TextFile(){this->init();}
		GINL TextFile(const TextFile& src){this->init(); this->operator = (src);}
		GINL ~TextFile(){}
		GINL GAIA::BL load(GAIA::FSYS::FileBase& file)
		{
			this->clear();
			__BufferType buf;
			buf.resize(file.Size());
			if(buf.write_size() == 0)
			{
				m_charset_type = GAIA::CHARSET_TYPE_ASCII;
				return GAIA::True;
			}
			if(file.Read(buf.front_ptr(), buf.write_size()) != buf.write_size())
				return GAIA::False;
			if(m_charset_type == GAIA::CHARSET_TYPE_INVALID && buf.write_size() >= sizeof(GAIA::UTF8_FILEHEAD))
			{
				if(GAIA::ALGO::xmemcmp(buf.front_ptr(), GAIA::UTF8_FILEHEAD, sizeof(GAIA::UTF8_FILEHEAD)) == 0)
					m_charset_type = GAIA::CHARSET_TYPE_UTF8;
			}
			if(m_charset_type == GAIA::CHARSET_TYPE_INVALID && buf.write_size() >= sizeof(GAIA::UTF16LE_FILEHEAD))
			{
				if(GAIA::ALGO::xmemcmp(buf.front_ptr(), GAIA::UTF16LE_FILEHEAD, sizeof(GAIA::UTF16LE_FILEHEAD)) == 0)
					m_charset_type = GAIA::CHARSET_TYPE_UTF16LE;
			}
			if(m_charset_type == GAIA::CHARSET_TYPE_INVALID && buf.write_size() >= sizeof(GAIA::UTF16BE_FILEHEAD))
			{
				if(GAIA::ALGO::xmemcmp(buf.front_ptr(), GAIA::UTF16BE_FILEHEAD, sizeof(GAIA::UTF16BE_FILEHEAD)) == 0)
					m_charset_type = GAIA::CHARSET_TYPE_UTF16BE;
			}
			if(m_charset_type == GAIA::CHARSET_TYPE_INVALID)
			{
				GAIA::BL bIsAllAnsi = GAIA::True;
				for(GAIA::SIZE x = 0; x < buf.write_size(); ++x)
				{
					if(!GAIA::ALGO::isansi(buf[x]))
					{
						bIsAllAnsi = GAIA::False;
						break;
					}
				}
				if(bIsAllAnsi)
					m_charset_type = GAIA::CHARSET_TYPE_ASCII;
				else
					m_charset_type = GAIA::CHARSET_TYPE_SYS;
			}
		#if GAIA_CHARSET == GAIA_CHARSET_ANSI
			if(m_charset_type != GAIA::CHARSET_TYPE_ASCII &&
				m_charset_type != GAIA::CHARSET_TYPE_SYS)
			{
				m_charset_type = GAIA::CHARSET_TYPE_INVALID;
				return GAIA::False;
			}
		#endif
			switch(m_charset_type)
			{
			case GAIA::CHARSET_TYPE_ASCII:
				{
					m_str.resize(buf.write_size());
					for(GAIA::SIZE x = 0; x < buf.write_size(); ++x)
						m_str[x] = buf[x];
				}
				break;
			case GAIA::CHARSET_TYPE_SYS:
				{
				#if GAIA_CHARSET == GAIA_CHARSET_ANSI
					m_str.resize(buf.write_size());
					for(GAIA::SIZE x = 0; x < buf.write_size(); ++x)
						m_str[x] = buf[x];
				#elif GAIA_CHARSET == GAIA_CHARSET_UNICODE
					GAIA::CTN::AString strOrigin;
					strOrigin.resize(buf.write_size());
					GAIA::ALGO::strcpy(strOrigin.front_ptr(), buf.front_ptr(), buf.write_size());
					GAIA::SIZE newsize = GAIA::LOCALE::m2w(strOrigin.front_ptr(), GNIL, 0, GAIA::CHARSET_TYPE_SYS);
					if(newsize > 1)
					{
						m_str.resize(newsize - 1);
						GAIA::LOCALE::m2w(strOrigin.front_ptr(), m_str, newsize - 1, GAIA::CHARSET_TYPE_SYS);
					}
				#endif
				}
				break;
			case GAIA::CHARSET_TYPE_UTF8:
				{
				#if GAIA_CHARSET == GAIA_CHARSET_ANSI
					return GAIA::False;
				#elif GAIA_CHARSET == GAIA_CHARSET_UNICODE
					GAIA::CTN::AString strOrigin;
					strOrigin.resize(buf.write_size() - sizeof(GAIA::UTF8_FILEHEAD));
					GAIA::ALGO::strcpy(strOrigin.front_ptr(), buf.front_ptr() + sizeof(GAIA::UTF8_FILEHEAD), buf.write_size() - sizeof(GAIA::UTF8_FILEHEAD));
					GAIA::SIZE newsize = GAIA::LOCALE::m2w(strOrigin.front_ptr(), GNIL, 0, GAIA::CHARSET_TYPE_UTF8);
					if(newsize > 1)
					{
						m_str.resize(newsize - 1);
						GAIA::LOCALE::m2w(strOrigin.front_ptr(), m_str.front_ptr(), newsize - 1, GAIA::CHARSET_TYPE_UTF8);
					}
				#endif
				}
				break;
			case GAIA::CHARSET_TYPE_UTF16LE:
				{
				#if GAIA_CHARSET == GAIA_CHARSET_ANSI
					return GAIA::False;
				#elif GAIA_CHARSET == GAIA_CHARSET_UNICODE
					GAIA_AST((buf.write_size() - sizeof(GAIA::UTF16LE_FILEHEAD)) % 2 == 0);
					GAIA::SIZE newsize = (buf.write_size() - sizeof(GAIA::UTF16LE_FILEHEAD)) / sizeof(__StringType::_datatype);
					if(newsize != 0)
					{
						m_str.resize(newsize);
						for(GAIA::SIZE x = 0; x < m_str.size(); ++x)
						{
							GAIA::SIZE bufindex = x * 2 + sizeof(GAIA::UTF16LE_FILEHEAD);
							m_str[x] = (buf[bufindex + 0] << 0) | (buf[bufindex + 1] << 8);
						}
					}
				#endif
				}
				break;
			case GAIA::CHARSET_TYPE_UTF16BE:
				{
				#if GAIA_CHARSET == GAIA_CHARSET_ANSI
					return GAIA::False;
				#elif GAIA_CHARSET == GAIA_CHARSET_UNICODE
					GAIA_AST((buf.write_size() - sizeof(GAIA::UTF16BE_FILEHEAD)) % 2 == 0);
					GAIA::SIZE newsize = (buf.write_size() - sizeof(GAIA::UTF16BE_FILEHEAD)) / sizeof(__StringType::_datatype);
					if(newsize != 0)
					{
						m_str.resize(newsize);
						for(GAIA::SIZE x = 0; x < m_str.size(); ++x)
						{
							GAIA::SIZE bufindex = x * 2 + sizeof(GAIA::UTF16BE_FILEHEAD);
							m_str[x] = (buf[bufindex + 0] << 8) | (buf[bufindex + 1] << 0);
						}
					}
				#endif
				}
				break;
			default:
				return GAIA::False;
			}
			return GAIA::True;
		}
		GINL GAIA::BL save(GAIA::FSYS::FileBase& file)
		{
			GAIA_AST(m_charset_type != GAIA::CHARSET_TYPE_INVALID);
			if(m_charset_type == GAIA::CHARSET_TYPE_INVALID)
				return GAIA::False;
		#if GAIA_CHARSET == GAIA_CHARSET_ANSI
			if(m_charset_type != GAIA::CHARSET_TYPE_ASCII &&
				m_charset_type != GAIA::CHARSET_TYPE_SYS)
				return GAIA::False;
		#endif
			switch(m_charset_type)
			{
			case GAIA::CHARSET_TYPE_ASCII:
				{
					if(m_str.size() > 0)
					{
						__BufferType buf;
						buf.resize(m_str.size());
						for(GAIA::SIZE x = 0; x < m_str.size(); ++x)
							buf[x] = (__BufferType::_datatype)m_str[x];
						file.Write(buf.front_ptr(), buf.write_size());
					}
				}
				break;
			case GAIA::CHARSET_TYPE_SYS:
				{
					if(m_str.size() > 0)
					{
					#if GAIA_CHARSET == GAIA_CHARSET_ANSI
						file.Write(m_str.front_ptr(), m_str.size() * sizeof(__StringType::_datatype));
					#elif GAIA_CHARSET == GAIA_CHARSET_UNICODE
						GAIA::SIZE newsize = GAIA::LOCALE::w2m(m_str, GNIL, 0, GAIA::CHARSET_TYPE_SYS);
						GAIA_AST(newsize > 0);
						if(newsize > 1)
						{
							__BufferType buf;
							buf.resize(newsize);
							GAIA::LOCALE::w2m(m_str, (GAIA::CH*)buf.front_ptr(), newsize, GAIA::CHARSET_TYPE_SYS);
							file.Write(buf.front_ptr(), buf.write_size() - 1);
						}
					#endif
					}
				}
				break;
			case GAIA::CHARSET_TYPE_UTF8:
				{
				#if GAIA_CHARSET == GAIA_CHARSET_ANSI
					return GAIA::False;
				#elif GAIA_CHARSET == GAIA_CHARSET_UNICODE
					file.Write(GAIA::UTF8_FILEHEAD, sizeof(GAIA::UTF8_FILEHEAD));
					if(m_str.size() != 0)
					{
						GAIA::SIZE newsize = GAIA::LOCALE::w2m(m_str, GNIL, 0, GAIA::CHARSET_TYPE_UTF8);
						GAIA_AST(newsize > 0);
						if(newsize > 1)
						{
							__BufferType buf;
							buf.resize(newsize);
							GAIA::LOCALE::w2m(m_str, (GAIA::CH*)buf.front_ptr(), newsize, GAIA::CHARSET_TYPE_UTF8);
							file.Write(buf.front_ptr(), buf.write_size() - 1);
						}
					}
				#endif
				}
				break;
			case GAIA::CHARSET_TYPE_UTF16LE:
				{
				#if GAIA_CHARSET == GAIA_CHARSET_ANSI
					return GAIA::False;
				#elif GAIA_CHARSET == GAIA_CHARSET_UNICODE
					file.Write(GAIA::UTF16LE_FILEHEAD, sizeof(GAIA::UTF16LE_FILEHEAD));
					if(m_str.size() != 0)
					{
						__BufferType buf;
						buf.resize(m_str.size() * sizeof(GAIA::U16));
						for(GAIA::SIZE x = 0; x < m_str.size(); ++x)
						{
							buf[x * 2 + 0] = GSCAST(GAIA::U8)(m_str[x] >> 0) & 0x00FF;
							buf[x * 2 + 1] = GSCAST(GAIA::U8)(m_str[x] >> 8) & 0x00FF;
						}
						file.Write(buf.front_ptr(), buf.write_size());
					}
				#endif
				}
				break;
			case GAIA::CHARSET_TYPE_UTF16BE:
				{
				#if GAIA_CHARSET == GAIA_CHARSET_ANSI
					return GAIA::False;
				#elif GAIA_CHARSET == GAIA_CHARSET_UNICODE
					file.Write(GAIA::UTF16BE_FILEHEAD, sizeof(GAIA::UTF16BE_FILEHEAD));
					if(m_str.size() != 0)
					{
						__BufferType buf;
						buf.resize(m_str.size() * sizeof(GAIA::U16));
						for(GAIA::SIZE x = 0; x < m_str.size(); ++x)
						{
							buf[x * 2 + 0] = GSCAST(GAIA::U8)(m_str[x] >> 8) & 0x00FF;
							buf[x * 2 + 1] = GSCAST(GAIA::U8)(m_str[x] >> 0) & 0x00FF;
						}
						file.Write(buf.front_ptr(), buf.write_size());
					}
				#endif
				}
				break;
			default:
				return GAIA::False;
			}
			return GAIA::True;
		}
		GINL GAIA::BL charset_type(GAIA::CHARSET_TYPE charset_type)
		{
			GAIA_AST(charset_type != GAIA::CHARSET_TYPE_INVALID);
			if(charset_type == GAIA::CHARSET_TYPE_INVALID)
				return GAIA::False;
			GAIA_AST(charset_type < GAIA::CHARSET_TYPE_MAXENUMCOUNT);
			if(charset_type >= GAIA::CHARSET_TYPE_MAXENUMCOUNT)
				return GAIA::False;
		#if GAIA_CHARSET == GAIA_CHARSET_ANSI
			if(charset_type != GAIA::CHARSET_TYPE_ASCII &&
				charset_type != GAIA::CHARSET_TYPE_SYS)
				return GAIA::False;
		#endif
			m_charset_type = charset_type;
			return GAIA::True;
		}
		GINL GAIA::CHARSET_TYPE charset_type() const{return m_charset_type;}
		GINL GAIA::GVOID clear(){m_charset_type = GAIA::CHARSET_TYPE_INVALID; m_str.clear();}
		GINL __StringType& get_string(){return m_str;}
		GINL const __StringType& get_string() const{return m_str;}
		GINL GAIA::GVOID set_string(const __StringType& str){m_str = str;}
		GINL TextFile& operator = (const TextFile& src){m_charset_type = src.m_charset_type; m_str = src.m_str; return *this;}
	private:
		GINL GAIA::GVOID init(){m_charset_type = GAIA::CHARSET_TYPE_INVALID;}
	private:
		GAIA::CHARSET_TYPE m_charset_type;
		__StringType m_str;
	};
};

#endif
