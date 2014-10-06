#ifndef		__GAIA_FRAMEWORK_INSTANCE_HD_H__
#define		__GAIA_FRAMEWORK_INSTANCE_HD_H__

namespace GAIA
{
	namespace FWORK
	{
		class InstanceHD : public GAIA::Entity // Handle class.
		{
		public:
			GAIA_ENUM_BEGIN(RIGHT)
				RIGHT_READ = 1 << 0,
				RIGHT_WRITE	= 1 << 1,
			GAIA_ENUM_END(RIGHT)
		public:
			GINL InstanceHD();
			GINL InstanceHD(const InstanceHD& src); // Auto reference count increase.
			GINL ~InstanceHD(); // Auto reference count decrease.
			GINL GAIA::GVOID Invalid();
			GINL GAIA::BL IsInvalid() const;
			GINL GAIA::BL SetRight(UM uRight) const;
			GINL GAIA::U32 GetRight() const;
			GINL GAIA::BL Close() const;
			GINL InstanceHD MakeShadow() const;
			GINL GAIA::BL IsShadow() const;
			GINL GAIA::FWORK::Instance* GetInstance() const;

			GINL const InstanceHD& operator = (const InstanceHD& src); // Auto reference count increase.
			GINL const BL operator == (const InstanceHD& src) const;
			GINL const BL operator != (const InstanceHD& src) const;
			GINL const BL operator >= (const InstanceHD& src) const;
			GINL const BL operator <= (const InstanceHD& src) const;
			GINL const BL operator > (const InstanceHD& src) const;
			GINL const BL operator < (const InstanceHD& src) const;
		private:
			InstanceHD* m_pPrevHD;
			InstanceHD* m_pNextHD;
			GAIA::FWORK::Instance* m_pInstance;
		};
	};
};

#endif
