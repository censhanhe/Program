/*
	String operator from Chars and inverse.
*/

#ifndef 	__PROMETHEUS_H__
#define 	__PROMETHEUS_H__

#include "../GAIA/gaia.h"
#include "../DWARFS/MISC/cmdparam.h"
#include "../DWARFS/MISC/textlines.h"

namespace PROM
{
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
			PROM_ERROR(501,		0x0000, 0x0003, "file specified by -i parameter is not exist", "");
			PROM_ERROR(502,		0x0000, 0x0004, "file not exist!", "");
			PROM_ERROR(503,		0x0000, 0x0002, "create file failed!", "");
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
		class PLCEmpty : public PipelineContext
		{
		public:
			GINL PLCEmpty(){}
			GINL ~PLCEmpty(){}
			virtual const GAIA::GCH* GetName() const{return "Prom:PLCEmpty";}
		};
		class PLCSourceCommand : public PipelineContext
		{
		public:
			GINL PLCSourceCommand(){pszCmd = GNULL;}
			GINL ~PLCSourceCommand(){}
			virtual const GAIA::GCH* GetName() const{return "Prom:PLCSourceCommand";}
			const GAIA::GCH* pszCmd;
		};
		class PLCCommandParam : public PipelineContext
		{
		public:
			GINL PLCCommandParam(){this->init();}
			GINL ~PLCCommandParam(){}
			virtual const GAIA::GCH* GetName() const{return "Prom:PLCCommandParam";}
			DWARFS_MISC::CmdParam cmdparam;
		private:
			GINL GAIA::GVOID init()
			{
			}
		};
		class PLCFile : public PipelineContext
		{
		public:
			GINL PLCFile(){}
			GINL ~PLCFile(){}
			virtual const GAIA::GCH* GetName() const{return "Prom:PLCFile";}
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
		class PLCFileCodeLines : public PipelineContext
		{
		public:
			GINL PLCFileCodeLines(){}
			GINL ~PLCFileCodeLines(){}
			virtual const GAIA::GCH* GetName() const{return "Prom:PLCFileCodeLines";}
		public:
			class FileCodeLines
			{
			public:
				DWARFS_MISC::TextLines lines;
			};
			typedef GAIA::CONTAINER::Vector<FileCodeLines> __FileCodelinesList;
		public:
			__FileCodelinesList file_codelines_list;
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
		};
		class PLCommandAnalyze : public Pipeline
		{
		public:
			GINL PLCommandAnalyze(){}
			GINL ~PLCommandAnalyze(){}
			virtual const GAIA::GCH* GetName() const{return "Prom:PLCommandAnalyze";}
			virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size, GAIA::PRINT::PrintBase& prt, __ErrorListType& errs)
			{
				/* Parameter check up. */
				GAIA_AST(ppPLC != GNULL);
				if(ppPLC == GNULL)
					return GNULL;
				GAIA_AST(size != 0);
				if(size == 0)
					return GNULL;
				PLCSourceCommand* plc_sourcecommand = static_cast<PLCSourceCommand*>(this->GetPLCByName(ppPLC, size, "Prom:PLCSourceCommand"));
				if(plc_sourcecommand == GNULL)
					return GNULL;

				/* Initialize result pipeline context. */
				PLCCommandParam* pRet = new PLCCommandParam;
				pRet->cmdparam.begin_decl();
				{
					pRet->cmdparam.cmd_decl("-i", "input files", 1, GINVALID, DWARFS_MISC::CmdParam::CMD_TYPE_INVALID);
					pRet->cmdparam.cmd_decl("-I", "input directory", 1, GINVALID, DWARFS_MISC::CmdParam::CMD_TYPE_INVALID);
					pRet->cmdparam.cmd_decl("-E", "input directory files extension name filter", 1, GINVALID, DWARFS_MISC::CmdParam::CMD_TYPE_INVALID);
					pRet->cmdparam.cmd_decl("-s", "save changes to source files", 0, 0, DWARFS_MISC::CmdParam::CMD_TYPE_INVALID);
					pRet->cmdparam.cmd_decl("-linebreak", "change lines break flag, use \"\\r\" \"\\n\" or \"\\r\\n\"", 1, 1, DWARFS_MISC::CmdParam::CMD_TYPE_INVALID);
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
		};
		class PLFileCollect : public Pipeline
		{
		public:
			GINL PLFileCollect(){}
			GINL ~PLFileCollect(){}
			virtual const GAIA::GCH* GetName() const{return "Prom:PLFileCollect";}
			virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size, GAIA::PRINT::PrintBase& prt, __ErrorListType& errs)
			{
				/* Parameter check up. */
				GAIA_AST(ppPLC != GNULL);
				if(ppPLC == GNULL)
					return GNULL;
				GAIA_AST(size != 0);
				if(size == 0)
					return GNULL;
				PLCCommandParam* plc_commandparam = static_cast<PLCCommandParam*>(this->GetPLCByName(ppPLC, size, "Prom:PLCCommandParam"));
				if(plc_commandparam == GNULL)
					return GNULL;

				/* Initialize result pipeline context. */
				PLCFile* pRet = new PLCFile;

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
					PLCFile::File tempfile;
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
				PLCFile::File tempfile;
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
		class PLLineCollect : public Pipeline
		{
		public:
			GINL PLLineCollect(){}
			GINL ~PLLineCollect(){}
			virtual const GAIA::GCH* GetName() const{return "Prom:PLLineCollect";}
			virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size, GAIA::PRINT::PrintBase& prt, __ErrorListType& errs)
			{
				/* Parameter check up. */
				GAIA_AST(ppPLC != GNULL);
				if(ppPLC == GNULL)
					return GNULL;
				GAIA_AST(size != 0);
				if(size == 0)
					return GNULL;
				PLCFile* plc_file = static_cast<PLCFile*>(this->GetPLCByName(ppPLC, size, "Prom:PLCFile"));
				if(plc_file == GNULL)
					return GNULL;

				/* Initialize result pipeline context. */
				PLCFileCodeLines* pRet = new PLCFileCodeLines;

				/* Execute */
				pRet->file_codelines_list.resize(plc_file->filelist.size());
				GAIA::SIZE uTotalLineCount = 0;
				for(PLCFile::__FileList::_sizetype x = 0; x < plc_file->filelist.size(); ++x)
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
		class PLLineBreakCorrect : public Pipeline
		{
		public:
			GINL PLLineBreakCorrect(){}
			GINL ~PLLineBreakCorrect(){}
			virtual const GAIA::GCH* GetName() const{return "Prom:PLLineBreakCorrect";}
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
				PLCEmpty* pRet = GNULL;
				PLCCommandParam* plc_commandparam = GNULL;
				PLCFile* plc_file = GNULL;
				PLCFileCodeLines* plc_codelines = GNULL;
				plc_commandparam = static_cast<PLCCommandParam*>(this->GetPLCByName(ppPLC, size, "Prom:PLCCommandParam"));
				if(plc_commandparam == GNULL)
					goto FUNCTION_END;
				plc_file = static_cast<PLCFile*>(this->GetPLCByName(ppPLC, size, "Prom:PLCFile"));
				if(plc_file == GNULL)
					goto FUNCTION_END;
				plc_codelines = static_cast<PLCFileCodeLines*>(this->GetPLCByName(ppPLC, size, "Prom:PLCFileCodeLines"));
				if(plc_codelines == GNULL)
					goto FUNCTION_END;

				/* Initialize result pipeline context. */
				pRet = new PLCEmpty;

				/* Execute */
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
						PLCFileCodeLines::__FileCodelinesList::_datatype& t = plc_codelines->file_codelines_list[x];
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
								if(strTemp.rfind(chs.front_ptr(), strTemp.size() - 1) != strTemp.size() - chs.size())
									++add;
								else
									bExistValidFlag = GAIA::True;
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
					prt << "\t\tAdd " << chs.front_ptr() << "=" << add << ".\n";
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
		class PLLineStatistics : public Pipeline
		{
		public:
			GINL PLLineStatistics(){}
			GINL ~PLLineStatistics(){}
			virtual const GAIA::GCH* GetName() const{return "Prom:PLLineStatistics";}
			virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size, GAIA::PRINT::PrintBase& prt, __ErrorListType& errs)
			{
				return GNULL;
			}
		};
		class PLSymbolStatistics : public Pipeline
		{
		public:
			GINL PLSymbolStatistics(){}
			GINL ~PLSymbolStatistics(){}
			virtual const GAIA::GCH* GetName() const{return "Prom:PLSymbolStatistics";}
			virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size, GAIA::PRINT::PrintBase& prt, __ErrorListType& errs)
			{
				return GNULL;
			}
		};
		class PLSingleLineAnalyze : public Pipeline
		{
		public:
			GINL PLSingleLineAnalyze(){}
			GINL ~PLSingleLineAnalyze(){}
			virtual const GAIA::GCH* GetName() const{return "Prom:PLSingleLineAnalyze";}
			virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size, GAIA::PRINT::PrintBase& prt, __ErrorListType& errs)
			{
				return GNULL;
			}
		};
		class PLSave : public Pipeline
		{
		public:
			GINL PLSave(){}
			GINL ~PLSave(){}
			virtual const GAIA::GCH* GetName() const{return "Prom:PLSave";}
			virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size, GAIA::PRINT::PrintBase& prt, __ErrorListType& errs)
			{
				/* Parameter check up. */
				GAIA_AST(ppPLC != GNULL);
				if(ppPLC == GNULL)
					return GNULL;
				GAIA_AST(size != 0);
				if(size == 0)
					return GNULL;
				PLCEmpty* pRet = GNULL;
				PLCCommandParam* plc_commandparam = GNULL;
				PLCFile* plc_file = GNULL;
				PLCFileCodeLines* plc_codelines = GNULL;
				plc_commandparam = static_cast<PLCCommandParam*>(this->GetPLCByName(ppPLC, size, "Prom:PLCCommandParam"));
				if(plc_commandparam == GNULL)
					goto FUNCTION_END;
				plc_file = static_cast<PLCFile*>(this->GetPLCByName(ppPLC, size, "Prom:PLCFile"));
				if(plc_file == GNULL)
					goto FUNCTION_END;
				plc_codelines = static_cast<PLCFileCodeLines*>(this->GetPLCByName(ppPLC, size, "Prom:PLCFileCodeLines"));
				if(plc_codelines == GNULL)
					goto FUNCTION_END;

				/* Initialize result pipeline context. */
				pRet = new PLCEmpty;

				/* Execute */
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
						prt << "\tPipeline Stage : " << pTempPL->GetName() << "\n";
						PipelineContext* pNewPLC = pTempPL->Execute(ppPLC, plc_size, prt, errs);
						if(pNewPLC == GNULL)
							PROM_RAISE_FATALERROR(101);
						else
						{
							for(GAIA::SIZE y = 0; y  < plc_size; y++)
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
						prt << "\tPipeline Stage : " << pTempPL->GetName() << "\n";
						PipelineContext* pNewPLC = pTempPL->Execute(plc_list.front_ptr(), plc_list.size(), prt, errs);
						if(pNewPLC == GNULL)
							PROM_RAISE_FATALERROR(101);
						else
						{
							for(GAIA::SIZE y = 0; y  < plc_size; y++)
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
			PLCSourceCommand* pPLC = new PLCSourceCommand; pPLC->pszCmd = psz;
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
			Pipeline* pl_cmdanalyze = new PLCommandAnalyze;
			{
				Pipeline* pl_filecollect = new PLFileCollect;
				pl_cmdanalyze->BindNext(pl_filecollect);
				{
					Pipeline* pl_linecollect = new PLLineCollect;
					pl_filecollect->BindNext(pl_linecollect);
					{
						PLLineBreakCorrect* pl_linebreakcorrect = new PLLineBreakCorrect;
						pl_linecollect->BindNext(pl_linebreakcorrect);
						pl_linebreakcorrect->Release();

						PLSave* pl_save = new PLSave;
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
