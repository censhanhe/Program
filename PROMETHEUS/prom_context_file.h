#ifndef		__PROM_CONTEXT_FILE_H__
#define		__PROM_CONTEXT_FILE_H__

namespace PROM
{
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
		typedef GAIA::CTN::Vector<File> __FileList;
	public:
		__FileList filelist;
	};
};

#endif