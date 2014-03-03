#ifndef		__GAIA_OBJECT_SCREEN_IO_H__
#define		__GAIA_OBJECT_SCREEN_IO_H__

namespace GAIA
{
	namespace OBJECT
	{
		class ScreenIO : public IO
		{
		public:
			GINL ScreenIO();
			GINL ~ScreenIO();
			virtual GAIA::BL Open(const GAIA::GCH* pszIOName, GAIA::UM uTypeMask);
			virtual GAIA::BL Close();
			virtual GAIA::BL IsOpen() const;	
			virtual GAIA::UM GetType() const;
			virtual GAIA::BL Read(GAIA::GVOID* pData, GAIA::UM uSize);
			virtual GAIA::BL Write(const GAIA::GVOID* pData, GAIA::UM uSize);
		private:
		};
	};
};

#endif
