#ifndef		__GAIA_FILESYSTEM_FILEBASE_H__
#define		__GAIA_FILESYSTEM_FILEBASE_H__

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
	};
};

#endif