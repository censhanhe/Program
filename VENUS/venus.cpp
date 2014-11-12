#include "venus.h"
#include "venus_render_gl.h"

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
		if(!fac.BeginRegistClsID())
			return GAIA::False;
		if(!fac.RegistClsID(CLSID_VENUS_RENDERGL))
		{
			fac.EndRegistClsID();
			return GAIA::False;
		}
		if(!fac.RegistCreateCallBack(&s_CallBack))
		{
			fac.EndRegistClsID();
			return GAIA::False;
		}
		fac.EndRegistClsID();
		return GAIA::True;
	}

	GAIA::BL Release(GAIA::FWORK::Factory& fac)
	{
		if(!fac.BeginRegistClsID())
			return GAIA::False;
		if(!fac.UnregistClsID(CLSID_VENUS_RENDERGL))
		{
			fac.EndRegistClsID();
			return GAIA::False;
		}
		if(!fac.UnregistCreateCallBack(&s_CallBack))
		{
			fac.EndRegistClsID();
			return GAIA::False;
		}
		fac.EndRegistClsID();
		return GAIA::True;
	}
};