#ifndef		__PROM_PIPELINE_FILECOLLECT_H__
#define		__PROM_PIPELINE_FILECOLLECT_H__

namespace PROM
{
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
};

#endif