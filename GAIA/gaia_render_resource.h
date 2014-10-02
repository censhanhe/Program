#ifndef		__GAIA_RENDER_RESOURCE_H__
#define		__GAIA_RENDER_RESOURCE_H__

namespace GAIA
{
	namespace RENDER
	{
		class Resource : public virtual GAIA::FWORK::Instance
		{
		public:
			GINL Resource(){this->init();}
			GINL ~Resource(){}

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