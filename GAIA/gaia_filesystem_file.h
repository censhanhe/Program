#ifndef		__GAIA_FILESYSTEM_FILE_H__
#define		__GAIA_FILESYSTEM_FILE_H__

namespace GAIA
{
	namespace FSYS
	{
		class FileBase : public GAIA::Entity
		{
		public:
			GAIA_ENUM_BEGIN(OPEN_TYPE)
				OPEN_TYPE_READ	= 1 << 0,
				OPEN_TYPE_WRITE = 1 << 1,
				OPEN_TYPE_CREATEALWAYS	= 1 << 2,
			GAIA_ENUM_END(OPEN_TYPE)
		public:
			virtual GAIA::BL Open(const GAIA::TCH* filekey, const GAIA::UM& opentype) = 0;
			virtual GAIA::BL Close() = 0;
			virtual GAIA::BL IsOpen() const = 0;
			virtual GAIA::N64 Size() const = 0;
			virtual GAIA::BL Resize(const GAIA::N64& size) = 0;
			virtual GAIA::N64 Read(GAIA::GVOID* pDst, const GAIA::N64& size) = 0;
			virtual GAIA::N64 Write(const GAIA::GVOID* pSrc, const GAIA::N64& size) = 0;
			virtual GAIA::BL Seek(SEEK_TYPE seektype, const GAIA::N64& offset) = 0;
			virtual const GAIA::N64& Tell() const = 0;
			virtual GAIA::BL Flush() = 0;
		private:
		};

		class File : public FileBase
		{
		public:
			GINL File(){m_fileopentype = OPEN_TYPE_INVALID; m_size = m_offset = 0; m_pFile = GNIL;}
			GINL virtual ~File(){if(this->IsOpen()) this->Close();}
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Open(const GAIA::TCH* filekey, const GAIA::UM& opentype);
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Close();
			GINL GAIA::BL IsOpen() const{return m_pFile != GNIL;}
			GINL GAIA::N64 Size() const{return m_size;}
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Resize(const GAIA::N64& size);
			template<typename _ObjType> GAIA::BL Read(_ObjType& obj)
			{
				GAIA_AST(!!m_pFile);
				if(m_pFile == GNIL)
					return GAIA::False;
				if(this->Read(&obj, sizeof(obj)) != sizeof(obj))
					return GAIA::False;
				return GAIA::True;
			}
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::N64 Read(GAIA::GVOID* pDst, const GAIA::N64& size);
			template<typename _ObjType> GAIA::BL Write(const _ObjType& obj)
			{
				GAIA_AST(!!m_pFile);
				if(m_pFile == GNIL)
					return GAIA::False;
				if(this->Write(&obj, sizeof(obj)) != sizeof(obj))
					return GAIA::False;
				return GAIA::True;
			}
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::N64 Write(const GAIA::GVOID* pSrc, const GAIA::N64& size);
			template<typename _ParamType> GAIA::N64 WriteText(const _ParamType* pszText){return this->Write(pszText, GAIA::ALGO::strlen(pszText) * sizeof(_ParamType));}
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Seek(SEEK_TYPE seektype, const GAIA::N64& offset);
			GINL const GAIA::N64& Tell() const{return m_offset;}
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Flush();
			template<typename _ObjType> File& operator >> (_ObjType& t){this->Read(t); return *this;}
			template<typename _ObjType> File& operator << (const _ObjType& t){this->Write(t); return *this;}
	#ifdef GAIA_DEBUG_MACHINELENGTH
		private: // Protect for 32-64bit error.
			GINL GAIA::BL Read(GAIA::NM& obj){return GAIA::False;}
			GINL GAIA::BL Write(const GAIA::NM& obj){return GAIA::False;}
			GINL GAIA::BL Read(GAIA::UM& obj){return GAIA::False;}
			GINL GAIA::BL Write(const GAIA::UM& obj){return GAIA::False;}
			GINL GAIA::BL Read(GAIA::WCH& obj){return GAIA::False;}
			GINL GAIA::BL Write(const GAIA::WCH& obj){return GAIA::False;}
			GINL File& operator >> (GAIA::NM& t){return *this;}
			GINL File& operator << (const GAIA::NM& t){return *this;}
			GINL File& operator >> (GAIA::UM& t){return *this;}
			GINL File& operator << (const GAIA::UM& t){return *this;}
			GINL File& operator >> (GAIA::WCH& t){return *this;}
			GINL File& operator << (const GAIA::WCH& t){return *this;}
			GINL GAIA::N64 Read(GAIA::NM* pDst, const GAIA::N64& size){return GAIA::False;}
			GINL GAIA::N64 Write(const GAIA::NM* pDst, const GAIA::N64& size){return GAIA::False;} GINL GAIA::N64 Write(GAIA::NM* pDst, const GAIA::N64& size){return GAIA::False;}
			GINL GAIA::N64 Read(GAIA::UM* pDst, const GAIA::N64& size){return GAIA::False;}
			GINL GAIA::N64 Write(const GAIA::UM* pDst, const GAIA::N64& size){return GAIA::False;} GINL GAIA::N64 Write(GAIA::UM* pDst, const GAIA::N64& size){return GAIA::False;}
	#endif
		private:
			GAIA::UM m_fileopentype;
			GAIA::N64 m_size;
			GAIA::N64 m_offset;
			GAIA::GVOID* m_pFile;
		};
	};
};

#ifndef GAIA_DEBUG_CODEPURE
#	include "gaia_filesystem_file_indp.h"
#endif

#endif