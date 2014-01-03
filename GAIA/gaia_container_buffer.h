#ifndef		__GAIA_CONTAINER_BUFFER_H__
#define		__GAIA_CONTAINER_BUFFER_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template <typename _SizeIncreaserType, typename _DataSizeType> class Buffer
		{
		public:
			GINL Buffer(){m_pFront = m_pBack = m_pRead = m_pWrite = GNULL;}
			GINL ~Buffer(){if(m_pFront != GNULL) delete[] m_pFront;}
			GINL GAIA::U8* front() const{return m_pFront;}
			GINL GAIA::U8* back() const{return m_pBack;}
			GINL _DataSizeType size_r() const{return m_pRead - m_pFront;}
			GINL _DataSizeType size_w() const{return m_pWrite - m_pFront;}

			template <typename ObjType> GINL GAIA::GVOID push(const ObjType& obj)
			{
				GAIA::U8* pNew = this->alloc(sizeof(obj));
				memcpy(pNew, &obj, sizeof(obj));
			}

			template <typename ObjType> GINL GAIA::BL pop(ObjType& obj)
			{
				if(sizeof(obj) > m_pBack - m_pRead)
					return GAIA::False;
				memcpy(&obj, m_pRead, sizeof(obj));
				m_pRead += sizeof(obj);
				return GAIA::True;
			}

			template <typename ObjType> GINL Buffer& operator << (const ObjType& obj){this->push(obj); return *this;}
			template <typename ObjType> GINL Buffer& operator >> (ObjType& obj){this->pop(obj); return *this;}

		private:
			GAIA::U8* alloc(_DataSizeType size)
			{
				if(size == 0)
					return GNULL;
				if(m_pBack - m_pWrite >= size)
				{
					GAIA::U8* pRet = m_pWrite;
					m_pWrite += size;
					return pRet;
				}

				_SizeIncreaserType increaser;
				_DataSizeType newsize = GAIA::max(increaser.Increase(m_pWrite - m_pFront), m_pWrite - m_pFront + size);
				GAIA::U8* pNew = new GAIA::U8[newsize];
				if(m_pWrite != m_pFront)
					memcpy(pNew, m_pFront, m_pWrite - m_pFront);
				if(m_pFront != GNULL)
					delete[] m_pFront;

				m_pRead = pNew + (m_pRead - m_pFront);
				m_pWrite = pNew + (m_pWrite - m_pFront);
				m_pFront = pNew;
				m_pBack = pNew + newsize;

				U8* pRet = m_pWrite;
				m_pWrite += size;
				return pRet;
			}

		private:
			GAIA::U8* m_pFront;
			GAIA::U8* m_pBack;
			GAIA::U8* m_pRead;
			GAIA::U8* m_pWrite;
		};
	};
};

#endif