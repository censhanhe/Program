#ifndef		__PROM_CONTEXT_FILECODELINE_H__
#define		__PROM_CONTEXT_FILECODELINE_H__

namespace PROM
{
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
};

#endif