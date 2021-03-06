#ifndef		__GAIA_CONTAINER_BASICBUFFER_H__
#define		__GAIA_CONTAINER_BASICBUFFER_H__

namespace GAIA
{
	namespace CTN
	{
		template<typename _SizeType, typename _SizeIncreaserType> class BasicBuffer : public GAIA::Entity
		{
		public:
			typedef _SizeType _sizetype;
			typedef _SizeIncreaserType _sizeincreasertype;
			typedef GAIA::U8 _datatype;
		public:
			typedef BasicBuffer<_SizeType, _SizeIncreaserType> __MyType;
		public:
			GINL BasicBuffer(){this->init();}
			GINL BasicBuffer(const __MyType& src){this->init(); this->operator = (src);}
			GINL ~BasicBuffer(){if(m_pFront != GNIL) GAIA_MFREE(m_pFront);}
			GINL GAIA::BL empty() const{return this->write_size() == 0;}
			GINL _SizeType capacity() const{return static_cast<_SizeType>(m_pBack - m_pFront);}
			GINL GAIA::GVOID clear(){m_pWrite = m_pRead = m_pFront;}
			GINL GAIA::GVOID destroy(){if(m_pFront != GNIL){GAIA_MFREE(m_pFront); this->init();}}
			GINL GAIA::GVOID reserve(const _SizeType& size)
			{
				if(size == this->capacity())
				{
					m_pWrite = m_pRead = m_pFront;
					return;
				}
				this->destroy();
				if(size > 0)
				{
					this->alloc(size);
					m_pWrite = m_pRead = m_pFront;
				}
			}
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
			GINL GAIA::GVOID write(const GAIA::GVOID* p, const _SizeType& size)
			{
				GAIA_AST(!!p);
				if(p == GNIL)
					return;
				GAIA_AST(size != 0);
				if(size == 0)
					return;
				GAIA::U8* pNew = this->alloc(size);
				GAIA::ALGO::xmemcpy(pNew, p, size);
			}
			GINL GAIA::BL read(GAIA::GVOID* p, const _SizeType& size)
			{
				GAIA_AST(!!p);
				if(p == GNIL)
					return GAIA::False;
				GAIA_AST(size != 0);
				if(size == 0)
					return GAIA::False;
				if(size > this->capacity() - this->read_size())
					return GAIA::False;
				GAIA::ALGO::xmemcpy(p, m_pRead, size);
				m_pRead += size;
				return GAIA::True;
			}
			GINL GAIA::GVOID write(const __MyType& src)
			{
				if(src.write_size() == 0)
					return;
				GAIA::U8* pNew = this->alloc(src.write_size());
				GAIA::ALGO::xmemcpy(pNew, src.front_ptr(), src.write_size());
			}
			GINL GAIA::BL read(__MyType& src)
			{
				if(src.write_size() == 0)
					return GAIA::False;
				if(src.write_size() > this->capacity() - this->read_size())
					return GAIA::False;
				GAIA::ALGO::xmemcpy(src.front_ptr(), m_pRead, src.write_size());
				m_pRead += src.write_size();
				return GAIA::True;
			}
			template<typename _ParamObjType> GAIA::GVOID write(const _ParamObjType* psz)
			{
				GAIA_AST(!!psz);
				if(psz == GNIL)
					return;
				GAIA::SIZE bytes = GAIA::ALGO::strlen(psz) * sizeof(_ParamObjType) + sizeof(_ParamObjType);
				GAIA::U8* pNew = this->alloc(bytes);
				GAIA::ALGO::xmemcpy(pNew, psz, bytes);
			}
			template<typename _ParamObjType> GAIA::BL read(_ParamObjType* psz)
			{
				GAIA_AST(!!psz);
				if(psz == GNIL)
					return GAIA::False;
				if(m_pRead == m_pBack)
					return GAIA::False;
				_ParamObjType* p = psz;
				while(this->capacity() - this->read_size() >= sizeof(_ParamObjType))
				{
					*p = *(_ParamObjType*)m_pRead;
					m_pRead += sizeof(_ParamObjType);
					if(*p == 0)
						return GAIA::True;
					++p;
				}
				return GAIA::False;
			}
			template<typename _ParamObjType> GAIA::GVOID write(const _ParamObjType& obj)
			{
				GAIA::U8* pNew = this->alloc(sizeof(obj));
				GAIA::ALGO::xmemcpy(pNew, &obj, sizeof(obj));
			}
			template<typename _ParamObjType> GAIA::BL read(_ParamObjType& obj)
			{
				if(sizeof(obj) > this->capacity() - this->read_size())
					return GAIA::False;
				GAIA::ALGO::xmemcpy(&obj, m_pRead, sizeof(obj));
				m_pRead += sizeof(obj);
				return GAIA::True;
			}
			GINL GAIA::BL operator == (const __MyType& src) const
			{
				if(src.write_size() != this->write_size())
					return GAIA::False;
				else
					return GAIA::ALGO::xmemcmp(this->front_ptr(), src.front_ptr(), this->write_size()) == 0;
			}
			GINL GAIA::BL operator != (const __MyType& src) const{return !this->operator == (src);}
			GINL GAIA::BL operator >= (const __MyType& src) const
			{
				if(this->write_size() > src.write_size())
					return GAIA::True;
				else if(this->write_size() < src.write_size())
					return GAIA::False;
				else
					return GAIA::ALGO::xmemcmp(this->front_ptr(), src.front_ptr(), this->write_size()) >= 0;
			}
			GINL GAIA::BL operator <= (const __MyType& src) const
			{
				if(this->write_size() < src.write_size())
					return GAIA::True;
				else if(this->write_size() > src.write_size())
					return GAIA::False;
				else
					return GAIA::ALGO::xmemcmp(this->front_ptr(), src.front_ptr(), this->write_size()) <= 0;
			}
			GINL GAIA::BL operator > (const __MyType& src) const{return !this->operator <= (src);}
			GINL GAIA::BL operator < (const __MyType& src) const{return !this->operator >= (src);}
			template<typename _ParamObjType> __MyType& operator << (const _ParamObjType& obj){this->write(obj); return *this;}
			template<typename _ParamObjType> __MyType& operator >> (_ParamObjType& obj){this->read(obj); return *this;}
			template<typename _ParamObjType> __MyType& operator << (const _ParamObjType* obj){this->write(obj); return *this;}
			template<typename _ParamObjType> __MyType& operator >> (_ParamObjType* obj){this->read(obj); return *this;}
			template<typename _ParamObjType> const GAIA::U8& operator [] (const _ParamObjType& index) const{GAIA_AST(index < this->write_size()); return this->front_ptr()[index];}
			template<typename _ParamObjType> GAIA::U8& operator [] (const _ParamObjType& index){GAIA_AST(index < this->write_size()); return this->front_ptr()[index];}
			GINL __MyType& operator = (const __MyType& src)
			{
				GAIA_AST(&src != this);
				this->reserve(src.write_size());
				if(src.write_size() > 0)
				{
					GAIA::ALGO::xmemcpy(this->front_ptr(), src.front_ptr(), src.write_size());
					m_pWrite = m_pFront + src.write_size();
				}
				return *this;
			}
			GINL operator GAIA::U8*(){return m_pFront;}
		private:
			GINL GAIA::GVOID init(){m_pFront = m_pBack = m_pWrite = m_pRead = GNIL;}
			GINL GAIA::U8* alloc(const _SizeType& size)
			{
				if(size == 0)
					return GNIL;
				GAIA_AST(m_pBack >= m_pWrite);
				if(this->capacity() - this->write_size() >= size)
				{
					GAIA::U8* pRet = m_pWrite;
					m_pWrite += size;
					return pRet;
				}
				_SizeIncreaserType increaser;
				_SizeType newsize = GAIA::ALGO::maximize(
					increaser.Increase(this->write_size()),
					this->write_size() + size);
				GAIA::U8* pNew = GAIA_MALLOC(GAIA::U8, newsize);
				if(m_pWrite != m_pFront)
					GAIA::ALGO::xmemcpy(pNew, m_pFront, this->write_size());
				if(m_pFront != GNIL)
					GAIA_MFREE(m_pFront);
				m_pWrite = pNew + this->write_size();
				m_pRead = pNew + this->read_size();
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
						if(size < 0 || size > this->capacity())
							return GAIA::False;
						p = m_pFront + size;
					}
					break;
				case SEEK_TYPE_END:
					{
						if(size < 0 || size > this->capacity())
							return GAIA::False;
						p = m_pBack - size;
					}
					break;
				case SEEK_TYPE_FORWARD:
					{
						if(static_cast<_SizeType>(m_pBack - p) < size)
							return GAIA::False;
						p += size;
					}
					break;
				case SEEK_TYPE_BACKWARD:
					{
						if(static_cast<_SizeType>(p - m_pFront) < size)
							return GAIA::False;
						p -= size;
					}
					break;
				default:
					return GAIA::False;
				}
				return GAIA::True;
			}
	#ifdef GAIA_DEBUG_MACHINELENGTH
		private: // Protect for 32-64bit error.
			GINL GAIA::GVOID write(const GAIA::NM& obj){}
			GINL GAIA::BL read(GAIA::NM& obj){return GAIA::False;}
			GINL GAIA::GVOID write(const GAIA::UM& obj){}
			GINL GAIA::BL read(GAIA::UM& obj){return GAIA::False;}
			GINL GAIA::GVOID write(const GAIA::WCH& obj){}
			GINL GAIA::BL read(GAIA::WCH& obj){return GAIA::False;}
			GINL GAIA::GVOID write(const GAIA::NM* psz){}
			GINL GAIA::BL read(GAIA::NM* psz){return GAIA::False;}
			GINL GAIA::GVOID write(const GAIA::UM* psz){}
			GINL GAIA::BL read(GAIA::UM* psz){return GAIA::False;}
			GINL __MyType& operator << (const GAIA::NM& obj){return *this;}
			GINL __MyType& operator >> (GAIA::NM& obj){return *this;}
			GINL __MyType& operator << (const GAIA::UM& obj){return *this;}
			GINL __MyType& operator >> (GAIA::UM& obj){return *this;}
			GINL __MyType& operator << (const GAIA::NM* obj){return *this;} GINL __MyType& operator << (GAIA::NM* obj){return *this;}
			GINL __MyType& operator >> (GAIA::NM* obj){return *this;}
			GINL __MyType& operator << (const GAIA::UM* obj){return *this;} GINL __MyType& operator << (GAIA::UM* obj){return *this;}
			GINL __MyType& operator >> (GAIA::UM* obj){return *this;}
	#endif
		private:
			GAIA::U8* m_pFront;
			GAIA::U8* m_pBack;
			GAIA::U8* m_pWrite;
			GAIA::U8* m_pRead;
		};
	};
};

#endif
