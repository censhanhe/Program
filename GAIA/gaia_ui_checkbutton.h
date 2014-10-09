#ifndef		__GAIA_UI_CHECKBUTTON_H__
#define		__GAIA_UI_CHECKBUTTON_H__

namespace GAIA
{
	namespace UI
	{
		class CheckButton : public virtual GAIA::UI::Form
		{
		public:
			virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_UI_CHECKBUTTON;}
		};
	};
};

#endif