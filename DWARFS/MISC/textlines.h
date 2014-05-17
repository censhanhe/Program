#ifndef 	__DWARFS_TEXTLINES_H__
#define 	__DWARFS_TEXTLINES_H__

namespace DWARFS_MISC
{
	class TextLines
	{
	public:
		typedef GAIA::CONTAINER::AString __LineType;
		typedef GAIA::CONTAINER::AString::_datatype __CharType;
	private:
		typedef GAIA::CONTAINER::Vector<__LineType> __LineListType;
	public:
		GINL TextLines(){}
		GINL ~TextLines(){}
		GINL GAIA::BL load(GAIA::FILESYSTEM::FileBase* pFile)
		{
			GAIA_AST(pFile != GNULL);
			if(pFile == GNULL)
				return GAIA::False;
			typedef GAIA::CONTAINER::Buffer __BufferType;
			__BufferType buf;
			buf.resize(1024 * 1024);
			__LineType empty_line;
			GAIA::N64 nReaded;
			while((nReaded = pFile->Read(
				buf.front_ptr() + buf.read_size(), 
				buf.write_size() - buf.read_size())) != 0)
			{
				__CharType* p = (__CharType*)buf.front_ptr();
				__CharType* pLast = p;
				__BufferType::_sizetype cursize = buf.read_size() + nReaded;
				for(__BufferType::_sizetype x = 0; x < cursize; ++x)
				{
					/* Find the new line token's last position. */
					__CharType* pMatched = GNULL;
					if(p[x] == 0)
					{
						if(x != 0 && p[x - 1] != '\n' && p[x - 1] != '\r')
							pMatched = p + x - 1;
					}
					else if(p[x] == '\r')
					{
						if(x + 1 < cursize)
						{
							if(p[x + 1] != '\n')
								pMatched = p;
						}	
					}
					else if(p[x] == '\n')
						pMatched = p;

					/* Push to line list. */
					if(pMatched != GNULL)
					{
						m_lines.push_back(empty_line);
						m_lines.back().resize(pMatched - pLast);
						GAIA::ALGORITHM::xmemcpy(
								m_lines.back().front_ptr(), 
								pLast, pMatched - pLast);
						
						pLast = pMatched + 1;
					}
				}
			}
			return GAIA::True;
		}
		GINL GAIA::BL save(GAIA::FILESYSTEM::FileBase* pFile)
		{
			GAIA_AST(pFile != GNULL);
			if(pFile == NULL)
				return GAIA::False;
			for(__LineListType::_sizetype x = 0; x < m_lines.size(); ++x)
				pFile->Write(m_lines[x].front_ptr(), m_lines[x].size());
			pFile->Write("", sizeof(GAIA::GCH));
			return GAIA::True;
		}
		GINL GAIA::GVOID clear(){m_lines.clear();}
		GINL GAIA::SIZE size() const{return m_lines.size();}
		GINL const __CharType* get_line(const GAIA::SIZE& index) const{return m_lines[index];}
		GINL GAIA::BL set_line(const GAIA::SIZE& index, const __CharType* p)
		{
			GAIA_AST(index < m_lines.size());
			if(index >= m_lines.size())
				return GAIA::False;
			GAIA_AST(p != GNULL);
			if(p == GNULL)
				return GAIA::False;
			if(!this->checkline(p))
				return GAIA::False;
			m_lines[index] = p;
			return GAIA::True;
		}
		GINL GAIA::BL insert_lines(const GAIA::SIZE& index, const __CharType** p, const GAIA::SIZE& size)
		{
			GAIA_AST(index < m_lines.size());
			if(index >= m_lines.size())
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
				if(!this->checkline(p[x]))
					return GAIA::False;
			}
			for(GAIA::SIZE x = 0; x < size; ++x)
			{
				if(!m_lines.insert(index, (__LineType)p[x]))
					return GAIA::False;
			}
			return GAIA::True;
		}
	private:
		GINL GAIA::BL checkline(const __CharType* p) const
		{
			GAIA_AST(!GAIA::ALGORITHM::stremp(p));
			if(GAIA::ALGORITHM::stremp(p))
				return GAIA::False;
			GAIA::SIZE newline_token_count = 0;
			while(*p != 0)
			{
				if(*p == '\r' && *(p + 1) == '\n')
				{
					++newline_token_count;
					++p;
				}
				else if(*p == '\n')
					++newline_token_count;
				++p;
			}
			if(newline_token_count != 1)
				return GAIA::False;
			return GAIA::True;
		}	
	private:
		__LineListType m_lines;
	};
};

#endif
