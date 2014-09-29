#ifndef		__GAIA_RENDER_RENDER_H__
#define		__GAIA_RENDER_RENDER_H__

namespace GAIA
{
	namespace RENDER
	{
		GAIA_ENUM_BEGIN(RENDER_STATEWORD)
			RENDER_STATEWORD_NONE,
			RENDER_STATEWORD_ON,
			RENDER_STATEWORD_OFF,
			RENDER_STATEWORD_LOWEST,
			RENDER_STATEWORD_LOWER,
			RENDER_STATEWORD_LOW,
			RENDER_STATEWORD_MID,
			RENDER_STATEWORD_HIGH,
			RENDER_STATEWORD_HIGHER,
			RENDER_STATEWORD_HIGHEST,
		GAIA_ENUM_END(RENDER_STATEWORD)
		static const GAIA::CH* RENDER_STATEWORD_STRING[] = 
		{
			"invalid",	// RENDER_STATEWORD_INVALID,
			"none",		// RENDER_STATEWORD_NONE
			"on",		// RENDER_STATEWORD_ON
			"off",		// RENDER_STATEWORD_OFF
			"lowest",	// RENDER_STATEWORD_LOWEST
			"lower",	// RENDER_STATEWORD_LOWER
			"low",		// RENDER_STATEWORD_LOW
			"mid",		// RENDER_STATEWORD_MID
			"high",		// RENDER_STATEWORD_HIGH
			"higher",	// RENDER_STATEWORD_HIGHER
			"highest",	// RENDER_STATEWORD_HIGHEST
		};

		class Render : public virtual GAIA::FWORK::Instance
		{
		public:
			typedef GAIA::RENDER::Render __MyType;

		public:
			class RenderDesc : public virtual GAIA::FWORK::InstanceDesc
			{
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
