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
#	pragma warning(disable : 4102)
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
	static const GAIA::GCH VERSION_STRING[] = "00.00.01.00";
	static const GAIA::U32 VERSION = 0x00000100;
	static const GAIA::NM MAX_DEPTH = 12;
	static const GAIA::NM MAX_PATHLEN = 240;
	static const GAIA::GCH FILE_USERGROUP[] = "usergroup";
	static const GAIA::U32 FILE_USERGROUP_FLAG = 'FSUG';
	static const GAIA::U32 FILE_USERGROUP_VERSION = 0;
	static const GAIA::GCH FILE_FILELIST[] = "filelist";
	static const GAIA::U32 FILE_FILELIST_FLAG = 'FSFL';
	static const GAIA::U32 FILE_FILELIST_VERSION = 0;

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
	typedef GAIA::CONTAINER::BasicChars<GAIA::GCH, GAIA::N16, MAX_PATHLEN> FNAMETYPE;
	typedef GAIA::CONTAINER::Array<FNAMETYPE, MAX_DEPTH> FNAMEPARTLISTTYPE;

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
		const GAIA::NM& GetRecCount() const{return m_files.size();}
		const GAIA::GCH* GetRec(const GAIA::NM& index){if(index >= this->GetRecCount()) return GNULL; return m_files[index];}
	private:
		FSTRLIST m_files;
		FSTRBTR m_filesbtr;
	};

	/* File list class. */
	class __DWARFS_FILESHARE_API FileList
	{
	public:
		FileList(){this->init();}
		~FileList(){}
		GAIA::BL Load(const GAIA::GCH* pszFileName)
		{
			GAIA_AST(!GAIA::ALGORITHM::stremp(pszFileName));
			if(GAIA::ALGORITHM::stremp(pszFileName))
				return GAIA::False;

			/* Construct serializer. */
			GAIA::FRAMEWORK::Factory* pFactory = new GAIA::FRAMEWORK::Factory;
			GAIA::SERIALIZER::Serializer* pSerializer = 
				(GAIA::SERIALIZER::Serializer*)pFactory->CreateInstance(GAIA::FRAMEWORK::GAIA_CLSID_SERIALIZER, GNULL);
			GAIA::IO::FileIO* pFileIO = (GAIA::IO::FileIO*)pFactory->CreateInstance(GAIA::FRAMEWORK::GAIA_CLSID_FILEIO, GNULL);	
			if(!pFileIO->Open(FILE_FILELIST, GAIA::IO::IO::IO_TYPE_READ))
			{
				pFileIO->Release();
				pSerializer->Release();
				delete pFactory;
				return GAIA::False;
			}
			pSerializer->BindIO(pFileIO);
			pFileIO->Release();
			GAIA::SERIALIZER::Serializer& sr = *pSerializer;

			/* Read file head. */
			GAIA::U32 uFileFlag;
			sr >> uFileFlag;
			if(uFileFlag != FILE_FILELIST_FLAG)
				goto FUNCTION_END;

			GAIA::U32 uVersion;
			sr >> uVersion;
			if(uVersion > FILE_FILELIST_VERSION)
				goto FUNCTION_END;

			/* Read name map list. */
			{
				__NameMapType::_sizetype size;
				sr >> size;
				for(__NameMapType::_sizetype x = 0; x < size; ++x)
				{
					__NameMapType::_datatype d;
					sr >> d.m_name;
					m_names.push_back(d);
				}
			}

			/* Read file tree. */
			{
				/* Read id. */
				/* Read file chunk progress. */
				/* Read file sequence. */
				/* Read file map index list. */
			}

		FUNCTION_END:
			/* Destruct serializer. */
			pSerializer->Release();
			delete pFactory;
			return GAIA::True;
		}
		GAIA::BL Save(const GAIA::GCH* pszFileName)
		{
			GAIA_AST(!GAIA::ALGORITHM::stremp(pszFileName));
			if(GAIA::ALGORITHM::stremp(pszFileName))
				return GAIA::False;

			/* Construct serializer. */
			GAIA::FRAMEWORK::Factory* pFactory = new GAIA::FRAMEWORK::Factory;
			GAIA::SERIALIZER::Serializer* pSerializer = 
				(GAIA::SERIALIZER::Serializer*)pFactory->CreateInstance(GAIA::FRAMEWORK::GAIA_CLSID_SERIALIZER, GNULL);
			GAIA::IO::FileIO* pFileIO = (GAIA::IO::FileIO*)pFactory->CreateInstance(GAIA::FRAMEWORK::GAIA_CLSID_FILEIO, GNULL);	
			if(!pFileIO->Open(FILE_FILELIST, GAIA::IO::IO::IO_TYPE_WRITE))
			{
				pFileIO->Release();
				pSerializer->Release();
				delete pFactory;
				return GAIA::False;
			}
			pSerializer->BindIO(pFileIO);
			pFileIO->Release();
			GAIA::SERIALIZER::Serializer& sr = *pSerializer;

			/* Write file head. */
			sr << FILE_FILELIST_FLAG;
			sr << FILE_FILELIST_VERSION;

			/* Write name map list. */
			{
				__NameMapType::_sizetype size = m_names.size();
				sr << size;
				__NameMapType::const_it it = m_names.const_front_it();
				while(!it.empty())
				{
					const __NameMapType::_datatype& d = *it;
					sr << d.m_name;
					++it;
				}
			}

			/* Write file tree. */
			{
				__FileTreeType::Node& n = m_ftree.root();
				this->SaveNode(sr, n);
			}
		FUNCTION_END:
			/* Destruct serializer. */
			pSerializer->Release();
			delete pFactory;
			return GAIA::True;
		}
		GAIA::BL Build(const GAIA::GCH* pszPathName, const GAIA::GCH* pszFilter)
		{
			GAIA::FILESYSTEM::Directory dir;
			GAIA::FILESYSTEM::Directory::__ResultTree restree;
			if(!dir.Collect(pszPathName, pszFilter, GAIA::True, restree))
				return GAIA::False;

			/* Build name list(m_names). */
			{
				m_names.clear();
				GAIA::FILESYSTEM::Directory::__ResultTree::it it = restree.front_it();
				while(!it.empty())
				{
					NameMap nm;
					nm.m_name = (*it).front_ptr();
					m_names.push_back(nm);
					++it;
				}
				m_names.sort();
			}

			/* Generate file tree(m_ftree). */
			{
				m_ftree.clear();
				GAIA::FILESYSTEM::Directory::__ResultTree::it it = restree.front_it();
				typedef GAIA::CONTAINER::Vector<TrieNode> __TempInsertVector;
				__TempInsertVector listInsert;
				FILEID id = 0;
				while(!it.empty())
				{
					if(restree.leaf(it))
					{
						listInsert.clear();
						typedef GAIA::CONTAINER::Vector<GAIA::FILESYSTEM::Directory::__ResultTree::_datatype*> __TempPartComineVector;
						__TempPartComineVector listTemp;
						GAIA::FILESYSTEM::Directory::__ResultTree::it itt = it;
						while(!itt.empty())
						{
							listTemp.push_back(&*itt);
							itt = restree.parent_it(itt);
							if(restree.root(itt))
								itt = restree.parent_it(itt);
						}
						listTemp.inverse();
						FNAMETYPE fname;
						__TempPartComineVector::it itv = listTemp.front_it();
						while(!itv.empty())
						{
							if(!fname.empty())
								fname += "/";
							fname += (*itv)->front_ptr();
							++itv;
						}
						MAP_INDEX_TYPE mit[MAX_DEPTH];
						if(this->NameToMapIndex(fname, mit))
						{
							MAP_INDEX_TYPE* pmit = mit;
							while(*pmit != 0)
							{
								TrieNode n;
								n.m_mapindex = *pmit;
								n.m_id = GINVALID;
								listInsert.push_back(n);
								++pmit;
							}
						}						
						else
							GAIA_AST(GAIA::ALWAYSFALSE);
						listInsert.back_ptr()->m_id = id++;
						m_ftree.insert(listInsert.front_ptr(), listInsert.size());
					}
					++it;
				}
			}

			/* Generate file record list. */
			{
				m_recids.clear();
				__FileTreeType::const_it it = m_ftree.const_front_it();
				while(!it.empty())
				{
					if(m_ftree.leaf(it))
					{
						const TrieNode& n = *it;
						FileRec fr;
						fr.m_id = n.m_id;
						fr.m_it = it;
						fr.m_uSequence = 0;
						m_recids.push_back(fr);
					}
					++it;
				}
				m_recids.sort();
			}

			/* Generate file state list. */
			{
				m_states.clear();
				__FileRecIDListType::_sizetype size = m_recids.size();
				for(__FileRecIDListType::_sizetype x = 0; x < size; ++x)
				{
					FileState fs;
					fs.m_chunkprogress = GINVALID;
					m_states.push_back(fs);
				}
			}

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
			GAIA::NM nIndex = m_recids.find(f);
			if(nIndex == GINVALID)
				return GAIA::False;
			MAP_INDEX_TYPE mapindex[MAX_DEPTH];
			if(!this->GenerateMapIndex(m_recids[nIndex].m_it, mapindex))
				return GAIA::False;
			return this->MapIndexToName(mapindex, pResult);
		}
		CHUNKPROGRESS GetChunkType(const FILEID& id) const
		{
			__FileRecIDListType::_datatype f;
			f.m_id = id;
			GAIA::NM nIndex = m_recids.find(f);
			if(nIndex == GINVALID)
				return (CHUNKPROGRESS)GINVALID;
			return m_states[nIndex].m_chunkprogress;
		}
	private:
		class TrieNode
		{
		public:
			GINL TrieNode& operator = (const TrieNode& src){m_mapindex = src.m_mapindex; m_id = src.m_id; return *this;}
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
		GAIA::GVOID init(){(*m_ftree.root()).m_id = GINVALID; (*m_ftree.root()).m_mapindex = GINVALID; m_LastMaxFileID = 0;}
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
				pResult[x] = n;
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
						GAIA::ALGORITHM::strcpy(sz, p);
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
				it = m_ftree.parent_it(it);
				if(m_ftree.root(it))
					it = m_ftree.parent_it(it);
			}
			GAIA::ALGORITHM::inverse(pMapIndex, p - 1);
			return GAIA::True;
		}
		GAIA::BL SaveNode(GAIA::SERIALIZER::Serializer& sr, __FileTreeType::Node& n)
		{
			/* Save node count. */
			__FileTreeType::__NodeTreeType::_sizetype childcnt = m_ftree.childsize(n);
			sr << childcnt;

			/* Save node data. */
			__FileTreeType::_datatype& data = *n;
			sr << data.m_id;
			sr << data.m_mapindex;

			/* Save child node. */
			__FileTreeType::__NodeTreeType::it it = m_ftree.child_front_it(n);
			while(!it.empty())
			{
				__FileTreeType::Node* pNode = m_ftree.tonode(it);
				this->SaveNode(sr, *pNode);
				++it;
			}
			return GAIA::False;
		}
	private:
		__NameMapType m_names; // Sorted by file name.
		__FileRecIDListType m_recids; // Sorted by file id.
		__FileStateListType m_states; // Sorted as file id list.
		__FileTreeType m_ftree; // Sorted by file name section.
		FILEID m_LastMaxFileID;
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

			/* Construct serializer. */
			GAIA::FRAMEWORK::Factory* pFactory = new GAIA::FRAMEWORK::Factory;
			GAIA::SERIALIZER::Serializer* pSerializer = 
				(GAIA::SERIALIZER::Serializer*)pFactory->CreateInstance(GAIA::FRAMEWORK::GAIA_CLSID_SERIALIZER, GNULL);
			GAIA::IO::FileIO* pFileIO = (GAIA::IO::FileIO*)pFactory->CreateInstance(GAIA::FRAMEWORK::GAIA_CLSID_FILEIO, GNULL);	
			if(!pFileIO->Open(FILE_USERGROUP, GAIA::IO::IO::IO_TYPE_READ))
			{
				pFileIO->Release();
				pSerializer->Release();
				delete pFactory;
				return GAIA::False;
			}
			pSerializer->BindIO(pFileIO);
			pFileIO->Release();
			GAIA::SERIALIZER::Serializer& sr = *pSerializer;

			/* Read file head. */
			GAIA::U32 uFlag;
			sr >> uFlag;
			if(uFlag != FILE_USERGROUP_FLAG)
				goto FUNCTION_END;
			GAIA::U32 uVersion;
			sr >> uVersion;
			if(uVersion > FILE_USERGROUP_VERSION)
				goto FUNCTION_END;

			/* Read user information. */
			__UserSetType::_sizetype user_cnt;
			sr >> user_cnt;
			for(__UserSetType::_sizetype x = 0; x < user_cnt; ++x)
			{
				__UserNameType uname;
				sr >> uname;
				__PasswordType pwd;
				sr >> pwd;
				this->AddUser(uname);
				this->SetUserPassword(uname, pwd);
			}

			/* Read group information. */
			__GroupSetType::_sizetype group_cnt;
			sr >> group_cnt;
			for(__GroupSetType::_sizetype x = 0; x < group_cnt; ++x)
			{
				__GroupNameType gname;
				sr >> gname;
				this->AddGroup(gname);
				Right right;
				sr >> right;
				this->SetGroupRightRead(gname, right.m_bRead);
				this->SetGroupRightWrite(gname, right.m_bWrite);
				Group::__UserRefListType::_sizetype user_cnt;
				sr >> user_cnt;
				for(Group::__UserRefListType::_sizetype y = 0; y < user_cnt; ++y)
				{
					__UserNameType uname;
					sr >> uname;
					this->AddGroupUser(gname, uname);
				}
			}

		FUNCTION_END:
			/* Destruct serializer */
			pSerializer->Release();
			delete pFactory;
			return GAIA::True;
		}
		GINL GAIA::BL Save(const GAIA::GCH* pszFileName)
		{
			GAIA_AST(!GAIA::ALGORITHM::stremp(pszFileName));
			if(GAIA::ALGORITHM::stremp(pszFileName))
				return GAIA::False;

			/* Construct serializer. */
			GAIA::FRAMEWORK::Factory* pFactory = new GAIA::FRAMEWORK::Factory;
			GAIA::SERIALIZER::Serializer* pSerializer = 
				(GAIA::SERIALIZER::Serializer*)pFactory->CreateInstance(GAIA::FRAMEWORK::GAIA_CLSID_SERIALIZER, GNULL);
			GAIA::IO::FileIO* pFileIO = (GAIA::IO::FileIO*)pFactory->CreateInstance(GAIA::FRAMEWORK::GAIA_CLSID_FILEIO, GNULL);	
			if(!pFileIO->Open(FILE_USERGROUP, GAIA::IO::IO::IO_TYPE_WRITE))
			{
				pFileIO->Release();
				pSerializer->Release();
				delete pFactory;
				return GAIA::False;
			}
			pSerializer->BindIO(pFileIO);
			pFileIO->Release();
			GAIA::SERIALIZER::Serializer& sr = *pSerializer;

			/* Write file flag. */
			sr << FILE_USERGROUP_FLAG;
			sr << FILE_USERGROUP_VERSION;

			/* Write user information. */
			__UserSetType::_sizetype user_cnt = m_users.size();
			sr << user_cnt;
			__UserSetType::it it_u = m_users.front_it();
			while(!it_u.empty())
			{
				User* pUser = *it_u;
				if(pUser != GNULL)
				{
					sr << pUser->m_name;
					sr << pUser->m_pwd;
				}
				++it_u;
			}

			/* Write group information. */
			__GroupSetType::_sizetype group_cnt = m_groups.size();
			sr << group_cnt;
			__GroupSetType::it it_g = m_groups.front_it();
			while(!it_g.empty())
			{
				Group* pGroup = *it_g;
				if(pGroup != GNULL)
				{
					sr << pGroup->m_name;
					sr << pGroup->m_right;
					Group::__UserRefListType::_sizetype user_cnt = pGroup->m_refusers.size();
					sr << user_cnt;
					Group::__UserRefListType::it it = pGroup->m_refusers.front_it();
					while(!it.empty())
					{
						User* pUser = *it;
						sr << pUser->m_name;
						++it;
					}
				}
				++it_g;
			}

		FUNCTION_END:
			/* Destruct serializer */
			pSerializer->Release();
			delete pFactory;
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
			User* pUser = this->FindUserInternal(name);
			if(pUser == GNULL)
				return GAIA::False;
			User::__GroupRefListType::it it = pUser->m_refgroups.front_it();
			while(!it.empty())
			{
				Group* pGroup = *it;
				if(pGroup != GNULL)
					pGroup->m_refusers.erase(pUser);
				++it;
			}
			m_users.erase(pUser);
			m_upool.release(pUser);
			return GAIA::True;
		}
		GINL GAIA::GVOID DeleteUserAll()
		{
			__GroupSetType::it it_g = m_groups.front_it();
			while(!it_g.empty())
			{
				Group* pGroup = *it_g;
				if(pGroup != GNULL)
					pGroup->m_refusers.clear();
				++it_g;
			}
			__UserSetType::it it_u = m_users.front_it();
			while(!it_u.empty())
			{
				User* pUser = *it_u;
				m_upool.release(pUser);
				++it_u;
			}
			m_users.clear();
		}
		GINL GAIA::BL FindUser(const __UserNameType& name) const
		{
			GAIA_AST(!name.empty());
			if(name.empty())
				return GAIA::False;
			const User* pUser = this->FindUserInternal(name);
			return pUser != GNULL;
		}
		GINL GAIA::BL AddGroup(const __GroupNameType& name)
		{
			GAIA_AST(!name.empty());
			if(name.empty())
				return GAIA::False;
			if(this->FindGroup(name))
				return GAIA::False;
			Group* pGroup = m_gpool.alloc();
			pGroup->m_name = name;
			m_groups.insert(pGroup);
			return GAIA::True;
		}
		GINL GAIA::BL DeleteGroup(const __GroupNameType& name)
		{
			GAIA_AST(!name.empty());
			if(name.empty())
				return GAIA::False;
			Group* pGroup = this->FindGroupInternal(name);
			if(pGroup == GNULL)
				return GAIA::False;
			Group::__UserRefListType::it it = pGroup->m_refusers.front_it();
			while(!it.empty())
			{
				User* pUser = *it;
				if(pUser != GNULL)
				{
					User::__GroupRefListType::it itu = pUser->m_refgroups.front_it();
					while(!itu.empty())
					{
						if(*itu != GNULL && *itu == pGroup)
						{
							*itu = GNULL;
							break;
						}
						++itu;
					}
				}
				++it;
			}
			return GAIA::True;
		}
		GINL GAIA::GVOID DeleteGroupAll()
		{
			__GroupSetType::it it = m_groups.front_it();
			while(!it.empty())
			{
				Group* pGroup = *it;
				if(pGroup != GNULL)
					m_gpool.release(pGroup);
				++it;
			}
		}
		GINL GAIA::BL FindGroup(const __GroupNameType& name) const
		{
			GAIA_AST(!name.empty());
			if(name.empty())
				return GAIA::False;
			const Group* pGroup = this->FindGroupInternal(name);
			return pGroup != GNULL;
		}
		GINL GAIA::BL SetGroupRightRead(const __GroupNameType& name, GAIA::BL bRead)
		{
			GAIA_AST(!name.empty());
			if(name.empty())
				return GAIA::False;
			Group* pGroup = this->FindGroupInternal(name);
			if(pGroup == GNULL)
				return GAIA::False;
			pGroup->m_right.m_bRead = bRead;
			return GAIA::True;
		}
		GINL GAIA::BL GetGroupRightRead(const __GroupNameType& name, GAIA::BL& bRead)
		{
			GAIA_AST(!name.empty());
			if(name.empty())
				return GAIA::False;
			Group* pGroup = this->FindGroupInternal(name);
			if(pGroup == GNULL)
				return GAIA::False;
			bRead = pGroup->m_right.m_bRead;
			return GAIA::True;
		}
		GINL GAIA::BL SetGroupRightWrite(const __GroupNameType& name, GAIA::BL bWrite)
		{
			GAIA_AST(!name.empty());
			if(name.empty())
				return GAIA::False;
			Group* pGroup = this->FindGroupInternal(name);
			if(pGroup == GNULL)
				return GAIA::False;
			pGroup->m_right.m_bWrite = bWrite;
			return GAIA::True;
		}
		GINL GAIA::BL GetGroupRightWrite(const __GroupNameType& name, GAIA::BL& bWrite)
		{
			GAIA_AST(!name.empty());
			if(name.empty())
				return GAIA::False;
			Group* pGroup = this->FindGroupInternal(name);
			if(pGroup == GNULL)
				return GAIA::False;
			bWrite = pGroup->m_right.m_bWrite;
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
			Group* pGroup = this->FindGroupInternal(gname);
			if(pGroup == GNULL)
				return GAIA::False;
			User* pUser = this->FindUserInternal(uname);
			if(pUser == GNULL)
				return GAIA::False;
			Group::__UserRefListType::_datatype* pFinded = pGroup->m_refusers.find(pUser);
			if(pFinded != GNULL)
				return GAIA::False;
			pGroup->m_refusers.insert(pUser);
			GAIA::NM nFreePos = pUser->m_refgroups.find(GNULL);
			if(nFreePos == GINVALID)
				pUser->m_refgroups.push_back(pGroup);
			else
				pUser->m_refgroups[nFreePos] = pGroup;
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
			Group* pGroup = this->FindGroupInternal(gname);
			if(pGroup == GNULL)
				return GAIA::False;
			User* pUser = this->FindUserInternal(uname);
			if(pUser == GNULL)
				return GAIA::False;
			User::__GroupRefListType::it itg = pUser->m_refgroups.front_it();
			if(!itg.empty())
			{
				Group* pGroupTemp = *itg;
				if(pGroupTemp == pGroup)
					*itg = GNULL;
				++itg;
			}
			pGroup->m_refusers.erase(pUser);
			return GAIA::True;
		}
		GINL GAIA::BL DeleteGroupUserAll(const __GroupNameType& name)
		{
			Group* pGroup = this->FindGroupInternal(name);
			if(pGroup == GNULL)
				return GAIA::False;
			Group::__UserRefListType::it it = pGroup->m_refusers.front_it();
			while(!it.empty())
			{
				User* pUser = *it;
				User::__GroupRefListType::it itg = pUser->m_refgroups.front_it();
				if(!itg.empty())
				{
					Group* pGroupTemp = *itg;
					if(pGroupTemp == pGroup)
						*itg = GNULL;
					++itg;
				}
				++it;
			}
			pGroup->m_refusers.clear();
			return GAIA::True;
		}
		GINL GAIA::GVOID EnumUser(__UserNameListType& result) const
		{
			__UserSetType::const_it it = m_users.const_front_it();
			while(!it.empty())
			{
				const User* pUser = *it;
				result.push_back(pUser->m_name);
				++it;
			}
		}
		GINL GAIA::GVOID EnumGroup(__GroupNameListType& result) const
		{
			__GroupSetType::const_it it = m_groups.const_front_it();
			while(!it.empty())
			{
				const Group* pGroup = *it;
				result.push_back(pGroup->m_name);
				++it;
			}
		}
		GINL GAIA::BL EnumUserGroup(const __UserNameType& name, __GroupNameListType& result) const
		{
			GAIA_AST(!name.empty());
			if(name.empty())
				return GAIA::False;
			const User* pUser = this->FindUserInternal(name);
			if(pUser == GNULL)
				return GAIA::False;
			User::__GroupRefListType::const_it it = pUser->m_refgroups.const_front_it();
			while(!it.empty())
			{
				const Group* pGroup = *it;
				if(pGroup != GNULL)
					result.push_back(pGroup->m_name);
				++it;
			}
			return GAIA::True;
		}
		GINL GAIA::BL EnumGroupUser(const __GroupNameType& name, __UserNameListType& result) const
		{
			GAIA_AST(!name.empty());
			if(name.empty())
				return GAIA::False;
			const Group* pGroup = this->FindGroupInternal(name);
			if(pGroup == GNULL)
				return GAIA::False;
			Group::__UserRefListType::const_it it = pGroup->m_refusers.const_front_it();
			while(!it.empty())
			{
				const User* pUser = *it;
				if(pUser != GNULL)
					result.push_back(pUser->m_name);
				++it;
			}
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
		GINL const Group* FindGroupInternal(const __GroupNameType& name) const
		{
			Group finder;
			finder.m_name = name;
			const __GroupSetType::_datatype* pFinded = m_groups.find(&finder);
			if(pFinded == GNULL)
				return GNULL;
			return *pFinded;
		}
		GINL Group* FindGroupInternal(const __GroupNameType& name)
		{
			Group finder;
			finder.m_name = name;
			__GroupSetType::_datatype* pFinded = m_groups.find(&finder);
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
			m_usergroup.Load(FILE_USERGROUP);
			m_filelist.Load(FILE_FILELIST);
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
			// Command analyze.
			GAIA_AST(!GAIA::ALGORITHM::stremp(pszCmd));
			if(GAIA::ALGORITHM::stremp(pszCmd))
				return GAIA::False;
			GAIA::CONTAINER::AString strCmd = pszCmd;
			GAIA::CONTAINER::Vector<GAIA::CONTAINER::AString> listPart;
			GAIA::CONTAINER::AString::_sizetype index;
			while((index = strCmd.find(' ', GINVALID)) != GINVALID)
			{
				GAIA::CONTAINER::AString strTemp = strCmd;
				strTemp.left(index);
				listPart.push_back(strTemp);
				strCmd.right(index);
			}
			if(!strCmd.empty())
				listPart.push_back(strCmd);
			strCmd.clear();

			// Execute command.
			static const GAIA::GCH* COMMAND_LIST[] = 
			{
				"Invalid",				"Invalid.",
				"h",					"show help information.",
				"save",					"save config change.",
				"build",				"build the path and generate file list, format = file_path file_ext_list.",
				"create_user",			"create a new user, format = create_user user_name.",
				"delete_user",			"delete a exist user, format = delete_user user_name.",
				"delete_all_user",		"delete all exist users.",
				"password",				"set/get user's password. format = password user_name password | password user_name.",
				"create_group",			"create a new group, format = create_group group name.",
				"delete_group",			"delete a exist group, format = delete_group group_name.",
				"delete_all_group",		"delete all exist groups.",
				"right",				"set group right, format = group_name isread iswrite.",
				"add_group_user",		"add a user to group, format = group_name user_name.",
				"delete_group_user",	"delete exist user from group, format = group_name user_name.",
				"delete_group_alluser",	"delete all exist users from group, format = group_name.",
				"show_users",			"show all users",
				"show_user",			"show user's information, format = show_user user_name.",
				"show_groups",			"show all groups",
				"show_group",			"show group's information, format = show_group group_name.",
			};
			GAIA_ENUM_BEGIN(COMMAND_LIST)
				CMD_HELP,
				CMD_SAVE,
				CMD_BUILD,
				CMD_CREATEUSER,
				CMD_DELETEUSER,
				CMD_DELETEALLUSER,
				CMD_PASSWORD,
				CMD_CREATEGROUP,
				CMD_DELETEGROUP,
				CMD_DELETEALLGROUP,
				CMD_RIGHT,
				CMD_ADDGROUPUSER,
				CMD_DELETEGROUPUSER,
				CMD_DELETEALLGROUPUSER,
				CMD_SHOWUSERS,
				CMD_SHOWUSER,
				CMD_SHOWGROUPS,
				CMD_SHOWGROUP,
			GAIA_ENUM_END(COMMAND_LIST)
			#define CMD(e) (listPart[0] == COMMAND_LIST[e * 2])
			#define CMDFAILED do{m_prt << "Failed!\n";}while(GAIA::ALWAYSFALSE)
			if(listPart.empty())
				return GAIA::False;
			if(CMD(CMD_HELP))
			{
				for(GAIA::N32 x = 0; x < sizeof(COMMAND_LIST) / sizeof(const GAIA::GCH*) / 2; ++x)
					m_prt << "[" << x << "] " << COMMAND_LIST[x * 2] << " Info:" << COMMAND_LIST[x * 2 + 1] << "\n";
			}
			else if(CMD(CMD_SAVE))
			{
				if(listPart.size() == 1)
				{
					if(!m_filelist.Save(FILE_FILELIST))
						CMDFAILED;
					if(!m_usergroup.Save(FILE_USERGROUP))
						CMDFAILED;
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_BUILD))
			{
				if(listPart.size() == 3)
				{
					if(!m_filelist.Build(listPart[1].front_ptr(), listPart[2].front_ptr()))
						CMDFAILED;
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_CREATEUSER))
			{
				if(listPart.size() == 2)
				{
					if(!m_usergroup.AddUser(listPart[1].front_ptr()))
						CMDFAILED;
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_DELETEUSER))
			{
				if(listPart.size() == 2)
				{
					if(!m_usergroup.DeleteUser(listPart[1].front_ptr()))
						CMDFAILED;
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_DELETEALLUSER))
			{
				if(listPart.size() == 1)
					m_usergroup.DeleteUserAll();
				else
					CMDFAILED;
			}
			else if(CMD(CMD_PASSWORD))
			{
				if(listPart.size() == 3)
				{
					if(!m_usergroup.SetUserPassword(listPart[1].front_ptr(), listPart[2].front_ptr()))
						CMDFAILED;
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_CREATEGROUP))
			{
				if(listPart.size() == 2)
				{
					if(!m_usergroup.AddGroup(listPart[1].front_ptr()))
						CMDFAILED;
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_DELETEGROUP))
			{
				if(listPart.size() == 2)
				{
					if(!m_usergroup.DeleteGroup(listPart[1].front_ptr()))
						CMDFAILED;
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_DELETEALLGROUP))
			{
				if(listPart.size() == 1)
					m_usergroup.DeleteGroupAll();
				else
					CMDFAILED;
			}
			else if(CMD(CMD_RIGHT))
			{
				if(listPart.size() == 4)
				{
					if(!m_usergroup.SetGroupRightWrite(listPart[1].front_ptr(), (GAIA::BL)listPart[2].front_ptr()))
						CMDFAILED;
					else
					{
						if(!m_usergroup.SetGroupRightRead(listPart[1].front_ptr(), (GAIA::BL)listPart[3].front_ptr()))
							CMDFAILED;
					}
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_ADDGROUPUSER))
			{
				if(listPart.size() == 3)
				{
					if(!m_usergroup.AddGroupUser(listPart[1].front_ptr(), listPart[2].front_ptr()))
						CMDFAILED;
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_DELETEGROUPUSER))
			{
				if(listPart.size() == 3)
				{
					if(!m_usergroup.DeleteGroupUser(listPart[1].front_ptr(), listPart[2].front_ptr()))
						CMDFAILED;
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_DELETEALLGROUPUSER))
			{
				if(listPart.size() == 2)
				{
					if(!m_usergroup.DeleteGroupUserAll(listPart[1].front_ptr()))
						CMDFAILED;
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_SHOWUSERS))
			{
				if(listPart.size() == 1)
				{
					UserGroup::__UserNameListType listUser;
					m_usergroup.EnumUser(listUser);
					UserGroup::__UserNameListType::const_it it = listUser.const_front_it();
					GAIA::N32 nIndex = 0;
					while(!it.empty())
					{
						m_prt << "[" << nIndex++ << "] " << (*it).front_ptr() << "\n";
						++it;
					}
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_SHOWUSER))
			{
				if(listPart.size() == 2)
				{
					const GAIA::GCH* pszPassword = m_usergroup.GetUserPassword(listPart[1].front_ptr());
					if(pszPassword == GNULL)
						CMDFAILED;
					m_prt << "Password = " << pszPassword << "\n";

					UserGroup::__GroupNameListType listGroup;
					m_usergroup.EnumUserGroup(listPart[1].front_ptr(), listGroup);
					UserGroup::__UserNameListType::const_it it = listGroup.const_front_it();
					GAIA::N32 nIndex = 0;
					while(!it.empty())
					{
						m_prt << "[" << nIndex++ << "] " << (*it).front_ptr() << "\n";
						++it;
					}
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_SHOWGROUPS))
			{
				if(listPart.size() == 1)
				{
					UserGroup::__GroupNameListType listGroup;
					m_usergroup.EnumGroup(listGroup);
					UserGroup::__UserNameListType::const_it it = listGroup.const_front_it();
					GAIA::N32 nIndex = 0;
					while(!it.empty())
					{
						m_prt << "[" << nIndex++ << "] " << (*it).front_ptr() << "\n";
						++it;
					}
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_SHOWGROUP))
			{
				if(listPart.size() == 2)
				{
					if(m_usergroup.FindGroup(listPart[1].front_ptr()))
					{
						GAIA::BL bWrite;
						GAIA::BL bRead;
						m_usergroup.GetGroupRightWrite(listPart[1].front_ptr(), bWrite);
						m_usergroup.GetGroupRightRead(listPart[1].front_ptr(), bRead);
						m_prt << "Right = " << bWrite << ", Read = " << bRead << "\n";

						UserGroup::__UserNameListType listUser;
						m_usergroup.EnumGroupUser(listPart[1].front_ptr(), listUser);
						UserGroup::__UserNameListType::const_it it = listUser.const_front_it();
						GAIA::N32 nIndex = 0;
						while(!it.empty())
						{
							m_prt << "[" << nIndex++ << "] " << (*it).front_ptr() << "\n";
							++it;
						}
					}
					else
						CMDFAILED;
				}
				else
					CMDFAILED;
			}
			else
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
		FileList m_filelist;
		UserGroup m_usergroup;
		GAIA::PRINT::Print m_prt;
	};
};

#endif
