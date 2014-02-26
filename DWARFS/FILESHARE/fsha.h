#ifndef 	__FILE_SHARE_H__
#define 	__FILE_SHARE_H__

#ifdef _MSC_VER
#	ifdef FILESHARE_EXPORT
#		define __DWARFS_FILESHARE_API __declspec(dllexport)
#	else
#		define __DWARFS_FILESHARE_API __declspec(dllimport)
#	endif
#	pragma warning(disable : 4996)
#	pragma warning(disable : 4800)
#	pragma warning(disable : 4244)
#	pragma warning(disable : 4018)
#	pragma warning(disable : 4251)
#endif

#include 	"../../GAIA/gaia.h"

namespace FSHA
{
	/* Type declaration. */
	typedef GAIA::U64 FILEID;
	typedef GAIA::CONTAINER::BasicString<GAIA::GCH, GAIA::U8> FSTR;
	typedef GAIA::CONTAINER::Vector<FSTR> FSTRLIST;
	typedef GAIA::CONTAINER::BasicAVLTree<
			FSTR, GAIA::N32, GAIA::N32, 
			GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32>, 
			GAIA_DEFAULT_GROUPELEMENTSIZE> FSTRBTR; 

	/* File sequence. */
	class __DWARFS_FILESHARE_API FileSequence
	{
	public:
		FileSequence(){}
		~FileSequence(){}
		GAIA::BL Add(const GAIA::GCH* pszFileName)
		{
			GAIA_AST(!GAIA::ALGORITHM::stremp(pszFileName));
			if(GAIA::ALGORITHM::stremp(pszFileName))
				return GAIA::False;
			FSTR str = pszFileName;
			str.tolower();
			if(m_filesbtr.find(str) != GNULL)
				return GAIA::False;
			m_files.push_back(str);
			m_filesbtr.insert(str);
			return GAIA::True;
		}
		GAIA::BL DeleteAll()
		{
			m_files.destroy();
			m_filesbtr.destroy();
		}
		const GAIA::UM& GetRecCount() const{return m_files.size();}
		const GAIA::GCH* GetRec(const GAIA::UM& index){if(index >= this->GetRecCount()) return GNULL; return m_files[index];}
	private:
		FSTRLIST m_files;
		FSTRBTR m_filesbtr;
	};

	/* File list class.  */
	class __DWARFS_FILESHARE_API FileList
	{
	public:
		FileList(){}
		~FileList(){}
		GAIA::BL Load(const GAIA::GCH* pszFileName){}
		GAIA::BL Save(const GAIA::GCH* pszFileName){}
		GAIA::BL Build(FileSequence* pFSeq = GNULL){}
		const FILEID* GetIDByName(const GAIA::GCH* pszFileName){}
		const GAIA::GCH* GetName(const FILEID& id){}
	private:
		class FileRec
		{
		public:
			FILEID m_id;
			FSTR m_name;
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
		class __DWARFS_FILESHARE_API FileShareDesc
		{
		public:
			FileShareDesc()
			{
				m_maxthreadcnt = 0xFF;
			}
			GAIA::U32 m_maxthreadcnt;
		};

	public:
		FileShare(){this->init();}
		~FileShare(){}
		
		GAIA::BL Initialize(const FileShareDesc& desc)
		{
			if(m_bInitialized)
				return GAIA::False;
			m_bInitialized = GAIA::True;
			return GAIA::True;
		}
		
		GAIA::BL Release()
		{
			if(!m_bInitialized)
				return GAIA::False;
			m_bInitialized = GAIA::False;
			return GAIA::True;
		}
		
		GAIA::BL IsInitialized() const
		{
			return m_bInitialized;
		}
		
		const FileShareDesc& GetDesc() const
		{
			return m_desc;
		}

		GAIA::BL Startup()
		{
			if(m_bStartuped)
				return GAIA::False;
			m_bStartuped = GAIA::True;
			return GAIA::True;
		}
		
		GAIA::BL Shutdown()
		{
			if(!m_bStartuped)
				return GAIA::False;
			m_bStartuped = GAIA::False;
			return GAIA::True;
		}
		
		GAIA::BL IsStartuped() const
		{
			return m_bStartuped;
		}

		GAIA::GVOID SetMaxUploadSpeed(const GAIA::U64& uSpeed){m_uUSpeed = uSpeed;}
		const GAIA::U64& GetMaxUploadSpeed() const{return m_uUSpeed;}
		GAIA::GVOID SetMaxDownloadSpeed(const GAIA::U64& uSpeed){m_uDSpeed = uSpeed;}
		const GAIA::U64& GetMaxDownloadSpeed() const{return m_uDSpeed;}

		GAIA::BL Command(const GAIA::GCH* pszCmd)
		{
			return GAIA::True;
		}
	private:
		GAIA::GVOID init()
		{
			m_bInitialized = GAIA::False;
			m_bStartuped = GAIA::False;
		}
	private:	
		FileShareDesc m_desc;
		GAIA::BL m_bInitialized;
		GAIA::BL m_bStartuped;
		GAIA::U64 m_uUSpeed;
		GAIA::U64 m_uDSpeed;
	};
};

#endif
