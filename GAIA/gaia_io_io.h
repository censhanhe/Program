#ifndef 	__GAIA_IO_IO_H__
#define 	__GAIA_IO_IO_H__

namespace GAIA
{
	namespace IO
	{
		class IO : public GAIA::FRAMEWORK::Instance
		{
		public:
			GAIA_ENUM_BEGIN(IO_TYPE)
				IO_TYPE_READ,
				IO_TYPE_WRITE,
			GAIA_ENUM_END(IO_TYPE)
		public:
			virtual GAIA::BL Open(const GAIA::GCH* pszIOName, GAIA::UM uTypeMask) = 0; // uTypeMask is the IO_TYPE's mask.
			virtual GAIA::BL Close() = 0;
			virtual GAIA::BL IsOpen() const = 0;
			virtual GAIA::UM GetType() const = 0;
			virtual GAIA::BL Read(GAIA::GVOID* pData, GAIA::UM uSize) = 0;
			virtual GAIA::BL Write(const GAIA::GVOID* pData, GAIA::UM uSize) = 0;
		private:
		};
	};
};

#endif
