#ifndef 	__PROMETHEUS_H__
#define 	__PROMETHEUS_H__

#include "../GAIA/gaia.h"
#include "../DWARFS/MISC/cmdparam.h"
#include "../DWARFS/MISC/textline.h"

namespace PROM
{
	static const GAIA::TCH VERSION_STRING[] = _T("00.00.01.00");
	static const GAIA::U32 VERSION = 0x00000100;
	static const GAIA::TCH FILEBREAK[] = _T("\r\n");

	typedef GAIA::TCH __FileNameChar;
	typedef GAIA::CONTAINER::TString __FileName;
	typedef GAIA::CONTAINER::TString __WordType;

	template<typename _DataType> GAIA::BL is_word_char(_DataType t)
	{
		if(t >= 'a' && t <= 'z' ||
			t >= 'A' && t <= 'Z' ||
			t >= '0' && t <= '9' ||
			t == '_')
			return GAIA::True;
		return GAIA::False;
	}
	template<typename _DataType> GAIA::BL is_blank_char(_DataType t)
	{
		if(t == ' ' || t == '\t')
			return GAIA::True;
		return GAIA::False;
	}

	class Prom : public GAIA::Entity
	{
	private:
		class ERROR_SYSTEM
		{
		public:
			GAIA_ENUM_BEGIN(ERROR_TYPE)
				ERROR_TYPE_INTERNAL_WARNING,
				ERROR_TYPE_INTERNAL_ERROR,
				ERROR_TYPE_WARING,
				ERROR_TYPE_ERROR,
			GAIA_ENUM_END(ERROR_TYPE)
			class ErrorBase : public GAIA::Entity
			{
			public:
				GINL ErrorBase(){m_uFileLine = (GAIA::U32)GINVALID;}
				virtual GAIA::U16 getid() const = 0;
				virtual GAIA::U8 getstage() const = 0;
				virtual GAIA::U8 getlevel() const = 0;
				virtual const GAIA::CH* getdesc() const = 0;
				virtual const GAIA::CH* getsample() const = 0;
				GINL GAIA::GVOID setfilename(const GAIA::TCH* pszFileName){m_strFileName = pszFileName;}
				GINL const GAIA::TCH* getfilename() const{return m_strFileName.front_ptr();}
				GINL GAIA::GVOID setfileline(GAIA::U32 uFileLine){m_uFileLine = uFileLine;}
				GINL GAIA::U32 getfileline() const{return m_uFileLine;}
			private:
				__FileName m_strFileName;
				GAIA::U32 m_uFileLine;
			};
			#define PROM_ERROR(id, stage, level, desc, sample) \
				class ERROR_##id : public ErrorBase\
				{\
				public:\
					virtual GAIA::U16 getid() const{return id;}\
					virtual GAIA::U8 getstage() const{return stage;}\
					virtual GAIA::U8 getlevel() const{return level;}\
					virtual const GAIA::CH* getdesc() const{return desc;}\
					virtual const GAIA::CH* getsample() const{return sample;}\
				};
			PROM_ERROR(101,		0x0000, 0x0000, "pipeline execute failed, no pipeline context returned", "");
			PROM_ERROR(102,		0x0000, 0x0000, "command parameters error", "");
			PROM_ERROR(103,		0x0000, 0x0000, "pipeline link structure error", "");
			PROM_ERROR(104,		0x0000, 0x0002, "pipeline output stage result failed", "");
			PROM_ERROR(501,		0x0000, 0x0003, "file specified by -i parameter is not exist", "");
			PROM_ERROR(502,		0x0000, 0x0004, "file not exist", "");
			PROM_ERROR(503,		0x0000, 0x0002, "create file failed", "");
			PROM_ERROR(504,		0x0000, 0x0003, "open file failed", "");
			PROM_ERROR(505,		0x0000, 0x0003, "delete file failed", "");
			PROM_ERROR(506,		0x0000, 0x0002, "create directory failed", "");
			PROM_ERROR(507,		0x0000, 0x0003, "open directory failed", "");
			PROM_ERROR(508,		0x0000, 0x0003, "delete directory failed", "");
			PROM_ERROR(511,		0x0000, 0x0002, "text line analyze failed", "");
			PROM_ERROR(512,		0x0000, 0x0002, "text line save failed", "");
			PROM_ERROR(1001,	0x0000, 0x0002, "allocate size not match the object", "Object* p = (Object*)malloc/calloc/realloc...(sizeof(Object));");
		};

	#define PROM_RAISE_FATALERROR(id) \
		do\
		{\
			ERROR_SYSTEM::ERROR_##id* temp_error = new ERROR_SYSTEM::ERROR_##id;\
			errs.push_back(temp_error);\
		}while(GAIA::ALWAYSFALSE)

	#define PROM_RAISE_FILEERROR(id, filename) \
		do\
		{\
			ERROR_SYSTEM::ERROR_##id* temp_error = new ERROR_SYSTEM::ERROR_##id;\
			errs.push_back(temp_error);\
			temp_error->setfilename(filename);\
		}while(GAIA::ALWAYSFALSE)

	#define PROM_RAISE_ERROR(id, filename, line) \
		do\
		{\
			ERROR_SYSTEM::ERROR_##id* temp_error = new ERROR_SYSTEM::ERROR_##id;\
			errs.push_back(temp_error);\
			temp_error->setfilename(filename);\
			temp_error->setfileline(line);\
		}while(GAIA::ALWAYSFALSE)

	private:
		typedef GAIA::CONTAINER::Vector<ERROR_SYSTEM::ErrorBase*> __ErrorListType;
	private:
		template<typename _DataType> class DirectionalFreeLink : public GAIA::RefObject
		{
		public:
			typedef DirectionalFreeLink<_DataType> __MyType;
		public:
			GINL GAIA::BL BindNext(__MyType* p)
			{
				GAIA_AST(p != GNULL);
				if(p == GNULL)
					return GAIA::False;
				GAIA_AST(p != this);
				if(p == this)
					return GAIA::False;
				if(this->prev_exist(p))
					return GAIA::False;
				if(this->next_exist(p))
					return GAIA::False;
				this->Reference();
				p->Reference();
				GAIA::BL bExist = GAIA::False;
				for(GAIA::SIZE x = 0; x < m_nexts.size(); ++x)
				{
					if(m_nexts[x] == GNULL)
					{
						m_nexts[x] = p;
						bExist = GAIA::True;
						break;
					}
				}
				if(!bExist)
					m_nexts.push_back(p);
				bExist = GAIA::False;
				for(GAIA::SIZE x = 0; x < p->m_prevs.size(); ++x)
				{
					if(p->m_prevs[x] == GNULL)
					{
						p->m_prevs[x] = this;
						bExist = GAIA::True;
						break;
					}
				}
				if(!bExist)
					p->m_prevs.push_back(this);
				return GAIA::True;
			}
			GINL GAIA::BL UnbindNext(__MyType* p)
			{
				GAIA_AST(p != GNULL);
				if(p == GNULL)
					return GAIA::False;
				GAIA_AST(p != this);
				if(p == this)
					return GAIA::False;
				GAIA::BL bExist = GAIA::False;
				for(GAIA::SIZE x = 0; x < m_nexts.size(); ++x)
				{
					if(m_nexts[x] == p)
					{
						m_nexts[x] = GNULL;
						bExist = GAIA::True;
						break;
					}
				}
				if(!bExist)
					return GAIA::False;
				bExist = GAIA::False;
				for(GAIA::SIZE x = 0; x < p->m_prevs.size(); ++x)
				{
					if(p->m_prevs[x] == this)
					{
						p->m_prevs[x] = GNULL;
						bExist = GAIA::True;
						break;
					}
				}
				if(!bExist)
				{
					GAIA_AST(GAIA::ALWAYSFALSE);
					return GAIA::False;
				}
				this->Release();
				p->Release();
				return GAIA::True;
			}
			GINL GAIA::GVOID UnbindNextAll()
			{
				for(GAIA::SIZE x = 0; x < m_nexts.size(); ++x)
				{
					__MyType* pPLC = m_nexts[x];
					if(pPLC == GNULL)
						continue;
					this->UnbindNext(pPLC);
				}
			}
			GINL GAIA::SIZE GetNextSize() const{return m_nexts.size();}
			GINL __MyType* GetNext(const GAIA::SIZE& index) const
			{
				if(index >= m_nexts.size())
					return GNULL;
				if(m_nexts[index] == GNULL)
					return GNULL;
				m_nexts[index]->Reference();
				return m_nexts[index];
			}
			GINL GAIA::BL BindPrev(__MyType* p){return p->BindNext(this);}
			GINL GAIA::BL UnbindPrev(__MyType* p){return p->UnbindNext(this);}
			GINL GAIA::GVOID UnbindPrevAll()
			{
				for(GAIA::SIZE x = 0; x < this->GetPrevSize(); ++x)
				{
					__MyType* pPLC = m_prevs[x];
					if(pPLC == GNULL)
						continue;
					this->UnbindPrev(pPLC);
				}
			}
			GINL GAIA::SIZE GetPrevSize() const{return m_prevs.size();}
			GINL __MyType* GetPrev(const GAIA::SIZE& index) const
			{
				if(index >= m_prevs.size())
					return GNULL;
				if(m_prevs[index] == GNULL)
					return GNULL;
				m_prevs[index]->Reference();
				return m_prevs[index];
			}
		private:
			GINL GAIA::BL next_exist(__MyType* p) const
			{
				GAIA_AST(p != GNULL);
				if(p == GNULL)
					return GAIA::False;
				for(GAIA::SIZE x = 0; x < this->GetNextSize(); ++x)
				{
					__MyType* pNext = this->GetNext(x);
					if(pNext == GNULL)
						continue;
					if(pNext == p)
					{
						pNext->Release();
						return GAIA::True;
					}
					if(pNext->next_exist(p))
					{
						pNext->Release();
						return GAIA::True;
					}
					pNext->Release();
				}
				return GAIA::False;
			}
			GINL GAIA::BL prev_exist(__MyType* p) const
			{
				GAIA_AST(p != GNULL);
				if(p == GNULL)
					return GAIA::False;
				for(GAIA::SIZE x = 0; x < this->GetPrevSize(); ++x)
				{
					__MyType* pPrev = this->GetPrev(x);
					if(pPrev == GNULL)
						continue;
					if(pPrev == p)
					{
						p->Release();
						return GAIA::True;
					}
					if(pPrev->prev_exist(p))
					{
						pPrev->Release();
						return GAIA::True;
					}
					pPrev->Release();
				}
				return GAIA::False;
			}
		protected:
			virtual GAIA::GVOID Destruct()
			{
				this->UnbindNextAll();
				this->UnbindPrevAll();
			}
		private:
			typedef GAIA::CONTAINER::Vector<__MyType*> __DoubleLinkList;
		private:
			__DoubleLinkList m_nexts;
			__DoubleLinkList m_prevs;
		};
		template<typename _RowType, typename _ColType> class BasicTextLocation
		{
		public:
			typedef _RowType _rowtype;
			typedef _ColType _columntype;
		public:
			typedef BasicTextLocation<_RowType, _ColType> __MyType;
		public:
			GINL BasicTextLocation(){this->clear();}
			GINL BasicTextLocation(const _RowType& row, const _ColType& col){this->row(row); this->col(col);}
			GINL BasicTextLocation(const __MyType& src){this->operator = (src);}
			GINL GAIA::GVOID clear(){m_row = m_col = GINVALID;}
			GINL GAIA::GVOID empty() const{if(m_row == GINVALID || m_row == GINVALID) return GAIA::True; return GAIA::False;}
			GINL GAIA::GVOID row(const _RowType& row){m_row = row;}
			GINL const _RowType& row() const{return m_row;}
			GINL GAIA::GVOID col(const _ColType& col){m_col = col;}
			GINL const _ColType& col() const{return m_col;}
			const __MyType& operator = (const __MyType& src)
			{
				m_row = src.m_row;
				m_col = src.m_col;
				return *this;
			}
			GAIA_CLASS_OPERATOR_COMPARE2(m_col, m_col, m_row, m_row, __MyType);
		private:
			_RowType m_row;
			_ColType m_col;
		};
		template<typename _FileIDType, typename _RowType, typename _ColType> class BasicLocation
		{
		public:
			typedef _FileIDType _fileidtype;
			typedef _RowType _rowtype;
			typedef _ColType _columntype;
		public:
			typedef BasicLocation<_FileIDType, _RowType, _ColType> __MyType;
			typedef BasicTextLocation<_RowType, _ColType> __TextLocType;
		public:
			GINL BasicLocation(){this->clear();}
			GINL BasicLocation(const _FileIDType& fileid, const __TextLocType& begin, const __TextLocType& end){this->fileid(fileid); this->begin(begin); this->end(end);}
			GINL BasicLocation(const __MyType& src){this->operator = (src);}
			GINL GAIA::GVOID clear(){m_fileid = GINVALID; m_begin.clear(); m_end.clear();}
			GINL GAIA::GVOID empty() const{if(m_fileid == GINVALID || m_begin.empty() || m_end.empty()) return GAIA::True; return GAIA::False;}
			GINL GAIA::GVOID fileid(const _FileIDType& src){m_fileid = src;}
			GINL const _FileIDType& fileid() const{return m_fileid;}
			GINL GAIA::GVOID begin(const __TextLocType& src){m_begin = src;}
			GINL const __TextLocType& begin() const{return m_begin;}
			GINL GAIA::GVOID end(const __TextLocType& src){m_end = src;}
			GINL const __TextLocType& end() const{return m_end;}
			const __MyType& operator = (const __MyType& src)
			{
				m_fileid = src.m_fileid;
				m_begin = src.m_begin;
				m_end = src.m_end;
				return *this;
			}
			GAIA_CLASS_OPERATOR_COMPARE3(m_fileid, m_fileid, m_begin, m_begin, m_end, m_end, __MyType);
		private:
			_FileIDType m_fileid;
			__TextLocType m_begin;
			__TextLocType m_end;
		};
		typedef BasicTextLocation<GAIA::N32, GAIA::N32> TLoc;
		typedef BasicLocation<GAIA::N32, GAIA::N32, GAIA::N32> Loc;
		class PipelineContext : public DirectionalFreeLink<PipelineContext>
		{
		public:
			GINL PipelineContext(){}
			GINL ~PipelineContext(){}
			virtual const GAIA::TCH* GetName() const = 0;
		};
		class PLC_Empty : public PipelineContext
		{
		public:
			GINL PLC_Empty(){}
			GINL ~PLC_Empty(){}
			virtual const GAIA::TCH* GetName() const{return _T("Prom:PLC_Empty");}
		};
		class PLC_SourceCommand : public PipelineContext
		{
		public:
			GINL PLC_SourceCommand(){pszCmd = GNULL;}
			GINL ~PLC_SourceCommand(){}
			virtual const GAIA::TCH* GetName() const{return _T("Prom:PLC_SourceCommand");}
			const GAIA::TCH* pszCmd;
		};
		class PLC_CommandParam : public PipelineContext
		{
		public:
			GINL PLC_CommandParam(){this->init();}
			GINL ~PLC_CommandParam(){}
			virtual const GAIA::TCH* GetName() const{return _T("Prom:PLC_CommandParam");}
			DWARFS_MISC::CmdParam cmdparam;
		private:
			GINL GAIA::GVOID init()
			{
			}
		};
		class PLC_File : public PipelineContext
		{
		public:
			GINL PLC_File(){}
			GINL ~PLC_File(){}
			virtual const GAIA::TCH* GetName() const{return _T("Prom:PLC_File");}
		public:
			class File
			{
			public:
				File(){this->init();}
				GAIA_CLASS_OPERATOR_COMPARE(name, name, File);
				__FileName name;
				GAIA::BL bNeedSave;
			private:
				GINL GAIA::GVOID init(){bNeedSave = GAIA::False;}
			};
			typedef GAIA::CONTAINER::Vector<File> __FileList;
		public:
			__FileList filelist;
		};
		class PLC_FileCodeLine : public PipelineContext
		{
		public:
			GINL PLC_FileCodeLine(){}
			GINL ~PLC_FileCodeLine(){}
			virtual const GAIA::TCH* GetName() const{return _T("Prom:PLC_FileCodeLine");}
		public:
			class FileCodeLines
			{
			public:
				DWARFS_MISC::TextLine lines;
			};
			typedef GAIA::CONTAINER::Vector<FileCodeLines> __FileCodelinesList;
		public:
			__FileCodelinesList file_codelines_list;
		};
		class PLC_FileCodeLinePrepare : public PipelineContext
		{
		public:
			GINL PLC_FileCodeLinePrepare(){}
			GINL ~PLC_FileCodeLinePrepare(){}
			virtual const GAIA::TCH* GetName() const{return _T("Prom:PLC_FileCodeLinePrepare");}
		public:
			PLC_FileCodeLine::__FileCodelinesList file_codelines_list;
		};
		class PLC_FileStructure : public PipelineContext
		{
		public:
			GINL PLC_FileStructure(){}
			GINL ~PLC_FileStructure(){}
			virtual const GAIA::TCH* GetName() const{return _T("Prom:PLC_FileStructure");}
		public:
			typedef GAIA::CONTAINER::Set<__FileName> __FileLinkSet;
			class Node
			{
			public:
				GAIA_CLASS_OPERATOR_COMPARE(name, name, Node);
				__FileName name;
				__FileLinkSet parents;
				__FileLinkSet childs;
			};
			typedef GAIA::CONTAINER::Set<Node> __FileNodeSet;
		public:
			GINL GAIA::BL AddLink(const GAIA::TCH* pszParentFile, const GAIA::TCH* pszChildFile)
			{
				GPCHR_NULLSTRPTR_RET(pszParentFile, GAIA::False);
				GPCHR_NULLSTRPTR_RET(pszChildFile, GAIA::False);
				if(this->IsLinkExist(pszParentFile, pszChildFile))
					return GAIA::True;
				Node* pFindedParent = this->FindNode(pszParentFile);
				if(pFindedParent == GNULL)
				{
					Node n;
					n.name = pszParentFile;
					filenodeset.insert(n);
					pFindedParent = filenodeset.find(n);
				}
				Node* pFindedChild = this->FindNode(pszChildFile);
				if(pFindedChild == GNULL)
				{
					Node n;
					n.name = pszChildFile;
					filenodeset.insert(n);
					pFindedChild = filenodeset.find(n);
				}
				GPCHR_NULL_RET(pFindedParent, GAIA::False);
				GPCHR_NULL_RET(pFindedChild, GAIA::False);
				pFindedParent->childs.insert(pszChildFile);
				pFindedChild->parents.insert(pszParentFile);
				return GAIA::True;
			}
			GINL GAIA::BL IsLinkExist(const GAIA::TCH* pszParentFile, const GAIA::TCH* pszChildFile) const
			{
				GPCHR_NULLSTRPTR_RET(pszParentFile, GAIA::False);
				GPCHR_NULLSTRPTR_RET(pszChildFile, GAIA::False);
				const Node* pFinded = this->FindNode(pszParentFile);
				if(pFinded != GNULL)
					if(pFinded->childs.find(pszChildFile) != GNULL)
						return GAIA::True;
				return GAIA::False;
			}
			GINL const Node* FindNode(const GAIA::TCH* pszFile) const
			{
				GPCHR_NULLSTRPTR_RET(pszFile, GNULL);
				Node finder;
				finder.name = pszFile;
				return filenodeset.find(finder);
			}
			GINL Node* FindNode(const GAIA::TCH* pszFile)
			{
				GPCHR_NULLSTRPTR_RET(pszFile, GNULL);
				Node finder;
				finder.name = pszFile;
				return filenodeset.find(finder);
			}
		public:
			__FileNodeSet filenodeset;
		};
		class PLC_ObjCtn : public PipelineContext
		{
		public:
			class Obj : public GAIA::Base
			{
			public:
				GAIA_ENUM_BEGIN(TYPE)
					MACRO,
					INCLUDE,
					TEMPLATE,
					EXPRESSION,
					VAR,
					ARRAY,
					FUNC,
					ENUM,
					UNION,
					STRUCT,
					CLASS,
					NAMESPACE,
					FIELD,
					OTHERS,
				GAIA_ENUM_END(TYPE)

