#ifndef		__GAIA_STREAM_STREAM_H__
#define		__GAIA_STREAM_STREAM_H__

namespace GAIA
{
	namespace STREAM
	{
		class Stream : public StreamBase
		{
		public:
			GINL Stream(){this->init();}
			GINL ~Stream(){}

			virtual GAIA::GVOID enable_write(GAIA::BL bEnable){m_bEnableWrite = bEnable;}
			virtual GAIA::BL enable_write() const{return m_bEnableWrite;}
			virtual GAIA::GVOID enable_read(GAIA::BL bEnable){m_bEnableRead = bEnable;}
			virtual GAIA::BL enable_read() const{return m_bEnableRead;}

			virtual GINL Stream& operator << (GAIA::BL t);
			virtual GINL Stream& operator << (GAIA::NM t);
			virtual GINL Stream& operator << (GAIA::UM t);
			virtual GINL Stream& operator << (GAIA::N8 t);
			virtual GINL Stream& operator << (GAIA::N16 t);
			virtual GINL Stream& operator << (GAIA::N32 t);
			virtual GINL Stream& operator << (const GAIA::N64& t);
			virtual GINL Stream& operator << (GAIA::U8 t);
			virtual GINL Stream& operator << (GAIA::U16 t);
			virtual GINL Stream& operator << (GAIA::U32 t);
			virtual GINL Stream& operator << (const GAIA::U64& t);
			virtual GINL Stream& operator << (GAIA::F32 t);
			virtual GINL Stream& operator << (const GAIA::F64& t);
			virtual GINL Stream& operator << (const GAIA::WCH& t);
			virtual GINL Stream& operator << (const GAIA::CH* p);
			virtual GINL Stream& operator << (const GAIA::WCH* p);
			virtual GINL Stream& operator << (const GAIA::X128& t);

			virtual GINL Stream& operator >> (GAIA::BL& t);
			virtual GINL Stream& operator >> (GAIA::NM& t);
			virtual GINL Stream& operator >> (GAIA::UM& t);
			virtual GINL Stream& operator >> (GAIA::N8& t);
			virtual GINL Stream& operator >> (GAIA::N16& t);
			virtual GINL Stream& operator >> (GAIA::N32& t);
			virtual GINL Stream& operator >> (GAIA::N64& t);
			virtual GINL Stream& operator >> (GAIA::U8& t);
			virtual GINL Stream& operator >> (GAIA::U16& t);
			virtual GINL Stream& operator >> (GAIA::U32& t);
			virtual GINL Stream& operator >> (GAIA::U64& t);
			virtual GINL Stream& operator >> (GAIA::F32& t);
			virtual GINL Stream& operator >> (GAIA::F64& t);
			virtual GINL Stream& operator >> (GAIA::WCH& t);
			virtual GINL Stream& operator >> (GAIA::CH* p);
			virtual GINL Stream& operator >> (GAIA::WCH* p);
			virtual GINL Stream& operator >> (GAIA::X128& t);

			virtual GINL Stream& operator >> (StreamFormat& pf);
			virtual GINL Stream& operator << (const StreamFormat& pf);

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
