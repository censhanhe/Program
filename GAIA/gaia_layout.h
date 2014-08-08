#ifndef		__GAIA_LAYOUT_H__
#define		__GAIA_LAYOUT_H__

namespace GAIA
{
	namespace LAYOUT
	{
		class Layout : public virtual GAIA::FRAMEWORK::Instance
		{
		public:
			GINL Layout(){}
			GINL ~Layout(){}
			GINL GAIA::BL AddWidget(GAIA::LAYOUT::Widget& lw);
			GINL GAIA::BL RemoveWidget(GAIA::LAYOUT::Widget& lw);
			GINL GAIA::BL RemoveWidgetAll();
			GINL GAIA::BL CollectWidget(GAIA::CONTAINER::Vector<GAIA::LAYOUT::Widget*>& listResult) const;
		public:
			virtual GAIA::BL Update() = 0; // If there are some widget been reposition or resize, return GAIA::True, or will return GAIA::False.
		private:
			GINL GAIA::GVOID init(){}
		private:
		};
	};
};

#endif