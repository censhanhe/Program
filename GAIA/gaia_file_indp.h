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
			GAIA_ASSERT(filekey != GNULL);
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
			GAIA_ASSERT(pDst != GNULL);
			GAIA_ASSERT(size > 0);
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
			GAIA_ASSERT(pDst != GNULL);
			GAIA_ASSERT(size > 0);
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
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL File::Seek(FILE_SEEK_TYPE seektype, const GAIA::N64& offset)
		{
			GAIA_ASSERT(pDst != GNULL);
			GAIA_ASSERT(size > 0);
			if(m_pFile == GNULL)
				return GAIA::False;
			if(seektype == FILE_SEEK_TYPE_BEGIN)
			{
				if(fseek((FILE*)m_pFile, GAIA::ALGORITHM::clamp(offset, 0, m_size), SEEK_SET) == 0)
					return GAIA::True;
			}
			else if(seektype == FILE_SEEK_TYPE_END)
			{
				if(fseek((FILE*)m_pFile, GAIA::ALGORITHM::clamp(m_size - offset, 0, m_size), SEEK_SET) == 0)
					return GAIA::True;
			}
			else if(seektype == FILE_SEEK_TYPE_FORWARD)
			{
				if(fseek((FILE*)m_pFile, GAIA::ALGORITHM::clamp(m_offset + offset, 0, m_size), SEEK_SET) == 0)
				{
					m_offset += offset;
					return GAIA::True;
				}
			}
			else if(seektype == FILE_SEEK_TYPE_BACKWARD)
			{
				if(fseek((FILE*)m_pFile, GAIA::ALGORITHM::clamp(m_offset - offset, 0, m_size), SEEK_SET) == 0)
				{
					m_offset -= offset;
					return GAIA::True;
				}
			}
			return GAIA::False;
		}
	};
};

#endif