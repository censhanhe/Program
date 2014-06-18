/*
	String operator from Chars and inverse.
*/

#ifndef 	__PROMETHEUS_H__
#define 	__PROMETHEUS_H__

#include "../GAIA/gaia.h"
#include "../DWARFS/MISC/cmdparam.h"
#include "../DWARFS/MISC/textline.h"

namespace PROM
{
	static const GAIA::GCH VERSION_STRING[] = "00.00.01.00";
	static const GAIA::U32 VERSION = 0x00000100;

	class Prom : public GAIA::Base
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
			class ErrorBase : public GAIA::Base
			{
			public:
				GINL ErrorBase(){m_uFileLine = (GAIA::U32)GINVALID;}
				virtual GAIA::U16 getid() const = 0;
				virtual GAIA::U8 getstage() const = 0;
				virtual GAIA::U8 getlevel() const = 0;
				virtual const GAIA::GCH* getdesc() const = 0;
				virtual const GAIA::GCH* getsample() const = 0;
				GINL GAIA::GVOID setfilename(const GAIA::GCH* pszFileName){m_strFileName = pszFileName;}
				GINL const GAIA::GCH* getfilename() const{return m_strFileName.front_ptr();}
				GINL GAIA::GVOID setfileline(GAIA::U32 uFileLine){m_uFileLine = uFileLine;}
				GINL GAIA::U32 getfileline() const{return m_uFileLine;}
			private:
				GAIA::CONTAINER::AString m_strFileName;
				GAIA::U32 m_uFileLine;
			};
			#define PROM_ERROR(id, stage, level, desc, sample) \
				class ERROR_##id : public ErrorBase\
				{\
				public:\
					virtual GAIA::U16 getid() const{return id;}\
					virtual GAIA::U8 getstage() const{return stage;}\
					virtual GAIA::U8 getlevel() const{return level;}\
					virtual const GAIA::GCH* getdesc() const{return desc;}\
					virtual const GAIA::GCH* getsample() const{return sample;}\
				};
			PROM_ERROR(101,		0x0000, 0x0000, "pipeline execute failed, no pipeline context returned", "");
			PROM_ERROR(102,		0x0000, 0x0000, "command parameters error", "");
			PROM_ERROR(103,		0x0000, 0x0000, "pipeline link structure error", "");
			PROM_ERROR(104,		0x0000, 0x0002, "pipeline output stage result failed", "");
			PROM_ERROR(501,		0x0000, 0x0003, "file specified by -i parameter is not exist", "");
			PROM_ERROR(502,		0x0000, 0x0004, "file not exist!", "");
			PROM_ERROR(503,		0x0000, 0x0002, "create file failed!", "");
			PROM_ERROR(504,		0x0000, 0x0003, "open file failed!", "");
			PROM_ERROR(511,		0x0000, 0x0002, "text line analyze failed!", "");
			PROM_ERROR(512,		0x0000, 0x0002, "text line save failed!", "");
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
		class PipelineContext : public DirectionalFreeLink<PipelineContext>
		{
		public:
			GINL PipelineContext(){}
			GINL ~PipelineContext(){}
			virtual const GAIA::GCH* GetName() const = 0;
		};
		class PLC_Empty : public PipelineContext
		{
		public:
			GINL PLC_Empty(){}
			GINL ~PLC_Empty(){}
			virtual const GAIA::GCH* GetName() const{return "Prom:PLC_Empty";}
		};
		class PLC_SourceCommand : public PipelineContext
		{
		public:
			GINL PLC_SourceCommand(){pszCmd = GNULL;}
			GINL ~PLC_SourceCommand(){}
			virtual const GAIA::GCH* GetName() const{return "Prom:PLC_SourceCommand";}
			const GAIA::GCH* pszCmd;
		};
		class PLC_CommandParam : public PipelineContext
		{
		public:
			GINL PLC_CommandParam(){this->init();}
			GINL ~PLC_CommandParam(){}
			virtual const GAIA::GCH* GetName() const{return "Prom:PLC_CommandParam";}
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
			virtual const GAIA::GCH* GetName() const{return "Prom:PLC_File";}
		public:
			typedef GAIA::CONTAINER::AString __FileName;
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
			virtual const GAIA::GCH* GetName() const{return "Prom:PLC_FileCodeLine";}
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
		class PLC_Word : public PipelineContext
		{
		public:
			typedef GAIA::CONTAINER::AString __WordType;
		public:
			GINL PLC_Word(){}
			GINL ~PLC_Word(){}
			virtual const GAIA::GCH* GetName() const{return "Prom:PLC_Word";}
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
			GINL PipelineContext* GetPLCByName(PipelineContext** ppPLC, const GAIA::SIZE& size, const GAIA::GCH* pszName) const
			{
				GAIA_AST(ppPLC != GNULL);
				if(ppPLC == GNULL)
					return GNULL;
				GAIA_AST(size != 0);
				if(size == 0)
					return GNULL;
				for(GAIA::SIZE x = 0; x < size; ++x)
				{
					if(ppPLC[x] == GNULL)
						continue;
					const GAIA::GCH* pszTempName = ppPLC[x]->GetName();
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
			virtual const GAIA::GCH* GetName() const = 0;
			virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size, GAIA::PRINT::PrintBase& prt, __ErrorListType& errs) = 0;
			virtual GAIA::BL Output(PipelineContext* pPLC, GAIA::FILESYSTEM::FileBase* pFile, GAIA::PRINT::PrintBase& prt){return GAIA::False;}
		};
		class PL_CommandAnalyze : public Pipeline
		{
		public:
			GINL PL_CommandAnalyze(){}
			GINL ~PL_CommandAnalyze(){}
			virtual const GAIA::GCH* GetName() const{return "Prom:PL_CommandAnalyze";}
			virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size, GAIA::PRINT::PrintBase& prt, __ErrorListType& errs)
			{
				/* Parameter check up. */
				GAIA_AST(ppPLC != GNULL);
				if(ppPLC == GNULL)
					return GNULL;
				GAIA_AST(size != 0);
				if(size == 0)
					return GNULL;
				PLC_SourceCommand* plc_sourcecommand = static_cast<PLC_SourceCommand*>(this->GetPLCByName(ppPLC, size, "Prom:PLC_SourceCommand"));
				if(plc_sourcecommand == GNULL)
					return GNULL;

				/* Initialize result pipeline context. */
				PLC_CommandParam* pRet = new PLC_CommandParam;
				pRet->cmdparam.begin_decl();
				{
					pRet->cmdparam.cmd_decl("help", "show help information", 0, 1, DWARFS_MISC::CmdParam::CMD_TYPE_INVALID);

					pRet->cmdparam.cmd_decl("-i", "input files", 1, GINVALID, DWARFS_MISC::CmdParam::CMD_TYPE_INVALID);
					pRet->cmdparam.cmd_decl("-I", "input directory", 1, GINVALID, DWARFS_MISC::CmdParam::CMD_TYPE_INVALID);
					pRet->cmdparam.cmd_decl("-E", "input directory files extension name filter", 1, GINVALID, DWARFS_MISC::CmdParam::CMD_TYPE_INVALID);
					pRet->cmdparam.cmd_decl("-s", "save changes to source files", 0, 0, DWARFS_MISC::CmdParam::CMD_TYPE_INVALID);
					pRet->cmdparam.cmd_decl("-o", "output the stage result", 1, 2, DWARFS_MISC::CmdParam::CMD_TYPE_INVALID);
					pRet->cmdparam.cmd_decl("-linebreak", "change lines break flag, use \"\\r\" \"\\n\" or \"\\r\\n\"", 1, 1, DWARFS_MISC::CmdParam::CMD_TYPE_INVALID);
					pRet->cmdparam.cmd_decl("-fmt", "format the codes", 0, 0, DWARFS_MISC::CmdParam::CMD_TYPE_INVALID);

					pRet->cmdparam.cmd_decl("-linestat", "statistics the lines, use -o to output the result", 0, 0, DWARFS_MISC::CmdParam::CMD_TYPE_INVALID);
					pRet->cmdparam.cmd_decl("-wordstat", "statistics the words, use -o to output the result", 0, 0, DWARFS_MISC::CmdParam::CMD_TYPE_INVALID);
					pRet->cmdparam.cmd_decl("-symbolstat", "statistics the symbols, use -o to output the result", 0, 0, DWARFS_MISC::CmdParam::CMD_TYPE_INVALID);
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
				if(GAIA::ALGORITHM::strcmp(pPLC->GetName(), "Prom:PLC_CommandParam") != 0)
					return GAIA::False;

				for(GAIA::SIZE x = 0; x < plc_sourcecommand->cmdparam.cmd_size(); ++x)
				{
					const GAIA::GCH* pszCmd = plc_sourcecommand->cmdparam.cmd(x);
					if(GAIA::ALGORITHM::stremp(pszCmd))
						continue;
					prt << "\t\t" << pszCmd << " ";
					for(GAIA::SIZE y = 0; y < plc_sourcecommand->cmdparam.param_size(x); ++y)
					{
						const GAIA::GCH* pszParam = plc_sourcecommand->cmdparam.param(x, y);
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
			virtual const GAIA::GCH* GetName() const{return "Prom:PL_Help";}
			virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size, GAIA::PRINT::PrintBase& prt, __ErrorListType& errs)
			{
				/* Parameter check up. */
				GAIA_AST(ppPLC != GNULL);
				if(ppPLC == GNULL)
					return GNULL;
				GAIA_AST(size != 0);
				if(size == 0)
					return GNULL;
				PLC_CommandParam* plc_commandparam = static_cast<PLC_CommandParam*>(this->GetPLCByName(ppPLC, size, "Prom:PLC_CommandParam"));
				if(plc_commandparam == GNULL)
					return GNULL;

				/* Initialize result pipeline context. */
				PLC_Empty* pRet = new PLC_Empty;
				for(GAIA::SIZE x = 0; x < plc_commandparam->cmdparam.cmd_size(); ++x)
				{
					const GAIA::GCH* pszCmd = plc_commandparam->cmdparam.cmd(x);
					if(GAIA::ALGORITHM::stremp(pszCmd))
						continue;
					if(GAIA::ALGORITHM::strcmp(pszCmd, "help") == 0)
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
								const GAIA::GCH* pszDeclCmd = plc_commandparam->cmdparam.cmd_decl_cmd(y);
								if(pszDeclCmd == GNULL)
									continue;
								const GAIA::GCH* pszDeclDesc = plc_commandparam->cmdparam.cmd_decl_desc(y);
								GAIA::SIZE min_param_size = plc_commandparam->cmdparam.cmd_decl_min_param_size(y);
								GAIA::SIZE max_param_size = plc_commandparam->cmdparam.cmd_decl_max_param_size(y);
								DWARFS_MISC::CmdParam::CMD_TYPE cmdtype = plc_commandparam->cmdparam.cmd_decl_type(y);
								if(GAIA::ALGORITHM::stremp(pszDeclDesc))
									pszDeclDesc = "Noinfo";
								prt << "\t" << "[" << y << "]" << pszDeclCmd << ", Info:" << pszDeclDesc << ", " <<
									"[" << min_param_size << ", " << max_param_size << "] " <<
									DWARFS_MISC::CMD_TYPE_ANAME[cmdtype] << "\n";
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
			virtual const GAIA::GCH* GetName() const{return "Prom:PL_FileCollect";}
			virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size, GAIA::PRINT::PrintBase& prt, __ErrorListType& errs)
			{
				/* Parameter check up. */
				GAIA_AST(ppPLC != GNULL);
				if(ppPLC == GNULL)
					return GNULL;
				GAIA_AST(size != 0);
				if(size == 0)
					return GNULL;
				PLC_CommandParam* plc_commandparam = static_cast<PLC_CommandParam*>(this->GetPLCByName(ppPLC, size, "Prom:PLC_CommandParam"));
				if(plc_commandparam == GNULL)
					return GNULL;

				/* Initialize result pipeline context. */
				PLC_File* pRet = new PLC_File;

				/* Execute. */
				typedef GAIA::CONTAINER::Vector<GAIA::CONTAINER::AString> __FileListType;
				typedef GAIA::CONTAINER::Vector<GAIA::CONTAINER::AString> __PathListType;
				typedef GAIA::CONTAINER::Vector<GAIA::CONTAINER::AString> __ExtListType;
				__FileListType listFile;
				__PathListType listPath;
				__ExtListType listExt;
				for(GAIA::SIZE x = 0; x < plc_commandparam->cmdparam.cmd_size(); ++x)
				{
					const GAIA::GCH* pszCmd = plc_commandparam->cmdparam.cmd(x);
					if(GAIA::ALGORITHM::stremp(pszCmd))
						continue;
					if(GAIA::ALGORITHM::strcmp(pszCmd, "-i") == 0)
					{
						for(GAIA::SIZE y = 0; y < plc_commandparam->cmdparam.param_size(x); ++y)
						{
							const GAIA::GCH* pszParam = plc_commandparam->cmdparam.param(x, y);
							if(GAIA::ALGORITHM::stremp(pszParam))
								continue;
							listFile.push_back(pszParam);
						}
					}
					else if(GAIA::ALGORITHM::strcmp(pszCmd, "-I") == 0)
					{
						for(GAIA::SIZE y = 0; y < plc_commandparam->cmdparam.param_size(x); ++y)
						{
							const GAIA::GCH* pszParam = plc_commandparam->cmdparam.param(x, y);
							if(GAIA::ALGORITHM::stremp(pszParam))
								continue;
							listPath.push_back(pszParam);
						}
					}
					else if(GAIA::ALGORITHM::strcmp(pszCmd, "-E") == 0)
					{
						for(GAIA::SIZE y = 0; y < plc_commandparam->cmdparam.param_size(x); ++y)
						{
							const GAIA::GCH* pszParam = plc_commandparam->cmdparam.param(x, y);
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
				GAIA::CONTAINER::AString strExt;
				for(__ExtListType::_sizetype x = 0; x < listExt.size(); ++x)
				{
					if(!strExt.empty())
						strExt += "|";
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
										tempfile.name += "/";
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
			virtual const GAIA::GCH* GetName() const{return "Prom:PL_LineCollect";}
			virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size, GAIA::PRINT::PrintBase& prt, __ErrorListType& errs)
			{
				/* Parameter check up. */
				GAIA_AST(ppPLC != GNULL);
				if(ppPLC == GNULL)
					return GNULL;
				GAIA_AST(size != 0);
				if(size == 0)
					return GNULL;
				PLC_File* plc_file = static_cast<PLC_File*>(this->GetPLCByName(ppPLC, size, "Prom:PLC_File"));
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
					if(!pRet->file_codelines_list[x].lines.load(&file))
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
			virtual const GAIA::GCH* GetName() const{return "Prom:PL_LineBreakCorrect";}
			virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size, GAIA::PRINT::PrintBase& prt, __ErrorListType& errs)
			{
				/* Parameter check up. */
				GAIA_AST(ppPLC != GNULL);
				if(ppPLC == GNULL)
					return GNULL;
				GAIA_AST(size != 0);
				if(size == 0)
					return GNULL;
				GAIA::CONTAINER::AChars chs;
				PLC_Empty* pRet = GNULL;
				PLC_CommandParam* plc_commandparam = GNULL;
				PLC_File* plc_file = GNULL;
				PLC_FileCodeLine* plc_codelines = GNULL;
				plc_commandparam = static_cast<PLC_CommandParam*>(this->GetPLCByName(ppPLC, size, "Prom:PLC_CommandParam"));
				if(plc_commandparam == GNULL)
					goto FUNCTION_END;
				plc_file = static_cast<PLC_File*>(this->GetPLCByName(ppPLC, size, "Prom:PLC_File"));
				if(plc_file == GNULL)
					goto FUNCTION_END;
				plc_codelines = static_cast<PLC_FileCodeLine*>(this->GetPLCByName(ppPLC, size, "Prom:PLC_FileCodeLine"));
				if(plc_codelines == GNULL)
					goto FUNCTION_END;

				/* Initialize result pipeline context. */
				pRet = new PLC_Empty;

				/* Execute. */
				for(GAIA::SIZE x = 0; x < plc_commandparam->cmdparam.cmd_size(); ++x)
				{
					const GAIA::GCH* pszCmd = plc_commandparam->cmdparam.cmd(x);
					if(GAIA::ALGORITHM::stremp(pszCmd))
						continue;
					if(GAIA::ALGORITHM::strcmp(pszCmd, "-linebreak") == 0)
					{
						GAIA_AST(plc_commandparam->cmdparam.param_size(x) == 1);
						if(plc_commandparam->cmdparam.param_size(x) == 1)
						{
							chs = plc_commandparam->cmdparam.param(x, 0);
							break;
						}
					}
				}
				if(chs == "\\r\\n")
					chs = "\r\n";
				else if(chs == "\\n")
					chs = "\n";
				else if(chs == "\\r")
					chs = "\r";
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
					GAIA::CONTAINER::AString strTemp;
					for(GAIA::SIZE x = 0; x < plc_codelines->file_codelines_list.size(); ++x)
					{
						PLC_FileCodeLine::__FileCodelinesList::_datatype& t = plc_codelines->file_codelines_list[x];
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
									if(chs == "\n")
									{
										if(strTemp.size() >= 2)
										{
											if(strTemp[strTemp.size() - 2] == '\r' &&
												strTemp[strTemp.size() - 1] == '\n')
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

							remove_rn += strTemp.replace("\r\n", "");
							remove_n += strTemp.replace("\n", "");
							remove_r += strTemp.replace("\r", "");
							strTemp += chs.front_ptr();

							if(bExistValidFlag)
							{
								if(chs == "\r\n")
									--remove_rn;
								if(chs == "\n")
									--remove_n;
								if(chs == "\r")
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

					GAIA::CONTAINER::AChars tempchs;
					if(chs == "\r\n")
						tempchs = "\\r\\n";
					else if(chs == "\n")
						tempchs = "\\n";
					else if(chs == "\r")
						tempchs = "\\r";
					else
						tempchs = "(InvalidCharacter)";
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
				if(plc_codelines != GNULL)
					plc_codelines->Release();
				return pRet;
			}
		};
		class PL_Format : public Pipeline
		{
		public:
			GINL PL_Format(){}
			GINL ~PL_Format(){}
			virtual const GAIA::GCH* GetName() const{return "Prom:PL_Format";}
			virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size, GAIA::PRINT::PrintBase& prt, __ErrorListType& errs)
			{
				/* Parameter check up. */
				GAIA_AST(ppPLC != GNULL);
				if(ppPLC == GNULL)
					return GNULL;
				GAIA_AST(size != 0);
				if(size == 0)
					return GNULL;
				PLC_Empty* pRet = GNULL;
				PLC_CommandParam* plc_commandparam = GNULL;
				PLC_File* plc_file = GNULL;
				PLC_FileCodeLine* plc_codelines = GNULL;
				plc_commandparam = static_cast<PLC_CommandParam*>(this->GetPLCByName(ppPLC, size, "Prom:PLC_CommandParam"));
				if(plc_commandparam == GNULL)
					goto FUNCTION_END;
				plc_file = static_cast<PLC_File*>(this->GetPLCByName(ppPLC, size, "Prom:PLC_File"));
				if(plc_file == GNULL)
					goto FUNCTION_END;
				plc_codelines = static_cast<PLC_FileCodeLine*>(this->GetPLCByName(ppPLC, size, "Prom:PLC_FileCodeLine"));
				if(plc_codelines == GNULL)
					goto FUNCTION_END;

				/* Initialize result pipeline context. */
				pRet = new PLC_Empty;

				/* Execute. */
				GAIA::BL bFmt = GAIA::False;
				for(GAIA::SIZE x = 0; x < plc_commandparam->cmdparam.cmd_size(); ++x)
				{
					const GAIA::GCH* pszCmd = plc_commandparam->cmdparam.cmd(x);
					if(GAIA::ALGORITHM::stremp(pszCmd))
						continue;
					if(GAIA::ALGORITHM::strcmp(pszCmd, "-fmt") == 0)
					{
						bFmt = GAIA::True;
						break;
					}
				}
				if(bFmt)
				{
					typedef GAIA::CONTAINER::AString __LineType;
					__LineType strLine;
					GAIA::SIZE remove_space_count = 0;
					GAIA::SIZE remove_tab_count = 0;
					GAIA::SIZE line_change_count = 0;
					GAIA::SIZE file_change_count = 0;
					for(GAIA::SIZE x = 0; x < plc_codelines->file_codelines_list.size(); ++x)
					{
						GAIA::BL bFileChanged = GAIA::False;
						PLC_FileCodeLine::FileCodeLines& fcl = plc_codelines->file_codelines_list[x];

						/* Line inside based code-format. */
						for(GAIA::SIZE y = 0; y < fcl.lines.size(); ++y)
						{
							strLine = fcl.lines.get_line(y);
							if(strLine.empty())
								continue;
							GAIA::BL bLineChanged = GAIA::False;

							/* Get line break flag. */
							GAIA::GCH szLineBreak[3];
							if(strLine.back() == '\n')
							{
								if(strLine.size() > 1)
								{
									if(strLine[strLine.size() - 2] == '\r')
										GAIA::ALGORITHM::strcpy(szLineBreak, "\r\n");
									else
										GAIA::ALGORITHM::strcpy(szLineBreak, "\n");
								}
								else
									GAIA::ALGORITHM::strcpy(szLineBreak, "\n");
							}
							else if(strLine.back() == '\r')
								GAIA::ALGORITHM::strcpy(szLineBreak, "\r");
							if(GAIA::ALGORITHM::strlen(szLineBreak) == 2)
								strLine.resize(strLine.size() - 2);
							else
								strLine.resize(strLine.size() - 1);

							/* Delete space or tab at line tail. */
							__LineType::it itback = strLine.back_it();
							while(!itback.empty())
							{
								if(*itback != ' ' && *itback != '\t')
									break;
								if(*itback == ' ')
								{
									++remove_space_count;
									bLineChanged = GAIA::True;
								}
								else if(*itback == '\t')
								{
									++remove_tab_count;
									bLineChanged = GAIA::True;
								}
								GAIA_AST(strLine.size() > 0);
								strLine.resize(strLine.size() - 1);
								--itback;
							}

							/* Remove continuation-space. */
							GAIA::GCH chOld = '\0';
							for(GAIA::SIZE z = 0; z < strLine.size(); ++z)
							{
								if(strLine[z] == ' ')
								{
									if(chOld == ' ')
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
				if(plc_codelines != GNULL)
					plc_codelines->Release();
				return pRet;
			}
		};
		class PL_LineStat : public Pipeline
		{
		public:
			GINL PL_LineStat(){}
			GINL ~PL_LineStat(){}
			virtual const GAIA::GCH* GetName() const{return "Prom:PL_LineStat";}
			virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size, GAIA::PRINT::PrintBase& prt, __ErrorListType& errs)
			{
				return GNULL;
			}
		};
		class PL_WordStat : public Pipeline
		{
		public:
			GINL PL_WordStat(){}
			GINL ~PL_WordStat(){}
			virtual const GAIA::GCH* GetName() const{return "Prom:PL_WordStat";}
			virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size, GAIA::PRINT::PrintBase& prt, __ErrorListType& errs)
			{
				/* Parameter check up. */
				GAIA_AST(ppPLC != GNULL);
				if(ppPLC == GNULL)
					return GNULL;
				GAIA_AST(size != 0);
				if(size == 0)
					return GNULL;
				PLC_Word* pRet = GNULL;
				PLC_CommandParam* plc_commandparam = GNULL;
				PLC_File* plc_file = GNULL;
				PLC_FileCodeLine* plc_codelines = GNULL;
				plc_commandparam = static_cast<PLC_CommandParam*>(this->GetPLCByName(ppPLC, size, "Prom:PLC_CommandParam"));
				if(plc_commandparam == GNULL)
					goto FUNCTION_END;
				plc_file = static_cast<PLC_File*>(this->GetPLCByName(ppPLC, size, "Prom:PLC_File"));
				if(plc_file == GNULL)
					goto FUNCTION_END;
				plc_codelines = static_cast<PLC_FileCodeLine*>(this->GetPLCByName(ppPLC, size, "Prom:PLC_FileCodeLine"));
				if(plc_codelines == GNULL)
					goto FUNCTION_END;

				/* Initialize result pipeline context. */
				pRet = new PLC_Word;

				/* Execute. */
				GAIA::BL bWordStat = GAIA::False;
				for(GAIA::SIZE x = 0; x < plc_commandparam->cmdparam.cmd_size(); ++x)
				{
					const GAIA::GCH* pszCmd = plc_commandparam->cmdparam.cmd(x);
					if(GAIA::ALGORITHM::stremp(pszCmd))
						continue;
					if(GAIA::ALGORITHM::strcmp(pszCmd, "-wordstat") == 0)
					{
						bWordStat = GAIA::True;
						break;
					}
				}
				if(bWordStat)
				{
					DWARFS_MISC::TextLine::__LineType strLine;
					PLC_Word::Word word;
					for(GAIA::SIZE x = 0; x < plc_codelines->file_codelines_list.size(); ++x)
					{
						DWARFS_MISC::TextLine& l = plc_codelines->file_codelines_list[x].lines;
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
								if(strLine[z] == '\t' || strLine[z] == ' ' || strLine[z] == '\r' || strLine[z] == '\n')
								{
									newflag = EMPTY_FLAG;
								}
								else if(GAIA::ALGORITHM::isalpha(strLine[z]) || 
									GAIA::ALGORITHM::isdigit(strLine[z]) || 
									strLine[z] == '_' || 
									strLine[z] == '.' && z + 1 < strLine.size() && GAIA::ALGORITHM::isdigit(strLine[z + 1]))
								{
									newflag = CHAR_FLAG;
								}
								else
								{
									newflag = SIGN_FLAG;
								}

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
											static const GAIA::GCH* LINK_SIGN_LIST[] = 
											{
												">>", "<<", 
												"++", "--", 
												"+=", "-=", "*=", "/=", 
												"==", "!=", ">=", "<="
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
				if(plc_codelines != GNULL)
					plc_codelines->Release();
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
				if(GAIA::ALGORITHM::strcmp(pPLC->GetName(), "Prom:PLC_Word") != 0)
					return GAIA::False;

				GAIA::SIZE index = 0;
				PLC_Word::__WordSetType::it it = plc_word->wordset.front_it();
				while(!it.empty())
				{
					PLC_Word::Word& word = *it;
					if(pFile != GNULL)
					{
						GAIA::GCH szTemp[32];
						GAIA::ALGORITHM::int2str(index, szTemp);
						pFile->Write("[", 1);
						pFile->Write(szTemp, GAIA::ALGORITHM::strlen(szTemp));
						pFile->Write("] \"", 3);
						pFile->Write(word.strWord.front_ptr(), word.strWord.size());
						pFile->Write("\", Count = ", sizeof("\", Count = ") - 1);
						GAIA::ALGORITHM::int2str(word.uExistCount, szTemp);
						pFile->Write(szTemp, GAIA::ALGORITHM::strlen(szTemp));
						pFile->Write("\n", 1);
					}
					else
						prt << "[" << index++ << "] \"" << word.strWord.front_ptr() << "\", Count = " << word.uExistCount << "\n";
					++it;
				}

				return GAIA::True;
			}
		};
		class PL_SymbolStat : public Pipeline
		{
		public:
			GINL PL_SymbolStat(){}
			GINL ~PL_SymbolStat(){}
			virtual const GAIA::GCH* GetName() const{return "Prom:PL_SymbolStat";}
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
			virtual const GAIA::GCH* GetName() const{return "Prom:PL_SingleLineAnalyze";}
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
			virtual const GAIA::GCH* GetName() const{return "Prom:PL_Save";}
			virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size, GAIA::PRINT::PrintBase& prt, __ErrorListType& errs)
			{
				/* Parameter check up. */
				GAIA_AST(ppPLC != GNULL);
				if(ppPLC == GNULL)
					return GNULL;
				GAIA_AST(size != 0);
				if(size == 0)
					return GNULL;
				PLC_Empty* pRet = GNULL;
				PLC_CommandParam* plc_commandparam = GNULL;
				PLC_File* plc_file = GNULL;
				PLC_FileCodeLine* plc_codelines = GNULL;
				plc_commandparam = static_cast<PLC_CommandParam*>(this->GetPLCByName(ppPLC, size, "Prom:PLC_CommandParam"));
				if(plc_commandparam == GNULL)
					goto FUNCTION_END;
				plc_file = static_cast<PLC_File*>(this->GetPLCByName(ppPLC, size, "Prom:PLC_File"));
				if(plc_file == GNULL)
					goto FUNCTION_END;
				plc_codelines = static_cast<PLC_FileCodeLine*>(this->GetPLCByName(ppPLC, size, "Prom:PLC_FileCodeLine"));
				if(plc_codelines == GNULL)
					goto FUNCTION_END;

				/* Initialize result pipeline context. */
				pRet = new PLC_Empty;

				/* Execute. */
				GAIA::BL bSaveCmd = GAIA::False;
				for(GAIA::SIZE x = 0; x < plc_commandparam->cmdparam.cmd_size(); ++x)
				{
					const GAIA::GCH* pszCmd = plc_commandparam->cmdparam.cmd(x);
					if(GAIA::ALGORITHM::stremp(pszCmd))
						continue;
					if(GAIA::ALGORITHM::strcmp(pszCmd, "-s") == 0)
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
							if(plc_codelines->file_codelines_list[x].lines.save(&file))
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
				if(plc_codelines != GNULL)
					plc_codelines->Release();

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
				GAIA_AST(ppNextPL != GNULL);
				if(ppNextPL == GNULL)
					return;
				GAIA_AST(nextpl_size != 0);
				if(nextpl_size == 0)
					return;
				GAIA_AST(ppPLC != GNULL);
				if(ppPLC == GNULL)
					return;
				GAIA_AST(plc_size != 0);
				if(plc_size == 0)
					return;
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
						PipelineContext* pNewPLC = pTempPL->Execute(ppPLC, plc_size, prt, errs);
						if(pNewPLC == GNULL)
							PROM_RAISE_FATALERROR(101);
						else
						{
							this->ExecuteOutput(pNewPLC, pTempPL, prt, errs);
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
						PipelineContext* pNewPLC = pTempPL->Execute(plc_list.front_ptr(), plc_list.size(), prt, errs);
						if(pNewPLC == GNULL)
							PROM_RAISE_FATALERROR(101);
						else
						{
							this->ExecuteOutput(pNewPLC, pTempPL, prt, errs);
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
					if(GAIA::ALGORITHM::strcmp(pPLC->GetName(), "Prom:PLC_CommandParam") == 0)
						m_plc_commandparam = static_cast<PLC_CommandParam*>(pPLC);
				}
				if(m_plc_commandparam != GNULL)
				{
					for(GAIA::SIZE y = 0; y < m_plc_commandparam->cmdparam.cmd_size(); ++y)
					{
						const GAIA::GCH* pszCmd = m_plc_commandparam->cmdparam.cmd(y);
						if(GAIA::ALGORITHM::stremp(pszCmd))
							continue;
						if(GAIA::ALGORITHM::strcmp(pszCmd, "-o") == 0)
						{
							if(m_plc_commandparam->cmdparam.param_size(y) == 2)
							{
								const GAIA::GCH* pszParam0 = m_plc_commandparam->cmdparam.param(y, 0);
								const GAIA::GCH* pszParam1 = m_plc_commandparam->cmdparam.param(y, 1);
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
								const GAIA::GCH* pszParam0 = m_plc_commandparam->cmdparam.param(y, 0);
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
		GINL GAIA::BL Command(const GAIA::GCH* psz, GAIA::PRINT::PrintBase& prt)
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

				Pipeline* pl_filecollect = new PL_FileCollect;
				pl_cmdanalyze->BindNext(pl_filecollect);
				{
					Pipeline* pl_linecollect = new PL_LineCollect;
					pl_filecollect->BindNext(pl_linecollect);
					{
						PL_LineBreakCorrect* pl_linebreakcorrect = new PL_LineBreakCorrect;
						pl_linecollect->BindNext(pl_linebreakcorrect);
						pl_linebreakcorrect->Release();

						PL_Format* pl_format = new PL_Format;
						pl_linecollect->BindNext(pl_format);
						pl_format->Release();

						PL_WordStat* pl_wordstatistics = new PL_WordStat;
						pl_linecollect->BindNext(pl_wordstatistics);
						pl_wordstatistics->Release();

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
