#ifndef 	__GAIA_OBJECT_MEMIO_H__
#define 	__GAIA_OBJECT_MEMIO_H__

namespace GAIA
{
	namespace OBJECT
	{
		class MemIO : public IO
		{
		public:
			GINL MemIO(){}
			GINL ~MemIO(){}
			virtual GAIA::BL Open(const GAIA::GCH* pszIOName, GAIA::UM uTypeMask)
			{
				return GAIA::True;
			}
			virtual GAIA::BL Close()
			{
				return GAIA::True;
			}
			virtual GAIA::BL IsOpen() const
			{
				return GAIA::False;
			}
			virtual GAIA::UM GetType() const
			{
				return 0;
			}
			virtual GAIA::BL Read(GAIA::GVOID* pData, GAIA::UM uSize)
			{
				return GAIA::True;
			}
			virtual GAIA::BL Write(const GAIA::GVOID* pData, GAIA::UM uSize)
			{
				return GAIA::False;
			}
		private:
		};
	};
};

#endif
