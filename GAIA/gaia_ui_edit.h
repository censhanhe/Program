#ifndef		__GAIA_UI_EDIT_H__
#define		__GAIA_UI_EDIT_H__

namespace GAIA
{
	namespace UI
	{
		class Edit : public virtual GAIA::UI::Form
		{
		public:
			virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_UI_EDIT;}
		};
	};
};

#endif