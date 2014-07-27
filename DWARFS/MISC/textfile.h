#ifndef		__DWARFS_TEXT_FILE_H__
#define		__DWARFS_TEXT_FILE_H__

namespace DWARFS_MISC
{
	class TextFile : public GAIA::Entity
	{
	public:
		typedef GAIA::CONTAINER::TString __StringType;
		typedef __StringType::_datatype __CharType;
	public:
		GINL TextFile(){this->init();}
		GINL TextFile(const TextFile& src){this->init(); this->operator = (src);}
		GINL ~TextFile(){}
		GINL GAIA::BL load(GAIA::FILESYSTEM::FileBase* pFile)
		{
			GPCHR_NULL_RET(pFile, GAIA::False);
			this->clear();
			if(m_charset_type == GAIA::CHARSET_TYPE_INVALID && pFile->Tell() >= sizeof(GAIA::UTF8_FILEHEAD))
			{
			}
			if(m_charset_type == GAIA::CHARSET_TYPE_INVALID && pFile->Tell() >= sizeof(GAIA::UTF16LE_FILEHEAD))
			{
			}
			if(m_charset_type == GAIA::CHARSET_TYPE_INVALID && pFile->Tell() >= sizeof(GAIA::UTF16BE_FILEHEAD))
			{
			}
			m_charset_type = GAIA::CHARSET_TYPE_ANSI;
			switch(m_charset_type)
			{
			case GAIA::CHARSET_TYPE_ANSI:
				{
				}
				break;
			case GAIA::CHARSET_TYPE_OEM:
				{
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
				}
				break;
			case GAIA::CHARSET_TYPE_OEM:
				{
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