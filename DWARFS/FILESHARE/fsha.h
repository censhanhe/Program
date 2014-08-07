#ifndef 	__DWARFS_FILE_SHARE_H__
#define 	__DWARFS_FILE_SHARE_H__

//#define FSHA_DEBUG

#if GAIA_COMPILER == GAIA_COMPILER_CL
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

#define FSHA_PERF ((GAIA::F64)GAIA::TIME::tick_time() * 0.001 * 0.001)

/*
*	[Lock order table]
*
*	------	----	usergroup	filelist	-------------	--------------	-------		-----	--------	----
*	reqeds	reqs	---------	--------	-------------	--------------	fcaches		-----	--------	----
*	------	----	---------	--------	filesendtasks	--------------	fcaches		-----	--------	----
*	------	----	---------	--------	-------------	filewritetasks	fcaches		-----	--------	----
*	------	----	---------	--------	-------------	--------------	-------		links	prilinks	----
*	------	----	usergroup	--------	-------------	--------------	-------		links	prilinks	----
*	------	----	---------	--------	-------------	--------------	-------		links	--------	send
*/

/*
*	[Protocal flow]
*	NodeA---------------NodeB-----------------NodeB---------------------NodeB
*
*
*	=========================================================================
*	LOGIN---------------->---------------------->
*						 |						|
*						 |						|
*	LOGINOK--------------<						|
*						 |						|
*						 |						|
*	CMPLFILECOUNT--------<						|
*												|
*												|
*	CMPFILECOUNT--------->						|
*	|											|
*	|											|
*	CMPLFILESECTION------>						|
*												|
*	ERROR---------------------------------------<
*		INVALIDPARAM							|
*		USERNAME								|
*		PASSWORD								|
*		REPEATOP								|
*
*
*	=========================================================================
*	LOGOUT--------------->---------------------->
*						 |						|
*						 |						|
*	LOGOUTOK-------------<						|
*												|
*												|
*	ERROR---------------------------------------<
*		INVALIDPARAM
*		USERNAME
*		NOTREADY
*
*
*	=========================================================================
*	FILE----------------->---------------------->----------------------->
*						 |						|						|
*						 |						|						|
*	FILEHEAD-------------<						|						|
*						 |						|						|
*						 |						|						|
*	FILECHUNK[1,n]-------<						|						|
*	|											|						|
*	|											|						|
*	CMPLFILESECTION[0,1]->						|						|
*												|						|
*												|						|
*	CNN-----------------------------------------<						|
*																		|
*																		|
*	FILENOTEXIST--------------------------------------------------------<
*
*
*	=========================================================================
*	FILECHUNK------------>
*						 |
*						 |
*	FILECHUNK[1,n]-------<
*	|
*	|
*	CMPLFILESECTION[0,1]->
*
*
*	=========================================================================
*	NOOP<---------------->NOOP
*/

namespace DWARFS_FSHA
{
	/* Constants. */
	static const GAIA::TCH VERSION_STRING[] = _T("00.00.01.00");
	static const GAIA::U32 VERSION = 0x00000100;
	static const GAIA::TCH INTERNAL_USERNAME[] = _T("admin");
	static const GAIA::TCH INTERNAL_PASSWORD[] = _T("password");
	static const GAIA::N32 MAXPATHDEPTH = 18;
	static const GAIA::N32 MAXPATHLEN = 240;
	static const GAIA::U16 MAINRECVPORT = 7121;
	static const GAIA::U32 SUBCHUNKSIZE = 800;
	static const GAIA::U32 CHUNKSIZE = SUBCHUNKSIZE * 256;
	static const GAIA::U32 THREADSTACKSIZE = 1024 * 128;
	static const GAIA::N32 USERNAMELEN = 16;
	static const GAIA::N32 PASSWORDLEN = 16;
	static const GAIA::N32 GROUPNAMELEN = 16;
	static const GAIA::TCH FILE_USERGROUP[] = _T("usergroup");
	static const GAIA::U32 FILE_USERGROUP_FLAG = 'FSUG';
	static const GAIA::U32 FILE_USERGROUP_VERSION = 0;
	static const GAIA::TCH FILE_FILELIST[] = _T("filelist");
	static const GAIA::U32 FILE_FILELIST_FLAG = 'FSFL';
	static const GAIA::U32 FILE_FILELIST_VERSION = 0;
	static const GAIA::TCH FILE_BANIP[] = _T("banip");
	static const GAIA::U32 FILE_BANIP_FLAG = 'BAIP';
	static const GAIA::U32 FILE_BANIP_VERSION = 0;
	static const GAIA::N32 DEFAULTMAXREQFILECOUNTSAMETIME = 32;
	static const GAIA::U64 CMPLFILESNOTIFYFREQ = 400;
	static const GAIA::U64 LINKRECYCLETIME = 22000000;
	static const GAIA::U32 JUMPDISTANCE = 100;
	static const GAIA::U32 MAINJUMPODDS = 99;
	static const GAIA::U32 SUBJUMPODDS = 30;
	static const GAIA::U64 REQUESTTIMEOUTTIME = 5000000;
	static const GAIA::U64 REREQUESTTIMEOUTTIME = 10000000;
	static const GAIA::U64 REQUESTCMPLFILESNOTIFYTIME = 5000000;
	static const GAIA::U32 SINGLECHUNKREQUESTLIMIT = 4;
	static const GAIA::U32 MAXCHUNKREQUESTCOUNTPERDISPATCH = 100;
	static const GAIA::U32 JUMPOFFSETFILESCOUNT = 100;
	static const GAIA::U32 BATCHCHUNKSENDCOUNT = 10;
	static const GAIA::U32 BANIPDISPATCHTIME = 1000000;

	/* Type declaration. */
	typedef GAIA::SYNC::AutoLock AL;
	typedef GAIA::U32 FILEID; // GINVALID means invalid id.
	typedef GAIA::U16 CHUNKINDEX;
	typedef GAIA::U8 SUBCHUNKINDEX;
	typedef GAIA::U16 SUBCHUNKSIZETYPE;
	typedef GAIA::U8 REQFILECOUNTTYPE;
	typedef GAIA::U32 FILESIZETYPE;
	typedef GAIA::CONTAINER::BasicString<GAIA::TCH, GAIA::U8> FSTR;
	typedef GAIA::CONTAINER::BasicVector<FSTR, FILEID, GAIA::ALGORITHM::TwiceSizeIncreaser<FILEID> > FSTRLIST;
	typedef GAIA::CONTAINER::Vector<FILEID> FIDLIST;
	typedef GAIA::CONTAINER::BasicAVLTree<
			FSTR, GAIA::N32, GAIA::N32,
			GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32> > FSTRBTR;
	typedef GAIA::U32 MAPINDEX; // 0 means invalid id.
	typedef GAIA::CONTAINER::BasicChars<GAIA::TCH, GAIA::N16, MAXPATHLEN> FNAMETYPE;
	typedef GAIA::CONTAINER::Array<FNAMETYPE, MAXPATHDEPTH> FNAMEPARTLISTTYPE;
	typedef GAIA::U32 CRCTYPE;

	/* File sequence. */
	class __DWARFS_FILESHARE_API FileSequence : public GAIA::Entity
	{
	public:
		FileSequence(){}
		~FileSequence(){}
		GINL GAIA::BL Add(const GAIA::TCH* pszFileName)
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
		GINL const FILEID& GetRecCount() const{return m_files.size();}
		GINL const GAIA::TCH* GetRec(const FILEID& index){if(index >= this->GetRecCount()) return GNULL; return m_files[index];}
	private:
		FSTRLIST m_files;
		FSTRBTR m_filesbtr;
	};

	/* File list class. */
	class __DWARFS_FILESHARE_API FileList : public GAIA::Entity
	{
	#define FILE_LIST_LOG(msg) do{if(m_pPr != GNULL){*m_pPr << (msg) << "\n";}}while(GAIA::ALWAYSFALSE)
	#define FILE_LIST_LOG2(msg1, msg2) do{if(m_pPr != GNULL){*m_pPr << (msg1) << (msg2) << "\n";}}while(GAIA::ALWAYSFALSE)
	#define FILE_LIST_LOG3(msg1, msg2, msg3) do{if(m_pPr != GNULL){*m_pPr << (msg1) << (msg2) << (msg3) << "\n";}}while(GAIA::ALWAYSFALSE)
	public:
		GINL FileList(){this->init();}
		GINL ~FileList(){}
		GINL GAIA::GVOID SetPrint(GAIA::PRINT::PrintBase* pPr){m_pPr = pPr;}
		GINL GAIA::PRINT::PrintBase* GetPrint() const{return m_pPr;}
		GAIA::BL Load(const GAIA::TCH* pszFileName)
		{
			GAIA_AST(!GAIA::ALGORITHM::stremp(pszFileName));
			if(GAIA::ALGORITHM::stremp(pszFileName))
				return GAIA::False;

			/* Construct serializer. */
			GAIA::FILESYSTEM::File fileiofile;
			GAIA::FRAMEWORK::Factory* pFactory = new GAIA::FRAMEWORK::Factory;
			GAIA::SERIALIZER::Serializer* pSerializer =
				(GAIA::SERIALIZER::Serializer*)pFactory->CreateInstance(GAIA::FRAMEWORK::CLSID_SERIALIZER, GNULL);
			GAIA::IO::FileIO* pFileIO = (GAIA::IO::FileIO*)pFactory->CreateInstance(GAIA::FRAMEWORK::CLSID_FILEIO, &fileiofile);
			if(!pFileIO->Open(pszFileName, GAIA::IO::IO::IO_TYPE_READ))
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
				for(__NameMapType::it it = m_names.front_it(); !it.empty(); ++it)
					m_namespool.release((__NameMapPool::_datatype*)(*it));
				m_names.clear();
				__NameMapType::_sizetype size;
				sr >> size;
				m_names.reserve(size);
				for(__NameMapType::_sizetype x = 0; x < size; ++x)
				{
					__NameMapPool::_datatype* p = m_namespool.alloc();
					sr >> p->name;
					m_names.push_back(p);
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
						fr.fid = n.fid;
						__FileRecIDListType::_sizetype tfinded = m_recids.search(fr);
						GAIA_AST(tfinded != GINVALID);
						m_recids[tfinded].it = it;
					}
					++it;
				}
			}
		#ifdef FSHA_DEBUG
			for(__FileRecIDListType::_sizetype x = 0; x < m_recids.size(); ++x)
				GAIA_AST(m_recids[x].fid == x);
		#endif

			/* Construct file rec seq list. */
			m_recseqs.clear();
			for(__FileRecIDListType::it it = m_recids.front_it(); !it.empty(); ++it)
			{
				FileRecSeq frs;
				frs.pFileRec = &(*it);
				m_recseqs.push_back(frs);
			}
			m_recseqs.sort();

