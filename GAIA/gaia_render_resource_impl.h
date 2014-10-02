#ifndef		__GAIA_RENDER_RESOURCE_IMPL_H__
#define		__GAIA_RENDER_RESOURCE_IMPL_H__

namespace GAIA
{
	namespace RENDER
	{
		GINL GAIA::GVOID RenderResource::SetRender(GAIA::RENDER::Render* pRender)
		{
			if(m_pRender != GNIL)
				m_pRender->Release();
			m_pRender = pRender;
			if(m_pRender != GNIL)
				m_pRender->Reference();
		}
		GINL GAIA::RENDER::Render* RenderResource::GetRender() const
		{
			if(m_pRender != GNIL)
				m_pRender->Reference();
			return m_pRender;
		}
	};
};

#endif