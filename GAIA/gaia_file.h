#ifndef		__GAIA_FILESYSTEM_FILE_H__
#define		__GAIA_FILESYSTEM_FILE_H__

namespace GAIA
{
	namespace FILESYSTEM
	{
		ENUM_BEGIN(FILE_OPEN_TYPE)
			FILE_OPEN_READ				= 0x00000001,
			FILE_OPEN_WRITE				= 0x00000002,
			FILE_OPEN_NOTEXISTCREATE	= 0x00000004,
			FILE_OPEN_CREATEALWAYS		= 0x00000008,
		ENUM_END(FILE_OPEN_TYPE)
		
		ENUM_BEGIN(FILE_SEEK_TYPE)
			FILE_SEEK_BEGIN,
			FILE_SEEK_END,
			FILE_SEEK_FORWARD,
			FILE_SEEK_BACKWARD,
		ENUM_END(FILE_SEEK_TYPE)
		
		template <typename _SizeType, typename _KeyType> class File
		{
		public:
			GINL File();
			GINL virtual ~File();

			GINL GAIA::BL Open(const _KeyType& filekey, FILE_OPEN_TYPE opentype){}
			GINL GAIA::BL Close(){}
			GINL GAIA::BL IsOpen() const{}
			
			template <typename _ObjType> GINL GAIA::BL Read(const _ObjType& obj){}
			GINL const _SizeType& Read(GAIA::GVOID* pDst, const _SizeType& size){}
			template <typename _ObjType> GINL GAIA::BL Write(const _ObjType& obj){}
			GINL const _SizeType& Write(const GAIA::GVOID* pSrc, const _SizeType& size){}

			GINL const _SizeType& Seek(FILE_SEEK_TYPE seektype, const _SizeType& offset){}
			GINL const _SizeType& Tell() const{}
			
		private:
			_SizeType m_size;
			_SizeType m_offset;
			GAIA::GVOID* m_pFile;
		};
	};
};

#endif