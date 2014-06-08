#ifndef		__GAIA_FILE_INDP_H__
#define		__GAIA_FILE_INDP_H__

#include <stdio.h>

namespace GAIA
{
	namespace FILESYSTEM
	{
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL File::Open(const GAIA::GCH* filekey, const GAIA::UM& opentype)
		{
			if(this->IsOpen())
				this->Close();
			GAIA_AST(!!filekey);
			if(opentype & OPEN_TYPE_CREATEALWAYS)
				m_pFile = (GAIA::GVOID*)fopen(filekey, "wb+"); // Create for read and write.
			else if(opentype & OPEN_TYPE_WRITE)
				m_pFile = (GAIA::GVOID*)fopen(filekey, "rb+"); // Open for read and write.
			else if(opentype == OPEN_TYPE_READ)
				m_pFile = (GAIA::GVOID*)fopen(filekey, "rb"); // Open for read.
			else
				return GAIA::False;
			if(m_pFile == GNULL)
				return GAIA::False;
			m_offset = 0;
			if(fseek((FILE*)m_pFile, 0, SEEK_END) != 0)
			{
				this->Close();
				return GAIA::False;
			}
			m_size = ftell((FILE*)m_pFile);
			GAIA_AST(m_size != -1);
			if(m_size == -1)
			{
				this->Close();
				return GAIA::False;
			}
			if(fseek((FILE*)m_pFile, 0, SEEK_SET) != 0)
			{
				this->Close();
				return GAIA::False;
			}
			m_fileopentype = opentype;
			return GAIA::True;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL File::Close()
		{
			if(m_pFile != GNULL)
			{
				fclose((FILE*)m_pFile);
				m_pFile = GNULL;
				m_fileopentype = OPEN_TYPE_INVALID;
				m_size = m_offset = 0;
				return GAIA::True;
			}
			return GAIA::False;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL File::Resize(const GAIA::N64& size)
		{
			if(m_pFile != GNULL)
			{
				if(size <= m_size)
					return GAIA::False;
				GAIA::N64 cur = ftell((FILE*)m_pFile);
				GAIA_AST(cur != -1);
				if(cur == -1)
					return GAIA::False;
				if(m_fileopentype & OPEN_TYPE_CREATEALWAYS ||
					m_fileopentype & OPEN_TYPE_WRITE)
				{
					if(fseek((FILE*)m_pFile, size - 1, SEEK_SET) != 0)
						return GAIA::False;
					GAIA::U8 uEnd = 0;
					if(!this->Write(&uEnd, sizeof(uEnd)))
						return GAIA::False;
					if(!this->Flush())
						return GAIA::False;
					if(fseek((FILE*)m_pFile, cur, SEEK_SET) != 0)
						return GAIA::False;
					m_size = size;
					return GAIA::True;
				}
			}
			return GAIA::False;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::N64 File::Read(GAIA::GVOID* pDst, const GAIA::N64& size)
		{
			GAIA_AST(!!pDst);
			GAIA_AST(size > 0);
			if(pDst == GNULL)
				return 0;
			if(size <= 0)
				return 0;
			if(m_pFile == GNULL)
				return 0;
			if(!(m_fileopentype & OPEN_TYPE_READ))
				return 0;
			GAIA::N64 nReaded;
			if((nReaded = fread(pDst, 1, size, (FILE*)m_pFile)) > 0)
			{
				m_offset += nReaded;
				return nReaded;
			}
			return 0;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::N64 File::Write(const GAIA::GVOID* pSrc, const GAIA::N64& size)
		{
			GAIA_AST(!!pSrc);
			GAIA_AST(size > 0);
			if(pSrc == GNULL)
				return 0;
			if(size <= 0)
				return 0;
			if(m_pFile == GNULL)
				return 0;
			if(!(m_fileopentype & OPEN_TYPE_WRITE))
				return 0;
			GAIA::N64 nWriten;
			if((nWriten = fwrite(pSrc, 1, size, (FILE*)m_pFile)) > 0)
			{
				m_offset += nWriten;
				if(m_offset > m_size)
					m_size = m_offset;
				return nWriten;
			}
			return 0;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL File::Seek(SEEK_TYPE seektype, const GAIA::N64& offset)
		{
			if(m_pFile == GNULL)
				return GAIA::False;
			GAIA::N64 toffset = m_offset;
			if(seektype == SEEK_TYPE_BEGIN)
				toffset = GAIA::MATH::xclamp(offset, 0, m_size);
			else if(seektype == SEEK_TYPE_END)
				toffset = GAIA::MATH::xclamp(m_size - offset, 0, m_size);
			else if(seektype == SEEK_TYPE_FORWARD)
				toffset = GAIA::MATH::xclamp(m_offset + offset, 0, m_size);
			else if(seektype == SEEK_TYPE_BACKWARD)
				toffset = GAIA::MATH::xclamp(m_offset - offset, 0, m_size);
			if(toffset == m_offset)
				return GAIA::True;
			if(fseek((FILE*)m_pFile, toffset, SEEK_SET) == 0)
			{
				m_offset = toffset;
				return GAIA::True;
			}
			return GAIA::False;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL File::Flush()
		{
			if(m_pFile == GNULL)
				return GAIA::False;
			if(fflush((FILE*)m_pFile) == 0)
				return GAIA::True;
			return GAIA::False;
		}
	};
};

#endif
