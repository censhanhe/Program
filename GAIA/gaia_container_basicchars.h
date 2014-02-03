#ifndef 	__GAIA_CONTAINER_BASICCHARS_H__
#define 	__GAIA_CONTAINER_BASICCHARS_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template <typename _DataType, typename _SizeType, _SizeType _Size> class BasicChars
		{
		public:
			typedef _DataType _datatype;
			typedef _SizeType _sizetype;
		public:
			static const _SizeType _size = _Size;
		public:
			typedef BasicChars<_DataType, _SizeType, _Size> __MyType;
		private:
			static const GAIA::UM GAIA_DIGIT_TOSTRING_LEN = 64;
		public:
			GINL BasicChars(){this->init();}
			GINL BasicChars(const _DataType* p){this->init(); this->operator = (p);}
			GINL BasicChars(const __MyType& src){this->init(); this->operator = (src);}
			GINL BasicChars(const GAIA::N8& t){this->init(); this->operator = (t);}
			GINL BasicChars(const GAIA::N16& t){this->init(); this->operator = (t);}
			GINL BasicChars(const GAIA::N32& t){this->init(); this->operator = (t);}
			GINL BasicChars(const GAIA::N64& t){this->init(); this->operator = (t);}
			GINL BasicChars(const GAIA::U8& t){this->init(); this->operator = (t);}
			GINL BasicChars(const GAIA::U16& t){this->init(); this->operator = (t);}
			GINL BasicChars(const GAIA::U32& t){this->init(); this->operator = (t);}
			GINL BasicChars(const GAIA::U64& t){this->init(); this->operator = (t);}
			GINL BasicChars(const GAIA::X128& t){this->init(); this->operator = (t);}
			GINL BasicChars(const GAIA::F32& t){this->init(); this->operator = (t);}
			GINL BasicChars(const GAIA::F64& t){this->init(); this->operator = (t);}
			GINL BasicChars(const GAIA::BL& t){this->init(); this->operator = (t);}
			GINL BasicChars(const _DataType* p1, const _SizeType& size1, const _DataType* p2, const _SizeType& size2){this->init(); this->combin(p1, size1, p2, size2);}
			GINL ~BasicChars(){}
			GINL GAIA::BL empty() const{if(this->size() == 0) return GAIA::True; return GAIA::False;}
			GINL _SizeType size() const{if(m_size == 0) return 0; return m_size - 1;}
			GINL _SizeType capacity() const{return _Size;}
			GINL GAIA::GVOID resize(const _SizeType& size){if(size > _Size) return; m_size = size + 1;}
			GINL GAIA::GVOID clear(){m_size = 0; if(m_chars != GNULL) m_chars[0] = 0;}
			GINL _DataType* front_ptr(){return &this->operator[](0);}
			GINL const _DataType* front_ptr() const{return &this->operator[](0);}
			GINL GAIA::GVOID inverse(){if(this->size() > 1) GAIA::ALGORITHM::inverse(m_chars, m_chars + this->size() - 2);}
			GINL GAIA::BL insert(const _DataType& t, const _SizeType& index)
			{
				if(index > this->size())
					return GAIA::False;
				if(this->size() == this->capacity())
					return GAIA::False;
				GAIA::ALGORITHM::move_next(this->front_ptr() + this->size() + 1, this->size() - index + 1);
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
				if(this->size() + newsize >= this->capacity())
					return GAIA::False;
				GAIA::ALGORITHM::move_next(this->front_ptr() + this->size() + newsize, this->front_ptr() + this->size(), newsize);
				GAIA::ALGORITHM::xcopy(this->front_ptr() + index, p, newsize);
				return GAIA::True;
			}
			GINL GAIA::BL insert(const __MyType& src, const _SizeType& index)
			{
				if(index > this->size())
					return GAIA::False;
				if(src.size() == 0)
					return GAIA::True;
				if(this->size() + src.size() >= this->capacity())
					return GAIA::False;
				GAIA::ALGORITHM::move_next(this->front_ptr() + this->size() + src.size(), this->front_ptr() + this->size(), src.size());
				GAIA::ALGORITHM::xcopy(this->front_ptr() + index, src.front_ptr(), src.size());
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
				GAIA_ASSERT(p != GNULL);
			}
			GINL GAIA::BL erase(const __MyType& src)
			{
			}
			GINL _SizeType find(const _DataType& t, const _SizeType& index) const
			{
				if(index >= this->size())
					return (_SizeType)-1;
				_DataType* pFinded = GAIA::ALGORITHM::find(m_chars + index, m_chars + this->size() - 1, t);
				if(pFinded == GNULL)
					return (_SizeType)-1;
				return pFinded - m_chars;
			}
			GINL _SizeType find(const _DataType* p, const _SizeType& index) const
			{
				GAIA_ASSERT(p != GNULL);
				if(p == GNULL)
					return (_SizeType)-1;
				if(index >= this->size())
					return (_SizeType)-1;
				_DataType* pFinded = GAIA::ALGORITHM::strstr(m_chars + index, p);
				if(pFinded == GNULL)
					return (_SizeType)-1;
				return pFinded - m_chars;
			}
			GINL _SizeType find(const __MyType& src, const _SizeType& index) const
			{
				GAIA_ASSERT(src.size() != 0);
				if(src.size() == 0)
					return (_SizeType)-1;
				if(index >= this->size())
					return (_SizeType)-1;
				_DataType* pFinded = GAIA::ALGORITHM::strstr(m_chars + index, src.front_ptr());
				if(pFinded == GNULL)
					return (_SizeType)-1;
				return pFinded - m_chars;
			}
			GINL _SizeType rfind(const _DataType& t, const _SizeType& index) const
			{
				if(index >= this->size())
					return (_SizeType)-1;
				_DataType* pFinded = GAIA::ALGORITHM::rfind(m_chars, m_chars + index - 1, t);
				if(pFinded == GNULL)
					return (_SizeType)-1;
				return pFinded - m_chars;
			}
			GINL _SizeType rfind(const _DataType* p, const _SizeType& size, const _SizeType& index) const
			{
				GAIA_ASSERT(p != GNULL);
				if(p == GNULL)
					return (_SizeType)-1;
				if(index >= this->size())
					return (_SizeType)-1;
				_DataType* pFinded = GAIA::ALGORITHM::rfinds(m_chars, m_chars + index - 1, p, size);
				if(pFinded == GNULL)
					return (_SizeType)-1;
				return pFinded - m_chars;
			}
			GINL _SizeType rfind(const __MyType& src, const _SizeType& index) const
			{
				GAIA_ASSERT(src.size() != 0);
				if(src.size() == 0)
					return (_SizeType)-1;
				if(index >= this->size())
					return (_SizeType)-1;
				_DataType* pFinded = GAIA::ALGORITHM::rfinds(m_chars, m_chars + index - 1, src.front_ptr(), src.size());
				if(pFinded == GNULL)
					return (_SizeType)-1;
				return pFinded - m_chars;
			}
			GINL _SizeType replace(const _DataType& src, const _DataType& dst)
			{
			}
			GINL _SizeType replace(const _DataType* pSrc, const _DataType* pDst)
			{
			}
			GINL _SizeType replace(const __MyType& src, const __MyType& dst)
			{
			}
			GINL __MyType& left(const _SizeType& index)
			{
				if(index >= this->size())
					return *this;
				this->operator[](index) = 0;
				this->resize(index);
				return *this;
			}
			GINL __MyType& right(const _SizeType& index)
			{
				if(index >= this->size())
					return *this;
				GAIA::ALGORITHM::move_prev(this->front_ptr(), this->front_ptr() + index + 1, this->size() - index);
				this->resize(this->size() - index);
				return *this;
			}
			GINL __MyType& mid(const _SizeType& index_start, const _SizeType& index_end)
			{
				GAIA_ASSERT(index_start <= index_end);
				if(index_start > index_end)
					return *this;
				if(index_start >= this->size())
					return *this;
				if(index_end >= this->size())
					return *this;
				_SizeType tempsize = index_end - index_start + 1;
				GAIA::ALGORITHM::move_prev(this->front_ptr(), this->front_ptr() + index_start, tempsize);
				this->operator[](tempsize) = 0;
				this->resize(tempsize);
				return *this;
			}
			GINL GAIA::BL trim_left(const _SizeType& index)
			{
				if(index > this->size() + 1)
					return GAIA::False;
				if(index <= 0)
					return GAIA::False;
				GAIA::ALGORITHM::move_prev(this->front_ptr(), this->front_ptr() + index, this->size() + 1 - index);
				this->resize(this->size() - index);
				return GAIA::True;
			}
			GINL GAIA::BL trim_left(const _DataType& t)
			{
				if(this->empty())
					return GAIA::False;
				const _DataType* pTemp = m_chars;
				while(*pTemp != 0)
				{
					if(*pTemp != t)
						break;
					++pTemp;
				}
				if(pTemp == this->front_ptr())
					return GAIA::False;
				_SizeType newsize = this->size() - (pTemp - this->front_ptr());
				GAIA::ALGORITHM::move_prev(this->front_ptr(), pTemp, newsize + 1);
				this->resize(newsize);
				return GAIA::True;
			}
			GINL GAIA::BL trim_left(const _DataType* p)
			{
				GAIA_ASSERT(p != GNULL);
				if(this->empty())
					return GAIA::False;
				_DataType* pTemp = this->front_ptr();
				while(*pTemp != 0 && *p != 0)
				{
					if(*pTemp != *p)
						break;
					++pTemp;
					++p;
				}
				if(pTemp == this->front_ptr())
					return GAIA::False;
				_SizeType newsize = this->size() - (pTemp - this->front_ptr());
				GAIA::ALGORITHM::move_prev(this->front_ptr(), pTemp, newsize + 1);
				this->resize(newsize);
				return GAIA::True;
			}
			GINL GAIA::BL trim_left(const __MyType& src)
			{
				if(src.empty())
					return GAIA::False;
				return this->trim_left(src.front_ptr());
			}
			GINL GAIA::BL trim_right(const _DataType& t)
			{
				return GAIA::True;
			}
			GINL GAIA::BL trim_right(const _DataType* p)
			{
				return GAIA::True;
			}
			GINL GAIA::BL trim_right(const __MyType& src)
			{
				return GAIA::True;
			}
			GINL __MyType& operator = (const __MyType& src){this->assign(src.front_ptr(), src.size()); return *this;}
			GINL __MyType& operator = (const _DataType* p){this->assign(p, GAIA::ALGORITHM::strlen(p)); return *this;}
			GINL __MyType& operator = (const GAIA::N8& t){_DataType sz[GAIA_DIGIT_TOSTRING_LEN]; GAIA::ALGORITHM::int2str(t, sz); return this->operator = (sz);}
			GINL __MyType& operator = (const GAIA::N16& t){_DataType sz[GAIA_DIGIT_TOSTRING_LEN]; GAIA::ALGORITHM::int2str(t, sz); return this->operator = (sz);}
			GINL __MyType& operator = (const GAIA::N32& t){_DataType sz[GAIA_DIGIT_TOSTRING_LEN]; GAIA::ALGORITHM::int2str(t, sz); return this->operator = (sz);}
			GINL __MyType& operator = (const GAIA::N64& t){_DataType sz[GAIA_DIGIT_TOSTRING_LEN]; GAIA::ALGORITHM::int2str(t, sz); return this->operator = (sz);}
			GINL __MyType& operator = (const GAIA::U8& t){_DataType sz[GAIA_DIGIT_TOSTRING_LEN]; GAIA::ALGORITHM::int2str(t, sz); return this->operator = (sz);}
			GINL __MyType& operator = (const GAIA::U16& t){_DataType sz[GAIA_DIGIT_TOSTRING_LEN]; GAIA::ALGORITHM::int2str(t, sz); return this->operator = (sz);}
			GINL __MyType& operator = (const GAIA::U32& t){_DataType sz[GAIA_DIGIT_TOSTRING_LEN]; GAIA::ALGORITHM::int2str(t, sz); return this->operator = (sz);}
			GINL __MyType& operator = (const GAIA::U64& t){_DataType sz[GAIA_DIGIT_TOSTRING_LEN]; GAIA::ALGORITHM::int2str(t, sz); return this->operator = (sz);}
			GINL __MyType& operator = (const GAIA::X128& t){}
			GINL __MyType& operator = (const GAIA::F32& t){_DataType sz[GAIA_DIGIT_TOSTRING_LEN]; GAIA::ALGORITHM::real2str(t, sz); return this->operator = (sz);}
			GINL __MyType& operator = (const GAIA::F64& t){_DataType sz[GAIA_DIGIT_TOSTRING_LEN]; GAIA::ALGORITHM::real2str(t, sz); return this->operator = (sz);}
			GINL __MyType& operator = (const GAIA::BL& t){_DataType sz[GAIA_DIGIT_TOSTRING_LEN]; GAIA::ALGORITHM::int2str(t, sz); return this->operator = (sz);}
			GINL __MyType& operator += (const __MyType& src){return this->combin(src.front_ptr(), src.size());}
			GINL __MyType& operator += (const _DataType* p){return this->combin(p, GAIA::ALGORITHM::strlen(p));}
			GINL __MyType operator + (const __MyType& src) const{return __MyType(this->front_ptr(), this->size(), src.front_ptr(), src.size());}
			GINL __MyType operator + (const _DataType* p) const{return __MyType(this->front_ptr(), this->size(), p, GAIA::ALGORITHM::strlen(p));}
			GINL GAIA::BL operator == (const __MyType& src) const{if(this->size() != src.size()) return GAIA::False; return GAIA::ALGORITHM::strcmp(this->front_ptr(), src.front_ptr()) == 0;}
			GINL GAIA::BL operator == (const _DataType* p) const{return GAIA::ALGORITHM::strcmp(this->front_ptr(), p) == 0;}
			GINL GAIA::BL operator != (const __MyType& src) const{if(this->size() != src.size()) return GAIA::True; return GAIA::ALGORITHM::strcmp(this->front_ptr(), src.front_ptr()) != 0;}
			GINL GAIA::BL operator != (const _DataType* p) const{return GAIA::ALGORITHM::strcmp(this->front_ptr(), p) != 0;}
			GINL GAIA::BL operator >= (const __MyType& src) const{return GAIA::ALGORITHM::strcmp(this->front_ptr(), src.front_ptr()) >= 0;}
			GINL GAIA::BL operator >= (const _DataType* p) const{return GAIA::ALGORITHM::strcmp(this->front_ptr(), p) >= 0;}
			GINL GAIA::BL operator <= (const __MyType& src) const{return GAIA::ALGORITHM::strcmp(this->front_ptr(), src.front_ptr()) <= 0;}
			GINL GAIA::BL operator <= (const _DataType* p) const{return GAIA::ALGORITHM::strcmp(this->front_ptr(), p) <= 0;}
			GINL GAIA::BL operator > (const __MyType& src) const{return GAIA::ALGORITHM::strcmp(this->front_ptr(), src.front_ptr()) > 0;}
			GINL GAIA::BL operator > (const _DataType* p) const{return GAIA::ALGORITHM::strcmp(this->front_ptr(), p) > 0;}
			GINL GAIA::BL operator < (const __MyType& src) const{return GAIA::ALGORITHM::strcmp(this->front_ptr(), src.front_ptr()) < 0;}
			GINL GAIA::BL operator < (const _DataType* p) const{return GAIA::ALGORITHM::strcmp(this->front_ptr(), p) < 0;}
			GINL const _DataType& operator[](const _SizeType& index) const{GAIA_ASSERT(index < this->size()); return m_chars[index];}
			GINL _DataType& operator[](const _SizeType& index){GAIA_ASSERT(index < this->size()); return m_chars[index];}
			GINL operator _DataType*(){return m_chars;}
			GINL operator const _DataType*() const{return m_chars;}
			GINL operator GAIA::UM() const{return GAIA::ALGORITHM::string_cast<UM>(m_chars);}
			GINL operator GAIA::NM() const{return GAIA::ALGORITHM::string_cast<NM>(m_chars);}
			GINL operator GAIA::N8() const{return GAIA::ALGORITHM::string_cast<N8>(m_chars);}
			GINL operator GAIA::N16() const{return GAIA::ALGORITHM::string_cast<N16>(m_chars);}
			GINL operator GAIA::N32() const{return GAIA::ALGORITHM::string_cast<N32>(m_chars);}
			GINL operator GAIA::N64() const{return GAIA::ALGORITHM::string_cast<N64>(m_chars);}
			GINL operator GAIA::U8() const{return GAIA::ALGORITHM::string_cast<U8>(m_chars);}
			GINL operator GAIA::U16() const{return GAIA::ALGORITHM::string_cast<U16>(m_chars);}
			GINL operator GAIA::U32() const{return GAIA::ALGORITHM::string_cast<U32>(m_chars);}
			GINL operator GAIA::U64() const{return GAIA::ALGORITHM::string_cast<U64>(m_chars);}
			GINL operator GAIA::X128() const{}
			GINL operator GAIA::F32() const{return GAIA::ALGORITHM::string_cast<F32>(m_chars);}
			GINL operator GAIA::F64() const{return GAIA::ALGORITHM::string_cast<F64>(m_chars);}
			GINL operator GAIA::BL() const{return GAIA::ALGORITHM::string_cast<BL>(m_chars);}
		private:
			GINL GAIA::GVOID init(){m_chars[0] = 0; m_size = 0;}
			GINL __MyType& assign(const _DataType* p, const _SizeType& size)
			{
				if(p == GNULL || size == 0)
					return *this;
				if(size >= _Size)
					return *this;
				this->clear();
				GAIA::ALGORITHM::strcpy(m_chars, p);
				this->resize(size);
				return *this;
			}
			GINL __MyType& combin(const _DataType* p, const _SizeType& size)
			{
				if(p == GNULL)
					return *this;
				if(*p == 0)
					return *this;
				if(size == 0)
					return *this;
				if(this->capacity() - this->size() >= size)
				{
					GAIA::ALGORITHM::strcpy(this->front_ptr() + this->size(), p);
					this->resize(this->size() + size);
				}
				return *this;
			}
			GINL __MyType& combin(const _DataType* p1, const _SizeType& size1, const _DataType* p2, const _SizeType& size2)
			{
				if(size1 + size2 + 1 > _Size)
					return *this;
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
					this->operator = (p1);
					GAIA::ALGORITHM::strcpy(this->front_ptr() + this->size(), p2);
					this->resize(size1 + size2);
					return *this;
				}
			}
		private:
			_DataType m_chars[_Size + 1];
			_SizeType m_size;
		};
	};
};

#endif