		FUNCTION_END:
			/* Destruct serializer. */
			pSerializer->Release();
			delete pFactory;
			return GAIA::True;
		}
		GAIA::BL Save(const GAIA::TCH* pszFileName)
		{
			GAIA_AST(!GAIA::ALGORITHM::stremp(pszFileName));
			if(GAIA::ALGORITHM::stremp(pszFileName))
				return GAIA::False;

			/* Construct serializer. */
			GAIA::FILESYSTEM::File fileiofile;
			GAIA::FRAMEWORK::Factory* pFactory = new GAIA::FRAMEWORK::Factory;
			GAIA::SERIALIZER::Serializer* pSerializer =
				(GAIA::SERIALIZER::Serializer*)pFactory->CreateInstance(GAIA::FRAMEWORK::CLSID_SERIALIZER, GNULL);
			GAIA::IO::FileIO* pFileIO = (GAIA::IO::FileIO*)pFactory->CreateInstance(GAIA::FRAMEWORK::CLSID_FILEIO, &fileiofile);
			if(!pFileIO->Open(pszFileName, GAIA::IO::IO::IO_TYPE_WRITE))
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
					sr << (*d).name;
					++it;
				}
			}

			/* Write file tree. */
			FILE_LIST_LOG("Save file trie tree...");
			{
				__FileTreeType::Node& n = m_ftree.root();
				this->SaveNode(sr, n);
			}

			/* Destruct serializer. */
			pSerializer->Release();
			delete pFactory;
			return GAIA::True;
		}
		CRCTYPE BuildFileCRC(const GAIA::TCH* pszPathName)
		{
			GAIA_AST(!GAIA::ALGORITHM::stremp(pszPathName));
			if(GAIA::ALGORITHM::stremp(pszPathName))
				return 0;
			m_crcbuilder.clear();
			GAIA::FILESYSTEM::File file;
			if(!file.Open(pszPathName, GAIA::FILESYSTEM::File::OPEN_TYPE_READ))
				return 0;
			static const GAIA::U32 CRCFILEREADPATCHSIZE = 1024 * 1024;
			GAIA::U8* pBuffer = new GAIA::U8[CRCFILEREADPATCHSIZE];
			GAIA::N64 nReaded;
			while((nReaded = file.Read(pBuffer, CRCFILEREADPATCHSIZE)) != 0)
				m_crcbuilder.build(pBuffer, nReaded);
			delete[] pBuffer;
			return m_crcbuilder.result();
		}
		GAIA::BL Build(const GAIA::TCH* pszPathName, const GAIA::TCH* pszFilter)
		{
			FILE_LIST_LOG("Collision destination path files...");
			GAIA::FILESYSTEM::Directory::__ResultTree restree;
			{
				GAIA::FILESYSTEM::Directory dir;
				if(!dir.CollectFile(pszPathName, pszFilter, GAIA::True, restree))
					return GAIA::False;
			}
			FILE_LIST_LOG3("There are ", restree.catagory_count(restree.root()), " files collected!");

			/* Build name list(m_names). */
			FNAMEPARTLISTTYPE listNamePart;
			this->GenerateFileNamePartList(pszPathName, listNamePart);
			FILE_LIST_LOG("Build file name's string token list...");
			{
				for(__NameMapType::it it = m_names.front_it(); !it.empty(); ++it)
					m_namespool.release((__NameMapPool::_datatype*)(*it));
				m_names.clear();
				m_names.reserve(restree.catagory_count(restree.root()));
				GAIA::FILESYSTEM::Directory::__ResultTree::it it = restree.front_it();
				FNAMEPARTLISTTYPE::_sizetype nRootPart = listNamePart.size();
				while(!it.empty())
				{
					if(nRootPart == 0)
					{
						NameMap* nm = m_namespool.alloc();
						m_names.push_back(nm);
						(**m_names.back_ptr()).name = (*it).front_ptr();
						(**m_names.back_ptr()).name.tolower();
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
				typedef GAIA::CONTAINER::Vector<GAIA::FILESYSTEM::Directory::__ResultTree::_datatype*> __TempPartComineVector;
				__TempPartComineVector listTemp;
				while(!it.empty())
				{
					if(restree.leaf(it))
					{
						listInsert.clear();
						listTemp.clear();
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
								fname += _T("/");
							fname += (*itv)->front_ptr();
							++itv;
						}
						fname.tolower();
						MAPINDEX mit[MAXPATHDEPTH];
						if(this->NameToMapIndex(fname, mit))
						{
							MAPINDEX* pmit = mit;
							while(*pmit != GINVALID)
							{
								TrieNode n;
								n.mapindex = *pmit;
								n.fid = (FILEID)GINVALID;
								listInsert.push_back(n);
								++pmit;
							}
						}
						else
							GAIA_AST(GAIA::ALWAYSFALSE);
						listInsert.back_ptr()->fid = id++;
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
						fr.fid = n.fid;
						fr.it = it;
						fr.uSequence = 0;
						m_recids.push_back(fr);
					}
					++it;
				}
				m_recids.sort();
			}
		#ifdef FSHA_DEBUG
			for(__FileRecIDListType::_sizetype x = 0; x < m_recids.size(); ++x)
				GAIA_AST(m_recids[x].fid == x);
		#endif

			/* Generate file CRC. */
			FILE_LIST_LOG("Generate file CRC...");
			{
				GAIA::N32 nLastPercent = 0;
				for(__FileRecIDListType::_sizetype x = 0; x < m_recids.size(); ++x)
				{
					GAIA::N32 nNewPercent = x * 100 / m_recids.size();
					if(nNewPercent != nLastPercent)
					{
						nLastPercent = nNewPercent;
						if(m_pPr != GNULL)
							(*m_pPr) << nLastPercent << " ";
					}
					GAIA::TCH szName[MAXPATHLEN];
					if(this->GetName(m_recids[x].fid, szName))
					{
						GAIA::TCH szFullName[MAXPATHLEN];
						if(GAIA::ALGORITHM::stremp(pszPathName))
							szFullName[0] = 0;
						else
							GAIA::ALGORITHM::strcpy(szFullName, pszPathName);
						GAIA::ALGORITHM::strcat(szFullName, szName);
						m_recids[x].uCRC = this->BuildFileCRC(szFullName);
					}
					else
						GAIA_AST(GAIA::ALWAYSFALSE);
				}
				if(m_pPr != GNULL)
					(*m_pPr) << "\n";
			}

			/* Generate file rec seq list. */
			FILE_LIST_LOG("Generate file record list by sequence...");
			m_recseqs.clear();
			for(__FileRecIDListType::it it = m_recids.front_it(); !it.empty(); ++it)
			{
				FileRecSeq frs;
				frs.pFileRec = &(*it);
				m_recseqs.push_back(frs);
			}
			m_recseqs.sort();

			return GAIA::True;
		}
		const FILEID* GetIDByName(const GAIA::TCH* pszFileName)
		{
			GAIA_AST(!GAIA::ALGORITHM::stremp(pszFileName));
			if(GAIA::ALGORITHM::stremp(pszFileName))
				return GNULL;
			GAIA::TCH szLower[MAXPATHLEN];
			GAIA::ALGORITHM::strcpy(szLower, pszFileName);
			GAIA::ALGORITHM::tolowers(szLower);
			MAPINDEX mapindex[MAXPATHDEPTH];
			if(!this->NameToMapIndex(szLower, mapindex))
				return GNULL;
			TrieNode tnlist[MAXPATHDEPTH];
			MAPINDEX* p = mapindex;
			for(;;)
			{
				if(*p == GINVALID)
					break;
				TrieNode& tn = tnlist[p - mapindex];
				tn.mapindex = *p;
				++p;
			}
			GAIA_AST(p != mapindex);
			__FileTreeType::Node* pNode = m_ftree.find(GNULL, tnlist, p - mapindex);
			if(pNode == GNULL)
				return GNULL;
			return &(**pNode).fid;
		}
		GAIA::BL GetName(const FILEID& id, GAIA::TCH* pResult)
		{
			__FileRecIDListType::_datatype f;
			f.fid = id;
			__FileRecIDListType::_sizetype nIndex = m_recids.search(f);
			if(nIndex == GINVALID)
				return GAIA::False;
			MAPINDEX mapindex[MAXPATHDEPTH];
			if(!this->GenerateMapIndex(m_recids[nIndex].it, mapindex))
				return GAIA::False;
			return this->MapIndexToName(mapindex, pResult);
		}
		GAIA::BL GetCRC(const FILEID& id, CRCTYPE& crc) const
		{
			__FileRecIDListType::_datatype f;
			f.fid = id;
			__FileRecIDListType::_sizetype nIndex = m_recids.search(f);
			if(nIndex == GINVALID)
				return GAIA::False;
			crc = m_recids[nIndex].uCRC;
			return GAIA::True;
		}
		FILEID GetFileCount() const{return m_recids.size();}
		const FILEID& GetIDBySequence(FILEID uIndex) const{return m_recseqs[uIndex].pFileRec->fid;}
	private:
		class TrieNode
		{
		public:
			GINL TrieNode& operator = (const TrieNode& src){GAIA_AST(&src != this); mapindex = src.mapindex; fid = src.fid; return *this;}
			GAIA_CLASS_OPERATOR_COMPARE(mapindex, mapindex, TrieNode);
			MAPINDEX mapindex;
			FILEID fid;
		};
	public:
		typedef GAIA::CONTAINER::BasicTrieTree<TrieNode, GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32> > __FileTreeType;
	private:
		class NameMap
		{
		public:
			GAIA_CLASS_OPERATOR_COMPARE(name, name, NameMap);
			FSTR name;
		};
		class FileRec
		{
		public:
			GINL FileRec& operator = (const FileRec& src)
			{
				GAIA_AST(&src != this);
				fid = src.fid;
				it = src.it;
				uSequence = src.uSequence;
				uCRC = src.uCRC;
				return *this;
			}
			GAIA_CLASS_OPERATOR_COMPARE(fid, fid, FileRec);
			FILEID fid;
			__FileTreeType::const_it it;
			FILEID uSequence;
			CRCTYPE uCRC;
		};
		class FileRecSeq
		{
		public:
			GINL FileRecSeq& operator = (const FileRecSeq& src){GAIA_AST(&src != this); pFileRec = src.pFileRec; return *this;}
			GINL GAIA::BL operator == (const FileRecSeq& src) const{return pFileRec->uSequence == src.pFileRec->uSequence && pFileRec->fid == src.pFileRec->fid;}
			GINL GAIA::BL operator != (const FileRecSeq& src) const{return !this->operator == (src);}
			GINL GAIA::BL operator >= (const FileRecSeq& src) const
			{
				if(pFileRec->uSequence > src.pFileRec->uSequence)
					return GAIA::True;
				else if(pFileRec->uSequence < src.pFileRec->uSequence)
					return GAIA::False;
				else
				{
					if(pFileRec->fid >= src.pFileRec->fid)
						return GAIA::True;
					else
						return GAIA::False;
				}
			}
			GINL GAIA::BL operator <= (const FileRecSeq& src) const
			{
				if(pFileRec->uSequence < src.pFileRec->uSequence)
					return GAIA::True;
				else if(pFileRec->uSequence > src.pFileRec->uSequence)
					return GAIA::False;
				else
				{
					if(pFileRec->fid <= src.pFileRec->fid)
						return GAIA::True;
					else
						return GAIA::False;
				}
			}
			GINL GAIA::BL operator > (const FileRecSeq& src) const{return !this->operator <= (src);}
			GINL GAIA::BL operator < (const FileRecSeq& src) const{return !this->operator >= (src);}
			FileRec* pFileRec;
		};
	public:
		typedef GAIA::CONTAINER::BasicVector<GAIA::CONTAINER::Ref<NameMap>, GAIA::U32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::U32> > __NameMapType;
		typedef GAIA::CONTAINER::Pool<NameMap> __NameMapPool;
		typedef GAIA::CONTAINER::BasicVector<FileRec, FILEID, GAIA::ALGORITHM::TwiceSizeIncreaser<FILEID> > __FileRecIDListType;
		typedef GAIA::CONTAINER::BasicVector<FileRecSeq, FILEID, GAIA::ALGORITHM::TwiceSizeIncreaser<FILEID> > __FileRecSeqListType;
	private:
		GINL GAIA::GVOID init(){(*m_ftree.root()).fid = (FILEID)GINVALID; (*m_ftree.root()).mapindex = (MAPINDEX)GINVALID; m_LastMaxFileID = 0; m_pPr = GNULL;}
		GAIA::BL NameToMapIndex(const GAIA::TCH* pszFileName, MAPINDEX* pResult) const
		{
			GAIA_AST(!GAIA::ALGORITHM::stremp(pszFileName));
			if(GAIA::ALGORITHM::stremp(pszFileName))
				return GAIA::False;
			GAIA_AST(!!pResult);
			if(pResult == GNULL)
				return GAIA::False;
			FNAMEPARTLISTTYPE namelist;
			if(!this->GenerateFileNamePartList(pszFileName, namelist))
				return GAIA::False;
			NameMap f;
			f.name.reserve(MAXPATHLEN);
			NameMap* p = &f;
			GAIA_AST(namelist.size() < MAXPATHDEPTH);
			for(FNAMEPARTLISTTYPE::_sizetype x = 0; x < namelist.size(); ++x)
			{
				p->name = namelist[x].front_ptr();
				GAIA::N32 n = m_names.search(p);
				if(n == GINVALID)
					return GAIA::False;
				pResult[x] = n;
			}
			pResult[namelist.size()] = (MAPINDEX)GINVALID;
			return GAIA::True;
		}
		GAIA::BL MapIndexToName(const MAPINDEX* pResult, GAIA::TCH* pszFileName) const
		{
			GAIA_AST(!!pResult);
			if(pResult == GNULL)
				return GAIA::False;
			const MAPINDEX* p = pResult;
			GAIA::TCH* pDst = pszFileName;
			while(*p != GINVALID)
			{
				if(pDst != pszFileName)
					*pDst++ = '/';
				GAIA::ALGORITHM::strcpy(pDst, (*m_names[*p]).name.front_ptr());
				pDst += (*m_names[*p]).name.size();
				++p;
			}
			*pDst++ = 0;
			return GAIA::True;
		}
		GAIA::BL GenerateFileNamePartList(const GAIA::TCH* pszFileName, FNAMEPARTLISTTYPE& listResult) const
		{
			GAIA_AST(!GAIA::ALGORITHM::stremp(pszFileName));
			if(GAIA::ALGORITHM::stremp(pszFileName))
				return GAIA::False;
			listResult.clear();
			const GAIA::TCH* p = pszFileName;
			for(;;)
			{
				const GAIA::TCH* pNew = GAIA::ALGORITHM::stridrop(p, _T("/\\\0"));
				if(pNew != p)
				{
					if(pNew == GNULL || *pNew == 0)
					{
						GAIA::TCH sz[MAXPATHLEN];
						GAIA::ALGORITHM::strcpy(sz, p);
						if(sz[0] != 0)
							listResult.push_back(sz);
						break;
					}
					else
					{
						GAIA::TCH sz[MAXPATHLEN];
						GAIA::ALGORITHM::xmemcpy(sz, p, (pNew - p) * sizeof(GAIA::TCH));
						sz[pNew - p] = 0;
						if(sz[0] != 0)
							listResult.push_back(sz);
					}
				}
				p = pNew + 1;
			}
			return GAIA::True;
		}
		GAIA::BL GenerateMapIndex(__FileTreeType::const_it it, MAPINDEX* pMapIndex) const
		{
			if(it.empty())
				return GAIA::False;
			MAPINDEX* p = pMapIndex;
			while(!it.empty())
			{
				*p++ = (*it).mapindex;
				it = m_ftree.parent_it(it);
				if(m_ftree.root(it))
					it = m_ftree.parent_it(it);
			}
			GAIA::ALGORITHM::inverse(pMapIndex, p - 1);
			pMapIndex[p - pMapIndex] = (MAPINDEX)GINVALID;
			return GAIA::True;
		}
		GAIA::BL LoadNode(GAIA::SERIALIZER::Serializer& sr, GAIA::CONTAINER::Stack<TrieNode>& stack)
		{
			/* Load node data. */
			TrieNode tn;
			sr >> tn.fid;
			sr >> tn.mapindex;
			FileRec fr;
			sr >> fr.uSequence;
			sr >> fr.uCRC;
			fr.fid = tn.fid;
			stack.push_back(tn);

			/* Load node count. */
			__FileTreeType::__NodeTreeType::_sizetype childcnt;
			sr >> childcnt;

			/* Insert. */
			if(childcnt == 0)
			{
				if(stack.size() > 1)
				{
					GAIA_AST(stack.back().fid != GINVALID);
					m_ftree.insert(stack.front_ptr() + 1, stack.size() - 1);
					m_recids.push_back(fr);
				}
			}

			/* Load child node. */
			for(__FileTreeType::__NodeTreeType::_sizetype x = 0; x < childcnt; ++x)
				this->LoadNode(sr, stack);
			stack.pop_back();

			return GAIA::True;
		}
		GAIA::BL SaveNode(GAIA::SERIALIZER::Serializer& sr, __FileTreeType::Node& n)
		{
			/* Save node data. */
			__FileTreeType::_datatype& data = *n;
			sr << data.fid;
			sr << data.mapindex;
			FileRec fr;
			fr.fid = data.fid;
			__FileRecIDListType::_sizetype findedindex = m_recids.search(fr);
			if(findedindex != GINVALID)
			{
				sr << m_recids[findedindex].uSequence;
				sr << m_recids[findedindex].uCRC;
			}
			else
			{
				FILEID uSequence = (FILEID)GINVALID;
				sr << uSequence;
				CRCTYPE uCRC = 0;
				sr << uCRC;
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
		__NameMapPool m_namespool;
		__FileRecIDListType m_recids; // Sorted by file id.
		__FileRecSeqListType m_recseqs; // Sorted by sequence and id.
		__FileTreeType m_ftree; // Sorted by file name section.
		FILEID m_LastMaxFileID;
		GAIA::PRINT::PrintBase* m_pPr;
		GAIA::DATAPHASE::CRC32 m_crcbuilder;
	};

	/* User group class. */
	class __DWARFS_FILESHARE_API UserGroup : public GAIA::Entity
	{
	public:
		typedef GAIA::CONTAINER::BasicChars<GAIA::TCH, GAIA::U8, USERNAMELEN> __UserNameType;
		typedef GAIA::CONTAINER::BasicChars<GAIA::TCH, GAIA::U8, PASSWORDLEN> __PasswordType;
		typedef GAIA::CONTAINER::BasicChars<GAIA::TCH, GAIA::U8, GROUPNAMELEN> __GroupNameType;
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
			GAIA_CLASS_OPERATOR_COMPARE(name, name, User);
			__UserNameType name;
			__PasswordType pwd;
			__GroupRefListType refgroups;
		};
		class Group
		{
		public:
			typedef GAIA::CONTAINER::BasicSet<GAIA::CONTAINER::Ref<User>, GAIA::N32, GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32> > __UserRefListType;
		public:
			GAIA_CLASS_OPERATOR_COMPARE(name, name, Group);
			__GroupNameType name;
			__UserRefListType refusers;
			Right right;
		};
	private:
		typedef GAIA::CONTAINER::BasicSet<GAIA::CONTAINER::Ref<User>, GAIA::N32, GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32> > __UserSetType;
		typedef GAIA::CONTAINER::BasicSet<GAIA::CONTAINER::Ref<Group>, GAIA::N32, GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32> > __GroupSetType;
		typedef GAIA::CONTAINER::Pool<User> __UserPoolType;
		typedef GAIA::CONTAINER::Pool<Group> __GroupPoolType;
	public:
		GINL GAIA::BL Load(const GAIA::TCH* pszFileName)
		{
			GAIA_AST(!GAIA::ALGORITHM::stremp(pszFileName));
			if(GAIA::ALGORITHM::stremp(pszFileName))
				return GAIA::False;

			/* Construct serializer. */
			GAIA::FILESYSTEM::File fileiofile;
			GAIA::FRAMEWORK::Factory* pFactory = new GAIA::FRAMEWORK::Factory;
			GAIA::SERIALIZER::Serializer* pSerializer =
				(GAIA::SERIALIZER::Serializer*)pFactory->CreateInstance(GAIA::FRAMEWORK::CLSID_SERIALIZER, GNULL);
			GAIA::IO::FileIO* pFileIO = (GAIA::IO::FileIO*)pFactory->CreateInstance(GAIA::FRAMEWORK::CLSID_FILEIO, &fileiofile);
			if(!pFileIO->Open(pszFileName, GAIA::IO::IO::IO_TYPE_READ))
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
		GINL GAIA::BL Save(const GAIA::TCH* pszFileName)
		{
			GAIA_AST(!GAIA::ALGORITHM::stremp(pszFileName));
			if(GAIA::ALGORITHM::stremp(pszFileName))
				return GAIA::False;

			/* Construct serializer. */
			GAIA::FILESYSTEM::File fileiofile;
			GAIA::FRAMEWORK::Factory* pFactory = new GAIA::FRAMEWORK::Factory;
			GAIA::SERIALIZER::Serializer* pSerializer =
				(GAIA::SERIALIZER::Serializer*)pFactory->CreateInstance(GAIA::FRAMEWORK::CLSID_SERIALIZER, GNULL);
			GAIA::IO::FileIO* pFileIO = (GAIA::IO::FileIO*)pFactory->CreateInstance(GAIA::FRAMEWORK::CLSID_FILEIO, &fileiofile);
			if(!pFileIO->Open(pszFileName, GAIA::IO::IO::IO_TYPE_WRITE))
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
					sr << pUser->name;
					sr << pUser->pwd;
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
					sr << pGroup->name;
					sr << pGroup->right;
					Group::__UserRefListType::_sizetype user_cnt = pGroup->refusers.size();
					sr << user_cnt;
					Group::__UserRefListType::it it = pGroup->refusers.front_it();
					while(!it.empty())
					{
						User* pUser = *it;
						sr << pUser->name;
						++it;
					}
				}
				++it_g;
			}

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
			pUser->name = name;
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
			pUser->pwd = pwd;
			return GAIA::True;
		}
		GINL const GAIA::TCH* GetUserPassword(const __UserNameType& name) const
		{
			GAIA_AST(!name.empty());
			if(name.empty())
				return GNULL;
			const User* pUser = this->FindUserInternal(name);
			if(pUser == GNULL)
				return GNULL;
			return pUser->pwd;
		}
		GINL GAIA::BL DeleteUser(const __UserNameType& name)
		{
			GAIA_AST(!name.empty());
			if(name.empty())
				return GAIA::False;
			User* pUser = this->FindUserInternal(name);
			if(pUser == GNULL)
				return GAIA::False;
			User::__GroupRefListType::it it = pUser->refgroups.front_it();
			while(!it.empty())
			{
				Group* pGroup = *it;
				if(pGroup != GNULL)
					pGroup->refusers.erase(pUser);
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
					pGroup->refusers.clear();
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
			pGroup->name = name;
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
			Group::__UserRefListType::it it = pGroup->refusers.front_it();
			while(!it.empty())
			{
				User* pUser = *it;
				if(pUser != GNULL)
				{
					User::__GroupRefListType::it itu = pUser->refgroups.front_it();
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
			pGroup->right.m_bRead = bRead;
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
			bRead = pGroup->right.m_bRead;
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
			pGroup->right.m_bWrite = bWrite;
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
			bWrite = pGroup->right.m_bWrite;
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
			Group::__UserRefListType::_datatype* pFinded = pGroup->refusers.find(pUser);
			if(pFinded != GNULL)
				return GAIA::False;
			pGroup->refusers.insert(pUser);
			User::__GroupRefListType::_sizetype nFreePos = pUser->refgroups.find(GNULL, 0);
			if(nFreePos == GINVALID)
				pUser->refgroups.push_back(pGroup);
			else
				pUser->refgroups[nFreePos] = pGroup;
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
			User::__GroupRefListType::it itg = pUser->refgroups.front_it();
			if(!itg.empty())
			{
				Group* pGroupTemp = *itg;
				if(pGroupTemp == pGroup)
					*itg = GNULL;
				++itg;
			}
			pGroup->refusers.erase(pUser);
			return GAIA::True;
		}
		GINL GAIA::BL DeleteGroupUserAll(const __GroupNameType& name)
		{
			Group* pGroup = this->FindGroupInternal(name);
			if(pGroup == GNULL)
				return GAIA::False;
			Group::__UserRefListType::it it = pGroup->refusers.front_it();
			while(!it.empty())
			{
				User* pUser = *it;
				User::__GroupRefListType::it itg = pUser->refgroups.front_it();
				if(!itg.empty())
				{
					Group* pGroupTemp = *itg;
					if(pGroupTemp == pGroup)
						*itg = GNULL;
					++itg;
				}
				++it;
			}
			pGroup->refusers.clear();
			return GAIA::True;
		}
		GINL GAIA::GVOID EnumUser(__UserNameListType& result) const
		{
			__UserSetType::const_it it = m_users.const_front_it();
			while(!it.empty())
			{
				const User* pUser = *it;
				result.push_back(pUser->name);
				++it;
			}
		}
		GINL GAIA::GVOID EnumGroup(__GroupNameListType& result) const
		{
			__GroupSetType::const_it it = m_groups.const_front_it();
			while(!it.empty())
			{
				const Group* pGroup = *it;
				result.push_back(pGroup->name);
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
			User::__GroupRefListType::const_it it = pUser->refgroups.const_front_it();
			while(!it.empty())
			{
				const Group* pGroup = *it;
				if(pGroup != GNULL)
					result.push_back(pGroup->name);
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
			Group::__UserRefListType::const_it it = pGroup->refusers.const_front_it();
			while(!it.empty())
			{
				const User* pUser = *it;
				if(pUser != GNULL)
					result.push_back(pUser->name);
				++it;
			}
			return GAIA::True;
		}
	private:
		GINL const User* FindUserInternal(const __UserNameType& name) const
		{
			User finder;
			finder.name = name;
			const __UserSetType::_datatype* pFinded = m_users.find(&finder);
			if(pFinded == GNULL)
				return GNULL;
			return *pFinded;
		}
		GINL User* FindUserInternal(const __UserNameType& name)
		{
			User finder;
			finder.name = name;
			__UserSetType::_datatype* pFinded = m_users.find(&finder);
			if(pFinded == GNULL)
				return GNULL;
			return *pFinded;
		}
		GINL const Group* FindGroupInternal(const __GroupNameType& name) const
		{
			Group finder;
			finder.name = name;
			const __GroupSetType::_datatype* pFinded = m_groups.find(&finder);
			if(pFinded == GNULL)
				return GNULL;
			return *pFinded;
		}
		GINL Group* FindGroupInternal(const __GroupNameType& name)
		{
			Group finder;
			finder.name = name;
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

	/* Ban IP. */
	class __DWARFS_FILESHARE_API BanIP : public GAIA::Entity
	{
	public:
		class BanIPNode
		{
		public:
			GAIA_CLASS_OPERATOR_COMPARE(ip, ip, BanIPNode);
			GINL BanIPNode& operator = (const BanIPNode& src)
			{
				GAIA_AST(&src != this);
				ip = src.ip;
				uOccurTime = src.uOccurTime;
				uBanTime = src.uBanTime;
				return *this;
			}
		public:
			GAIA::NETWORK::IP ip;
			GAIA::U64 uOccurTime; // The time ban ip operation occured.
			GAIA::U64 uBanTime; // The time will the ip been banned. if 0xFFFFFFFFFFFFFFFF means always banned.
		};
	public:
		typedef GAIA::CONTAINER::BasicSet<BanIPNode, GAIA::N32, GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32> > __BanIPSet;
		typedef GAIA::CONTAINER::Vector<BanIPNode> __BanIPList;
	public:
		GINL BanIP(){}
		GINL ~BanIP(){}
		GINL GAIA::BL Load(const GAIA::TCH* pszFileName)
		{
			GAIA_AST(!GAIA::ALGORITHM::stremp(pszFileName));
			if(GAIA::ALGORITHM::stremp(pszFileName))
				return GAIA::False;

			/* Construct serializer. */
			GAIA::FILESYSTEM::File fileiofile;
			GAIA::FRAMEWORK::Factory* pFactory = new GAIA::FRAMEWORK::Factory;
			GAIA::SERIALIZER::Serializer* pSerializer =
				(GAIA::SERIALIZER::Serializer*)pFactory->CreateInstance(GAIA::FRAMEWORK::CLSID_SERIALIZER, GNULL);
			GAIA::IO::FileIO* pFileIO = (GAIA::IO::FileIO*)pFactory->CreateInstance(GAIA::FRAMEWORK::CLSID_FILEIO, &fileiofile);
			if(!pFileIO->Open(FILE_BANIP, GAIA::IO::IO::IO_TYPE_READ))
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
			if(uFileFlag != FILE_BANIP_FLAG)
				goto FUNCTION_END;

			GAIA::U32 uVersion;
			sr >> uVersion;
			if(uVersion > FILE_BANIP_VERSION)
				goto FUNCTION_END;

			__BanIPSet::_sizetype bansize;
			sr >> bansize;
			m_bans.clear();
			for(__BanIPSet::_sizetype x = 0; x < bansize; ++x)
			{
				__BanIPSet::_datatype t;
				sr >> t.ip;
				sr >> t.uOccurTime;
				sr >> t.uBanTime;
				m_bans.insert(t);
			}

		FUNCTION_END:
			/* Destruct serializer */
			pSerializer->Release();
			delete pFactory;
			return GAIA::True;
		}
		GINL GAIA::BL Save(const GAIA::TCH* pszFileName)
		{
			GAIA_AST(!GAIA::ALGORITHM::stremp(pszFileName));
			if(GAIA::ALGORITHM::stremp(pszFileName))
				return GAIA::False;

			/* Construct serializer. */
			GAIA::FILESYSTEM::File fileiofile;
			GAIA::FRAMEWORK::Factory* pFactory = new GAIA::FRAMEWORK::Factory;
			GAIA::SERIALIZER::Serializer* pSerializer =
				(GAIA::SERIALIZER::Serializer*)pFactory->CreateInstance(GAIA::FRAMEWORK::CLSID_SERIALIZER, GNULL);
			GAIA::IO::FileIO* pFileIO = (GAIA::IO::FileIO*)pFactory->CreateInstance(GAIA::FRAMEWORK::CLSID_FILEIO, &fileiofile);
			if(!pFileIO->Open(FILE_BANIP, GAIA::IO::IO::IO_TYPE_WRITE))
			{
				pFileIO->Release();
				pSerializer->Release();
				delete pFactory;
				return GAIA::False;
			}
			pSerializer->BindIO(pFileIO);
			pFileIO->Release();
			GAIA::SERIALIZER::Serializer& sr = *pSerializer;

			sr << FILE_BANIP_FLAG;
			sr << FILE_BANIP_VERSION;

			__BanIPSet::_sizetype bansize = m_bans.size();
			sr << bansize;
			__BanIPSet::const_it it = m_bans.const_front_it();
			while(!it.empty())
			{
				const __BanIPSet::_datatype& t = *it;
				sr << t.ip;
				sr << t.uOccurTime;
				sr << t.uBanTime;
				++it;
			}

			/* Destruct serializer */
			pSerializer->Release();
			delete pFactory;

			return GAIA::True;
		}
		GINL GAIA::BL Execute()
		{
			GAIA::BL bRet = GAIA::False;
			GAIA::U64 uCurrentTime = GAIA::TIME::clock_time();
			/* Collect timeout record. */
			{
				__BanIPSet::it it = m_bans.front_it();
				while(!it.empty())
				{
					__BanIPSet::_datatype& t = *it;
					if(t.uBanTime != GINVALID)
					{
						if(uCurrentTime - t.uOccurTime >= t.uBanTime)
							m_bans_temp.push_back(t);
					}
					++it;
				}
			}
			/* Delete timeout record. */
			{
				__BanIPList::const_it it = m_bans_temp.const_front_it();
				while(!it.empty())
				{
					m_bans.erase(*it);
					++it;
				}
				m_bans_temp.clear();
			}
			return bRet;
		}
		GINL GAIA::BL AddBanIP(const GAIA::NETWORK::IP& ip, const GAIA::U64& uBanTime)
		{
			BanIPNode n;
			n.ip = ip;
			n.uOccurTime = GAIA::TIME::clock_time();
			n.uBanTime = uBanTime;
			BanIPNode* pBan = m_bans.find(n);
			if(pBan == GNULL)
				m_bans.insert(n);
			else
				*pBan = n;
			return GAIA::True;
		}
		GINL GAIA::BL DeleteBanIP(const GAIA::NETWORK::IP& ip)
		{
			BanIPNode n;
			n.ip = ip;
			return m_bans.erase(n);
		}
		GINL GAIA::BL IsBanIP(const GAIA::NETWORK::IP& ip, GAIA::U64* pOccurTime, GAIA::U64* pBanTime) const
		{
			BanIPNode n;
			n.ip = ip;
			const BanIPNode* pBan = m_bans.find(n);
			if(pBan == GNULL)
				return GAIA::False;
			if(pOccurTime != GNULL)
				*pOccurTime = pBan->uOccurTime;
			if(pBanTime != GNULL)
				*pBanTime = pBan->uBanTime;
			return GAIA::True;
		}
		GINL GAIA::N32 GetBanIPCount() const{return m_bans.size();}
		__BanIPSet::const_it GetBanIPFrontIterator() const{return m_bans.const_front_it();}
		GINL GAIA::GVOID DeleteBanIPAll(){m_bans.clear();}
	private:
		__BanIPSet m_bans;
		__BanIPList m_bans_temp;
	};
	/* File share class. */
	class __DWARFS_FILESHARE_API FileShare : public GAIA::Entity
	{
	public:
		/* File access. */
		class __DWARFS_FILESHARE_API FileAccess
		{
		public:
			virtual ~FileAccess(){}
			virtual GAIA::BL Open(const GAIA::TCH* pszFileName, GAIA::BL bReadOnly) = 0;
			virtual GAIA::BL Close() = 0;
			virtual GAIA::BL IsOpen() const = 0;
			virtual GAIA::N64 Read(GAIA::GVOID* p, GAIA::N64 nSize) = 0;
			virtual GAIA::N64 Write(const GAIA::GVOID* p, GAIA::N64 nSize) = 0;
			virtual GAIA::BL Seek(GAIA::SEEK_TYPE st, GAIA::N64 offset) = 0;
			virtual GAIA::N64 Tell() const = 0;
			virtual GAIA::N64 Size() const = 0;
			virtual GAIA::BL Resize(GAIA::N64 size) = 0;
			virtual GAIA::BL Flush() = 0;
		};
		/* Default file access. */
		class __DWARFS_FILESHARE_API DefaultFileAccess : public FileAccess
		{
		public:
			virtual GAIA::BL Open(const GAIA::TCH* pszFileName, GAIA::BL bReadOnly)
			{
				if(bReadOnly)
					return m_file.Open(pszFileName, GAIA::FILESYSTEM::File::OPEN_TYPE_READ);
				else
				{
					if(m_file.Open(pszFileName, GAIA::FILESYSTEM::File::OPEN_TYPE_WRITE))
						return GAIA::True;
					else
						return m_file.Open(pszFileName, GAIA::FILESYSTEM::File::OPEN_TYPE_WRITE | GAIA::FILESYSTEM::File::OPEN_TYPE_CREATEALWAYS);
				}
			}
			virtual GAIA::BL Close(){return m_file.Close();}
			virtual GAIA::BL IsOpen() const{return m_file.IsOpen();}
			virtual GAIA::N64 Read(GAIA::GVOID* p, GAIA::N64 nSize){return m_file.Read(p, nSize);}
			virtual GAIA::N64 Write(const GAIA::GVOID* p, GAIA::N64 nSize){return m_file.Write(p, nSize);}
			virtual GAIA::BL Seek(GAIA::SEEK_TYPE st, GAIA::N64 offset){return m_file.Seek(st, offset);}
			virtual GAIA::N64 Tell() const{return m_file.Tell();}
			virtual GAIA::N64 Size() const{return m_file.Size();}
			virtual GAIA::BL Resize(GAIA::N64 size){return m_file.Resize(size);}
			virtual GAIA::BL Flush(){return m_file.Flush();}
		private:
			GAIA::FILESYSTEM::File m_file;
		};
		/* File access creator. */
		class __DWARFS_FILESHARE_API FileAccessCreator
		{
		public:
			virtual FileAccess* CreateFileAccess(){return new DefaultFileAccess;}
			virtual GAIA::GVOID ReleaseFileAccess(FileAccess* pFileAccess){delete pFileAccess;}
		};
		/* File share desc. */
		class __DWARFS_FILESHARE_API FileShareDesc
		{
		public:
			GINL FileShareDesc()
			{
				selfaddr.ip.FromString(_T("127.0.0.1"));
				selfaddr.uPort = MAINRECVPORT;
				pFAC = &default_fileacccreator;
			}
			GINL FileShareDesc& operator = (const FileShareDesc& src)
			{
				GAIA_AST(&src != this);
				selfaddr = src.selfaddr;
				pFAC = src.pFAC;
				return *this;
			}
			GAIA::NETWORK::NetworkAddress selfaddr;
			FileAccessCreator* pFAC;
		private:
			FileAccessCreator default_fileacccreator;
		};
		/* Network handle. */
		class __DWARFS_FILESHARE_API NHandle : public GAIA::NETWORK::NetworkHandle
		{
		public:
			GINL NHandle(){m_pFS = GNULL;}
			GINL GAIA::GVOID SetFileShare(FileShare* pFS){m_pFS = pFS;}
			GINL FileShare* GetFileShare() const{return m_pFS;}
			GINL virtual GAIA::GVOID LostConnection(const GAIA::NETWORK::NetworkAddress& na, GAIA::BL bRecvTrueSendFalse)
			{
				m_pFS->OnLostConnection(na, bRecvTrueSendFalse);
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
				GAIA::N32 nSleepRemainCnt = 0;
				for(;;)
				{
					if(m_bExitCmd)
						break;
					if(m_pFS->OnExecute())
						nSleepRemainCnt = 10;
					else
					{
						if(nSleepRemainCnt > 0)
							--nSleepRemainCnt;
					}
					if(nSleepRemainCnt == 0)
						GAIA::SYNC::xsleep(1);
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
					for(GAIA::N32 x = 0; x < 100; ++x)
					{
						if(m_bExitCmd)
							break;
						GAIA::SYNC::xsleep(100);
					}
					if(m_bExitCmd)
						break;
					m_pFS->OnHeartTick();
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
			GINL FileIDSection& operator = (const FileIDSection& src){GAIA_AST(&src != this); uStart = src.uStart; uEnd = src.uEnd; return *this;}
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
				state = STATE_DISCONNECT;
				uCmplFileCnt = 0;
				pCmplFiles = GNULL;
				uLastHeartTime = 0;
				bBeLink = GAIA::False;
			}
			GAIA_CLASS_OPERATOR_COMPARE2(na, na, bBeLink, bBeLink, NLink);
			GINL NLink& operator = (const NLink& src)
			{
				GAIA_AST(&src != this);
				na = src.na;
				state = src.state;
				uCmplFileCnt = src.uCmplFileCnt;
				pCmplFiles = src.pCmplFiles;
				uLastHeartTime = src.uLastHeartTime;
				bBeLink = src.bBeLink;
				return *this;
			}
		public:
			GAIA::NETWORK::NetworkAddress na;
			STATE state;
			FILEID uCmplFileCnt;
			GAIA::CONTAINER::Set<FileIDSection>* pCmplFiles;
			GAIA::U64 uLastHeartTime;
			GAIA::U8 bBeLink : 1;
		};
		/* Link priority object. */
		class __DWARFS_FILESHARE_API NLinkPri
		{
		public:
			NLinkPri(){}
			GAIA_CLASS_OPERATOR_COMPARE2(nlink.uCmplFileCnt, nlink.uCmplFileCnt, nlink, nlink, NLinkPri);
			GINL NLinkPri& operator = (const NLinkPri& src){GAIA_AST(&src != this); nlink = src.nlink; return *this;}
		public:
			NLink nlink;
		};
		/* FileChunkSection. */
		class __DWARFS_FILESHARE_API FileChunkSection
		{
		public:
			GINL GAIA::BL Intersect(const FileChunkSection& src)
			{
				GAIA_AST(s * 256 + ss <= e * 256 + ee);
				GAIA_AST(src.s * 256 + src.ss <= src.e * 256 + src.ee);
				if(e * 256 + ee < src.s * 256 + src.ss)
					return GAIA::False;
				if(src.e * 256 + src.ee < s * 256 + ss)
					return GAIA::False;
				return GAIA::True;
			}
			GINL GAIA::BL NextTo(const FileChunkSection& src)
			{
				GAIA_AST(s * 256 + ss <= e * 256 + ee);
				GAIA_AST(src.s * 256 + src.ss <= src.e * 256 + src.ee);
				if(e == src.s)
				{
					if(ee < src.ss)
					{
						if(ee + 1 == src.ss)
							return GAIA::True;
					}
				}
				else if(e + 1 == src.s)
				{
					if(src.ss == 0 && (SUBCHUNKINDEX)(ee + 1) == 0)
						return GAIA::True;
				}
				return GAIA::False;
			}
			GAIA_CLASS_OPERATOR_COMPARE2(s, s, ss, ss, FileChunkSection);
			GINL FileChunkSection& operator = (const FileChunkSection& src)
			{
				GAIA_AST(&src != this);
				s = src.s;
				e = src.e;
				ss = src.ss;
				ee = src.ee;
				return *this;
			}
			GINL GAIA::BL dbg_check(const FileChunkSection& src)
			{
				FILESIZETYPE begin = s * 256 + ss;
				FILESIZETYPE end = e * 256 + ee;
				FILESIZETYPE sbegin = src.s * 256 + src.ss;
				FILESIZETYPE send = src.e * 256 + src.ee;
				if(begin > end)
					return GAIA::False;
				if(sbegin > send)
					return GAIA::False;
				if(begin < sbegin)
				{
					if(end >= sbegin)
						return GAIA::False;
				}
				else if(begin > sbegin)
				{
					if(send >= begin)
						return GAIA::False;
				}
				else
					return GAIA::False;
				return GAIA::True;
			}
		public:
			CHUNKINDEX s;
			CHUNKINDEX e;
			SUBCHUNKINDEX ss;
			SUBCHUNKINDEX ee;
		};
		/* File cache. */
		class __DWARFS_FILESHARE_API FileRecCache
		{
		public:
			typedef GAIA::CONTAINER::Set<FileChunkSection> __FileChunkSectionListType;
		public:
			GINL FileRecCache(){fid = (FILEID)GINVALID; pFA = GNULL; fsize = 0; uCRC = 0; pFCSL = GNULL; bWrite = GAIA::False;}
			GAIA_CLASS_OPERATOR_COMPARE2(fid, fid, bWrite, bWrite, FileRecCache);
			GINL FileRecCache& operator = (const FileRecCache& src)
			{
				GAIA_AST(&src != this);
				fid = src.fid;
				pFA = src.pFA;
				fsize = src.fsize;
				uCRC = src.uCRC;
				pFCSL = src.pFCSL;
				bWrite = src.bWrite;
				return *this;
			}
		public:
			FILEID fid;
			FileAccess* pFA;
			FILESIZETYPE fsize;
			CRCTYPE uCRC;
			__FileChunkSectionListType* pFCSL;
			GAIA::U8 bWrite : 1;
		};
		/* Send file task. */
		class __DWARFS_FILESHARE_API FileSendTask
		{
		public:
			GINL FileSendTask(){na.Invalid(); fid = (FILEID)GINVALID; ci = 0; sci = 0; bNeedHead = GAIA::True;}
			GAIA_CLASS_OPERATOR_COMPARE2(na, na, fid, fid, FileSendTask);
			GINL FileSendTask& operator = (const FileSendTask& src)
			{
				GAIA_AST(&src != this);
				na = src.na;
				fid = src.fid;
				ci = src.ci;
				sci = src.sci;
				bNeedHead = src.bNeedHead;
				return *this;
			}
		public:
			GAIA::NETWORK::NetworkAddress na;
			FILEID fid;
			CHUNKINDEX ci;
			SUBCHUNKINDEX sci;
			GAIA::U8 bNeedHead : 1; // If true, the file head information will send to requester.
		};
		/* Chunk send task. */
		class __DWARFS_FILESHARE_API ChunkSendTask
		{
		public:
			GINL ChunkSendTask(){}
			GAIA_CLASS_OPERATOR_COMPARE3(na, na, fid, fid, ci, ci, ChunkSendTask);
			GINL ChunkSendTask& operator = (const ChunkSendTask& src)
			{
				GAIA_AST(&src != this);
				na = src.na;
				fid = src.fid;
				ci = src.ci;
				sci = src.sci;
				return *this;
			}
		public:
			GAIA::NETWORK::NetworkAddress na;
			FILEID fid;
			CHUNKINDEX ci;
			SUBCHUNKINDEX sci;
		};
		/* File write task. */
		class __DWARFS_FILESHARE_API FileWriteTask
		{
		public:
			GINL FileWriteTask(){na.Invalid(); fid = (FILEID)GINVALID; ci = 0; sci = 0; size = 0;}
			GAIA_CLASS_OPERATOR_COMPARE3(fid, fid, ci, ci, sci, sci, FileWriteTask);
			GINL FileWriteTask& operator = (const FileWriteTask& src)
			{
				GAIA_AST(&src != this);
				na = src.na;
				fid = src.fid;
				ci = src.ci;
				sci = src.sci;
				size = src.size;
				if(src.size > 0)
				{
					GAIA_AST(src.size <= SUBCHUNKSIZE);
					GAIA::ALGORITHM::xmemcpy(buf, src.buf, src.size);
				}
				return *this;
			}
		public:
			GAIA::NETWORK::NetworkAddress na;
			FILEID fid;
			CHUNKINDEX ci;
			SUBCHUNKINDEX sci;
			SUBCHUNKSIZETYPE size;
			GAIA::U8 buf[SUBCHUNKSIZE];
		};
		/* File head task. */
		class __DWARFS_FILESHARE_API FileHeadSendTask
		{
		public:
			GINL FileHeadSendTask(){na.Invalid(); fid = (FILEID)GINVALID;}
			GINL FileHeadSendTask& operator = (const FileHeadSendTask& src)
			{
				GAIA_AST(&src != this);
				na = src.na;
				fid = src.fid;
				return *this;
			}
			GAIA_CLASS_OPERATOR_COMPARE2(na, na, fid, fid, FileHeadSendTask);
		public:
			GAIA::NETWORK::NetworkAddress na;
			FILEID fid;
		};
		/* File request record. */
		class __DWARFS_FILESHARE_API FileReq
		{
		public:
			GINL FileReq()
			{
				fid = (FILEID)GINVALID;
				uUserReqTime = 0;
				uFirstReqTime = 0;
				uLastActiveTime = 0;
				uLastTimeoutSectionRequestTime = 0;
				uLastTimeoutChunkRequestTime = 0;
				uLastTimeoutReRequestTime = 0;
			}
			GINL FileReq& operator = (const FileReq& src)
			{
				GAIA_AST(&src != this);
				fid = src.fid;
				uUserReqTime = src.uUserReqTime;
				uFirstReqTime = src.uFirstReqTime;
				uLastActiveTime = src.uLastActiveTime;
				uLastTimeoutSectionRequestTime = src.uLastTimeoutSectionRequestTime;
				uLastTimeoutChunkRequestTime = src.uLastTimeoutChunkRequestTime;
				uLastTimeoutReRequestTime = src.uLastTimeoutReRequestTime;
				return *this;
			}
			GAIA_CLASS_OPERATOR_COMPARE(fid, fid, FileReq);
			FILEID fid;
			/*
			*	If the FileShare(Current module)'s user call FileShare::Request function,
			*	the time will been recorded into variable 'uUserReqTime' at that time.
			*/
			GAIA::U64 uUserReqTime;
			/*
			*	If FileShare request the file from other FileShare server at the first time,
			*	The time will been recorded into 'uFirstReqTime' and 'uLastActiveTime'.
			*	And then if the request's answer received, the 'uLastActiveTime' will been updated.
			*/
			GAIA::U64 uFirstReqTime;
			GAIA::U64 uLastActiveTime;
			/*
			*	If request timeout, and the section-based request operation occured,
			*	the 'uLastTimeoutSectionRequestTime' will been updated.
			*/
			GAIA::U64 uLastTimeoutSectionRequestTime;
			/*
			*	If request timeout, and the chunk-based request operation occured,
			*	the 'uLastTimeoutChunkRequestTime' will been updated.
			*/
			GAIA::U64 uLastTimeoutChunkRequestTime;
			/*
			*	If request timeout, and the rerequest operation occured,
			*	the 'uLastTimeoutReRequestTime' will been updated.
			*/
			GAIA::U64 uLastTimeoutReRequestTime;
		};
		/* Jump request. */
		class __DWARFS_FILESHARE_API JumpReq
		{
		public:
			GINL JumpReq(){na.Invalid();}
			GINL JumpReq& operator = (const JumpReq& src)
			{
				GAIA_AST(&src != this);
				na = src.na;
				listFID = src.listFID;
				return *this;
			}
			GAIA_CLASS_OPERATOR_COMPARE(na, na, JumpReq);
			GAIA::NETWORK::NetworkAddress na;
			FIDLIST listFID;
		};
		/* Statistics */
		class __DWARFS_FILESHARE_API Statistics
		{
		public:
			GINL Statistics(){this->init();}
			GINL GAIA::GVOID init()
			{
				fStartupTime = 0.0;
				uRequestFileCount = 0;
				uRequestFileCmplCount = 0;
				uBeRequestFileCount = 0;
				uRequestChunkCount = 0;
				uRequestChunkCmplCount = 0;
				uBeRequestChunkCount = 0;
				uRequestFileHeadCount = 0;
				uSendFileCount = 0;
				uSendCmplFileCount = 0;
				uSendChunkCount = 0;
				uRecvChunkCount = 0;
				uNSendCount = 0;
				uNRecvCount = 0;
				uNSendBytes = 0;
				uNRecvBytes = 0;
				uFrameCount = 0;
				uValidFrameCount = 0;
				uTotalCmplFileCount = 0;
				uJumpFileCount = 0;
				uBeJumpFileCount = 0;
				uCRCCheckFailedCount = 0;
				uBanIPMessageCount = 0;
				uEmptyFileCount = 0;

				uMsgRecvLoginCountR = 0;
				uMsgRecvLogoutCountR = 0;
				uMsgRecvNoopCountC = 0;
				uMsgRecvFileHeadCountR = 0;
				uMsgRecvFileCountR = 0;
				uMsgRecvFileChunkCountR = 0;
				uMsgRecvFileHeadCountA = 0;
				uMsgRecvFileChunkCountA = 0;
				uMsgRecvFileNotExistCountA = 0;
				uMsgRecvFileCmplCountA = 0;
				uMsgRecvCmplFileCountCountN = 0;
				uMsgRecvCmplFileSectionCountN = 0;
				uMsgRecvCNNCountA = 0;
				uMsgRecvLoginOKCountA = 0;
				uMsgRecvLogoutOKCountA = 0;
				uMsgRecvErrorCountA = 0;

				uMsgSendLoginCountR = 0;
				uMsgSendLogoutCountR = 0;
				uMsgSendNoopCountC = 0;
				uMsgSendFileHeadCountR = 0;
				uMsgSendFileCountR = 0;
				uMsgSendFileChunkCountR = 0;
				uMsgSendFileHeadCountA = 0;
				uMsgSendFileChunkCountA = 0;
				uMsgSendFileNotExistCountA = 0;
				uMsgSendFileCmplCountA = 0;
				uMsgSendCmplFileCountCountN = 0;
				uMsgSendCmplFileSectionCountN = 0;
				uMsgSendCNNCountA = 0;
				uMsgSendLoginOKCountA = 0;
				uMsgSendLogoutOKCountA = 0;
				uMsgSendErrorCountA = 0;

				uTimeoutSectionRequestCount = 0;
				uTimeoutChunkRequestCount = 0;
				uTimeoutReRequestCount = 0;
				uRecvRepeatedDataSize = 0;
			}
			GAIA::F64 fStartupTime;				// The time when the FileShare been startuped.
			GAIA::U64 uRequestFileCount;		// The file count current FileShare requested.
			GAIA::U64 uRequestFileCmplCount;	// The request complete count of current FileShare requested.
			GAIA::U64 uBeRequestFileCount;		// The file count been requested from other FileShare.
			GAIA::U64 uRequestChunkCount;
			GAIA::U64 uRequestChunkCmplCount;
			GAIA::U64 uBeRequestChunkCount;
			GAIA::U64 uRequestFileHeadCount;
			GAIA::U64 uSendFileCount;
			GAIA::U64 uSendCmplFileCount;
			GAIA::U64 uSendChunkCount;
			GAIA::U64 uRecvChunkCount;
			GAIA::U64 uNSendCount;
			GAIA::U64 uNRecvCount;
			GAIA::U64 uNSendBytes;
			GAIA::U64 uNRecvBytes;
			GAIA::U64 uFrameCount;
			GAIA::U64 uValidFrameCount;
			GAIA::U64 uTotalCmplFileCount;
			GAIA::U64 uJumpFileCount;
			GAIA::U64 uBeJumpFileCount;
			GAIA::U64 uCRCCheckFailedCount;
			GAIA::U64 uBanIPMessageCount;
			GAIA::U64 uEmptyFileCount;

			GAIA::U64 uMsgRecvLoginCountR;
			GAIA::U64 uMsgRecvLogoutCountR;
			GAIA::U64 uMsgRecvNoopCountC;
			GAIA::U64 uMsgRecvFileHeadCountR;
			GAIA::U64 uMsgRecvFileCountR;
			GAIA::U64 uMsgRecvFileChunkCountR;
			GAIA::U64 uMsgRecvFileHeadCountA;
			GAIA::U64 uMsgRecvFileChunkCountA;
			GAIA::U64 uMsgRecvFileNotExistCountA;
			GAIA::U64 uMsgRecvFileCmplCountA;
			GAIA::U64 uMsgRecvCmplFileCountCountN;
			GAIA::U64 uMsgRecvCmplFileSectionCountN;
			GAIA::U64 uMsgRecvCNNCountA;
			GAIA::U64 uMsgRecvLoginOKCountA;
			GAIA::U64 uMsgRecvLogoutOKCountA;
			GAIA::U64 uMsgRecvErrorCountA;

			GAIA::U64 uMsgSendLoginCountR;
			GAIA::U64 uMsgSendLogoutCountR;
			GAIA::U64 uMsgSendNoopCountC;
			GAIA::U64 uMsgSendFileHeadCountR;
			GAIA::U64 uMsgSendFileCountR;
			GAIA::U64 uMsgSendFileChunkCountR;
			GAIA::U64 uMsgSendFileHeadCountA;
			GAIA::U64 uMsgSendFileChunkCountA;
			GAIA::U64 uMsgSendFileNotExistCountA;
			GAIA::U64 uMsgSendFileCmplCountA;
			GAIA::U64 uMsgSendCmplFileCountCountN;
			GAIA::U64 uMsgSendCmplFileSectionCountN;
			GAIA::U64 uMsgSendCNNCountA;
			GAIA::U64 uMsgSendLoginOKCountA;
			GAIA::U64 uMsgSendLogoutOKCountA;
			GAIA::U64 uMsgSendErrorCountA;

			GAIA::U64 uTimeoutSectionRequestCount;
			GAIA::U64 uTimeoutChunkRequestCount;
			GAIA::U64 uTimeoutReRequestCount;
			GAIA::U64 uRecvRepeatedDataSize;
		};
		/* Performance. */
		class __DWARFS_FILESHARE_API Perf
		{
		public:
			GINL Perf(){this->init();}
			GINL GAIA::GVOID init()
			{
				fExecute = 0.0;
				fExecuteRequest = 0.0;
				fExecuteSeqRequest = 0.0;
				fExecuteFileSend = 0.0;
				fExecuteChunkSend = 0.0;
				fExecuteFileWrite = 0.0;
				fExecuteFileWriteSort = 0.0;
				fExecuteFileWriteRequest = 0.0;
				fExecuteFileWriteCombinSection = 0.0;
				fExecuteFileWriteWriteFile = 0.0;
				fExecuteFileWriteCheckComplete = 0.0;
				fExecuteFileWriteCompleteDispatch = 0.0;
				fExecuteCmpFilesNotify = 0.0;
				fExecuteRecycleLink = 0.0;
				fExecuteTimeoutSectionRequest = 0.0;
				fExecuteTimeoutChunkRequest = 0.0;
				fExecuteTimeoutReRequest = 0.0;
				fExecuteFileHeadSend = 0.0;
				fExecuteBanIP = 0.0;
				fHeartTick = 0.0;
				fOnRecv = 0.0;
				fOnRecvLoginR = 0.0;
				fOnRecvLogoutR = 0.0;
				fOnRecvNoopC = 0.0;
				fOnRecvFileHeadR = 0.0;
				fOnRecvFileR = 0.0;
				fOnRecvFileChunkR = 0.0;
				fOnRecvFileHeadA = 0.0;
				fOnRecvFileChunkA = 0.0;
				fOnRecvFileNotExistA = 0.0;
				fOnRecvFileCmplA = 0.0;
				fOnRecvCmplFileCountN = 0.0;
				fOnRecvCmplFileSectionN = 0.0;
				fOnRecvCnnA = 0.0;
				fOnRecvLoginOKA = 0.0;
				fOnRecvLogoutOKA = 0.0;
				fOnRecvErrorA = 0.0F;
				fMinFileCmplTime = +999999.0;
				fMaxFileCmplTime = -999999.0;
				fSumFileCmplTime = 0.0;
				fBanIPCheckUp = 0.0;
				fTemp1 = 0.0;
				fTemp2 = 0.0;
				fTemp3 = 0.0;
				fTemp4 = 0.0;
			}
			GAIA::F64 fExecute;
			GAIA::F64 fExecuteRequest;
			GAIA::F64 fExecuteSeqRequest;
			GAIA::F64 fExecuteFileSend;
			GAIA::F64 fExecuteChunkSend;
			GAIA::F64 fExecuteFileWrite;
			GAIA::F64 fExecuteFileWriteSort;
			GAIA::F64 fExecuteFileWriteRequest;
			GAIA::F64 fExecuteFileWriteCombinSection;
			GAIA::F64 fExecuteFileWriteWriteFile;
			GAIA::F64 fExecuteFileWriteCheckComplete;
			GAIA::F64 fExecuteFileWriteCompleteDispatch;
			GAIA::F64 fExecuteCmpFilesNotify;
			GAIA::F64 fExecuteRecycleLink;
			GAIA::F64 fExecuteTimeoutSectionRequest;
			GAIA::F64 fExecuteTimeoutChunkRequest;
			GAIA::F64 fExecuteTimeoutReRequest;
			GAIA::F64 fExecuteFileHeadSend;
			GAIA::F64 fExecuteBanIP;
			GAIA::F64 fHeartTick;
			GAIA::F64 fOnRecv;
			GAIA::F64 fOnRecvLoginR;
			GAIA::F64 fOnRecvLogoutR;
			GAIA::F64 fOnRecvNoopC;
			GAIA::F64 fOnRecvFileHeadR;
			GAIA::F64 fOnRecvFileR;
			GAIA::F64 fOnRecvFileChunkR;
			GAIA::F64 fOnRecvFileHeadA;
			GAIA::F64 fOnRecvFileChunkA;
			GAIA::F64 fOnRecvFileNotExistA;
			GAIA::F64 fOnRecvFileCmplA;
			GAIA::F64 fOnRecvCmplFileCountN;
			GAIA::F64 fOnRecvCmplFileSectionN;
			GAIA::F64 fOnRecvCnnA;
			GAIA::F64 fOnRecvLoginOKA;
			GAIA::F64 fOnRecvLogoutOKA;
			GAIA::F64 fOnRecvErrorA;
			GAIA::F64 fMinFileCmplTime;
			GAIA::F64 fMaxFileCmplTime;
			GAIA::F64 fSumFileCmplTime;
			GAIA::F64 fBanIPCheckUp;
			GAIA::F64 fTemp1;
			GAIA::F64 fTemp2;
			GAIA::F64 fTemp3;
			GAIA::F64 fTemp4;
		};
	private:
		/*
		*	[Message table]
		*	The following codes is the message and format declaration.
		*	_R_ : means request message.
		*	_A_ : means answer message.
		*	_N_	: means notify message.
		*	_C_	: means common message.
		*/
		typedef GAIA::U8 MSGIDTYPE;
		#define MSG_R_LOGIN 			((MSGIDTYPE)1)
		// username + password.
		#define MSG_R_LOGOUT			((MSGIDTYPE)2)
		// username.
		#define MSG_C_NOOP				((MSGIDTYPE)3)
		// nothing.
		#define MSG_R_FILEHEAD			((MSGIDTYPE)10)
		// fileid(FILEID).
		#define MSG_R_FILE				((MSGIDTYPE)11)
		// filecount(REQFILECOUNTTYPE) * (fileid(FILEID) + chunkindex(CHUNKINDEX)).
		#define MSG_R_FILECHUNK			((MSGIDTYPE)12)
		// fileid(FILEID) + chunkindex(CHUNKINDEX).
		#define MSG_A_FILEHEAD			((MSGIDTYPE)20)
		// fileid(FILEID) + filesize(FILESIZETYPE) + filecrccode(CRCTYPE).
		#define MSG_A_FILECHUNK			((MSGIDTYPE)21)
		// fileid(FILEID) + chunkindex(CHUNKINDEX) + subchunkindex(SUBCHUNKINDEX) + filedatasize(SUBCHUNKSIZETYPE) + filedata(void*).
		#define MSG_A_FILENOTEXIST		((MSGIDTYPE)22)
		// fileid(FILEID).
		#define MSG_A_FILECMPL			((MSGIDTYPE)40)
		// fileid(FILEID).
		#define MSG_N_CMPLFILECOUNT		((MSGIDTYPE)50)
		// filecount(FILEID).
		#define MSG_N_CMPLFILESECTION	((MSGIDTYPE)51)
		// startindex(FILEID) + endindex(FILEID).
		#define MSG_A_CNN				((MSGIDTYPE)80)
		// NetworkAddress + filecount(REQFILECOUNTTYPE) * (fileid(FILEID) + chunkindex(CHUNKINDEX)).
		#define MSG_A_LOGINOK			((MSGIDTYPE)200)
		// nothing.
		#define MSG_A_LOGOUTOK			((MSGIDTYPE)201)
		// nothing.
		#define MSG_A_ERROR				((MSGIDTYPE)250)
		// errno(ERRNO).

		/*
		*	[Error table]
		*	The following codes is the error number declaration.
		*/
		typedef GAIA::U16 ERRNO;
		#define ERRNO_NOERROR		((ERRNO)0)
		#define ERRNO_BUSY			((ERRNO)1)
		#define ERRNO_SHUTDOWN		((ERRNO)2)
		#define ERRNO_USERNAME		((ERRNO)3)
		#define ERRNO_PASSWORD		((ERRNO)4)
		#define ERRNO_INVALIDPARAM	((ERRNO)5)
		#define ERRNO_REPEATOP		((ERRNO)6)
		#define ERRNO_NOTREADY		((ERRNO)7)
		#define ERRNO_TIMEOUT		((ERRNO)8)
		const GAIA::TCH* ErrorString(ERRNO en)
		{
			static const GAIA::TCH* ERRNO_NAME[] =
			{
				_T("NoError"),
				_T("Busy"),
				_T("Shutdown"),
				_T("UserName"),
				_T("Password"),
				_T("InvalidParam"),
				_T("RepeatOp"),
				_T("NotReady"),
				_T("Timeout"),
			};
			if(en >= sizeofarray(ERRNO_NAME))
				return GNULL;
			return ERRNO_NAME[en];
		}
	private:
		typedef GAIA::CONTAINER::Set<NLink> __LinkListType;
		typedef GAIA::CONTAINER::Set<NLinkPri> __LinkPriListType;
		typedef GAIA::CONTAINER::Set<FileRecCache> __FileRecCacheListType;
		typedef GAIA::CONTAINER::Set<FileSendTask> __FileSendTaskListType;
		typedef GAIA::CONTAINER::Set<ChunkSendTask> __ChunkSendTaskListType;
		typedef GAIA::CONTAINER::Vector<GAIA::CONTAINER::Ref<FileWriteTask> > __FileWriteTaskListType;
		typedef GAIA::CONTAINER::Queue<FileReq> __FileReqQueueType;
		typedef GAIA::CONTAINER::Set<FileReq> __FileReqSetType;
		typedef GAIA::CONTAINER::Vector<FileReq> __FileReqListType;
		typedef GAIA::CONTAINER::Set<JumpReq> __JumpReqSetType;
		typedef GAIA::CONTAINER::Pool<FileWriteTask> __FileWriteTaskPoolType;
		typedef GAIA::CONTAINER::Vector<FileHeadSendTask> __FileHeadSendTaskListType;
		typedef GAIA::CONTAINER::BasicBuffer<GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32> > __MsgType;
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
			m_banip.Load(FILE_BANIP);
			m_filestate.resize(m_filelist.GetFileCount() / 8 + m_filelist.GetFileCount() % 8);
			m_pMWThread = new MainWorkThread; m_pMWThread->SetFileShare(this);
			m_pMWThread->SetStackSize(THREADSTACKSIZE);
			m_pHeartTickThread = new HeartTickThread; m_pHeartTickThread->SetFileShare(this);
			m_pHeartTickThread->SetStackSize(THREADSTACKSIZE);
			m_pNH = new NHandle; m_pNH->SetFileShare(this); m_pNH->SetSendBufSize(1024 * 1024);
		#if GAIA_OS == GAIA_OS_OSX
			m_pNH->SetRecvBufSize(1024 * 1024 * 3);
		#else
			m_pNH->SetRecvBufSize(1024 * 1024 * 100);
		#endif
			m_pNReceiver = new NReceiver; m_pNReceiver->SetFileShare(this); m_pNReceiver->SetStackSize(THREADSTACKSIZE);
			m_pNSender = new NSender; m_pNSender->SetFileShare(this); m_pNSender->SetStackSize(THREADSTACKSIZE);
			m_pNListener = new NListener; m_pNListener->SetFileShare(this); m_pNListener->SetStackSize(THREADSTACKSIZE);
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
			m_pNH->SetSelfAddress(m_desc.selfaddr);
			GAIA::NETWORK::NetworkHandle::ConnectDesc cnndesc;
			cnndesc.addr = m_desc.selfaddr;
			cnndesc.bStabilityLink = GAIA::False;
			for(GAIA::U16 uPort = 0; uPort < 10; ++uPort)
			{
				if(m_pNH->Connect(cnndesc))
				{
					m_pNH->SetSelfAddress(cnndesc.addr);
					break;
				}
				++cnndesc.addr.uPort;
			}
			if(!m_pNH->IsConnected())
			{
				m_prt << "NetworkHandle connect self failed!\n";
				return GAIA::False;
			}
			m_pNH->SetReceiver(m_pNReceiver);
			m_pNH->SetSender(m_pNSender);
			m_pNReceiver->Begin();
			m_pNSender->Begin();
			m_pMWThread->Run();
			m_pHeartTickThread->Run();
			m_statistics.fStartupTime = FSHA_PERF;
			m_statistics_last.fStartupTime = FSHA_PERF;
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
			m_filestate.clear();
			m_state = NLink::STATE_DISCONNECT;
			m_bEnableSequenceRequest = GAIA::False;
			m_uSequenceRequestIndex = 0;
			for(__FileRecCacheListType::it it = m_fcaches.front_it(); !it.empty(); ++it)
			{
				FileRecCache& frc = *it;
				if(frc.pFA != GNULL)
					m_desc.pFAC->ReleaseFileAccess(frc.pFA);
				if(frc.pFCSL != GNULL)
					delete frc.pFCSL;
			}
			m_fcaches.clear();
			m_filesendtasks.clear();
			m_chunksendtasks.clear();
			m_filewritetasks.clear();
			m_reqs.clear();
			m_reqeds.clear();
			m_jumpreqs.clear();
			m_cmplfiles.clear();
			m_fwtpool.clear();
			m_fileheadsendtasks.clear();
			m_statistics.init();
			m_statistics_last.init();
			m_perf.init();
			m_perf_last.init();
			m_listFileReqTemp.clear();
			m_listFileDeleteTemp.clear();
			m_listChunkDeleteTemp.clear();
			m_listCompleteTemp.clear();
			m_listRecycleTemp.clear();
			m_listFileCmplFileTemp.clear();
			m_listFileCmplChunkTemp.clear();
			m_listReRequestTemp.clear();
			m_FileSendMsgTemp.clear();
			m_ChunkSendMsgTemp.clear();
			m_OnReceiveMsgTemp.clear();
			m_TimeoutSectionRequestMsgTemp.clear();
			m_TimeoutChunkRequestMsgTemp.clear();
			m_RequestMsgTemp.clear();
			m_HeartTickMsgTemp.clear();
			m_ExecuteCmplFilesNotifyMsgTemp.clear();
			m_RecycleLinkMsgTemp.clear();
			m_FileHeadSendMsgTemp.clear();
			m_filewritetasks_temp.clear();
			m_fileheadsendtasks_temp.clear();
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
		GINL GAIA::GVOID SetReadRootPath(const GAIA::TCH* pszPathName){m_readroot = pszPathName;}
		GINL const GAIA::TCH* GetReadRootPath() const{return m_readroot.front_ptr();}
		GINL GAIA::GVOID SetWriteRootPath(const GAIA::TCH* pszPathName){m_writeroot = pszPathName;}
		GINL const GAIA::TCH* GetWriteRootPath() const{return m_writeroot.front_ptr();}
		GINL GAIA::GVOID SetFileCmpl(const FILEID& fileid, GAIA::BL bCmpl)
		{
			AL al(m_lr_filestate);
			if(bCmpl)
			{
				if(!m_filestate.exist(fileid))
				{
					m_filestate.set(fileid);
					++m_uCmplFileCount;
				}
			}
			else
			{
				if(m_filestate.exist(fileid))
				{
					m_filestate.reset(fileid);
					--m_uCmplFileCount;
				}
			}
		}
		GINL GAIA::BL GetFileCmpl(const FILEID& fileid) const{AL al((const_cast<FileShare*>(this))->m_lr_filestate); return m_filestate.exist(fileid);}
		GINL GAIA::GVOID SetAllFileCmpl(GAIA::BL bCmpl)
		{
			if(bCmpl)
				m_uCmplFileCount = (FILEID)m_filelist.GetFileCount();
			else
				m_uCmplFileCount = 0;
			AL al(m_lr_filestate);
			if(m_filestate.size() > 0)
				GAIA::ALGORITHM::xmemset(m_filestate.front_ptr(), bCmpl ? 0xFF : 0x00, m_filestate.size());
		}
		GINL GAIA::GVOID SetMainNAddr(const GAIA::NETWORK::NetworkAddress& na){m_mainna = na;}
		GINL const GAIA::NETWORK::NetworkAddress& GetMainNAddr() const{return m_mainna;}
		GINL GAIA::BL Request(const GAIA::NETWORK::NetworkAddress& na, const FIDLIST& listID)
		{
			GAIA_AST(!listID.empty());
			AL al(m_lr_RequestMsgTemp);
			m_RequestMsgTemp.clear();
			for(FIDLIST::const_it it = listID.const_front_it(); !it.empty(); ++it)
			{
				if(m_RequestMsgTemp.write_size() == 0)
				{
					m_RequestMsgTemp << na;
					m_RequestMsgTemp << MSG_R_FILE;
					m_RequestMsgTemp << (REQFILECOUNTTYPE)0;
				}
				GAIA_AST(GAIA::NETWORK::NetworkHandle::MAX_NOSTABILITY_SENDSIZE - m_RequestMsgTemp.write_size() >= sizeof(FILEID) + sizeof(CHUNKINDEX));
				m_RequestMsgTemp << *it;
				m_RequestMsgTemp << (CHUNKINDEX)0;
				FIDLIST::const_it itnext = it;
				++itnext;
				if(GAIA::NETWORK::NetworkHandle::MAX_NOSTABILITY_SENDSIZE - m_RequestMsgTemp.write_size() <= sizeof(FILEID) + sizeof(CHUNKINDEX) || itnext.empty())
				{
					GAIA::N32 nCount = m_RequestMsgTemp.write_size() - sizeof(na) - sizeof(MSG_R_FILE) - sizeof(REQFILECOUNTTYPE);
					nCount /= sizeof(FILEID) + sizeof(CHUNKINDEX);
					GAIA_AST(nCount < 256);
					*(REQFILECOUNTTYPE*)(m_RequestMsgTemp.front_ptr() + sizeof(na) + sizeof(MSG_R_FILE)) = (REQFILECOUNTTYPE)nCount;
					m_statistics.uRequestFileCount += nCount;
					this->Send(m_RequestMsgTemp.front_ptr(), m_RequestMsgTemp.write_size());
					m_RequestMsgTemp.clear();
				}
			}
			if(m_RequestMsgTemp.write_size() != 0)
				this->Send(m_RequestMsgTemp.front_ptr(), m_RequestMsgTemp.write_size());
			return GAIA::True;
		}
		GINL GAIA::GVOID EnableSequenceRequest(GAIA::BL bEnable){m_bEnableSequenceRequest = bEnable;}
		GINL GAIA::BL IsEnableSequenceRequest() const{return m_bEnableSequenceRequest;}
		GINL GAIA::GVOID SetMaxRequestFileCountSameTime(GAIA::N32 nCount){m_nMaxRequestFileCountSameTime = nCount;}
		GINL GAIA::N32 GetMaxRequestFileCountSameTime() const{return m_nMaxRequestFileCountSameTime;}
		GINL GAIA::GVOID EnableRecycleLink(GAIA::BL bEnable){m_bEnableRecycleLink = bEnable;}
		GINL GAIA::BL IsEnableRecycleLink() const{return m_bEnableRecycleLink;}
		GAIA::BL Command(const GAIA::TCH* pszCmd)
		{
			// Command analyze.
			if(GAIA::ALGORITHM::stremp(pszCmd))
				return GAIA::False;
			GAIA::CONTAINER::TString strCmd = pszCmd;
			GAIA::CONTAINER::Vector<GAIA::CONTAINER::TString> listPart;
			GAIA::CONTAINER::TString::_sizetype index;
			while((index = strCmd.find(' ', GINVALID)) != GINVALID)
			{
				GAIA::CONTAINER::TString strTemp = strCmd;
				strTemp.left(index);
				listPart.push_back(strTemp);
				strCmd.right(index);
			}
			if(!strCmd.empty())
				listPart.push_back(strCmd);
			strCmd.clear();

			// Execute command.
			static const GAIA::TCH* COMMAND_LIST[] =
			{
				_T("Invalid"),				_T("Invalid, format = Invalid."),
				_T("v"),					_T("show version, format = v."),
				_T("loop"),					_T("loop execute command, format = batch [command(space is -) times escape(in msecond)][no]."),
				_T("pid"),					_T("show process id, format = pid."),
				_T("clear"),				_T("clear the screen, format = clear."),
				_T("h"),					_T("show help information, format = h."),
				_T("s"),					_T("statistics, format = s."),
				_T("ss"),					_T("state, format = ss."),
				_T("save"),					_T("save config change, format = save."),
				_T("build"),				_T("build the path and generate file list, format = file_path file_ext_list."),
				_T("readroot"),				_T("set read root path, format = readroot [file_path_name]."),
				_T("writeroot"),			_T("set write root path, format = writeroot [file_path_name]."),
				_T("clearread"), 			_T("clear read root path, format = clearread."),
				_T("clearwrite"),			_T("clear write root path, format = clearwrite."),
				_T("clearconfigfile"),		_T("clear setting file, format = clearconfigfile."),

				_T("cmpl"),					_T("set/get file download complete state, format = cmpl fileid [0or1]"),
				_T("cmplall"),				_T("set all file download complete, format = cmplall 0or1."),
				_T("req"),					_T("request a file, format = req fileid"),
				_T("reqall"),				_T("request all files, format = reqall 0or1"),
				_T("reqs"),					_T("show requesting file list, format = reqs."),
				_T("reqeds"),				_T("show requested file list, format = reqeds."),

				_T("create_user"),			_T("create a new user, format = create_user user_name."),
				_T("delete_user"),			_T("delete a exist user, format = delete_user user_name."),
				_T("delete_all_user"),		_T("delete all exist users, format = delete_all_user."),
				_T("password"),				_T("set/get user's password. format = password user_name password | password user_name."),

				_T("create_group"),			_T("create a new group, format = create_group group_name."),
				_T("delete_group"),			_T("delete a exist group, format = delete_group group_name."),
				_T("delete_all_group"),		_T("delete all exist groups, format = delete_all_group."),
				_T("right"),				_T("set group right, format = group_name isread iswrite."),
				_T("add_group_user"),		_T("add a user to group, format = group_name user_name."),
				_T("delete_group_user"),	_T("delete exist user from group, format = group_name user_name."),
				_T("delete_group_alluser"),	_T("delete all exist users from group, format = group_name."),
				_T("show_users"),			_T("show all users, format = show_users."),
				_T("show_user"),			_T("show user's information, format = show_user user_name."),
				_T("show_groups"),			_T("show all groups, format = show_groups."),
				_T("show_group"),			_T("show group's information, format = show_group group_name."),
				_T("filename"),				_T("show filename by id, format = filename id."),
				_T("fileid"),				_T("show fileid by filename, format = fileid filename."),
				_T("files"),				_T("show file in the path, format = files."),

				_T("ban"),					_T("ban ip address, format = ban timeinsecond ipstart [ipend]."),
				_T("unban"),				_T("unban ip address, format = unban ipstart [ipend]."),
				_T("unbanall"),				_T("unban all ip address, format = unbanall."),
				_T("showbanips"),			_T("show all ban ips, format = showbanips."),

				_T("login"),				_T("login to remote node, format = login username password ip port."),
				_T("logout"),				_T("logout from remote node, format = logout username ip port."),

				_T("recycle_link"),			_T("enable recycle link, format = recycle_link 0|1"),
				_T("dspeed"),				_T("set download speed, format = dspeed [speedinbytes]."),
				_T("uspeed"),				_T("set upload speed, format = uspeed [speedinbytes]."),

				_T("l"),					_T("show link state, format = l."),
				_T("pril"),					_T("show priority link state, format = pril."),
				_T("p"),					_T("show performance, format = p."),
				_T("f"),					_T("show file cache information, format = f."),

				_T("sreset"),				_T("reset statistics, format = sreset."),
				_T("preset"),				_T("reset performance, format = preset."),

				_T("t_genfile"),			_T("test:generate sample data file, format = t_genfile."),
				_T("t_watch"),				_T("test:enable or disable watch, format = t_watch 0|1."),
				_T("t_watchfile"),			_T("test:watch file status, format = t_watchfile fileid."),
				_T("t_watchip"),			_T("test:watch ip status, format = t_watchip xxx.xxx.xxx.xxx."),
				_T("t_watchport"),			_T("test:watch port status, format = t_watchport port."),
			};
			GAIA_ENUM_BEGIN(COMMAND_LIST)
				CMD_VERSION,
				CMD_LOOP,
				CMD_PID,
				CMD_CLEAR,
				CMD_HELP,
				CMD_STATISTICS,
				CMD_STATE,
				CMD_SAVE,
				CMD_BUILD,
				CMD_READROOT,
				CMD_WRITEROOT,
				CMD_CLEARREAD,
				CMD_CLEARWRITE,
				CMD_CLEARCONFIGFILE,

				CMD_CMPL,
				CMD_CMPLALL,
				CMD_REQUEST,
				CMD_REQUESTALL,
				CMD_REQS,
				CMD_REQEDS,

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

				CMD_BANIP,
				CMD_UNBANIP,
				CMD_UNBANIPALL,
				CMD_SHOWBANIPS,

				CMD_LOGIN,
				CMD_LOGOUT,

				CMD_RECYCLELINK,
				CMD_DOWNLOADSPEED,
				CMD_UPLOADSPEED,

				CMD_LINK,
				CMD_PRIORITYLINK,
				CMD_PERF,
				CMD_FILECACHEINFO,

				CMD_STATISTICSRESET,
				CMD_PERFRESET,

				CMD_T_GENFILE,
				CMD_T_WATCH,
				CMD_T_WATCHFILE,
				CMD_T_WATCHIP,
				CMD_T_WATCHPORT,
			GAIA_ENUM_END(COMMAND_LIST)
			#define CMD(e) (listPart[0] == COMMAND_LIST[(e) * 2])
			#define CMDFAILED do{m_prt << "Failed!\n";}while(GAIA::ALWAYSFALSE)
			if(listPart.empty())
				return GAIA::False;
			if(CMD(CMD_VERSION))
			{
				if(listPart.size() == 1)
				{
					AL alprt(m_lr_prt);
					m_prt << VERSION_STRING << "\n";
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_LOOP))
			{
				if(listPart.size() == 1)
				{
					if(m_szLoopCmd[0] == 0)
					{
						AL alprt(m_lr_prt);
						m_prt << "No loop command!" << "\n";
					}
				}
				else if(listPart.size() == 2)
				{
					if(listPart[1] == _T("no"))
						m_szLoopCmd[0] = 0;
					else
						CMDFAILED;
				}
				else if(listPart.size() == 4)
				{
					GAIA::ALGORITHM::strcat(m_szLoopCmd, listPart[1].front_ptr());
					m_uLoopCmdTimes = listPart[2];
					m_uLoopCmdEscape = listPart[3];
					m_uLoopCmdLastFireTime = 0;
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_PID))
			{
				GAIA::UM uProcessID = GAIA::PROCESS::processid();
				AL alprt(m_lr_prt);
				m_prt << "Current Process ID = " << uProcessID << "\n";
			}
			else if(CMD(CMD_CLEAR))
			{
				if(listPart.size() == 1)
				{
					AL alprt(m_lr_prt);
					m_prt.clear_screen();
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_HELP))
			{
				AL alprt(m_lr_prt);
				GAIA::PRINT::PrintFormat pfold, pfnew;
				m_prt >> pfold >> pfnew;
				pfnew.align(24);
				pfnew.left(GAIA::True);
				for(GAIA::N32 x = 0; x < sizeof(COMMAND_LIST) / sizeof(const GAIA::TCH*) / 2; ++x)
					m_prt << "[" << x << "] " << pfnew << COMMAND_LIST[x * 2] << pfold << "Info: " << COMMAND_LIST[x * 2 + 1] << "\n";
			}
			else if(CMD(CMD_STATISTICS))
			{
				AL alprt(m_lr_prt);
				m_prt << "WorkTime = " << FSHA_PERF - m_statistics.fStartupTime << "(" << m_statistics.fStartupTime - m_statistics_last.fStartupTime << ")" << "\n";
				m_prt << "\n";
				m_prt << "ReqFileCount = " << m_statistics.uRequestFileCount << "(" << m_statistics.uRequestFileCount - m_statistics_last.uRequestFileCount << ")" << "\n";
				m_prt << "ReqCmplFileCount = " << m_statistics.uRequestFileCmplCount << "(" << m_statistics.uRequestFileCmplCount - m_statistics_last.uRequestFileCmplCount << ")" << "\n";
				m_prt << "BeReqFileCount = " << m_statistics.uBeRequestFileCount << "(" << m_statistics.uBeRequestFileCount - m_statistics_last.uBeRequestFileCount << ")" << "\n";
				m_prt << "ReqChunkCount = " << m_statistics.uRequestChunkCount << "(" << m_statistics.uRequestChunkCount - m_statistics_last.uRequestChunkCount << ")" << "\n";
				m_prt << "ReqChunkCmplCount = " << m_statistics.uRequestChunkCmplCount << "(" << m_statistics.uRequestChunkCmplCount - m_statistics_last.uRequestChunkCmplCount << ")" << "\n";
				m_prt << "BeReqChunkCount = " << m_statistics.uBeRequestChunkCount << "(" << m_statistics.uBeRequestChunkCount - m_statistics_last.uBeRequestChunkCount << ")" << "\n";
				m_prt << "ReqFileHeadCount = " << m_statistics.uRequestFileHeadCount << "(" << m_statistics.uRequestFileHeadCount - m_statistics_last.uRequestFileHeadCount << ")" << "\n";
				m_prt << "\n";
				m_prt << "SendFileCount = " << m_statistics.uSendFileCount << "(" << m_statistics.uSendFileCount - m_statistics_last.uSendFileCount << ")" << "\n";
				m_prt << "SendCmplFileCount = " << m_statistics.uSendCmplFileCount << "(" << m_statistics.uSendCmplFileCount - m_statistics_last.uSendCmplFileCount << ")" << "\n";
				m_prt << "SendChunkCount = " << m_statistics.uSendChunkCount << "(" << m_statistics.uSendChunkCount - m_statistics_last.uSendChunkCount << ")" << "\n";
				m_prt << "RecvChunkCount = " << m_statistics.uRecvChunkCount << "(" << m_statistics.uRecvChunkCount - m_statistics_last.uRecvChunkCount << ")" << "\n";
				m_prt << "\n";
				m_prt << "NSendCount = " << m_statistics.uNSendCount << "(" << m_statistics.uNSendCount - m_statistics_last.uNSendCount << ")" << "\n";
				m_prt << "NRecvCount = " << m_statistics.uNRecvCount << "(" << m_statistics.uNRecvCount - m_statistics_last.uNRecvCount << ")" << "\n";
				m_prt << "NSendBytes = " << m_statistics.uNSendBytes << "(" << m_statistics.uNSendBytes - m_statistics_last.uNSendBytes << ")" << "\n";
				m_prt << "NRecvBytes = " << m_statistics.uNRecvBytes << "(" << m_statistics.uNRecvBytes - m_statistics_last.uNRecvBytes << ")" << "\n";
				m_prt << "\n";
				m_prt << "FrameCount = " << m_statistics.uFrameCount << "(" << m_statistics.uFrameCount - m_statistics_last.uFrameCount << ")" << "\n";
				m_prt << "ValidFrameCount = " << m_statistics.uValidFrameCount << "(" << m_statistics.uValidFrameCount - m_statistics_last.uValidFrameCount << ")" << "\n";
				m_prt << "\n";
				m_prt << "TotalCmplFileCount = " << m_statistics.uTotalCmplFileCount << "(" << (GAIA::F64)m_statistics.uTotalCmplFileCount / (GAIA::F64)(m_filelist.GetFileCount() * m_links.size()) << ")" << "\n";
				m_prt << "JumpFileCount = " << m_statistics.uJumpFileCount << "(" << m_statistics.uJumpFileCount - m_statistics_last.uJumpFileCount << ")" << "\n";
				m_prt << "BeJumpFileCount = " << m_statistics.uBeJumpFileCount << "(" << m_statistics.uBeJumpFileCount - m_statistics_last.uBeJumpFileCount << ")" << "\n";
				m_prt << "CRCCheckFailedCount = " << m_statistics.uCRCCheckFailedCount << "(" << m_statistics.uCRCCheckFailedCount - m_statistics_last.uCRCCheckFailedCount << ")" << "\n";
				m_prt << "BanIPMessageCount = " << m_statistics.uBanIPMessageCount << "(" << m_statistics.uBanIPMessageCount - m_statistics_last.uBanIPMessageCount << ")" << "\n";
				m_prt << "EmptyFileCount = " << m_statistics.uEmptyFileCount << "(" << m_statistics.uEmptyFileCount - m_statistics_last.uEmptyFileCount << ")" << "\n";
				m_prt << "\n";
				m_prt << "MsgRecvLoginCountR = " << m_statistics.uMsgRecvLoginCountR << "(" << m_statistics.uMsgRecvLoginCountR - m_statistics_last.uMsgRecvLoginCountR << ")" << "\n";
				m_prt << "MsgRecvLogoutCountR = " << m_statistics.uMsgRecvLogoutCountR << "(" << m_statistics.uMsgRecvLogoutCountR - m_statistics_last.uMsgRecvLogoutCountR << ")" << "\n";
				m_prt << "MsgRecvNoopCountC = " << m_statistics.uMsgRecvNoopCountC << "(" << m_statistics.uMsgRecvNoopCountC - m_statistics_last.uMsgRecvNoopCountC << ")" << "\n";
				m_prt << "MsgRecvFileHeadCountR = " << m_statistics.uMsgRecvFileHeadCountR << "(" << m_statistics.uMsgRecvFileHeadCountR - m_statistics_last.uMsgRecvFileHeadCountR << ")" << "\n";
				m_prt << "MsgRecvFileCountR = " << m_statistics.uMsgRecvFileCountR << "(" << m_statistics.uMsgRecvFileCountR - m_statistics_last.uMsgRecvFileCountR << ")" << "\n";
				m_prt << "MsgRecvFileChunkCountR = " << m_statistics.uMsgRecvFileChunkCountR << "(" << m_statistics.uMsgRecvFileChunkCountR - m_statistics_last.uMsgRecvFileChunkCountR << ")" << "\n";
				m_prt << "MsgRecvFileHeadCountA = " << m_statistics.uMsgRecvFileHeadCountA << "(" << m_statistics.uMsgRecvFileHeadCountA - m_statistics_last.uMsgRecvFileHeadCountA << ")" << "\n";
				m_prt << "MsgRecvFileChunkCountA = " << m_statistics.uMsgRecvFileChunkCountA << "(" << m_statistics.uMsgRecvFileChunkCountA - m_statistics_last.uMsgRecvFileChunkCountA << ")" << "\n";
				m_prt << "MsgRecvFileNotExistCountA = " << m_statistics.uMsgRecvFileNotExistCountA << "(" << m_statistics.uMsgRecvFileNotExistCountA - m_statistics_last.uMsgRecvFileNotExistCountA << ")" << "\n";
				m_prt << "MsgRecvFileCmplCountA = " << m_statistics.uMsgRecvFileCmplCountA << "(" << m_statistics.uMsgRecvFileCmplCountA - m_statistics_last.uMsgRecvFileCmplCountA << ")" << "\n";
				m_prt << "MsgRecvCmplFileCountN = " << m_statistics.uMsgRecvCmplFileCountCountN << "(" << m_statistics.uMsgRecvCmplFileCountCountN - m_statistics_last.uMsgRecvCmplFileCountCountN << ")" << "\n";
				m_prt << "MsgRecvCmplFileSectionCountN = " << m_statistics.uMsgRecvCmplFileSectionCountN << "(" << m_statistics.uMsgRecvCmplFileSectionCountN - m_statistics_last.uMsgRecvCmplFileSectionCountN << ")" << "\n";
				m_prt << "MsgRecvCNNCountA = " << m_statistics.uMsgRecvCNNCountA << "(" << m_statistics.uMsgRecvCNNCountA - m_statistics_last.uMsgRecvCNNCountA << ")" << "\n";
				m_prt << "MsgRecvLoginOKCountA = " << m_statistics.uMsgRecvLoginOKCountA << "(" << m_statistics.uMsgRecvLoginOKCountA - m_statistics_last.uMsgRecvLoginOKCountA << ")" << "\n";
				m_prt << "MsgRecvLogoutOKCountA = " << m_statistics.uMsgRecvLogoutOKCountA << "(" << m_statistics.uMsgRecvLogoutOKCountA - m_statistics_last.uMsgRecvLogoutOKCountA << ")" << "\n";
				m_prt << "MsgRecvErrorCountA = " << m_statistics.uMsgRecvErrorCountA << "(" << m_statistics.uMsgRecvErrorCountA - m_statistics_last.uMsgRecvErrorCountA << ")" << "\n";
				m_prt << "\n";
				m_prt << "MsgSendLoginCountR = " << m_statistics.uMsgSendLoginCountR << "(" << m_statistics.uMsgSendLoginCountR - m_statistics_last.uMsgSendLoginCountR << ")" << "\n";
				m_prt << "MsgSendLogoutCountR = " << m_statistics.uMsgSendLogoutCountR << "(" << m_statistics.uMsgSendLogoutCountR - m_statistics_last.uMsgSendLogoutCountR << ")" << "\n";
				m_prt << "MsgSendNoopCountC = " << m_statistics.uMsgSendNoopCountC << "(" << m_statistics.uMsgSendNoopCountC - m_statistics_last.uMsgSendNoopCountC << ")" << "\n";
				m_prt << "MsgSendFileHeadCountR = " << m_statistics.uMsgSendFileHeadCountR << "(" << m_statistics.uMsgSendFileHeadCountR - m_statistics_last.uMsgSendFileHeadCountR << ")" << "\n";
				m_prt << "MsgSendFileCountR = " << m_statistics.uMsgSendFileCountR << "(" << m_statistics.uMsgSendFileCountR - m_statistics_last.uMsgSendFileCountR << ")" << "\n";
				m_prt << "MsgSendFileChunkCountR = " << m_statistics.uMsgSendFileChunkCountR << "(" << m_statistics.uMsgSendFileChunkCountR - m_statistics_last.uMsgSendFileChunkCountR << ")" << "\n";
				m_prt << "MsgSendFileHeadCountA = " << m_statistics.uMsgSendFileHeadCountA << "(" << m_statistics.uMsgSendFileHeadCountA - m_statistics_last.uMsgSendFileHeadCountA << ")" << "\n";
				m_prt << "MsgSendFileChunkCountA = " << m_statistics.uMsgSendFileChunkCountA << "(" << m_statistics.uMsgSendFileChunkCountA - m_statistics_last.uMsgSendFileChunkCountA << ")" << "\n";
				m_prt << "MsgSendFileNotExistCountA = " << m_statistics.uMsgSendFileNotExistCountA << "(" << m_statistics.uMsgSendFileNotExistCountA - m_statistics_last.uMsgSendFileNotExistCountA << ")" << "\n";
				m_prt << "MsgSendFileCmplCountA = " << m_statistics.uMsgSendFileCmplCountA << "(" << m_statistics.uMsgSendFileCmplCountA - m_statistics_last.uMsgSendFileCmplCountA << ")" << "\n";
				m_prt << "MsgSendCmplFileCountN = " << m_statistics.uMsgSendCmplFileCountCountN << "(" << m_statistics.uMsgSendCmplFileCountCountN - m_statistics_last.uMsgSendCmplFileCountCountN << ")" << "\n";
				m_prt << "MsgSendCmplFileSectionCountN = " << m_statistics.uMsgSendCmplFileSectionCountN << "(" << m_statistics.uMsgSendCmplFileSectionCountN - m_statistics_last.uMsgSendCmplFileSectionCountN << ")" << "\n";
				m_prt << "MsgSendCNNCountA = " << m_statistics.uMsgSendCNNCountA << "(" << m_statistics.uMsgSendCNNCountA - m_statistics_last.uMsgSendCNNCountA << ")" << "\n";
				m_prt << "MsgSendLoginOKCountA = " << m_statistics.uMsgSendLoginOKCountA << "(" << m_statistics.uMsgSendLoginOKCountA - m_statistics_last.uMsgSendLoginOKCountA << ")" << "\n";
				m_prt << "MsgSendLogoutOKCountA = " << m_statistics.uMsgSendLogoutOKCountA << "(" << m_statistics.uMsgSendLogoutOKCountA - m_statistics_last.uMsgSendLogoutOKCountA << ")" << "\n";
				m_prt << "MsgSendErrorCountA = " << m_statistics.uMsgSendErrorCountA << "(" << m_statistics.uMsgSendErrorCountA - m_statistics_last.uMsgSendErrorCountA << ")" << "\n";
				m_prt << "\n";
				m_prt << "TimeoutSectionRequestCount = " << m_statistics.uTimeoutSectionRequestCount << "(" << m_statistics.uTimeoutSectionRequestCount - m_statistics_last.uTimeoutSectionRequestCount << ")" << "\n";
				m_prt << "TimeoutChunkRequestCount = " << m_statistics.uTimeoutChunkRequestCount << "(" << m_statistics.uTimeoutChunkRequestCount - m_statistics_last.uTimeoutChunkRequestCount << ")" << "\n";
				m_prt << "TimeoutReRequestCount = " << m_statistics.uTimeoutReRequestCount << "(" << m_statistics.uTimeoutReRequestCount - m_statistics_last.uTimeoutReRequestCount << ")" << "\n";
				m_prt << "RecvRepeatedDataSize = " << m_statistics.uRecvRepeatedDataSize << "(" << m_statistics.uRecvRepeatedDataSize - m_statistics_last.uRecvRepeatedDataSize << ")" << "\n";
				m_prt << "\n";
				m_prt << "OwnFile = " << m_uCmplFileCount << "/" << m_filelist.GetFileCount() << "\n";

				GAIA::ALGORITHM::xmemcpy(&m_statistics_last, &m_statistics, sizeof(m_statistics));
			}
			else if(CMD(CMD_STATE))
			{
				AL alprt(m_lr_prt);
				// Global constants.
				{
					m_prt << "[Global constants information.]" << "\n";
					m_prt << "MAXPATHDEPTH = " << MAXPATHDEPTH << "\n";
					m_prt << "MAXPATHLEN = " << MAXPATHLEN << "\n";
					m_prt << "MAINRECVPORT = " << MAINRECVPORT << "\n";
					m_prt << "CHUNKSIZE = " << CHUNKSIZE << "\n";
					m_prt << "SUBCHUNKSIZE = " << SUBCHUNKSIZE << "\n";
					m_prt << "THREADSTACKSIZE = " << THREADSTACKSIZE << "\n";
					m_prt << "USERNAMELEN = " << USERNAMELEN << "\n";
					m_prt << "PASSWORDLEN = " << PASSWORDLEN << "\n";
					m_prt << "GROUPNAMELEN = " << GROUPNAMELEN << "\n";
					m_prt << "FILE_USERGROUP = " << FILE_USERGROUP << "\n";
					m_prt << "FILE_USERGROUP_FLAG = " << FILE_USERGROUP_FLAG << "\n";
					m_prt << "FILE_USERGROUP_VERSION = " << FILE_USERGROUP_VERSION << "\n";
					m_prt << "FILE_FILELIST = " << FILE_FILELIST << "\n";
					m_prt << "FILE_FILELIST_FLAG = " << FILE_FILELIST_FLAG << "\n";
					m_prt << "FILE_FILELIST_VERSION = " << FILE_FILELIST_VERSION << "\n";
					m_prt << "FILE_BANIP = " << FILE_BANIP << "\n";
					m_prt << "FILE_BANIP_FLAG = " << FILE_BANIP_FLAG << "\n";
					m_prt << "FILE_BANIP_VERSION = " << FILE_BANIP_VERSION << "\n";
					m_prt << "DEFAULTMAXREQFILECOUNTSAMETIME = " << DEFAULTMAXREQFILECOUNTSAMETIME << "\n";
					m_prt << "CMPLFILESNOTIFYFREQ = " << CMPLFILESNOTIFYFREQ << "\n";
					m_prt << "LINKRECYCLETIME = " << LINKRECYCLETIME << "\n";
					m_prt << "JUMPDISTANCE = " << JUMPDISTANCE << "\n";
					m_prt << "MAINJUMPODDS = " << MAINJUMPODDS << "\n";
					m_prt << "SUBJUMPODDS = " << SUBJUMPODDS << "\n";
					m_prt << "REQUESTTIMEOUTTIME = " << REQUESTTIMEOUTTIME << "\n";
					m_prt << "REQUESTCMPLFILESNOTIFYTIME = " << REQUESTCMPLFILESNOTIFYTIME << "\n";
					m_prt << "SINGLECHUNKREQUESTLIMIT = " << SINGLECHUNKREQUESTLIMIT << "\n";
					m_prt << "MAXCHUNKREQUESTCOUNTPERDISPATCH = " << MAXCHUNKREQUESTCOUNTPERDISPATCH << "\n";
					m_prt << "JUMPOFFSETFILESCOUNT = " << JUMPOFFSETFILESCOUNT << "\n";
					m_prt << "BATCHCHUNKSENDCOUNT = " << BATCHCHUNKSENDCOUNT << "\n";
					m_prt << "BANIPDISPATCHTIME = " << BANIPDISPATCHTIME << "\n";
					m_prt << "\n";
				}
				// Global variable.
				{
					m_prt << "[Global variables information]" << "\n";
					m_prt << "m_readroot = " << m_readroot.front_ptr() << "\n";
					m_prt << "m_writeroot = " << m_writeroot.front_ptr() << "\n";
					m_prt << "m_uUSpeed = " << m_uUSpeed << "\n";
					m_prt << "m_uDSpeed = " << m_uDSpeed << "\n";
					m_prt << "m_uCmplFileCount = " << m_uCmplFileCount << "\n";
					m_prt << "m_state = " << m_state << "\n";
					m_prt << "m_bEnableSequenceRequest = " << m_bEnableSequenceRequest << "\n";
					m_prt << "m_uSequenceRequestIndex = " << m_uSequenceRequestIndex << "\n";
					m_prt << "m_nMaxRequestFileCountSameTime = " << m_nMaxRequestFileCountSameTime << "\n";
					m_prt << "m_bEnableRecycleLink = " << m_bEnableRecycleLink << "\n";
					m_prt << "m_uLastNotifyCmplTime = " << m_uLastNotifyCmplTime << "\n";
					m_prt << "\n";
				}
				// Main address and self address.
				{
					m_prt << "[IP address information]" << "\n";
					GAIA::TCH szText[128];
					m_mainna.ToString(szText);
					m_prt << "MainAddress = " << szText << "\n";
					m_pNH->GetSelfNetAddress().ToString(szText);
					m_prt << "SelfAddress = " << szText << "\n";
					m_prt << "\n";
				}
			}
			else if(CMD(CMD_SAVE))
			{
				if(listPart.size() == 1)
				{
					AL al1(m_lr_usergroup);
					AL al2(m_lr_filelist);
					if(!m_filelist.Save(FILE_FILELIST))
						CMDFAILED;
					if(!m_usergroup.Save(FILE_USERGROUP))
						CMDFAILED;
					if(!m_banip.Save(FILE_BANIP))
						CMDFAILED;
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_BUILD))
			{
				if(listPart.size() == 3)
				{
					const GAIA::TCH* psz = _T("");
					if(listPart[2] != _T("NULL"))
						psz = listPart[2].front_ptr();
					AL al(m_lr_filelist);
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
				{
					AL alprt(m_lr_prt);
					m_prt << m_readroot.front_ptr() << "\n";
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_WRITEROOT))
			{
				if(listPart.size() == 2)
					m_writeroot = listPart[1].front_ptr();
				else if(listPart.size() == 1)
				{
					AL alprt(m_lr_prt);
					m_prt << m_writeroot.front_ptr() << "\n";
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_CLEARREAD))
			{
				if(listPart.size() == 1)
				{
					GAIA::FILESYSTEM::Directory dir;
					dir.Remove(m_readroot, GAIA::True);
					dir.Create(m_readroot, GAIA::True);
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_CLEARWRITE))
			{
				if(listPart.size() == 1)
				{
					GAIA::FILESYSTEM::Directory dir;
					dir.Remove(m_writeroot, GAIA::True);
					dir.Create(m_writeroot, GAIA::True);
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_CLEARCONFIGFILE))
			{
				if(listPart.size() == 1)
				{
					GAIA::FILESYSTEM::Directory dir;
					dir.RemoveFile(FILE_USERGROUP);
					dir.RemoveFile(FILE_FILELIST);
					dir.RemoveFile(FILE_BANIP);
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_CMPL))
			{
				if(listPart.size() == 3)
					this->SetFileCmpl((FILEID)listPart[1], (GAIA::BL)(GAIA::N32)listPart[2]);
				else
					CMDFAILED;
			}
			else if(CMD(CMD_CMPLALL))
			{
				if(listPart.size() == 2)
					this->SetAllFileCmpl((GAIA::BL)(GAIA::N32)listPart[1]);
				else
					CMDFAILED;
			}
			else if(CMD(CMD_REQUEST))
			{
				if(listPart.size() == 2)
				{
					AL al(m_lr_reqs);
					FileReq fr;
					fr.fid = listPart[1];
					fr.uUserReqTime = GAIA::TIME::tick_time();
					m_reqs.push_back(fr);
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_REQUESTALL))
			{
				if(listPart.size() == 2)
				{
					m_uSequenceRequestIndex = 0;
					this->EnableSequenceRequest((GAIA::BL)(GAIA::N32)listPart[1]);
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_REQS))
			{
				if(listPart.size() == 1)
				{
					AL al(m_lr_reqs);
					__FileReqQueueType::it it = m_reqs.front_it();
					GAIA::N32 nIndex = 0;
					GAIA::U64 uCurrentTime = GAIA::TIME::tick_time();
					while(!it.empty())
					{
						FileReq& fr = *it;
						FILESIZETYPE fsize;
						FILESIZETYPE fcmplsize;
						{
							AL al1(m_lr_fcaches);
							FileRecCache frc;
							frc.fid = fr.fid;
							frc.bWrite = GAIA::True;
							FileRecCache* pFRC = m_fcaches.find(frc);
							if(pFRC == GNULL)
							{
								fsize = 0;
								fcmplsize = 0;
							}
							else
							{
								fsize = pFRC->fsize;
								fcmplsize = this->GetFileCacheCompleteSize(*pFRC);
							}
						}
						AL alprt(m_lr_prt);
						m_prt << "[" << nIndex++ << "] FID=" << fr.fid <<
							" Size=" << fsize <<
							" CmplSize=" << fcmplsize <<
							" UserReqTime=" << (GAIA::F64)(uCurrentTime - fr.uUserReqTime) * 0.001 * 0.001 <<
							" FirstReqTime=" << (GAIA::F64)(uCurrentTime - fr.uFirstReqTime) * 0.001 * 0.001 <<
							" LastActiveTime=" << (GAIA::F64)(uCurrentTime - fr.uLastActiveTime) * 0.001 * 0.001 << "\n";
						++it;
					}
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_REQEDS))
			{
				if(listPart.size() == 1)
				{
					AL al(m_lr_reqeds);
					__FileReqSetType::it it = m_reqeds.front_it();
					GAIA::N32 nIndex = 0;
					GAIA::U64 uCurrentTime = GAIA::TIME::tick_time();
					while(!it.empty())
					{
						FileReq& fr = *it;
						FILESIZETYPE fsize;
						FILESIZETYPE fcmplsize;
						{
							AL al1(m_lr_fcaches);
							FileRecCache frc;
							frc.fid = fr.fid;
							frc.bWrite = GAIA::True;
							FileRecCache* pFRC = m_fcaches.find(frc);
							if(pFRC == GNULL)
							{
								fsize = 0;
								fcmplsize = 0;
							}
							else
							{
								fsize = pFRC->fsize;
								fcmplsize = this->GetFileCacheCompleteSize(*pFRC);
							}
						}
						AL alprt(m_lr_prt);
						m_prt << "[" << nIndex++ << "] FID=" << fr.fid <<
							" Size=" << fsize <<
							" CmplSize=" << fcmplsize <<
							" UserReqTime=" << (GAIA::F64)(uCurrentTime - fr.uUserReqTime) * 0.001 * 0.001 <<
							" FirstReqTime=" << (GAIA::F64)(uCurrentTime - fr.uFirstReqTime) * 0.001 * 0.001 <<
							" LastActiveTime=" << (GAIA::F64)(uCurrentTime - fr.uLastActiveTime) * 0.001 * 0.001 << "\n";
						++it;
					}
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_CREATEUSER))
			{
				if(listPart.size() == 2)
				{
					AL al(m_lr_usergroup);
					if(!m_usergroup.AddUser(listPart[1]))
						CMDFAILED;
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_DELETEUSER))
			{
				if(listPart.size() == 2)
				{
					AL al(m_lr_usergroup);
					if(!m_usergroup.DeleteUser(listPart[1]))
						CMDFAILED;
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_DELETEALLUSER))
			{
				if(listPart.size() == 1)
				{
					AL al(m_lr_usergroup);
					m_usergroup.DeleteUserAll();
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_PASSWORD))
			{
				if(listPart.size() == 3)
				{
					AL al(m_lr_usergroup);
					if(!m_usergroup.SetUserPassword(listPart[1], listPart[2]))
						CMDFAILED;
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_CREATEGROUP))
			{
				if(listPart.size() == 2)
				{
					AL al(m_lr_usergroup);
					if(!m_usergroup.AddGroup(listPart[1]))
						CMDFAILED;
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_DELETEGROUP))
			{
				if(listPart.size() == 2)
				{
					AL al(m_lr_usergroup);
					if(!m_usergroup.DeleteGroup(listPart[1]))
						CMDFAILED;
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_DELETEALLGROUP))
			{
				if(listPart.size() == 1)
				{
					AL al(m_lr_usergroup);
					m_usergroup.DeleteGroupAll();
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_RIGHT))
			{
				if(listPart.size() == 4)
				{
					AL al(m_lr_usergroup);
					if(!m_usergroup.SetGroupRightWrite(listPart[1], (GAIA::BL)listPart[2].front_ptr()))
						CMDFAILED;
					else
					{
						if(!m_usergroup.SetGroupRightRead(listPart[1], (GAIA::BL)listPart[3].front_ptr()))
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
					AL al(m_lr_usergroup);
					if(!m_usergroup.AddGroupUser(listPart[1], listPart[2]))
						CMDFAILED;
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_DELETEGROUPUSER))
			{
				if(listPart.size() == 3)
				{
					AL al(m_lr_usergroup);
					if(!m_usergroup.DeleteGroupUser(listPart[1], listPart[2]))
						CMDFAILED;
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_DELETEALLGROUPUSER))
			{
				if(listPart.size() == 2)
				{
					AL al(m_lr_usergroup);
					if(!m_usergroup.DeleteGroupUserAll(listPart[1]))
						CMDFAILED;
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_SHOWUSERS))
			{
				if(listPart.size() == 1)
				{
					AL al(m_lr_usergroup);
					UserGroup::__UserNameListType listUser;
					m_usergroup.EnumUser(listUser);
					UserGroup::__UserNameListType::const_it it = listUser.const_front_it();
					GAIA::N32 nIndex = 0;
					AL alprt(m_lr_prt);
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
					AL al(m_lr_usergroup);
					const GAIA::TCH* pszPassword = m_usergroup.GetUserPassword(listPart[1].front_ptr());
					if(pszPassword == GNULL)
						CMDFAILED;
					AL alprt(m_lr_prt);
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
					AL al(m_lr_usergroup);
					UserGroup::__GroupNameListType listGroup;
					m_usergroup.EnumGroup(listGroup);
					UserGroup::__UserNameListType::const_it it = listGroup.const_front_it();
					GAIA::N32 nIndex = 0;
					AL alprt(m_lr_prt);
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
					AL al(m_lr_usergroup);
					if(m_usergroup.FindGroup(listPart[1]))
					{
						GAIA::BL bWrite;
						GAIA::BL bRead;
						m_usergroup.GetGroupRightWrite(listPart[1], bWrite);
						m_usergroup.GetGroupRightRead(listPart[1], bRead);
						AL alprt(m_lr_prt);
						m_prt << "Right = " << bWrite << ", Read = " << bRead << "\n";

						UserGroup::__UserNameListType listUser;
						m_usergroup.EnumGroupUser(listPart[1], listUser);
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
					AL al(m_lr_filelist);
					FILEID fid = listPart[1];
					GAIA::TCH szPathName[MAXPATHLEN];
					CRCTYPE crc;
					if(m_filelist.GetName(fid, szPathName) &&
						m_filelist.GetCRC(fid, crc))
					{
						AL alprt(m_lr_prt);
						m_prt << szPathName << " CRC=" << crc << "\n";
					}
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
					AL al(m_lr_filelist);
					const FILEID* pFileID = m_filelist.GetIDByName(listPart[1]);
					CRCTYPE crc;
					if(pFileID != GNULL && m_filelist.GetCRC(*pFileID, crc))
					{
						AL alprt(m_lr_prt);
						m_prt << *pFileID << " CRC=" << crc << "\n";
					}
					else
						CMDFAILED;
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_FILES))
			{
				if(listPart.size() == 1)
				{
					AL alprt(m_lr_prt);
					for(FILEID x = 0; x < m_filelist.GetFileCount(); ++x)
					{
						GAIA::TCH szPathName[MAXPATHLEN];
						CRCTYPE crc;
						m_filelist.GetName(x, szPathName);
						m_filelist.GetCRC(x, crc);
						m_prt << "[" << x << "] " << szPathName << " CRC=" << crc << "\n";
					}
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_BANIP))
			{
				if(listPart.size() == 3)
				{
					AL al(m_lr_banip);
					GAIA::NETWORK::IP ip;
					ip.FromString(listPart[2].front_ptr());
					m_banip.AddBanIP(ip, listPart[1]);
				}
				else if(listPart.size() == 4)
				{
					AL al(m_lr_banip);
					GAIA::NETWORK::IP ipstart, ipend;
					ipstart.FromString(listPart[2].front_ptr());
					ipend.FromString(listPart[3].front_ptr());
					if(ipstart > ipend)
						CMDFAILED;
					else
					{
						GAIA::U64 uBanTime = listPart[1];
						for(; ipstart <= ipend; ++ipstart)
							m_banip.AddBanIP(ipstart, uBanTime);
					}
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_UNBANIP))
			{
				if(listPart.size() == 2)
				{
					AL al(m_lr_banip);
					GAIA::NETWORK::IP ip;
					ip.FromString(listPart[1].front_ptr());
					m_banip.DeleteBanIP(ip);
				}
				else if(listPart.size() == 3)
				{
					AL al(m_lr_banip);
					GAIA::NETWORK::IP ipstart, ipend;
					ipstart.FromString(listPart[1].front_ptr());
					ipend.FromString(listPart[2].front_ptr());
					if(ipstart > ipend)
						CMDFAILED;
					else
					{
						for(; ipstart <= ipend; ++ipstart)
							m_banip.DeleteBanIP(ipstart);
					}
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_UNBANIPALL))
			{
				if(listPart.size() == 1)
				{
					AL al(m_lr_banip);
					m_banip.DeleteBanIPAll();
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_SHOWBANIPS))
			{
				if(listPart.size() == 1)
				{
					AL al(m_lr_banip);
					BanIP::__BanIPSet::const_it it = m_banip.GetBanIPFrontIterator();
					GAIA::N32 nIndex = 0;
					GAIA::TCH szTemp[120];
					GAIA::U64 uCurrentTime = GAIA::TIME::clock_time();
					AL alprt(m_lr_prt);
					for(; !it.empty(); ++it)
					{
						const BanIP::BanIPNode& n = *it;
						n.ip.ToString(szTemp);
						m_prt << "[" << nIndex++ << "] " << szTemp;
						if(n.uBanTime != GINVALID)
						{
							GAIA::U64 uDeltaTime = uCurrentTime - n.uOccurTime;
							if(uDeltaTime > n.uBanTime)
								m_prt << " RemainTime=" << "0";
							else
								m_prt << " RemainTime=" << n.uBanTime - uDeltaTime;
						}
						m_prt << "\n";
					}
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
					if(!this->NLogin(na, listPart[1], listPart[2]))
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
			else if(CMD(CMD_RECYCLELINK))
			{
				if(listPart.size() == 2)
				{
					if(listPart[1] == _T("0"))
						this->EnableRecycleLink(GAIA::False);
					else
						this->EnableRecycleLink(GAIA::True);
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_DOWNLOADSPEED))
			{
				if(listPart.size() == 1)
				{
					AL alprt(m_lr_prt);
					m_prt << "DownloadSpeed = " << m_uDSpeed << "\n";
				}
				else if(listPart.size() == 2)
					m_uDSpeed = listPart[1];
				else
					CMDFAILED;
			}
			else if(CMD(CMD_UPLOADSPEED))
			{
				if(listPart.size() == 1)
				{
					AL alprt(m_lr_prt);
					m_prt << "UploadSpeed = " << m_uUSpeed << "\n";
				}
				else if(listPart.size() == 2)
					m_uUSpeed = listPart[1];
				else
					CMDFAILED;
			}
			else if(CMD(CMD_LINK))
			{
				if(listPart.size() == 1)
				{
					{
						AL alprt(m_lr_prt);
						GAIA::TCH szText[128];
						m_mainna.ToString(szText);
						m_prt << "MainAddress = " << szText << "\n";
						m_pNH->GetSelfNetAddress().ToString(szText);
						m_prt << "SelfAddress = " << szText << "\n";
					}

					AL al(m_lr_links);
					GAIA::N32 nIndex = 0;
					for(__LinkListType::it it = m_links.front_it(); !it.empty(); ++it)
					{
						NLink& nl = *it;
						GAIA::TCH szText[128];
						nl.na.ToString(szText);
						AL alprt(m_lr_prt);
						m_prt << "[" << nIndex << "] " << szText << " ";
						if(nl.bBeLink)
							m_prt << "BeLink" << " ";
						else
							m_prt << "Link" << " ";
						if(nl.state == NLink::STATE_DISCONNECT)
							m_prt << "Disconnect" << " ";
						else if(nl.state == NLink::STATE_READY)
							m_prt << "Ready" << " ";
						else if(nl.state == NLink::STATE_ONLINE)
							m_prt << "Online" << " ";
						else
							m_prt << "Invalid" << " ";
						m_prt << "Files[" << nl.uCmplFileCnt << "]";
						m_prt << "\n";
					}
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_PRIORITYLINK))
			{
				if(listPart.size() == 1)
				{
					{
						AL alprt(m_lr_prt);
						GAIA::TCH szText[128];
						m_mainna.ToString(szText);
						m_prt << "MainAddress = " << szText << "\n";
						m_pNH->GetSelfNetAddress().ToString(szText);
						m_prt << "SelfAddress = " << szText << "\n";
					}

					AL al(m_lr_prilinks);
					GAIA::N32 nIndex = 0;
					for(__LinkPriListType::it it = m_prilinks.front_it(); !it.empty(); ++it)
					{
						NLinkPri& nlp = *it;
						GAIA::TCH szText[128];
						nlp.nlink.na.ToString(szText);
						AL alprt(m_lr_prt);
						m_prt << "[" << nIndex << "] " << szText << " ";
						if(nlp.nlink.bBeLink)
							m_prt << "BeLink" << " ";
						else
							m_prt << "Link" << " ";
						if(nlp.nlink.state == NLink::STATE_DISCONNECT)
							m_prt << "Disconnect" << " ";
						else if(nlp.nlink.state == NLink::STATE_READY)
							m_prt << "Ready" << " ";
						else if(nlp.nlink.state == NLink::STATE_ONLINE)
							m_prt << "Online" << " ";
						else
							m_prt << "Invalid" << " ";
						m_prt << "Files[" << nlp.nlink.uCmplFileCnt << "]";
						m_prt << "\n";
					}
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_PERF))
			{
				if(listPart.size() == 1)
				{
					AL alprt(m_lr_prt);
					m_prt << "Execute = " << m_perf.fExecute << "(" << m_perf.fExecute - m_perf_last.fExecute << ")" << "\n";
					m_prt << "	ExecuteRequest = " << m_perf.fExecuteRequest << "(" << m_perf.fExecuteRequest - m_perf_last.fExecuteRequest << ")" << "\n";
					m_prt << "	ExecuteSeqRequest = " << m_perf.fExecuteSeqRequest << "(" << m_perf.fExecuteSeqRequest - m_perf_last.fExecuteSeqRequest << ")" << "\n";
					m_prt << "	ExecuteFileSend = " << m_perf.fExecuteFileSend << "(" << m_perf.fExecuteFileSend - m_perf_last.fExecuteFileSend << ")" << "\n";
					m_prt << "	ExecuteChunkSend = " << m_perf.fExecuteChunkSend << "(" << m_perf.fExecuteChunkSend - m_perf_last.fExecuteChunkSend << ")" << "\n";
					m_prt << "	ExecuteFileWrite = " << m_perf.fExecuteFileWrite << "(" << m_perf.fExecuteFileWrite - m_perf_last.fExecuteFileWrite << ")" << "\n";
					m_prt << "		Sort = " << m_perf.fExecuteFileWriteSort << "(" << m_perf.fExecuteFileWriteSort - m_perf_last.fExecuteFileWriteSort << ")" << "\n";
					m_prt << "		Request = " << m_perf.fExecuteFileWriteRequest << "(" << m_perf.fExecuteFileWriteRequest - m_perf_last.fExecuteFileWriteRequest << ")" << "\n";
					m_prt << "		Combin = " << m_perf.fExecuteFileWriteCombinSection << "(" << m_perf.fExecuteFileWriteCombinSection - m_perf_last.fExecuteFileWriteCombinSection << ")" << "\n";
					m_prt << "		WriteFile = " << m_perf.fExecuteFileWriteWriteFile << "(" << m_perf.fExecuteFileWriteWriteFile - m_perf_last.fExecuteFileWriteWriteFile << ")" << "\n";
					m_prt << "		CheckComplete = " << m_perf.fExecuteFileWriteCheckComplete << "(" << m_perf.fExecuteFileWriteCheckComplete - m_perf_last.fExecuteFileWriteCheckComplete << ")" << "\n";
					m_prt << "		CompleteDispatch = " << m_perf.fExecuteFileWriteCompleteDispatch << "(" << m_perf.fExecuteFileWriteCompleteDispatch - m_perf_last.fExecuteFileWriteCompleteDispatch << ")" << "\n";
					m_prt << "	ExecuteCmpFilesNotify = " << m_perf.fExecuteCmpFilesNotify << "(" << m_perf.fExecuteCmpFilesNotify - m_perf_last.fExecuteCmpFilesNotify << ")" << "\n";
					m_prt << "	ExecuteRecycleLink = " << m_perf.fExecuteRecycleLink << "(" << m_perf.fExecuteRecycleLink - m_perf_last.fExecuteRecycleLink << ")" << "\n";
					m_prt << "	ExecuteTimeoutSectionRequest = " << m_perf.fExecuteTimeoutSectionRequest << "(" << m_perf.fExecuteTimeoutSectionRequest - m_perf_last.fExecuteTimeoutSectionRequest << ")" << "\n";
					m_prt << "	ExecuteTimeoutChunkRequest = " << m_perf.fExecuteTimeoutChunkRequest << "(" << m_perf.fExecuteTimeoutChunkRequest - m_perf_last.fExecuteTimeoutChunkRequest << ")" << "\n";
					m_prt << "	ExecuteFileHeadSend = " << m_perf.fExecuteFileHeadSend << "(" << m_perf.fExecuteFileHeadSend - m_perf_last.fExecuteFileHeadSend << ")" << "\n";
					m_prt << "	ExecuteBanIP = " << m_perf.fExecuteBanIP << "(" << m_perf.fExecuteBanIP - m_perf_last.fExecuteBanIP << ")" << "\n";
					m_prt << "\n";
					m_prt << "HeartTick = " << m_perf.fHeartTick << "(" << m_perf.fHeartTick - m_perf_last.fHeartTick << ")" << "\n";
					m_prt << "\n";
					m_prt << "OnRecv = " << m_perf.fOnRecv << "(" << m_perf.fOnRecv - m_perf_last.fOnRecv << ")" << "\n";
					m_prt << "	BanIPCheckUp = " << m_perf.fBanIPCheckUp << "(" << m_perf.fBanIPCheckUp - m_perf_last.fBanIPCheckUp << ")" << "\n";
					m_prt << "	OnRecvLoginR = " << m_perf.fOnRecvLoginR << "(" << m_perf.fOnRecvLoginR - m_perf_last.fOnRecvLoginR << ")" << "\n";
					m_prt << "	OnRecvLogoutR = " << m_perf.fOnRecvLogoutR << "(" << m_perf.fOnRecvLogoutR - m_perf_last.fOnRecvLogoutR << ")" << "\n";
					m_prt << "	OnRecvNoopC = " << m_perf.fOnRecvNoopC << "(" << m_perf.fOnRecvNoopC - m_perf_last.fOnRecvNoopC << ")" << "\n";
					m_prt << "	OnRecvFileHeadR = " << m_perf.fOnRecvFileHeadR << "(" << m_perf.fOnRecvFileHeadR - m_perf_last.fOnRecvFileHeadR << ")" << "\n";
					m_prt << "	OnRecvFileR = " << m_perf.fOnRecvFileR << "(" << m_perf.fOnRecvFileR - m_perf_last.fOnRecvFileR << ")" << "\n";
					m_prt << "	OnRecvFileChunkR = " << m_perf.fOnRecvFileChunkR << "(" << m_perf.fOnRecvFileChunkR - m_perf_last.fOnRecvFileChunkR << ")" << "\n";
					m_prt << "	OnRecvFileHeadA = " << m_perf.fOnRecvFileHeadA << "(" << m_perf.fOnRecvFileHeadA - m_perf_last.fOnRecvFileHeadA << ")" << "\n";
					m_prt << "	OnRecvFileChunkA = " << m_perf.fOnRecvFileChunkA << "(" << m_perf.fOnRecvFileChunkA - m_perf_last.fOnRecvFileChunkA << ")" << "\n";
					m_prt << "	OnRecvFileNotExistA = " << m_perf.fOnRecvFileNotExistA << "(" << m_perf.fOnRecvFileNotExistA - m_perf_last.fOnRecvFileNotExistA << ")" << "\n";
					m_prt << "	OnRecvFileCmplA = " << m_perf.fOnRecvFileCmplA << "(" << m_perf.fOnRecvFileCmplA - m_perf_last.fOnRecvFileCmplA << ")" << "\n";
					m_prt << "	OnRecvCmplFileCountN = " << m_perf.fOnRecvCmplFileCountN << "(" << m_perf.fOnRecvCmplFileCountN - m_perf_last.fOnRecvCmplFileCountN << ")" << "\n";
					m_prt << "	OnRecvCmplFileSectionN = " << m_perf.fOnRecvCmplFileSectionN << "(" << m_perf.fOnRecvCmplFileSectionN - m_perf_last.fOnRecvCmplFileSectionN << ")" << "\n";
					m_prt << "	OnRecvCnnA = " << m_perf.fOnRecvCnnA << "(" << m_perf.fOnRecvCnnA - m_perf_last.fOnRecvCnnA << ")" << "\n";
					m_prt << "	OnRecvLoginOKA = " << m_perf.fOnRecvLoginOKA << "(" << m_perf.fOnRecvLoginOKA - m_perf_last.fOnRecvLoginOKA << ")" << "\n";
					m_prt << "	OnRecvLogoutOKA = " << m_perf.fOnRecvLogoutOKA << "(" << m_perf.fOnRecvLogoutOKA - m_perf_last.fOnRecvLogoutOKA << ")" << "\n";
					m_prt << "	OnRecvErrorA = " << m_perf.fOnRecvErrorA << "(" << m_perf.fOnRecvErrorA - m_perf_last.fOnRecvErrorA << ")" << "\n";
					m_prt << "\n";
					m_prt << "MinFileCmplTime = " << m_perf.fMinFileCmplTime << "(" << m_perf.fMinFileCmplTime - m_perf_last.fMinFileCmplTime << ")" << "\n";
					m_prt << "MaxFileCmplTime = " << m_perf.fMaxFileCmplTime << "(" << m_perf.fMaxFileCmplTime - m_perf_last.fMaxFileCmplTime << ")" << "\n";
					m_prt << "AveFileCmplTime = " << m_perf.fSumFileCmplTime / (GAIA::F64)m_statistics.uRequestFileCmplCount << "\n";
					m_prt << "\n";
					m_prt << "Temp1 = " << m_perf.fTemp1 << "(" << m_perf.fTemp1 - m_perf_last.fTemp1 << ")" << "\n";
					m_prt << "Temp2 = " << m_perf.fTemp2 << "(" << m_perf.fTemp2 - m_perf_last.fTemp2 << ")" << "\n";
					m_prt << "Temp3 = " << m_perf.fTemp3 << "(" << m_perf.fTemp3 - m_perf_last.fTemp3 << ")" << "\n";
					m_prt << "Temp4 = " << m_perf.fTemp4 << "(" << m_perf.fTemp4 - m_perf_last.fTemp4 << ")" << "\n";

					GAIA::ALGORITHM::xmemcpy(&m_perf_last, &m_perf, sizeof(m_perf));
				}
			}
			else if(CMD(CMD_FILECACHEINFO))
			{
				if(listPart.size() == 1)
				{
					AL al(m_lr_fcaches);
					__FileRecCacheListType::it it = m_fcaches.front_it();
					FILEID nIndex = 0;
					AL alprt(m_lr_prt);
					for(; !it.empty(); ++it)
					{
						FileRecCache& frc = *it;
						GAIA::TCH szFileName[MAXPATHLEN];
						if(!m_filelist.GetName(frc.fid, szFileName))
							GAIA::ALGORITHM::strcpy(szFileName, _T("<InvalidFileName>"));
						m_prt << "[" << nIndex << "] " << " FileID=" << frc.fid << " " << szFileName <<
							" Size=" << frc.fsize <<
							" CmplSize=" << this->GetFileCacheCompleteSize(frc) << "\n";
						++nIndex;
					}
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_STATISTICSRESET))
			{
				if(listPart.size() == 1)
					m_statistics.init();
				else
					CMDFAILED;
			}
			else if(CMD(CMD_PERFRESET))
			{
				if(listPart.size() == 1)
					m_perf.init();
				else
					CMDFAILED;
			}
			else if(CMD(CMD_T_GENFILE))
			{
				if(listPart.size() == 1)
				{
					static const GAIA::TCH TESTREADROOT[] = _T("readroot/");
					static const GAIA::U32 TESTFILECOUNT = 1000;
					static const GAIA::U32 TESTFILEMINSIZE = 10;
					static const GAIA::U32 TESTFILEMAXSIZE = 1024 * 1024;
					AL alprt(m_lr_prt);
					m_prt << "Begin generate test file.\n";
					m_prt << "Min file size = ." << TESTFILEMINSIZE << "\n";
					m_prt << "Max file size = ." << TESTFILEMAXSIZE << "\n";
					m_prt << "File count = ." << TESTFILECOUNT << "\n";
					GAIA::FILESYSTEM::Directory dir;
					if(!dir.Create(TESTREADROOT, GAIA::False))
						m_prt << "Create root path failed!\n";
					GAIA::U64 uTotalFileSize = 0;
					for(GAIA::U32 x = 0; x < TESTFILECOUNT; ++x)
					{
						GAIA::TCH szFile[MAXPATHLEN];
						GAIA::ALGORITHM::int2str((GAIA::N32)x, szFile);
						GAIA::ALGORITHM::strcat(szFile, _T(".t"));
						GAIA::TCH szFullName[MAXPATHLEN];
						GAIA::ALGORITHM::strcpy(szFullName, TESTREADROOT);
						GAIA::ALGORITHM::strcat(szFullName, szFile);
						GAIA::FILESYSTEM::File file;
						if(!file.Open(szFullName, GAIA::FILESYSTEM::File::OPEN_TYPE_WRITE | GAIA::FILESYSTEM::File::OPEN_TYPE_CREATEALWAYS))
						{
							m_prt << "Create file " << szFullName << " failed!\n";
							continue;
						}
						GAIA::U32 u0 = (GAIA::U32)GAIA::MATH::xrandom();
						GAIA::U32 u1 = (GAIA::U32)GAIA::MATH::xrandom();
						GAIA_AST(TESTFILEMAXSIZE >= TESTFILEMINSIZE);
						GAIA::U32 uFileSize = (u0 * 65536 + u1) % (TESTFILEMAXSIZE - TESTFILEMINSIZE) + TESTFILEMINSIZE;
						GAIA::U32 uOriginFileSize = uFileSize;
						if(uFileSize > 0)
						{
							while(uFileSize >= sizeof(GAIA::U32))
							{
								file << x;
								uFileSize -= sizeof(GAIA::U32);
							}
							while(uFileSize >= sizeof(GAIA::U8))
							{
								file << (GAIA::U8)(x % 256);
								uFileSize -= sizeof(GAIA::U8);
							}
							file.Flush();
						}
						m_prt << x << "(" << uOriginFileSize << ") " << "\n";
						uTotalFileSize += uOriginFileSize;
					}
					m_prt << "\nTotalFileSize = " << uTotalFileSize << "\n";
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_T_WATCH))
			{
				if(listPart.size() == 2)
				{
					if(listPart[1] == _T("0"))
						m_test_enablewatch = GAIA::False;
					else if(listPart[1] == _T("1"))
						m_test_enablewatch = GAIA::True;
					else
						CMDFAILED;
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_T_WATCHFILE))
			{
				if(listPart.size() == 2)
				{
					if(listPart[1] == _T("no"))
						m_test_watchfid = (FILEID)GINVALID;
					else
					{
						FILEID fid = listPart[1];
						if(fid >= m_filelist.GetFileCount())
						{
							AL alprt(m_lr_prt);
							m_prt << "invalid fid!\n";
						}
						else
							m_test_watchfid = fid;
					}
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_T_WATCHIP))
			{
				if(listPart.size() == 2)
				{
					if(listPart[1] == _T("no"))
						m_test_watchna.ip.Invalid();
					else
						m_test_watchna.ip.FromString(listPart[1].front_ptr());
				}
				else
					CMDFAILED;
			}
			else if(CMD(CMD_T_WATCHPORT))
			{
				if(listPart.size() == 2)
				{
					if(listPart[1] == _T("no"))
						m_test_watchna.uPort = 0;
					else
						GAIA::ALGORITHM::str2int(listPart[1].front_ptr(), m_test_watchna.uPort);
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
			m_mainna.Invalid();
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
			m_uCmplFileCount = 0;
			m_state = NLink::STATE_DISCONNECT;
			m_bEnableSequenceRequest = GAIA::False;
			m_uSequenceRequestIndex = 0;
			m_nMaxRequestFileCountSameTime = DEFAULTMAXREQFILECOUNTSAMETIME;
		#ifdef FSHA_DEBUG
			m_bEnableRecycleLink = GAIA::False;
		#else
			m_bEnableRecycleLink = GAIA::True;
		#endif
			m_uLastNotifyCmplTime = 0;
			m_szLoopCmd[0] = 0;
			m_uLoopCmdTimes = 0;
			m_uLoopCmdEscape = 0;
			m_uLoopCmdLastFireTime = 0;
			m_uLastBanIPExecute = 0;
			m_test_enablewatch = GAIA::False;
			m_test_watchfid = (FILEID)GINVALID;
			m_test_watchna.Invalid();
		}
		GINL GAIA::BL OnExecute()
		{
			GAIA::F64 fPerf = FSHA_PERF;
			m_statistics.uFrameCount++;
			GAIA::BL bRet = GAIA::False;
			GAIA::U64 uTime = GAIA::TIME::tick_time();
			if(this->OnExecuteRequest())
				bRet = GAIA::True;
			if(this->OnExecuteSequenceRequest())
				bRet = GAIA::True;
			if(this->OnExecuteFileSend())
				bRet = GAIA::True;
			if(this->OnExecuteChunkSend())
				bRet = GAIA::True;
			if(this->OnExecuteFileWrite())
				bRet = GAIA::True;
			if(this->OnExecuteCmplFilesNotify())
				bRet = GAIA::True;
			if(this->OnExecuteRecycleLink())
				bRet = GAIA::True;
			if(this->OnExecuteTimeoutSectionRequest())
				bRet = GAIA::True;
			if(this->OnExecuteTimeoutChunkRequest())
				bRet = GAIA::True;
			if(this->OnExecuteTimeoutReRequest())
				bRet = GAIA::True;
			if(this->OnExecuteFileHeadSend())
				bRet = GAIA::False;
			if(this->OnExecuteLoopCommand())
				bRet = GAIA::True;
			if(uTime - m_uLastBanIPExecute > BANIPDISPATCHTIME)
			{
				GAIA::F64 fPerfBanIP = FSHA_PERF;
				m_banip.Execute();
				m_perf.fExecuteBanIP += FSHA_PERF - fPerfBanIP;
				m_uLastBanIPExecute = uTime;
			}
			if(bRet)
				m_statistics.uValidFrameCount++;
			m_perf.fExecute += FSHA_PERF - fPerf;
			return bRet;
		}
		GINL GAIA::BL OnExecuteRequest()
		{
			GAIA::F64 fPerf = FSHA_PERF;
			GAIA::BL bRet = GAIA::False;
			AL al1(m_lr_reqeds);
			AL al2(m_lr_reqs);
			if(!m_reqs.empty())
			{
				m_listFileReqTemp.clear();
				if(m_reqeds.size() < m_nMaxRequestFileCountSameTime)
				{
					for(; !m_reqs.empty(); m_reqs.pop_front())
					{
						if(m_listFileReqTemp.size() == m_nMaxRequestFileCountSameTime - m_reqeds.size())
							break;
						if(m_reqeds.find(m_reqs.front()) == GNULL)
							m_listFileReqTemp.push_back(m_reqs.front());
					}
					if(!m_listFileReqTemp.empty())
					{
						FIDLIST listFile;
						listFile.reserve(m_listFileReqTemp.size());
						for(__FileReqListType::it it = m_listFileReqTemp.front_it(); !it.empty(); ++it)
							listFile.push_back((*it).fid);
						GAIA::NETWORK::NetworkAddress selectna;
						this->SelectRequestNetworkAddress(selectna);
						this->Request(selectna, listFile);
						for(__FileReqListType::it it = m_listFileReqTemp.front_it(); !it.empty(); ++it)
						{
							FileReq& fr = *it;
							fr.uFirstReqTime = fr.uLastActiveTime = GAIA::TIME::tick_time();
							m_reqeds.insert(fr);
						}
					}
				}
			}
			m_perf.fExecuteRequest += FSHA_PERF - fPerf;
			return bRet;
		}
		GINL GAIA::BL OnExecuteSequenceRequest()
		{
			GAIA::F64 fPerf = FSHA_PERF;
			GAIA::BL bRet = GAIA::False;
			if(m_bEnableSequenceRequest)
			{
				AL al1(m_lr_reqeds);
				AL al2(m_lr_reqs);
				for(; m_uSequenceRequestIndex < m_filelist.GetFileCount(); ++m_uSequenceRequestIndex)
				{
					if(m_reqs.size() + m_reqeds.size() >= m_nMaxRequestFileCountSameTime * 2)
						break;
					const FILEID& fid = m_filelist.GetIDBySequence(m_uSequenceRequestIndex);
					if(m_filestate.exist(fid))
						continue;
					FileReq fr;
					fr.fid = fid;
					fr.uUserReqTime = GAIA::TIME::tick_time();
					m_reqs.push_back(fr);
					bRet = GAIA::True;
				}
			}
			m_perf.fExecuteSeqRequest += FSHA_PERF - fPerf;
			return bRet;
		}
		GINL GAIA::BL OnExecuteFileSend()
		{
			GAIA::F64 fPerf = FSHA_PERF;
			m_FileSendMsgTemp.clear();
			GAIA::BL bRet = GAIA::False;
			AL al1(m_lr_filesendtasks);
			m_listFileDeleteTemp.clear();
			for(__FileSendTaskListType::it it = m_filesendtasks.front_it(); !it.empty(); ++it)
			{
				FileSendTask& fst = *it;
				AL al2(m_lr_fcaches);
				FileRecCache* pFRC = this->RequestFileRecCache(fst.fid, GAIA::False);
				if(pFRC == GNULL)
				{
					m_listFileDeleteTemp.push_back(fst);
					continue;
				}
				if(fst.bNeedHead)
				{
					fst.bNeedHead = GAIA::False;
					m_FileSendMsgTemp.clear();
					m_FileSendMsgTemp << fst.na;
					m_FileSendMsgTemp << MSG_A_FILEHEAD;
					m_FileSendMsgTemp << fst.fid;
					m_FileSendMsgTemp << pFRC->fsize;
					m_FileSendMsgTemp << pFRC->uCRC;
					this->Send(m_FileSendMsgTemp.front_ptr(), m_FileSendMsgTemp.write_size());
				}
				for(GAIA::U32 x = 0; x < BATCHCHUNKSENDCOUNT; ++x)
				{
					m_FileSendMsgTemp.clear();
					m_FileSendMsgTemp << fst.na;
					m_FileSendMsgTemp << MSG_A_FILECHUNK;
					m_FileSendMsgTemp << fst.fid;
					m_FileSendMsgTemp << fst.ci;
					m_FileSendMsgTemp << fst.sci;
					FILESIZETYPE cursize = fst.ci * CHUNKSIZE + fst.sci * SUBCHUNKSIZE;
					FILESIZETYPE remainsize = pFRC->fsize - cursize;
					SUBCHUNKSIZETYPE scsize;
					GAIA::BL bComplete = GAIA::False;
					if(remainsize > SUBCHUNKSIZE)
						scsize = SUBCHUNKSIZE;
					else
					{
						scsize = remainsize;
						bComplete = GAIA::True;
					}
					m_FileSendMsgTemp << scsize;
					pFRC->pFA->Seek(GAIA::SEEK_TYPE_BEGIN, cursize);
					GAIA::U8 buf[SUBCHUNKSIZE];
					if(pFRC->pFA->Read(buf, scsize) != scsize)
						continue;
				#ifdef FSHA_DEBUG
					if(scsize > 0)
					{
						if(GAIA::MATH::xrandom() % 10000 == 0)
							buf[GAIA::MATH::xrandom() % scsize] = GAIA::MATH::xrandom() % 256;
					}
				#endif
					m_FileSendMsgTemp.write(buf, scsize);
					this->Send(m_FileSendMsgTemp.front_ptr(), m_FileSendMsgTemp.write_size());
					if(m_test_enablewatch && fst.fid == m_test_watchfid)
					{
						AL al(m_lr_prt);
						m_prt << "[TEST] Send file, ChunkIndex = " << fst.ci << ", SubChunkIndex = " << (GAIA::N32)fst.sci << ".\n";
					}
					m_statistics.uSendChunkCount++;
					++fst.sci;
					if(fst.sci == 0)
						++fst.ci;
					bRet = GAIA::True;
					if(bComplete)
					{
						if(m_test_enablewatch && fst.fid == m_test_watchfid)
						{
							AL al(m_lr_prt);
							m_prt << "[TEST] Send file complete.\n";
						}
						m_statistics.uSendCmplFileCount++;
						m_listFileDeleteTemp.push_back(fst);
						pFRC->pFA->Close();
						m_desc.pFAC->ReleaseFileAccess(pFRC->pFA);
						pFRC->pFA = GNULL;
						if(pFRC->pFCSL != GNULL)
						{
							delete pFRC->pFCSL;
							pFRC->pFCSL = GNULL;
						}
						m_fcaches.erase(*pFRC);
						break;
					}
				}
			}
			for(GAIA::CONTAINER::Vector<FileSendTask>::it it = m_listFileDeleteTemp.front_it(); !it.empty(); ++it)
			{
				if(!m_filesendtasks.erase(*it))
					GAIA_AST(GAIA::ALWAYSFALSE);
			}
			m_perf.fExecuteFileSend += FSHA_PERF - fPerf;
			return bRet;
		}
		GINL GAIA::BL OnExecuteChunkSend()
		{
			GAIA::F64 fPerf = FSHA_PERF;
			GAIA::BL bRet = GAIA::False;
			AL al1(m_lr_chunksendtasks);
			m_listChunkDeleteTemp.clear();
			for(__ChunkSendTaskListType::it it = m_chunksendtasks.front_it(); !it.empty(); ++it)
			{
				ChunkSendTask& cst = *it;
				AL al2(m_lr_fcaches);
				FileRecCache* pFRC = this->RequestFileRecCache(cst.fid, GAIA::False);
				if(pFRC == GNULL)
				{
					m_listChunkDeleteTemp.push_back(cst);
					continue;
				}
				for(GAIA::U32 x = 0; x < BATCHCHUNKSENDCOUNT; ++x)
				{
					m_ChunkSendMsgTemp.clear();
					m_ChunkSendMsgTemp << cst.na;
					m_ChunkSendMsgTemp << MSG_A_FILECHUNK;
					m_ChunkSendMsgTemp << cst.fid;
					m_ChunkSendMsgTemp << cst.ci;
					m_ChunkSendMsgTemp << cst.sci;
					FILESIZETYPE cursize = cst.ci * CHUNKSIZE + cst.sci * SUBCHUNKSIZE;
					FILESIZETYPE remainsize = pFRC->fsize - cursize;
					SUBCHUNKSIZETYPE scsize;
					GAIA::BL bComplete = GAIA::False;
					if(remainsize > SUBCHUNKSIZE)
						scsize = SUBCHUNKSIZE;
					else
					{
						scsize = remainsize;
						bComplete = GAIA::True;
					}
					m_ChunkSendMsgTemp << scsize;
					pFRC->pFA->Seek(GAIA::SEEK_TYPE_BEGIN, cursize);
					GAIA::U8 buf[SUBCHUNKSIZE];
					if(pFRC->pFA->Read(buf, scsize) != scsize)
						continue;
				#ifdef FSHA_DEBUG
					if(scsize > 0)
					{
						if(GAIA::MATH::xrandom() % 10000 == 0)
							buf[GAIA::MATH::xrandom() % scsize] = GAIA::MATH::xrandom() % 256;
					}
				#endif
					m_ChunkSendMsgTemp.write(buf, scsize);
					this->Send(m_ChunkSendMsgTemp.front_ptr(), m_ChunkSendMsgTemp.write_size());
					if(m_test_enablewatch && m_test_watchfid == cst.fid)
					{
						AL al(m_lr_prt);
						m_prt << "[TEST] Send chunk, ChunkIndex = " << cst.ci << ", SubChunkIndex = " << (GAIA::N32)cst.sci << ".\n";
					}
					m_statistics.uSendChunkCount++;
					++cst.sci;
					if(cst.sci == 0)
					{
						++cst.ci;
						bComplete = GAIA::True;
					}
					bRet = GAIA::True;
					if(bComplete)
					{
						if(m_test_enablewatch && m_test_watchfid == cst.fid)
						{
							AL al(m_lr_prt);
							m_prt << "[TEST] Send chunk complete.\n";
						}
						m_listChunkDeleteTemp.push_back(cst);
						pFRC->pFA->Close();
						m_desc.pFAC->ReleaseFileAccess(pFRC->pFA);
						pFRC->pFA = GNULL;
						if(pFRC->pFCSL != GNULL)
						{
							delete pFRC->pFCSL;
							pFRC->pFCSL = GNULL;
						}
						m_fcaches.erase(*pFRC);
						break;
					}
				}
			}
			for(GAIA::CONTAINER::Vector<ChunkSendTask>::it it = m_listChunkDeleteTemp.front_it(); !it.empty(); ++it)
			{
				if(!m_chunksendtasks.erase(*it))
					GAIA_AST(GAIA::ALWAYSFALSE);
			}
			m_perf.fExecuteChunkSend += FSHA_PERF - fPerf;
			return bRet;
		}
		GINL GAIA::BL OnExecuteFileWrite()
		{
			GAIA::F64 fPerf = FSHA_PERF;
			GAIA::BL bRet = GAIA::False;
			m_listCompleteTemp.clear();
			{
				{
					AL al1(m_lr_filewritetasks);
					m_filewritetasks_temp = m_filewritetasks;
					m_filewritetasks.clear();
				}

				GAIA::F64 fPerfSort = FSHA_PERF;
				m_filewritetasks_temp.sort();
				m_perf.fExecuteFileWriteSort += FSHA_PERF - fPerfSort;
				for(__FileWriteTaskListType::it it_fwt = m_filewritetasks_temp.front_it(); !it_fwt.empty(); ++it_fwt)
				{
					/* Get file write context. */
					FileWriteTask& fwt = **it_fwt;

					/* Check file state. */
					if(this->GetFileCmpl(fwt.fid))
					{
						AL al3(m_lr_fwtpool);
						m_fwtpool.release(&fwt);
						continue;
					}

					/* Get file record cache. */
					GAIA::F64 fPerfRequest = FSHA_PERF;
					AL al2(m_lr_fcaches);
					FileRecCache* pFRC = this->RequestFileRecCache(fwt.fid, GAIA::True);
					m_perf.fExecuteFileWriteRequest += FSHA_PERF - fPerfRequest;
					if(pFRC == GNULL)
					{
						GAIA_AST(GAIA::ALWAYSFALSE);
						AL al3(m_lr_fwtpool);
						m_fwtpool.release(&fwt);
						continue;
					}
					GAIA_AST(pFRC->fid == fwt.fid);
				#ifdef FSHA_DEBUG
					if(pFRC->fsize != 0 && (fwt.ci * CHUNKSIZE + fwt.sci * SUBCHUNKSIZE + fwt.size) > pFRC->fsize)
						GAIA_AST(GAIA::ALWAYSFALSE);
				#endif

					/* Combin file chunk section. */
					GAIA::F64 fPerfCombin = FSHA_PERF;
					if(pFRC->pFCSL == GNULL)
						pFRC->pFCSL = new FileRecCache::__FileChunkSectionListType;
					FileChunkSection fcs;
					fcs.e = fcs.s = fwt.ci;
					fcs.ee = fcs.ss = fwt.sci;
					FileRecCache::__FileChunkSectionListType::it itnext = pFRC->pFCSL->lower_bound(fcs);
					if(itnext.empty())
					{
						FileRecCache::__FileChunkSectionListType::it itprev = pFRC->pFCSL->upper_bound(fcs);
						if(itprev.empty())
							pFRC->pFCSL->insert(fcs);
						else
						{
							FileChunkSection& fcs_prev = *itprev;
							if(fcs_prev.Intersect(fcs))
							{
								m_statistics.uRecvRepeatedDataSize += fwt.size;
								goto CHECK_WRITE_COMPLETE;
							}
							if(fcs_prev.NextTo(fcs))
							{
								fcs_prev.e = fcs.e;
								fcs_prev.ee = fcs.ee;
							}
							else
								pFRC->pFCSL->insert(fcs);
						}
					}
					else
					{
						FileChunkSection& fcs_next = *itnext;
						if(fcs_next.Intersect(fcs))
						{
							m_statistics.uRecvRepeatedDataSize += fwt.size;
							goto CHECK_WRITE_COMPLETE;
						}
						FileRecCache::__FileChunkSectionListType::it itprev = itnext;
						--itprev;
						if(itprev.empty())
						{
							if(fcs.NextTo(fcs_next))
							{
								fcs_next.s = fcs.s;
								fcs_next.ss = fcs.ss;
							}
							else
								pFRC->pFCSL->insert(fcs);
						}
						else
						{
							FileChunkSection& fcs_prev = *itprev;
							if(fcs_prev.Intersect(fcs))
							{
								m_statistics.uRecvRepeatedDataSize += fwt.size;
								goto CHECK_WRITE_COMPLETE;
							}
							if(fcs_prev.NextTo(fcs) && fcs.NextTo(fcs_next))
							{
								fcs_prev.e = fcs_next.e;
								fcs_prev.ee = fcs_next.ee;
								pFRC->pFCSL->erase(fcs_next);
							}
							else if(fcs_prev.NextTo(fcs))
							{
								fcs_prev.e = fcs.e;
								fcs_prev.ee = fcs.ee;
							}
							else if(fcs.NextTo(fcs_next))
							{
								fcs_next.s = fcs.s;
								fcs_next.ss = fcs.ss;
							}
							else
								pFRC->pFCSL->insert(fcs);
						}
					}
					m_perf.fExecuteFileWriteCombinSection += FSHA_PERF - fPerfCombin;

				#ifdef FSHA_DEBUG
					{
						FileRecCache::__FileChunkSectionListType::it it = pFRC->pFCSL->front_it();
						while(!it.empty())
						{
							FileRecCache::__FileChunkSectionListType::it itnext = it;
							++itnext;
							if(!itnext.empty())
							{
								FileChunkSection& src = *it;
								FileChunkSection& dst = *itnext;
								GAIA_AST(src.dbg_check(dst));
							}
							++it;
						}
					}
				#endif

					/* Write file. */
					{
						if(m_test_enablewatch && m_test_watchfid != (FILEID)GINVALID)
						{
							if(m_test_watchfid == pFRC->fid)
							{
								AL al(m_lr_prt);
								m_prt << "[TEST] Write file data, ChunkIndex = " << (GAIA::N32)fwt.ci << ", SubChunkIndex = " << (GAIA::N32)fwt.sci << ".\n";
							}
						}

						GAIA::F64 fPerfWrite = FSHA_PERF;
						FILESIZETYPE dstsize = fwt.ci * CHUNKSIZE + fwt.sci * SUBCHUNKSIZE;
						if(pFRC->pFA->Size() < dstsize)
							pFRC->pFA->Resize(dstsize);
						pFRC->pFA->Seek(GAIA::SEEK_TYPE_BEGIN, dstsize);
						pFRC->pFA->Write(fwt.buf, fwt.size);
						m_perf.fExecuteFileWriteWriteFile += FSHA_PERF - fPerfWrite;
					}

					/* Check write complete. */
				CHECK_WRITE_COMPLETE:
					GAIA::F64 fPerfCheckComplete = FSHA_PERF;
					if(pFRC->pFCSL->size() == 1)
					{
						FileChunkSection fcs;
						fcs.e = fcs.s = 0;
						fcs.ee = fcs.ss = 0;
						FileChunkSection* pFCS = pFRC->pFCSL->find(fcs);
						if(pFCS != GNULL)
						{
							GAIA::U32 uSubChunkCount = (pFCS->e * 256 + pFCS->ee) - (pFCS->s * 256 + pFCS->ss) + 1;
							GAIA::U32 uCorrectSubChunkCount = pFRC->fsize / SUBCHUNKSIZE;
							if(pFRC->fsize % SUBCHUNKSIZE != 0)
								++uCorrectSubChunkCount;
							if(uSubChunkCount == uCorrectSubChunkCount)
							{
								if(pFRC->pFA != GNULL)
									pFRC->pFA->Flush();
								m_listCompleteTemp.push_back(*pFRC);
							}
						}
					}
					m_perf.fExecuteFileWriteCheckComplete += FSHA_PERF - fPerfCheckComplete;
					AL al3(m_lr_fwtpool);
					m_fwtpool.release(&fwt);
				}
				m_filewritetasks_temp.clear();
			}

			/* Dispatch complete file. */
			GAIA::F64 fPerfCompleteDispatch = FSHA_PERF;
			for(GAIA::CONTAINER::Vector<FileRecCache>::it it = m_listCompleteTemp.front_it(); !it.empty(); ++it)
			{
				GAIA::BL bCRCSuccess = GAIA::True;
				/* File CRC checkup. */
				{
					GAIA::TCH szFullName[MAXPATHLEN];
					if(m_writeroot.empty())
						szFullName[0] = 0;
					else
						GAIA::ALGORITHM::strcpy(szFullName, m_writeroot.front_ptr());
					GAIA::TCH szFileName[MAXPATHLEN];
					m_filelist.GetName((*it).fid, szFileName);
					GAIA::ALGORITHM::strcat(szFullName, szFileName);
					CRCTYPE crc = m_filelist.BuildFileCRC(szFullName);
					if(crc != (*it).uCRC)
					{
						bCRCSuccess = GAIA::False;
						m_statistics.uCRCCheckFailedCount++;
						{
							AL al(m_lr_fcaches);
							FileRecCache* pFRC = m_fcaches.find(*it);
							if(pFRC != GNULL)
							{
								if(pFRC->pFA != GNULL)
								{
									pFRC->pFA->Close();
									m_desc.pFAC->ReleaseFileAccess(pFRC->pFA);
									pFRC->pFA = GNULL;
								}
								if(pFRC->pFCSL != GNULL)
								{
									delete pFRC->pFCSL;
									pFRC->pFCSL = GNULL;
								}
								m_fcaches.erase(*it);
							}
						}

						{
							FIDLIST listRequest;
							listRequest.push_back((*it).fid);
							GAIA::NETWORK::NetworkAddress selectna;
							this->SelectRequestNetworkAddress(selectna);
							this->Request(selectna, listRequest);
						}
					}
				}
				if(bCRCSuccess)
				{
					if(m_test_enablewatch && m_test_watchfid == (*it).fid)
					{
						AL al(m_lr_prt);
						m_prt << "[TEST] File write complete.\n";
					}
						this->ReleaseFileRecCache(*it);
				}
				else
				{
					if(m_test_enablewatch && m_test_watchfid == (*it).fid)
					{
						AL al(m_lr_prt);
						m_prt << "[TEST] File CRC check failed and rerequest.\n";
					}
				}
			}
			m_perf.fExecuteFileWriteCompleteDispatch += FSHA_PERF - fPerfCompleteDispatch;
			m_perf.fExecuteFileWrite += FSHA_PERF - fPerf;
			return bRet;
		}
		GINL GAIA::BL OnExecuteCmplFilesNotify()
		{
			GAIA::F64 fPerf = FSHA_PERF;
			GAIA::BL bRet = GAIA::False;
			GAIA::U64 uTime = GAIA::TIME::tick_time();
			if(m_statistics.uFrameCount % CMPLFILESNOTIFYFREQ == 0 ||
				uTime - m_uLastNotifyCmplTime > REQUESTCMPLFILESNOTIFYTIME)
			{
				m_uLastNotifyCmplTime = uTime;
				AL al(m_lr_cmplfiles);
				if(!m_cmplfiles.empty())
				{
					m_cmplfiles.sort();
					m_cmplfiles.unique();
					FILEID startindex = (FILEID)GINVALID;
					FILEID endindex = (FILEID)GINVALID;
					for(FIDLIST::it it = m_cmplfiles.front_it(); !it.empty(); ++it)
					{
						if(startindex == GINVALID)
							startindex = endindex = *it;
						else
						{
							GAIA_AST((*it) > endindex);
							if(endindex + 1 != *it)
							{
								m_ExecuteCmplFilesNotifyMsgTemp.clear();
								m_ExecuteCmplFilesNotifyMsgTemp << m_mainna;
								m_ExecuteCmplFilesNotifyMsgTemp << MSG_N_CMPLFILESECTION;
								m_ExecuteCmplFilesNotifyMsgTemp << startindex;
								m_ExecuteCmplFilesNotifyMsgTemp << endindex;
								this->SendToAll(m_ExecuteCmplFilesNotifyMsgTemp.front_ptr(), m_ExecuteCmplFilesNotifyMsgTemp.write_size());
								startindex = endindex = *it;
							}
							else
								endindex = *it;
						}
					}
					if(startindex != GINVALID)
					{
						m_ExecuteCmplFilesNotifyMsgTemp.clear();
						m_ExecuteCmplFilesNotifyMsgTemp << m_mainna;
						m_ExecuteCmplFilesNotifyMsgTemp << MSG_N_CMPLFILESECTION;
						m_ExecuteCmplFilesNotifyMsgTemp << startindex;
						m_ExecuteCmplFilesNotifyMsgTemp << endindex;
						this->SendToAll(m_ExecuteCmplFilesNotifyMsgTemp.front_ptr(), m_ExecuteCmplFilesNotifyMsgTemp.write_size());
						startindex = endindex = (FILEID)GINVALID;
					}
					m_cmplfiles.clear();
				}
			}
			m_perf.fExecuteCmpFilesNotify += FSHA_PERF - fPerf;
			return bRet;
		}
		GINL GAIA::BL OnExecuteRecycleLink()
		{
			GAIA::F64 fPerf = FSHA_PERF;
			GAIA::BL bRet = GAIA::False;
			GAIA::U64 uCurrentTime = GAIA::TIME::tick_time();

			// Recycle from link list and prilink list.
			m_listRecycleTemp.clear();
			{
				if(this->IsEnableRecycleLink())
				{
					AL al1(m_lr_links);
					AL al2(m_lr_prilinks);
					for(__LinkListType::it it = m_links.front_it(); !it.empty(); ++it)
					{
						NLink& nl = *it;
						if(uCurrentTime > nl.uLastHeartTime)
						{
							if(uCurrentTime - nl.uLastHeartTime > LINKRECYCLETIME)
								m_listRecycleTemp.push_back(nl);
						}
					}
					for(GAIA::CONTAINER::Vector<NLink>::it it = m_listRecycleTemp.front_it(); !it.empty(); ++it)
					{
						NLinkPri nlp;
						nlp.nlink = *it;
						m_RecycleLinkMsgTemp.clear();
						m_RecycleLinkMsgTemp << nlp.nlink.na;
						m_RecycleLinkMsgTemp << MSG_A_ERROR;
						m_RecycleLinkMsgTemp << ERRNO_TIMEOUT;
						this->Send(m_RecycleLinkMsgTemp.front_ptr(), m_RecycleLinkMsgTemp.write_size());
						m_links.erase(nlp.nlink);
						m_prilinks.erase(nlp);
					}
				}
			}

			if(m_listRecycleTemp.size() > 0)
			{
				// Recycle all not sended file.
				{
					AL al(m_lr_filesendtasks);
					GAIA::CONTAINER::Vector<FileSendTask> listRecycleFST;
					for(GAIA::CONTAINER::Vector<NLink>::it it = m_listRecycleTemp.front_it(); !it.empty(); ++it)
					{
						NLink& nl = *it;
						if(!nl.bBeLink)
							continue;
						FileSendTask fst;
						fst.na = nl.na;
						fst.fid = 0;
						__FileSendTaskListType::it itc = m_filesendtasks.lower_bound(fst);
						for(; !itc.empty(); ++itc)
						{
							FileSendTask& fstref = *itc;
							if(fstref.na != fst.na)
								break;
							listRecycleFST.push_back(fstref);
						}
					}
					for(GAIA::CONTAINER::Vector<FileSendTask>::it it = listRecycleFST.front_it(); !it.empty(); ++it)
						m_filesendtasks.erase(*it);
				}

				// Recycle all not sended chunk.
				{
					AL al(m_lr_chunksendtasks);
					GAIA::CONTAINER::Vector<ChunkSendTask> listRecycleCST;
					for(GAIA::CONTAINER::Vector<NLink>::it it = m_listRecycleTemp.front_it(); !it.empty(); ++it)
					{
						NLink& nl = *it;
						if(!nl.bBeLink)
							continue;
						ChunkSendTask cst;
						cst.na = nl.na;
						cst.fid = 0;
						cst.ci = 0;
						__ChunkSendTaskListType::it itc = m_chunksendtasks.lower_bound(cst);
						for(; !itc.empty(); ++itc)
						{
							ChunkSendTask& cstref = *itc;
							if(cstref.na != cst.na)
								break;
							listRecycleCST.push_back(cstref);
						}
					}
					for(GAIA::CONTAINER::Vector<ChunkSendTask>::it it = listRecycleCST.front_it(); !it.empty(); ++it)
						m_chunksendtasks.erase(*it);
				}

				// Recycle jump requests.
				{
					AL al(m_lr_jumpreqs);
					GAIA::CONTAINER::Vector<JumpReq> listJR;
					for(GAIA::CONTAINER::Vector<NLink>::it it = m_listRecycleTemp.front_it(); !it.empty(); ++it)
					{
						NLink& nl = *it;
						JumpReq jr;
						jr.na = nl.na;
						JumpReq* pJR = m_jumpreqs.find(jr);
						if(pJR != GNULL)
							listJR.push_back(*pJR);
					}
					for(GAIA::CONTAINER::Vector<JumpReq>::it it = listJR.front_it(); !it.empty(); ++it)
						m_jumpreqs.erase(*it);
				}
			}

			m_perf.fExecuteRecycleLink += FSHA_PERF - fPerf;
			return bRet;
		}
		GINL GAIA::BL OnExecuteTimeoutSectionRequest()
		{
			GAIA::F64 fPerf = FSHA_PERF;
			GAIA::BL bRet = GAIA::False;
			AL al(m_lr_reqeds);
			__FileReqSetType::it it_reqed = m_reqeds.front_it();
			GAIA::U64 uCurrentTime = GAIA::TIME::tick_time();
			for(; !it_reqed.empty(); ++it_reqed)
			{
				FileReq& fr = *it_reqed;
				if(uCurrentTime - fr.uLastActiveTime > REQUESTTIMEOUTTIME &&
					uCurrentTime - fr.uLastTimeoutSectionRequestTime > REQUESTTIMEOUTTIME)
				{
					fr.uLastTimeoutSectionRequestTime = uCurrentTime;
					AL al(m_lr_fcaches);
					FileRecCache frc;
					frc.fid = fr.fid;
					frc.bWrite = GAIA::True;
					FileRecCache* pFRC = m_fcaches.find(frc);
					if(pFRC != GNULL)
					{
						if(pFRC->pFCSL != GNULL)
						{
							FileRecCache::__FileChunkSectionListType::it it = pFRC->pFCSL->front_it();
							for(; !it.empty(); ++it)
							{
								FileChunkSection& fcs = *it;
								GAIA::BL bRequested = GAIA::False;
								FileRecCache::__FileChunkSectionListType::it itnext = it;
								++itnext;
								if(itnext.empty())
								{
									FILESIZETYPE fcmplsize = fcs.e * CHUNKSIZE + fcs.ee * SUBCHUNKSIZE;
									if(pFRC->fsize == 0)
									{
										m_TimeoutChunkRequestMsgTemp.clear();
										m_TimeoutChunkRequestMsgTemp << m_mainna;
										m_TimeoutChunkRequestMsgTemp << MSG_R_FILEHEAD;
										m_TimeoutChunkRequestMsgTemp << pFRC->fid;
										this->Send(m_TimeoutChunkRequestMsgTemp.front_ptr(),
											m_TimeoutChunkRequestMsgTemp.write_size());
										m_statistics.uRequestFileHeadCount++;
										break;
									}
									GAIA_AST(pFRC->fsize > fcmplsize);
									FILESIZETYPE fsize = pFRC->fsize - fcmplsize;
									if(fsize > 1)
									{
										--fsize;
										if(fsize >= SINGLECHUNKREQUESTLIMIT * CHUNKSIZE)
											bRequested = GAIA::True;
									}
								}
								else
								{
									FileChunkSection& fcsnext = *itnext;
									GAIA_AST((fcsnext.s * 256 + fcsnext.ss) > (fcs.e * 256 + fcs.ee));
									FILESIZETYPE fsize = (fcsnext.s * CHUNKSIZE + fcsnext.ss * SUBCHUNKSIZE) -
										(fcs.e * CHUNKSIZE + fcs.ee * SUBCHUNKSIZE);
									if(fsize >= SINGLECHUNKREQUESTLIMIT * CHUNKSIZE + 1)
										bRequested = GAIA::True;
								}
								if(bRequested)
								{
									if(m_test_enablewatch && m_test_watchfid == fr.fid)
									{
										AL al(m_lr_prt);
										m_prt << "[TEST] Request section for time out, ChunkIndex = " << fcs.e << ".\n";
									}
									GAIA::NETWORK::NetworkAddress selectna;
									this->SelectRequestNetworkAddress(selectna);
									m_TimeoutSectionRequestMsgTemp.clear();
									m_TimeoutSectionRequestMsgTemp << selectna;
									m_TimeoutSectionRequestMsgTemp << MSG_R_FILE;
									m_TimeoutSectionRequestMsgTemp << (REQFILECOUNTTYPE)1;
									m_TimeoutSectionRequestMsgTemp << pFRC->fid;
									m_TimeoutSectionRequestMsgTemp << fcs.e;
									this->Send(m_TimeoutSectionRequestMsgTemp.front_ptr(), m_TimeoutSectionRequestMsgTemp.write_size());
									m_statistics.uTimeoutSectionRequestCount++;
									m_statistics.uRequestFileCount++;
									bRet = GAIA::True;
								}
							}
						}
						else
						{
							if(m_test_enablewatch && m_test_watchfid == fr.fid)
							{
								AL al(m_lr_prt);
								m_prt << "[TEST] Request full file for time out, the pFCSL is GNULL.\n";
							}
							GAIA::NETWORK::NetworkAddress selectna;
							this->SelectRequestNetworkAddress(selectna);
							m_TimeoutSectionRequestMsgTemp.clear();
							m_TimeoutSectionRequestMsgTemp << selectna;
							m_TimeoutSectionRequestMsgTemp << MSG_R_FILE;
							m_TimeoutSectionRequestMsgTemp << (REQFILECOUNTTYPE)1;
							m_TimeoutSectionRequestMsgTemp << pFRC->fid;
							m_TimeoutSectionRequestMsgTemp << (CHUNKINDEX)0;
							this->Send(m_TimeoutSectionRequestMsgTemp.front_ptr(), m_TimeoutSectionRequestMsgTemp.write_size());
							m_statistics.uTimeoutSectionRequestCount++;
							m_statistics.uRequestFileCount++;
							bRet = GAIA::True;
						}
					}
					else
					{
						if(m_test_enablewatch && m_test_watchfid == fr.fid)
						{
							AL al(m_lr_prt);
							m_prt << "[TEST] Request full file for time out, the pFRC is GNULL.\n";
						}
						GAIA::NETWORK::NetworkAddress selectna;
						this->SelectRequestNetworkAddress(selectna);
						m_TimeoutSectionRequestMsgTemp.clear();
						m_TimeoutSectionRequestMsgTemp << selectna;
						m_TimeoutSectionRequestMsgTemp << MSG_R_FILE;
						m_TimeoutSectionRequestMsgTemp << (REQFILECOUNTTYPE)1;
						m_TimeoutSectionRequestMsgTemp << fr.fid;
						m_TimeoutSectionRequestMsgTemp << (CHUNKINDEX)0;
						this->Send(m_TimeoutSectionRequestMsgTemp.front_ptr(), m_TimeoutSectionRequestMsgTemp.write_size());
						m_statistics.uTimeoutSectionRequestCount++;
						m_statistics.uRequestFileCount++;
						bRet = GAIA::True;
					}
				}
			}
			m_perf.fExecuteTimeoutSectionRequest += FSHA_PERF - fPerf;
			return bRet;
		}
		GINL GAIA::BL OnExecuteTimeoutChunkRequest()
		{
			GAIA::F64 fPerf = FSHA_PERF;
			GAIA::BL bRet = GAIA::False;
			AL al(m_lr_reqeds);
			__FileReqSetType::it it_reqed = m_reqeds.front_it();
			GAIA::U64 uCurrentTime = GAIA::TIME::tick_time();
			for(; !it_reqed.empty(); ++it_reqed)
			{
				FileReq& fr = *it_reqed;
				if(uCurrentTime - fr.uLastActiveTime > REQUESTTIMEOUTTIME &&
					uCurrentTime - fr.uLastTimeoutChunkRequestTime > REQUESTTIMEOUTTIME)
				{
					fr.uLastTimeoutChunkRequestTime = uCurrentTime;
					AL al(m_lr_fcaches);
					FileRecCache frc;
					frc.fid = fr.fid;
					frc.bWrite = GAIA::True;
					FileRecCache* pFRC = m_fcaches.find(frc);
					if(pFRC != GNULL)
					{
						if(pFRC->pFCSL != GNULL)
						{
							if(pFRC->fsize > 0)
							{
								GAIA::U32 uChunkRequestCount = 0;
								FileRecCache::__FileChunkSectionListType::it it = pFRC->pFCSL->front_it();
								for(; !it.empty(); ++it)
								{
									FileChunkSection& fcs = *it;
									FileRecCache::__FileChunkSectionListType::it itnext = it;
									++itnext;
									if(itnext.empty())
									{
										FILESIZETYPE fcmplsize = fcs.e * CHUNKSIZE + fcs.ee * SUBCHUNKSIZE;
										if(pFRC->fsize == 0)
										{
											m_TimeoutChunkRequestMsgTemp.clear();
											m_TimeoutChunkRequestMsgTemp << m_mainna;
											m_TimeoutChunkRequestMsgTemp << MSG_R_FILEHEAD;
											m_TimeoutChunkRequestMsgTemp << pFRC->fid;
											this->Send(m_TimeoutChunkRequestMsgTemp.front_ptr(),
												m_TimeoutChunkRequestMsgTemp.write_size());
											m_statistics.uRequestFileHeadCount++;
											break;
										}
										GAIA_AST(pFRC->fsize > fcmplsize);
										FILESIZETYPE fsize = pFRC->fsize - fcmplsize;
										if(fsize > 1)
										{
											--fsize;
											if(fsize < SINGLECHUNKREQUESTLIMIT * CHUNKSIZE)
											{
												CHUNKINDEX uTotalChunkCount = pFRC->fsize / CHUNKSIZE + ((pFRC->fsize % CHUNKSIZE == 0) ? 0 : 1);
												for(CHUNKINDEX x = fcs.e; x < uTotalChunkCount; ++x)
												{
													GAIA::NETWORK::NetworkAddress selectna;
													this->SelectRequestNetworkAddress(selectna);
													m_TimeoutChunkRequestMsgTemp.clear();
													m_TimeoutChunkRequestMsgTemp << selectna;
													m_TimeoutChunkRequestMsgTemp << MSG_R_FILECHUNK;
													m_TimeoutChunkRequestMsgTemp << pFRC->fid;
													m_TimeoutChunkRequestMsgTemp << x;
													this->Send(m_TimeoutChunkRequestMsgTemp.front_ptr(),
														m_TimeoutChunkRequestMsgTemp.write_size());

													if(m_test_enablewatch && m_test_watchfid == pFRC->fid)
													{
														AL al(m_lr_prt);
														m_prt << "[TEST] Request file chunk for time out, Chunk = " << x << ".\n";
													}
													m_statistics.uTimeoutChunkRequestCount++;
													++uChunkRequestCount;
													if(uChunkRequestCount == MAXCHUNKREQUESTCOUNTPERDISPATCH)
														break;
												}
											}
										}
									}
									else
									{
										FileChunkSection& fcs_next = *itnext;
										GAIA_AST(fcs_next.s * 256 + fcs_next.ss > fcs.e * 256 + fcs.ee);
										FILESIZETYPE fsize = (fcs_next.s * CHUNKSIZE + fcs_next.ss * SUBCHUNKSIZE) -
											(fcs.e * CHUNKSIZE + fcs.ee * SUBCHUNKSIZE);
										if(fsize < SINGLECHUNKREQUESTLIMIT * CHUNKSIZE + 1)
										{
											for(CHUNKINDEX x = fcs.e; x <= fcs_next.s; ++x)
											{
												GAIA::NETWORK::NetworkAddress selectna;
												this->SelectRequestNetworkAddress(selectna);
												m_TimeoutChunkRequestMsgTemp.clear();
												m_TimeoutChunkRequestMsgTemp << selectna;
												m_TimeoutChunkRequestMsgTemp << MSG_R_FILECHUNK;
												m_TimeoutChunkRequestMsgTemp << pFRC->fid;
												m_TimeoutChunkRequestMsgTemp << x;
												this->Send(m_TimeoutChunkRequestMsgTemp.front_ptr(),
													m_TimeoutChunkRequestMsgTemp.write_size());

												m_statistics.uTimeoutChunkRequestCount++;
												++uChunkRequestCount;
												if(uChunkRequestCount == MAXCHUNKREQUESTCOUNTPERDISPATCH)
													break;
											}
										}
									}
									if(uChunkRequestCount == MAXCHUNKREQUESTCOUNTPERDISPATCH)
										break;
								}
								m_statistics.uRequestChunkCount += uChunkRequestCount;
							}
						}
					}
				}
			}
			m_perf.fExecuteTimeoutChunkRequest += FSHA_PERF - fPerf;
			return bRet;
		}
		GINL GAIA::BL OnExecuteTimeoutReRequest()
		{
			GAIA::F64 fPerf = FSHA_PERF;
			GAIA::BL bRet = GAIA::False;
			AL al(m_lr_reqeds);
			__FileReqSetType::it it_reqed = m_reqeds.front_it();
			GAIA::U64 uCurrentTime = GAIA::TIME::tick_time();
			for(; !it_reqed.empty(); ++it_reqed)
			{
				FileReq& fr = *it_reqed;
				GAIA::BL bNeedReRequest = GAIA::False;
				if(uCurrentTime - fr.uLastTimeoutReRequestTime > REREQUESTTIMEOUTTIME)
				{
					if(uCurrentTime - fr.uLastActiveTime > REREQUESTTIMEOUTTIME)
						bNeedReRequest = GAIA::True;
					else
					{
						FILESIZETYPE fsize;
						{
							AL al(m_lr_fcaches);
							FileRecCache frc;
							frc.fid = fr.fid;
							frc.bWrite = GAIA::True;
							FileRecCache* pFRC = m_fcaches.find(frc);
							if(pFRC != GNULL)
								fsize = pFRC->fsize;
							else
								fsize = 0;
						}
						if(fsize == 0)
						{
							if(uCurrentTime - fr.uUserReqTime > REREQUESTTIMEOUTTIME)
								bNeedReRequest = GAIA::True;
						}
						else
						{
							if(fsize < 1024 * 1024 && (uCurrentTime - fr.uUserReqTime) > 60 * 1000 * 1000)
								bNeedReRequest = GAIA::True;
						}
					}
				}
				if(bNeedReRequest)
				{
					fr.uLastTimeoutSectionRequestTime = uCurrentTime;
					fr.uLastTimeoutChunkRequestTime = uCurrentTime;
					fr.uLastTimeoutReRequestTime = uCurrentTime;
					/* Clean up current FileRecCache. */
					{
						AL al(m_lr_fcaches);
						FileRecCache frc;
						frc.fid = fr.fid;
						frc.bWrite = GAIA::True;
						FileRecCache* pFRC = m_fcaches.find(frc);
						if(pFRC != GNULL)
						{
							if(pFRC->pFCSL != GNULL)
							{
								delete pFRC->pFCSL;
								pFRC->pFCSL = GNULL;
							}
							if(pFRC->pFA != GNULL)
							{
								m_desc.pFAC->ReleaseFileAccess(pFRC->pFA);
								pFRC->pFA = GNULL;
							}
						}
					}
					/* ReRequest. */
					{
						m_listReRequestTemp.clear();
						m_listReRequestTemp.push_back(fr.fid);
						GAIA::NETWORK::NetworkAddress selectna;
						this->SelectRequestNetworkAddress(selectna);
						this->Request(selectna, m_listReRequestTemp);
						m_statistics.uTimeoutReRequestCount++;
					}
				}
			}
			m_perf.fExecuteTimeoutReRequest += FSHA_PERF - fPerf;
			return bRet;
		}
		GINL GAIA::BL OnExecuteFileHeadSend()
		{
			GAIA::BL bRet = GAIA::False;
			GAIA::F64 fPerf = FSHA_PERF;
			{
				AL al(m_lr_fileheadsendtasks);
				m_fileheadsendtasks_temp = m_fileheadsendtasks;
				m_fileheadsendtasks.clear();
			}

			if(!m_fileheadsendtasks_temp.empty())
			{
				__FileHeadSendTaskListType::it it = m_fileheadsendtasks_temp.front_it();
				for(; !it.empty(); ++it)
				{
					__FileHeadSendTaskListType::_datatype& t = *it;
					/* Get file size. */
					FILESIZETYPE fsize;
					GAIA::TCH szFileName[MAXPATHLEN];
					if(!m_filelist.GetName(t.fid, szFileName))
					{
						GAIA_AST(GAIA::ALWAYSFALSE);
						continue;
					}
					GAIA::TCH szFullName[MAXPATHLEN];
					if(m_readroot.empty())
						szFullName[0] = 0;
					else
						GAIA::ALGORITHM::strcpy(szFullName, m_readroot.front_ptr());
					GAIA::ALGORITHM::strcat(szFullName, szFileName);
					FileAccess* pFA = m_desc.pFAC->CreateFileAccess();
					GAIA_AST(!!pFA);
					if(pFA == GNULL)
						continue;
					if(!pFA->Open(szFullName, GAIA::True))
					{
						GAIA_AST(GAIA::ALWAYSFALSE);
						m_desc.pFAC->ReleaseFileAccess(pFA);
						continue;
					}
					pFA->Seek(GAIA::SEEK_TYPE_END, 0);
					fsize = (FILESIZETYPE)pFA->Tell();
					m_desc.pFAC->ReleaseFileAccess(pFA);
					pFA = GNULL;
					/* Get file CRC. */
					CRCTYPE crc;
					if(!m_filelist.GetCRC(t.fid, crc))
					{
						GAIA_AST(GAIA::ALWAYSFALSE);
						continue;
					}
					m_FileHeadSendMsgTemp.clear();
					m_FileHeadSendMsgTemp << t.na;
					m_FileHeadSendMsgTemp << MSG_A_FILEHEAD;
					m_FileHeadSendMsgTemp << t.fid;
					m_FileHeadSendMsgTemp << fsize;
					m_FileHeadSendMsgTemp << crc;
					this->Send(m_FileHeadSendMsgTemp.front_ptr(), m_FileHeadSendMsgTemp.write_size());
				}
				m_fileheadsendtasks_temp.clear();
			}

			m_perf.fExecuteFileHeadSend += FSHA_PERF - fPerf;
			return bRet;
		}
		GINL GAIA::BL OnExecuteLoopCommand()
		{
			GAIA::BL bRet = GAIA::False;
			if(m_szLoopCmd[0] != 0)
			{
				GAIA::U64 uTime = GAIA::TIME::tick_time();
				if(uTime - m_uLoopCmdLastFireTime > m_uLoopCmdEscape * 1000)
				{
					m_uLoopCmdLastFireTime = uTime;
					GAIA::TCH szTemp[MAXPATHLEN];
					GAIA::ALGORITHM::strcpy(szTemp, m_szLoopCmd);
					GAIA::ALGORITHM::replace(szTemp, GAIA::ALGORITHM::strlen(szTemp), '-', ' ');
					this->Command(szTemp);
					if(m_uLoopCmdTimes > 0)
						--m_uLoopCmdTimes;
					if(m_uLoopCmdTimes == 0)
					{
						m_szLoopCmd[0] = 0;
						m_uLoopCmdTimes = 0;
						m_uLoopCmdEscape = 0;
						m_uLoopCmdLastFireTime = 0;
					}
				}
			}
			return bRet;
		}
		GINL GAIA::BL OnHeartTick()
		{
			GAIA::F64 fPerf = FSHA_PERF;
			AL al(m_lr_links);
			for(__LinkListType::it it = m_links.front_it(); !it.empty(); ++it)
			{
				NLink& n = *it;
				if(n.state == NLink::STATE_READY)
				{
					m_HeartTickMsgTemp.clear();
					m_HeartTickMsgTemp << n.na;
					m_HeartTickMsgTemp << MSG_C_NOOP;
					this->Send(m_HeartTickMsgTemp.front_ptr(), m_HeartTickMsgTemp.write_size());
				}
			}
			m_perf.fHeartTick += FSHA_PERF - fPerf;
			return GAIA::True;
		}
		GINL GAIA::BL OnReceive(NHandle& s, const GAIA::U8* p, GAIA::U32 size)
		{
			GAIA::F64 fPerf = FSHA_PERF;
			m_statistics.uNRecvCount++;
			m_statistics.uNRecvBytes += size - sizeof(GAIA::NETWORK::NetworkAddress);
			m_OnReceiveMsgTemp.clear();
			m_OnReceiveMsgTemp.write(p, size);
			/* Basic message size checkup. */
			if(size < sizeof(GAIA::NETWORK::NetworkAddress) + sizeof(MSGIDTYPE))
			{
				m_perf.fOnRecv += FSHA_PERF - fPerf;
				return GAIA::False;
			}
			/* Ban IP checkup. */
			GAIA::NETWORK::NetworkAddress na;
			MSGIDTYPE msgid;
			m_OnReceiveMsgTemp >> na;
			m_OnReceiveMsgTemp >> msgid;
			{
				GAIA::F64 fPerfBanIPCheckup = FSHA_PERF;
				AL al(m_lr_banip);
				GAIA::U64 uOccurTime;
				GAIA::U64 uBanTime;
				if(m_banip.IsBanIP(na.ip, &uOccurTime, &uBanTime))
				{
					m_perf.fOnRecv += FSHA_PERF - fPerf;
					m_perf.fBanIPCheckUp += FSHA_PERF - fPerfBanIPCheckup;
					++m_statistics.uBanIPMessageCount;
					return GAIA::False;
				}
				m_perf.fBanIPCheckUp += FSHA_PERF - fPerfBanIPCheckup;
			}
			/* Login status checkup. */
			if(msgid != MSG_R_LOGIN)
			{
				AL al(m_lr_links);
				NLink nl;
				nl.na = na;
				nl.bBeLink = GAIA::True;
				NLink* pBeNL = m_links.find(nl);
				nl.bBeLink = GAIA::False;
				NLink* pNL = m_links.find(nl);
				if(pBeNL == GNULL && pNL == GNULL)
				{
					m_perf.fOnRecv += FSHA_PERF - fPerf;
					return GAIA::False; // Ignore not login's msg.
				}
			}
			/* Update last heart time. */
			{
				GAIA::F64 fPerfNoopC = FSHA_PERF;
				GAIA::U64 uClockTime = GAIA::TIME::tick_time();

				AL al1(m_lr_links);
				AL al2(m_lr_prilinks);
				NLink nl;
				nl.na = na;
				nl.bBeLink = GAIA::True;
				NLink* pNL = m_links.find(nl);
				if(pNL != GNULL)
					pNL->uLastHeartTime = uClockTime;
				nl.bBeLink = GAIA::False;
				pNL = m_links.find(nl);
				if(pNL != GNULL)
					pNL->uLastHeartTime = uClockTime;

				NLinkPri nlp;
				nlp.nlink = nl;
				nlp.nlink.bBeLink = GAIA::True;
				NLinkPri* pNLP = m_prilinks.find(nlp);
				if(pNLP != GNULL)
					pNLP->nlink.uLastHeartTime = uClockTime;
				nlp.nlink.bBeLink = GAIA::False;
				pNLP = m_prilinks.find(nlp);
				if(pNLP != GNULL)
					pNLP->nlink.uLastHeartTime = uClockTime;

				m_perf.fOnRecvNoopC += FSHA_PERF - fPerfNoopC;
			}
			/* Watch print. */
			GAIA::BL bWatchMatch = GAIA::False;
			if(m_test_enablewatch)
			{
				if(!m_test_watchna.ip.IsInvalid() && m_test_watchna.uPort != 0)
				{
					if(m_test_watchna.ip == na.ip && m_test_watchna.uPort == na.uPort)
						bWatchMatch = GAIA::True;
				}
				else if(!m_test_watchna.ip.IsInvalid())
				{
					if(m_test_watchna.ip == na.ip)
						bWatchMatch = GAIA::True;
				}
				else if(m_test_watchna.uPort != 0)
				{
					if(m_test_watchna.uPort == na.uPort)
						bWatchMatch = GAIA::True;
				}
			}
			/* message statistics. */
			#define MSGWATCHHEAD(sz) if(bWatchMatch){AL al(m_lr_prt); m_prt << "[TEST] Receive msg " << (sz) << ".\n ";}
			switch(msgid)
			{
			case MSG_R_LOGIN:
				m_statistics.uMsgRecvLoginCountR++;
				MSGWATCHHEAD("MSG_R_LOGIN");
				break;
			case MSG_R_LOGOUT:
				m_statistics.uMsgRecvLogoutCountR++;
				MSGWATCHHEAD("MSG_R_LOGOUT");
				break;
			case MSG_C_NOOP:
				m_statistics.uMsgRecvNoopCountC++;
				MSGWATCHHEAD("MSG_C_NOOP");
				break;
			case MSG_R_FILEHEAD:
				m_statistics.uMsgRecvFileHeadCountR++;
				MSGWATCHHEAD("MSG_R_FILEHEAD");
				break;
			case MSG_R_FILE:
				m_statistics.uMsgRecvFileCountR++;
				MSGWATCHHEAD("MSG_R_FILE");
				break;
			case MSG_R_FILECHUNK:
				m_statistics.uMsgRecvFileChunkCountR++;
				MSGWATCHHEAD("MSG_R_FILECHUNK");
				break;
			case MSG_A_FILEHEAD:
				m_statistics.uMsgRecvFileHeadCountA++;
				MSGWATCHHEAD("MSG_A_FILEHEAD");
				break;
			case MSG_A_FILECHUNK:
				m_statistics.uMsgRecvFileChunkCountA++;
				MSGWATCHHEAD("MSG_A_FILECHUNK");
				break;
			case MSG_A_FILENOTEXIST:
				m_statistics.uMsgRecvFileNotExistCountA++;
				MSGWATCHHEAD("MSG_A_FILENOTEXIST");
				break;
			case MSG_A_FILECMPL:
				m_statistics.uMsgRecvFileCmplCountA++;
				MSGWATCHHEAD("MSG_A_FILECMPL");
				break;
			case MSG_N_CMPLFILECOUNT:
				m_statistics.uMsgRecvCmplFileCountCountN++;
				MSGWATCHHEAD("MSG_N_CMPLFILECOUNT");
				break;
			case MSG_N_CMPLFILESECTION:
				m_statistics.uMsgRecvCmplFileSectionCountN++;
				MSGWATCHHEAD("MSG_N_CMPLFILESECTION");
				break;
			case MSG_A_CNN:
				m_statistics.uMsgRecvCNNCountA++;
				MSGWATCHHEAD("MSG_A_CNN");
				break;
			case MSG_A_LOGINOK:
				m_statistics.uMsgRecvLoginOKCountA++;
				MSGWATCHHEAD("MSG_A_LOGINOK");
				break;
			case MSG_A_LOGOUTOK:
				m_statistics.uMsgRecvLogoutOKCountA++;
				MSGWATCHHEAD("MSG_A_LOGOUTOK");
				break;
			case MSG_A_ERROR:
				m_statistics.uMsgRecvErrorCountA++;
				MSGWATCHHEAD("MSG_A_ERROR");
				break;
			default:
				MSGWATCHHEAD("InvalidMessageID");
				break;
			}
			/* message dispatch. */
			switch(msgid)
			{
			case MSG_R_LOGIN:
				{
					GAIA::F64 fPerfLoginR = FSHA_PERF;
					GAIA::TCH uname[USERNAMELEN + 1];
					GAIA::TCH password[USERNAMELEN + 1];
					m_OnReceiveMsgTemp >> uname;
					m_OnReceiveMsgTemp >> password;
					ERRNO en = this->BeLogin(na, uname, password);
					if(en != ERRNO_NOERROR && en != ERRNO_REPEATOP)
					{
						__MsgType newmsg;
						newmsg.reserve(1024);
						newmsg << na;
						newmsg << MSG_A_ERROR;
						newmsg << en;
						this->Send(newmsg.front_ptr(), newmsg.write_size());
					}
					else
					{
						__MsgType newmsg;
						newmsg.reserve(1024);
						newmsg << na;
						newmsg << MSG_A_LOGINOK;
						this->Send(newmsg.front_ptr(), newmsg.write_size());
					}
					m_perf.fOnRecvLoginR += FSHA_PERF - fPerfLoginR;
				}
				break;
			case MSG_R_LOGOUT:
				{
					GAIA::F64 fPerfLogoutR = FSHA_PERF;
					GAIA::TCH uname[USERNAMELEN + 1];
					m_OnReceiveMsgTemp >> uname;
					ERRNO en = this->BeLogout(na, uname);
					if(en != ERRNO_NOERROR)
					{
						__MsgType newmsg;
						newmsg.reserve(1024);
						newmsg << na;
						newmsg << MSG_A_ERROR;
						newmsg << en;
						this->Send(newmsg.front_ptr(), newmsg.write_size());
					}
					else
					{
						__MsgType newmsg;
						newmsg.reserve(1024);
						newmsg << na;
						newmsg << MSG_A_LOGOUTOK;
						this->Send(newmsg.front_ptr(), newmsg.write_size());
					}
					m_perf.fOnRecvLogoutR += FSHA_PERF - fPerfLogoutR;
				}
				break;
			case MSG_C_NOOP:
				{
				}
				break;
			case MSG_R_FILEHEAD:
				{
					GAIA::F64 fPerfFileHeadR = FSHA_PERF;
					FileHeadSendTask fhst;
					fhst.na = na;
					m_OnReceiveMsgTemp >> fhst.fid;
					AL al(m_lr_fileheadsendtasks);
					m_fileheadsendtasks.push_back(fhst);
					m_perf.fOnRecvFileHeadR += FSHA_PERF - fPerfFileHeadR;

					if(m_test_enablewatch && m_test_watchfid != (FILEID)GINVALID)
					{
						if(fhst.fid == m_test_watchfid)
						{
							AL al(m_lr_prt);
							m_prt << "[TEST] Been request file head.\n";
						}
					}
				}
				break;
			case MSG_R_FILE:
				{
					GAIA::F64 fPerfFileR = FSHA_PERF;
					m_statistics.uBeRequestFileCount += *(REQFILECOUNTTYPE*)m_OnReceiveMsgTemp.read_ptr();
					if(!this->Jump(na, m_OnReceiveMsgTemp.read_ptr(), m_OnReceiveMsgTemp.write_size() - m_OnReceiveMsgTemp.read_size()))
					{
						REQFILECOUNTTYPE fcnt;
						m_OnReceiveMsgTemp >> fcnt;
						for(REQFILECOUNTTYPE x = 0; x < fcnt; ++x)
						{
							FileSendTask fst;
							m_OnReceiveMsgTemp >> fst.fid;
							m_OnReceiveMsgTemp >> fst.ci;
							fst.na = na;
							fst.bNeedHead = GAIA::True;
							if(fst.fid < m_filelist.GetFileCount() && m_filestate.exist(fst.fid))
							{
								AL al(m_lr_filesendtasks);
								FileSendTask* pFST = m_filesendtasks.find(fst);
								if(pFST == GNULL)
								{
									if(m_filesendtasks.insert(fst))
										m_statistics.uSendFileCount++;
									else
										GAIA_AST(GAIA::ALWAYSFALSE);
								}
								else
									*pFST = fst;
							}
							else
							{
								__MsgType newmsg;
								newmsg.reserve(1024);
								newmsg << na;
								newmsg << MSG_A_FILENOTEXIST;
								newmsg << fst.fid;
								this->Send(newmsg.front_ptr(), newmsg.write_size());
							}
							if(m_test_enablewatch && m_test_watchfid != (FILEID)GINVALID)
							{
								if(fst.fid == m_test_watchfid)
								{
									AL al(m_lr_prt);
									m_prt << "[TEST] Been request file.\n";
								}
							}
						}
					}
					else
						m_OnReceiveMsgTemp.seek_read(m_OnReceiveMsgTemp.write_size(), GAIA::SEEK_TYPE_BEGIN);
					m_perf.fOnRecvFileR += FSHA_PERF - fPerfFileR;
				}
				break;
			case MSG_R_FILECHUNK:
				{
					GAIA::F64 fPerfFileChunkR = FSHA_PERF;
					m_statistics.uBeRequestChunkCount++;
					ChunkSendTask cst;
					cst.na = na;
					m_OnReceiveMsgTemp >> cst.fid;
					m_OnReceiveMsgTemp >> cst.ci;
					cst.sci = 0;
					AL al(m_lr_chunksendtasks);
					ChunkSendTask* pCST = m_chunksendtasks.find(cst);
					if(pCST == GNULL)
						m_chunksendtasks.insert(cst);
					else
						*pCST = cst;
					m_perf.fOnRecvFileChunkR += FSHA_PERF - fPerfFileChunkR;
					if(m_test_enablewatch && m_test_watchfid != (FILEID)GINVALID)
					{
						if(cst.fid == m_test_watchfid)
						{
							AL al(m_lr_prt);
							m_prt << "[TEST] Been request file chunk, ChunkIndex = " << (GAIA::N32)cst.ci << ".\n";
						}
					}
				}
				break;
			case MSG_A_FILEHEAD:
				{
					GAIA::F64 fPerfFileHeadA = FSHA_PERF;
					FileRecCache frc;
					m_OnReceiveMsgTemp >> frc.fid;
					m_OnReceiveMsgTemp >> frc.fsize;
					m_OnReceiveMsgTemp >> frc.uCRC;
					frc.bWrite = GAIA::True;
					AL al(m_lr_fcaches);
					FileRecCache* pFRC = m_fcaches.find(frc);
					if(pFRC == GNULL)
						m_fcaches.insert(frc);
					else
						pFRC->fsize = frc.fsize;
					if(frc.fsize == 0)
					{
						this->RequestFileRecCache(frc.fid, GAIA::True);
						this->ReleaseFileRecCache(frc);
						m_statistics.uEmptyFileCount++;
					}
					m_perf.fOnRecvFileHeadA += FSHA_PERF - fPerfFileHeadA;

					if(m_test_enablewatch && m_test_watchfid != (FILEID)GINVALID)
					{
						if(frc.fid == m_test_watchfid)
						{
							AL al(m_lr_prt);
							m_prt << "[TEST] Receive file head.\n";
						}
					}
				}
				break;
			case MSG_A_FILECHUNK:
				{
					FileWriteTask* pFWT = GNULL;
					{
						AL al(m_lr_fwtpool);
						pFWT = m_fwtpool.alloc();
					}
					GAIA::F64 fPerfFileChunkA = FSHA_PERF;
					m_statistics.uRecvChunkCount++;
					pFWT->na = na;
					m_OnReceiveMsgTemp >> pFWT->fid;
					m_OnReceiveMsgTemp >> pFWT->ci;
					m_OnReceiveMsgTemp >> pFWT->sci;
					m_OnReceiveMsgTemp >> pFWT->size;
					GAIA::BL bExist;
					{
						AL al(m_lr_filestate);
						bExist = m_filestate.exist(pFWT->fid);
					}
					if(pFWT->size > 0 && !bExist)
					{
						// Add to file task list.
						{
							m_OnReceiveMsgTemp.read(pFWT->buf, pFWT->size);
							AL al(m_lr_filewritetasks);
							m_filewritetasks.push_back(pFWT);
						}

						// Update uLastActiveTime.
						{
							AL al(m_lr_reqeds);
							FileReq fr;
							fr.fid = pFWT->fid;
							FileReq* pFR = m_reqeds.find(fr);
							if(pFR != GNULL)
								pFR->uLastActiveTime = GAIA::TIME::tick_time();
						}

						if(m_test_enablewatch && m_test_watchfid != (FILEID)GINVALID)
						{
							if(pFWT->fid == m_test_watchfid)
							{
								AL al(m_lr_prt);
								m_prt << "[TEST] Receive file chunk, ChunkIndex = " << (GAIA::N32)pFWT->ci << ", SubChunkIndex = " << (GAIA::N32)pFWT->sci << ".\n";
							}
						}
					}
					else
					{
						m_OnReceiveMsgTemp.seek_read(m_OnReceiveMsgTemp.write_size(), GAIA::SEEK_TYPE_BEGIN);

						AL al(m_lr_fwtpool);
						m_fwtpool.release(pFWT);
					}

					m_perf.fOnRecvFileChunkA += FSHA_PERF - fPerfFileChunkA;
				}
				break;
			case MSG_A_FILENOTEXIST:
				{
					GAIA::F64 fPerfFileNotExistA = FSHA_PERF;
					FILEID fid;
					m_OnReceiveMsgTemp >> fid;
					AL al(m_lr_reqeds);
					FileReq fr;
					fr.fid = fid;
					FileReq* pFinded = m_reqeds.find(fr);
					if(pFinded != GNULL)
					{
						FIDLIST listRequest;
						listRequest.push_back(fid);
						this->Request(m_mainna, listRequest);
					}
					m_perf.fOnRecvFileNotExistA += FSHA_PERF - fPerfFileNotExistA;
				}
				break;
			case MSG_A_FILECMPL:
				{
					GAIA::F64 fPerfFileCmplA = FSHA_PERF;
					FILEID fid;
					m_OnReceiveMsgTemp >> fid;

					// Clean up file send task.
					{
						AL al(m_lr_filesendtasks);
						FileSendTask fst;
						fst.na = na;
						fst.fid = fid;
						fst.ci = 0;
						fst.sci = 0;
						m_listFileCmplFileTemp.clear();
						for(__FileSendTaskListType::it it = m_filesendtasks.lower_bound(fst); !it.empty(); ++it)
						{
							FileSendTask& r = *it;
							if(r.na == fst.na && r.fid == fst.fid)
								m_listFileCmplFileTemp.push_back(r);
							else
								break;
						}
						for(GAIA::CONTAINER::Vector<FileSendTask>::it it = m_listFileCmplFileTemp.front_it(); !it.empty(); ++it)
							m_filesendtasks.erase(*it);
					}

					// Clean up chunk send task.
					{
						AL al(m_lr_chunksendtasks);
						ChunkSendTask cst;
						cst.na = na;
						cst.fid = fid;
						cst.ci = 0;
						cst.sci = 0;
						m_listFileCmplChunkTemp.clear();
						for(__ChunkSendTaskListType::it it = m_chunksendtasks.lower_bound(cst); !it.empty(); ++it)
						{
							ChunkSendTask& r = *it;
							if(r.na == cst.na && r.fid == cst.fid)
								m_listFileCmplChunkTemp.push_back(r);
							else
								break;
						}
						for(GAIA::CONTAINER::Vector<ChunkSendTask>::it it = m_listFileCmplChunkTemp.front_it(); !it.empty(); ++it)
							m_chunksendtasks.erase(*it);
					}
					m_perf.fOnRecvFileCmplA += FSHA_PERF - fPerfFileCmplA;
				}
				break;
			case MSG_N_CMPLFILECOUNT:
				{
					GAIA::F64 fPerfCmplFileCountN = FSHA_PERF;
					FILEID filecount;
					m_OnReceiveMsgTemp >> filecount;
					NLinkPri np;
					np.nlink.na = na;
					np.nlink.bBeLink = GAIA::True;
					AL al1(m_lr_links);
					NLink* pBeLink = m_links.find(np.nlink);
					np.nlink.bBeLink = GAIA::False;
					NLink* pLink = m_links.find(np.nlink);
					if(pLink == GNULL && (pBeLink == GNULL || pBeLink->state != NLink::STATE_READY))
					{
						__MsgType newmsg;
						newmsg.reserve(1024);
						newmsg << na;
						newmsg << MSG_A_ERROR;
						newmsg << ERRNO_NOTREADY;
						this->Send(newmsg.front_ptr(), newmsg.write_size());
						m_perf.fOnRecvCmplFileCountN += FSHA_PERF - fPerfCmplFileCountN;
						break;
					}
					GAIA::BL bExistStatistics = GAIA::False;
					if(pBeLink != GNULL)
					{
						m_statistics.uTotalCmplFileCount += filecount - pBeLink->uCmplFileCnt;
						bExistStatistics = GAIA::True;

						np.nlink.uCmplFileCnt = pBeLink->uCmplFileCnt;
						pBeLink->uCmplFileCnt = filecount;
						AL al2(m_lr_prilinks);
						np.nlink.bBeLink = GAIA::True;
						m_prilinks.erase(np);
						np.nlink.uCmplFileCnt = filecount;
						m_prilinks.insert(np);
					}
					if(pLink != GNULL)
					{
						if(!bExistStatistics)
						{
							m_statistics.uTotalCmplFileCount += filecount - pLink->uCmplFileCnt;
							bExistStatistics = GAIA::True;
						}

						np.nlink.uCmplFileCnt = pLink->uCmplFileCnt;
						pLink->uCmplFileCnt = filecount;
						AL al2(m_lr_prilinks);
						np.nlink.bBeLink = GAIA::False;
						m_prilinks.erase(np);
						np.nlink.uCmplFileCnt = filecount;
						m_prilinks.insert(np);
					}
					m_perf.fOnRecvCmplFileCountN += FSHA_PERF - fPerfCmplFileCountN;
				}
				break;
			case MSG_N_CMPLFILESECTION:
				{
					GAIA::F64 fPerfCmplFileSectionN = FSHA_PERF;
					FileIDSection fidsec;
					m_OnReceiveMsgTemp >> fidsec.uStart;
					m_OnReceiveMsgTemp >> fidsec.uEnd;
					if(fidsec.uStart > fidsec.uEnd)
					{
						m_perf.fOnRecvCmplFileSectionN += FSHA_PERF - fPerfCmplFileSectionN;
						break;
					}
					NLinkPri np;
					np.nlink.na = na;
					np.nlink.bBeLink = GAIA::True;
					AL al(m_lr_links);
					NLink* pBeLink = m_links.find(np.nlink);
					np.nlink.bBeLink = GAIA::False;
					NLink* pLink = m_links.find(np.nlink);
					if(pLink == GNULL && (pBeLink == GNULL || pBeLink->state != NLink::STATE_READY))
					{
						__MsgType newmsg;
						newmsg.reserve(1024);
						newmsg << na;
						newmsg << MSG_A_ERROR;
						newmsg << ERRNO_NOTREADY;
						this->Send(newmsg.front_ptr(), newmsg.write_size());
						m_perf.fOnRecvCmplFileSectionN += FSHA_PERF - fPerfCmplFileSectionN;
						break;
					}
					if(pBeLink != GNULL)
					{
						np.nlink.uCmplFileCnt = pBeLink->uCmplFileCnt;
						FILEID uIncreaseFileCnt = 0;
						this->CmplFileSectionRecursive(pBeLink, fidsec, uIncreaseFileCnt);
						if(uIncreaseFileCnt > 0)
						{
							FILEID uNewFileCount = GAIA::ALGORITHM::minimize(np.nlink.uCmplFileCnt + uIncreaseFileCnt, m_filelist.GetFileCount());
							m_statistics.uTotalCmplFileCount += uNewFileCount - np.nlink.uCmplFileCnt;
							AL al2(m_lr_prilinks);
							np.nlink.bBeLink = GAIA::True;
							m_prilinks.erase(np);
							np.nlink.uCmplFileCnt = uNewFileCount;
							m_prilinks.insert(np);
							pBeLink->uCmplFileCnt = np.nlink.uCmplFileCnt;
						}
					}
					m_perf.fOnRecvCmplFileSectionN += FSHA_PERF - fPerfCmplFileSectionN;
				}
				break;
			case MSG_A_CNN:
				{
					GAIA::F64 fPerfCnnA = FSHA_PERF;
					GAIA::NETWORK::NetworkAddress jumpna;
					m_OnReceiveMsgTemp >> jumpna;
					if(jumpna != na && jumpna != m_pNH->GetRemoteAddress())
					{
						REQFILECOUNTTYPE fcnt;
						m_OnReceiveMsgTemp >> fcnt;
						if(fcnt > 0)
						{
							FIDLIST listValidFile;
							{
								AL al(m_lr_reqeds);
								for(GAIA::N32 x = 0; x < fcnt; ++x)
								{
									FILEID fid;
									CHUNKINDEX ci;
									m_OnReceiveMsgTemp >> fid;
									m_OnReceiveMsgTemp >> ci;
									FileReq fr;
									fr.fid = fid;
									FileReq* pFinded = m_reqeds.find(fr);
									if(pFinded != GNULL)
										listValidFile.push_back(fid);
								}
							}
							if(!listValidFile.empty())
							{
								m_statistics.uBeJumpFileCount += listValidFile.size();
								AL al(m_lr_links);
								NLink nl;
								nl.na = jumpna;
								nl.bBeLink = GAIA::False;
								NLink* pNL = m_links.find(nl);
								if(pNL == GNULL)
								{
									this->NLogin(jumpna, INTERNAL_USERNAME, INTERNAL_PASSWORD);
									pNL = m_links.find(nl);
									GAIA_AST(!!pNL);
								}
								if(pNL->state == NLink::STATE_READY)
									this->Request(jumpna, listValidFile);
								else
								{
									JumpReq jr;
									jr.na = jumpna;
									jr.listFID = listValidFile;
									AL al(m_lr_jumpreqs);
									JumpReq* pJR = m_jumpreqs.find(jr);
									if(pJR == GNULL)
										m_jumpreqs.insert(jr);
									else
									{
										pJR->listFID += listValidFile;
										pJR->listFID.sort();
										pJR->listFID.unique();
									}
								}
							}
						}
					}
					m_perf.fOnRecvCnnA += FSHA_PERF - fPerfCnnA;
				}
				break;
			case MSG_A_LOGINOK:
				{
					GAIA::F64 fPerfLoginOKA = FSHA_PERF;
					{
						AL alprt(m_lr_prt);
						m_prt << "Login OK!" << "\n";
					}

					// Change link state.
					{
						AL al1(m_lr_links);
						NLink nl;
						nl.na = na;
						nl.bBeLink = GAIA::False;
						NLink* pNL = m_links.find(nl);
						if(pNL != GNULL)
						{
							pNL->state = NLink::STATE_READY;
							NLinkPri nlp;
							nlp.nlink = *pNL;
							AL al2(m_lr_prilinks);
							NLinkPri* pNLP = m_prilinks.find(nlp);
							if(pNLP != GNULL)
								pNLP->nlink.state = NLink::STATE_READY;
						}
						else
						{
							GAIA_AST(GAIA::ALWAYSFALSE);
							nl.state = NLink::STATE_READY;
							nl.pCmplFiles = new GAIA::CONTAINER::Set<FileIDSection>;
							nl.uLastHeartTime = GAIA::TIME::tick_time();
							m_links.insert(nl);
							NLinkPri nlp;
							nlp.nlink = nl;
							AL al2(m_lr_prilinks);
							m_prilinks.insert(nlp);
						}
					}

					// Statistics file state.
					FILEID uFileCount = 0;
					GAIA::CONTAINER::Vector<FileIDSection> fidseclist;
					if(na == m_mainna)
						m_state = NLink::STATE_READY;
					{
						AL al(m_lr_filestate);
						FILEID startindex = (FILEID)GINVALID;
						for(GAIA::CONTAINER::BasicBitset<GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32> >::_sizetype x = 0; x < m_filelist.GetFileCount(); ++x)
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
									uFileCount += fidsec.uEnd - fidsec.uStart + 1;
									fidseclist.push_back(fidsec);
									startindex = (FILEID)GINVALID;
								}
							}
						}
						if(startindex != GINVALID)
						{
							FileIDSection fidsec;
							fidsec.uStart = startindex;
							fidsec.uEnd = m_filelist.GetFileCount() - 1;
							uFileCount += fidsec.uEnd - fidsec.uStart + 1;
							fidseclist.push_back(fidsec);
							startindex = (FILEID)GINVALID;
						}
					}
					// Send file count.
					{
						__MsgType newmsg;
						newmsg.reserve(1024);
						newmsg << na;
						newmsg << MSG_N_CMPLFILECOUNT;
						newmsg << uFileCount;
						this->Send(newmsg.front_ptr(), newmsg.write_size());
					}
					// Send file section.
					{
						for(GAIA::CONTAINER::Vector<FileIDSection>::it it = fidseclist.front_it(); !it.empty(); ++it)
						{
							__MsgType newmsg;
							newmsg.reserve(1024);
							newmsg << na;
							newmsg << MSG_N_CMPLFILESECTION;
							newmsg << (*it).uStart;
							newmsg << (*it).uEnd;
							this->Send(newmsg.front_ptr(), newmsg.write_size());
						}
					}
					// Send jump file request.
					{
						AL al(m_lr_jumpreqs);
						JumpReq jr;
						jr.na = na;
						JumpReq* pJR = m_jumpreqs.find(jr);
						if(pJR != GNULL)
						{
							this->Request(pJR->na, pJR->listFID);
							m_jumpreqs.erase(jr);
						}
					}
					m_perf.fOnRecvLoginOKA += FSHA_PERF - fPerfLoginOKA;
				}
				break;
			case MSG_A_LOGOUTOK:
				{
					GAIA::F64 fPerfLogoutOKA = FSHA_PERF;
					AL alprt(m_lr_prt);
					m_prt << "Logout OK!" << "\n";
					m_perf.fOnRecvLogoutOKA += FSHA_PERF - fPerfLogoutOKA;
				}
				break;
			case MSG_A_ERROR:
				{
					GAIA::F64 fPerfErrorA = FSHA_PERF;
					ERRNO en;
					m_OnReceiveMsgTemp >> en;
					const GAIA::TCH* pszError = this->ErrorString(en);
					AL alprt(m_lr_prt);
					if(pszError == GNULL)
						m_prt << "Known error!" << "\n";
					else
						m_prt << "Error! ErrorNo = " << pszError << "\n";
					m_perf.fOnRecvErrorA += FSHA_PERF - fPerfErrorA;
				}
				break;
			default:
				GAIA_AST(GAIA::ALWAYSFALSE);
				m_perf.fOnRecv += FSHA_PERF - fPerf;
				return GAIA::False;
			}
			GAIA_AST(m_OnReceiveMsgTemp.read_size() == m_OnReceiveMsgTemp.write_size());
			m_perf.fOnRecv += FSHA_PERF - fPerf;
			return GAIA::True;
		}
		GINL GAIA::GVOID OnLostConnection(const GAIA::NETWORK::NetworkAddress& na, GAIA::BL bRecvTrueSendFalse)
		{
		}
		GINL GAIA::BL NLogin(const GAIA::NETWORK::NetworkAddress& na, const GAIA::TCH* pszUserName, const GAIA::TCH* pszPassword)
		{
			__MsgType msg;
			msg.reserve(1024);
			msg << na;
			msg << MSG_R_LOGIN;
			msg << pszUserName;
			msg << pszPassword;
			if(m_mainna.IsInvalid())
				m_mainna = na;

			// Add new link.
			{
				AL al1(m_lr_links);
				NLink nl;
				nl.na = na;
				nl.bBeLink = GAIA::False;
				NLink* pNL = m_links.find(nl);
				if(pNL != GNULL)
				{
					pNL->state = NLink::STATE_DISCONNECT;
					NLinkPri nlp;
					nlp.nlink = *pNL;
					AL al2(m_lr_prilinks);
					NLinkPri* pNLP = m_prilinks.find(nlp);
					if(pNLP != GNULL)
						pNLP->nlink.state = NLink::STATE_DISCONNECT;
				}
				else
				{
					nl.state = NLink::STATE_DISCONNECT;
					nl.pCmplFiles = new GAIA::CONTAINER::Set<FileIDSection>;
					nl.uLastHeartTime = GAIA::TIME::tick_time();
					m_links.insert(nl);
					NLinkPri nlp;
					nlp.nlink = nl;
					AL al2(m_lr_prilinks);
					m_prilinks.insert(nlp);
				}
			}

			return this->Send(msg.front_ptr(), msg.write_size());
		}
		GINL ERRNO BeLogin(const GAIA::NETWORK::NetworkAddress& na, const GAIA::TCH* pszUserName, const GAIA::TCH* pszPassword)
		{
			GAIA_AST(!GAIA::ALGORITHM::stremp(pszUserName));
			if(GAIA::ALGORITHM::stremp(pszUserName))
				return ERRNO_INVALIDPARAM;
			if(GAIA::ALGORITHM::strcmp(pszUserName, INTERNAL_USERNAME) == 0)
			{
				if(GAIA::ALGORITHM::stremp(INTERNAL_PASSWORD) &&
					GAIA::ALGORITHM::stremp(pszPassword))
				{
				}
				else if(!GAIA::ALGORITHM::stremp(INTERNAL_PASSWORD) &&
					GAIA::ALGORITHM::stremp(pszPassword))
					return ERRNO_PASSWORD;
				else if(GAIA::ALGORITHM::stremp(INTERNAL_PASSWORD) &&
					!GAIA::ALGORITHM::stremp(pszPassword))
					return ERRNO_PASSWORD;
				else
				{
					if(GAIA::ALGORITHM::strcmp(pszPassword, INTERNAL_PASSWORD) != 0)
						return ERRNO_PASSWORD;
				}
			}
			else
			{
				AL al(m_lr_usergroup);
				if(!m_usergroup.FindUser(pszUserName))
					return ERRNO_USERNAME;
				const GAIA::TCH* pszCorrectPassword = m_usergroup.GetUserPassword(pszUserName);
				if(GAIA::ALGORITHM::stremp(pszCorrectPassword) &&
					GAIA::ALGORITHM::stremp(pszPassword))
				{
				}
				else if(!GAIA::ALGORITHM::stremp(pszCorrectPassword) &&
					GAIA::ALGORITHM::stremp(pszPassword))
					return ERRNO_PASSWORD;
				else if(GAIA::ALGORITHM::stremp(pszCorrectPassword) &&
					!GAIA::ALGORITHM::stremp(pszPassword))
					return ERRNO_PASSWORD;
				else
				{
					if(GAIA::ALGORITHM::strcmp(pszPassword, pszCorrectPassword) != 0)
						return ERRNO_PASSWORD;
				}
			}
			NLink nl;
			nl.na = na;
			nl.bBeLink = GAIA::True;
			AL al1(m_lr_links);
			NLink* pNL = m_links.find(nl);
			if(pNL != GNULL)
			{
				if(pNL->state == NLink::STATE_READY)
					return ERRNO_REPEATOP;
				pNL->state = NLink::STATE_READY;
				NLinkPri nlp;
				nlp.nlink = *pNL;
				AL al2(m_lr_prilinks);
				NLinkPri* pNLP = m_prilinks.find(nlp);
				if(pNLP != GNULL)
					pNLP->nlink.state = NLink::STATE_READY;
			}
			else
			{
				nl.state = NLink::STATE_READY;
				nl.pCmplFiles = new GAIA::CONTAINER::Set<FileIDSection>;
				nl.uLastHeartTime = GAIA::TIME::tick_time();
				m_links.insert(nl);
				NLinkPri nlp;
				nlp.nlink = nl;
				AL al2(m_lr_prilinks);
				m_prilinks.insert(nlp);
			}
			// Send file count.
			{
				__MsgType msg;
				msg.reserve(1024);
				msg << na;
				msg << MSG_N_CMPLFILECOUNT;
				msg << m_uCmplFileCount;
				this->Send(msg.front_ptr(), msg.write_size());
			}
			return ERRNO_NOERROR;
		}
		GINL GAIA::BL NLogout(const GAIA::NETWORK::NetworkAddress& na, const GAIA::TCH* pszUserName)
		{
			// Release a exist link.
			{
				AL al1(m_lr_links);
				NLink nl;
				nl.na = na;
				nl.bBeLink = GAIA::False;
				NLink* pNL = m_links.find(nl);
				if(pNL != GNULL)
				{
					NLinkPri nlp;
					nlp.nlink = *pNL;
					AL al2(m_lr_prilinks);
					m_prilinks.erase(nlp);
				}
				m_links.erase(nl);
			}

			__MsgType msg;
			msg.reserve(1024);
			msg << na;
			msg << MSG_R_LOGOUT;
			msg << pszUserName;
			return this->Send(msg.front_ptr(), msg.write_size());
		}
		GINL ERRNO BeLogout(const GAIA::NETWORK::NetworkAddress& na, const GAIA::TCH* pszUserName)
		{
			GAIA_AST(!GAIA::ALGORITHM::stremp(pszUserName));
			if(GAIA::ALGORITHM::stremp(pszUserName))
				return ERRNO_INVALIDPARAM;
			AL al1(m_lr_usergroup);
			if(!m_usergroup.FindUser(pszUserName))
				return ERRNO_USERNAME;
			NLink nl;
			nl.na = na;
			nl.bBeLink = GAIA::True;
			AL al2(m_lr_links);
			NLink* pLink = m_links.find(nl);
			if(pLink == GNULL)
				return ERRNO_NOTREADY;
			else
			{
				if(pLink->state != NLink::STATE_READY)
					return ERRNO_NOTREADY;
			}
			pLink->state = NLink::STATE_ONLINE;
			return ERRNO_NOERROR;
		}
		GINL FileRecCache* RequestFileRecCache(const FILEID& fid, GAIA::BL bWrite)
		{
			FileRecCache frc;
			frc.fid = fid;
			frc.bWrite = bWrite;
			FileRecCache* pFRC = m_fcaches.find(frc);
			if(pFRC == GNULL)
			{
				if(!m_filelist.GetCRC(fid, frc.uCRC))
					return GNULL;
				m_fcaches.insert(frc);
				pFRC = m_fcaches.find(frc);
			}
			if(pFRC->pFA == GNULL)
				pFRC->pFA = m_desc.pFAC->CreateFileAccess();
			if(!pFRC->pFA->IsOpen())
			{
				GAIA::TCH szFileName[MAXPATHLEN];
				if(m_filelist.GetName(fid, szFileName))
				{
					GAIA::TCH szFullName[MAXPATHLEN];
					if(bWrite)
					{
						if(m_writeroot.empty())
							szFullName[0] = 0;
						else
							GAIA::ALGORITHM::strcpy(szFullName, m_writeroot.front_ptr());
					}
					else
					{
						if(m_readroot.empty())
							szFullName[0] = 0;
						else
							GAIA::ALGORITHM::strcpy(szFullName, m_readroot.front_ptr());
					}
					GAIA::ALGORITHM::strcat(szFullName, szFileName);
					if(bWrite)
					{
						GAIA::TCH szPath[MAXPATHLEN];
						GAIA::ALGORITHM::strcpy(szPath, szFullName);
						GAIA::ALGORITHM::strdropr(szPath, _T("/\\"));
						GAIA::FILESYSTEM::Directory dir;
						if(!dir.Exist(szPath))
						{
							if(!dir.Create(szPath, GAIA::True))
							{
								GAIA_AST(GAIA::ALWAYSFALSE);
								return GNULL;
							}
						}
					}
					if(!pFRC->pFA->Open(szFullName, !bWrite))
					{
						GAIA_AST(GAIA::ALWAYSFALSE);
						return GNULL;
					}
					if(!bWrite)
					{
						pFRC->pFA->Seek(GAIA::SEEK_TYPE_END, 0);
						pFRC->fsize = (FILESIZETYPE)pFRC->pFA->Tell();
						pFRC->pFA->Seek(GAIA::SEEK_TYPE_BEGIN, 0);
					}
				}
			}
			return pFRC;
		}
		GINL GAIA::BL ReleaseFileRecCache(const FileRecCache& frc)
		{
			m_statistics.uRequestFileCmplCount++;
			this->SetFileCmpl(frc.fid, GAIA::True);
			/* Release FileRecCache. */
			{
				AL al(m_lr_fcaches);
				FileRecCache* pFRC = m_fcaches.find(frc);
				if(pFRC != GNULL)
				{
					if(pFRC->pFA != GNULL)
					{
						pFRC->pFA->Close();
						m_desc.pFAC->ReleaseFileAccess(pFRC->pFA);
						pFRC->pFA = GNULL;
					}
					if(pFRC->pFCSL != GNULL)
					{
						delete pFRC->pFCSL;
						pFRC->pFCSL = GNULL;
					}
					m_fcaches.erase(frc);
				}
			}
			/* Remove from requested set. */
			{
				AL al(m_lr_reqeds);
				FileReq fr;
				fr.fid = frc.fid;
				FileReq* pFR = m_reqeds.find(fr);
				if(pFR != GNULL)
				{
					GAIA::F64 fTime = (GAIA::F64)(GAIA::TIME::tick_time() - pFR->uFirstReqTime) * 0.001 * 0.001;
					if(fTime > m_perf.fMaxFileCmplTime)
						m_perf.fMaxFileCmplTime = fTime;
					if(fTime < m_perf.fMinFileCmplTime)
						m_perf.fMinFileCmplTime = fTime;
					m_perf.fSumFileCmplTime += fTime;
					m_reqeds.erase(fr);
				}
			}
			/* Add to complete file list. */
			{
				AL al(m_lr_cmplfiles);
				m_cmplfiles.push_back(frc.fid);
			}
			return GAIA::True;
		}
		GINL FILESIZETYPE GetFileCacheCompleteSize(const FileRecCache& frc) const
		{
			FILESIZETYPE tRet = 0;
			if(frc.pFCSL != GNULL)
			{
				FileRecCache::__FileChunkSectionListType::const_it it = frc.pFCSL->const_front_it();
				for(; !it.empty(); ++it)
				{
					const FileRecCache::__FileChunkSectionListType::_datatype& t = *it;
					tRet += (t.e * CHUNKSIZE + t.ee * SUBCHUNKSIZE) - (t.s * CHUNKSIZE + t.ss * SUBCHUNKSIZE) + SUBCHUNKSIZE;
				}
			}
			return tRet;
		}
		GINL GAIA::BL Send(const GAIA::GVOID* p, const GAIA::U32& size)
		{
			GAIA_AST(!!p);
			GAIA_AST(size > 0);
			if(m_pNH == GNULL)
				return GAIA::False;
			/* message statistics. */
			MSGIDTYPE msgid = *(MSGIDTYPE*)((GAIA::U8*)p + sizeof(GAIA::NETWORK::NetworkAddress));
			switch(msgid)
			{
			case MSG_R_LOGIN:
				m_statistics.uMsgSendLoginCountR++;
				break;
			case MSG_R_LOGOUT:
				m_statistics.uMsgSendLogoutCountR++;
				break;
			case MSG_C_NOOP:
				m_statistics.uMsgSendNoopCountC++;
				break;
			case MSG_R_FILEHEAD:
				m_statistics.uMsgSendFileHeadCountR++;
				break;
			case MSG_R_FILE:
				m_statistics.uMsgSendFileCountR++;
				break;
			case MSG_R_FILECHUNK:
				m_statistics.uMsgSendFileChunkCountR++;
				break;
			case MSG_A_FILEHEAD:
				m_statistics.uMsgSendFileHeadCountA++;
				break;
			case MSG_A_FILECHUNK:
				m_statistics.uMsgSendFileChunkCountA++;
				break;
			case MSG_A_FILENOTEXIST:
				m_statistics.uMsgSendFileNotExistCountA++;
				break;
			case MSG_A_FILECMPL:
				m_statistics.uMsgSendFileCmplCountA++;
				break;
			case MSG_N_CMPLFILECOUNT:
				m_statistics.uMsgSendCmplFileCountCountN++;
				break;
			case MSG_N_CMPLFILESECTION:
				m_statistics.uMsgSendCmplFileSectionCountN++;
				break;
			case MSG_A_CNN:
				m_statistics.uMsgSendCNNCountA++;
				break;
			case MSG_A_LOGINOK:
				m_statistics.uMsgSendLoginOKCountA++;
				break;
			case MSG_A_LOGOUTOK:
				m_statistics.uMsgSendLogoutOKCountA++;
				break;
			case MSG_A_ERROR:
				m_statistics.uMsgSendErrorCountA++;
				break;
			default:
				break;
			}
			/* Send. */
			AL al(m_lr_send);
			m_statistics.uNSendCount++;
			m_statistics.uNSendBytes += size - sizeof(GAIA::NETWORK::NetworkAddress);
			return m_pNH->Send((const GAIA::U8*)p, size);
		}
		GINL GAIA::BL SendToAll(GAIA::GVOID* p, const GAIA::U32& size)
		{
			GAIA_AST(!!p);
			GAIA_AST(size > 0);
			if(m_pNH == GNULL)
				return GAIA::False;
			GAIA::BL bRet = GAIA::True;
			AL al(m_lr_links);
			for(__LinkListType::it it = m_links.front_it(); !it.empty(); ++it)
			{
				NLink& nl = *it;
				if(nl.state == NLink::STATE_READY)
				{
					GAIA::ALGORITHM::xmemcpy(p, &nl.na, sizeof(nl.na));
					if(!this->Send(p, size))
						bRet = GAIA::False;
				}
			}
			return bRet;
		}
		GINL GAIA::GVOID CmplFileSectionRecursive(NLink* pLink, FileIDSection fidsec, FILEID& uIncreaseFileCnt)
		{
			GAIA::CONTAINER::Set<FileIDSection>::it it = pLink->pCmplFiles->lower_bound(fidsec);
			if(it.empty())
			{
				it = pLink->pCmplFiles->upper_bound(fidsec);
				if(it.empty())
				{
					pLink->pCmplFiles->insert(fidsec);
					uIncreaseFileCnt += fidsec.uEnd - fidsec.uStart + 1;
				}
				else
				{
					FileIDSection& fidsec_prev = *it;
					if(fidsec_prev.uEnd + 1 >= fidsec.uStart)
					{
						if(fidsec.uEnd > fidsec_prev.uEnd)
						{
							uIncreaseFileCnt += fidsec.uEnd - fidsec_prev.uEnd;
							fidsec_prev.uEnd = fidsec.uEnd;
						}
					}
					else
					{
						pLink->pCmplFiles->insert(fidsec);
						uIncreaseFileCnt += fidsec.uEnd - fidsec.uStart + 1;
					}
				}
			}
			else
			{
				FileIDSection& fidsec_next = *it;
				--it;
				if(it.empty())
				{
					FileIDSection fidsecnew;
					GAIA::N32 nSplitCnt = this->SplitFileIDSectionLeft(fidsec, fidsec_next, fidsecnew);
					if(nSplitCnt == 0)
					{
						pLink->pCmplFiles->insert(fidsec);
						uIncreaseFileCnt += fidsec.uEnd - fidsec.uStart + 1;
					}
					else
					{
						uIncreaseFileCnt += fidsec_next.uStart - fidsec.uStart;
						fidsec_next.uStart = fidsec.uStart;
						if(nSplitCnt == 2)
							this->CmplFileSectionRecursive(pLink, fidsecnew, uIncreaseFileCnt);
					}
				}
				else
				{
					FileIDSection& fidsec_prev = *it;
					if(fidsec.uStart <= fidsec_prev.uEnd + 1 &&
						fidsec.uEnd + 1 >= fidsec_next.uStart)
					{
						GAIA_AST(fidsec_next.uStart > fidsec_prev.uEnd);
						uIncreaseFileCnt += fidsec_next.uStart - fidsec_prev.uEnd - 1;
						fidsec_prev.uEnd = fidsec_next.uEnd;
						pLink->pCmplFiles->erase(fidsec_next);

					}
					if(fidsec.uStart < fidsec_prev.uStart)
					{
						FileIDSection fidsecnew;
						fidsecnew.uStart = fidsec.uStart;
						fidsec.uEnd = fidsec_prev.uStart - 1;
						this->CmplFileSectionRecursive(pLink, fidsecnew, uIncreaseFileCnt);
					}
					if(fidsec.uEnd > fidsec_next.uEnd)
					{
						FileIDSection fidsecnew;
						fidsecnew.uStart = fidsec_next.uStart + 1;
						fidsecnew.uEnd = fidsec.uEnd;
						this->CmplFileSectionRecursive(pLink, fidsecnew, uIncreaseFileCnt);
					}
				}
			}
		}
		GINL GAIA::N32 SplitFileIDSectionLeft(FileIDSection& src, const FileIDSection& dst, FileIDSection& splitnew)
		{
			GAIA_AST(src.uStart <= dst.uStart);
			if(src.uEnd + 1 >= dst.uStart)
			{
				if(src.uEnd <= dst.uEnd)
					return 1;
				else
				{
					splitnew.uStart = dst.uEnd + 1;
					splitnew.uEnd = src.uEnd;
					return 2;
				}
			}
			else
				return 0;
		}
		GINL GAIA::BL Jump(const GAIA::NETWORK::NetworkAddress& na, const GAIA::U8* p, GAIA::N32 nSize)
		{
			GAIA_AST(!!p);
			GAIA_AST(nSize > 0);
			if(m_mainna.IsInvalid())
			{
				if(GAIA::MATH::xrandom() % 100 > MAINJUMPODDS)
					return GAIA::False;
			}
			else
			{
				if(GAIA::MATH::xrandom() % 100 > SUBJUMPODDS)
					return GAIA::False;
			}
			GAIA::NETWORK::NetworkAddress jumpna;
			{
				AL al1(m_lr_links);
				NLink nl;
				nl.na = na;
				nl.bBeLink = GAIA::True;
				NLink* pNL = m_links.find(nl);
				if(pNL == GNULL)
					return GAIA::False;
				NLinkPri nlp;
				nlp.nlink = *pNL;
				AL al2(m_lr_prilinks);
				__LinkPriListType::it it = m_prilinks.lower_bound(nlp);
				GAIA::N32 index = 0;
				NLinkPri* listLinkPri[JUMPDISTANCE];
				for(; !it.empty(); ++it)
				{
					if(index >= JUMPDISTANCE)
						break;
					NLinkPri& nlp = (*it);
					if(nlp.nlink.na == na)
						continue;
					if(nlp.nlink.na == m_mainna)
						continue;
					if(!nlp.nlink.bBeLink)
						continue;
					GAIA_AST(nlp.nlink.uCmplFileCnt >= pNL->uCmplFileCnt);
					if(nlp.nlink.uCmplFileCnt - pNL->uCmplFileCnt <= JUMPOFFSETFILESCOUNT)
						continue;
					listLinkPri[index++] = &nlp;
					++it;
				}
				if(index == 0)
					return GAIA::False;
				jumpna = listLinkPri[GAIA::MATH::xrandom() % index]->nlink.na;
			}
			GAIA_AST(jumpna != na);
			const REQFILECOUNTTYPE& fcnt = *(const REQFILECOUNTTYPE*)p;
			__MsgType msg;
			msg.reserve(1024);
			if(sizeof(na) + sizeof(MSGIDTYPE) + sizeof(jumpna) + nSize > GAIA::NETWORK::NetworkHandle::MAX_NOSTABILITY_SENDSIZE)
			{
				GAIA_AST(fcnt / 2 > 0);
				GAIA::N32 first = fcnt / 2;
				GAIA::N32 second = first + (fcnt % 2 == 0 ? 0 : 1);
				GAIA::N32 nodesize = sizeof(FILEID) + sizeof(CHUNKINDEX);

				msg << na;
				msg << MSG_A_CNN;
				msg << jumpna;
				msg << (REQFILECOUNTTYPE)first;
				msg.write(p + sizeof(fcnt), first * nodesize);
				this->Send(msg.front_ptr(), msg.write_size());

				msg.clear();
				msg << na;
				msg << MSG_A_CNN;
				msg << jumpna;
				msg << (REQFILECOUNTTYPE)second;
				msg.write(p + sizeof(fcnt) + first * nodesize, second * nodesize);
				this->Send(msg.front_ptr(), msg.write_size());

				GAIA_AST(first + second == fcnt);
				m_statistics.uJumpFileCount += first + second;
			}
			else
			{
				msg << na;
				msg << MSG_A_CNN;
				msg << jumpna;
				msg.write(p, nSize);
				this->Send(msg.front_ptr(), msg.write_size());

				m_statistics.uJumpFileCount += fcnt;
			}
			return GAIA::True;
		}
		GINL GAIA::BL SelectRequestNetworkAddress(GAIA::NETWORK::NetworkAddress& na) const
		{
			NLinkPri nlp;
			nlp.nlink.uCmplFileCnt = m_uCmplFileCount + JUMPOFFSETFILESCOUNT;
			__LinkPriListType::const_it it = m_prilinks.lower_bound(nlp);
			const NLinkPri* reslist[JUMPDISTANCE];
			GAIA::U32 uCount = 0;
			for(; !it.empty(); ++it)
			{
				if(uCount >= JUMPDISTANCE)
					break;
				const NLinkPri& nlp = *it;
				if(nlp.nlink.bBeLink)
					continue;
				if(nlp.nlink.na == m_mainna)
					continue;
				if(nlp.nlink.state != NLink::STATE_READY)
					continue;
				reslist[uCount++] = &nlp;
			}
			if(uCount == 0 && m_mainna.IsInvalid())
				return GAIA::False;
			GAIA::N32 nSelectIndex = GAIA::MATH::xrandom() % (uCount + 1);
			if(nSelectIndex == 0)
				na = m_mainna;
			else
				na = reslist[nSelectIndex - 1]->nlink.na;
			return GAIA::True;
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
		BanIP m_banip; GAIA::SYNC::Lock m_lr_banip;
		MainWorkThread* m_pMWThread;
		HeartTickThread* m_pHeartTickThread;
		NHandle* m_pNH;
		NReceiver* m_pNReceiver;
		NSender* m_pNSender;
		NListener* m_pNListener;
		NAcceptCallBack m_NAcceptCallBack;
		GAIA::PRINT::Print m_prt; GAIA::SYNC::Lock m_lr_prt;
		FSTR m_readroot;
		FSTR m_writeroot;
		__LinkListType m_links; GAIA::SYNC::Lock m_lr_links;
		__LinkPriListType m_prilinks; GAIA::SYNC::Lock m_lr_prilinks;
		GAIA::CONTAINER::BasicBitset<GAIA::N32, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32> > m_filestate; GAIA::SYNC::Lock m_lr_filestate;
		FILEID m_uCmplFileCount;
		NLink::STATE m_state;
		GAIA::BL m_bEnableSequenceRequest;
		FILEID m_uSequenceRequestIndex;
		__FileRecCacheListType m_fcaches; GAIA::SYNC::Lock m_lr_fcaches;
		__FileSendTaskListType m_filesendtasks; GAIA::SYNC::Lock m_lr_filesendtasks;
		__ChunkSendTaskListType m_chunksendtasks; GAIA::SYNC::Lock m_lr_chunksendtasks;
		__FileWriteTaskListType m_filewritetasks; GAIA::SYNC::Lock m_lr_filewritetasks;
		__FileReqQueueType m_reqs; GAIA::SYNC::Lock m_lr_reqs;
		__FileReqSetType m_reqeds; GAIA::SYNC::Lock m_lr_reqeds;
		__JumpReqSetType m_jumpreqs; GAIA::SYNC::Lock m_lr_jumpreqs;
		FIDLIST m_cmplfiles; GAIA::SYNC::Lock m_lr_cmplfiles;
		__FileWriteTaskPoolType m_fwtpool; GAIA::SYNC::Lock m_lr_fwtpool;
		__FileHeadSendTaskListType m_fileheadsendtasks; GAIA::SYNC::Lock m_lr_fileheadsendtasks;
		GAIA::SYNC::Lock m_lr_send;
		GAIA::N32 m_nMaxRequestFileCountSameTime;
		GAIA::BL m_bEnableRecycleLink;
		GAIA::U64 m_uLastNotifyCmplTime;
		GAIA::TCH m_szLoopCmd[MAXPATHLEN];
		GAIA::U64 m_uLoopCmdTimes;
		GAIA::U64 m_uLoopCmdEscape;
		GAIA::U64 m_uLoopCmdLastFireTime;
		GAIA::U64 m_uLastBanIPExecute;
		Statistics m_statistics;
		Perf m_perf;
		Statistics m_statistics_last;
		Perf m_perf_last;

		__FileReqListType m_listFileReqTemp;
		GAIA::CONTAINER::Vector<FileSendTask> m_listFileDeleteTemp;
		GAIA::CONTAINER::Vector<ChunkSendTask> m_listChunkDeleteTemp;
		GAIA::CONTAINER::Vector<FileRecCache> m_listCompleteTemp;
		GAIA::CONTAINER::Vector<NLink> m_listRecycleTemp;
		GAIA::CONTAINER::Vector<FileSendTask> m_listFileCmplFileTemp;
		GAIA::CONTAINER::Vector<ChunkSendTask> m_listFileCmplChunkTemp;
		FIDLIST m_listReRequestTemp;
		__MsgType m_FileSendMsgTemp;
		__MsgType m_ChunkSendMsgTemp;
		__MsgType m_OnReceiveMsgTemp;
		__MsgType m_TimeoutSectionRequestMsgTemp;
		__MsgType m_TimeoutChunkRequestMsgTemp;
		__MsgType m_RequestMsgTemp; GAIA::SYNC::Lock m_lr_RequestMsgTemp;
		__MsgType m_HeartTickMsgTemp;
		__MsgType m_ExecuteCmplFilesNotifyMsgTemp;
		__MsgType m_RecycleLinkMsgTemp;
		__MsgType m_FileHeadSendMsgTemp;
		__FileWriteTaskListType m_filewritetasks_temp;
		__FileHeadSendTaskListType m_fileheadsendtasks_temp;

		GAIA::BL m_test_enablewatch;
		FILEID m_test_watchfid;
		GAIA::NETWORK::NetworkAddress m_test_watchna;
	};
};

#endif
