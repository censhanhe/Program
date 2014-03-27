#ifndef 	__GAIA_DATAPHASE_H__
#define 	__GAIA_DATAPHASE_H__

namespace GAIA
{
	namespace DATAPHASE
	{
		class CRC8
		{
		public:
			GINL CRC8(){m_crc = 0;}
			GINL GAIA::U8 Result() const{return m_crc;}
			GINL GAIA::GVOID Build(const GAIA::GVOID* p, GAIA::NM size);
		private:
			GAIA::U8 m_crc;
		};
		class CRC16
		{
		public:
			GINL CRC16(){m_crc = 0;}
			GINL GAIA::U16 Result() const{return m_crc;}
			GINL GAIA::GVOID Build(const GAIA::GVOID* p, GAIA::NM size);
		private:
			GAIA::U16 m_crc;
		};
		class CRC32
		{
		public:
			GINL CRC32(){m_crc = 0;}
			GINL GAIA::U32 Result() const{return m_crc;}
			GINL GAIA::GVOID Build(const GAIA::GVOID* p, GAIA::NM size);
		private:
			GAIA::U32 m_crc;
		};
	};
};

#endif
