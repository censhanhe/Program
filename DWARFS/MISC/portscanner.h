#ifndef		__DWARFS_MISC_PORTSCANNER_H__
#define		__DWARFS_MISC_PORTSCANNER_H__

namespace DWARFS_MISC
{
	class PortScanner
	{
	public:
		GINL PortScanner(){}
		GINL ~PortScanner(){}

		GINL GAIA::BL AddIPSection(const GAIA::NETWORK::IP& from, const GAIA::NETWORK::IP& to);
		GINL GAIA::BL DeleteIPSection(const GAIA::NETWORK::IP& from, const GAIA::NETWORK::IP& to);
		GINL GAIA::GVOID DeleteIPSecondAll();
		GINL GAIA::SIZE GetIPSectionCount() const;
		GINL GAIA::SIZE GetIPSection(GAIA::NETWORK::IP& from, GAIA::NETWORK::IP& to) const;

		GINL GAIA::BL AddPortSection(GAIA::U16 from, GAIA::U16 to);
		GINL GAIA::BL DeletePortSection(GAIA::U16 from, GAIA::U16 to);
		GINL GAIA::BL DeletePortSectionAll();
		GINL GAIA::SIZE GetPortSectionCount() const;
		GINL GAIA::SIZE GetPortSection(GAIA::U16& from, GAIA::U16& to) const;

	private:
	};
};

#endif