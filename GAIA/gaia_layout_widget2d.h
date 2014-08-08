#ifndef		__GAIA_LAYOUT_WIDGET_2D_H__
#define		__GAIA_LAYOUT_WIDGET_2D_H__

namespace GAIA
{
	namespace LAYOUT
	{
		class Widget2D : public virtual Widget
		{
		public:
			GINL Widget2D(){}
			GINL ~Widget2D(){}
		public:
			virtual WIDGET_TYPE GetType() const{return WIDGET_TYPE_2D;}
		public:
			virtual GAIA::MATH::AABR<GAIA::REAL> GetAABR() const = 0;
			virtual GAIA::BL SetAABR(const GAIA::MATH::AABR<GAIA::REAL>& aabr) = 0;
		private:
			GINL GAIA::GVOID init(){}
		};
	};
};

#endif