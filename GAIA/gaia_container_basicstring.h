#ifndef		__GAIA_CONTAINER_BASICSTRING_H__
#define		__GAIA_CONTAINER_BASICSTRING_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template <typename _DataType, typename _SizeType> class BasicString
		{
		public:
			typedef _DataType _datatype;
			typedef _SizeType _sizetype;
		private:
			static const GAIA::UM GAIA_DIGIT_TOSTRING_LEN = 64;
		public:
			GINL BasicString(){this->init();}
			GINL BasicString(const _DataType* p){this->init(); this->operator = (p);}
			GINL BasicString(const BasicString<_DataType, _SizeType>& src){this->init(); this->operator = (src);}
			GINL BasicString(const GAIA::N8& t){this->init(); this->operator = (t);}
			GINL BasicString(const GAIA::N16& t){this->init(); this->operator = (t);}
			GINL BasicString(const GAIA::N32& t){this->init(); this->operator = (t);}
			GINL BasicString(const GAIA::N64& t){this->init(); this->operator = (t);}
			GINL BasicString(const GAIA::U8& t){this->init(); this->operator = (t);}
			GINL BasicString(const GAIA::U16& t){this->init(); this->operator = (t);}
			GINL BasicString(const GAIA::U32& t){this->init(); this->operator = (t);}
			GINL BasicString(const GAIA::U64& t){this->init(); this->operator = (t);}
			GINL BasicString(const GAIA::X128& t){this->init(); this->operator = (t);}
			GINL BasicString(const GAIA::F32& t){this->init(); this->operator = (t);}
			GINL BasicString(const GAIA::F64& t){this->init(); this->operator = (t);}
			GINL BasicString(const GAIA::BL& t){this->init(); this->operator = (t);}
			GINL BasicString(const _DataType* p1, const _SizeType& size1, const _DataType* p2, const _SizeType& size2){this->init(); this->combin(p1, size1, p2, size2);}
			GINL ~BasicString(){this->destroy();}
			GINL GAIA::BL empty() const{if(this->size() == 0) return GAIA::True; if(this->front()[0] == 0) return GAIA::True; return GAIA::False;}
			GINL _SizeType size() const{if(m_size == 0) return 0; return m_size - 1;}
			GINL _SizeType capacity() const{if(m_capacity == 0) return 0; return m_capacity - 1;}
			GINL GAIA::GVOID resize(const _SizeType& size)
			{
				if(size == 0)
					m_size = 0;
				else
				{
					if(size > this->capacity())
						this->reserve(size);
					m_size = size + 1;
				}
			}
			GINL GAIA::GVOID reserve(const _SizeType& size)
			{
				this->destroy();
				if(size > 0)
				{
					m_capacity = size + 1;
					m_size = 0;
					m_pFront = new _DataType[m_capacity];
					m_pFront[size] = 0;
				}
			}
			GINL GAIA::GVOID clear(){m_size = 0; if(m_pFront != GNULL) m_pFront[0] = 0;}
			GINL GAIA::GVOID destroy(){m_size = m_capacity = 0; if(m_pFront != GNULL){delete[] m_pFront; m_pFront = GNULL;}}
			GINL _DataType* front(){return m_pFront;}
			GINL const _DataType* front() const{return m_pFront;}
			GINL GAIA::GVOID inverse(){if(this->size() > 1) GAIA::ALGORITHM::inverse(m_pFront, m_pFront + this->size() - 2);}
			GINL GAIA::BL insert(const _DataType& t, const _SizeType& index)
			{
				if(index > this->size())
					return GAIA::False;
				if(this->size() == this->capacity())
					this->exten(1);
				GAIA::ALGORITHM::move_next(this->front() + this->size() + 1, this->size() - index + 1);
				this->operator[](index) = t;
				this->resize(this->size() + 1);
				return GAIA::True;
			}
			GINL GAIA::BL insert(const _DataType* p, const _SizeType& index)
			{
				if(index > this->size())
					return GAIA::False;
				GAIA_ASSERT(p != GNULL);
				if(p == GNULL)
					return GAIA::False;
				if(*p == 0)
					return GAIA::True;
				_SizeType newsize = GAIA::ALGORITHM::strlen(p);
				if(this->size() == this->capacity())
					this->exten(newsize);
				GAIA::ALGORITHM::move_next(this->front() + this->size() + newsize, this->front() + this->size(), newsize);
				GAIA::ALGORITHM::xcopy(this->front() + index, p, newsize);
				return GAIA::True;
			}
			GINL GAIA::BL insert(const BasicString<_DataType, _SizeType>& src, const _SizeType& index)
			{
				if(index > this->size())
					return GAIA::False;
				if(src.size() == 0)
					return GAIA::True;
				if(this->size() == this->capacity())
					this->exten(src.size());
				GAIA::ALGORITHM::move_next(this->front() + this->size() + src.size(), this->front() + this->size(), src.size());
				GAIA::ALGORITHM::xcopy(this->front() + index, src.front(), src.size());
				return GAIA::True;
			}
			GINL GAIA::BL erase(const _SizeType& index)
			{
			}
			GINL GAIA::BL erase(const _SizeType& index_start, const _SizeType& index_end)
			{
			}
			GINL GAIA::BL erase(const _DataType& t, const _SizeType& index)
			{
			}
			GINL GAIA::BL erase(const _DataType* p, const _SizeType& index)
			{
			}
			GINL GAIA::BL erase(const BasicString<_DataType, _SizeType>& src)
			{
			}
			GINL _SizeType find(const _DataType& t, const _SizeType& index) const
			{
				if(index >= this->size())
					return (_SizeType)-1;
				_DataType* pFinded = GAIA::ALGORITHM::find(m_pFront, m_pFront + index - 1, t);
				if(pFinded == GNULL)
					return (_SizeType)-1;
				return pFinded - m_pFront;
			}
			GINL _SizeType find(const _DataType* p, const _SizeType& index) const
			{
				GAIA_ASSERT(p != GNULL);
				if(p == GNULL)
					return (_SizeType)-1;
				if(index >= this->size())
					return (_SizeType)-1;
				_DataType* pFinded = GAIA::ALGORITHM::strstr(m_pFront + index, p);
				if(pFinded == GNULL)
					return (_SizeType)-1;
				return pFinded - m_pFront;
			}
			GINL _SizeType find(const BasicString<_DataType, _SizeType>& src, const _SizeType& index) const
			{
				GAIA_ASSERT(src.size() == 0);
				if(src.size() == 0)
					return (_SizeType)-1;
				if(index >= this->size())
					return (_SizeType)-1;
				_DataType* pFinded = GAIA::ALGORITHM::strstr(m_pFront + index, src.front());
				if(pFinded == GNULL)
					return (_SizeType)-1;
				return pFinded - m_pFront;
			}
			GINL _SizeType rfind(const _DataType& t, const _SizeType& index) const
			{
				if(index >= this->size())
					return (_SizeType)-1;
				_DataType* pFinded = GAIA::ALGORITHM::rfind(m_pFront, m_pFront + index - 1, t);
				if(pFinded == GNULL)
					return (_SizeType)-1;
				return pFinded - m_pFront;
			}
			GINL _SizeType rfind(const _DataType* p, const _SizeType& size, const _SizeType& index) const
			{
				GAIA_ASSERT(p != GNULL);
				if(p == GNULL)
					return (_SizeType)-1;
				if(index >= this->size())
					return (_SizeType)-1;
				_DataType* pFinded = GAIA::ALGORITHM::rfinds(m_pFront, m_pFront + index - 1, p, size);
				if(pFinded == GNULL)
					return (_SizeType)-1;
				return pFinded - m_pFront;
			}
			GINL _SizeType rfind(const BasicString<_DataType, _SizeType>& src, const _SizeType& index) const
			{
				GAIA_ASSERT(src.size() != 0);
				if(src.size() == 0)
					return (_SizeType)-1;
				if(index >= this->size())
					return (_SizeType)-1;
				_DataType* pFinded = GAIA::ALGORITHM::rfinds(m_pFront, m_pFront + index - 1, src.front(), src.size());
				if(pFinded == GNULL)
					return (_SizeType)-1;
				return pFinded - m_pFront;
			}
			GINL _SizeType replace(const _DataType& src, const _DataType& dst)
			{
			}
			GINL _SizeType replace(const _DataType* pSrc, const _DataType* pDst)
			{
			}
			GINL _SizeType replace(const BasicString<_DataType, _SizeType>& src, const BasicString<_DataType, _SizeType>& dst)
			{
			}
			GINL BasicString<_DataType, _SizeType>& left(const _SizeType& index) const
			{
				if(index >= this->size())
					return *this;
				this->operator[](index) = 0;
				this->resize(index);
				return *this;
			}
			GINL BasicString<_DataType, _SizeType>& right(const _SizeType& index) const
			{
				if(index >= this->size())
					return *this;
				GAIA::ALGORITHM::move_prev(this->front(), this->front() + index + 1, this->size() - index);
				this->resize(this->size() - index);
				return *this;
			}
			GINL BasicString<_DataType, _SizeType>& mid(const _SizeType& index_start, const _SizeType& index_end) const
			{
				GAIA_ASSERT(index_start <= index_end);
				if(index_start > index_end)
					return *this;
				if(index_start >= this->size())
					return *this;
				if(index_end >= this->size())
					return *this;
				_SizeType tempsize = index_end - index_start + 1;
				GAIA::ALGORITHM::move_prev(this->front(), this->front() + index_start, tempsize);
				this->operator[](tempsize) = 0;
				this->resize(tempsize);
				return *this;
			}
			GINL BasicString<_DataType, _SizeType>& trim_left(const _DataType& t)
			{
			}
			GINL BasicString<_DataType, _SizeType>& trim_left(const _DataType* p)
			{
			}
			GINL BasicString<_DataType, _SizeType>& trim_left(const BasicString<_DataType, _SizeType>& src)
			{
			}
			GINL BasicString<_DataType, _SizeType>& trim_right(const _DataType& t)
			{
			}
			GINL BasicString<_DataType, _SizeType>& trim_right(const _DataType* p)
			{
			}
			GINL BasicString<_DataType, _SizeType>& trim_right(const BasicString<_DataType, _SizeType>& src)
			{
			}
			GINL BasicString<_DataType, _SizeType>& operator = (const BasicString<_DataType, _SizeType>& src){return this->assign(src.front(), src.size());}
			GINL BasicString<_DataType, _SizeType>& operator = (const _DataType* p){return this->assign(p, GAIA::ALGORITHM::strlen(p));}
			GINL BasicString<_DataType, _SizeType>& operator = (const GAIA::N8& t){_DataType sz[GAIA_DIGIT_TOSTRING_LEN]; GAIA::ALGORITHM::int2str(t, sz); return this->operator = (sz);}
			GINL BasicString<_DataType, _SizeType>& operator = (const GAIA::N16& t){_DataType sz[GAIA_DIGIT_TOSTRING_LEN]; GAIA::ALGORITHM::int2str(t, sz); return this->operator = (sz);}
			GINL BasicString<_DataType, _SizeType>& operator = (const GAIA::N32& t){_DataType sz[GAIA_DIGIT_TOSTRING_LEN]; GAIA::ALGORITHM::int2str(t, sz); return this->operator = (sz);}
			GINL BasicString<_DataType, _SizeType>& operator = (const GAIA::N64& t){_DataType sz[GAIA_DIGIT_TOSTRING_LEN]; GAIA::ALGORITHM::int2str(t, sz); return this->operator = (sz);}
			GINL BasicString<_DataType, _SizeType>& operator = (const GAIA::U8& t){_DataType sz[GAIA_DIGIT_TOSTRING_LEN]; GAIA::ALGORITHM::int2str(t, sz); return this->operator = (sz);}
			GINL BasicString<_DataType, _SizeType>& operator = (const GAIA::U16& t){_DataType sz[GAIA_DIGIT_TOSTRING_LEN]; GAIA::ALGORITHM::int2str(t, sz); return this->operator = (sz);}
			GINL BasicString<_DataType, _SizeType>& operator = (const GAIA::U32& t){_DataType sz[GAIA_DIGIT_TOSTRING_LEN]; GAIA::ALGORITHM::int2str(t, sz); return this->operator = (sz);}
			GINL BasicString<_DataType, _SizeType>& operator = (const GAIA::U64& t){_DataType sz[GAIA_DIGIT_TOSTRING_LEN]; GAIA::ALGORITHM::int2str(t, sz); return this->operator = (sz);}
			GINL BasicString<_DataType, _SizeType>& operator = (const GAIA::X128& t){}
			GINL BasicString<_DataType, _SizeType>& operator = (const GAIA::F32& t){_DataType sz[GAIA_DIGIT_TOSTRING_LEN]; GAIA::ALGORITHM::real2str(t, sz); return this->operator = (sz);}
			GINL BasicString<_DataType, _SizeType>& operator = (const GAIA::F64& t){_DataType sz[GAIA_DIGIT_TOSTRING_LEN]; GAIA::ALGORITHM::real2str(t, sz); return this->operator = (sz);}
			GINL BasicString<_DataType, _SizeType>& operator = (const GAIA::BL& t){_DataType sz[GAIA_DIGIT_TOSTRING_LEN]; GAIA::ALGORITHM::int2str(t, sz); return this->operator = (sz);}
			GINL BasicString<_DataType, _SizeType>& operator += (const BasicString<_DataType, _SizeType>& src){return this->combin(src.front(), src.size());}
			GINL BasicString<_DataType, _SizeType>& operator += (const _DataType* p){return this->combin(p, GAIA::ALGORITHM::strlen(p));}
			GINL BasicString<_DataType, _SizeType> operator + (const BasicString<_DataType, _SizeType>& src) const{return BasicString<_DataType, _SizeType>(this->front(), this->size(), src.front(), src.size());}
			GINL BasicString<_DataType, _SizeType> operator + (const _DataType* p) const{return BasicString<_DataType, _SizeType>(this->front(), this->size(), p, GAIA::ALGORITHM::strlen(p));}
			GINL GAIA::BL operator == (const BasicString<_DataType, _SizeType>& src) const{if(this->size() != src.size()) return GAIA::False; return GAIA::ALGORITHM::strcmp(this->front(), src.front()) == 0;}
			GINL GAIA::BL operator == (const _DataType* p) const{return GAIA::ALGORITHM::strcmp(this->front(), p) == 0;}
			GINL GAIA::BL operator != (const BasicString<_DataType, _SizeType>& src) const{if(this->size() != src.size()) return GAIA::True; return GAIA::ALGORITHM::strcmp(this->front(), src.front()) != 0;}
			GINL GAIA::BL operator != (const _DataType* p) const{return GAIA::ALGORITHM::strcmp(this->front(), p) != 0;}
			GINL GAIA::BL operator >= (const BasicString<_DataType, _SizeType>& src) const{return GAIA::ALGORITHM::strcmp(this->front(), src.front()) >= 0;}
			GINL GAIA::BL operator >= (const _DataType* p) const{return GAIA::ALGORITHM::strcmp(this->front(), p) >= 0;}
			GINL GAIA::BL operator <= (const BasicString<_DataType, _SizeType>& src) const{return GAIA::ALGORITHM::strcmp(this->front(), src.front()) <= 0;}
			GINL GAIA::BL operator <= (const _DataType* p) const{return GAIA::ALGORITHM::strcmp(this->front(), p) <= 0;}
			GINL GAIA::BL operator > (const BasicString<_DataType, _SizeType>& src) const{return GAIA::ALGORITHM::strcmp(this->front(), src.front()) > 0;}
			GINL GAIA::BL operator > (const _DataType* p) const{return GAIA::ALGORITHM::strcmp(this->front(), p) > 0;}
			GINL GAIA::BL operator < (const BasicString<_DataType, _SizeType>& src) const{return GAIA::ALGORITHM::strcmp(this->front(), src.front()) < 0;}
			GINL GAIA::BL operator < (const _DataType* p) const{return GAIA::ALGORITHM::strcmp(this->front(), p) < 0;}
			GINL const _DataType& operator[](const _SizeType& index) const{GAIA_ASSERT(index < this->size()); return m_pFront[index];}
			GINL _DataType& operator[](const _SizeType& index){GAIA_ASSERT(index < this->size()); return m_pFront[index];}
			GINL operator _DataType*(){return m_pFront;}
			GINL operator const _DataType*() const{return m_pFront;}
			GINL operator GAIA::UM() const{return GAIA::ALGORITHM::string_cast<UM>(m_pFront);}
			GINL operator GAIA::NM() const{return GAIA::ALGORITHM::string_cast<NM>(m_pFront);}
			GINL operator GAIA::N8() const{return GAIA::ALGORITHM::string_cast<N8>(m_pFront);}
			GINL operator GAIA::N16() const{return GAIA::ALGORITHM::string_cast<N16>(m_pFront);}
			GINL operator GAIA::N32() const{return GAIA::ALGORITHM::string_cast<N32>(m_pFront);}
			GINL operator GAIA::N64() const{return GAIA::ALGORITHM::string_cast<N64>(m_pFront);}
			GINL operator GAIA::U8() const{return GAIA::ALGORITHM::string_cast<U8>(m_pFront);}
			GINL operator GAIA::U16() const{return GAIA::ALGORITHM::string_cast<U16>(m_pFront);}
			GINL operator GAIA::U32() const{return GAIA::ALGORITHM::string_cast<U32>(m_pFront);}
			GINL operator GAIA::U64() const{return GAIA::ALGORITHM::string_cast<U64>(m_pFront);}
			GINL operator GAIA::X128() const{}
			GINL operator GAIA::F32() const{return GAIA::ALGORITHM::string_cast<F32>(m_pFront);}
			GINL operator GAIA::F64() const{return GAIA::ALGORITHM::string_cast<F64>(m_pFront);}
			GINL operator GAIA::BL() const{return GAIA::ALGORITHM::string_cast<BL>(m_pFront);}
		private:
			GINL GAIA::GVOID init(){m_pFront = GNULL; m_size = m_capacity = 0;}
			GINL GAIA::GVOID exten(const _SizeType& size)
			{
				GAIA_ASSERT(size >= 0);
				if(size == 0)
					return;
				_DataType* pNew = new _DataType[this->capacity() + size + 1];
				if(!this->empty())
					GAIA::ALGORITHM::strcpy(pNew, this->front());
				m_capacity = this->capacity() + size + 1;
				delete[] m_pFront;
				m_pFront = pNew;
			}
			GINL BasicString<_DataType, _SizeType>& assign(const _DataType* p, const _SizeType& size)
			{
				if(p == GNULL || size == 0)
					return *this;
				this->clear();
				this->resize(size);
				GAIA::ALGORITHM::strcpy(m_pFront, p);
				return *this;
			}
			GINL BasicString<_DataType, _SizeType>& combin(const _DataType* p, const _SizeType& size)
			{
				if(p == GNULL)
					return *this;
				if(*p == 0)
					return *this;
				if(size == 0)
					return *this;
				if(this->capacity() - this->size() >= size)
				{
					GAIA::ALGORITHM::strcpy(this->front() + this->size(), p);
					this->resize(this->size() + size);
				}
				else
				{
					this->exten(size - (this->capacity() - this->size()));
					GAIA::ALGORITHM::strcpy(this->front() + this->size(), p);
					this->resize(this->size() + size);
				}
				return *this;
			}
			GINL BasicString<_DataType, _SizeType>& combin(const _DataType* p1, const _SizeType& size1, const _DataType* p2, const _SizeType& size2)
			{
				GAIA::BL bEmpty1 = p1 == GNULL || *p1 == 0 || size1 == 0;
				GAIA::BL bEmpty2 = p2 == GNULL || *p2 == 0 || size2 == 0;
				if(bEmpty1 && bEmpty2)
					return *this;
				else if(!bEmpty1 && bEmpty2)
				{
					this->operator = (p1);
					return *this;
				}
				else if(bEmpty1 && !bEmpty2)
				{
					this->operator = (p2);
					return *this;
				}
				else
				{
					this->reserve(size1 + size2);
					this->operator = (p1);
					GAIA::ALGORITHM::strcpy(this->front() + this->size(), p2);
					this->resize(size1 + size2);
					return *this;
				}
			}
		private:
			_DataType* m_pFront;
			_SizeType m_size;
			_SizeType m_capacity;
		};
	};
};

#endif
