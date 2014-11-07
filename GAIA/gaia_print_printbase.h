#ifndef		__GAIA_PRINT_PRINTBASE_H__
#define		__GAIA_PRINT_PRINTBASE_H__

namespace GAIA
{
	namespace PRINT
	{
		class PrintBase : public GAIA::Entity
		{
		public:
			virtual GAIA::GVOID enable_write(GAIA::BL bEnable) = 0;
			virtual GAIA::BL enable_write() const = 0;
			virtual GAIA::GVOID enable_read(GAIA::BL bEnable) = 0;
			virtual GAIA::BL enable_read() const = 0;

			virtual PrintBase& operator << (GAIA::BL t) = 0;
			virtual PrintBase& operator << (GAIA::NM t) = 0;
			virtual PrintBase& operator << (GAIA::UM t) = 0;
			virtual PrintBase& operator << (GAIA::N8 t) = 0;
			virtual PrintBase& operator << (GAIA::N16 t) = 0;
			virtual PrintBase& operator << (GAIA::N32 t) = 0;
			virtual PrintBase& operator << (const GAIA::N64& t) = 0;
			virtual PrintBase& operator << (GAIA::U8 t) = 0;
			virtual PrintBase& operator << (GAIA::U16 t) = 0;
			virtual PrintBase& operator << (GAIA::U32 t) = 0;
			virtual PrintBase& operator << (const GAIA::U64& t) = 0;
			virtual PrintBase& operator << (GAIA::F32 t) = 0;
			virtual PrintBase& operator << (const GAIA::F64& t) = 0;
			virtual PrintBase& operator << (const GAIA::WCH& t) = 0;
			virtual PrintBase& operator << (const GAIA::CH* p) = 0;
			virtual PrintBase& operator << (const GAIA::WCH* p) = 0;
			virtual PrintBase& operator << (const GAIA::X128& t) = 0;

			virtual PrintBase& operator >> (GAIA::BL& t) = 0;
			virtual PrintBase& operator >> (GAIA::NM& t) = 0;
			virtual PrintBase& operator >> (GAIA::UM& t) = 0;
			virtual PrintBase& operator >> (GAIA::N8& t) = 0;
			virtual PrintBase& operator >> (GAIA::N16& t) = 0;
			virtual PrintBase& operator >> (GAIA::N32& t) = 0;
			virtual PrintBase& operator >> (GAIA::N64& t) = 0;
			virtual PrintBase& operator >> (GAIA::U8& t) = 0;
			virtual PrintBase& operator >> (GAIA::U16& t) = 0;
			virtual PrintBase& operator >> (GAIA::U32& t) = 0;
			virtual PrintBase& operator >> (GAIA::U64& t) = 0;
			virtual PrintBase& operator >> (GAIA::F32& t) = 0;
			virtual PrintBase& operator >> (GAIA::F64& t) = 0;
			virtual PrintBase& operator >> (GAIA::WCH& t) = 0;
			virtual PrintBase& operator >> (GAIA::CH* p) = 0;
			virtual PrintBase& operator >> (GAIA::WCH* p) = 0;
			virtual PrintBase& operator >> (GAIA::X128& t) = 0;

			virtual PrintBase& operator >> (PrintFormat& pf) = 0;
			virtual PrintBase& operator << (const PrintFormat& pf) = 0;

			virtual GAIA::GVOID flush() = 0;
		};
	};
};

#endif