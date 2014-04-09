#ifndef		__GAIA_FRAMEWORK_HD_H__
#define		__GAIA_FRAMEWORK_HD_H__

namespace GAIA
{
	namespace FRAMEWORK
	{
		class Instance;
		class HD : public GAIA::Base // Handle class.
		{
		public:
			GAIA_ENUM_BEGIN(RIGHT)
				RIGHT_READ			= 0x00000001,
				RIGHT_WRITE			= 0x00000002,
			GAIA_ENUM_END(RIGHT)
		public:
			GINL HD();
			GINL HD(const HD& src); // Auto reference count increase.
			GINL ~HD(); // Auto reference count decrease.
			GINL GAIA::GVOID Invalid();
			GINL GAIA::BL IsInvalid() const;
			GINL GAIA::BL SetRight(UM uRight) const;
			GINL GAIA::U32 GetRight() const;
			GINL GAIA::BL Close() const;
			GINL HD MakeShadow() const;
			GINL GAIA::BL IsShadow() const;
			GINL GAIA::FRAMEWORK::Instance* GetInstance() const;

			GINL const HD& operator = (const HD& src); // Auto reference count increase.
			GINL const BL operator == (const HD& src) const;
			GINL const BL operator != (const HD& src) const;
			GINL const BL operator >= (const HD& src) const;
			GINL const BL operator <= (const HD& src) const;
			GINL const BL operator > (const HD& src) const;
			GINL const BL operator < (const HD& src) const;
		private:
			HD* m_pPrevHD;
			HD* m_pNextHD;
			GAIA::FRAMEWORK::Instance* m_pInstance;
		};
	};
};

#endif
