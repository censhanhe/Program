#ifndef		__GAIA_UI_PAINTER_H__
#define		__GAIA_UI_PAINTER_H__

namespace GAIA
{
	namespace UI
	{
		class Painter : public virtual GAIA::FWORK::Instance
		{
		public:
			class PainterDesc : public virtual GAIA::FWORK::InstanceDesc
			{
			public:
				virtual GAIA::GVOID reset()
				{
				}
				virtual GAIA::BL check() const
				{
					return GAIA::True;
				}

			};

		public:
			GINL Painter(){this->init();}
			GINL ~Painter(){}

			GINL GAIA::BL Create(const GAIA::UI::Painter::PainterDesc& desc)
			{
				if(!desc.check())
					return GAIA::False;
				return GAIA::True;
			}
			GINL GAIA::GVOID Destroy()
			{
			}
			GINL const GAIA::UI::Painter::PainterDesc& GetDesc() const{return m_desc;}

			GINL GAIA::BL Draw(GAIA::UI::Form* pForm)
			{
				return GAIA::True;
			}

		private:
			GINL GAIA::GVOID init(){}

		private:
			GAIA::UI::Painter::PainterDesc m_desc;
		};
	};
};

#endif