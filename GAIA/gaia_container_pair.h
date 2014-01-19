#ifndef		__GAIA_CONTAINER_PAIR_H__
#define		__GAIA_CONTAINER_PAIR_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template <typename _DataTypeFront, typename _DataTypeBack> class Pair
		{
		public:
			typedef _DataTypeFront _datatypefront;
			typedef _DataTypeBack _datatypeback;
		public:
			typedef Pair<_DataTypeFront, _datatypeback> __MyType;
		public:
			GINL Pair(){}
			GINL Pair(const _DataTypeFront& front, const _DataTypeBack& back){m_front = front; m_back = back;}
			GINL Pair(const Pair<_DataTypeFront, _DataTypeBack>& src){this->operator = (src);}
			GINL ~Pair(){}
			GINL GAIA::GVOID front(const _DataTypeFront& front){m_front = front;}
			GINL GAIA::GVOID back(const _DataTypeBack& back){m_back = back;}
			GINL GAIA::GVOID frontback(const _DataTypeFront& front, const _DataTypeBack& back){m_front = front; m_back = back;}
			GINL _DataTypeFront& front(){return m_front;}
			GINL const _DataTypeFront& front() const{return m_front;}
			GINL _DataTypeBack& back(){return m_back;}
			GINL const _DataTypeBack& back() const{return m_back;}
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
			_DataTypeFront m_front;
			_DataTypeBack m_back;
		};
	};
};

#endif