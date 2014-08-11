#ifndef		__GAIA_LAYOUT_WIDGET_3D_H__
#define		__GAIA_LAYOUT_WIDGET_3D_H__

namespace GAIA
{
	namespace LAYOUT
	{
		class Widget3D : public virtual Widget
		{
		public:
			GINL Widget3D(){}
			GINL ~Widget3D(){}
		public:
			virtual WIDGET_TYPE GetWidgetType() const{return WIDGET_TYPE_3D;}
		public:
			virtual GAIA::MATH::AABB<GAIA::REAL> GetWidgetAABB() const = 0;
		private:
			GINL GAIA::GVOID init(){}
		};
	};
};

#endif