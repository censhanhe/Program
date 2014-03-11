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
			GAIA_AST(filekey != GNULL);
			if(opentype & FILE_OPEN_TYPE_CREATEALWAYS)
				m_pFile = (GAIA::GVOID*)fopen(filekey, "wb");
			else if(opentype & FILE_OPEN_TYPE_WRITE)
				m_pFile = (GAIA::GVOID*)fopen(filekey, "rb+");
			else if(opentype == FILE_OPEN_TYPE_READ)
				m_pFile = (GAIA::GVOID*)fopen(filekey, "rb");
			else
				return GAIA::False;
			if(m_pFile == GNULL)
				return GAIA::False;
			m_offset = 0;
			fseek((FILE*)m_pFile, 0, SEEK_END);
			m_size = ftell((FILE*)m_pFile);
			fseek((FILE*)m_pFile, 0, SEEK_SET);
			m_fileopentype = opentype;
			return GAIA::True;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL File::Close()
		{
			if(m_pFile != GNULL)
			{
				fclose((FILE*)m_pFile);
				m_pFile = GNULL;
				m_fileopentype = FILE_OPEN_TYPE_INVALID;
				m_size = m_offset = 0;
				return GAIA::True;
			}
			return GAIA::False;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::N64 File::Read(GAIA::GVOID* pDst, const GAIA::N64& size)
		{
			GAIA_AST(pDst != GNULL);
			GAIA_AST(size > 0);
			if(pDst == GNULL)
				return 0;
			if(size <= 0)
				return 0;
			if(m_pFile == GNULL)
				return 0;
			if(!(m_fileopentype & FILE_OPEN_TYPE_READ))
				return 0;
			if(fread(pDst, size, 1, (FILE*)m_pFile) == 1)
			{
				m_offset += size;
				return size;
			}
			return 0;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::N64 File::Write(const GAIA::GVOID* pSrc, const GAIA::N64& size)
		{
			GAIA_AST(pSrc != GNULL);
			GAIA_AST(size > 0);
			if(pSrc == GNULL)
				return 0;
			if(size <= 0)
				return 0;
			if(m_pFile == GNULL)
				return 0;
			if(!(m_fileopentype & FILE_OPEN_TYPE_WRITE))
				return 0;
			if(fwrite(pSrc, size, 1, (FILE*)m_pFile) == 1)
			{
				m_offset += size;
				if(m_offset > m_size)
					m_size = m_offset;
				return size;
			}
			return 0;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL File::Seek(SEEK_TYPE seektype, const GAIA::N64& offset)
		{
			if(m_pFile == GNULL)
				return GAIA::False;
			if(seektype == SEEK_TYPE_BEGIN)
			{
				GAIA::N64 toffset = GAIA::MATH::clamp(offset, 0, m_size);
				if(fseek((FILE*)m_pFile, toffset, SEEK_SET) == 0)
				{
					m_offset = toffset;
					return GAIA::True;
				}
			}
			else if(seektype == SEEK_TYPE_END)
			{
				GAIA::N64 toffset = GAIA::MATH::clamp(m_size - offset, 0, m_size);
				if(fseek((FILE*)m_pFile, toffset, SEEK_SET) == 0)
				{
					m_offset = toffset;
					return GAIA::True;
				}
			}
			else if(seektype == SEEK_TYPE_FORWARD)
			{
				GAIA::N64 toffset = GAIA::MATH::clamp(m_offset + offset, 0, m_size);
				if(fseek((FILE*)m_pFile, toffset, SEEK_SET) == 0)
				{
					m_offset = toffset;
					return GAIA::True;
				}
			}
			else if(seektype == SEEK_TYPE_BACKWARD)
			{
				GAIA::N64 toffset = GAIA::MATH::clamp(m_offset - offset, 0, m_size);
				if(fseek((FILE*)m_pFile, toffset, SEEK_SET) == 0)
				{
					m_offset = toffset;
					return GAIA::True;
				}
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
