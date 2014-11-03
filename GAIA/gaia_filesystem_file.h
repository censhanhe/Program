#ifndef		__GAIA_FILESYSTEM_FILE_H__
#define		__GAIA_FILESYSTEM_FILE_H__

namespace GAIA
{
	namespace FSYS
	{
	#if GAIA_OS == GAIA_OS_WINDOWS
		static const GAIA::U32 MAXPL = MAX_PATH;
	#else
		static const GAIA::U32 MAXPL = 260;
	#endif

		class FileBase : public GAIA::Entity
		{
		public:
			typedef GAIA::N64 __FileSizeType;
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
			virtual GAIA::FSYS::FileBase::__FileSizeType Size() const = 0;
			virtual GAIA::BL Resize(const GAIA::FSYS::FileBase::__FileSizeType& size) = 0;
			virtual GAIA::FSYS::FileBase::__FileSizeType Read(GAIA::GVOID* pDst, const GAIA::FSYS::FileBase::__FileSizeType& size) = 0;
			virtual GAIA::FSYS::FileBase::__FileSizeType Write(const GAIA::GVOID* pSrc, const GAIA::FSYS::FileBase::__FileSizeType& size) = 0;
			virtual GAIA::BL Seek(SEEK_TYPE seektype, const GAIA::FSYS::FileBase::__FileSizeType& offset) = 0;
			virtual const GAIA::FSYS::FileBase::__FileSizeType& Tell() const = 0;
			virtual GAIA::BL Flush() = 0;
		private:
		};

		class File : public FileBase
		{
		public:
			GINL File(){m_fileopentype = OPEN_TYPE_INVALID; m_size = m_offset = 0; m_pFile = GNIL;}
			GINL virtual ~File(){if(this->IsOpen()) this->Close();}
			GINL GAIA::BL Open(const GAIA::TCH* filekey, const GAIA::UM& opentype);
			GINL GAIA::BL Close();
			GINL GAIA::BL IsOpen() const{return m_pFile != GNIL;}
			GINL GAIA::FSYS::FileBase::__FileSizeType Size() const{return m_size;}
			GINL GAIA::BL Resize(const GAIA::FSYS::FileBase::__FileSizeType& size);
			template<typename _ObjType> GAIA::BL Read(_ObjType& obj)
			{
				GAIA_AST(!!m_pFile);
				if(m_pFile == GNIL)
					return GAIA::False;
				if(this->Read(&obj, sizeof(obj)) != sizeof(obj))
					return GAIA::False;
				return GAIA::True;
			}
			GINL GAIA::FSYS::FileBase::__FileSizeType Read(GAIA::GVOID* pDst, const GAIA::FSYS::FileBase::__FileSizeType& size);
			template<typename _ObjType> GAIA::BL Write(const _ObjType& obj)
			{
				GAIA_AST(!!m_pFile);
				if(m_pFile == GNIL)
					return GAIA::False;
				if(this->Write(&obj, sizeof(obj)) != sizeof(obj))
					return GAIA::False;
				return GAIA::True;
			}
			GINL GAIA::FSYS::FileBase::__FileSizeType Write(const GAIA::GVOID* pSrc, const GAIA::FSYS::FileBase::__FileSizeType& size);
			template<typename _ParamType> GAIA::FSYS::FileBase::__FileSizeType WriteText(const _ParamType* pszText){return this->Write(pszText, GAIA::ALGO::strlen(pszText) * sizeof(_ParamType));}
			GINL GAIA::BL Seek(SEEK_TYPE seektype, const GAIA::FSYS::FileBase::__FileSizeType& offset);
			GINL const GAIA::FSYS::FileBase::__FileSizeType& Tell() const{return m_offset;}
			GINL GAIA::BL Flush();
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
			GINL GAIA::FSYS::FileBase::__FileSizeType Read(GAIA::NM* pDst, const GAIA::FSYS::FileBase::__FileSizeType& size){return GAIA::False;}
			GINL GAIA::FSYS::FileBase::__FileSizeType Write(const GAIA::NM* pDst, const GAIA::FSYS::FileBase::__FileSizeType& size){return GAIA::False;} GINL GAIA::FSYS::FileBase::__FileSizeType Write(GAIA::NM* pDst, const GAIA::FSYS::FileBase::__FileSizeType& size){return GAIA::False;}
			GINL GAIA::FSYS::FileBase::__FileSizeType Read(GAIA::UM* pDst, const GAIA::FSYS::FileBase::__FileSizeType& size){return GAIA::False;}
			GINL GAIA::FSYS::FileBase::__FileSizeType Write(const GAIA::UM* pDst, const GAIA::FSYS::FileBase::__FileSizeType& size){return GAIA::False;} GINL GAIA::FSYS::FileBase::__FileSizeType Write(GAIA::UM* pDst, const GAIA::FSYS::FileBase::__FileSizeType& size){return GAIA::False;}
	#endif
		private:
			GAIA::UM m_fileopentype;
			GAIA::FSYS::FileBase::__FileSizeType m_size;
			GAIA::FSYS::FileBase::__FileSizeType m_offset;
			GAIA::GVOID* m_pFile;
		};
	};
};

#include "gaia_filesystem_file_indp.h"

#endif
