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
#else
#	define __DWARFS_FILESHARE_API
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
			return GAIA::True;
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
			// Load name map list.
			{
			}
			// Load file tree.
			{
				// Load id.
				// Load file chunk progress.
				// Load file sequence.
				// Load file map index list.
			}
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
			// Save name map list.
			{
			}
			// Save file tree.
			{
				// Save id.
				// Save file chunk progress.
				// Save file sequence.
				// Save file map index list.
			}
			return GAIA::True;
		}
		GAIA::BL Build()
		{
			return GAIA::True;
		}
		const FILEID* GetIDByName(const GAIA::GCH* pszFileName)
		{
			GAIA_AST(!GAIA::ALGORITHM::stremp(pszFileName));
			if(GAIA::ALGORITHM::stremp(pszFileName))
				return GNULL;
			MAP_INDEX_TYPE mapindex[MAX_DEPTH];
			if(!this->NameToMapIndex(pszFileName, mapindex))
				return GNULL;
			TrieNode tnlist[MAX_DEPTH];
			MAP_INDEX_TYPE* p = mapindex;
			for(;;)
			{
				if(*p == 0)
					break;
				TrieNode& tn = tnlist[p - mapindex];
				tn.m_mapindex = *p;
			}
			GAIA_AST(p != mapindex);
			__FileTreeType::Node* pNode = m_ftree.find(GNULL, tnlist, p - mapindex);
			if(pNode == GNULL)
				return GNULL;
			return &(**pNode).m_id;
		}
		GAIA::BL GetName(const FILEID& id, GAIA::GCH* pResult)
		{
			__FileRecIDListType::_datatype f;
			f.m_id = id;
			GAIA::UM uIndex = m_recids.find(f);
			if(uIndex == GINVALID)
				return GAIA::False;
			MAP_INDEX_TYPE mapindex[MAX_DEPTH];
			if(!this->GenerateMapIndex(m_recids[uIndex].m_it, mapindex))
				return GAIA::False;
			return this->MapIndexToName(mapindex, pResult);
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
		class TrieNode
		{
		public:
			GINL TrieNode& operator = (const TrieNode& src){m_mapindex = src.m_mapindex; return *this;}
			GAIA_CLASS_OPERATOR_COMPARE(m_mapindex, m_mapindex, TrieNode);
			MAP_INDEX_TYPE m_mapindex;
			FILEID m_id;
		};
	public:
		typedef GAIA::CONTAINER::BasicTrieTree<TrieNode, GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32>, 10> __FileTreeType;
	private:
		class NameMap
		{
		public:
			GAIA_CLASS_OPERATOR_COMPARE(m_name, m_name, NameMap);
			FSTR m_name;
		};
		class FileRec
		{
		public:
			GINL FileRec& operator = (const FileRec& src){m_id = src.m_id; m_it = src.m_it; return *this;}
			GAIA_CLASS_OPERATOR_COMPARE(m_id, m_id, FileRec);
			FILEID m_id;
			__FileTreeType::const_it m_it;
			GAIA::U32 m_uSequence;
		};
		class FileState
		{
		public:
			CHUNKPROGRESS m_chunkprogress;
		};
	public:
		typedef GAIA::CONTAINER::Vector<NameMap> __NameMapType;
		typedef GAIA::CONTAINER::Vector<FileRec> __FileRecIDListType;
		typedef GAIA::CONTAINER::Vector<FileState> __FileStateListType;
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
		GAIA::BL GenerateMapIndex(__FileTreeType::const_it it, MAP_INDEX_TYPE* pMapIndex) const
		{
			if(it.empty())
				return GAIA::False;
			MAP_INDEX_TYPE* p = pMapIndex;
			while(!it.empty())
			{
				*p++ = (*it).m_mapindex;
				it = m_ftree.parent(it);
				if(m_ftree.root(it))
					it = m_ftree.parent(it);
			}
			GAIA::ALGORITHM::inverse(pMapIndex, p - 1);
			return GAIA::True;
		}
	private:
		__NameMapType m_names; // Sorted by file name.
		__FileRecIDListType m_recids; // Sorted by file id.
		__FileStateListType m_states; // Sorted as file id list.
		__FileTreeType m_ftree; // Sorted by file name section.
	};

	/* User group class. */
	class __DWARFS_FILESHARE_API UserGroup
	{
	public:
		typedef GAIA::CONTAINER::BasicChars<GAIA::GCH, GAIA::U8, 16> __UserNameType;
		typedef GAIA::CONTAINER::BasicChars<GAIA::GCH, GAIA::U8, 16> __PasswordType;
		typedef GAIA::CONTAINER::BasicChars<GAIA::GCH, GAIA::U8, 16> __GroupNameType;
		typedef GAIA::CONTAINER::Vector<__UserNameType> __UserNameListType;
		typedef GAIA::CONTAINER::Vector<__GroupNameType> __GroupNameListType;
	private:
		class Right
		{
		public:
			Right(){this->Reset();}
			GINL GAIA::GVOID Reset()
			{
				m_bRead = GAIA::False;
				m_bWrite = GAIA::False;
			}
			GAIA::U8 m_bRead : 1;
			GAIA::U8 m_bWrite : 1;
		};
		class Group;
		class User
		{
		public:
			typedef GAIA::CONTAINER::Vector<Group*> __GroupRefListType;
		public:
			GAIA_CLASS_OPERATOR_COMPARE(m_name, m_name, User);
			__UserNameType m_name;
			__PasswordType m_pwd;
			__GroupRefListType m_refgroups;
		};
		class Group
		{
		public:
			typedef GAIA::CONTAINER::Set<GAIA::CONTAINER::Ref<User>> __UserRefListType;
		public:
			GAIA_CLASS_OPERATOR_COMPARE(m_name, m_name, Group);
			__GroupNameType m_name;
			__UserRefListType m_refusers;
			Right m_right;
		};
	private:
		typedef GAIA::CONTAINER::Set<GAIA::CONTAINER::Ref<User>> __UserSetType;
		typedef GAIA::CONTAINER::Set<GAIA::CONTAINER::Ref<Group>> __GroupSetType;
		typedef GAIA::CONTAINER::Pool<User, 100> __UserPoolType;
		typedef GAIA::CONTAINER::Pool<Group, 100> __GroupPoolType;
	public:
		GINL GAIA::BL Load(const GAIA::GCH* pszFileName)
		{
			GAIA_AST(!GAIA::ALGORITHM::stremp(pszFileName));
			if(GAIA::ALGORITHM::stremp(pszFileName))
				return GAIA::False;
			return GAIA::True;
		}
		GINL GAIA::BL Save(const GAIA::GCH* pszFileName)
		{
			GAIA_AST(!GAIA::ALGORITHM::stremp(pszFileName));
			if(GAIA::ALGORITHM::stremp(pszFileName))
				return GAIA::False;
			return GAIA::True;
		}
		GINL GAIA::BL AddUser(const __UserNameType& name)
		{
			GAIA_AST(!name.empty());
			if(name.empty())
				return GAIA::False;
			if(this->FindUser(name))
				return GAIA::False;
			User* pUser = m_upool.alloc();
			__UserSetType::_datatype ru = pUser;
			pUser->m_name = name;
			return m_users.insert(pUser);
		}
		GINL GAIA::BL SetUserPassword(const __UserNameType& name, const __PasswordType& pwd)
		{
			GAIA_AST(!name.empty());
			if(name.empty())
				return GAIA::False;
			User* pUser = this->FindUserInternal(name);
			if(pUser == GNULL)
				return GAIA::False;
			pUser->m_pwd = pwd;
			return GAIA::True;
		}
		GINL const GAIA::GCH* GetUserPassword(const __UserNameType& name) const
		{
			GAIA_AST(!name.empty());
			if(name.empty())
				return GNULL;
			const User* pUser = this->FindUserInternal(name);
			if(pUser == GNULL)
				return GNULL;
			return pUser->m_pwd;
		}
		GINL GAIA::BL DeleteUser(const __UserNameType& name)
		{
			GAIA_AST(!name.empty());
			if(name.empty())
				return GAIA::False;
			return GAIA::True;
		}
		GINL GAIA::GVOID DeleteUserAll()
		{
		}
		GINL GAIA::BL FindUser(const __UserNameType& name) const
		{
			GAIA_AST(!name.empty());
			if(name.empty())
				return GAIA::False;
			const User* pUser = this->FindUserInternal(name);
			if(pUser == GNULL)
				return GAIA::False;
			return GAIA::True;
		}
		GINL GAIA::BL AddGroup(const __GroupNameType& name)
		{
			GAIA_AST(!name.empty());
			if(name.empty())
				return GAIA::False;
			return GAIA::True;
		}
		GINL GAIA::BL DeleteGroup(const __GroupNameType& name)
		{
			GAIA_AST(!name.empty());
			if(name.empty())
				return GAIA::False;
			return GAIA::True;
		}
		GINL GAIA::GVOID DeleteGroupAll()
		{
		}
		GINL GAIA::BL FindGroup(const __GroupNameType& name) const
		{
			GAIA_AST(!name.empty());
			if(name.empty())
				return GAIA::False;
			return GAIA::True;
		}
		GINL GAIA::BL AddGroupUser(const __GroupNameType& gname, const __UserNameType& uname)
		{
			GAIA_AST(!gname.empty());
			if(gname.empty())
				return GAIA::False;
			GAIA_AST(!uname.empty());
			if(uname.empty())
				return GAIA::False;
			return GAIA::True;
		}
		GINL GAIA::BL DeleteGroupUser(const __GroupNameType& gname, const __UserNameType& uname)
		{
			GAIA_AST(!gname.empty());
			if(gname.empty())
				return GAIA::False;
			GAIA_AST(!uname.empty());
			if(uname.empty())
				return GAIA::False;
			return GAIA::True;
		}
		GINL GAIA::BL DeleteGroupUserAll()
		{
		}
		GINL GAIA::BL EnumUserGroup(const __UserNameType& name, __GroupNameListType& result) const
		{
			GAIA_AST(!name.empty());
			if(name.empty())
				return GAIA::False;
			return GAIA::True;
		}
		GINL GAIA::BL EnumGroupUser(const __GroupNameType& name, __UserNameListType& result) const
		{
			GAIA_AST(!name.empty());
			if(name.empty())
				return GAIA::False;
			return GAIA::True;
		}
	private:
		GINL const User* FindUserInternal(const __UserNameType& name) const
		{
			User finder;
			finder.m_name = name;
			const __UserSetType::_datatype* pFinded = m_users.find(&finder);
			if(pFinded == GNULL)
				return GNULL;
			return *pFinded;
		}
		GINL User* FindUserInternal(const __UserNameType& name)
		{
			User finder;
			finder.m_name = name;
			__UserSetType::_datatype* pFinded = m_users.find(&finder);
			if(pFinded == GNULL)
				return GNULL;
			return *pFinded;
		}
	private:
		__UserSetType m_users; // Sorted by user name.
		__GroupSetType m_groups; // Sorted by group name.
		__UserPoolType m_upool;
		__GroupPoolType m_gpool;
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
			GAIA_AST(!GAIA::ALGORITHM::stremp(pszCmd));
			if(GAIA::ALGORITHM::stremp(pszCmd))
				return GAIA::False;
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
