#ifndef		__GAIA_CONTAINER_BUFFER_H__
#define		__GAIA_CONTAINER_BUFFER_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template <typename _SizeIncreaserType, typename _DataSizeType> class Buffer
		{
		public:
			GINL Buffer(){m_pFront = m_pBack = m_pCur = GNULL;}
			GINL ~Buffer(){if(m_pFront != GNULL) delete[] m_pFront;}
			GINL GAIA::U8* front() const{return m_pFront;}
			GINL GAIA::U8* back() const{return m_pBack;}
			GINL GAIA::GVOID reserve(const _DataSizeType& size){this->destroy(); if(size > 0){this->alloc(size); m_pCur = m_pFront;}}
			GINL GAIA::GVOID resize(const _DataSizeType& size){if(this->capacity() < size) this->reserve(size); m_pCur = m_pFront + size;}
			GINL GAIA::GVOID clear(){m_pCur = m_pFront;}
			GINL GAIA::GVOID destroy(){if(m_pFront != GNULL){delete[] m_pFront; m_pFront = m_pBack = m_pCur = GNULL;}}
			GINL _DataSizeType capacity() const{return m_pBack - m_pFront;}
			GINL _DataSizeType size() const{return m_pCur - m_pFront;}
			template <typename ObjType> GINL GAIA::GVOID push(const ObjType& obj)
			{
				GAIA::U8* pNew = this->alloc(sizeof(obj));
				GAIA::ALGORITHM::memcpy(pNew, &obj, sizeof(obj));
			}
			template <typename ObjType> GINL GAIA::BL pop(ObjType& obj)
			{
				if(sizeof(obj) > m_pCur - m_pFront)
					return GAIA::False;
				GAIA::ALGORITHM::memcpy(&obj, m_pCur - sizeof(obj), sizeof(obj));
				m_pCur -= sizeof(obj);
				return GAIA::True;
			}
			template <typename ObjType> GINL Buffer& operator << (const ObjType& obj){this->push(obj); return *this;}
			template <typename ObjType> GINL Buffer& operator >> (ObjType& obj){this->pop(obj); return *this;}
			GINL operator GAIA::U8*(){return m_pFront;}
		private:
			GAIA::U8* alloc(_DataSizeType size)
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
				_DataSizeType newsize = GAIA::ALGORITHM::max(increaser.Increase(m_pCur - m_pFront), m_pCur - m_pFront + size);
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