				GAIA_ENUM_BEGIN(STRUCTTYPE)
					DECLARATION,
					IMPLEMENT,
				GAIA_ENUM_END(STRUCTTYPE)

				GAIA_ENUM_BEGIN(REFTYPE)
					INST,
					REF,
					PTR,
				GAIA_ENUM_END(REFTYPE)
			public:
				virtual const GAIA::TCH* GetName() const{return GNULL;}
				virtual GAIA::SIZE GetNameSize() const{return GINVALID;}
				virtual TYPE GetType() const{return TYPE_INVALID;}
				virtual STRUCTTYPE GetStructType() const{return STRUCTTYPE_INVALID;}
				virtual REFTYPE GetRefType() const{return REFTYPE_INVALID;}
			public:
				GINL GAIA::GVOID SetLocation(const Loc& l){m_loc = l;}
				GINL const Loc& GetLocation() const{return m_loc;}
			private:
				Loc m_loc;
			};
			class ObjVar
			{
			public:
				GAIA_ENUM_BEGIN(TYPE)
					BOOL,
					INT8,
					INT16,
					INT32,
					INT64,
					REAL32,
					REAL64,
					STRING,
					WSTRING,
				GAIA_ENUM_END(TYPE)
			};
			class ObjExpression
			{
			public:
				GAIA_ENUM_BEGIN(TYPE)
					PRE_INC,
					PRE_DEC,
					POST_INC,
					POST_DEC,
					ADD1,
					SUB1,
					MUL1,
					DIV1,
					ADD2,
					SUB2,
					MUL2,
					DIV2,
					MOD,
				GAIA_ENUM_END(TYPE)
			};
			class Rec : public GAIA::Base
			{
			public:
				Obj* pObj;
				GAIA::SIZE uLocationIndex;
				GAIA::SIZE uNameIndex;
				GAIA::SIZE uTypeIndex;
			};
			class RecLocation : public Rec
			{
			public:
				GINL GAIA::BL operator == (const RecLocation& src){return pObj->GetLocation() == src.pObj->GetLocation();}
				GINL GAIA::BL operator != (const RecLocation& src){return !this->operator == (src);}
				GINL GAIA::BL operator >= (const RecLocation& src){return pObj->GetLocation() >= src.pObj->GetLocation();}
				GINL GAIA::BL operator <= (const RecLocation& src){return pObj->GetLocation() <= src.pObj->GetLocation();}
				GINL GAIA::BL operator > (const RecLocation& src){return !this->operator <= (src);}
				GINL GAIA::BL operator < (const RecLocation& src){return !this->operator >= (src);}
			};
			class RecName : public Rec
			{
			public:
				GINL GAIA::BL operator == (const RecName& src){return GAIA::ALGORITHM::cmps(pObj->GetName(), pObj->GetNameSize(), src.pObj->GetName(), src.pObj->GetNameSize()) == 0;}
				GINL GAIA::BL operator != (const RecName& src){return !this->operator == (src);}
				GINL GAIA::BL operator >= (const RecName& src){return GAIA::ALGORITHM::cmps(pObj->GetName(), pObj->GetNameSize(), src.pObj->GetName(), src.pObj->GetNameSize()) >= 0;}
				GINL GAIA::BL operator <= (const RecName& src){return GAIA::ALGORITHM::cmps(pObj->GetName(), pObj->GetNameSize(), src.pObj->GetName(), src.pObj->GetNameSize()) <= 0;}
				GINL GAIA::BL operator > (const RecName& src){return !this->operator <= (src);}
				GINL GAIA::BL operator < (const RecName& src){return !this->operator >= (src);}
			};
			class RecType : public Rec
			{
			public:
				GINL GAIA::BL operator == (const RecLocation& src){return pObj->GetType() == src.pObj->GetType();}
				GINL GAIA::BL operator != (const RecLocation& src){return !this->operator == (src);}
				GINL GAIA::BL operator >= (const RecLocation& src){return pObj->GetType() >= src.pObj->GetType();}
				GINL GAIA::BL operator <= (const RecLocation& src){return pObj->GetType() <= src.pObj->GetType();}
				GINL GAIA::BL operator > (const RecLocation& src){return !this->operator <= (src);}
				GINL GAIA::BL operator < (const RecLocation& src){return !this->operator >= (src);}
			};
		public:
			GINL PLC_ObjCtn(){}
			GINL ~PLC_ObjCtn(){}
			virtual const GAIA::TCH* GetName() const{return _T("Prom:PLC_ObjCtn");}
		public:
			typedef GAIA::CONTAINER::Vector<RecLocation> __RecLocationListType;
			typedef GAIA::CONTAINER::Vector<RecName> __RecNameListType;
			typedef GAIA::CONTAINER::Vector<RecType> __RecTypeListType;
		public:
			__RecLocationListType rec_location;
			__RecNameListType rec_name;
			__RecTypeListType rec_type;
		};
		class PLC_Word : public PipelineContext
		{
		public:
			GINL PLC_Word(){}
			GINL ~PLC_Word(){}
			virtual const GAIA::TCH* GetName() const{return _T("Prom:PLC_Word");}
		public:
			class Word
			{
			public:
				GINL Word(){this->init();}
				GINL Word& operator = (const Word& src)
				{
					strWord = src.strWord;
					uExistCount = src.uExistCount;
					return *this;
				}
				GAIA_CLASS_OPERATOR_COMPARE(strWord, strWord, Word);
			private:
				GINL GAIA::GVOID init()
				{
					uExistCount = 0;
				}
			public:
				__WordType strWord;
				GAIA::U32 uExistCount;
			};
			typedef GAIA::CONTAINER::Set<Word> __WordSetType;
		public:
			__WordSetType wordset;
		};
		class Pipeline : public DirectionalFreeLink<Pipeline>
		{
		public:
			GINL Pipeline(){}
			GINL ~Pipeline(){}
			GINL PipelineContext* GetPLCByName(PipelineContext** ppPLC, const GAIA::SIZE& size, const GAIA::TCH* pszName) const
			{
				GPCHR_NULL_RET(ppPLC, GNULL);
				GPCHR_ZERO_RET(size, GNULL);
				for(GAIA::SIZE x = 0; x < size; ++x)
				{
					if(ppPLC[x] == GNULL)
						continue;
					const GAIA::TCH* pszTempName = ppPLC[x]->GetName();
					if(GAIA::ALGORITHM::strcmp(pszTempName, pszName) == 0)
					{
						ppPLC[x]->Reference();
						return ppPLC[x];
					}
					for(GAIA::SIZE y = 0; y < ppPLC[x]->GetPrevSize(); ++y)
					{
						PipelineContext* pPrevPLC = static_cast<PipelineContext*>(ppPLC[x]->GetPrev(y));
						if(pPrevPLC == GNULL)
							continue;
						PipelineContext* pPrevResult = this->GetPLCByName(&pPrevPLC, 1, pszName);
						pPrevPLC->Release();
						if(pPrevResult != GNULL)
							return pPrevResult;
					}
				}
				return GNULL;
			}
			virtual const GAIA::TCH* GetName() const = 0;
			virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size, GAIA::PRINT::PrintBase& prt, __ErrorListType& errs) = 0;
			virtual GAIA::BL Output(PipelineContext* pPLC, GAIA::FILESYSTEM::FileBase* pFile, GAIA::PRINT::PrintBase& prt){return GAIA::False;}
		};
		class PL_CommandAnalyze : public Pipeline
		{
		public:
			GINL PL_CommandAnalyze(){}
			GINL ~PL_CommandAnalyze(){}
			virtual const GAIA::TCH* GetName() const{return _T("Prom:PL_CommandAnalyze");}
			virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size, GAIA::PRINT::PrintBase& prt, __ErrorListType& errs)
			{
				/* Parameter check up. */
				GPCHR_NULL_RET(ppPLC, GNULL);
				GPCHR_ZERO_RET(size, GNULL);
				PLC_SourceCommand* plc_sourcecommand = static_cast<PLC_SourceCommand*>(this->GetPLCByName(ppPLC, size, _T("Prom:PLC_SourceCommand")));
				if(plc_sourcecommand == GNULL)
					return GNULL;

				/* Initialize result pipeline context. */
				PLC_CommandParam* pRet = new PLC_CommandParam;
				pRet->cmdparam.begin_decl();
				{
					pRet->cmdparam.cmd_decl(_T("help"), _T("show help information"), 0, 1, DWARFS_MISC::CmdParam::CMD_TYPE_INVALID);

					pRet->cmdparam.cmd_decl(_T("-i"), _T("input files"), 1, GINVALID, DWARFS_MISC::CmdParam::CMD_TYPE_INVALID);
					pRet->cmdparam.cmd_decl(_T("-I"), _T("input directory"), 1, GINVALID, DWARFS_MISC::CmdParam::CMD_TYPE_INVALID);
					pRet->cmdparam.cmd_decl(_T("-E"), _T("input directory files extension name filter"), 1, GINVALID, DWARFS_MISC::CmdParam::CMD_TYPE_INVALID);
					pRet->cmdparam.cmd_decl(_T("-s"), _T("save changes to source files"), 0, 0, DWARFS_MISC::CmdParam::CMD_TYPE_INVALID);
					pRet->cmdparam.cmd_decl(_T("-o"), _T("output the stage result"), 1, 2, DWARFS_MISC::CmdParam::CMD_TYPE_INVALID);
					pRet->cmdparam.cmd_decl(_T("-h"), _T("set header file path"), 0, GINVALID, DWARFS_MISC::CmdParam::CMD_TYPE_INVALID);
					pRet->cmdparam.cmd_decl(_T("-predefine"), _T("set predefine macros"), 0, GINVALID, DWARFS_MISC::CmdParam::CMD_TYPE_INVALID);
					pRet->cmdparam.cmd_decl(_T("-export"), _T("export the temp result to destination path"), 2, 2, DWARFS_MISC::CmdParam::CMD_TYPE_INVALID);

					pRet->cmdparam.cmd_decl(_T("-linebreak"), _T("change lines break flag, use \"\\r\" \"\\n\" or \"\\r\\n\""), 1, 1, DWARFS_MISC::CmdParam::CMD_TYPE_INVALID);
					pRet->cmdparam.cmd_decl(_T("-fmt"), _T("format the codes"), 0, 0, DWARFS_MISC::CmdParam::CMD_TYPE_INVALID);

					pRet->cmdparam.cmd_decl(_T("-linestat"), _T("statistics the lines"), 0, 0, DWARFS_MISC::CmdParam::CMD_TYPE_INVALID);
					pRet->cmdparam.cmd_decl(_T("-wordstat"), _T("statistics the words, use -o to output the result"), 0, 1, DWARFS_MISC::CmdParam::CMD_TYPE_INVALID);
					pRet->cmdparam.cmd_decl(_T("-symbolstat"), _T("statistics the symbols, use -o to output the result"), 0, 0, DWARFS_MISC::CmdParam::CMD_TYPE_INVALID);
				}
				pRet->cmdparam.end_decl();

				/* Execute. */
				if(!pRet->cmdparam.build(plc_sourcecommand->pszCmd, prt))
				{
					PROM_RAISE_FATALERROR(102);
					pRet->Release();
					plc_sourcecommand->Release();
					return GNULL;
				}

				/* Release. */
				plc_sourcecommand->Release();

				return pRet;
			}
			virtual GAIA::BL Output(PipelineContext* pPLC, GAIA::FILESYSTEM::FileBase* pFile, GAIA::PRINT::PrintBase& prt)
			{
				/* Parameter check up. */
				GAIA_AST(pPLC != GNULL);
				if(pPLC == GNULL)
					return GAIA::False;

				GAIA_AST(!GAIA::ALGORITHM::stremp(pPLC->GetName()));
				if(GAIA::ALGORITHM::stremp(pPLC->GetName()))
					return GAIA::False;

				PLC_CommandParam* plc_sourcecommand = static_cast<PLC_CommandParam*>(pPLC);
				if(plc_sourcecommand == GNULL)
					return GAIA::False;
				if(GAIA::ALGORITHM::strcmp(pPLC->GetName(), _T("Prom:PLC_CommandParam")) != 0)
					return GAIA::False;

				for(GAIA::SIZE x = 0; x < plc_sourcecommand->cmdparam.cmd_size(); ++x)
				{
					const GAIA::TCH* pszCmd = plc_sourcecommand->cmdparam.cmd(x);
					if(GAIA::ALGORITHM::stremp(pszCmd))
						continue;
					prt << "\t\t" << pszCmd << " ";
					for(GAIA::SIZE y = 0; y < plc_sourcecommand->cmdparam.param_size(x); ++y)
					{
						const GAIA::TCH* pszParam = plc_sourcecommand->cmdparam.param(x, y);
						if(GAIA::ALGORITHM::stremp(pszParam))
							continue;
						prt << pszParam << " ";
					}
					prt << "\n";
				}

				return GAIA::True;
			}
		};
		class PL_Help : public Pipeline
		{
		public:
			GINL PL_Help(){}
			GINL ~PL_Help(){}
			virtual const GAIA::TCH* GetName() const{return _T("Prom:PL_Help");}
			virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size, GAIA::PRINT::PrintBase& prt, __ErrorListType& errs)
			{
				/* Parameter check up. */
				GPCHR_NULL_RET(ppPLC, GNULL);
				GPCHR_ZERO_RET(size, GNULL);
				PLC_CommandParam* plc_commandparam = static_cast<PLC_CommandParam*>(this->GetPLCByName(ppPLC, size, _T("Prom:PLC_CommandParam")));
				if(plc_commandparam == GNULL)
					return GNULL;

				/* Initialize result pipeline context. */
				PLC_Empty* pRet = new PLC_Empty;
				for(GAIA::SIZE x = 0; x < plc_commandparam->cmdparam.cmd_size(); ++x)
				{
					const GAIA::TCH* pszCmd = plc_commandparam->cmdparam.cmd(x);
					if(GAIA::ALGORITHM::stremp(pszCmd))
						continue;
					if(GAIA::ALGORITHM::strcmp(pszCmd, _T("help")) == 0)
					{
						if(plc_commandparam->cmdparam.param_size(x) != 0)
						{
							for(GAIA::SIZE y = 0; y < plc_commandparam->cmdparam.param_size(x); ++y)
							{
							}
						}
						else
						{
							for(GAIA::SIZE y = 0; y < plc_commandparam->cmdparam.cmd_decl_size(); ++y)
							{
								const GAIA::TCH* pszDeclCmd = plc_commandparam->cmdparam.cmd_decl_cmd(y);
								if(pszDeclCmd == GNULL)
									continue;
								const GAIA::TCH* pszDeclDesc = plc_commandparam->cmdparam.cmd_decl_desc(y);
								GAIA::SIZE min_param_size = plc_commandparam->cmdparam.cmd_decl_min_param_size(y);
								GAIA::SIZE max_param_size = plc_commandparam->cmdparam.cmd_decl_max_param_size(y);
								DWARFS_MISC::CmdParam::CMD_TYPE cmdtype = plc_commandparam->cmdparam.cmd_decl_type(y);
								if(GAIA::ALGORITHM::stremp(pszDeclDesc))
									pszDeclDesc = _T("NoInfo");
								prt << "\t" << "[" << y << "]" << pszDeclCmd << ", Info:" << pszDeclDesc << ", " <<
									"[" << min_param_size << ", " << max_param_size << "] " <<
									DWARFS_MISC::CMD_TYPE_NAME[cmdtype] << "\n";
							}
						}
						break;
					}
				}

			FUNCTION_END:
				if(plc_commandparam != GNULL)
					plc_commandparam->Release();
				return pRet;
			}
		};
		class PL_FileCollect : public Pipeline
		{
		public:
			GINL PL_FileCollect(){}
			GINL ~PL_FileCollect(){}
			virtual const GAIA::TCH* GetName() const{return _T("Prom:PL_FileCollect");}
			virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size, GAIA::PRINT::PrintBase& prt, __ErrorListType& errs)
			{
				/* Parameter check up. */
				GPCHR_NULL_RET(ppPLC, GNULL);
				GPCHR_ZERO_RET(size, GNULL);
				PLC_CommandParam* plc_commandparam = static_cast<PLC_CommandParam*>(this->GetPLCByName(ppPLC, size, _T("Prom:PLC_CommandParam")));
				if(plc_commandparam == GNULL)
					return GNULL;

				/* Initialize result pipeline context. */
				PLC_File* pRet = new PLC_File;

				/* Execute. */
				typedef GAIA::CONTAINER::Vector<__FileName> __FileListType;
				typedef GAIA::CONTAINER::Vector<__FileName> __PathListType;
				typedef GAIA::CONTAINER::Vector<__FileName> __ExtListType;
				__FileListType listFile;
				__PathListType listPath;
				__ExtListType listExt;
				for(GAIA::SIZE x = 0; x < plc_commandparam->cmdparam.cmd_size(); ++x)
				{
					const GAIA::TCH* pszCmd = plc_commandparam->cmdparam.cmd(x);
					if(GAIA::ALGORITHM::stremp(pszCmd))
						continue;
					if(GAIA::ALGORITHM::strcmp(pszCmd, _T("-i")) == 0)
					{
						for(GAIA::SIZE y = 0; y < plc_commandparam->cmdparam.param_size(x); ++y)
						{
							const GAIA::TCH* pszParam = plc_commandparam->cmdparam.param(x, y);
							if(GAIA::ALGORITHM::stremp(pszParam))
								continue;
							listFile.push_back(pszParam);
						}
					}
					else if(GAIA::ALGORITHM::strcmp(pszCmd, _T("-I")) == 0)
					{
						for(GAIA::SIZE y = 0; y < plc_commandparam->cmdparam.param_size(x); ++y)
						{
							const GAIA::TCH* pszParam = plc_commandparam->cmdparam.param(x, y);
							if(GAIA::ALGORITHM::stremp(pszParam))
								continue;
							listPath.push_back(pszParam);
						}
					}
					else if(GAIA::ALGORITHM::strcmp(pszCmd, _T("-E")) == 0)
					{
						for(GAIA::SIZE y = 0; y < plc_commandparam->cmdparam.param_size(x); ++y)
						{
							const GAIA::TCH* pszParam = plc_commandparam->cmdparam.param(x, y);
							if(GAIA::ALGORITHM::stremp(pszParam))
								continue;
							listExt.push_back(pszParam);
						}
					}
				}
				for(__FileListType::_sizetype x = 0; x < listFile.size(); ++x)
				{
					PLC_File::File tempfile;
					tempfile.name = listFile[x];
					pRet->filelist.push_back(tempfile);

					GAIA::FILESYSTEM::File file;
					if(!file.Open(tempfile.name, GAIA::FILESYSTEM::File::OPEN_TYPE_READ))
						PROM_RAISE_FILEERROR(501, tempfile.name);
				}
				__FileName strExt;
				for(__ExtListType::_sizetype x = 0; x < listExt.size(); ++x)
				{
					if(!strExt.empty())
						strExt += _T("|");
					strExt += listExt[x];
				}
				GAIA::FILESYSTEM::Directory::__ResultTree restree;
				__PathListType listTempPathPart;
				PLC_File::File tempfile;
				for(__PathListType::_sizetype x = 0; x < listPath.size(); ++x)
				{
					GAIA::FILESYSTEM::Directory dir;
					restree.clear();
					if(dir.CollectFile(listPath[x], strExt, GAIA::True, restree))
					{
						GAIA::FILESYSTEM::Directory::__ResultTree::const_it it = restree.const_front_it();
						for(; !it.empty(); ++it)
						{
							if(restree.leaf(it))
							{
								GAIA::FILESYSTEM::Directory::__ResultTree::const_it tempit = it;
								listTempPathPart.clear();
								tempfile.name.clear();
								for(; !tempit.empty(); tempit = restree.parent_it(tempit))
									listTempPathPart.push_back(*tempit);
								listTempPathPart.inverse();
								for(__PathListType::_sizetype y = 0; y < listTempPathPart.size(); ++y)
								{
									if(!tempfile.name.empty())
										tempfile.name += _T("/");
									tempfile.name += listTempPathPart[y];
								}
								pRet->filelist.push_back(tempfile);
							}
						}
					}
				}
				pRet->filelist.sort();
				pRet->filelist.unique();
				prt << "\t\tThere are " << pRet->filelist.size() << " files collected!\n";

				/* Release. */
				plc_commandparam->Release();

				return pRet;
			}
		};
		class PL_LineCollect : public Pipeline
		{
		public:
			GINL PL_LineCollect(){}
			GINL ~PL_LineCollect(){}
			virtual const GAIA::TCH* GetName() const{return _T("Prom:PL_LineCollect");}
			virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size, GAIA::PRINT::PrintBase& prt, __ErrorListType& errs)
			{
				/* Parameter check up. */
				GPCHR_NULL_RET(ppPLC, GNULL);
				GPCHR_ZERO_RET(size, GNULL);
				PLC_File* plc_file = static_cast<PLC_File*>(this->GetPLCByName(ppPLC, size, _T("Prom:PLC_File")));
				if(plc_file == GNULL)
					return GNULL;

				/* Initialize result pipeline context. */
				PLC_FileCodeLine* pRet = new PLC_FileCodeLine;

				/* Execute. */
				pRet->file_codelines_list.resize(plc_file->filelist.size());
				GAIA::SIZE uTotalLineCount = 0;
				for(PLC_File::__FileList::_sizetype x = 0; x < plc_file->filelist.size(); ++x)
				{
					GAIA::FILESYSTEM::File file;
					if(!file.Open(plc_file->filelist[x].name, GAIA::FILESYSTEM::File::OPEN_TYPE_READ))
					{
						PROM_RAISE_FILEERROR(502, plc_file->filelist[x].name);
						continue;
					}
					if(!pRet->file_codelines_list[x].lines.load(file))
					{
						PROM_RAISE_FILEERROR(511, plc_file->filelist[x].name);
						continue;
					}
					uTotalLineCount += pRet->file_codelines_list.size();
				}
				prt << "\t\tThere are " << uTotalLineCount << " lines collected!\n";

				/* Release. */
				plc_file->Release();

				return pRet;
			}
		};
		class PL_LineBreakCorrect : public Pipeline
		{
		public:
			GINL PL_LineBreakCorrect(){}
			GINL ~PL_LineBreakCorrect(){}
			virtual const GAIA::TCH* GetName() const{return _T("Prom:PL_LineBreakCorrect");}
			virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size, GAIA::PRINT::PrintBase& prt, __ErrorListType& errs)
			{
				/* Parameter check up. */
				GPCHR_NULL_RET(ppPLC, GNULL);
				GPCHR_ZERO_RET(size, GNULL);
				GAIA::CONTAINER::TChars chs;
				PLC_Empty* pRet = GNULL;
				PLC_CommandParam* plc_commandparam = GNULL;
				PLC_File* plc_file = GNULL;
				PLC_FileCodeLine* plc_codeline = GNULL;
				plc_commandparam = static_cast<PLC_CommandParam*>(this->GetPLCByName(ppPLC, size, _T("Prom:PLC_CommandParam")));
				if(plc_commandparam == GNULL)
					goto FUNCTION_END;
				plc_file = static_cast<PLC_File*>(this->GetPLCByName(ppPLC, size, _T("Prom:PLC_File")));
				if(plc_file == GNULL)
					goto FUNCTION_END;
				plc_codeline = static_cast<PLC_FileCodeLine*>(this->GetPLCByName(ppPLC, size, _T("Prom:PLC_FileCodeLine")));
				if(plc_codeline == GNULL)
					goto FUNCTION_END;

				/* Initialize result pipeline context. */
				pRet = new PLC_Empty;

				/* Execute. */
				for(GAIA::SIZE x = 0; x < plc_commandparam->cmdparam.cmd_size(); ++x)
				{
					const GAIA::TCH* pszCmd = plc_commandparam->cmdparam.cmd(x);
					if(GAIA::ALGORITHM::stremp(pszCmd))
						continue;
					if(GAIA::ALGORITHM::strcmp(pszCmd, _T("-linebreak")) == 0)
					{
						GAIA_AST(plc_commandparam->cmdparam.param_size(x) == 1);
						if(plc_commandparam->cmdparam.param_size(x) == 1)
						{
							chs = plc_commandparam->cmdparam.param(x, 0);
							break;
						}
					}
				}
				if(chs == _T("\\r\\n"))
					chs = _T("\r\n");
				else if(chs == _T("\\n"))
					chs = _T("\n");
				else if(chs == _T("\\r"))
					chs = _T("\r");
				else
					chs.clear();
				if(!chs.empty())
				{
					GAIA::SIZE remove_rn = 0;
					GAIA::SIZE remove_n = 0;
					GAIA::SIZE remove_r = 0;
					GAIA::SIZE add = 0;
					GAIA::SIZE old_remove_rn = 0;
					GAIA::SIZE old_remove_n = 0;
					GAIA::SIZE old_remove_r = 0;
					GAIA::SIZE old_add = 0;
					GAIA::SIZE need_save = 0;
					DWARFS_MISC::TextLine::__LineType strTemp;
					for(GAIA::SIZE x = 0; x < plc_codeline->file_codelines_list.size(); ++x)
					{
						PLC_FileCodeLine::__FileCodelinesList::_datatype& t = plc_codeline->file_codelines_list[x];
						GAIA::BL bNeedSave = GAIA::False;
						for(GAIA::SIZE y = 0; y < t.lines.size(); ++y)
						{
							strTemp = t.lines.get_line(y);
							GAIA_AST(!strTemp.empty());
							if(strTemp.empty())
								continue;

							old_remove_rn = remove_rn;
							old_remove_n = remove_n;
							old_remove_r = remove_r;
							old_add = add;

							GAIA::BL bExistValidFlag = GAIA::False;
							if(strTemp.size () >= chs.size())
							{
								if(strTemp.rfind(chs.front_ptr(), strTemp.size() - 1) !=
									strTemp.size() - chs.size())
									++add;
								else
								{
									if(chs == _T("\n"))
									{
										if(strTemp.size() >= 2)
										{
											if(strTemp[strTemp.size() - 2] == _T('\r') &&
												strTemp[strTemp.size() - 1] == _T('\n'))
												++add;
											else
												bExistValidFlag = GAIA::True;
										}
										else
											bExistValidFlag = GAIA::True;
									}
									else
										bExistValidFlag = GAIA::True;
								}
							}
							else
								++add;

							remove_rn += strTemp.replace(_T("\r\n"), _T(""));
							remove_n += strTemp.replace(_T("\n"), _T(""));
							remove_r += strTemp.replace(_T("\r"), _T(""));
							strTemp += chs.front_ptr();

							if(bExistValidFlag)
							{
								if(chs == _T("\r\n"))
									--remove_rn;
								if(chs == _T("\n"))
									--remove_n;
								if(chs == _T("\r"))
									--remove_r;
							}
							t.lines.set_line(y, strTemp);

							if(remove_rn != old_remove_rn ||
								remove_n != old_remove_n ||
								remove_r != old_remove_r ||
								add != old_add)
								bNeedSave = GAIA::True;
						}
						if(bNeedSave)
						{
							plc_file->filelist[x].bNeedSave = GAIA::True;
							++need_save;
						}
					}

					GAIA::CONTAINER::TChars tempchs;
					if(chs == _T("\r\n"))
						tempchs = _T("\\r\\n");
					else if(chs == _T("\n"))
						tempchs = _T("\\n");
					else if(chs == _T("\r"))
						tempchs = _T("\\r");
					else
						tempchs = _T("(InvalidCharacter)");
					prt << "\t\tAdd " << tempchs.front_ptr() << "=" << add << ".\n";
					prt << "\t\tRemove \\r\\n=" << remove_rn << ", \\n=" << remove_n << ", \\r=" << remove_r << ".\n";
					prt << "\t\tChange " << need_save << " files.\n";
				}

				/* Release. */
			FUNCTION_END:
				if(plc_commandparam != GNULL)
					plc_commandparam->Release();
				if(plc_file != GNULL)
					plc_file->Release();
				if(plc_codeline != GNULL)
					plc_codeline->Release();
				return pRet;
			}
		};
		class PL_Format : public Pipeline
		{
		public:
			GINL PL_Format(){}
			GINL ~PL_Format(){}
			virtual const GAIA::TCH* GetName() const{return _T("Prom:PL_Format");}
			virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size, GAIA::PRINT::PrintBase& prt, __ErrorListType& errs)
			{
				/* Parameter check up. */
				GPCHR_NULL_RET(ppPLC, GNULL);
				GPCHR_ZERO_RET(size, GNULL);
				PLC_Empty* pRet = GNULL;
				PLC_CommandParam* plc_commandparam = GNULL;
				PLC_File* plc_file = GNULL;
				PLC_FileCodeLine* plc_codeline = GNULL;
				plc_commandparam = static_cast<PLC_CommandParam*>(this->GetPLCByName(ppPLC, size, _T("Prom:PLC_CommandParam")));
				if(plc_commandparam == GNULL)
					goto FUNCTION_END;
				plc_file = static_cast<PLC_File*>(this->GetPLCByName(ppPLC, size, _T("Prom:PLC_File")));
				if(plc_file == GNULL)
					goto FUNCTION_END;
				plc_codeline = static_cast<PLC_FileCodeLine*>(this->GetPLCByName(ppPLC, size, _T("Prom:PLC_FileCodeLine")));
				if(plc_codeline == GNULL)
					goto FUNCTION_END;

				/* Initialize result pipeline context. */
				pRet = new PLC_Empty;

				/* Execute. */
				GAIA::BL bFmt = GAIA::False;
				for(GAIA::SIZE x = 0; x < plc_commandparam->cmdparam.cmd_size(); ++x)
				{
					const GAIA::TCH* pszCmd = plc_commandparam->cmdparam.cmd(x);
					if(GAIA::ALGORITHM::stremp(pszCmd))
						continue;
					if(GAIA::ALGORITHM::strcmp(pszCmd, _T("-fmt")) == 0)
					{
						bFmt = GAIA::True;
						break;
					}
				}
				if(bFmt)
				{
					typedef DWARFS_MISC::TextLine::__LineType __LineType;
					__LineType strLine;
					GAIA::SIZE remove_space_count = 0;
					GAIA::SIZE remove_tab_count = 0;
					GAIA::SIZE line_change_count = 0;
					GAIA::SIZE file_change_count = 0;
					for(GAIA::SIZE x = 0; x < plc_codeline->file_codelines_list.size(); ++x)
					{
						GAIA::BL bFileChanged = GAIA::False;
						PLC_FileCodeLine::FileCodeLines& fcl = plc_codeline->file_codelines_list[x];

						/* Line inside based code-format. */
						for(GAIA::SIZE y = 0; y < fcl.lines.size(); ++y)
						{
							strLine = fcl.lines.get_line(y);
							if(strLine.empty())
								continue;
							GAIA::BL bLineChanged = GAIA::False;

							/* Get line break flag. */
							GAIA::TCH szLineBreak[3];
							if(strLine.back() == _T('\n'))
							{
								if(strLine.size() > 1)
								{
									if(strLine[strLine.size() - 2] == _T('\r'))
										GAIA::ALGORITHM::strcpy(szLineBreak, _T("\r\n"));
									else
										GAIA::ALGORITHM::strcpy(szLineBreak, _T("\n"));
								}
								else
									GAIA::ALGORITHM::strcpy(szLineBreak, _T("\n"));
							}
							else if(strLine.back() == _T('\r'))
								GAIA::ALGORITHM::strcpy(szLineBreak, _T("\r"));
							if(GAIA::ALGORITHM::strlen(szLineBreak) == 2)
								strLine.resize(strLine.size() - 2);
							else
								strLine.resize(strLine.size() - 1);

							/* Delete space or tab at line tail. */
							__LineType::it itback = strLine.back_it();
							while(!itback.empty())
							{
								if(*itback != _T(' ') && *itback != _T('\t'))
									break;
								if(*itback == _T(' '))
								{
									++remove_space_count;
									bLineChanged = GAIA::True;
								}
								else if(*itback == _T('\t'))
								{
									++remove_tab_count;
									bLineChanged = GAIA::True;
								}
								GAIA_AST(strLine.size() > 0);
								strLine.resize(strLine.size() - 1);
								--itback;
							}

							/* Remove continuation-space. */
							GAIA::TCH chOld = _T('\0');
							for(GAIA::SIZE z = 0; z < strLine.size(); ++z)
							{
								if(strLine[z] == _T(' '))
								{
									if(chOld == _T(' '))
									{
										strLine.erase_index(z);
										--z;
										++remove_space_count;
										bLineChanged = GAIA::True;
									}
								}
								chOld = strLine[z];
							}

							/* Update the line. */
							if(bLineChanged)
							{
								strLine += szLineBreak;
								fcl.lines.set_line(y, strLine);
								++line_change_count;
								bFileChanged = GAIA::True;
							}
						}

						/* Line outside based code-format. */

						/* Set need save. */
						if(bFileChanged)
						{
							plc_file->filelist[x].bNeedSave = GAIA::True;
							++file_change_count;
						}
					}
					prt << "\t\tCode line formated!" << "\n";
					prt << "\t\tRemove space = " << remove_space_count << ", remove tab = " << remove_tab_count << ".\n";
					prt << "\t\tThere are " << line_change_count << " line changed, and " << file_change_count << " file changed.\n";
				}

			FUNCTION_END:
				if(plc_commandparam != GNULL)
					plc_commandparam->Release();
				if(plc_file != GNULL)
					plc_file->Release();
				if(plc_codeline != GNULL)
					plc_codeline->Release();
				return pRet;
			}
		};
		class PL_LinePrepare : public Pipeline
		{
		public:
			GINL PL_LinePrepare(){}
			GINL ~PL_LinePrepare(){}
			virtual const GAIA::TCH* GetName() const{return _T("Prom:PL_LinePrepare");}
			virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size, GAIA::PRINT::PrintBase& prt, __ErrorListType& errs)
			{
				/* Parameter check up. */
				GPCHR_NULL_RET(ppPLC, GNULL);
				GPCHR_ZERO_RET(size, GNULL);

				GAIA::CONTAINER::Vector<GAIA::BL> listEraseTemp;
				DWARFS_MISC::TextLine::__LineType strLine, strLineTemp;
				PLC_FileCodeLinePrepare* pRet = GNULL;
				PLC_CommandParam* plc_commandparam = GNULL;
				PLC_FileCodeLine* plc_codeline = GNULL;
				plc_commandparam = static_cast<PLC_CommandParam*>(this->GetPLCByName(ppPLC, size, _T("Prom:PLC_CommandParam")));
				if(plc_commandparam == GNULL)
					goto FUNCTION_END;
				plc_codeline = static_cast<PLC_FileCodeLine*>(this->GetPLCByName(ppPLC, size, _T("Prom:PLC_FileCodeLine")));
				if(plc_codeline == GNULL)
					goto FUNCTION_END;

				/* Initialize result pipeline context. */
				pRet = new PLC_FileCodeLinePrepare;
				pRet->file_codelines_list = plc_codeline->file_codelines_list;
				for(GAIA::SIZE x = 0; x < pRet->file_codelines_list.size(); ++x)
					pRet->file_codelines_list[x].lines.enable_checkline(GAIA::False);

				/* Execute. */
				for(GAIA::SIZE x = 0; x < pRet->file_codelines_list.size(); ++x)
				{
					PLC_FileCodeLine::FileCodeLines& fcl = pRet->file_codelines_list[x];
					GAIA::BL bInString = GAIA::False;
					GAIA::BL bInMultiLineComment = GAIA::False;
					for(GAIA::SIZE y = 0; y < fcl.lines.size(); ++y)
					{
						strLine = strLineTemp = fcl.lines.get_line(y);
						listEraseTemp.resize(strLineTemp.size());
						listEraseTemp.reset(GAIA::False);
						GAIA::BL bInSingleLineComment = GAIA::False;
						GAIA::BL bSign = GAIA::True;
						GAIA::SIZE sLastNotBlankIndex = GINVALID;
						for(GAIA::SIZE z = 0; z < strLineTemp.size(); ++z)
						{
							DWARFS_MISC::TextLine::__CharType ch = strLineTemp[z];
							if(bInMultiLineComment)
							{
								if(ch == _T('/') && (z > 0 && strLineTemp[z - 1] == _T('*')))
								{
									bInMultiLineComment = GAIA::False;
									bSign = GAIA::True;
									sLastNotBlankIndex = z;
								}
								listEraseTemp[z] = GAIA::True; // Erase the multi line comment.
								continue;
							}
							if(bInSingleLineComment)
							{
								if(z + 1 == strLineTemp.size())
								{
									bInSingleLineComment = GAIA::False;
									bSign = GAIA::True;
									sLastNotBlankIndex = z;
								}
								listEraseTemp[z] = GAIA::True; // Erase the single line comment.
								continue;
							}
							if(bInString)
							{
								if(ch == _T('"'))
								{
									GAIA::SIZE flagcount = 0;
									GAIA::ALGORITHM::prevcount(strLineTemp.front_ptr(), strLineTemp.front_ptr() + z - 1, _T('\\'), flagcount);
									if(z == 0 || flagcount % 2 == 0)
									{
										bInString = GAIA::False;
										bSign = GAIA::True;
										sLastNotBlankIndex = z;
									}
								}
								continue;
							}
							if(!is_blank_char(ch))
							{
								if(is_word_char(ch))
								{
									if(bSign)
									{
										if(z > sLastNotBlankIndex + 1)
										{
											GAIA::ALGORITHM::set(
												listEraseTemp.front_ptr() + sLastNotBlankIndex + 1,
												GAIA::True,
												z - sLastNotBlankIndex - 1); // Erase blank between sign and word.
										}
									}
									else
									{
										if(z > sLastNotBlankIndex + 2)
										{
											GAIA::ALGORITHM::set(
												listEraseTemp.front_ptr() + sLastNotBlankIndex + 2,
												GAIA::True,
												z - sLastNotBlankIndex - 2); // Erase blank between word and word.
										}
									}
									bSign = GAIA::False;
								}
								else
								{
									if(z > sLastNotBlankIndex + 1)
									{
										GAIA::ALGORITHM::set(
											listEraseTemp.front_ptr() + sLastNotBlankIndex + 1,
											GAIA::True,
											z - sLastNotBlankIndex - 1); // Erase blank between sign and word or between sign and sign.
									}
									bSign = GAIA::True;
								}
								sLastNotBlankIndex = z;
							}
							if(ch == _T('/'))
							{
								if(z + 1 < strLineTemp.size())
								{
									if(strLineTemp[z + 1] == _T('/'))
									{
										listEraseTemp[z] = GAIA::True; // Erase the single line comment head.
										bInSingleLineComment = GAIA::True;
									}
									else if(strLineTemp[z + 1] == _T('*'))
									{
										listEraseTemp[z] = GAIA::True; // Erase the multi line comment head.
										bInMultiLineComment = GAIA::True;
									}
								}
							}
							if(ch == _T('"'))
								bInString = GAIA::True;
						}
						for(GAIA::SIZE z = 0; z < strLineTemp.size(); ++z)
						{
							if(strLineTemp[z] == _T('\r') || strLineTemp[z] == _T('\n'))
								listEraseTemp[z] = GAIA::True;
						}
						GAIA_AST(listEraseTemp.size() == strLine.size());
						GAIA_AST(listEraseTemp.size() == strLineTemp.size());
						GAIA::SIZE sWriteIndex = 0;
						for(GAIA::SIZE z = 0; z < strLineTemp.size(); ++z)
						{
							if(listEraseTemp[z])
								continue;
							strLine[sWriteIndex++] = strLineTemp[z];
						}
						strLine.resize(sWriteIndex);
						if(strLine != fcl.lines.get_line(y))
							fcl.lines.set_line(y, strLine);
					}
					GAIA_AST(!bInString);
				}

			FUNCTION_END:
				if(plc_commandparam != GNULL)
					plc_commandparam->Release();
				if(plc_codeline != GNULL)
					plc_codeline->Release();
				return pRet;
			}
			virtual GAIA::BL Output(PipelineContext* pPLC, GAIA::FILESYSTEM::FileBase* pFile, GAIA::PRINT::PrintBase& prt)
			{
				/* Parameter check up. */
				GAIA_AST(pPLC != GNULL);
				if(pPLC == GNULL)
					return GAIA::False;

				GAIA_AST(!GAIA::ALGORITHM::stremp(pPLC->GetName()));
				if(GAIA::ALGORITHM::stremp(pPLC->GetName()))
					return GAIA::False;

				PLC_FileCodeLinePrepare* plc_filecodelineprepare = static_cast<PLC_FileCodeLinePrepare*>(pPLC);
				if(plc_filecodelineprepare == GNULL)
					return GAIA::False;
				if(GAIA::ALGORITHM::strcmp(pPLC->GetName(), _T("Prom:PLC_FileCodeLinePrepare")) != 0)
					return GAIA::False;

				for(GAIA::SIZE x = 0; x < plc_filecodelineprepare->file_codelines_list.size(); ++x)
				{
					PLC_FileCodeLine::FileCodeLines& fcl = plc_filecodelineprepare->file_codelines_list[x];
					for(GAIA::SIZE y = 0; y < fcl.lines.size(); ++y)
					{
						const DWARFS_MISC::TextLine::__CharType* pszLine = fcl.lines.get_line(y);
						if(pszLine == GNULL)
							continue;
						if(pszLine[0] != _T('\0'))
							pFile->Write(pszLine, GAIA::ALGORITHM::strlen(pszLine) * sizeof(DWARFS_MISC::TextLine::__CharType));
						pFile->Write(fcl.lines.lineflag(), GAIA::ALGORITHM::strlen(fcl.lines.lineflag()) * sizeof(DWARFS_MISC::TextLine::__CharType));
					}
				}

				return GAIA::True;
			}
		};
		class PL_FileStructureAnalyze : public Pipeline
		{
		public:
			GINL PL_FileStructureAnalyze(){}
			GINL ~PL_FileStructureAnalyze(){}
			virtual const GAIA::TCH* GetName() const{return _T("Prom:PL_FileStructureAnalyze");}
			virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size, GAIA::PRINT::PrintBase& prt, __ErrorListType& errs)
			{
				/* Parameter check up. */
				GPCHR_NULL_RET(ppPLC, GNULL);
				GPCHR_ZERO_RET(size, GNULL);

				PLC_FileStructure* pRet = GNULL;
				PLC_CommandParam* plc_commandparam = GNULL;
				PLC_File* plc_file = GNULL;
				PLC_FileCodeLinePrepare* plc_codelineprepare = GNULL;
				plc_commandparam = static_cast<PLC_CommandParam*>(this->GetPLCByName(ppPLC, size, _T("Prom:PLC_CommandParam")));
				if(plc_commandparam == GNULL)
					goto FUNCTION_END;
				plc_file = static_cast<PLC_File*>(this->GetPLCByName(ppPLC, size, _T("Prom:PLC_File")));
				if(plc_file == GNULL)
					goto FUNCTION_END;
				plc_codelineprepare = static_cast<PLC_FileCodeLinePrepare*>(this->GetPLCByName(ppPLC, size, _T("Prom:PLC_FileCodeLinePrepare")));
				if(plc_codelineprepare == GNULL)
					goto FUNCTION_END;

				/* Initialize result pipeline context. */
				pRet = new PLC_FileStructure;

				/* Execute. */
				for(GAIA::SIZE x = 0; x < plc_codelineprepare->file_codelines_list.size(); ++x)
				{
					PLC_File::File& file = plc_file->filelist[x];
					DWARFS_MISC::TextLine& l = plc_codelineprepare->file_codelines_list[x].lines;
					for(GAIA::SIZE y = 0; y < l.size(); ++y)
					{
						const DWARFS_MISC::TextLine::__CharType* pLine = l.get_line(y);
						if(GAIA::ALGORITHM::stremp(pLine))
							continue;
						const DWARFS_MISC::TextLine::__CharType* pFinded = GAIA::ALGORITHM::strstr(pLine, "#include");
						if(pFinded == GNULL)
							continue;
						pFinded += GAIA::ALGORITHM::strlen("#include");
						const DWARFS_MISC::TextLine::__CharType* pFindedNext = GNULL;
						if(*pFinded == _T('"'))
							pFindedNext = GAIA::ALGORITHM::strch(pFinded + 1, _T('"'));
						else
							pFindedNext = GAIA::ALGORITHM::strch(pFinded + 1, _T('>'));
						if(pFindedNext != GNULL)
						{
							__FileName tempfilename;
							tempfilename.assign(pFinded + 1, pFindedNext - pFinded - 1);
							tempfilename.trim_left(_T(' '));
							tempfilename.trim_left(_T('\t'));
							tempfilename.trim_right(_T(' '));
							tempfilename.trim_right(_T('\t'));
							pRet->AddLink(tempfilename, file.name);
						}
					}
				}

			FUNCTION_END:
				if(plc_commandparam != GNULL)
					plc_commandparam->Release();
				if(plc_file != GNULL)
					plc_file->Release();
				if(plc_codelineprepare != GNULL)
					plc_codelineprepare->Release();
				return pRet;
			}
			virtual GAIA::BL Output(PipelineContext* pPLC, GAIA::FILESYSTEM::FileBase* pFile, GAIA::PRINT::PrintBase& prt)
			{
				/* Parameter check up. */
				GAIA_AST(pPLC != GNULL);
				if(pPLC == GNULL)
					return GAIA::False;

				GAIA_AST(!GAIA::ALGORITHM::stremp(pPLC->GetName()));
				if(GAIA::ALGORITHM::stremp(pPLC->GetName()))
					return GAIA::False;

				PLC_FileStructure* plc_filestructure = static_cast<PLC_FileStructure*>(pPLC);
				if(plc_filestructure == GNULL)
					return GAIA::False;
				if(GAIA::ALGORITHM::strcmp(pPLC->GetName(), _T("Prom:PLC_FileStructure")) != 0)
					return GAIA::False;

				/* Print parent relation. */
				if(pFile != GNULL && pFile->Tell() == 0)
				{
				#if GAIA_CHARSET == GAIA_CHARSET_UNICODE
					pFile->Write(GAIA::UTF16LE_FILEHEAD, sizeof(GAIA::UTF16LE_FILEHEAD));
				#endif
				}
				prt << "[To Parent]" << "\n";
				if(pFile != GNULL)
				{
					pFile->Write(_T("[To Parent]"), GAIA::ALGORITHM::strlen("[To Parent]") * sizeof(GAIA::TCH));
					pFile->Write(FILEBREAK, GAIA::ALGORITHM::strlen(FILEBREAK) * sizeof(FILEBREAK[0]));
				}
				PLC_FileStructure::__FileNodeSet::it it = plc_filestructure->filenodeset.front_it();
				while(!it.empty())
				{
					PLC_FileStructure::__FileNodeSet::_datatype& t = *it;
					if(t.childs.empty())
						this->OutputParentRelation(plc_filestructure, t, pFile, prt, 0);
					++it;
				}

				/* Print child relation. */
				prt << "[To Child]" << "\n";
				if(pFile != GNULL)
				{
					pFile->Write(_T("[To Child]"), GAIA::ALGORITHM::strlen("[To Child]") * sizeof(GAIA::TCH));
					pFile->Write(FILEBREAK, GAIA::ALGORITHM::strlen(FILEBREAK) * sizeof(FILEBREAK[0]));
				}
				it = plc_filestructure->filenodeset.front_it();
				while(!it.empty())
				{
					PLC_FileStructure::__FileNodeSet::_datatype& t = *it;
					if(t.parents.empty())
						this->OutputChildRelation(plc_filestructure, t, pFile, prt, 0);
					++it;
				}

				return GAIA::True;
			}
		private:
			GINL GAIA::GVOID OutputParentRelation(
				PLC_FileStructure* plc_filestructure,
				PLC_FileStructure::Node& node,
				GAIA::FILESYSTEM::FileBase* pFile,
				GAIA::PRINT::PrintBase& prt,
				GAIA::SIZE depth)
			{
				GPCHR_NULL(plc_filestructure);
				prt << node.name.front_ptr() << "\n";
				if(pFile != GNULL)
				{
					this->OutputDepth(prt, pFile, depth);
					pFile->Write(node.name.front_ptr(), node.name.size() * sizeof(__FileName::_datatype));
					pFile->Write(FILEBREAK, GAIA::ALGORITHM::strlen(FILEBREAK) * sizeof(FILEBREAK[0]));
				}
				PLC_FileStructure::__FileLinkSet::it itlink = node.parents.front_it();
				while(!itlink.empty())
				{
					__FileName& filename = *itlink;
					PLC_FileStructure::Node* pParentNode = plc_filestructure->FindNode(filename);
					if(pParentNode != GNULL)
						this->OutputParentRelation(plc_filestructure, *pParentNode, pFile, prt, depth + 1);
					++itlink;
				}
			}
			GINL GAIA::GVOID OutputChildRelation(
				PLC_FileStructure* plc_filestructure,
				PLC_FileStructure::Node& node,
				GAIA::FILESYSTEM::FileBase* pFile,
				GAIA::PRINT::PrintBase& prt,
				GAIA::SIZE depth)
			{
				GPCHR_NULL(plc_filestructure);
				prt << node.name.front_ptr() << "\n";
				if(pFile != GNULL)
				{
					this->OutputDepth(prt, pFile, depth);
					pFile->Write(node.name.front_ptr(), node.name.size() * sizeof(__FileName::_datatype));
					pFile->Write(FILEBREAK, GAIA::ALGORITHM::strlen(FILEBREAK) * sizeof(FILEBREAK[0]));
				}
				PLC_FileStructure::__FileLinkSet::it itlink = node.childs.front_it();
				while(!itlink.empty())
				{
					__FileName& filename = *itlink;
					PLC_FileStructure::Node* pChildNode = plc_filestructure->FindNode(filename);
					if(pChildNode != GNULL)
						this->OutputChildRelation(plc_filestructure, *pChildNode, pFile, prt, depth + 1);
					++itlink;
				}
			}
			GINL GAIA::GVOID OutputDepth(GAIA::PRINT::PrintBase& prt, GAIA::FILESYSTEM::FileBase* pFile, GAIA::SIZE depth)
			{
				for(GAIA::SIZE x = 0; x < depth; ++x)
				{
					prt << "\t";
					if(pFile != GNULL)
						pFile->Write(_T("\t"), sizeof(GAIA::TCH));
				}
			}
		};
		class PL_ObjAnalyzeBase : public Pipeline
		{
		public:
			GINL PL_ObjAnalyzeBase(){}
			GINL ~PL_ObjAnalyzeBase(){}
			virtual const GAIA::TCH* GetName() const{return _T("Prom:PL_ObjAnalyzeBase");}
			virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size, GAIA::PRINT::PrintBase& prt, __ErrorListType& errs)
			{
				/* Parameter check up. */
				GPCHR_NULL_RET(ppPLC, GNULL);
				GPCHR_ZERO_RET(size, GNULL);

				PLC_ObjCtn* pRet = GNULL;
				PLC_CommandParam* plc_commandparam = GNULL;
				PLC_FileCodeLinePrepare* plc_codelineprepare = GNULL;
				plc_commandparam = static_cast<PLC_CommandParam*>(this->GetPLCByName(ppPLC, size, _T("Prom:PLC_CommandParam")));
				if(plc_commandparam == GNULL)
					goto FUNCTION_END;
				plc_codelineprepare = static_cast<PLC_FileCodeLinePrepare*>(this->GetPLCByName(ppPLC, size, _T("Prom:PLC_FileCodeLinePrepare")));
				if(plc_codelineprepare == GNULL)
					goto FUNCTION_END;

				/* Initialize result pipeline context. */
				pRet = new PLC_ObjCtn;

				/* Execute. */

			FUNCTION_END:
				if(plc_commandparam != GNULL)
					plc_commandparam->Release();
				if(plc_codelineprepare != GNULL)
					plc_codelineprepare->Release();
				return pRet;
			}
			virtual GAIA::BL Output(PipelineContext* pPLC, GAIA::FILESYSTEM::FileBase* pFile, GAIA::PRINT::PrintBase& prt)
			{
				/* Parameter check up. */
				GAIA_AST(pPLC != GNULL);
				if(pPLC == GNULL)
					return GAIA::False;

				GAIA_AST(!GAIA::ALGORITHM::stremp(pPLC->GetName()));
				if(GAIA::ALGORITHM::stremp(pPLC->GetName()))
					return GAIA::False;

				PLC_ObjCtn* plc_objctn = static_cast<PLC_ObjCtn*>(pPLC);
				if(plc_objctn == GNULL)
					return GAIA::False;
				if(GAIA::ALGORITHM::strcmp(pPLC->GetName(), _T("Prom:PLC_ObjCtn")) != 0)
					return GAIA::False;

				return GAIA::True;
			}
		};
		class PL_ObjAnalyzeUnwrapMacro : public Pipeline
		{
		public:
			GINL PL_ObjAnalyzeUnwrapMacro(){}
			GINL ~PL_ObjAnalyzeUnwrapMacro(){}
			virtual const GAIA::TCH* GetName() const{return _T("Prom:PL_ObjAnalyzeUnwrapMacro");}
			virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size, GAIA::PRINT::PrintBase& prt, __ErrorListType& errs)
			{
				/* Parameter check up. */
				GPCHR_NULL_RET(ppPLC, GNULL);
				GPCHR_ZERO_RET(size, GNULL);

				PLC_Empty* pRet = GNULL;
				PLC_CommandParam* plc_commandparam = GNULL;
				PLC_FileCodeLinePrepare* plc_codelineprepare = GNULL;
				PLC_ObjCtn* plc_objctn = GNULL;
				plc_commandparam = static_cast<PLC_CommandParam*>(this->GetPLCByName(ppPLC, size, _T("Prom:PLC_CommandParam")));
				if(plc_commandparam == GNULL)
					goto FUNCTION_END;
				plc_codelineprepare = static_cast<PLC_FileCodeLinePrepare*>(this->GetPLCByName(ppPLC, size, _T("Prom:PLC_FileCodeLinePrepare")));
				if(plc_codelineprepare == GNULL)
					goto FUNCTION_END;
				plc_objctn = static_cast<PLC_ObjCtn*>(this->GetPLCByName(ppPLC, size, _T("Prom:PLC_ObjCtn")));
				if(plc_objctn == GNULL)
					goto FUNCTION_END;

				/* Initialize result pipeline context. */
				pRet = new PLC_Empty;

				/* Execute. */


			FUNCTION_END:
				if(plc_commandparam != GNULL)
					plc_commandparam->Release();
				if(plc_codelineprepare != GNULL)
					plc_codelineprepare->Release();
				if(plc_objctn != GNULL)
					plc_objctn->Release();
				return pRet;
			}
			virtual GAIA::BL Output(PipelineContext* pPLC, GAIA::FILESYSTEM::FileBase* pFile, GAIA::PRINT::PrintBase& prt)
			{
				/* Parameter check up. */
				GAIA_AST(pPLC != GNULL);
				if(pPLC == GNULL)
					return GAIA::False;

				GAIA_AST(!GAIA::ALGORITHM::stremp(pPLC->GetName()));
				if(GAIA::ALGORITHM::stremp(pPLC->GetName()))
					return GAIA::False;

				return GAIA::True;
			}
		};
		class PL_LineStat : public Pipeline
		{
		public:
			GINL PL_LineStat(){}
			GINL ~PL_LineStat(){}
			virtual const GAIA::TCH* GetName() const{return _T("Prom:PL_LineStat");}
			virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size, GAIA::PRINT::PrintBase& prt, __ErrorListType& errs)
			{
				/* Parameter check up. */
				GPCHR_NULL_RET(ppPLC, GNULL);
				GPCHR_ZERO_RET(size, GNULL);

				DWARFS_MISC::TextLine::__LineType strLine;
				FileLineInfo fli;
				PLC_Empty* pRet = GNULL;
				PLC_CommandParam* plc_commandparam = GNULL;
				PLC_FileCodeLine* plc_codeline = GNULL;
				plc_commandparam = static_cast<PLC_CommandParam*>(this->GetPLCByName(ppPLC, size, _T("Prom:PLC_CommandParam")));
				if(plc_commandparam == GNULL)
					goto FUNCTION_END;
				plc_codeline = static_cast<PLC_FileCodeLine*>(this->GetPLCByName(ppPLC, size, _T("Prom:PLC_FileCodeLine")));
				if(plc_codeline == GNULL)
					goto FUNCTION_END;

				/* Initialize result pipeline context. */
				pRet = new PLC_Empty;

				/* Execute. */
				GAIA::BL bLineStat = GAIA::False;
				for(GAIA::SIZE x = 0; x < plc_commandparam->cmdparam.cmd_size(); ++x)
				{
					const GAIA::TCH* pszCmd = plc_commandparam->cmdparam.cmd(x);
					if(GAIA::ALGORITHM::stremp(pszCmd))
						continue;
					if(GAIA::ALGORITHM::strcmp(pszCmd, _T("-linestat")) == 0)
					{
						bLineStat = GAIA::True;
						break;
					}
				}
				if(bLineStat)
				{
					for(GAIA::SIZE x = 0; x < plc_codeline->file_codelines_list.size(); ++x)
					{
						DWARFS_MISC::TextLine& l = plc_codeline->file_codelines_list[x].lines;
						fli.uTotalLineCount += l.size();
						for(GAIA::SIZE y = 0; y < l.size(); ++y)
						{
							strLine = l.get_line(y);
							if(strLine.empty())
							{
								++fli.uBlankLineCount;
								continue;
							}
							if(GAIA::ALGORITHM::strcnts(strLine.front_ptr(), _T("\r\n\t ")) == strLine.size())
							{
								++fli.uBlankLineCount;
								continue;
							}
						}
					}
					prt << "\t\tTotalLineCount = " << fli.uTotalLineCount << "\n";
					prt << "\t\tPureLineCount = " << fli.uTotalLineCount - fli.uCommentLineCount - fli.uBlankLineCount << "\n";
					prt << "\t\tBlankLineCount = " << fli.uBlankLineCount << "\n";
					prt << "\t\tCommentLineCount = " << fli.uCommentLineCount << "\n";
				}

			FUNCTION_END:
				if(plc_commandparam != GNULL)
					plc_commandparam->Release();
				if(plc_codeline != GNULL)
					plc_codeline->Release();
				return pRet;
			}
		private:
			class FileLineInfo
			{
			public:
				GINL FileLineInfo(){this->init();}
				GAIA::U64 uTotalLineCount;
				GAIA::U64 uCommentLineCount;
				GAIA::U64 uBlankLineCount;
			private:
				GINL GAIA::GVOID init()
				{
					uTotalLineCount = 0;
					uCommentLineCount = 0;
					uBlankLineCount = 0;
				}
			};
		};
		class PL_WordStat : public Pipeline
		{
		public:
			GINL PL_WordStat(){}
			GINL ~PL_WordStat(){}
			virtual const GAIA::TCH* GetName() const{return _T("Prom:PL_WordStat");}
			virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size, GAIA::PRINT::PrintBase& prt, __ErrorListType& errs)
			{
				/* Parameter check up. */
				GPCHR_NULL_RET(ppPLC, GNULL);
				GPCHR_ZERO_RET(size, GNULL);

				PLC_Word* pRet = GNULL;
				PLC_CommandParam* plc_commandparam = GNULL;
				PLC_File* plc_file = GNULL;
				PLC_FileCodeLine* plc_codeline = GNULL;
				plc_commandparam = static_cast<PLC_CommandParam*>(this->GetPLCByName(ppPLC, size, _T("Prom:PLC_CommandParam")));
				if(plc_commandparam == GNULL)
					goto FUNCTION_END;
				plc_file = static_cast<PLC_File*>(this->GetPLCByName(ppPLC, size, _T("Prom:PLC_File")));
				if(plc_file == GNULL)
					goto FUNCTION_END;
				plc_codeline = static_cast<PLC_FileCodeLine*>(this->GetPLCByName(ppPLC, size, _T("Prom:PLC_FileCodeLine")));
				if(plc_codeline == GNULL)
					goto FUNCTION_END;

				/* Initialize result pipeline context. */
				pRet = new PLC_Word;

				/* Execute. */
				GAIA::BL bWordStat = GAIA::False;
				for(GAIA::SIZE x = 0; x < plc_commandparam->cmdparam.cmd_size(); ++x)
				{
					const GAIA::TCH* pszCmd = plc_commandparam->cmdparam.cmd(x);
					if(GAIA::ALGORITHM::stremp(pszCmd))
						continue;
					if(GAIA::ALGORITHM::strcmp(pszCmd, _T("-wordstat")) == 0)
					{
						bWordStat = GAIA::True;
						break;
					}
				}
				if(bWordStat)
				{
					DWARFS_MISC::TextLine::__LineType strLine;
					PLC_Word::Word word;
					for(GAIA::SIZE x = 0; x < plc_codeline->file_codelines_list.size(); ++x)
					{
						DWARFS_MISC::TextLine& l = plc_codeline->file_codelines_list[x].lines;
						for(GAIA::SIZE y = 0; y < l.size(); ++y)
						{
							strLine = l.get_line(y);
							if(strLine.empty())
								continue;
							static const GAIA::SIZE EMPTY_FLAG = 0;
							static const GAIA::SIZE CHAR_FLAG = 1;
							static const GAIA::SIZE SIGN_FLAG = 2;
							GAIA::SIZE lastflag = EMPTY_FLAG;
							GAIA::SIZE flag_changed_index = 0;
							for(GAIA::SIZE z = 0; z < strLine.size(); ++z)
							{
								GAIA::SIZE newflag;
								if(strLine[z] == _T('\t') || strLine[z] == _T(' ') || strLine[z] == _T('\r') || strLine[z] == _T('\n'))
									newflag = EMPTY_FLAG;
								else if(
									GAIA::ALGORITHM::isalpha(strLine[z]) ||
									GAIA::ALGORITHM::isdigit(strLine[z]) ||
									strLine[z] == _T('_') ||
									strLine[z] == _T('.') && z + 1 < strLine.size() && GAIA::ALGORITHM::isdigit(strLine[z + 1]))
									newflag = CHAR_FLAG;
								else
									newflag = SIGN_FLAG;

								if(newflag != lastflag)
								{
									if(lastflag != EMPTY_FLAG)
									{
										word.strWord = strLine;
										word.strWord.mid(flag_changed_index, z > flag_changed_index ? z - 1 : z);
										PLC_Word::Word* pWord = pRet->wordset.find(word);
										if(pWord == GNULL)
										{
											word.uExistCount = 1;
											pRet->wordset.insert(word);
										}
										else
											++pWord->uExistCount;
									}
									lastflag = newflag;
									flag_changed_index = z;
								}
								else
								{
									if(lastflag == SIGN_FLAG)
									{
										if(z != flag_changed_index)
										{
											static const GAIA::TCH* LINK_SIGN_LIST[] =
											{
												_T(">>"), _T("<<"),
												_T("++"), _T("--"),
												_T("+="), _T("-="), _T("*="), _T("/="),
												_T("=="), _T("!="), _T(">="), _T("<=")
											};
											GAIA::BL bLink = GAIA::False;
											for(GAIA::SIZE t = 0; t < sizeofarray(LINK_SIGN_LIST); ++t)
											{
												if(strLine[flag_changed_index] == LINK_SIGN_LIST[t][0] &&
													strLine[z] == LINK_SIGN_LIST[t][1])
												{
													bLink = GAIA::True;
													break;
												}
											}
											if(!bLink)
											{
												word.strWord = strLine;
												word.strWord.mid(flag_changed_index, z > flag_changed_index ? z - 1 : z);
												PLC_Word::Word* pWord = pRet->wordset.find(word);
												if(pWord == GNULL)
												{
													word.uExistCount = 1;
													pRet->wordset.insert(word);
												}
												else
													++pWord->uExistCount;
												flag_changed_index = z;
											}
										}
									}
								}
							}
						}
					}
				}

			FUNCTION_END:
				if(plc_commandparam != GNULL)
					plc_commandparam->Release();
				if(plc_file != GNULL)
					plc_file->Release();
				if(plc_codeline != GNULL)
					plc_codeline->Release();
				return pRet;
			}
			virtual GAIA::BL Output(PipelineContext* pPLC, GAIA::FILESYSTEM::FileBase* pFile, GAIA::PRINT::PrintBase& prt)
			{
				/* Parameter check up. */
				GAIA_AST(pPLC != GNULL);
				if(pPLC == GNULL)
					return GAIA::False;

				GAIA_AST(!GAIA::ALGORITHM::stremp(pPLC->GetName()));
				if(GAIA::ALGORITHM::stremp(pPLC->GetName()))
					return GAIA::False;

				PLC_Word* plc_word = static_cast<PLC_Word*>(pPLC);
				if(plc_word == GNULL)
					return GAIA::False;
				if(GAIA::ALGORITHM::strcmp(pPLC->GetName(), _T("Prom:PLC_Word")) != 0)
					return GAIA::False;
				if(pFile != GNULL && pFile->Tell() == 0)
				{
				#if GAIA_CHARSET == GAIA_CHARSET_UNICODE
					pFile->Write(GAIA::UTF16LE_FILEHEAD, sizeof(GAIA::UTF16LE_FILEHEAD));
				#endif
				}
				GAIA::SIZE index = 0;
				PLC_Word::__WordSetType::it it = plc_word->wordset.front_it();
				while(!it.empty())
				{
					PLC_Word::Word& word = *it;
					if(pFile != GNULL)
					{
						GAIA::TCH szTemp[32];
						GAIA::ALGORITHM::int2str(index++, szTemp);
						pFile->Write(_T("["), sizeof(GAIA::TCH));
						pFile->Write(szTemp, GAIA::ALGORITHM::strlen(szTemp) * sizeof(GAIA::TCH));
						pFile->Write(_T("] \""), sizeof(GAIA::TCH) * 3);
						pFile->Write(word.strWord.front_ptr(), word.strWord.size() * sizeof(__WordType::_datatype));
						pFile->Write(_T("\", Count = "), sizeof(_T("\", Count = ")) - sizeof(GAIA::TCH));
						GAIA::ALGORITHM::int2str(word.uExistCount, szTemp);
						pFile->Write(szTemp, GAIA::ALGORITHM::strlen(szTemp) * sizeof(GAIA::TCH));
						pFile->Write(FILEBREAK, GAIA::ALGORITHM::strlen(FILEBREAK) * sizeof(FILEBREAK[0]));
					}
					else
						prt << "[" << index++ << "] \"" << word.strWord.front_ptr() << "\", Count = " << word.uExistCount << "\n";
					++it;
				}

				typedef GAIA::CONTAINER::Vector<WordByRefCount> __WordCountSortVectorType;
				__WordCountSortVectorType wordcountsortlist;
				it = plc_word->wordset.front_it();
				while(!it.empty())
				{
					PLC_Word::Word& word = *it;
					WordByRefCount temp;
					temp.pWord = &word.strWord;
					temp.uExistCount = word.uExistCount;
					wordcountsortlist.push_back(temp);
					++it;
				}
				wordcountsortlist.sort();

				index = 0;
				__WordCountSortVectorType::it itcountsort = wordcountsortlist.front_it();
				while(!itcountsort.empty())
				{
					WordByRefCount& word = *itcountsort;
					if(pFile != GNULL)
					{
						GAIA::TCH szTemp[32];
						GAIA::ALGORITHM::int2str(index++, szTemp);
						pFile->Write(_T("["), sizeof(GAIA::TCH));
						pFile->Write(szTemp, GAIA::ALGORITHM::strlen(szTemp) * sizeof(GAIA::TCH));
						pFile->Write(_T("] \""), sizeof(GAIA::TCH) * 3);
						pFile->Write(word.pWord->front_ptr(), word.pWord->size() * sizeof(__WordType::_datatype));
						pFile->Write(_T("\", Count = "), sizeof(_T("\", Count = ")) - sizeof(GAIA::TCH));
						GAIA::ALGORITHM::int2str(word.uExistCount, szTemp);
						pFile->Write(szTemp, GAIA::ALGORITHM::strlen(szTemp) * sizeof(GAIA::TCH));
						pFile->Write(FILEBREAK, GAIA::ALGORITHM::strlen(FILEBREAK) * sizeof(FILEBREAK[0]));
					}
					else
						prt << "[" << index++ << "] \"" << word.pWord->front_ptr() << "\", Count = " << word.uExistCount << "\n";
					++itcountsort;
				}

				return GAIA::True;
			}
		private:
			class WordByRefCount
			{
			public:
				const WordByRefCount& operator = (const WordByRefCount& src)
				{
					pWord = src.pWord;
					uExistCount = src.uExistCount;
					return *this;
				}
				GAIA_CLASS_OPERATOR_COMPARE(uExistCount, uExistCount, WordByRefCount);
			public:
				__WordType* pWord;
				GAIA::U32 uExistCount;
			};
		};
		class PL_SymbolStat : public Pipeline
		{
		public:
			GINL PL_SymbolStat(){}
			GINL ~PL_SymbolStat(){}
			virtual const GAIA::TCH* GetName() const{return _T("Prom:PL_SymbolStat");}
			virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size, GAIA::PRINT::PrintBase& prt, __ErrorListType& errs)
			{
				return GNULL;
			}
		};
		class PL_SingleLineAnalyze : public Pipeline
		{
		public:
			GINL PL_SingleLineAnalyze(){}
			GINL ~PL_SingleLineAnalyze(){}
			virtual const GAIA::TCH* GetName() const{return _T("Prom:PL_SingleLineAnalyze");}
			virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size, GAIA::PRINT::PrintBase& prt, __ErrorListType& errs)
			{
				return GNULL;
			}
		};
		class PL_Save : public Pipeline
		{
		public:
			GINL PL_Save(){}
			GINL ~PL_Save(){}
			virtual const GAIA::TCH* GetName() const{return _T("Prom:PL_Save");}
			virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size, GAIA::PRINT::PrintBase& prt, __ErrorListType& errs)
			{
				/* Parameter check up. */
				GPCHR_NULL_RET(ppPLC, GNULL);
				GPCHR_ZERO_RET(size, GNULL);
				PLC_Empty* pRet = GNULL;
				PLC_CommandParam* plc_commandparam = GNULL;
				PLC_File* plc_file = GNULL;
				PLC_FileCodeLine* plc_codeline = GNULL;
				plc_commandparam = static_cast<PLC_CommandParam*>(this->GetPLCByName(ppPLC, size, _T("Prom:PLC_CommandParam")));
				if(plc_commandparam == GNULL)
					goto FUNCTION_END;
				plc_file = static_cast<PLC_File*>(this->GetPLCByName(ppPLC, size, _T("Prom:PLC_File")));
				if(plc_file == GNULL)
					goto FUNCTION_END;
				plc_codeline = static_cast<PLC_FileCodeLine*>(this->GetPLCByName(ppPLC, size, _T("Prom:PLC_FileCodeLine")));
				if(plc_codeline == GNULL)
					goto FUNCTION_END;

				/* Initialize result pipeline context. */
				pRet = new PLC_Empty;

				/* Execute. */
				GAIA::BL bSaveCmd = GAIA::False;
				for(GAIA::SIZE x = 0; x < plc_commandparam->cmdparam.cmd_size(); ++x)
				{
					const GAIA::TCH* pszCmd = plc_commandparam->cmdparam.cmd(x);
					if(GAIA::ALGORITHM::stremp(pszCmd))
						continue;
					if(GAIA::ALGORITHM::strcmp(pszCmd, _T("-s")) == 0)
					{
						bSaveCmd = GAIA::True;
						break;
					}
				}
				GAIA::SIZE save_success_count = 0;
				GAIA::SIZE save_failed_count = 0;
				if(bSaveCmd)
				{
					for(GAIA::SIZE x = 0; x < plc_file->filelist.size(); ++x)
					{
						if(!plc_file->filelist[x].bNeedSave)
							continue;
						GAIA::FILESYSTEM::File file;
						if(file.Open(plc_file->filelist[x].name,
							GAIA::FILESYSTEM::File::OPEN_TYPE_CREATEALWAYS | GAIA::FILESYSTEM::File::OPEN_TYPE_WRITE))
						{
							if(plc_codeline->file_codelines_list[x].lines.save(file))
							{
								plc_file->filelist[x].bNeedSave = GAIA::False;
								++save_success_count;
							}
							else
								--save_failed_count;
						}
						else
							--save_failed_count;
					}
					if(save_failed_count == 0)
						prt << "\t\tThere are " << save_success_count << " files save successfully.\n";
					else
						prt << "\t\tThere are " << save_success_count << " files save successfully, and " << save_failed_count << " files save failed!.\n";
				}

				/* Release. */
			FUNCTION_END:
				if(plc_commandparam != GNULL)
					plc_commandparam->Release();
				if(plc_file != GNULL)
					plc_file->Release();
				if(plc_codeline != GNULL)
					plc_codeline->Release();

				return pRet;
			}
		};
		class PipelineDispatch : public GAIA::RefObject
		{
		public:
			GINL PipelineDispatch(){this->init();}
			GINL GAIA::GVOID Run(
				Pipeline** ppPrevPL, const GAIA::SIZE& prevpl_size,
				Pipeline** ppNextPL, const GAIA::SIZE& nextpl_size,
				PipelineContext** ppPLC, const GAIA::SIZE& plc_size,
				GAIA::PRINT::PrintBase& prt, __ErrorListType& errs)
			{
				/* Internal type. */
				typedef GAIA::CONTAINER::Vector<Pipeline*> __PipelineList;
				typedef GAIA::CONTAINER::Vector<PipelineContext*> __PipelineContextList;

				/* Check parameter. */
				GPCHR_NULL(ppNextPL);
				GPCHR_ZERO(nextpl_size);
				GPCHR_NULL(ppPLC);
				GPCHR_ZERO(plc_size);

				if(ppPrevPL == GNULL)
				{
					GAIA_AST(prevpl_size == 0);
					if(prevpl_size != 0)
						return;
				}
				else
				{
					GAIA_AST(prevpl_size != 0);
					if(prevpl_size == 0)
						return;
				}
				for(GAIA::SIZE x = 0; x < prevpl_size; ++x)
				{
					GAIA_AST(ppPrevPL[x] != GNULL);
					if(ppPrevPL[x] == GNULL)
						return;
				}
				for(GAIA::SIZE x = 0; x < nextpl_size; ++x)
				{
					GAIA_AST(ppNextPL[x] != GNULL);
					if(ppNextPL[x] == GNULL)
						return;
				}

				/* Dispatch current layer. */
				__PipelineContextList plc_list;
				__PipelineContextList new_plc_list;
				plc_list.reserve(prevpl_size);
				new_plc_list.reserve(prevpl_size);
				for(GAIA::SIZE x = 0; x < nextpl_size; ++x)
				{
					Pipeline* pTempPL = ppNextPL[x];
					GAIA::SIZE uPracPrevSize = 0;
					for(GAIA::SIZE y = 0; y < pTempPL->GetPrevSize(); ++y)
					{
						Pipeline* pTempPrevPL = dynamic_cast<Pipeline*>(pTempPL->GetPrev(y));
						if(pTempPrevPL == GNULL)
							continue;
						pTempPrevPL->Release();
						++uPracPrevSize;
					}
					if(uPracPrevSize == 0)
					{
						prt << "\n\tPipeline Stage : " << pTempPL->GetName() << "\n";
						GAIA::U64 uStartTick = GAIA::TIME::tick_time();
						PipelineContext* pNewPLC = pTempPL->Execute(ppPLC, plc_size, prt, errs);
						GAIA::U64 uEndTick = GAIA::TIME::tick_time();
						prt << "\t\tTimeLost : " << (GAIA::F64)(uEndTick - uStartTick) / 1000.0 / 1000.0 << "\n";
						if(pNewPLC == GNULL)
							PROM_RAISE_FATALERROR(101);
						else
						{
							this->ExecuteOutput(pNewPLC, pTempPL, prt, errs);
							this->ExecuteExportTempResult(ppPLC, plc_size, pNewPLC, pTempPL, prt, errs);
							for(GAIA::SIZE y = 0; y < plc_size; y++)
							{
								if(ppPLC[y] == GNULL)
									continue;
								ppPLC[y]->BindNext(pNewPLC);
							}
						}
						new_plc_list.push_back(pNewPLC);
					}
					else
					{
						plc_list.clear();
						GAIA::BL bExecuteAble = GAIA::True;
						for(GAIA::SIZE y = 0; y < pTempPL->GetPrevSize(); ++y)
						{
							Pipeline* pTempPrevPL = dynamic_cast<Pipeline*>(pTempPL->GetPrev(y));
							if(pTempPrevPL == GNULL)
								continue;
							GAIA::BL bFindedMatchedPLC = GAIA::False;
							for(GAIA::SIZE z = 0; z < prevpl_size; ++z)
							{
								if(ppPrevPL[z] == pTempPrevPL)
								{
									plc_list.push_back(ppPLC[z]);
									bFindedMatchedPLC = GAIA::True;
									break;
								}
							}
							pTempPrevPL->Release();
							if(!bFindedMatchedPLC)
							{
								PROM_RAISE_FATALERROR(103);
								bExecuteAble = GAIA::False;
								break;
							}
						}
						prt << "\n\tPipeline Stage : " << pTempPL->GetName() << "\n";
						GAIA::U64 uStartTick = GAIA::TIME::tick_time();
						PipelineContext* pNewPLC = pTempPL->Execute(plc_list.front_ptr(), plc_list.size(), prt, errs);
						GAIA::U64 uEndTick = GAIA::TIME::tick_time();
						prt << "\t\tTimeLost : " << (GAIA::F64)(uEndTick - uStartTick) / 1000.0 / 1000.0 << "\n";
						if(pNewPLC == GNULL)
							PROM_RAISE_FATALERROR(101);
						else
						{
							this->ExecuteOutput(pNewPLC, pTempPL, prt, errs);
							this->ExecuteExportTempResult(plc_list.front_ptr(), plc_list.size(), pNewPLC, pTempPL, prt, errs);
							for(GAIA::SIZE y = 0; y < plc_size; y++)
							{
								if(ppPLC[y] == GNULL)
									continue;
								ppPLC[y]->BindNext(pNewPLC);
							}
						}
						new_plc_list.push_back(pNewPLC);
					}
				}

				/* Dispatch next layer. */
				__PipelineList pl_list;
				for(GAIA::SIZE x = 0; x < nextpl_size; ++x)
				{
					for(GAIA::SIZE y = 0; y < ppNextPL[x]->GetNextSize(); ++y)
					{
						Pipeline* pTempNext = dynamic_cast<Pipeline*>(ppNextPL[x]->GetNext(y));
						if(pTempNext == GNULL)
							continue;
						pl_list.push_back(pTempNext);
					}
				}
				if(pl_list.size() != 0)
				{
					this->Run(ppNextPL, nextpl_size,
						pl_list.front_ptr(), pl_list.size(),
						new_plc_list.front_ptr(), new_plc_list.size(),
						prt, errs);
				}
				for(GAIA::SIZE x = 0; x < pl_list.size(); ++x)
					pl_list[x]->Release();

				/* Release new pipeline context. */
				for(GAIA::SIZE x = 0; x < new_plc_list.size(); ++x)
				{
					if(new_plc_list[x] != GNULL)
					{
						new_plc_list[x]->UnbindPrevAll();
						new_plc_list[x]->UnbindNextAll();
						new_plc_list[x]->Release();
					}
				}
			}
		protected:
			virtual GAIA::GVOID Destruct()
			{
			}
		private:
			GINL GAIA::GVOID init()
			{
				m_plc_commandparam = GNULL;
			}
			GINL GAIA::GVOID ExecuteOutput(PipelineContext* pPLC, Pipeline* pPL, GAIA::PRINT::PrintBase& prt, __ErrorListType& errs)
			{
				GAIA_AST(!GAIA::ALGORITHM::stremp(pPLC->GetName()));
				if(!GAIA::ALGORITHM::stremp(pPLC->GetName()))
				{
					if(GAIA::ALGORITHM::strcmp(pPLC->GetName(), _T("Prom:PLC_CommandParam")) == 0)
						m_plc_commandparam = static_cast<PLC_CommandParam*>(pPLC);
				}
				if(m_plc_commandparam != GNULL)
				{
					for(GAIA::SIZE y = 0; y < m_plc_commandparam->cmdparam.cmd_size(); ++y)
					{
						const GAIA::TCH* pszCmd = m_plc_commandparam->cmdparam.cmd(y);
						if(GAIA::ALGORITHM::stremp(pszCmd))
							continue;
						if(GAIA::ALGORITHM::strcmp(pszCmd, _T("-o")) == 0)
						{
							if(m_plc_commandparam->cmdparam.param_size(y) == 2)
							{
								const GAIA::TCH* pszParam0 = m_plc_commandparam->cmdparam.param(y, 0);
								const GAIA::TCH* pszParam1 = m_plc_commandparam->cmdparam.param(y, 1);
								GAIA_AST(!GAIA::ALGORITHM::stremp(pszParam0));
								GAIA_AST(!GAIA::ALGORITHM::stremp(pszParam1));
								if(!GAIA::ALGORITHM::stremp(pszParam0) && !GAIA::ALGORITHM::stremp(pszParam1))
								{
									if(GAIA::ALGORITHM::strcmp(pszParam0, pPL->GetName()) == 0)
									{
										GAIA::FILESYSTEM::File ofile;
										if(ofile.Open(pszParam1, GAIA::FILESYSTEM::File::OPEN_TYPE_CREATEALWAYS | GAIA::FILESYSTEM::File::OPEN_TYPE_WRITE))
										{
											if(pPL->Output(pPLC, &ofile, prt))
												prt << "\t\tOutput " << pPL->GetName() << " successfully!\n";
											else
												PROM_RAISE_FATALERROR(104);
										}
										else
											PROM_RAISE_FATALERROR(503);
									}
								}
							}
							else if(m_plc_commandparam->cmdparam.param_size(y) == 1)
							{
								const GAIA::TCH* pszParam0 = m_plc_commandparam->cmdparam.param(y, 0);
								GAIA_AST(!GAIA::ALGORITHM::stremp(pszParam0));
								if(!GAIA::ALGORITHM::stremp(pszParam0))
								{
									if(GAIA::ALGORITHM::strcmp(pszParam0, pPL->GetName()) == 0)
									{
										if(pPL->Output(pPLC, GNULL, prt))
											prt << "\t\tOutput " << pPL->GetName() << " successfully!\n";
										else
											PROM_RAISE_FATALERROR(104);
									}
								}
							}
							else
								GAIA_AST(GAIA::False);
						}
					}
				}
			}
			GINL GAIA::GVOID ExecuteExportTempResult(PipelineContext** ppPLC, const GAIA::SIZE& plc_size, PipelineContext* pNewPLC, Pipeline* pPL, GAIA::PRINT::PrintBase& prt, __ErrorListType& errs)
			{
				GPCHR_NULL(ppPLC);
				GPCHR_ZERO(plc_size);
				GPCHR_NULL(pNewPLC);
				GPCHR_NULL(pPL);

				PLC_CommandParam* plc_commandparam = GNULL;
				PLC_File* plc_file = GNULL;
				PLC_FileCodeLinePrepare* plc_codelineprepare = GNULL;
				plc_commandparam = static_cast<PLC_CommandParam*>(pPL->GetPLCByName(ppPLC, plc_size, _T("Prom:PLC_CommandParam")));
				if(plc_commandparam == GNULL)
					goto FUNCTION_END;
				plc_file = static_cast<PLC_File*>(pPL->GetPLCByName(ppPLC, plc_size, _T("Prom:PLC_File")));
				if(plc_file == GNULL)
					goto FUNCTION_END;
				plc_codelineprepare = static_cast<PLC_FileCodeLinePrepare*>(pPL->GetPLCByName(ppPLC, plc_size, _T("Prom:PLC_FileCodeLinePrepare")));
				if(plc_codelineprepare == GNULL)
				{
					if(GAIA::ALGORITHM::strcmp(pNewPLC->GetName(), _T("Prom:PLC_FileCodeLinePrepare")) == 0)
						plc_codelineprepare = (PLC_FileCodeLinePrepare*)pNewPLC;
				}
				if(plc_codelineprepare == GNULL)
					goto FUNCTION_END;

				/* Execute. */
				const GAIA::TCH* pszExportPath = GNULL;
				GAIA::BL bMatch = GAIA::False;
				for(GAIA::SIZE x = 0; x < plc_commandparam->cmdparam.cmd_size(); ++x)
				{
					const GAIA::TCH* pszCmd = plc_commandparam->cmdparam.cmd(x);
					if(GAIA::ALGORITHM::stremp(pszCmd))
						continue;
					if(GAIA::ALGORITHM::strcmp(pszCmd, _T("-export")) == 0)
					{
						const GAIA::TCH* pszPLName = plc_commandparam->cmdparam.param(x, 0);
						if(GAIA::ALGORITHM::stremp(pszPLName))
							continue;
						if(GAIA::ALGORITHM::strcmp(pszPLName, pPL->GetName()) != 0)
							continue;
						pszExportPath = plc_commandparam->cmdparam.param(x, 1);
						if(pszExportPath == GNULL)
							continue;
						bMatch = GAIA::True;
						break;
					}
				}
				if(bMatch)
				{
					GAIA::TCH szPath[GAIA::FILESYSTEM::MAXPL];
					GAIA::ALGORITHM::strcpy(szPath, pszExportPath);
					GAIA::TCH* pszEnd = GAIA::ALGORITHM::strend(szPath);
					if(pszEnd != GNULL && *(pszEnd - 1) != '\\' && *(pszEnd - 1) != '/')
					{
						*pszEnd = '/';
						*(pszEnd + 1) = '\0';
					}
					GAIA::FILESYSTEM::Directory dir;
					if(dir.Exist(szPath) || dir.Create(szPath, GAIA::True))
					{
						for(GAIA::SIZE x = 0; x < plc_codelineprepare->file_codelines_list.size(); ++x)
						{
							DWARFS_MISC::TextLine& l = plc_codelineprepare->file_codelines_list[x].lines;
							__FileName fname = plc_file->filelist[x].name;
							GAIA_AST(!fname.empty());
							if(fname.empty())
								continue;
							fname.replace(_T("\\..\\"), _T("\\prev\\"));
							fname.replace(_T("..\\"), _T("prev\\"));
							fname.replace(_T("\\.."), _T("\\prev"));
							fname.replace(_T("/../"), _T("/prev/"));
							fname.replace(_T("../"), _T("prev/"));
							fname.replace(_T("/.."), _T("/prev"));
							fname.replace(_T(":\\"), _T("_disk\\"));
							fname.replace(_T(":/"), _T("_disk/"));

							GAIA::TCH szFinal[GAIA::FILESYSTEM::MAXPL];
							GAIA::ALGORITHM::strcpy(szFinal, szPath);
							GAIA::ALGORITHM::strcat(szFinal, fname.front_ptr());

							GAIA::TCH szFinalPath[GAIA::FILESYSTEM::MAXPL];
							GAIA::ALGORITHM::strcpy(szFinalPath, szFinal);
							GAIA::ALGORITHM::strpath(szFinalPath);

							if(!dir.Exist(szFinalPath) && !dir.Create(szFinalPath, GAIA::True))
							{
								PROM_RAISE_FILEERROR(506, szFinalPath);
								break;
							}

							GAIA::FILESYSTEM::File file;
							if(!file.Open(szFinal, GAIA::FILESYSTEM::File::OPEN_TYPE_CREATEALWAYS | GAIA::FILESYSTEM::File::OPEN_TYPE_WRITE))
							{
								PROM_RAISE_FILEERROR(503, szFinal);
								break;
							}
							DWARFS_MISC::TextFile textfile;
							textfile.charset_type(GAIA::CHARSET_TYPE_UTF16LE);
							DWARFS_MISC::TextFile::__StringType& strTextFile = textfile.get_string();
							for(GAIA::SIZE x = 0; x < l.size(); ++x)
							{
								strTextFile += l.get_line(x);
								strTextFile += FILEBREAK;
							}
							if(!textfile.save(file))
							{
								PROM_RAISE_FILEERROR(503, szFinal);
								break;
							}
						}
					}
					else
						PROM_RAISE_FILEERROR(506, szPath);
				}

			FUNCTION_END:
				if(plc_commandparam != GNULL)
					plc_commandparam->Release();
				if(plc_file != GNULL)
					plc_file->Release();
				if(plc_codelineprepare != GNULL && plc_codelineprepare != pNewPLC)
					plc_codelineprepare->Release();
			}
		private:
			PLC_CommandParam* m_plc_commandparam;
		};
	public:
		GINL Prom()
		{
		}
		GINL ~Prom()
		{
		}
		GINL GAIA::BL Command(const GAIA::TCH* psz, GAIA::PRINT::PrintBase& prt)
		{
			GAIA_AST(psz != GNULL);
			if(psz == GNULL)
				return GAIA::False;
			if(*psz == 0)
				return GAIA::False;

			PipelineDispatch* pPLD = new PipelineDispatch;
			PLC_SourceCommand* pPLC = new PLC_SourceCommand; pPLC->pszCmd = psz;
			Pipeline* pPL = this->ConstructPipeline();
			{
				pPLD->Run(GNULL, 0, &pPL, 1, (PipelineContext**)&pPLC, 1, prt, m_errors);
				this->PrintError(prt);
				this->ClearError();
			}
			this->DestructPipeline(pPL); pPL = GNULL;
			pPLC->Release(); pPLC = GNULL;
			pPLD->Release(); pPLD = GNULL;

			return GAIA::True;
		}
	private:
		GINL Pipeline* ConstructPipeline()
		{
			Pipeline* pl_cmdanalyze = new PL_CommandAnalyze;
			{
				PL_Help* pl_help = new PL_Help;
				pl_cmdanalyze->BindNext(pl_help);
				pl_help->Release();

				PL_FileCollect* pl_filecollect = new PL_FileCollect;
				pl_cmdanalyze->BindNext(pl_filecollect);
				{
					PL_LineCollect* pl_linecollect = new PL_LineCollect;
					pl_filecollect->BindNext(pl_linecollect);
					{
						PL_LineBreakCorrect* pl_linebreakcorrect = new PL_LineBreakCorrect;
						pl_linecollect->BindNext(pl_linebreakcorrect);
						pl_linebreakcorrect->Release();

						PL_Format* pl_format = new PL_Format;
						pl_linecollect->BindNext(pl_format);
						pl_format->Release();

						PL_WordStat* pl_wordstat = new PL_WordStat;
						pl_linecollect->BindNext(pl_wordstat);
						pl_wordstat->Release();

						PL_LineStat* pl_linestat = new PL_LineStat;
						pl_linecollect->BindNext(pl_linestat);
						pl_linestat->Release();

						PL_LinePrepare* pl_lineprepare = new PL_LinePrepare;
						pl_linecollect->BindNext(pl_lineprepare);
						pl_lineprepare->Release();
						{
							PL_FileStructureAnalyze* pl_filestructureanalyze = new PL_FileStructureAnalyze;
							pl_lineprepare->BindNext(pl_filestructureanalyze);
							pl_filestructureanalyze->Release();

							PL_ObjAnalyzeBase* pl_objanalyzebase = new PL_ObjAnalyzeBase;
							pl_lineprepare->BindNext(pl_objanalyzebase);
							pl_objanalyzebase->Release();
							{
								PL_ObjAnalyzeUnwrapMacro* pl_objanalyzeunwrapmacro = new PL_ObjAnalyzeUnwrapMacro;
								pl_objanalyzebase->BindNext(pl_objanalyzeunwrapmacro);
								pl_objanalyzeunwrapmacro->Release();
							}
						}

						PL_Save* pl_save = new PL_Save;
						pl_linecollect->BindNext(pl_save);
						pl_save->Release();
					}
					pl_linecollect->Release();
				}
				pl_filecollect->Release();
			}
			return pl_cmdanalyze;
		}
		GINL GAIA::GVOID DestructPipeline(Pipeline* pPL)
		{
			pPL->UnbindPrevAll();
			pPL->UnbindNextAll();
			pPL->Release();
		}
		GINL GAIA::GVOID PrintError(GAIA::PRINT::PrintBase& prt)
		{
			GAIA::PRINT::PrintFormat prtfmt;
			GAIA::PRINT::PrintFormat prtfmt_old;
			prt >> prtfmt_old;
			prt << prtfmt;

			for(GAIA::SIZE x = 0; x < m_errors.size(); ++x)
			{
				ERROR_SYSTEM::ErrorBase* pError = m_errors[x];
				if(pError == GNULL)
					continue;
				prt << "Prometheus:";
				prt << "P" << (GAIA::N32)pError->getstage();
				prt << "L" << (GAIA::N32)pError->getlevel();
				prt << "N" << (GAIA::N32)pError->getid();
				if(!GAIA::ALGORITHM::stremp(pError->getdesc()))
				{
					prt << ", ";
					prt << pError->getdesc();
				}
				if(!GAIA::ALGORITHM::stremp(pError->getfilename()))
				{
					prt << ", ";
					prt << pError->getfilename();
					if(pError->getfileline() != GINVALID)
						prt << "(" << pError->getfileline() << ")";
				}
				if(!GAIA::ALGORITHM::stremp(pError->getsample()))
				{
					prt << ", ";
					prt << pError->getsample();
				}
				prt << ". \n";
			}
			prt << prtfmt_old;
		}
		GINL GAIA::GVOID ClearError()
		{
			for(GAIA::SIZE x = 0; x < m_errors.size(); ++x)
			{
				ERROR_SYSTEM::ErrorBase* pError = m_errors[x];
				if(pError == GNULL)
					continue;
				delete pError;
			}
			m_errors.clear();
		}
	private:
		__ErrorListType m_errors;
	};
};

#endif
