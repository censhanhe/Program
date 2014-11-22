#ifndef 	__DWARFS_TEXTLINE_H__
#define 	__DWARFS_TEXTLINE_H__

#include "textfile.h"

namespace DWARFS_MISC
{
	class TextLine : public GAIA::Entity
	{
	public:
		typedef GAIA::CTN::TString __LineType;
		typedef __LineType::_datatype __CharType;
		typedef GAIA::CTN::BasicChars<__CharType, GAIA::N32, 2> __LineBreakType;
	private:
		typedef GAIA::CTN::Vector<__LineType> __LineListType;
	public:
		GINL TextLine(){this->init();}
		GINL TextLine(const TextLine& src){this->init(); this->operator = (src);}
		GINL ~TextLine(){}
		GINL GAIA::BL lineflag(const __CharType* psz)
		{
			GPCHR_NULLSTR_RET(psz, GAIA::False);
			if(GAIA::ALGO::strcmp(psz, _T(GAIA_FILELINEBREAK_R)) != 0 &&
				GAIA::ALGO::strcmp(psz, _T(GAIA_FILELINEBREAK_N)) != 0 &&
				GAIA::ALGO::strcmp(psz, _T(GAIA_FILELINEBREAK_RN)) != 0)
				return GAIA::False;
			m_linebreak = psz;
			return GAIA::True;
		}
		GINL const __CharType* lineflag() const{return m_linebreak;}
		GINL GAIA::BL load(GAIA::FSYS::FileBase& file)
		{
			if(file.Size() == 0)
				return GAIA::True;
			DWARFS_MISC::TextFile textfile;
			if(!textfile.load(file))
				return GAIA::False;
			m_charset_type = textfile.charset_type();
			if(m_charset_type == GAIA::CHARSET_TYPE_INVALID)
				return GAIA::False;
			__CharType* p = textfile.get_string().front_ptr();
			GAIA::SIZE charcount = textfile.get_string().size();
			__LineType empty_line;
			GAIA::BL bExistMatch = GAIA::False;
			__CharType* pLast = p;
			for(GAIA::SIZE x = 0; x < charcount; ++x)
			{
				/* Find the new line token's last position. */
				__CharType* pMatched = GNIL;
				if(p[x] == _T('\0'))
				{
					if(x != 0 && p[x - 1] != _T('\n') && p[x - 1] != _T('\r'))
						pMatched = p + x - 1;
				}
				else if(p[x] == _T('\r'))
				{
					if(x + 1 < charcount)
					{
						if(p[x + 1] != _T('\n'))
							pMatched = p + x;
					}
					else
						pMatched = p + x;
				}
				else if(p[x] == _T('\n'))
					pMatched = p + x;
				else if(x == charcount - 1)
					pMatched = p + x;

				/* Push to line list. */
				if(pMatched != GNIL)
				{
					m_lines.push_back(empty_line);
					m_lines.back().resize(pMatched - pLast + 1);
					GAIA::ALGO::xmemcpy(
						m_lines.back().front_ptr(),
						pLast, (pMatched - pLast + 1) * sizeof(__CharType));
					pLast = pMatched + 1;
					bExistMatch = GAIA::True;
				}
			}
			if(!m_lines.empty())
			{
				GAIA_AST(!m_lines.back().empty());
				__LineType& l = m_lines.back();
				__LineType::_datatype t = *l.back_it();
				if(t != _T('\r') && t != _T('\n'))
					l += m_linebreak;
			}
			return GAIA::True;
		}
		GINL GAIA::BL save(GAIA::FSYS::FileBase& file)
		{
			DWARFS_MISC::TextFile textfile;
			textfile.charset_type(m_charset_type);
			TextFile::__StringType& str = textfile.get_string();
			GAIA::SIZE len = 0;
			for(__LineListType::_sizetype x = 0; x < m_lines.size(); ++x)
			{
				GAIA_AST(m_lines[x].size() > 0);
				len += m_lines[x].size();
			}
			str.reserve(len);
			for(__LineListType::_sizetype x = 0; x < m_lines.size(); ++x)
				str += m_lines[x];
			return textfile.save(file);
		}
		GINL GAIA::GVOID clear(){m_charset_type = GAIA::CHARSET_TYPE_INVALID; m_lines.clear();}
		GINL GAIA::SIZE size() const{return m_lines.size();}
		GINL GAIA::BL set_line(const GAIA::SIZE& index, const __CharType* p)
		{
			GAIA_AST(index < m_lines.size());
			if(index >= m_lines.size())
				return GAIA::False;
			GAIA_AST(p != GNIL);
			if(p == GNIL)
				return GAIA::False;
			GAIA::SIZE line_flag_count = 0;
			GAIA::BL bAppendLineFlag = GAIA::False;
			if(!this->checkline(p, line_flag_count))
			{
				if(line_flag_count == 0)
					bAppendLineFlag = GAIA::True;
				else
					return GAIA::False;
			}
			m_lines[index] = p;
			if(bAppendLineFlag)
				m_lines[index] += m_linebreak;
			return GAIA::True;
		}
		GINL const __CharType* get_line(const GAIA::SIZE& index) const{return m_lines[index];}
		GINL GAIA::BL insert_lines(const GAIA::SIZE& index, const __CharType** p, const GAIA::SIZE& size)
		{
			GAIA_AST(index <= m_lines.size());
			if(index > m_lines.size())
				return GAIA::False;
			GAIA_AST(p != GNIL);
			if(p == GNIL)
				return GAIA::False;
			GAIA_AST(size > 0);
			if(size <= 0)
				return GAIA::False;
			for(GAIA::SIZE x = 0; x < size; ++x)
			{
				if(p[x] == GNIL)
					return GAIA::False;
				GAIA::SIZE line_flag_count = 0;
				if(!this->checkline(p[x], line_flag_count))
				{
					if(line_flag_count != 0)
						return GAIA::False;
				}
			}
			for(GAIA::SIZE x = 0; x < size; ++x)
			{
				if(!m_lines.insert(GSCAST(__LineType)(p[x]), index + x))
				{
					GAIA_AST(GAIA::ALWAYSFALSE);
					return GAIA::False;
				}
				GAIA::SIZE line_flag_count = 0;
				if(!this->checkline(p[x], line_flag_count))
				{
					if(line_flag_count == 0)
						m_lines[index + x] += m_linebreak;
				}
			}
			return GAIA::True;
		}
		GINL GAIA::BL erase_lines(const GAIA::SIZE& index, const GAIA::SIZE& size)
		{
			GAIA_AST(index < m_lines.size());
			if(index >= m_lines.size())
				return GAIA::False;
			GAIA_AST(index + size < m_lines.size());
			if(index + size >= m_lines.size())
				return GAIA::False;
			GAIA_AST(size > 0);
			if(size <= 0)
				return GAIA::False;
			for(GAIA::SIZE x = 0; x < size; ++x)
			{
				if(!m_lines.erase(index))
				{
					GAIA_AST(GAIA::ALWAYSFALSE);
					return GAIA::False;
				}
			}
			return GAIA::True;
		}
		GINL GAIA::GVOID enable_checkline(GAIA::BL bEnable){m_bEnableCheckLine = bEnable;}
		GINL GAIA::BL isenable_checkline() const{return m_bEnableCheckLine;}
		GINL TextLine& operator = (const TextLine& src)
		{
			m_lines = src.m_lines;
			m_linebreak = src.m_linebreak;
			return *this;
		}
		GAIA_CLASS_OPERATOR_COMPARE2(m_lines, m_lines, m_linebreak, m_linebreak, TextLine);
	private:
		GINL GAIA::GVOID init(){m_linebreak = _T(GAIA_FILELINEBREAK); m_charset_type = GAIA::CHARSET_TYPE_INVALID; m_bEnableCheckLine = GAIA::True;}
		GINL GAIA::BL checkline(const __CharType* p, GAIA::SIZE& line_flag_count) const
		{
			if(!this->isenable_checkline())
			{
				line_flag_count = 1;
				return GAIA::True;
			}
			line_flag_count = 0;
			GAIA_AST(!GAIA::ALGO::stremp(p));
			if(GAIA::ALGO::stremp(p))
				return GAIA::False;
			while(*p != _T('\0'))
			{
				if(*p == _T('\r') && *(p + 1) == _T('\n'))
				{
					if(*(p + 2) != _T('\0'))
					{
						line_flag_count = GINVALID;
						return GAIA::False;
					}
					++line_flag_count;
					++p;
				}
				else if(*p == _T('\r') || *p == _T('\n'))
				{
					if(*(p + 1) != _T('\0'))
					{
						line_flag_count = GINVALID;
						return GAIA::False;
					}
					++line_flag_count;
				}
				++p;
			}
			if(line_flag_count != 1)
				return GAIA::False;
			return GAIA::True;
		}
	private:
		__LineListType m_lines;
		__LineBreakType m_linebreak;
		GAIA::CHARSET_TYPE m_charset_type;
		GAIA::U8 m_bEnableCheckLine : 1;
	};
};

#endif
