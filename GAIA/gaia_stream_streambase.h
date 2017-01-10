#ifndef		__GAIA_STREAM_STREAMBASE_H__
#define		__GAIA_STREAM_STREAMBASE_H__

namespace GAIA
{
	namespace STREAM
	{
		class StreamBase : public GAIA::Entity
		{
		public:
			virtual GAIA::GVOID enable_write(GAIA::BL bEnable) = 0;
			virtual GAIA::BL enable_write() const = 0;
			virtual GAIA::GVOID enable_read(GAIA::BL bEnable) = 0;
			virtual GAIA::BL enable_read() const = 0;

			virtual StreamBase& operator << (GAIA::BL t) = 0;
			virtual StreamBase& operator << (GAIA::NM t) = 0;
			virtual StreamBase& operator << (GAIA::UM t) = 0;
			virtual StreamBase& operator << (GAIA::N8 t) = 0;
			virtual StreamBase& operator << (GAIA::N16 t) = 0;
			virtual StreamBase& operator << (GAIA::N32 t) = 0;
			virtual StreamBase& operator << (const GAIA::N64& t) = 0;
			virtual StreamBase& operator << (GAIA::U8 t) = 0;
			virtual StreamBase& operator << (GAIA::U16 t) = 0;
			virtual StreamBase& operator << (GAIA::U32 t) = 0;
			virtual StreamBase& operator << (const GAIA::U64& t) = 0;
			virtual StreamBase& operator << (GAIA::F32 t) = 0;
			virtual StreamBase& operator << (const GAIA::F64& t) = 0;
			virtual StreamBase& operator << (const GAIA::WCH& t) = 0;
			virtual StreamBase& operator << (const GAIA::CH* p) = 0;
			virtual StreamBase& operator << (const GAIA::WCH* p) = 0;
			virtual StreamBase& operator << (const GAIA::X128& t) = 0;

			virtual StreamBase& operator >> (GAIA::BL& t) = 0;
			virtual StreamBase& operator >> (GAIA::NM& t) = 0;
			virtual StreamBase& operator >> (GAIA::UM& t) = 0;
			virtual StreamBase& operator >> (GAIA::N8& t) = 0;
			virtual StreamBase& operator >> (GAIA::N16& t) = 0;
			virtual StreamBase& operator >> (GAIA::N32& t) = 0;
			virtual StreamBase& operator >> (GAIA::N64& t) = 0;
			virtual StreamBase& operator >> (GAIA::U8& t) = 0;
			virtual StreamBase& operator >> (GAIA::U16& t) = 0;
			virtual StreamBase& operator >> (GAIA::U32& t) = 0;
			virtual StreamBase& operator >> (GAIA::U64& t) = 0;
			virtual StreamBase& operator >> (GAIA::F32& t) = 0;
			virtual StreamBase& operator >> (GAIA::F64& t) = 0;
			virtual StreamBase& operator >> (GAIA::WCH& t) = 0;
			virtual StreamBase& operator >> (GAIA::CH* p) = 0;
			virtual StreamBase& operator >> (GAIA::WCH* p) = 0;
			virtual StreamBase& operator >> (GAIA::X128& t) = 0;

			virtual StreamBase& operator >> (StreamFormat& pf) = 0;
			virtual StreamBase& operator << (const StreamFormat& pf) = 0;

			virtual GAIA::GVOID flush() = 0;
		};
	};
};

#endif