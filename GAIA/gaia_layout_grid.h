#ifndef		__GAIA_LAYOUT_GRID_H__
#define		__GAIA_LAYOUT_GRID_H__

namespace GAIA
{
	namespace LAYOUT
	{
		class LayoutGrid : public virtual GAIA::LAYOUT::Layout
		{
		public:
			GINL LayoutGrid(){}
			GINL ~LayoutGrid(){}
			GINL GAIA::GVOID SetMaxColumnCount(const GAIA::SIZE& c);
			GINL const GAIA::SIZE& GetMaxColumnCount() const;
			GINL GAIA::GVOID SetMaxRowCount(const GAIA::SIZE& c);
			GINL const GAIA::SIZE& GetMaxRowCount() const;
			GINL GAIA::GVOID SetHorizonSpacingSize(const GAIA::REAL& s);
			GINL const GAIA::REAL& GetHorizonSpacingSize() const;
			GINL GAIA::GVOID SetVerticalSpacingSize(const GAIA::REAL& s);
			GINL const GAIA::REAL& GetVerticalSpacingSize() const;
		public:
			virtual GAIA::BL UpdateLayout()
			{
				return GAIA::False;
			}
		private:
			GINL GAIA::GVOID init(){}
		};
	};
};

#endif