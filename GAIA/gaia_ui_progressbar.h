#ifndef		__GAIA_UI_PROGRESSBAR_H__
#define		__GAIA_UI_PROGRESSBAR_H__

namespace GAIA
{
	namespace UI
	{
		class ProgressBar : public virtual GAIA::UI::Form
		{
		public:
			virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_UI_PROGRESSBAR;}
		};
	};
};

#endif