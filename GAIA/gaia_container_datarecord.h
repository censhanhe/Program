#ifndef		__GAIA_CONTAINER_DATARECORD_H__
#define		__GAIA_CONTAINER_DATARECORD_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template<typename _SizeType> class DataRecord
		{
		public:
			typedef _SizeType _sizetype;
		public:
			typedef DataRecord<_SizeType> __MyType;
		public:
			GINL DataRecord(){this->init();}
			GINL DataRecord(const DataRecord& src){this->init(); this->operator = (src);}
			GINL ~DataRecord(){}
			GINL GAIA::BL empty() const{return this->size() == 0;}
			GINL _SizeType size() const{return m_size;}
			GINL GAIA::GVOID resize(const _SizeType& size){m_size = size;}
			GINL GAIA::GVOID* front_ptr() const{return m_pFront;}
			GINL GAIA::GVOID front_ptr(GAIA::GVOID* p){m_pFront = p;}
			GINL operator GAIA::GVOID*(){return m_pFront;}
			GINL DataRecord& operator = (const DataRecord& src){m_pFront = src.m_pFront; m_size = src.m_size; return *this;}
			GINL GAIA::BL operator == (const __MyType& src) const{if(m_pFront == src.m_pFront && m_size == src.m_size) return GAIA::True; return GAIA::False;}
			GINL GAIA::BL operator != (const __MyType& src) const{return this->operator == (src);}
			GINL GAIA::BL operator >= (const __MyType& src) const
			{
				if(m_pFront < src.m_pFront)
					return GAIA::False;
				else if(m_pFront > src.m_pFront)
					return GAIA::True;
				else
				{
					if(m_size < src.m_size)
						return GAIA::False;
					else
						return GAIA::True;
				}
			}
			GINL GAIA::BL operator <= (const __MyType& src) const
			{
				if(m_pFront > src.m_pFront)
					return GAIA::False;
				else if(m_pFront < src.m_pFront)
					return GAIA::True;
				else
				{
					if(m_size > src.m_size)
						return GAIA::False;
					else
						return GAIA::True;
				}
			}
			GINL GAIA::BL operator > (const __MyType& src) const{return !(this->operator <= (src));}
			GINL GAIA::BL operator < (const __MyType& src) const{return !(this->operator >= (src));}
		private:
			GINL GAIA::GVOID init(){m_pFront = GNULL; m_size = 0;}
		private:
			GAIA::GVOID* m_pFront;
			_SizeType m_size;
		};
	};
};

#endif