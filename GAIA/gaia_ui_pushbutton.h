#ifndef		__GAIA_UI_PUSHBUTTON_H__
#define		__GAIA_UI_PUSHBUTTON_H__

namespace GAIA
{
	namespace UI
	{
		class PushButton : public virtual GAIA::UI::Form
		{
		public:
			virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_UI_PUSHBUTTON;}
		};
	};
};

#endif