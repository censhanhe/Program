#ifndef		__GAIA_UI_RADIOBUTTON_H__
#define		__GAIA_UI_RADIOBUTTON_H__

namespace GAIA
{
	namespace UI
	{
		class RadioButton : public virtual GAIA::UI::Form
		{
		public:
			virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_UI_RADIOBUTTON;}
		};
	};
};

#endif