#ifndef		__DWARFS_TEXT_FILE_H__
#define		__DWARFS_TEXT_FILE_H__

namespace DWARFS_MISC
{
	class TextFile : public GAIA::Entity
	{
	public:
		typedef GAIA::CONTAINER::TString __StringType;
		typedef __StringType::_datatype __CharType;
		typedef GAIA::CONTAINER::Buffer __BufferType;
	public:
		GINL TextFile(){this->init();}
		GINL TextFile(const TextFile& src){this->init(); this->operator = (src);}
		GINL ~TextFile(){}
		GINL GAIA::BL load(GAIA::FILESYSTEM::FileBase* pFile)
		{
			GPCHR_NULL_RET(pFile, GAIA::False);
			this->clear();
			__BufferType buf;
			buf.resize(pFile->Size());
			if(buf.write_size() == 0)
			{
				m_charset_type = GAIA::CHARSET_TYPE_ANSI;
				return GAIA::True;
			}
			if(pFile->Read(buf.front_ptr(), buf.write_size()) != buf.write_size())
				return GAIA::False;
			if(m_charset_type == GAIA::CHARSET_TYPE_INVALID && buf.write_size() >= sizeof(GAIA::UTF8_FILEHEAD))
			{
				if(GAIA::ALGORITHM::xmemcmp(buf.front_ptr(), GAIA::UTF8_FILEHEAD, sizeof(GAIA::UTF8_FILEHEAD)) == 0)
					m_charset_type = GAIA::CHARSET_TYPE_UTF8;
			}
			if(m_charset_type == GAIA::CHARSET_TYPE_INVALID && buf.write_size() >= sizeof(GAIA::UTF16LE_FILEHEAD))
			{
				if(GAIA::ALGORITHM::xmemcmp(buf.front_ptr(), GAIA::UTF16LE_FILEHEAD, sizeof(GAIA::UTF16LE_FILEHEAD)) == 0)
					m_charset_type = GAIA::CHARSET_TYPE_UTF16LE;
			}
			if(m_charset_type == GAIA::CHARSET_TYPE_INVALID && buf.write_size() >= sizeof(GAIA::UTF16BE_FILEHEAD))
			{
				if(GAIA::ALGORITHM::xmemcmp(buf.front_ptr(), GAIA::UTF16BE_FILEHEAD, sizeof(GAIA::UTF16BE_FILEHEAD)) == 0)
					m_charset_type = GAIA::CHARSET_TYPE_UTF16BE;
			}
			if(m_charset_type == GAIA::CHARSET_TYPE_INVALID)
			{
				if(GAIA::ALGORITHM::isallansi(buf.front_ptr()))
					m_charset_type = GAIA::CHARSET_TYPE_ANSI;
				else
					m_charset_type = GAIA::CHARSET_TYPE_SYS;
			}
			switch(m_charset_type)
			{
			case GAIA::CHARSET_TYPE_ANSI:
				{
					m_str.resize(buf.write_size());
					for(GAIA::SIZE x = 0; x < buf.write_size(); ++x)
						m_str[x] = buf[x];
				}
				break;
			case GAIA::CHARSET_TYPE_SYS:
				{
					GAIA::SIZE newsize = GAIA::LOCALE::m2w((GAIA::CH*)buf.front_ptr(), GNULL, 0);
					m_str.resize(newsize);
					GAIA_AST(newsize > 0);
					GAIA::LOCALE::m2w((GAIA::CH*)buf.front_ptr(), m_str, newsize);
				}
				break;
			case GAIA::CHARSET_TYPE_UTF8:
				{
				}
				break;
			case GAIA::CHARSET_TYPE_UTF16LE:
				{
				}
				break;
			case GAIA::CHARSET_TYPE_UTF16BE:
				{
				}
				break;
			default:
				return GAIA::False;
			}
			return GAIA::True;
		}
		GINL GAIA::BL save(GAIA::FILESYSTEM::FileBase* pFile)
		{
			GPCHR_NULL_RET(pFile, GAIA::False);
			GAIA_AST(m_charset_type != GAIA::CHARSET_TYPE_INVALID);
			if(m_charset_type == GAIA::CHARSET_TYPE_INVALID)
				return GAIA::False;
			switch(m_charset_type)
			{
			case GAIA::CHARSET_TYPE_ANSI:
				{
					if(m_str.size() > 0)
					{
						__BufferType buf;
						buf.resize(m_str.size());
						for(GAIA::SIZE x = 0; x < m_str.size(); ++x)
							buf[x] = (__BufferType::_datatype)m_str[x];
						pFile->Write(buf.front_ptr(), buf.write_size());
					}
				}
				break;
			case GAIA::CHARSET_TYPE_SYS:
				{
					if(m_str.size() > 0)
					{
						GAIA::SIZE newsize = GAIA::LOCALE::w2m(m_str, GNULL, 0);
						GAIA_AST(newsize > 0);
						__BufferType buf;
						buf.resize(newsize);
						GAIA::LOCALE::w2m(m_str, (GAIA::CH*)buf.front_ptr(), newsize);
						pFile->Write(buf.front_ptr(), buf.write_size());
					}
				}
				break;
			case GAIA::CHARSET_TYPE_UTF8:
				{
					pFile->Write(GAIA::UTF8_FILEHEAD, sizeof(GAIA::UTF8_FILEHEAD));
				}
				break;
			case GAIA::CHARSET_TYPE_UTF16LE:
				{
					pFile->Write(GAIA::UTF16LE_FILEHEAD, sizeof(GAIA::UTF16LE_FILEHEAD));
				}
				break;
			case GAIA::CHARSET_TYPE_UTF16BE:
				{
					pFile->Write(GAIA::UTF16BE_FILEHEAD, sizeof(GAIA::UTF16BE_FILEHEAD));
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
			GAIA_AST(charset_type < GAIA::CHARSET_TYPE_COUNT);
			if(charset_type >= GAIA::CHARSET_TYPE_COUNT)
				return GAIA::False;
			m_charset_type = charset_type;
			return GAIA::True;
		}
		GINL GAIA::CHARSET_TYPE charset_type() const{return m_charset_type;}
		GINL GAIA::GVOID clear(){m_charset_type = GAIA::CHARSET_TYPE_INVALID; m_str.clear();}
		GINL __StringType& get_string(){return m_str;}
		GINL const __StringType& get_string() const{return m_str;}
		GINL TextFile& operator = (const TextFile& src){m_charset_type = src.m_charset_type; m_str = src.m_str; return *this;}
	private:
		GINL GAIA::GVOID init(){m_charset_type = GAIA::CHARSET_TYPE_INVALID;}
	private:
		GAIA::CHARSET_TYPE m_charset_type;
		__StringType m_str;
	};
};

#endif