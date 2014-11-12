#include	"venus.h"
#include	"venus_gl.h"

namespace VENUS
{
	class VenusFactoryCreateCallBack : public GAIA::FWORK::Factory::CreateCallBack
	{
	public:
		virtual GAIA::FWORK::Instance* Create(GAIA::FWORK::Factory* pFactory, const GAIA::FWORK::ClsID& cid)
		{
			if(cid == CLSID_VENUS_RENDERGL)
				return new VENUS::RenderGL;
			return GNIL;
		}
	};
	static VenusFactoryCreateCallBack s_CallBack;

	GAIA::BL Initialize(GAIA::FWORK::Factory& fac)
	{
		if(!fac.RegistClsID(CLSID_VENUS_RENDERGL))
			return GAIA::False;
		if(!fac.RegistCreateCallBack(&s_CallBack))
			return GAIA::False;
		return GAIA::True;
	}

	GAIA::BL Release(GAIA::FWORK::Factory& fac)
	{
		if(!fac.UnregistClsID(CLSID_VENUS_RENDERGL))
			return GAIA::False;
		if(!fac.UnregistCreateCallBack(&s_CallBack))
			return GAIA::False;
		return GAIA::True;
	}
};