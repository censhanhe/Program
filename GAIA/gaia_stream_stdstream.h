#ifndef		__GAIA_STREAM_STREAM_H__
#define		__GAIA_STREAM_STREAM_H__

namespace GAIA
{
	namespace STREAM
	{
		class STDStream : public StreamBase
		{
		public:
			GINL STDStream(){this->init();}
			GINL ~STDStream(){}

			virtual GAIA::GVOID enable_write(GAIA::BL bEnable){m_bEnableWrite = bEnable;}
			virtual GAIA::BL enable_write() const{return m_bEnableWrite;}
			virtual GAIA::GVOID enable_read(GAIA::BL bEnable){m_bEnableRead = bEnable;}
			virtual GAIA::BL enable_read() const{return m_bEnableRead;}

			virtual GINL STDStream& operator << (GAIA::BL t);
			virtual GINL STDStream& operator << (GAIA::NM t);
			virtual GINL STDStream& operator << (GAIA::UM t);
			virtual GINL STDStream& operator << (GAIA::N8 t);
			virtual GINL STDStream& operator << (GAIA::N16 t);
			virtual GINL STDStream& operator << (GAIA::N32 t);
			virtual GINL STDStream& operator << (const GAIA::N64& t);
			virtual GINL STDStream& operator << (GAIA::U8 t);
			virtual GINL STDStream& operator << (GAIA::U16 t);
			virtual GINL STDStream& operator << (GAIA::U32 t);
			virtual GINL STDStream& operator << (const GAIA::U64& t);
			virtual GINL STDStream& operator << (GAIA::F32 t);
			virtual GINL STDStream& operator << (const GAIA::F64& t);
			virtual GINL STDStream& operator << (const GAIA::WCH& t);
			virtual GINL STDStream& operator << (const GAIA::CH* p);
			virtual GINL STDStream& operator << (const GAIA::WCH* p);
			virtual GINL STDStream& operator << (const GAIA::X128& t);

			virtual GINL STDStream& operator >> (GAIA::BL& t);
			virtual GINL STDStream& operator >> (GAIA::NM& t);
			virtual GINL STDStream& operator >> (GAIA::UM& t);
			virtual GINL STDStream& operator >> (GAIA::N8& t);
			virtual GINL STDStream& operator >> (GAIA::N16& t);
			virtual GINL STDStream& operator >> (GAIA::N32& t);
			virtual GINL STDStream& operator >> (GAIA::N64& t);
			virtual GINL STDStream& operator >> (GAIA::U8& t);
			virtual GINL STDStream& operator >> (GAIA::U16& t);
			virtual GINL STDStream& operator >> (GAIA::U32& t);
			virtual GINL STDStream& operator >> (GAIA::U64& t);
			virtual GINL STDStream& operator >> (GAIA::F32& t);
			virtual GINL STDStream& operator >> (GAIA::F64& t);
			virtual GINL STDStream& operator >> (GAIA::WCH& t);
			virtual GINL STDStream& operator >> (GAIA::CH* p);
			virtual GINL STDStream& operator >> (GAIA::WCH* p);
			virtual GINL STDStream& operator >> (GAIA::X128& t);

			virtual GINL STDStream& operator >> (StreamFormat& pf);
			virtual GINL STDStream& operator << (const StreamFormat& pf);

			virtual GINL GAIA::GVOID flush();

		private:
			GINL GAIA::GVOID init()
			{
				m_pf.reset();
				m_bEnableWrite = GAIA::True;
				m_bEnableRead = GAIA::True;
			}

		private:
			StreamFormat m_pf;
			GAIA::U8 m_bEnableWrite : 1;
			GAIA::U8 m_bEnableRead : 1;
		};
	};
};

#include "gaia_stream_stdstream_indp.h"

#endif
