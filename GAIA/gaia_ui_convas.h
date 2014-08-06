#ifndef		__GAIA_UI_CONVAS_H__
#define		__GAIA_UI_CONVAS_H__

namespace GAIA
{
	namespace UI
	{
		class Convas : public GAIA::FRAMEWORK::Instance
		{
		public:
			typedef GAIA::MATH::VEC2<GAIA::N32> __PosType;
			typedef __PosType __SizeType;
		public:
			class ConvasDesc
			{
			public:

			};
		public:
			virtual GAIA::BL Create(const ConvasDesc& desc) = 0;
			virtual GAIA::BL Destroy() = 0;
			virtual GAIA::BL SetParent(GAIA::UI::Convas* pParent) = 0;
			virtual GAIA::UI::Convas* GetParent() const = 0;
			virtual GAIA::GVOID Show(GAIA::BL bShow) = 0;
			virtual GAIA::BL IsShow() const = 0;
			virtual GAIA::GVOID Position(const __PosType& pos) = 0;
			virtual const __PosType& Position() const = 0;
			virtual GAIA::GVOID Size(const __SizeType& pos) = 0;
			virtual const __SizeType& Size() const = 0;
			virtual GAIA::GVOID EnableCollision(GAIA::BL bEnable) = 0;
			virtual GAIA::BL IsEnableCollision() const = 0;
		};
	};
};

#endif