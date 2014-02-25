#ifndef 	__FILE_SHARE_H__
#define 	__FILE_SHARE_H__

#include 	"../../GAIA/gaia.h"

#ifdef _MSC_VER
#	ifdef FILESHARE_EXPORT
#		define __DWARFS_FILESHARE_API __declspec(dllexport)
#	else
#		define __DWARFS_FILESHARE_API __declspec(dllimport)
#	endif
#endif

namespace FSHA
{
	/* Type declaration. */
	typedef GAIA::U64 FILEID;
	typedef GAIA::CONTAINER::BasicString<GAIA::GCH, GAIA::U8> STR;

	/* File sequence. */
	class __DWARFS_FILESHARE_API FileSequence
	{
	public:
		FileSequence();
		~FileSequence();
		GAIA::BL Add(const GAIA::GCH* pszFileName);
		GAIA::BL DeleteAll();
		const GAIA::UM& GetRecCount() const;
		const GAIA::GCH* GetRec(const GAIA::UM& index);
	private:
	};

	/* File list class.  */
	class __DWARFS_FILESHARE_API FileList
	{
	public:
		FileList();
		~FileList();
		GAIA::BL Load(const GAIA::GCH* pszFileName);
		GAIA::BL Save(const GAIA::GCH* pszFileName);
		GAIA::BL Build(FileSequence* pFSeq = GNULL);
		const FILEID* GetIDByName(const GAIA::GCH* pszFileName);
		const GAIA::GCH* GetName(const FILEID& id);
	private:
		class FileRec
		{
		public:
			FILEID m_id;
			STR m_name;
		};
		class FileState
		{
		public:
			GAIA::U16 m_nextchunk;
		};
	public:
		typedef GAIA::CONTAINER::Vector<FileRec> __FileRecListType;
		typedef GAIA::CONTAINER::Vector<FileState> __FileStateListType;
	private:
		__FileRecListType m_recs;
		__FileStateListType m_states;
	};

	/* File share class. */
	class __DWARFS_FILESHARE_API FileShare
	{
	public:
		class FileShareDesc
		{
		public:

		}

	public:
		GAIA::BL Initialize(const FileShareDesc& desc);
		GAIA::BL Release();
		GAIA::BL IsInitialized() const;
		const FileShareDesc& GetDesc() const;

		GAIA::BL Startup();
		GAIA::BL Shutdown();
		GAIA::BL IsStartuped() const;

		GAIA::BL SetMaxUploadSpeed(const GAIA::UM& uSpeed);
		const GAIA::UM& GetMaxUploadSpeed() const;
		GAIA::BL SetMaxDownloadSpeed(const GAIA::UM& uSpeed);
		const GAIA::UM& GetMaxDownloadSpeed() const;

		GAIA::BL Command(const GAIA::GCH* pszCmd);
	private:
	};
};

#endif
