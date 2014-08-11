#ifndef		__GAIA_LAYOUT_WIDGET_H__
#define		__GAIA_LAYOUT_WIDGET_H__

namespace GAIA
{
	namespace LAYOUT
	{
		GAIA_ENUM_BEGIN(WIDGET_TYPE)
			WIDGET_TYPE_2D,
			WIDGET_TYPE_3D,
		GAIA_ENUM_END(WIDGET_TYPE)

		class Widget : public virtual GAIA::FRAMEWORK::Instance
		{
		public:
			GINL Widget(){}
			GINL ~Widget(){}
		public:
			virtual WIDGET_TYPE GetWidgetType() const = 0;
		private:
			GINL GAIA::GVOID init(){}
		};
	};
};

#endif