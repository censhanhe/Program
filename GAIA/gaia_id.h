#ifndef		__GAIA_FRAMEWORK_ID_H__
#define		__GAIA_FRAMEWORK_ID_H__

namespace GAIA
{
	namespace FRAMEWORK
	{
		template<GAIA::U32 _ElementSize> class ID : public GAIA::Base
		{
		public:
			static const GAIA::U32 _elementsize = _ElementSize;
		public:
			GINL ID(){}
			GINL ~ID(){}
			GINL GAIA::GVOID Invalid();
			GINL GAIA::BL IsInvalid() const;
		private:
			GAIA::U8 m_eles[_ElementSize];
		};
	};
};

#endif
