#ifndef		__GAIA_FRAMEWORK_ID_H__
#define		__GAIA_FRAMEWORK_ID_H__

namespace GAIA
{
	namespace FRAMEWORK
	{
		class ID
		{
		public:
			GINL ID();
			GINL ~ID();
			GINL GAIA::GVOID Invalid();
			GINL GAIA::BL IsInvalid() const;
			GINL GAIA::BL IsStatic() const;
			GINL  const ID& operator = (const ID& src);
			GINL  const GAIA::BL operator == (const ID& src) const;
			GINL  const GAIA::BL operator != (const ID& src) const;
			GINL  const GAIA::BL operator >= (const ID& src) const;
			GINL  const GAIA::BL operator <= (const ID& src) const;
			GINL  const GAIA::BL operator > (const ID& src) const;
			GINL  const GAIA::BL operator < (const ID& src) const;
		private:
			GAIA::U32 m_uIndex0;
			GAIA::U32 m_uIndex1;
			GAIA::U32 m_uIndex2;
			GAIA::U16 m_uGroup;
			GAIA::U16 m_uStaticCheckField;
		};
	};
};

#endif
