#ifndef		__GAIA_FILESYSTEM_FILE_H__
#define		__GAIA_FILESYSTEM_FILE_H__

namespace GAIA
{
	namespace FILESYSTEM
	{
		ENUM_BEGIN(FILE_OPEN_TYPE)
			FILE_OPEN_TYPE_READ				= 0x00000001,
			FILE_OPEN_TYPE_WRITE			= 0x00000002,
			FILE_OPEN_TYPE_CREATEALWAYS		= 0x00000004,
		ENUM_END(FILE_OPEN_TYPE)
		
		ENUM_BEGIN(FILE_SEEK_TYPE)
			FILE_SEEK_TYPE_BEGIN,
			FILE_SEEK_TYPE_END,
			FILE_SEEK_TYPE_FORWARD,
			FILE_SEEK_TYPE_BACKWARD,
		ENUM_END(FILE_SEEK_TYPE)
		
		class File
		{
		public:
			GINL File(){m_fileopentype = FILE_OPEN_TYPE_INVALID; m_size = m_offset = 0; m_pFile = GNULL;}
			GINL virtual ~File(){if(this->IsOpen()) this->Close();}
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Open(const GAIA::GCH* filekey, const GAIA::UM& opentype);
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Close();
			GINL GAIA::BL IsOpen() const{if(m_pFile == GNULL) return GAIA::False; return GAIA::True;}
			GINL GAIA::N64 Size() const{return m_size;}
			template <typename _ObjType> GINL GAIA::BL Read(_ObjType& obj)
			{
				GAIA_ASSERT(m_pFile != GNULL); 
				if(m_pFile == GNULL)
					return GAIA::False;
				if(this->Read(&obj, sizeof(obj)) != sizeof(obj))
					return GAIA::False;
				return GAIA::True;
			}
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::N64 Read(GAIA::GVOID* pDst, const GAIA::N64& size);
			template <typename _ObjType> GINL GAIA::BL Write(const _ObjType& obj)
			{
				GAIA_ASSERT(m_pFile != GNULL);
				if(m_pFile == GNULL)
					return GAIA::False;
				if(this->Write(&obj, sizeof(obj)) != sizeof(obj))
					return GAIA::False;
				return GAIA::True;
			}
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::N64 Write(const GAIA::GVOID* pSrc, const GAIA::N64& size);
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Seek(FILE_SEEK_TYPE seektype, const GAIA::N64& offset);
			GINL const GAIA::N64& Tell() const{return m_offset;}
		private:
			GAIA::UM m_fileopentype;
			GAIA::N64 m_size;
			GAIA::N64 m_offset;
			GAIA::GVOID* m_pFile;
		};
	};
};

#ifndef GAIA_DEBUG_CODEPURE
#	include "gaia_file_indp.h"
#endif

#endif