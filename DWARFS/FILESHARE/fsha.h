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

#if GAIA_OS == GAIA_OS_WINDOWS
#	pragma comment(lib, "ws2_32.lib")
#endif

namespace FSHA
{
	/* Constants. */
	static const GAIA::GCH VERSION_STRING[] = "00.00.01.00";
	static const GAIA::U32 VERSION = 0x00000100;
	static const GAIA::NM MAX_DEPTH = 18;
	static const GAIA::NM MAX_PATHLEN = 240;
	static const GAIA::U16 MAINRECVPORT = 7121;
	static const GAIA::U16 DEFAULT_SEND_THREAD_COUNT = 4;
	static const GAIA::U32 CHUNKSIZE = 100 * 1024;
	static const GAIA::UM THREAD_STACK_SIZE = 1024 * 128;
	static const GAIA::NM USERNAMELEN = 16;
	static const GAIA::NM PASSWORDLEN = 16;
	static const GAIA::NM GROUPNAMELEN = 16;
	static const GAIA::GCH FILE_USERGROUP[] = "usergroup";
	static const GAIA::U32 FILE_USERGROUP_FLAG = 'FSUG';
	static const GAIA::U32 FILE_USERGROUP_VERSION = 0;
	static const GAIA::GCH FILE_FILELIST[] = "filelist";
	static const GAIA::U32 FILE_FILELIST_FLAG = 'FSFL';
	static const GAIA::U32 FILE_FILELIST_VERSION = 0;

	/* Type declaration. */
	typedef GAIA::U32 FILEID; // GINVALID means invalid id.
	typedef GAIA::CONTAINER::BasicString<GAIA::GCH, GAIA::U8> FSTR;
	typedef GAIA::CONTAINER::Vector<FSTR> FSTRLIST;
	typedef GAIA::CONTAINER::BasicAVLTree<
			FSTR, GAIA::N32, GAIA::N32, 
			GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32> > FSTRBTR; 
	typedef GAIA::U32 MAP_INDEX_TYPE; // 0 means invalid id.
	typedef GAIA::CONTAINER::BasicChars<GAIA::GCH, GAIA::N16, MAX_PATHLEN> FNAMETYPE;
	typedef GAIA::CONTAINER::Array<FNAMETYPE, MAX_DEPTH> FNAMEPARTLISTTYPE;

	/* File sequence. */
	class __DWARFS_FILESHARE_API FileSequence
	{
	public:
		FileSequence(){}
		~FileSequence(){}
		GINL GAIA::BL Add(const GAIA::GCH* pszFileName)
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
		GINL GAIA::BL DeleteAll()
		{
			m_files.destroy();
			m_filesbtr.destroy();
			return GAIA::True;
		}
		GINL const GAIA::NM& GetRecCount() const{return m_files.size();}
		GINL const GAIA::GCH* GetRec(const GAIA::NM& index){if(index >= this->GetRecCount()) return GNULL; return m_files[index];}
	private:
		FSTRLIST m_files;
		FSTRBTR m_filesbtr;
	};

	/* File list class. */
	class __DWARFS_FILESHARE_API FileList
	{
	#define FILE_LIST_LOG(msg) do{if(m_pPr != GNULL){*m_pPr << (msg) << "\n";}}while(GAIA::ALWAYSFALSE)
	#define FILE_LIST_LOG2(msg1, msg2) do{if(m_pPr != GNULL){*m_pPr << (msg1) << (msg2) << "\n";}}while(GAIA::ALWAYSFALSE)
	#define FILE_LIST_LOG3(msg1, msg2, msg3) do{if(m_pPr != GNULL){*m_pPr << (msg1) << (msg2) << (msg3) << "\n";}}while(GAIA::ALWAYSFALSE)
	public:
		GINL FileList(){this->init();}
		GINL ~FileList(){}
		GINL GAIA::GVOID SetPrint(GAIA::PRINT::Print* pPr){m_pPr = pPr;}
		GINL GAIA::PRINT::Print* GetPrint() const{return m_pPr;}
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
				m_names.clear();
				__NameMapType::_sizetype size;
				sr >> size;
				m_names.reserve(size);
				for(__NameMapType::_sizetype x = 0; x < size; ++x)
				{
					__NameMapType::_datatype d;
					sr >> d.m_name;
					m_names.push_back(d);
				}
			}

