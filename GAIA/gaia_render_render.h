#ifndef		__GAIA_RENDER_RENDER_H__
#define		__GAIA_RENDER_RENDER_H__

namespace GAIA
{
	namespace RENDER
	{
		class Render : public virtual GAIA::FWORK::Instance
		{
		public:
			typedef GAIA::RENDER::Render __MyType;

		public:
			class RenderDesc : public virtual GAIA::Base
			{
			public:
				GINL RenderDesc(){this->reset();}
			public:
				virtual GAIA::GVOID reset(){pCanvas = GNIL;}
				virtual GAIA::BL check() const
				{
					if(pCanvas == GNIL)
						return GAIA::False;
					if(!pCanvas->IsCreated())
						return GAIA::False;
					return GAIA::True;
				}
			public:
				GAIA::UI::Canvas* pCanvas;
			};

		public:
			virtual GAIA::BL Create(const GAIA::RENDER::Render::RenderDesc& desc) = 0;
			virtual GAIA::BL Destroy() = 0;
			virtual GAIA::BL IsCreated() const = 0;
			virtual const GAIA::RENDER::Render::RenderDesc& GetDesc() const = 0;

			virtual GAIA::GVOID Flush() = 0;
		};
	};
};

#endif
