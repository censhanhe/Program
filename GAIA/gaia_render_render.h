#ifndef		__GAIA_RENDER_RENDER_H__
#define		__GAIA_RENDER_RENDER_H__

namespace GAIA
{
	namespace RENDER
	{
		class Render : public virtual GAIA::FRAMEWORK::Instance
		{
		public:
			class RenderDesc : public GAIA::Base
			{
			public:
			};

		public:
			GINL Render(){}
			GINL ~Render() = 0;

			virtual GAIA::BL Initialize(const RenderDesc& desc) = 0;
			virtual GAIA::BL Release() = 0;
			virtual GAIA::BL IsInitialized() const = 0;
			virtual const RenderDesc& GetDesc() const = 0;

			virtual GAIA::GVOID Flush() = 0;
		};
	};
};

#endif
