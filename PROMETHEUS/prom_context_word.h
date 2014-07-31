#ifndef		__PROM_CONTEXT_WORD_H__
#define		__PROM_CONTEXT_WORD_H__

namespace PROM
{
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
			GINL GAIA::GVOID init(){uExistCount = 0;}
		public:
			__WordType strWord;
			GAIA::U32 uExistCount;
		};
		typedef GAIA::CONTAINER::Set<Word> __WordSetType;
	public:
		__WordSetType wordset;
	};
};

#endif