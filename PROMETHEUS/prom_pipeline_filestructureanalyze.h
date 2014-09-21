#ifndef		__PROM_PIPELINE_FILESTRUCTUREANALYZE_H__
#define		__PROM_PIPELINE_FILESTRUCTUREANALYZE_H__

namespace PROM
{
	class PL_FileStructureAnalyze : public Pipeline
	{
	public:
		GINL PL_FileStructureAnalyze(){}
		GINL ~PL_FileStructureAnalyze(){}
		virtual const GAIA::TCH* GetName() const{return _T("Prom:PL_FileStructureAnalyze");}
		virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size, GAIA::PRINT::PrintBase& prt, __ErrorListType& errs)
		{
			/* Parameter check up. */
			GPCHR_NULL_RET(ppPLC, GNIL);
			GPCHR_ZERO_RET(size, GNIL);

			PLC_FileStructure* pRet = GNIL;
			PLC_CommandParam* plc_commandparam = GNIL;
			PLC_File* plc_file = GNIL;
			PLC_FileCodeLinePrepare* plc_codelineprepare = GNIL;
			plc_commandparam = static_cast<PLC_CommandParam*>(this->GetPLCByName(ppPLC, size, _T("Prom:PLC_CommandParam")));
			if(plc_commandparam == GNIL)
				goto FUNCTION_END;
			plc_file = static_cast<PLC_File*>(this->GetPLCByName(ppPLC, size, _T("Prom:PLC_File")));
			if(plc_file == GNIL)
				goto FUNCTION_END;
			plc_codelineprepare = static_cast<PLC_FileCodeLinePrepare*>(this->GetPLCByName(ppPLC, size, _T("Prom:PLC_FileCodeLinePrepare")));
			if(plc_codelineprepare == GNIL)
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
					if(GAIA::ALGO::stremp(pLine))
						continue;
					const DWARFS_MISC::TextLine::__CharType* pFinded = GAIA::ALGO::strstr(pLine, "#include");
					if(pFinded == GNIL)
						continue;
					pFinded += GAIA::ALGO::strlen("#include");
					const DWARFS_MISC::TextLine::__CharType* pFindedNext = GNIL;
					if(*pFinded == _T('"'))
						pFindedNext = GAIA::ALGO::strch(pFinded + 1, _T('"'));
					else
						pFindedNext = GAIA::ALGO::strch(pFinded + 1, _T('>'));
					if(pFindedNext != GNIL)
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
			if(plc_commandparam != GNIL)
				plc_commandparam->Release();
			if(plc_file != GNIL)
				plc_file->Release();
			if(plc_codelineprepare != GNIL)
				plc_codelineprepare->Release();
			return pRet;
		}
		virtual GAIA::BL Output(PipelineContext* pPLC, GAIA::FSYS::FileBase* pFile, GAIA::PRINT::PrintBase& prt)
		{
			/* Parameter check up. */
			GAIA_AST(pPLC != GNIL);
			if(pPLC == GNIL)
				return GAIA::False;

			GAIA_AST(!GAIA::ALGO::stremp(pPLC->GetName()));
			if(GAIA::ALGO::stremp(pPLC->GetName()))
				return GAIA::False;

			PLC_FileStructure* plc_filestructure = static_cast<PLC_FileStructure*>(pPLC);
			if(plc_filestructure == GNIL)
				return GAIA::False;
			if(GAIA::ALGO::strcmp(pPLC->GetName(), _T("Prom:PLC_FileStructure")) != 0)
				return GAIA::False;

			/* Print parent relation. */
			if(pFile != GNIL && pFile->Tell() == 0)
			{
			#if GAIA_CHARSET == GAIA_CHARSET_UNICODE
				pFile->Write(GAIA::UTF16LE_FILEHEAD, sizeof(GAIA::UTF16LE_FILEHEAD));
			#endif
			}
			prt << "[To Parent]" << "\n";
			if(pFile != GNIL)
			{
				pFile->Write(_T("[To Parent]"), GAIA::ALGO::strlen("[To Parent]") * sizeof(GAIA::TCH));
				pFile->Write(FILEBREAK, GAIA::ALGO::strlen(FILEBREAK) * sizeof(FILEBREAK[0]));
			}
			PLC_FileStructure::__FileNodeSet::it it = plc_filestructure->filenodeset.front_it();
			for(; !it.empty(); ++it)
			{
				PLC_FileStructure::__FileNodeSet::_datatype& t = *it;
				if(t.childs.empty())
					this->OutputParentRelation(plc_filestructure, t, pFile, prt, 0);
			}

			/* Print child relation. */
			prt << "[To Child]" << "\n";
			if(pFile != GNIL)
			{
				pFile->Write(_T("[To Child]"), GAIA::ALGO::strlen("[To Child]") * sizeof(GAIA::TCH));
				pFile->Write(FILEBREAK, GAIA::ALGO::strlen(FILEBREAK) * sizeof(FILEBREAK[0]));
			}
			it = plc_filestructure->filenodeset.front_it();
			for(; !it.empty(); ++it)
			{
				PLC_FileStructure::__FileNodeSet::_datatype& t = *it;
				if(t.parents.empty())
					this->OutputChildRelation(plc_filestructure, t, pFile, prt, 0);
			}

			return GAIA::True;
		}
	private:
		GINL GAIA::GVOID OutputParentRelation(
			PLC_FileStructure* plc_filestructure,
			PLC_FileStructure::Node& node,
			GAIA::FSYS::FileBase* pFile,
			GAIA::PRINT::PrintBase& prt,
			GAIA::SIZE depth)
		{
			GPCHR_NULL(plc_filestructure);
			prt << node.name.front_ptr() << "\n";
			if(pFile != GNIL)
			{
				this->OutputDepth(prt, pFile, depth);
				pFile->Write(node.name.front_ptr(), node.name.size() * sizeof(__FileName::_datatype));
				pFile->Write(FILEBREAK, GAIA::ALGO::strlen(FILEBREAK) * sizeof(FILEBREAK[0]));
			}
			PLC_FileStructure::__FileLinkSet::it itlink = node.parents.front_it();
			for(; !itlink.empty(); ++itlink)
			{
				__FileName& filename = *itlink;
				PLC_FileStructure::Node* pParentNode = plc_filestructure->FindNode(filename);
				if(pParentNode != GNIL)
					this->OutputParentRelation(plc_filestructure, *pParentNode, pFile, prt, depth + 1);
			}
		}
		GINL GAIA::GVOID OutputChildRelation(
			PLC_FileStructure* plc_filestructure,
			PLC_FileStructure::Node& node,
			GAIA::FSYS::FileBase* pFile,
			GAIA::PRINT::PrintBase& prt,
			GAIA::SIZE depth)
		{
			GPCHR_NULL(plc_filestructure);
			prt << node.name.front_ptr() << "\n";
			if(pFile != GNIL)
			{
				this->OutputDepth(prt, pFile, depth);
				pFile->Write(node.name.front_ptr(), node.name.size() * sizeof(__FileName::_datatype));
				pFile->Write(FILEBREAK, GAIA::ALGO::strlen(FILEBREAK) * sizeof(FILEBREAK[0]));
			}
			PLC_FileStructure::__FileLinkSet::it itlink = node.childs.front_it();
			for(; !itlink.empty(); ++itlink)
			{
				__FileName& filename = *itlink;
				PLC_FileStructure::Node* pChildNode = plc_filestructure->FindNode(filename);
				if(pChildNode != GNIL)
					this->OutputChildRelation(plc_filestructure, *pChildNode, pFile, prt, depth + 1);
			}
		}
		GINL GAIA::GVOID OutputDepth(GAIA::PRINT::PrintBase& prt, GAIA::FSYS::FileBase* pFile, GAIA::SIZE depth)
		{
			for(GAIA::SIZE x = 0; x < depth; ++x)
			{
				prt << "\t";
				if(pFile != GNIL)
					pFile->Write(_T("\t"), sizeof(GAIA::TCH));
			}
		}
	};
};

#endif