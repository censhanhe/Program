#ifndef		__GAIA_PAINTER_H__
#define		__GAIA_PAINTER_H__

namespace GAIA
{
	namespace PAINTER
	{
		class Painter : public GAIA::FRAMEWORK::Instance
		{
		public:
			class PainterDesc
			{
			public:
				GAIA::UI::Convas* pConvas;
			};
		public:
			/* Base. */
			virtual GAIA::BL Create(const PainterDesc& desc) = 0;
			virtual GAIA::BL Destroy() = 0;
			virtual const PainterDesc& GetDesc() const = 0;

			/* Target. */

			/* Font. */

			/* Rect. */

			/* Line */

			/* Texture. */
		};
	};
};

#endif