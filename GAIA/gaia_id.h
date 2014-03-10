#ifndef		__GAIA_FRAMEWORK_ID_H__
#define		__GAIA_FRAMEWORK_ID_H__

namespace GAIA
{
	namespace FRAMEWORK
	{
		template<GAIA::NM _ElementSize> class ID
		{
		public:
			static const GAIA::NM _elementsize = _ElementSize;
		public:
			GINL ID(){}
			GINL ~ID(){}
			GINL GAIA::GVOID invalid();
			GINL GAIA::BL isinvalid() const;
		private:
			GAIA::U8 m_eles[_ElementSize];
		};
	};
};

#endif
