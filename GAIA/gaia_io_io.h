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
				IO_TYPE_READ = 1 << 0,
				IO_TYPE_WRITE = 1 << 1,
			GAIA_ENUM_END(IO_TYPE)
		public:
			virtual GAIA::BL Open(const GAIA::TCH* pszIOName, GAIA::UM uTypeMask) = 0; // uTypeMask is the IO_TYPE's mask.
			virtual GAIA::BL Close() = 0;
			virtual GAIA::BL IsOpen() const = 0;
			virtual GAIA::UM GetType() const = 0;
			virtual GAIA::BL Read(GAIA::GVOID* pData, GAIA::U32 uSize) = 0;
			virtual GAIA::BL Write(const GAIA::GVOID* pData, GAIA::U32 uSize) = 0;
		private:
		};
	};
};

#endif
