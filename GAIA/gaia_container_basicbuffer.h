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
			GINL GAIA::BL empty() const{return this->write_size() == 0;}
			GINL _SizeType capacity() const{return static_cast<_SizeType>(m_pBack - m_pFront);}
			GINL GAIA::GVOID clear(){m_pWrite = m_pRead = m_pFront;}
			GINL GAIA::GVOID destroy(){if(m_pFront != GNULL){delete[] m_pFront; this->init();}}
			GINL GAIA::GVOID reserve(const _SizeType& size){this->destroy(); if(size > 0){this->alloc(size); m_pWrite = m_pRead = m_pFront;}}
			GINL GAIA::GVOID resize(const _SizeType& size){if(this->capacity() < size) this->reserve(size); m_pWrite = m_pRead = m_pFront; m_pWrite += size;}
			GINL const GAIA::U8* front_ptr() const{return m_pFront;}
			GINL GAIA::U8* front_ptr(){return m_pFront;}
			GINL const GAIA::U8* back_ptr() const{return m_pBack;}
			GINL GAIA::U8* back_ptr(){return m_pBack;}
			GINL const GAIA::U8* write_ptr() const{return m_pWrite;}
			GINL GAIA::U8* write_ptr(){return m_pWrite;}
			GINL const GAIA::U8* read_ptr() const{return m_pRead;}
			GINL GAIA::U8* read_ptr(){return m_pRead;}
			GINL GAIA::BL seek_write(const _SizeType& size, SEEK_TYPE seektype){return this->seek_ptr(size, seektype, m_pWrite);}
			GINL GAIA::BL seek_read(const _SizeType& size, SEEK_TYPE seektype){return this->seek_ptr(size, seektype, m_pRead);}
			GINL _SizeType write_size() const{return static_cast<_SizeType>(m_pWrite - m_pFront);}
			GINL _SizeType read_size() const{return static_cast<_SizeType>(m_pRead - m_pFront);}
			GINL GAIA::GVOID write(const __MyType& src)
			{
				if(src.write_size() == 0)
					return;
				GAIA::U8* pNew = this->alloc(src.write_size());
				GAIA::ALGORITHM::memcpy(pNew, src.front_ptr(), src.write_size());
			}
			GINL GAIA::BL read(__MyType& src)
			{
				if(src.write_size() == 0)
					return GAIA::True;
				if(src.write_size() > m_pBack - m_pRead)
					return GAIA::False;
				GAIA::ALGORITHM::memcpy(src.front_ptr(), m_pRead, src.write_size());
				m_pRead += src.write_size();
				return GAIA::True;
			}
			template<typename _ParamObjType> GINL GAIA::GVOID write(const _ParamObjType& obj)
			{
				GAIA::U8* pNew = this->alloc(sizeof(obj));
				GAIA::ALGORITHM::memcpy(pNew, &obj, sizeof(obj));
			}
			template<typename _ParamObjType> GINL GAIA::BL read(_ParamObjType& obj)
			{
				if(sizeof(obj) > m_pBack - m_pRead)
					return GAIA::False;
				GAIA::ALGORITHM::memcpy(&obj, m_pRead, sizeof(obj));
				m_pRead += sizeof(obj);
				return GAIA::True;
			}
			GINL __MyType& operator << (const __MyType& src){this->write(src); return *this;}
			GINL __MyType& operator >> (const __MyType& src){this->read(src); return *this;}
			template<typename _ParamObjType> GINL __MyType& operator << (const _ParamObjType& obj){this->write(obj); return *this;}
			template<typename _ParamObjType> GINL __MyType& operator >> (_ParamObjType& obj){this->read(obj); return *this;}
			GINL __MyType& operator = (const __MyType& src)
			{
				this->destroy();
				if(src.write_size() > 0)
				{
					this->reserve(src.write_size());
					GAIA::ALGORITHM::memcpy(this->front_ptr(), src.front_ptr(), src.write_size());
				}
				return *this;
			}
			GINL operator GAIA::U8*(){return m_pFront;}
		private:
			GINL GAIA::GVOID init(){m_pFront = m_pBack = m_pWrite = m_pRead = GNULL;}
			GINL GAIA::U8* alloc(const _SizeType& size)
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
				_SizeType newsize = GAIA::ALGORITHM::maximize(
					increaser.Increase(static_cast<_SizeType>(m_pWrite - m_pFront)),
					static_cast<_SizeType>(m_pWrite - m_pFront) + size);
				GAIA::U8* pNew = new GAIA::U8[newsize];
				if(m_pWrite != m_pFront)
					GAIA::ALGORITHM::memcpy(pNew, m_pFront, m_pWrite - m_pFront);
				if(m_pFront != GNULL)
					delete[] m_pFront;
				m_pWrite = pNew + (m_pWrite - m_pFront);
				m_pFront = pNew;
				m_pBack = pNew + newsize;
				U8* pRet = m_pWrite;
				m_pWrite += size;
				return pRet;
			}
			GINL GAIA::BL seek_ptr(const _SizeType& size, SEEK_TYPE seektype, GAIA::U8*& p)
			{
				switch(seektype)
				{
				case SEEK_TYPE_BEGIN:
					{
						if(size < 0 || size >= this->capacity())
							return GAIA::False;
						p = m_pFront + size;
					}
					break;
				case SEEK_TYPE_END:
					{
						if(size < 0 || size >= this->capacity())
							return GAIA::False;
						p = m_pBack - size;
					}
					break;
				case SEEK_TYPE_FORWARD:
					{
						if(m_pBack - p < size)
							return GAIA::False;
						p += size;
					}
					break;
				case SEEK_TYPE_BACKWARD:
					{
						if(p - m_pFront < size)
							return GAIA::False;
						p -= size;
					}
					break;
				default:
					return GAIA::False;
				}
				return GAIA::True;
			}
		private:
			GAIA::U8* m_pFront;
			GAIA::U8* m_pBack;
			GAIA::U8* m_pWrite;
			GAIA::U8* m_pRead;
		};
	};
};

#endif
