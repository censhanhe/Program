#ifndef 	__GAIA_OBJECT_MEMIO_H__
#define 	__GAIA_OBJECT_MEMIO_H__

namespace GAIA
{
	namespace OBJECT
	{
		class MemIO : public IO
		{
		public:
			GINL MemIO();
			GINL ~MemIO();
			virtual GAIA::BL Open(const GAIA::GCH* pszIOName);
			virtual GAIA::BL Close();
			virtual GAIA::BL IsOpen() const;
			virtual GAIA::BL Read(GAIA::GVOID* pData, GAIA::UM uSize);
			virtual GAIA::BL Write(const GAIA::GVOID* pData, GAIA::UM uSize);
		private:
		};
	};
};

#endif
