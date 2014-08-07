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
			GINL GAIA::BL AddWidget(LayoutWidget& lw);
			GINL GAIA::BL RemoveWidget(LayoutWidget& lw);
			GINL GAIA::BL RemoveWidageAll();
		private:
			GINL GAIA::GVOID init(){}
		};
	};
};

#endif