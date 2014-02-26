#ifndef 	__FILE_SHARE_H__
#define 	__FILE_SHARE_H__

#ifdef _MSC_VER
#	if defined(_FSHADLL) || defined(_USEFSHADLL)
#		ifdef FILESHARE_EXPORT
#			define __DWARFS_FILESHARE_API __declspec(dllexport)
#		else
#			define __DWARFS_FILESHARE_API __declspec(dllimport)
#		endif
#	else
#		define __DWARFS_FILESHARE_API
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
	/* Constants. */
	static const GAIA::NM MAX_DEPTH = 12;
	static const GAIA::NM MAX_PATHLEN = 240;

	/* Type declaration. */
	typedef GAIA::U64 FILEID; // GINVALID means invalid id.
	typedef GAIA::U16 CHUNKPROGRESS;
	typedef GAIA::CONTAINER::BasicString<GAIA::GCH, GAIA::U8> FSTR;
	typedef GAIA::CONTAINER::Vector<FSTR> FSTRLIST;
	typedef GAIA::CONTAINER::BasicAVLTree<
			FSTR, GAIA::N32, GAIA::N32, 
			GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32>, 
			GAIA_DEFAULT_GROUPELEMENTSIZE> FSTRBTR; 
	typedef GAIA::U32 MAP_INDEX_TYPE; // 0 means invalid id.
	typedef GAIA::CONTAINER::Array<GAIA::CONTAINER::BasicChars<GAIA::GCH, GAIA::N16, MAX_PATHLEN>, MAX_DEPTH> FNAMEPARTLISTTYPE;

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
		GAIA::BL Load(const GAIA::GCH* pszFileName)
		{
			GAIA_AST(!GAIA::ALGORITHM::stremp(pszFileName));
			if(GAIA::ALGORITHM::stremp(pszFileName))
				return GAIA::False;
			GAIA::FILESYSTEM::File file;
			if(!file.Open(pszFileName, GAIA::FILESYSTEM::FILE_OPEN_TYPE_READ))
				return GAIA::False;
			return GAIA::True;
		}
		GAIA::BL Save(const GAIA::GCH* pszFileName)
		{
			GAIA_AST(!GAIA::ALGORITHM::stremp(pszFileName));
			if(GAIA::ALGORITHM::stremp(pszFileName))
				return GAIA::False;
			GAIA::FILESYSTEM::File file;
			if(!file.Open(pszFileName, GAIA::FILESYSTEM::FILE_OPEN_TYPE_CREATEALWAYS | GAIA::FILESYSTEM::FILE_OPEN_TYPE_WRITE))
				return GAIA::False;
			return GAIA::True;
		}
		GAIA::BL Build()
		{
		}
		const FILEID* GetIDByName(const GAIA::GCH* pszFileName)
		{
			GAIA_AST(!GAIA::ALGORITHM::stremp(pszFileName));
			if(GAIA::ALGORITHM::stremp(pszFileName))
				return GNULL;
			__FileRecNameListType::_datatype f;
			__FileRecIDListType::_datatype frec;
			f.m_pRec = &frec;
			if(!this->NameToMapIndex(pszFileName, f.m_pRec->m_mapindex))
				return GNULL;
			GAIA::UM uIndex = m_recnames.find(f);
			if(uIndex == GINVALID)
				return GNULL;
			return &m_recnames[uIndex].m_pRec->m_id;
		}
		GAIA::BL GetName(const FILEID& id, GAIA::GCH* pResult)
		{
			__FileRecIDListType::_datatype f;
			f.m_id = id;
			GAIA::UM uIndex = m_recids.find(f);
			if(uIndex == GINVALID)
				return GAIA::False;
			return this->MapIndexToName(m_recids[uIndex].m_mapindex, pResult);
		}
		CHUNKPROGRESS GetChunkType(const FILEID& id) const
		{
			__FileRecIDListType::_datatype f;
			f.m_id = id;
			GAIA::UM uIndex = m_recids.find(f);
			if(uIndex == GINVALID)
				return (CHUNKPROGRESS)GINVALID;
			return m_states[uIndex].m_chunkprogress;
		}
	private:
		GAIA::BL NameToMapIndex(const GAIA::GCH* pszFileName, MAP_INDEX_TYPE* pResult) const
		{
			GAIA_AST(!GAIA::ALGORITHM::stremp(pszFileName));
			if(GAIA::ALGORITHM::stremp(pszFileName))
				return GAIA::False;
			GAIA_AST(pResult != GNULL);
			if(pResult == GNULL)
				return GAIA::False;
			FNAMEPARTLISTTYPE namelist;
			if(!this->GenerateFileNamePartList(pszFileName, namelist))
				return GAIA::False;
			NameMap f;
			f.m_name.reserve(MAX_PATHLEN);
			for(FNAMEPARTLISTTYPE::_sizetype x = 0; x < namelist.size(); ++x)
			{
				f.m_name = namelist[x].front_ptr();
				GAIA::N32 n = m_names.find(f);
				if(n == GINVALID)
					return GAIA::False;
				pResult[x] = n + 1;
			}
			pResult[namelist.size()] = 0;
			return GAIA::True;
		}
		GAIA::BL MapIndexToName(const MAP_INDEX_TYPE* pResult, GAIA::GCH* pszFileName) const
		{
			GAIA_AST(!GAIA::ALGORITHM::stremp(pszFileName));
			if(GAIA::ALGORITHM::stremp(pszFileName))
				return GAIA::False;
			GAIA_AST(pResult != GNULL);
			if(pResult == GNULL)
				return GAIA::False;
			const MAP_INDEX_TYPE* p = pResult;
			GAIA::GCH* pDst = pszFileName;
			while(*p != 0)
			{
				GAIA::ALGORITHM::strcpy(pDst, m_names[*p].m_name.front_ptr());
				pDst += m_names[*p].m_name.size();
				++p;
			}
			return GAIA::True;
		}
		GAIA::BL GenerateFileNamePartList(const GAIA::GCH* pszFileName, FNAMEPARTLISTTYPE& listResult) const
		{
			GAIA_AST(!GAIA::ALGORITHM::stremp(pszFileName));
			if(GAIA::ALGORITHM::stremp(pszFileName))
				return GAIA::False;
			listResult.clear();
			const GAIA::GCH* p = pszFileName;
			for(;;)
			{
				const GAIA::GCH* pNew = GAIA::ALGORITHM::stridrop(p, "/\\\0");
				if(pNew != p)
				{
					if(pNew == GNULL || *pNew == 0)
					{
						GAIA::GCH sz[MAX_PATHLEN];
						GAIA::ALGORITHM::strcpy(sz, pNew);
						if(sz[0] != 0)
							listResult.push_back(sz);
						break;
					}
					else
					{
						GAIA::GCH sz[MAX_PATHLEN];
						GAIA::ALGORITHM::memcpy(sz, p, (pNew - p) * sizeof(GAIA::GCH));
						sz[pNew - p] = 0;
						if(sz[0] != 0)
							listResult.push_back(sz);
					}
				}
				p = pNew + 1;
			}
			return GAIA::True;
		}
	private:
		class NameMap
		{
		public:
			GINL GAIA::BL operator == (const NameMap& src) const{return m_name == src.m_name;}
			GINL GAIA::BL operator != (const NameMap& src) const{return m_name != src.m_name;}
			GINL GAIA::BL operator >= (const NameMap& src) const{return m_name >= src.m_name;}
			GINL GAIA::BL operator <= (const NameMap& src) const{return m_name <= src.m_name;}
			GINL GAIA::BL operator > (const NameMap& src) const{return m_name > src.m_name;}
			GINL GAIA::BL operator < (const NameMap& src) const{return m_name < src.m_name;}
			FSTR m_name;
		};
		class FileRec
		{
		public:
			GINL FileRec& operator = (const FileRec& src){m_id = src.m_id; GAIA::ALGORITHM::strcpy(m_mapindex, src.m_mapindex); return *this;}
			GINL GAIA::BL operator == (const FileRec& src) const{return m_id == src.m_id;}
			GINL GAIA::BL operator != (const FileRec& src) const{return m_id != src.m_id;}
			GINL GAIA::BL operator >= (const FileRec& src) const{return m_id >= src.m_id;}
			GINL GAIA::BL operator <= (const FileRec& src) const{return m_id <= src.m_id;}
			GINL GAIA::BL operator > (const FileRec& src) const{return m_id > src.m_id;}
			GINL GAIA::BL operator < (const FileRec& src) const{return m_id < src.m_id;}
			FILEID m_id;
			MAP_INDEX_TYPE m_mapindex[MAX_DEPTH];
			GAIA::U32 m_uSequence;
		};
		class FileRecName
		{
		public:
			GINL GAIA::BL operator == (const FileRecName& src) const{return GAIA::ALGORITHM::strcmp(m_pRec->m_mapindex, src.m_pRec->m_mapindex) == 0;}
			GINL GAIA::BL operator != (const FileRecName& src) const{return !(this->operator != (src));}
			GINL GAIA::BL operator >= (const FileRecName& src) const{return GAIA::ALGORITHM::strcmp(m_pRec->m_mapindex, src.m_pRec->m_mapindex) >= 0;}
			GINL GAIA::BL operator <= (const FileRecName& src) const{return GAIA::ALGORITHM::strcmp(m_pRec->m_mapindex, src.m_pRec->m_mapindex) <= 0;}
			GINL GAIA::BL operator > (const FileRecName& src) const{return !(this->operator <= (src));}
			GINL GAIA::BL operator < (const FileRecName& src) const{return !(this->operator >= (src));}
			FileRec* m_pRec;
		};
		class FileState
		{
		public:
			CHUNKPROGRESS m_chunkprogress;
		};
	public:
		typedef GAIA::CONTAINER::Vector<NameMap> __NameMapType;
		typedef GAIA::CONTAINER::Vector<FileRec> __FileRecIDListType;
		typedef GAIA::CONTAINER::Vector<FileRecName> __FileRecNameListType;
		typedef GAIA::CONTAINER::Vector<FileState> __FileStateListType;
		typedef GAIA::CONTAINER::BasicTrieTree<GAIA::N32, GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32>, 10> __FileTreeType;
	private:
		__NameMapType m_names; // Sorted by file name.
		__FileRecIDListType m_recids; // Sorted by file id.
		__FileRecNameListType m_recnames; // Sorted by file name.
		__FileStateListType m_states; // Sorted as file id list.
		__FileTreeType m_ftree; // Sorted by file name section.
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
			GAIA::U16 m_maxthreadcnt;
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
			m_uUSpeed = (GAIA::U64)GINVALID;
			m_uDSpeed = (GAIA::U64)GINVALID;
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
