#ifndef		__GAIA_EXCEPTION_H__
#define		__GAIA_EXCEPTION_H__

namespace GAIA
{
	namespace EXCEPTION
	{
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
	};
};

#endif