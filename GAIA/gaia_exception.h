#ifndef		__GAIA_EXCEPTION_H__
#define		__GAIA_EXCEPTION_H__

namespace GAIA
{
	namespace EXCEPTION
	{
		/*
		*	Exception base class.
		*/
		class Exception : public GAIA::Base
		{
		public:
			GAIA_ENUM_BEGIN(CODE)
			GAIA_ENUM_END(CODE)
		public:
			GINL Exception(){this->init();}
			GINL ~Exception(){}
			GINL GAIA::GVOID SetCode(CODE code){m_code = code;}
			GINL CODE GetCode() const{return m_code;}
		private:
			GINL GAIA::GVOID init(){m_code = CODE_INVALID;}
		private:
			CODE m_code;
		};

		/*
		*	When the GAIA_AST failed, the exception will occurred.
		*/
		class ExceptionAst : public GAIA::EXCEPTION::Exception
		{
		public:
			ExceptionAst(const GAIA::CH* pszFile, GAIA::N32 nLine){m_pszFile = pszFile; m_nLine = nLine;}
		private:
			const GAIA::CH* m_pszFile;
			GAIA::N32 m_nLine;
		};

		/*
		*	When the GAIA_ASTDEBUG failed, the exception will occurred.
		*/
		class ExceptionAstDebug : public GAIA::EXCEPTION::Exception
		{
		public:
			ExceptionAstDebug(const GAIA::CH* pszFile, GAIA::N32 nLine){m_pszFile = pszFile; m_nLine = nLine;}
		private:
			const GAIA::CH* m_pszFile;
			GAIA::N32 m_nLine;
		};

		/*
		*	When access out of bounder, will cause this exception.
		*/
		class ExceptionOutOfBounder : public GAIA::EXCEPTION::Exception
		{
		public:
		};

		/*
		*	When the memory is not enough, will cause this exception.
		*/
		class ExceptionNotEnoughMem : public GAIA::EXCEPTION::Exception
		{
		public:
		};
	};
};

#endif