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
			};

		public:
			virtual GAIA::BL Initialize(const GAIA::RENDER::Render::RenderDesc& desc) = 0;
			virtual GAIA::BL Release() = 0;
			virtual GAIA::BL IsInitialized() const = 0;
			virtual const GAIA::RENDER::Render::RenderDesc& GetDesc() const = 0;

			virtual GAIA::GVOID Flush() = 0;
		};
	};
};

#endif
