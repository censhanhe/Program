#ifndef 	__GAIA_OBJECT_IO_H__
#define 	__GAIA_OBJECT_IO_H__

namespace GAIA
{
	namespace OBJECT
	{
		class IO : public GAIA::FRAMEWORK::Instance
		{
		public:
			virtual GAIA::BL Open(const GAIA::GCH* pszIOName) = 0;
			virtual GAIA::BL Close() = 0;
			virtual GAIA::BL IsOpen() const = 0;
			virtual GAIA::BL Read(GAIA::GVOID* pData, GAIA::UM uSize) = 0;
			virtual GAIA::BL Write(const GAIA::GVOID* pData, GAIA::UM uSize) = 0;
		private:
		};
	};
};

#endif
