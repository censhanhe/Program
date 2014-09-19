#ifndef		__PROM_PIPELINE_LINESTAT_H__
#define		__PROM_PIPELINE_LINESTAT_H__

namespace PROM
{
	class PL_LineStat : public Pipeline
	{
	public:
		GINL PL_LineStat(){}
		GINL ~PL_LineStat(){}
		virtual const GAIA::TCH* GetName() const{return _T("Prom:PL_LineStat");}
		virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size, GAIA::PRINT::PrintBase& prt, __ErrorListType& errs)
		{
			/* Parameter check up. */
			GPCHR_NULL_RET(ppPLC, GNIL);
			GPCHR_ZERO_RET(size, GNIL);

			DWARFS_MISC::TextLine::__LineType strLine;
			FileLineInfo fli;
			PLC_Empty* pRet = GNIL;
			PLC_CommandParam* plc_commandparam = GNIL;
			PLC_FileCodeLine* plc_codeline = GNIL;
			plc_commandparam = static_cast<PLC_CommandParam*>(this->GetPLCByName(ppPLC, size, _T("Prom:PLC_CommandParam")));
			if(plc_commandparam == GNIL)
				goto FUNCTION_END;
			plc_codeline = static_cast<PLC_FileCodeLine*>(this->GetPLCByName(ppPLC, size, _T("Prom:PLC_FileCodeLine")));
			if(plc_codeline == GNIL)
				goto FUNCTION_END;

			/* Initialize result pipeline context. */
			pRet = new PLC_Empty;

			/* Execute. */
			GAIA::BL bLineStat = GAIA::False;
			for(GAIA::SIZE x = 0; x < plc_commandparam->cmdparam.cmd_size(); ++x)
			{
				const GAIA::TCH* pszCmd = plc_commandparam->cmdparam.cmd(x);
				if(GAIA::ALGO::stremp(pszCmd))
					continue;
				if(GAIA::ALGO::strcmp(pszCmd, _T("-linestat")) == 0)
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
						if(GAIA::ALGO::strcnts(strLine.front_ptr(), _T("\r\n\t ")) == strLine.size())
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
			if(plc_commandparam != GNIL)
				plc_commandparam->Release();
			if(plc_codeline != GNIL)
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
};

#endif