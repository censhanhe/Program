#ifndef		__GAIA_CONTAINER_BASICBUFFER_H__
#define		__GAIA_CONTAINER_BASICBUFFER_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template<typename _SizeType, typename _SizeIncreaserType> class BasicBuffer
		{
		public:
			typedef _SizeType _sizetype;
			typedef _SizeIncreaserType _sizeincreasertype;
		public:
			typedef BasicBuffer<_SizeType, _SizeIncreaserType> __MyType;
		public:
			GINL BasicBuffer(){this->init();}
			GINL BasicBuffer(const __MyType& src){this->init(); this->operator = (src);}
			GINL ~BasicBuffer(){if(m_pFront != GNULL) delete[] m_pFront;}
			GINL const GAIA::U8* front_ptr() const{return m_pFront;}
			GINL GAIA::U8* front_ptr(){return m_pFront;}
			GINL const GAIA::U8* back_ptr() const{return m_pBack;}
			GINL GAIA::U8* back_ptr(){return m_pBack;}
			GINL GAIA::GVOID reserve(const _SizeType& size){this->destroy(); if(size > 0){this->alloc(size); m_pCur = m_pFront;}}
			GINL GAIA::GVOID resize(const _SizeType& size){if(this->capacity() < size) this->reserve(size); m_pCur = m_pFront + size;}
			GINL GAIA::GVOID clear(){m_pCur = m_pFront;}
			GINL GAIA::GVOID destroy(){if(m_pFront != GNULL){delete[] m_pFront; m_pFront = m_pBack = m_pCur = GNULL;}}
			GINL _SizeType capacity() const{return static_cast<_SizeType>(m_pBack - m_pFront);}
			GINL _SizeType size() const{return static_cast<_SizeType>(m_pCur - m_pFront);}
			GINL GAIA::BL empty() const{return this->size() == 0;}
			template<typename ObjType> GINL GAIA::GVOID push(const ObjType& obj)
			{
				GAIA::U8* pNew = this->alloc(sizeof(obj));
				GAIA::ALGORITHM::memcpy(pNew, &obj, sizeof(obj));
			}
			template<typename ObjType> GINL GAIA::BL pop(ObjType& obj)
			{
				if(sizeof(obj) > m_pCur - m_pFront)
					return GAIA::False;
				GAIA::ALGORITHM::memcpy(&obj, m_pCur - sizeof(obj), sizeof(obj));
				m_pCur -= sizeof(obj);
				return GAIA::True;
			}
			template<typename ObjType> GINL BasicBuffer& operator << (const ObjType& obj){this->push(obj); return *this;}
			template<typename ObjType> GINL BasicBuffer& operator >> (ObjType& obj){this->pop(obj); return *this;}
			GINL __MyType& operator = (const __MyType& src)
			{
				this->destroy();
				if(src.size() > 0)
				{
					this->reserve(src.size());
					GAIA::ALGORITHM::memcpy(this->front_ptr(), src.front_ptr(), src.size());
				}
				return *this;
			}
			GINL operator GAIA::U8*(){return m_pFront;}
		private:
			GINL GAIA::GVOID init(){m_pFront = m_pBack = m_pCur = GNULL;}
			GINL GAIA::U8* alloc(_SizeType size)
			{
				if(size == 0)
					return GNULL;
				if(m_pBack - m_pCur >= size)
				{
					GAIA::U8* pRet = m_pCur;
					m_pCur += size;
					return pRet;
				}
				_SizeIncreaserType increaser;
				_SizeType newsize = GAIA::ALGORITHM::maximize(
					increaser.Increase(static_cast<_SizeType>(m_pCur - m_pFront)),
					static_cast<_SizeType>(m_pCur - m_pFront) + size);
				GAIA::U8* pNew = new GAIA::U8[newsize];
				if(m_pCur != m_pFront)
					GAIA::ALGORITHM::memcpy(pNew, m_pFront, m_pCur - m_pFront);
				if(m_pFront != GNULL)
					delete[] m_pFront;
				m_pCur = pNew + (m_pCur - m_pFront);
				m_pFront = pNew;
				m_pBack = pNew + newsize;
				U8* pRet = m_pCur;
				m_pCur += size;
				return pRet;
			}
		private:
			GAIA::U8* m_pFront;
			GAIA::U8* m_pBack;
			GAIA::U8* m_pCur;
		};
	};
};

#endif
