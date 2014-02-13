#ifndef		__GAIA_CONTAINER_PAIR_H__
#define		__GAIA_CONTAINER_PAIR_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template<typename _FrontDataType, typename _BackDataType> class Pair
		{
		public:
			typedef _FrontDataType _frontdatatype;
			typedef _BackDataType _backdatatype;
		public:
			typedef Pair<_FrontDataType, _BackDataType> __MyType;
		public:
			GINL Pair(){}
			GINL Pair(const _FrontDataType& front, const _BackDataType& back){m_front = front; m_back = back;}
			GINL Pair(const Pair<_FrontDataType, _BackDataType>& src){this->operator = (src);}
			GINL ~Pair(){}
			GINL GAIA::GVOID front(const _FrontDataType& front){m_front = front;}
			GINL GAIA::GVOID back(const _BackDataType& back){m_back = back;}
			GINL GAIA::GVOID frontback(const _FrontDataType& front, const _BackDataType& back){m_front = front; m_back = back;}
			GINL _FrontDataType& front(){return m_front;}
			GINL const _FrontDataType& front() const{return m_front;}
			GINL _BackDataType& back(){return m_back;}
			GINL const _BackDataType& back() const{return m_back;}
			GINL __MyType& operator = (const __MyType& src){m_front = src.m_front; m_back = src.m_back; return *this;}
			GINL GAIA::BL operator == (const __MyType& src) const{if(m_front == src.m_front && m_back == src.m_back) return GAIA::True; return GAIA::False;}
			GINL GAIA::BL operator != (const __MyType& src) const{return !(this->operator == (src));}
			GINL GAIA::BL operator >= (const __MyType& src) const
			{
				if(m_front > src.m_front)
					return GAIA::True;
				else if(m_front < src.m_front)
					return GAIA::False;
				else
				{
					if(m_back > src.m_back)
						return GAIA::True;
					else if(m_back < src.m_back)
						return GAIA::False;
					else
						return GAIA::True;
				}
			}
			GINL GAIA::BL operator <= (const __MyType& src) const
			{
				if(m_front < src.m_front)
					return GAIA::True;
				else if(m_front > src.m_front)
					return GAIA::False;
				else
				{
					if(m_back < src.m_back)
						return GAIA::True;
					else if(m_back > src.m_back)
						return GAIA::False;
					else
						return GAIA::True;
				}
			}
			GINL GAIA::BL operator > (const __MyType& src) const{return !(this->operator <= (src));}
			GINL GAIA::BL operator < (const __MyType& src) const{return !(this->operator >= (src));}
		private:
			_FrontDataType m_front;
			_BackDataType m_back;
		};
	};
};

#endif