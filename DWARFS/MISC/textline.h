#ifndef 	__DWARFS_TEXTLINE_H__
#define 	__DWARFS_TEXTLINE_H__

namespace DWARFS_MISC
{
	class TextLine : public GAIA::Entity
	{
	public:
		typedef GAIA::CONTAINER::AString __LineType;
		typedef GAIA::CONTAINER::AString::_datatype __CharType;
		typedef GAIA::CONTAINER::BasicChars<__CharType, GAIA::N32, 3> __FlagType;
	private:
		typedef GAIA::CONTAINER::Vector<__LineType> __LineListType;
	public:
		GINL TextLine(){this->init();}
		GINL ~TextLine(){}
		GINL GAIA::BL lineflag(const GAIA::GCH* psz)
		{
			if(GAIA::ALGORITHM::strcmp(psz, "\r") != 0 &&
				GAIA::ALGORITHM::strcmp(psz, "\n") != 0 &&
				GAIA::ALGORITHM::strcmp(psz, "\r\n") != 0)
				return GAIA::False;
			m_lineflag = psz;
			return GAIA::True;
		}
		GINL const GAIA::GCH* lineflag() const{return m_lineflag;}
		GINL GAIA::BL load(GAIA::FILESYSTEM::FileBase* pFile)
		{
			GAIA_AST(pFile != GNULL);
			if(pFile == GNULL)
				return GAIA::False;
			if(pFile->Size() == 0)
				return GAIA::True;
			typedef GAIA::CONTAINER::Buffer __BufferType;
			__BufferType buf;
			buf.resize(pFile->Size());
			__LineType empty_line;
			GAIA::N64 nReaded = 0;
			while((nReaded = pFile->Read(buf.front_ptr() + buf.read_size(), buf.write_size() - buf.read_size())) != 0)
			{
				buf.seek_read(nReaded, GAIA::SEEK_TYPE_FORWARD);
				if(buf.read_size() == buf.write_size())
					break;
			}
			GAIA::BL bExistMatch = GAIA::False;
			__CharType* p = (__CharType*)buf.front_ptr();
			__CharType* pLast = p;
			for(__BufferType::_sizetype x = 0; x < buf.read_size(); ++x)
			{
				/* Find the new line token's last position. */
				__CharType* pMatched = GNULL;
				if(p[x] == '\0')
				{
					if(x != 0 && p[x - 1] != '\n' && p[x - 1] != '\r')
						pMatched = p + x - 1;
				}
				else if(p[x] == '\r')
				{
					if(x + 1 < buf.read_size())
					{
						if(p[x + 1] != '\n')
							pMatched = p + x;
					}
					else
						pMatched = p + x;
				}
				else if(p[x] == '\n')
					pMatched = p + x;
				else if(x == buf.read_size() - 1)
					pMatched = p + x;

				/* Push to line list. */
				if(pMatched != GNULL)
				{
					m_lines.push_back(empty_line);
					m_lines.back().resize(pMatched - pLast + 1);
					GAIA::ALGORITHM::xmemcpy(
						m_lines.back().front_ptr(),
						pLast, pMatched - pLast + 1);
					pLast = pMatched + 1;
					bExistMatch = GAIA::True;
				}
			}
			if(!m_lines.empty())
			{
				GAIA_AST(!m_lines.back().empty());
				__LineType& l = m_lines.back();
				__LineType::_datatype t = *l.back_it();
				if(t != '\r' && t != '\n')
					l += m_lineflag.front_ptr();
			}
			return GAIA::True;
		}
		GINL GAIA::BL save(GAIA::FILESYSTEM::FileBase* pFile)
		{
			GAIA_AST(pFile != GNULL);
			if(pFile == NULL)
				return GAIA::False;
			for(__LineListType::_sizetype x = 0; x < m_lines.size(); ++x)
			{
				GAIA_AST(m_lines[x].size() > 0);
				pFile->Write(m_lines[x].front_ptr(), m_lines[x].size());
			}
			return GAIA::True;
		}
		GINL GAIA::GVOID clear(){m_lines.clear();}
		GINL GAIA::SIZE size() const{return m_lines.size();}
		GINL GAIA::BL set_line(const GAIA::SIZE& index, const __CharType* p)
		{
			GAIA_AST(index < m_lines.size());
			if(index >= m_lines.size())
				return GAIA::False;
			GAIA_AST(p != GNULL);
			if(p == GNULL)
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
				m_lines[index] += m_lineflag.front_ptr();
			return GAIA::True;
		}
		GINL const __CharType* get_line(const GAIA::SIZE& index) const{return m_lines[index];}
		GINL GAIA::BL insert_lines(const GAIA::SIZE& index, const __CharType** p, const GAIA::SIZE& size)
		{
			GAIA_AST(index <= m_lines.size());
			if(index > m_lines.size())
				return GAIA::False;
			GAIA_AST(p != GNULL);
			if(p == GNULL)
				return GAIA::False;
			GAIA_AST(size > 0);
			if(size <= 0)
				return GAIA::False;
			for(GAIA::SIZE x = 0; x < size; ++x)
			{
				if(p[x] == GNULL)
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
				if(!m_lines.insert((__LineType)p[x], index + x))
				{
					GAIA_AST(GAIA::ALWAYSFALSE);
					return GAIA::False;
				}
				GAIA::SIZE line_flag_count = 0;
				if(!this->checkline(p[x], line_flag_count))
				{
					if(line_flag_count == 0)
						m_lines[index + x] += m_lineflag.front_ptr();
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
		GINL TextLine& operator = (const TextLine& src)
		{
			m_lines = src.m_lines;
			m_lineflag = src.m_lineflag;
			return *this;
		}
		GAIA_CLASS_OPERATOR_COMPARE2(m_lines, m_lines, m_lineflag, m_lineflag, TextLine);
	private:
		GINL GAIA::GVOID init(){m_lineflag = "\r";}
		GINL GAIA::BL checkline(const __CharType* p, GAIA::SIZE& line_flag_count) const
		{
			line_flag_count = 0;
			GAIA_AST(!GAIA::ALGORITHM::stremp(p));
			if(GAIA::ALGORITHM::stremp(p))
				return GAIA::False;
			while(*p != '\0')
			{
				if(*p == '\r' && *(p + 1) == '\n')
				{
					if(*(p + 2) != '\0')
					{
						line_flag_count = GINVALID;
						return GAIA::False;
					}
					++line_flag_count;
					++p;
				}
				else if(*p == '\r' || *p == '\n')
				{
					if(*(p + 1) != '\0')
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
		__FlagType m_lineflag;
	};
};

#endif
