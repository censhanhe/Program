#ifndef		__GAIA_UI_LABEL_H__
#define		__GAIA_UI_LABEL_H__

namespace GAIA
{
	namespace UI
	{
		class Label : public virtual GAIA::UI::Form
		{
		public:
			virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_UI_LABEL;}
		};
	};
};

#endif