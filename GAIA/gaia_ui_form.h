#ifndef		__GAIA_UI_FORM_H__
#define		__GAIA_UI_FORM_H__

namespace GAIA
{
	namespace UI
	{
		class Form : public virtual GAIA::MVC::View, public virtual GAIA::LAYOUT::Widget2D, public virtual GAIA::COLLISIONER::Bounder
		{
		public:
			typedef GAIA::MATH::VEC3<GAIA::REAL> __PosType;
			typedef GAIA::MATH::VEC3<GAIA::REAL> __SizeType;
			typedef GAIA::MATH::VEC3<GAIA::REAL> __RotateType;
			typedef GAIA::MATH::ARGB<GAIA::U8> __ColorType;
		public:
			class Desc : public virtual GAIA::FWORK::InstanceDesc
			{
			public:
				const GAIA::TCH* pszName;
			};
		public:
			/* Location management. */
			GINL GAIA::BL Position(const __PosType& pos);
			GINL const __PosType& Position() const;
			GINL GAIA::BL Size(const __SizeType& size);
			GINL const __SizeType& Size() const;
			GINL GAIA::BL Rotate(const __RotateType& rotate);
			GINL const __RotateType& Rotate() const;

			/* Link management. */
			GINL GAIA::BL SetParent(GAIA::UI::Form* pParent);
			GINL GAIA::UI::Form* GetParent() const;
			GINL GAIA::UI::Form* GetRoot() const;
			GINL GAIA::BL CollectChild(GAIA::CTN::Vector<GAIA::UI::Form*>& listResult) const;

			/* Msg management. */
			GINL GAIA::GVOID EnableCallbackMsg(GAIA::BL bEnable);
			GINL GAIA::BL IsEnableCallBackMsg() const;

			/* Model management. */
			GINL GAIA::GVOID Active(GAIA::BL bActive);
			GINL GAIA::BL Active() const;
			GINL GAIA::GVOID Focus(GAIA::BL bFocus);
			GINL GAIA::BL Focus() const;
			GINL GAIA::GVOID FocusAble(GAIA::BL bFocusAble);
			GINL GAIA::BL FocusAble() const;
			GINL GAIA::GVOID Capture(GAIA::BL bCapture);
			GINL GAIA::BL Capture() const;
			GINL GAIA::GVOID Modal(GAIA::BL bModal);
			GINL GAIA::BL Modal() const;

			/* Display management. */
			GINL GAIA::BL Show(GAIA::BL bShow);
			GINL GAIA::BL IsShow() const;
			GINL GAIA::BL Color(const __ColorType& cr);
			GINL const __ColorType& Color() const;

			/* Scissor management. */
			GINL GAIA::GVOID EnableScissor(GAIA::BL bEnable);
			GINL GAIA::BL IsEnableScissor() const;
			
		public:
			virtual GAIA::BL Create(const GAIA::UI::Form::Desc& desc);
			virtual GAIA::BL Destroy();
			virtual GAIA::BL IsCreated() const;
			virtual const GAIA::UI::Form::Desc& GetDesc() const;

		private:
		};
	};
};

#endif