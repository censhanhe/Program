#ifndef		__GAIA_UI_DOCUMENT_H__
#define		__GAIA_UI_DOCUMENT_H__

namespace GAIA
{
	namespace UI
	{
		class Document : public virtual GAIA::UI::Form
		{
		public:
			virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_UI_DOCUMENT;}
		};
	};
};

#endif