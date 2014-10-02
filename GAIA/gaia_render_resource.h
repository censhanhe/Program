#ifndef		__GAIA_RENDER_RESOURCE_H__
#define		__GAIA_RENDER_RESOURCE_H__

namespace GAIA
{
	namespace RENDER
	{
		class RenderResource : public virtual GAIA::FWORK::Instance
		{
		public:
			GINL RenderResource(){this->init();}
			GINL ~RenderResource(){this->SetRender(GNIL);}

			GINL GAIA::GVOID SetRender(GAIA::RENDER::Render* pRender);
			GINL GAIA::RENDER::Render* GetRender() const;

		private:
			GINL GAIA::GVOID init(){m_pRender = GNIL;}

		private:
			GAIA::RENDER::Render* m_pRender;
		};
	};
};

#endif