			/* Read file tree. */
			{
				m_ftree.clear();
				m_recids.clear();
				GAIA::CONTAINER::Stack<TrieNode> stack;
				this->LoadNode(sr, stack);
				m_recids.sort();
				__FileTreeType::const_it it = m_ftree.const_front_it();
				while(!it.empty())
				{
					if(m_ftree.leaf(it))
					{
						const TrieNode& n = *it;
						FileRec fr;
						fr.m_id = n.m_id;
						GAIA::NM nFinded = m_recids.search(fr);
						GAIA_AST(nFinded != GINVALID);
						m_recids[nFinded].m_it = it;
					}
					++it;
				}
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
			FILE_LIST_LOG("Save file name's string token list...");
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
			FILE_LIST_LOG("Save file trie tree...");
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
			FILE_LIST_LOG("Collision destination path files...");
			GAIA::FILESYSTEM::Directory::__ResultTree restree;
			{
				GAIA::FILESYSTEM::Directory dir;
				if(!dir.Collect(pszPathName, pszFilter, GAIA::True, restree))
					return GAIA::False;
			}
			FILE_LIST_LOG3("There are ", restree.catagory_count(restree.root()), " files collected!");

			/* Build name list(m_names). */
			FNAMEPARTLISTTYPE listNamePart;
			this->GenerateFileNamePartList(pszPathName, listNamePart);
			FILE_LIST_LOG("Build file name's string token list...");
			{
				m_names.clear();
				m_names.reserve(restree.catagory_count(restree.root()));
				GAIA::FILESYSTEM::Directory::__ResultTree::it it = restree.front_it();
				FNAMEPARTLISTTYPE::_sizetype nRootPart = listNamePart.size();
				while(!it.empty())
				{
					if(nRootPart == 0)
					{
						NameMap nm;
						m_names.push_back(nm);
						m_names.back_ptr()->m_name = (*it).front_ptr();
						m_names.back_ptr()->m_name.tolower();
					}
					else
						--nRootPart;
					++it;
				}
				m_names.sort();
			}

			/* Generate file tree(m_ftree). */
			FILE_LIST_LOG("Generate file trie tree...");
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
						GAIA_AST(listTemp.size() > listNamePart.size());
						listTemp.resize(listTemp.size() - listNamePart.size());
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
						fname.tolower();
						MAP_INDEX_TYPE mit[MAX_DEPTH];
						if(this->NameToMapIndex(fname, mit))
						{
							MAP_INDEX_TYPE* pmit = mit;
							while(*pmit != GINVALID)
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
			FILE_LIST_LOG("Generate file record list...");
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

			return GAIA::True;
		}
		const FILEID* GetIDByName(const GAIA::GCH* pszFileName)
		{
			GAIA_AST(!GAIA::ALGORITHM::stremp(pszFileName));
			if(GAIA::ALGORITHM::stremp(pszFileName))
				return GNULL;
			GAIA::GCH szLower[MAX_PATHLEN];
			GAIA::ALGORITHM::strcpy(szLower, pszFileName);
			GAIA::ALGORITHM::tolower(szLower);
			MAP_INDEX_TYPE mapindex[MAX_DEPTH];
			if(!this->NameToMapIndex(szLower, mapindex))
				return GNULL;
			TrieNode tnlist[MAX_DEPTH];
			MAP_INDEX_TYPE* p = mapindex;
			for(;;)
			{
				if(*p == GINVALID)
					break;
				TrieNode& tn = tnlist[p - mapindex];
				tn.m_mapindex = *p;
				++p;
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
			GAIA::NM nIndex = m_recids.search(f);
			if(nIndex == GINVALID)
				return GAIA::False;
			MAP_INDEX_TYPE mapindex[MAX_DEPTH];
			if(!this->GenerateMapIndex(m_recids[nIndex].m_it, mapindex))
				return GAIA::False;
			return this->MapIndexToName(mapindex, pResult);
		}
		GAIA::UM GetFileCount() const{return m_recids.size();}
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
		typedef GAIA::CONTAINER::BasicTrieTree<TrieNode, GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32> > __FileTreeType;
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
			GINL FileRec& operator = (const FileRec& src)
			{
				m_id = src.m_id;
				m_it = src.m_it;
				m_uSequence = src.m_uSequence;
				return *this;
			}
			GAIA_CLASS_OPERATOR_COMPARE(m_id, m_id, FileRec);
			FILEID m_id;
			__FileTreeType::const_it m_it;
			FILEID m_uSequence;
		};
	public:
		typedef GAIA::CONTAINER::Vector<NameMap> __NameMapType;
		typedef GAIA::CONTAINER::Vector<FileRec> __FileRecIDListType;
	private:
		GINL GAIA::GVOID init(){(*m_ftree.root()).m_id = GINVALID; (*m_ftree.root()).m_mapindex = GINVALID; m_LastMaxFileID = 0; m_pPr = GNULL;}
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
			GAIA_AST(namelist.size() < MAX_DEPTH);
			for(FNAMEPARTLISTTYPE::_sizetype x = 0; x < namelist.size(); ++x)
			{
				f.m_name = namelist[x].front_ptr();
				GAIA::N32 n = m_names.search(f);
				if(n == GINVALID)
					return GAIA::False;
				pResult[x] = n;
			}
			pResult[namelist.size()] = GINVALID;
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
			while(*p != GINVALID)
			{
				if(pDst != pszFileName)
					*pDst++ = '/';
				GAIA::ALGORITHM::strcpy(pDst, m_names[*p].m_name.front_ptr());
				pDst += m_names[*p].m_name.size();
				++p;
			}
			*pDst++ = 0;
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
			pMapIndex[p - pMapIndex] = GINVALID;
			return GAIA::True;
		}
		GAIA::BL LoadNode(GAIA::SERIALIZER::Serializer& sr, GAIA::CONTAINER::Stack<TrieNode>& stack)
		{
			/* Load node data. */
			TrieNode tn;
			sr >> tn.m_id;
			sr >> tn.m_mapindex;
			FileRec fr;
			sr >> fr.m_uSequence;
			fr.m_id = tn.m_id;
			stack.push(tn);

			/* Load node count. */
			__FileTreeType::__NodeTreeType::_sizetype childcnt;
			sr >> childcnt;

			/* Insert. */
			if(childcnt == 0)
			{
				if(stack.size() > 1)
				{
					GAIA_AST(stack.top().m_id != GINVALID);
					m_ftree.insert(stack.front_ptr() + 1, stack.size() - 1);
					m_recids.push_back(fr);
				}
			}

			/* Load child node. */
			for(__FileTreeType::__NodeTreeType::_sizetype x = 0; x < childcnt; ++x)
				this->LoadNode(sr, stack);
			stack.pop();

			return GAIA::True;
		}
		GAIA::BL SaveNode(GAIA::SERIALIZER::Serializer& sr, __FileTreeType::Node& n)
		{
			/* Save node data. */
			__FileTreeType::_datatype& data = *n;
			sr << data.m_id;
			sr << data.m_mapindex;
			FileRec fr;
			fr.m_id = data.m_id;
			__FileRecIDListType::_sizetype findedindex = m_recids.search(fr);
			if(findedindex != GINVALID)
				sr << m_recids[findedindex].m_uSequence;
			else
			{
				FILEID uSequence = GINVALID;
				sr << uSequence;
			}

			/* Save node count. */
			__FileTreeType::__NodeTreeType::_sizetype childcnt = m_ftree.childsize(n);
			sr << childcnt;

			/* Save child node. */
			__FileTreeType::__NodeTreeType::it it = m_ftree.child_front_it(n);
			while(!it.empty())
			{
				__FileTreeType::Node* pNode = m_ftree.tonode(it);
				this->SaveNode(sr, *pNode);
				++it;
			}
			return GAIA::True;
		}
	private:
		__NameMapType m_names; // Sorted by file name.
		__FileRecIDListType m_recids; // Sorted by file id.
		__FileTreeType m_ftree; // Sorted by file name section.
		FILEID m_LastMaxFileID;
		GAIA::PRINT::Print* m_pPr;
	};

	/* User group class. */
	class __DWARFS_FILESHARE_API UserGroup
	{
	public:
		typedef GAIA::CONTAINER::BasicChars<GAIA::GCH, GAIA::U8, USERNAMELEN> __UserNameType;
		typedef GAIA::CONTAINER::BasicChars<GAIA::GCH, GAIA::U8, PASSWORDLEN> __PasswordType;
		typedef GAIA::CONTAINER::BasicChars<GAIA::GCH, GAIA::U8, GROUPNAMELEN> __GroupNameType;
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
			typedef GAIA::CONTAINER::Set<GAIA::CONTAINER::Ref<User> > __UserRefListType;
		public:
			GAIA_CLASS_OPERATOR_COMPARE(m_name, m_name, Group);
			__GroupNameType m_name;
			__UserRefListType m_refusers;
			Right m_right;
		};
	private:
		typedef GAIA::CONTAINER::Set<GAIA::CONTAINER::Ref<User> > __UserSetType;
		typedef GAIA::CONTAINER::Set<GAIA::CONTAINER::Ref<Group> > __GroupSetType;
		typedef GAIA::CONTAINER::Pool<User> __UserPoolType;
		typedef GAIA::CONTAINER::Pool<Group> __GroupPoolType;
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
		/* File access. */
		class __DWARFS_FILESHARE_API FileAccess
		{
		public:
			virtual GAIA::BL Open(const GAIA::GCH* pszFileName, GAIA::BL bReadOnly) = 0;
			virtual GAIA::BL Close() = 0;
			virtual GAIA::BL IsOpen() const = 0;
			virtual GAIA::NM Read(GAIA::GVOID* p, GAIA::NM nSize) = 0;
			virtual GAIA::NM Write(const GAIA::GVOID* p, GAIA::NM nSize) = 0;
			virtual GAIA::BL Seek(GAIA::SEEK_TYPE st, GAIA::NM offset) = 0;
			virtual GAIA::NM Tell() const = 0;
		};
		/* Default file access. */
		class __DWARFS_FILESHARE_API DefaultFileAccess : public FileAccess
		{
		public:
			virtual GAIA::BL Open(const GAIA::GCH* pszFileName, GAIA::BL bReadOnly)
			{
				if(bReadOnly)
					return m_file.Open(pszFileName, GAIA::FILESYSTEM::FILE_OPEN_TYPE_READ);
				else
					return m_file.Open(pszFileName, GAIA::FILESYSTEM::FILE_OPEN_TYPE_CREATEALWAYS | GAIA::FILESYSTEM::FILE_OPEN_TYPE_WRITE);
			}
			virtual GAIA::BL Close(){return m_file.Close();}
			virtual GAIA::BL IsOpen() const{return m_file.IsOpen();}
			virtual GAIA::NM Read(GAIA::GVOID* p, GAIA::NM nSize){return m_file.Read(p, nSize);}
			virtual GAIA::NM Write(const GAIA::GVOID* p, GAIA::NM nSize){return m_file.Write(p, nSize);}
			virtual GAIA::BL Seek(GAIA::SEEK_TYPE st, GAIA::NM offset){return m_file.Seek(st, offset);}
			virtual GAIA::NM Tell() const{return m_file.Tell();}
		private:
			GAIA::FILESYSTEM::File m_file;
		};
		/* File share desc. */
		class __DWARFS_FILESHARE_API FileShareDesc
		{
		public:
			GINL FileShareDesc()
			{
				m_sendthreadcnt = DEFAULT_SEND_THREAD_COUNT;
				m_selfaddr.ip.FromString("127.0.0.1");
				m_selfaddr.uPort = MAINRECVPORT;
				m_pFA = &m_defaultfa;
			}
			GINL FileShareDesc& operator = (const FileShareDesc& src)
			{
				m_sendthreadcnt = src.m_sendthreadcnt;
				m_selfaddr = src.m_selfaddr;
				return *this;
			}
			GAIA::U16 m_sendthreadcnt;
			GAIA::NETWORK::NetworkAddress m_selfaddr;
			FileAccess* m_pFA;
		private:
			DefaultFileAccess m_defaultfa;
		};
		/* Network handle. */
		class __DWARFS_FILESHARE_API NHandle : public GAIA::NETWORK::NetworkHandle
		{
		public:
			GINL NHandle(){m_pFS = GNULL;}
			GINL GAIA::GVOID SetFileShare(FileShare* pFS){m_pFS = pFS;}
			GINL FileShare* GetFileShare() const{return m_pFS;}
			GINL virtual GAIA::GVOID LostConnection(GAIA::BL bRecvTrueSendFalse)
			{
			}
		private:
			FileShare* m_pFS;
		};
		/* Network listen accept callback. */
		class __DWARFS_FILESHARE_API NAcceptCallBack : public GAIA::NETWORK::NetworkListener::AcceptCallBack
		{
		public:
			GINL NAcceptCallBack(){m_pFS = GNULL;}
			GINL GAIA::GVOID SetFileShare(FileShare* pFS){m_pFS = pFS;}
			GINL FileShare* GetFileShare() const{return m_pFS;}
			virtual GAIA::NETWORK::NetworkHandle* CreateNetworkHandle(){return new NHandle;}
		private:
			FileShare* m_pFS;
		};
		/* Network listener. */
		class __DWARFS_FILESHARE_API NListener : public GAIA::NETWORK::NetworkListener
		{
		public:
			GINL NListener(){m_pFS = GNULL;}
			GINL GAIA::GVOID SetFileShare(FileShare* pFS){m_pFS = pFS;}
			GINL FileShare* GetFileShare() const{return m_pFS;}
			virtual GAIA::BL Accept(GAIA::NETWORK::NetworkHandle& h)
			{
				NHandle* pNHandle = (NHandle*)&h;
				pNHandle->SetFileShare(this->GetFileShare());
				return GAIA::True;
			}
		private:
			FileShare* m_pFS;
		};
		/* Network receiver. */
		class __DWARFS_FILESHARE_API NReceiver : public GAIA::NETWORK::NetworkReceiver
		{
		public:
			GINL NReceiver(){m_pFS = GNULL;}
			GINL GAIA::GVOID SetFileShare(FileShare* pFS){m_pFS = pFS;}
			GINL FileShare* GetFileShare() const{return m_pFS;}
			virtual GAIA::BL Receive(GAIA::NETWORK::NetworkHandle& s, const GAIA::U8* p, GAIA::U32 size)
			{
				return m_pFS->OnReceive(*(NHandle*)&s, p, size);
			}
		private:
			FileShare* m_pFS;
		};
		/* Network sender. */
		class __DWARFS_FILESHARE_API NSender : public GAIA::NETWORK::NetworkSender
		{
		public:
			GINL NSender(){m_pFS = GNULL;}
			GINL GAIA::GVOID SetFileShare(FileShare* pFS){m_pFS = pFS;}
			GINL FileShare* GetFileShare() const{return m_pFS;}
		private:
			FileShare* m_pFS;
		};
		/* Main work thread. */
		class __DWARFS_FILESHARE_API MainWorkThread : public GAIA::THREAD::Thread
		{
		public:
			GINL MainWorkThread(){m_pFS = GNULL; m_bExitCmd = GAIA::False;}
			GINL GAIA::GVOID SetFileShare(FileShare* pFS){m_pFS = pFS;}
			GINL FileShare* GetFileShare() const{return m_pFS;}
			virtual GAIA::GVOID WorkProcedure()
			{
				for(;;)
				{
					if(m_bExitCmd)
						break;
					GAIA::BL bExecuted = GAIA::False;
					if(!bExecuted)
						GAIA::SYNC::sleep(1);
				}
			}
			GINL GAIA::GVOID SetExitCmd(GAIA::BL bExitCmd){m_bExitCmd = bExitCmd;}
		private:
			FileShare* m_pFS;
			GAIA::BL m_bExitCmd;
		};
		/* Heart tick thread. */
		class __DWARFS_FILESHARE_API HeartTickThread : public GAIA::THREAD::Thread
		{
		public:
			GINL HeartTickThread(){m_pFS = GNULL; m_bExitCmd = GAIA::False;}
			GINL GAIA::GVOID SetFileShare(FileShare* pFS){m_pFS = pFS;}
			GINL FileShare* GetFileShare() const{return m_pFS;}
			virtual GAIA::GVOID WorkProcedure()
			{
				for(;;)
				{
					if(m_bExitCmd)
						break;
					GAIA::BL bExecuted = GAIA::False;
					if(!bExecuted)
						GAIA::SYNC::sleep(1);
				}
			}
			GINL GAIA::GVOID SetExitCmd(GAIA::BL bExitCmd){m_bExitCmd = bExitCmd;}
		private:
			FileShare* m_pFS;
			GAIA::BL m_bExitCmd;
		};
		/* File id section. */
		class __DWARFS_FILESHARE_API FileIDSection
		{
		public:
			GAIA_CLASS_OPERATOR_COMPARE(uStart, uStart, FileIDSection);
		public:
			FILEID uStart;
			FILEID uEnd;
		};
		/* Link object. */
		class __DWARFS_FILESHARE_API NLink
		{
		public:
			GAIA_ENUM_BEGIN(STATE)
				STATE_DISCONNECT,	// after socket create. in this state only login message can been send to other node.
				STATE_READY,		// after user password check up successfully.
				STATE_ONLINE,		// after logout. in this state only login message can been send to other node.
			GAIA_ENUM_END(STATE)
		public:
			NLink()
			{
				na.Invalid();
				state = STATE_INVALID;
				uCmplFileCnt = 0;
				pCmplFiles = GNULL;
				bBeLink = GAIA::False;
			}
			GAIA_CLASS_OPERATOR_COMPARE2(na, na, bBeLink, bBeLink, NLink);
		public:
			GAIA::NETWORK::NetworkAddress na;
			STATE state;
			FILEID uCmplFileCnt;
			GAIA::CONTAINER::Set<FileIDSection>* pCmplFiles;
			GAIA::U8 bBeLink : 1;
		};
		/* Link priority object. */
		class __DWARFS_FILESHARE_API NLinkPri
		{
		public:
			NLinkPri(){}
			GAIA_CLASS_OPERATOR_COMPARE2(nlink.uCmplFileCnt, nlink.uCmplFileCnt, nlink, nlink, NLinkPri);
		public:
			NLink nlink;
		};
	private:
		typedef GAIA::U8 MSGIDTYPE;
		#define MSG_LOGIN 			((MSGIDTYPE)1)
		// username + password.
		#define MSG_LOGOUT			((MSGIDTYPE)2)
		// username.
		#define MSG_NOOP			((MSGIDTYPE)3)
		// Nothing.
		#define MSG_R_FILE			((MSGIDTYPE)10)
		// filecount(u8) * (fileid(u64) + chunkindex(u16)).
		#define MSG_R_FILECHUNK		((MSGIDTYPE)11)
		// fileid(u64) + chunkindex(u16).
		#define MSG_A_FILEHEAD		((MSGIDTYPE)20)
		// fileid(u64) + filecrcsize(u8) + filecrc(void*) + filesize(u32).
		#define MSG_A_FILECHUNK		((MSGIDTYPE)21)
		// fileid(u64) + chunkindex(u16) + subchunkindex(u8) + filedatasize(u16) + filedata(void*).
		#define MSG_A_FILECMPL		((MSGIDTYPE)40)
		// fileid(u64).
		#define MSG_CMPLFILECOUNT	((MSGIDTYPE)50)
		// filecount(FILEID)
		#define MSG_CMPLFILESECTION	((MSGIDTYPE)51)
		// startindex(FILEID) + endindex(FILEID)
		#define MSG_A_CNN			((MSGIDTYPE)80)
		// NetworkAddress + username + password.
		#define MSG_A_OK			((MSGIDTYPE)200)
		// Nothing.
		#define MSG_A_ERROR			((MSGIDTYPE)250)
		// errno(u16).
		typedef GAIA::U16 ERRNO;
		static const ERRNO ERRNO_NOERROR		= 0;
		static const ERRNO ERRNO_BUSY			= 1;
		static const ERRNO ERRNO_SHUTDOWN		= 2;
		static const ERRNO ERRNO_USERNAME		= 3;
		static const ERRNO ERRNO_PASSWORD		= 4;
		static const ERRNO ERRNO_INVALIDPARAM	= 5;
		static const ERRNO ERRNO_REPEATOP		= 6;
		static const ERRNO ERRNO_NOTREADY		= 7;
		const GAIA::GCH* ErrorString(ERRNO en)
		{
			static const GAIA::GCH* ERRNO_STRING[] = 
			{
				"NoError",
				"Busy",
				"Shutdown",
				"UserName",
				"Password",
				"InvalidParam",
				"RepeatOp",
				"NotReady",
			};
			if(en >= sizeofarray(ERRNO_STRING))
				return GNULL;
			return ERRNO_STRING[en];
		}
	private:
		typedef GAIA::CONTAINER::Set<NLink> __LinkListType;
		typedef GAIA::CONTAINER::Set<NLinkPri> __LinkPriListType;
		typedef GAIA::CONTAINER::BasicBuffer<GAIA::NM, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::NM> > __MsgType;
	public:
		FileShare(){this->init();}
		~FileShare(){}
		GAIA::BL Initialize(const FileShareDesc& desc)
		{
			if(m_bInitialized)
				return GAIA::False;
		#if GAIA_OS == GAIA_OS_WINDOWS
			WSAData wsadata;
			WSAStartup(MAKEWORD(2, 2), &wsadata);
		#endif
			m_usergroup.Load(FILE_USERGROUP);
			m_filelist.Load(FILE_FILELIST);
			m_filestate.resize(m_filelist.GetFileCount() / 8 + m_filelist.GetFileCount() % 8);
			m_pMWThread = new MainWorkThread; m_pMWThread->SetFileShare(this);
			m_pMWThread->SetStackSize(THREAD_STACK_SIZE);
			m_pHeartTickThread = new HeartTickThread; m_pHeartTickThread->SetFileShare(this);
			m_pHeartTickThread->SetStackSize(THREAD_STACK_SIZE);
			m_pNH = new NHandle; m_pNH->SetFileShare(this);
			m_pNReceiver = new NReceiver; m_pNReceiver->SetFileShare(this); m_pNReceiver->SetStackSize(THREAD_STACK_SIZE);
			m_pNSender = new NSender; m_pNSender->SetFileShare(this); m_pNSender->SetStackSize(THREAD_STACK_SIZE);
			m_pNListener = new NListener; m_pNListener->SetFileShare(this); m_pNListener->SetStackSize(THREAD_STACK_SIZE);
			m_pNListener->SetAcceptCallBack(&m_NAcceptCallBack); m_NAcceptCallBack.SetFileShare(this);
			m_desc = desc;
			m_bInitialized = GAIA::True;
			return GAIA::True;
		}
		GAIA::BL Release()
		{
			if(!m_bInitialized)
				return GAIA::False;
		#if GAIA_OS == GAIA_OS_WINDOWS
			WSACleanup();
		#endif
			delete m_pMWThread;
			delete m_pHeartTickThread;
			m_pNH->Release(); m_pNH = GNULL;
			delete m_pNReceiver;
			delete m_pNSender;
			delete m_pNListener;
			m_bInitialized = GAIA::False;
			return GAIA::True;
		}
		GINL GAIA::BL IsInitialized() const
		{
			return m_bInitialized;
		}
		GINL const FileShareDesc& GetDesc() const
		{
			return m_desc;
		}
		GAIA::BL Startup()
		{
			if(m_bStartuped)
				return GAIA::False;
			m_pNH->SetSelfAddress(m_desc.m_selfaddr);
			GAIA::NETWORK::NetworkHandle::ConnectDesc cnndesc;
			cnndesc.addr = m_desc.m_selfaddr;
			cnndesc.bStabilityLink = GAIA::False;
			if(!m_pNH->Connect(cnndesc))
				return GAIA::False;
			m_pNH->SetReceiver(m_pNReceiver);
			m_pNH->SetSender(m_pNSender);
			m_pNReceiver->Begin();
			m_pNSender->Begin();
			m_pMWThread->Run();
			m_pHeartTickThread->Run();
			m_bStartuped = GAIA::True;
			return GAIA::True;
		}
		GAIA::BL Shutdown()
		{
			if(!m_bStartuped)
				return GAIA::False;
			m_pMWThread->SetExitCmd(GAIA::True);
			{
				m_pMWThread->Wait();
			}
			m_pMWThread->SetExitCmd(GAIA::False);
			m_pHeartTickThread->SetExitCmd(GAIA::True);
			{
				m_pHeartTickThread->Wait();
			}
			m_pHeartTickThread->SetExitCmd(GAIA::False);
			m_pNSender->End();
			m_pNReceiver->End();
			m_pNH->SetReceiver(GNULL);
			if(m_pNH->IsConnected())
				m_pNH->Disconnect();
			for(__LinkListType::it it = m_links.front_it(); !it.empty(); ++it)
				delete (*it).pCmplFiles;
			m_links.clear();
			m_prilinks.clear();
			m_bStartuped = GAIA::False;
			return GAIA::True;
		}
		GINL GAIA::BL IsStartuped() const
		{
			return m_bStartuped;
		}
		GINL GAIA::GVOID SetMaxUploadSpeed(const GAIA::U64& uSpeed){m_uUSpeed = uSpeed;}
		GINL const GAIA::U64& GetMaxUploadSpeed() const{return m_uUSpeed;}
		GINL GAIA::GVOID SetMaxDownloadSpeed(const GAIA::U64& uSpeed){m_uDSpeed = uSpeed;}
		GINL const GAIA::U64& GetMaxDownloadSpeed() const{return m_uDSpeed;}
		GINL GAIA::GVOID SetReadRootPath(const GAIA::GCH* pszPathName){m_readroot = pszPathName;}
		GINL const GAIA::GCH* GetReadRootPath() const{return m_readroot.front_ptr();}
		GINL GAIA::GVOID SetWriteRootPath(const GAIA::GCH* pszPathName){m_writeroot = pszPathName;}
		GINL const GAIA::GCH* GetWriteRootPath() const{return m_writeroot.front_ptr();}
		GINL GAIA::GVOID SetFileCmpl(const FILEID& fileid, GAIA::BL bCmpl){GAIA::SYNC::AutoLock al(m_lr_filestate); m_filestate.set(fileid);}
		GINL GAIA::BL GetFileCmpl(const FILEID& fileid) const{GAIA::SYNC::AutoLock al((const_cast<FileShare*>(this))->m_lr_filestate); return m_filestate.exist(fileid);}
		GINL GAIA::GVOID SetAllFileCmpl(GAIA::BL bCmpl){GAIA::SYNC::AutoLock al(m_lr_filestate); if(m_filestate.size() > 0){GAIA::ALGORITHM::memset(m_filestate.front_ptr(), bCmpl ? 1 : 0, m_filestate.size());}}
		GINL GAIA::GVOID SetMainServerNAddr(const GAIA::NETWORK::NetworkAddress& na){m_mainna = na;}
		GINL const GAIA::NETWORK::NetworkAddress& GetMainServerNAddr() const{return m_mainna;}
		GINL GAIA::BL Request(const GAIA::NETWORK::NetworkAddress& na, const GAIA::CONTAINER::Vector<FILEID>& listID)
		{
			__MsgType msg;
			for(GAIA::CONTAINER::Vector<FILEID>::const_it it = listID.const_front_it(); !it.empty(); ++it)
			{
				if(msg.write_size() == 0)
				{
					msg << na;
					msg << MSG_R_FILE;
					msg << (GAIA::U8)0;
				}
				GAIA_AST(GAIA::NETWORK::NetworkHandle::MAX_NOSTABILITY_SENDSIZE - msg.write_size() >= sizeof(FILEID) + sizeof(GAIA::U16));
				msg << *it;
				msg << (GAIA::U16)0;
				if(GAIA::NETWORK::NetworkHandle::MAX_NOSTABILITY_SENDSIZE - msg.write_size() < sizeof(FILEID) + sizeof(GAIA::U16))
				{
					GAIA::NM nCount = msg.write_size() - sizeof(na) - sizeof(MSG_R_FILE) - sizeof(GAIA::U8);
					nCount /= sizeof(FILEID) + sizeof(GAIA::U16);
					GAIA_AST(nCount < 256);
					*(GAIA::U8*)(msg.front_ptr() + sizeof(na) + sizeof(MSG_R_FILE)) = (GAIA::U8)nCount;
					m_pNH->Send(msg.front_ptr(), msg.write_size());
					msg.clear();
				}
			}
			if(msg.write_size() != 0)
				m_pNH->Send(msg.front_ptr(), msg.write_size());
			return GAIA::True;
		}
		GINL GAIA::GVOID RequestAll()
		{
		}
		GAIA::BL Command(const GAIA::GCH* pszCmd)
		{
			// Command analyze.
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
				"readroot",				"set read root path, format = readroot [file_path_name].",
				"writeroot",			"set write root path, format = writeroot [file_path_name].",

				"cmpl",					"set/get file downlaod complete state, format = cmpl fileid [0or1]",
				"cmplall",				"set all file download complete, format = cmplall 0or1.",
				"req",					"request a file, format = req fileid",
				"reqall",				"request all files, format reqall",

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
				"filename",				"show filename by id, format = filename id.",
				"fileid",				"show fileid by filename, format = fileid filename.",
				"files",				"show file in the path, format = files filename isincludechild.",

				"login",				"login to remote node, format = login username password ip port.",
				"logout",				"logout from remote node, format = logout username ip port.",
			};
			GAIA_ENUM_BEGIN(COMMAND_LIST)
				CMD_HELP,
				CMD_SAVE,
				CMD_BUILD,
				CMD_READROOT,
				CMD_WRITEROOT,

				CMD_CMPL,
				CMD_CMPLALL,
				CMD_REQUEST,
				CMD_REQUESTALL,

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
				CMD_FILENAME,
				CMD_FILEID,
				CMD_FILES,

				CMD_LOGIN,
				CMD_LOGOUT,
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
					GAIA::SYNC::AutoLock al1(m_lr_usergroup);
					GAIA::SYNC::AutoLock al2(m_lr_filelist);
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
					const GAIA::GCH* psz = "";
					if(listPart[2] != "NULL")
						psz = listPart[2].front_ptr();
					GAIA::SYNC::AutoLock al(m_lr_filelist);
					if(!m_filelist.Build(listPart[1].front_ptr(), psz))
						CMDFAILED;
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_READROOT))
			{
				if(listPart.size() == 2)
					m_readroot = listPart[1].front_ptr();
				else if(listPart.size() == 1)
					m_prt << m_readroot.front_ptr() << "\n";
				else
					CMDFAILED;
			}
			else if(CMD(CMD_WRITEROOT))
			{
				if(listPart.size() == 2)
					m_writeroot = listPart[1].front_ptr();
				else if(listPart.size() == 1)
					m_prt << m_writeroot.front_ptr() << "\n";
				else
					CMDFAILED;
			}
			else if(CMD(CMD_CMPL))
			{
				if(listPart.size() == 3)
					this->SetFileCmpl((FILEID)listPart[1], (GAIA::BL)(GAIA::NM)listPart[2]);
				else
					CMDFAILED;
			}
			else if(CMD(CMD_CMPLALL))
			{
				if(listPart.size() == 2)
					this->SetAllFileCmpl((GAIA::BL)(GAIA::NM)listPart[1]);
				else
					CMDFAILED;
			}
			else if(CMD(CMD_REQUEST))
			{
				if(listPart.size() == 2)
				{
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_REQUESTALL))
			{
				if(listPart.size() == 1)
				{
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_CREATEUSER))
			{
				if(listPart.size() == 2)
				{
					GAIA::SYNC::AutoLock al(m_lr_usergroup);
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
					GAIA::SYNC::AutoLock al(m_lr_usergroup);
					if(!m_usergroup.DeleteUser(listPart[1].front_ptr()))
						CMDFAILED;
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_DELETEALLUSER))
			{
				if(listPart.size() == 1)
				{
					GAIA::SYNC::AutoLock al(m_lr_usergroup);
					m_usergroup.DeleteUserAll();
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_PASSWORD))
			{
				if(listPart.size() == 3)
				{
					GAIA::SYNC::AutoLock al(m_lr_usergroup);
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
					GAIA::SYNC::AutoLock al(m_lr_usergroup);
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
					GAIA::SYNC::AutoLock al(m_lr_usergroup);
					if(!m_usergroup.DeleteGroup(listPart[1].front_ptr()))
						CMDFAILED;
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_DELETEALLGROUP))
			{
				if(listPart.size() == 1)
				{
					GAIA::SYNC::AutoLock al(m_lr_usergroup);
					m_usergroup.DeleteGroupAll();
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_RIGHT))
			{
				if(listPart.size() == 4)
				{
					GAIA::SYNC::AutoLock al(m_lr_usergroup);
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
					GAIA::SYNC::AutoLock al(m_lr_usergroup);
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
					GAIA::SYNC::AutoLock al(m_lr_usergroup);
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
					GAIA::SYNC::AutoLock al(m_lr_usergroup);
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
					GAIA::SYNC::AutoLock al(m_lr_usergroup);
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
					GAIA::SYNC::AutoLock al(m_lr_usergroup);
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
					GAIA::SYNC::AutoLock al(m_lr_usergroup);
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
					GAIA::SYNC::AutoLock al(m_lr_usergroup);
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
			else if(CMD(CMD_FILENAME))
			{
				if(listPart.size() == 2)
				{
					GAIA::SYNC::AutoLock al(m_lr_filelist);
					FILEID fid = listPart[1];
					GAIA::GCH szFileName[MAX_PATHLEN];
					if(m_filelist.GetName(fid, szFileName))
						m_prt << szFileName << "\n";
					else
						CMDFAILED;
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_FILEID))
			{
				if(listPart.size() == 2)
				{
					GAIA::SYNC::AutoLock al(m_lr_filelist);
					const FILEID* pFileID = m_filelist.GetIDByName(listPart[1]);
					if(pFileID != GNULL)
						m_prt << *pFileID << "\n";
					else
						CMDFAILED;
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_FILES))
			{
				if(listPart.size() == 3)
				{
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_LOGIN))
			{
				if(listPart.size() == 5)
				{
					GAIA::NETWORK::NetworkAddress na;
					na.ip.FromString(listPart[3].front_ptr());
					na.uPort = listPart[4];
					if(!this->NLogin(na, listPart[1].front_ptr(), listPart[2].front_ptr()))
						CMDFAILED;
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_LOGOUT))
			{
				if(listPart.size() == 4)
				{
					GAIA::NETWORK::NetworkAddress na;
					na.ip.FromString(listPart[2].front_ptr());
					na.uPort = listPart[3];
					if(!this->NLogout(na, listPart[1].front_ptr()))
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
		GINL GAIA::GVOID init()
		{
			m_bInitialized = GAIA::False;
			m_bStartuped = GAIA::False;
			m_uUSpeed = (GAIA::U64)GINVALID;
			m_uDSpeed = (GAIA::U64)GINVALID;
			m_filelist.SetPrint(&m_prt);
			m_pMWThread = GNULL;
			m_pHeartTickThread = GNULL;
			m_pNH = GNULL;
			m_pNReceiver = GNULL;
			m_pNSender = GNULL;
			m_pNListener = GNULL;
			m_state = NLink::STATE_DISCONNECT;
		}
		GINL GAIA::BL OnReceive(NHandle& s, const GAIA::U8* p, GAIA::U32 size)
		{
			__MsgType msg;
			msg.write(p, size);
			GAIA::NETWORK::NetworkAddress na;
			MSGIDTYPE msgid;
			msg >> na;
			msg >> msgid;
			switch(msgid)
			{
			case MSG_LOGIN:
				{
					GAIA::GCH uname[USERNAMELEN + 1];
					GAIA::GCH password[USERNAMELEN + 1];
					msg >> uname;
					msg >> password;
					ERRNO en = this->BeLogin(na, uname, password);
					if(en != ERRNO_NOERROR)
					{
						__MsgType msg;
						msg << na;
						msg << MSG_A_ERROR;
						msg << en;
						m_pNH->Send(msg.front_ptr(), msg.write_size());
					}
					else
						this->SendOK(na);
				}
				break;
			case MSG_LOGOUT:
				{
					GAIA::GCH uname[USERNAMELEN + 1];
					msg >> uname;
					ERRNO en = this->BeLogout(na, uname);
					if(en != ERRNO_NOERROR)
					{
						__MsgType msg;
						msg << na;
						msg << MSG_A_ERROR;
						msg << en;
						m_pNH->Send(msg.front_ptr(), msg.write_size());
					}
					else
						this->SendOK(na);
				}
				break;
			case MSG_NOOP:
				{
				}
				break;
			case MSG_R_FILE:
				{
				}
				break;
			case MSG_R_FILECHUNK:
				{
				}
				break;
			case MSG_A_FILEHEAD:
				{
				}
				break;
			case MSG_A_FILECHUNK:
				{
				}
				break;
			case MSG_A_FILECMPL:
				{
				}
				break;
			case MSG_CMPLFILECOUNT:
				{
					FILEID filecount;
					msg >> filecount;
					NLinkPri np;
					np.nlink.na = na;
					np.nlink.bBeLink = GAIA::True;
					GAIA::SYNC::AutoLock al1(m_lr_links);
					NLink* pNLink = m_links.find(np.nlink);
					if(pNLink == GNULL)
					{
						__MsgType msg;
						msg << na;
						msg << MSG_A_ERROR;
						msg << ERRNO_NOTREADY;
						m_pNH->Send(msg.front_ptr(), msg.write_size());
						break;
					}
					np.nlink.uCmplFileCnt = pNLink->uCmplFileCnt;
					pNLink->uCmplFileCnt = filecount;
					GAIA::SYNC::AutoLock al2(m_lr_prilinks);
					m_prilinks.erase(np);
					np.nlink.uCmplFileCnt = filecount;
					m_prilinks.insert(np);
				}
				break;
			case MSG_CMPLFILESECTION:
				{
					FileIDSection fidsec;
					msg >> fidsec.uStart;
					msg >> fidsec.uEnd;
					if(fidsec.uStart < fidsec.uEnd)
						break;
					NLinkPri np;
					np.nlink.na = na;
					np.nlink.bBeLink = GAIA::True;
					GAIA::SYNC::AutoLock al(m_lr_links);
					NLink* pNLink = m_links.find(np.nlink);
					if(pNLink == GNULL)
					{
						__MsgType msg;
						msg << na;
						msg << MSG_A_ERROR;
						msg << ERRNO_NOTREADY;
						m_pNH->Send(msg.front_ptr(), msg.write_size());
						break;
					}
					GAIA::CONTAINER::Set<FileIDSection>::it it = np.nlink.pCmplFiles->lower_bound(fidsec);
					if(it.empty())
					{
						it = np.nlink.pCmplFiles->upper_bound(fidsec);
						if(it.empty())
							np.nlink.pCmplFiles->insert(fidsec);
						else
						{
							FileIDSection& fidsec_prev = *it;
							if(fidsec_prev.uEnd + 1 == fidsec.uStart)
								fidsec_prev.uEnd = fidsec.uEnd;
							else
								np.nlink.pCmplFiles->insert(fidsec);
						}
					}
					else
					{
						FileIDSection& fidsec_next = *it;
						--it;
						if(it.empty())
						{
							if(fidsec.uEnd + 1 == fidsec_next.uStart)
								fidsec_next.uStart = fidsec.uStart;
							else
								np.nlink.pCmplFiles->insert(fidsec);
						}
						else
						{
							FileIDSection& fidsec_prev = *it;
							if(fidsec_prev.uEnd + 1 == fidsec.uStart && 
								fidsec.uEnd + 1 == fidsec_next.uStart)
							{
								fidsec_prev.uEnd = fidsec_next.uEnd;
								np.nlink.pCmplFiles->erase(fidsec_next);
							}
							else if(fidsec_prev.uEnd + 1 == fidsec.uStart)
								fidsec_prev.uEnd = fidsec.uEnd;
							else if(fidsec.uEnd + 1 == fidsec_next.uStart)
								fidsec_next.uStart = fidsec.uStart;
							else
								np.nlink.pCmplFiles->insert(fidsec);
						}
					}
				}
				break;
			case MSG_A_CNN:
				{
				}
				break;
			case MSG_A_OK:
				{
					m_prt << "OK!" << "\n";

					if(m_state == NLink::STATE_DISCONNECT || 
						m_state == NLink::STATE_ONLINE)
					{
						// Statistics file state.
						FILEID uFileCount = 0;
						m_state = NLink::STATE_READY;
						GAIA::SYNC::AutoLock al(m_lr_filestate);
						GAIA::CONTAINER::BasicBitset<GAIA::NM>::_sizetype size = m_filestate.size();
						FILEID startindex = GINVALID, endindex = GINVALID;
						GAIA::CONTAINER::Vector<FileIDSection> fidseclist;
						for(GAIA::CONTAINER::BasicBitset<GAIA::NM>::_sizetype x = 0; x < size * 8; ++x)
						{
							if(startindex == GINVALID)
							{
								if(m_filestate.exist(x))
									startindex = (FILEID)x;
							}
							else
							{
								if(!m_filestate.exist(x))
								{
									FileIDSection fidsec;
									fidsec.uStart = startindex;
									fidsec.uEnd = x - 1;
									uFileCount += fidsec.uEnd - fidsec.uStart;
									fidseclist.push_back(fidsec);
									startindex = GINVALID;
								}
							}
						}
						// Send file count.
						{
							__MsgType msg;
							msg << na;
							msg << MSG_CMPLFILECOUNT;
							msg << uFileCount;
							m_pNH->Send(msg.front_ptr(), msg.write_size());
						}
						// Send file section.
						{
							for(GAIA::CONTAINER::Vector<FileIDSection>::it it = fidseclist.front_it(); !it.empty(); ++it)
							{
								__MsgType msg;
								msg << na;
								msg << MSG_CMPLFILESECTION;
								msg << (*it).uStart;
								msg << (*it).uEnd;
								m_pNH->Send(msg.front_ptr(), msg.write_size());
							}
						}
					}
				}
				break;
			case MSG_A_ERROR:
				{
					ERRNO en;
					msg >> en;
					const GAIA::GCH* pszError = this->ErrorString(en);
					if(pszError == GNULL)
						m_prt << "Known error!" << "\n";
					else
						m_prt << "Error! ErrorNo = " << pszError << "\n";
				}
				break;
			default:
				return GAIA::False;
			}
			return GAIA::True;
		}
		GINL GAIA::BL NLogin(const GAIA::NETWORK::NetworkAddress& na, const GAIA::GCH* pszUserName, const GAIA::GCH* pszPassword)
		{
			__MsgType msg;
			msg << na;
			msg << MSG_LOGIN;
			msg << pszUserName;
			msg << pszPassword;
			return m_pNH->Send(msg.front_ptr(), msg.write_size());
		}
		GINL ERRNO BeLogin(const GAIA::NETWORK::NetworkAddress& na, const GAIA::GCH* pszUserName, const GAIA::GCH* pszPassword)
		{
			GAIA_AST(!GAIA::ALGORITHM::stremp(pszUserName));
			if(GAIA::ALGORITHM::stremp(pszUserName))
				return ERRNO_INVALIDPARAM;
			GAIA::SYNC::AutoLock al(m_lr_usergroup);
			if(!m_usergroup.FindUser(pszUserName))
				return ERRNO_USERNAME;
			const GAIA::GCH* pszCorrectPassword = m_usergroup.GetUserPassword(pszUserName);
			if(GAIA::ALGORITHM::stremp(pszCorrectPassword) && 
				GAIA::ALGORITHM::stremp(pszPassword))
			{
			}
			else
			{
				if(GAIA::ALGORITHM::strcmp(pszPassword, pszCorrectPassword) != 0)
					return ERRNO_PASSWORD;
			}
			NLink nl;
			nl.na = na;
			nl.bBeLink = GAIA::True;
			GAIA::SYNC::AutoLock al1(m_lr_links);
			NLink* pNLink = m_links.find(nl);
			if(pNLink != GNULL)
			{
				if(pNLink->state == NLink::STATE_READY)
					return ERRNO_REPEATOP;
				pNLink->state = NLink::STATE_READY;
			}
			else
			{
				nl.state = NLink::STATE_READY;
				nl.pCmplFiles = new GAIA::CONTAINER::Set<FileIDSection>;
				m_links.insert(nl);
				NLinkPri nlp;
				nlp.nlink = nl;
				GAIA::SYNC::AutoLock al2(m_lr_prilinks);
				m_prilinks.insert(nlp);
			}
			return ERRNO_NOERROR;
		}
		GINL GAIA::BL NLogout(const GAIA::NETWORK::NetworkAddress& na, const GAIA::GCH* pszUserName)
		{
			__MsgType msg;
			msg << na;
			msg << MSG_LOGOUT;
			msg << pszUserName;
			return m_pNH->Send(msg.front_ptr(), msg.write_size());
		}
		GINL ERRNO BeLogout(const GAIA::NETWORK::NetworkAddress& na, const GAIA::GCH* pszUserName)
		{
			GAIA_AST(!GAIA::ALGORITHM::stremp(pszUserName));
			if(GAIA::ALGORITHM::stremp(pszUserName))
				return ERRNO_INVALIDPARAM;
			GAIA::SYNC::AutoLock al1(m_lr_usergroup);
			if(!m_usergroup.FindUser(pszUserName))
				return ERRNO_USERNAME;
			NLink nl;
			nl.na = na;
			nl.bBeLink = GAIA::True;
			GAIA::SYNC::AutoLock al2(m_lr_links);
			NLink* pNLink = m_links.find(nl);
			if(pNLink == GNULL)
				return ERRNO_NOTREADY;
			else
			{
				if(pNLink->state != NLink::STATE_READY)
					return ERRNO_NOTREADY;
			}
			pNLink->state = NLink::STATE_ONLINE;
			return ERRNO_NOERROR;
		}
		GINL GAIA::GVOID SendOK(const GAIA::NETWORK::NetworkAddress& na)
		{
			__MsgType msg;
			msg << na;
			msg << MSG_A_OK;
			m_pNH->Send(msg.front_ptr(), msg.write_size());
		}
	private:	
		FileShareDesc m_desc;
		GAIA::NETWORK::NetworkAddress m_mainna;
		GAIA::BL m_bInitialized;
		GAIA::BL m_bStartuped;
		GAIA::U64 m_uUSpeed;
		GAIA::U64 m_uDSpeed;
		FileList m_filelist; GAIA::SYNC::Lock m_lr_filelist;
		UserGroup m_usergroup; GAIA::SYNC::Lock m_lr_usergroup;
		MainWorkThread* m_pMWThread;
		HeartTickThread* m_pHeartTickThread;
		NHandle* m_pNH;
		NReceiver* m_pNReceiver;
		NSender* m_pNSender;
		NListener* m_pNListener;
		NAcceptCallBack m_NAcceptCallBack;
		GAIA::PRINT::Print m_prt;
		FSTR m_readroot;
		FSTR m_writeroot;
		__LinkListType m_links; GAIA::SYNC::Lock m_lr_links;
		__LinkPriListType m_prilinks; GAIA::SYNC::Lock m_lr_prilinks;
		GAIA::CONTAINER::BasicBitset<GAIA::NM> m_filestate; GAIA::SYNC::Lock m_lr_filestate;
		NLink::STATE m_state;
	};
};

#endif
