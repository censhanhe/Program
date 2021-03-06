#ifndef 	__GAIA_CONTAINER_BASICCHARS_H__
#define 	__GAIA_CONTAINER_BASICCHARS_H__

namespace GAIA
{
	namespace CTN
	{
		template<typename _DataType, typename _SizeType> class BasicString;
		template<typename _DataType, typename _SizeType, _SizeType _Size> class BasicChars : public GAIA::Entity
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
			class it : public GAIA::ITERATOR::Iterator<_DataType>
			{
			private:
				friend class BasicChars;
			public:
				GINL it(){this->init();}
				GINL virtual ~it(){}
				GINL virtual GAIA::BL empty() const{return m_pContainer == GNIL;}
				GINL virtual _DataType& operator * (){GAIA_AST(!!m_pContainer); return (*m_pContainer)[m_index];}
				GINL virtual const _DataType& operator * () const{GAIA_AST(!!m_pContainer); return (*m_pContainer)[m_index];}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator ++ (){GAIA_AST(!!m_pContainer); ++m_index; if(m_index >= m_pContainer->size()) this->init(); return *this;}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator -- (){GAIA_AST(!!m_pContainer); --m_index; if(m_index >= m_pContainer->size() || m_index < 0) this->init(); return *this;}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator = (const GAIA::ITERATOR::Iterator<_DataType>& src){GAIA_AST(&src != this); return this->operator = (*static_cast<const it*>(&src));}
				GINL virtual GAIA::BL operator == (const GAIA::ITERATOR::Iterator<_DataType>& src) const{return this->operator == (*static_cast<const it*>(&src));}
				GINL virtual GAIA::BL operator != (const GAIA::ITERATOR::Iterator<_DataType>& src) const{return this->operator != (*static_cast<const it*>(&src));}
				GINL it& operator = (const it& src){GAIA_AST(&src != this); m_index = src.m_index; m_pContainer = src.m_pContainer; return *this;}
				GINL it& operator += (const _SizeType& c)
				{
					if(m_pContainer == GNIL)
						return *this;
					m_index += c;
					if(m_index >= m_pContainer->size() || m_index < 0)
						this->init();
					return *this;
				}
				GINL it& operator -= (const _SizeType& c)
				{
					if(m_pContainer == GNIL)
						return *this;
					m_index -= c;
					if(m_index >= m_pContainer->size() || m_index < 0)
						this->init();
					return *this;
				}
				GINL it operator + (const _SizeType& c) const
				{
					it ret = *this;
					ret += c;
					return ret;
				}
				GINL it operator - (const _SizeType& c) const
				{
					it ret = *this;
					ret -= c;
					return ret;
				}
				GINL _SizeType operator - (const it& src) const
				{
					if(this->empty() || src.empty())
						return 0;
					return this->m_index - src.m_index;
				}
				GAIA_CLASS_OPERATOR_COMPARE(m_index, m_index, it);
			private:
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator ++ (GAIA::N32){++(*this); return *this;}
				GINL virtual GAIA::ITERATOR::Iterator<_DataType>& operator -- (GAIA::N32){--(*this); return *this;}
			private:
				GINL GAIA::GVOID init(){m_pContainer = GNIL; m_index = 0;}
			private:
				_SizeType m_index;
				__MyType* m_pContainer;
			};
			class const_it : public GAIA::ITERATOR::ConstIterator<_DataType>
			{
			private:
				friend class BasicChars;
			public:
				GINL const_it(){this->init();}
				GINL virtual ~const_it(){}
				GINL virtual GAIA::BL empty() const{return m_pContainer == GNIL;}
				GINL virtual const _DataType& operator * () const{GAIA_AST(!!m_pContainer); return (*m_pContainer)[m_index];}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator ++ (){GAIA_AST(!!m_pContainer); ++m_index; if(m_index >= m_pContainer->size()) this->init(); return *this;}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator -- (){GAIA_AST(!!m_pContainer); --m_index; if(m_index >= m_pContainer->size() || m_index < 0) this->init(); return *this;}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator = (const GAIA::ITERATOR::ConstIterator<_DataType>& src){GAIA_AST(&src != this); return this->operator = (*static_cast<const const_it*>(&src));}
				GINL virtual GAIA::BL operator == (const GAIA::ITERATOR::ConstIterator<_DataType>& src) const{return this->operator == (*static_cast<const const_it*>(&src));}
				GINL virtual GAIA::BL operator != (const GAIA::ITERATOR::ConstIterator<_DataType>& src) const{return this->operator != (*static_cast<const const_it*>(&src));}
				GINL const_it& operator = (const const_it& src){GAIA_AST(&src != this); m_index = src.m_index; m_pContainer = src.m_pContainer; return *this;}
				GINL const_it& operator += (const _SizeType& c)
				{
					if(m_pContainer == GNIL)
						return *this;
					m_index += c;
					if(m_index >= m_pContainer->size() || m_index < 0)
						this->init();
					return *this;
				}
				GINL const_it& operator -= (const _SizeType& c)
				{
					if(m_pContainer == GNIL)
						return *this;
					m_index -= c;
					if(m_index >= m_pContainer->size() || m_index < 0)
						this->init();
					return *this;
				}
				GINL const_it operator + (const _SizeType& c) const
				{
					const_it ret = *this;
					ret += c;
					return ret;
				}
				GINL const_it operator - (const _SizeType& c) const
				{
					const_it ret = *this;
					ret -= c;
					return ret;
				}
				GINL _SizeType operator - (const const_it& src) const
				{
					if(this->empty() || src.empty())
						return 0;
					return this->m_index - src.m_index;
				}
				GAIA_CLASS_OPERATOR_COMPARE(m_index, m_index, const_it);
			private:
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator ++ (GAIA::N32){++(*this); return *this;}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator -- (GAIA::N32){--(*this); return *this;}
			private:
				GINL GAIA::GVOID init(){m_pContainer = GNIL; m_index = 0;}
			private:
				_SizeType m_index;
				const __MyType* m_pContainer;
			};
		public:
			GINL BasicChars(){this->init();}
			template<typename _ParamDataType> BasicChars(const _ParamDataType* p){this->init(); this->operator = (p);}
			GINL BasicChars(const __MyType& src){this->init(); this->operator = (src);}
			GINL BasicChars(const GAIA::NM& t){this->init(); this->operator = (t);}
			GINL BasicChars(const GAIA::N8& t){this->init(); this->operator = (t);}
			GINL BasicChars(const GAIA::N16& t){this->init(); this->operator = (t);}
			GINL BasicChars(const GAIA::N32& t){this->init(); this->operator = (t);}
			GINL BasicChars(const GAIA::N64& t){this->init(); this->operator = (t);}
			GINL BasicChars(const GAIA::UM& t){this->init(); this->operator = (t);}
			GINL BasicChars(const GAIA::U8& t){this->init(); this->operator = (t);}
			GINL BasicChars(const GAIA::U16& t){this->init(); this->operator = (t);}
			GINL BasicChars(const GAIA::U32& t){this->init(); this->operator = (t);}
			GINL BasicChars(const GAIA::U64& t){this->init(); this->operator = (t);}
			GINL BasicChars(const GAIA::X128& t){this->init(); this->operator = (t);}
			GINL BasicChars(const GAIA::F32& t){this->init(); this->operator = (t);}
			GINL BasicChars(const GAIA::F64& t){this->init(); this->operator = (t);}
			GINL BasicChars(const GAIA::BL& t){this->init(); this->operator = (t);}
			template<typename _ParamDataType1, typename _ParamSizeType1, typename _ParamDataType2, typename _ParamSizeType2> BasicChars(const _ParamDataType1* p1, const _ParamSizeType1& size1, const _ParamDataType2* p2, const _ParamSizeType2& size2){this->init(); this->combin(p1, size1, p2, size2);}
			template<typename _ParamSizeType> BasicChars(const GAIA::CTN::BasicString<_DataType, _ParamSizeType>& src){this->operator = (src);}
			GINL ~BasicChars(){}
			GINL GAIA::BL empty() const{return this->size() == 0;}
			GINL _SizeType size() const{if(m_size == 0) return 0; return m_size - 1;}
			GINL _SizeType capacity() const{return _Size;}
			GINL GAIA::BL resize(const _SizeType& size){if(size > _Size) return GAIA::False; m_size = size + 1; m_chars[size] = 0; return GAIA::True;}
			GINL GAIA::GVOID clear(){m_size = 0; if(this->front_ptr() != GNIL) this->front_ptr()[0] = 0;}
			GINL GAIA::U32 type() const{return GAIA::ALGO::strtype(this->front_ptr());}
			template<typename _ParamDataType> __MyType& assign(const _ParamDataType* p, const _SizeType& size)
			{
				if(p == GNIL || size == 0)
					return *this;
				if(size > _Size)
					return *this;
				this->clear();
				GAIA::ALGO::strcpy(this->front_ptr(), p, size);
				this->resize(size);
				return *this;
			}
			GINL _DataType* front_ptr(){return m_chars;}
			GINL _DataType* back_ptr(){if(this->empty()) return GNIL; return this->front_ptr() + this->size() - 1;}
			GINL const _DataType* front_ptr() const{return m_chars;}
			GINL const _DataType* back_ptr() const{if(this->empty()) return GNIL; return this->front_ptr() + this->size() - 1;}
			GINL _DataType& front(){return *this->front_ptr();}
			GINL const _DataType& front() const{return *this->front_ptr();}
			GINL _DataType& back(){return *this->back_ptr();}
			GINL const _DataType& back() const{return *this->back_ptr();}
			GINL it front_it()
			{
				it ret;
				if(this->empty())
				{
					ret.m_index = 0;
					ret.m_pContainer = GNIL;
				}
				else
				{
					ret.m_index = 0;
					ret.m_pContainer = this;
				}
				return ret;
			}
			GINL it back_it()
			{
				it ret;
				if(this->empty())
				{
					ret.m_index = 0;
					ret.m_pContainer = GNIL;
				}
				else
				{
					ret.m_index = this->size() - 1;
					ret.m_pContainer = this;
				}
				return ret;
			}
			GINL const_it const_front_it() const
			{
				const_it ret;
				if(this->empty())
				{
					ret.m_index = 0;
					ret.m_pContainer = GNIL;
				}
				else
				{
					ret.m_index = 0;
					ret.m_pContainer = this;
				}
				return ret;
			}
			GINL const_it const_back_it() const
			{
				const_it ret;
				if(this->empty())
				{
					ret.m_index = 0;
					ret.m_pContainer = GNIL;
				}
				else
				{
					ret.m_index = this->size() - 1;
					ret.m_pContainer = this;
				}
				return ret;
			}
			GINL GAIA::GVOID inverse(){if(this->size() > 1) GAIA::ALGO::inverse(this->front_ptr(), this->front_ptr() + this->size() - 1);}
			template<typename _ParamDataType> GAIA::BL insert(const _ParamDataType& t, const _SizeType& index)
			{
				if(index > this->size())
					return GAIA::False;
				if(this->size() == this->capacity())
					return GAIA::False;
				this->resize(this->size() + 1);
				if(this->size() - 1 - index != 0)
				{
					GAIA::ALGO::move_next(
						this->front_ptr() + this->size() - 1,
						this->size() - 1 - index);
				}
				this->operator[](index) = t;
				return GAIA::True;
			}
			template<typename _ParamDataType> GAIA::BL insert(const _ParamDataType* p, const _SizeType& index)
			{
				if(index > this->size())
					return GAIA::False;
				GAIA_AST(!!p);
				if(p == GNIL)
					return GAIA::False;
				if(*p == 0)
					return GAIA::True;
				_SizeType newsize = GAIA::ALGO::strlen(p);
				if(this->size() + newsize >= this->capacity())
					return GAIA::False;
				this->resize(this->size() + newsize);
				if(this->size() - newsize - index != 0)
				{
					GAIA::ALGO::move_next(
						this->front_ptr() + this->size() - 1,
						this->front_ptr() + this->size() - newsize - 1,
						this->size() - newsize - index);
				}
				GAIA::ALGO::copy(this->front_ptr() + index, p, newsize);
				return GAIA::True;
			}
			GINL GAIA::BL insert(const __MyType& src, const _SizeType& index)
			{
				if(index > this->size())
					return GAIA::False;
				if(src.empty())
					return GAIA::True;
				if(this->size() + src.size() >= this->capacity())
					return GAIA::False;
				this->resize(this->size() + src.size());
				if(this->size() - src.size() - index != 0)
				{
					GAIA::ALGO::move_next(
						this->front_ptr() + this->size() - 1,
						this->front_ptr() + this->size() - src.size() - 1,
						this->size() - src.size() - index);
				}
				GAIA::ALGO::copy(this->front_ptr() + index, src.front_ptr(), src.size());
				return GAIA::True;
			}
			template<typename _ParamSizeType> GAIA::BL erase_index(const _ParamSizeType& index)
			{
				if(index >= 0 && index < this->size())
				{
					if(this->size() - index - 1 != 0)
						GAIA::ALGO::move_prev(this->front_ptr() + index, this->size() - index - 1);
					this->resize(this->size() - 1);
				}
				return GAIA::False;
			}
			template<typename _ParamSizeType1, typename _ParamSizeType2> GAIA::BL erase_index(const _ParamSizeType1& index_start, const _ParamSizeType2& index_end)
			{
				GAIA_AST(index_start <= index_end);
				if(index_start >= 0 && index_start < this->size() &&
					index_end >= index_start && index_end < this->size())
				{
					if(this->size() - index_start - 1 != 0)
					{
						GAIA::ALGO::move_prev(
							this->front_ptr() + index_start,
							this->front_ptr() + index_end + 1,
							this->size() - index_end - 1);
					}
					this->resize(this->size() - (index_end - index_start) - 1);
					return GAIA::True;
				}
				return GAIA::False;
			}
			template<typename _ParamDataType> _SizeType erase(const _ParamDataType& t, const _SizeType& index)
			{
				GAIA_AST(index >= 0 && index < this->size());
				_SizeType ret = 0;
				if(index >= 0 && index < this->size())
				{
					_SizeType tindex = index;
					while((tindex = this->find(t, tindex)) != GINVALID)
					{
						this->erase_index(tindex);
						++ret;
						++tindex;
					}
				}
				return ret;
			}
			template<typename _ParamDataType> _SizeType erase(const _ParamDataType* p, const _SizeType& index)
			{
				GAIA_AST(!!p);
				if(!p) return 0;
				GAIA_AST(index >= 0 && index < this->size());
				_SizeType ret = 0;
				if(index >= 0 && index < this->size())
				{
					_SizeType tindex = index;
					_SizeType len = GAIA::ALGO::strlen(p);
					while((tindex = this->find(p, tindex)) != GINVALID)
					{
						this->erase_index(tindex, tindex + len - 1);
						++ret;
						tindex += len;
					}
				}
				return ret;
			}
			GINL _SizeType erase(const __MyType& src, const _SizeType& index)
			{
				if(src.empty())
					return 0;
				GAIA_AST(index >= 0 && index < this->size());
				_SizeType ret = 0;
				if(index >= 0 && index < this->size())
				{
					_SizeType tindex = index;
					while((tindex = this->find(src, tindex)) != GINVALID)
					{
						this->erase_index(tindex, tindex + src.size() - 1);
						++ret;
						tindex += src.size();
					}
				}
				return ret;
			}
			template<typename _ParamDataType> _SizeType find(const _ParamDataType& t, const _SizeType& index) const
			{
				if(index >= this->size())
					return (_SizeType)GINVALID;
				if(this->empty())
					return (_SizeType)GINVALID;
				const _DataType* pFinded = GAIA::ALGO::find(this->front_ptr() + index, this->front_ptr() + this->size() - 1, t);
				if(pFinded == GNIL)
					return (_SizeType)GINVALID;
				return pFinded - this->front_ptr();
			}
			template<typename _ParamDataType> _SizeType find(const _ParamDataType* p, const _SizeType& index) const
			{
				GAIA_AST(!!p);
				if(p == GNIL)
					return (_SizeType)GINVALID;
				if(this->empty())
					return (_SizeType)GINVALID;
				if(index >= this->size())
					return (_SizeType)GINVALID;
				const _DataType* pFinded = GAIA::ALGO::strstr(this->front_ptr() + index, p);
				if(pFinded == GNIL)
					return (_SizeType)GINVALID;
				return pFinded - this->front_ptr();
			}
			GINL _SizeType find(const __MyType& src, const _SizeType& index) const
			{
				GAIA_AST(!src.empty());
				if(src.empty())
					return (_SizeType)GINVALID;
				if(this->empty())
					return (_SizeType)GINVALID;
				if(index >= this->size())
					return (_SizeType)GINVALID;
				const _DataType* pFinded = GAIA::ALGO::strstr(this->front_ptr() + index, src.front_ptr());
				if(pFinded == GNIL)
					return (_SizeType)GINVALID;
				return pFinded - this->front_ptr();
			}
			template<typename _ParamDataType> _SizeType rfind(const _ParamDataType& t, const _SizeType& index) const
			{
				if(this->empty())
					return (_SizeType)GINVALID;
				if(index >= this->size())
					return (_SizeType)GINVALID;
				const _DataType* pFinded = GAIA::ALGO::rfind(this->front_ptr(), this->front_ptr() + index, t);
				if(pFinded == GNIL)
					return (_SizeType)GINVALID;
				return pFinded - this->front_ptr();
			}
			template<typename _ParamDataType> _SizeType rfind(const _ParamDataType* p, const _SizeType& index) const
			{
				GAIA_AST(!!p);
				if(p == GNIL)
					return (_SizeType)GINVALID;
				if(this->empty())
					return (_SizeType)GINVALID;
				if(index >= this->size())
					return (_SizeType)GINVALID;
				const _DataType* pFinded = GAIA::ALGO::rfinds(this->front_ptr(), this->front_ptr() + index, p, GAIA::ALGO::strlen(p));
				if(pFinded == GNIL)
					return (_SizeType)GINVALID;
				return pFinded - this->front_ptr();
			}
			GINL _SizeType rfind(const __MyType& src, const _SizeType& index) const
			{
				GAIA_AST(!src.empty());
				if(src.empty())
					return (_SizeType)GINVALID;
				if(this->empty())
					return (_SizeType)GINVALID;
				if(index >= this->size())
					return (_SizeType)GINVALID;
				const _DataType* pFinded = GAIA::ALGO::rfinds(this->front_ptr(), this->front_ptr() + index, src.front_ptr(), src.size());
				if(pFinded == GNIL)
					return (_SizeType)GINVALID;
				return pFinded - this->front_ptr();
			}
			GINL _SizeType replace(const _DataType& src, const _DataType& dst)
			{
				if(this->empty())
					return 0;
				return GAIA::ALGO::replace(this->front_ptr(), this->size(), src, dst);
			}
			template<typename _ParamDataType> _SizeType replace(const _ParamDataType* pSrc, const _ParamDataType* pDst)
			{
				GAIA_AST(!!pSrc);
				GAIA_AST(!!pDst);
				if(this->empty())
					return 0;
				if(GAIA::ALGO::stremp(pSrc))
					return 0;
				_SizeType srclen = GAIA::ALGO::strlen(pSrc);
				if(srclen == 0)
					return 0;
				_SizeType dstlen = GAIA::ALGO::strlen(pDst);
				_SizeType ret = 0;
				_SizeType tindex = 0;
				while((tindex = this->find(pSrc, tindex)) != GINVALID)
				{
					this->erase_index(tindex, tindex + srclen - 1);
					if(dstlen != 0)
					{
						if(this->insert(pDst, tindex))
							tindex += dstlen + 1;
						else
							break;
					}
					else
						tindex += dstlen + 1;
					++ret;
				}
				return ret;
			}
			GINL _SizeType replace(const __MyType& src, const __MyType& dst)
			{
				if(this->empty())
					return 0;
				if(src.size() == 0)
					return 0;
				_SizeType ret = 0;
				_SizeType tindex = 0;
				while((tindex = this->find(src, tindex)) != GINVALID)
				{
					this->erase_index(tindex, tindex + src.size() - 1);
					if(dst.size() != 0)
					{
						if(this->insert(dst, tindex))
							tindex += dst.size() + 1;
						else
							break;
					}
					else
						tindex += dst.size() + 1;
					++ret;
				}
				return ret;
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
				GAIA::ALGO::move_prev(this->front_ptr(), this->front_ptr() + index + 1, this->size() - index);
				this->resize(this->size() - index - 1);
				return *this;
			}
			GINL __MyType& mid(const _SizeType& index_start, const _SizeType& index_end)
			{
				GAIA_AST(index_start <= index_end);
				if(index_start > index_end)
					return *this;
				if(index_start >= this->size())
					return *this;
				if(index_end >= this->size())
					return *this;
				_SizeType tempsize = index_end - index_start + 1;
				GAIA::ALGO::move_prev(this->front_ptr(), this->front_ptr() + index_start, tempsize);
				this->operator[](tempsize) = 0;
				this->resize(tempsize);
				return *this;
			}
			template<typename _ParamSizeType> GAIA::BL trim_left_index(const _ParamSizeType& index)
			{
				if(this->empty())
					return GAIA::False;
				if(index >= 0 && index <= this->size())
				{
					if(index != 0)
						this->right(index - 1);
					return GAIA::True;
				}
				return GAIA::False;
			}
			template<typename _ParamDataType> GAIA::BL trim_left(const _ParamDataType& t)
			{
				if(this->empty())
					return GAIA::False;
				const _DataType* pTemp = this->front_ptr();
				while(*pTemp != 0)
				{
					if(*pTemp != t)
						break;
					++pTemp;
				}
				if(pTemp == this->front_ptr())
					return GAIA::False;
				_SizeType newsize = this->size() - (pTemp - this->front_ptr());
				GAIA::ALGO::move_prev(this->front_ptr(), pTemp, newsize + 1);
				this->resize(newsize);
				return GAIA::True;
			}
			template<typename _ParamDataType> GAIA::BL trim_left(const _ParamDataType* p)
			{
				GAIA_AST(!!p);
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
				GAIA::ALGO::move_prev(this->front_ptr(), pTemp, newsize + 1);
				this->resize(newsize);
				return GAIA::True;
			}
			GINL GAIA::BL trim_left(const __MyType& src)
			{
				if(src.empty())
					return GAIA::False;
				return this->trim_left(src.front_ptr());
			}
			template<typename _ParamDataType> GAIA::BL trim_lefti(const _ParamDataType& t)
			{
				if(this->empty())
					return GAIA::False;
				const _DataType* pTemp = this->front_ptr();
				while(*pTemp != 0)
				{
					if(GAIA::ALGO::tolower(*pTemp) != GAIA::ALGO::tolower(t))
						break;
					++pTemp;
				}
				if(pTemp == this->front_ptr())
					return GAIA::False;
				_SizeType newsize = this->size() - (pTemp - this->front_ptr());
				GAIA::ALGO::move_prev(this->front_ptr(), pTemp, newsize + 1);
				this->resize(newsize);
				return GAIA::True;
			}
			template<typename _ParamDataType> GAIA::BL trim_lefti(const _ParamDataType* p)
			{
				GAIA_AST(!!p);
				if(this->empty())
					return GAIA::False;
				_DataType* pTemp = this->front_ptr();
				while(*pTemp != 0 && *p != 0)
				{
					if(GAIA::ALGO::tolower(*pTemp) != GAIA::ALGO::tolower(*p))
						break;
					++pTemp;
					++p;
				}
				if(pTemp == this->front_ptr())
					return GAIA::False;
				_SizeType newsize = this->size() - (pTemp - this->front_ptr());
				GAIA::ALGO::move_prev(this->front_ptr(), pTemp, newsize + 1);
				this->resize(newsize);
				return GAIA::True;
			}
			GINL GAIA::BL trim_lefti(const __MyType& src)
			{
				if(src.empty())
					return GAIA::False;
				return this->trim_lefti(src.front_ptr());
			}
			template<typename _ParamSizeType> GAIA::BL trim_right_index(const _ParamSizeType& index)
			{
				if(this->empty())
					return GAIA::False;
				if(index >= 0 && index < this->size())
				{
					this->left(index + 1);
					return GAIA::True;
				}
				return GAIA::False;
			}
			template<typename _ParamDataType> GAIA::BL trim_right(const _ParamDataType& t)
			{
				if(this->empty())
					return GAIA::False;
				it it = this->back_it();
				for(; !it.empty(); --it)
				{
					if(*it != t)
						break;
					*it = 0;
				}
				this->resize(this->size() - (this->back_it() - it));
				return GAIA::True;
			}
			template<typename _ParamDataType> GAIA::BL trim_right(const _ParamDataType* p)
			{
				GAIA_AST(!!p);
				if(this->empty())
					return GAIA::False;
				_SizeType len = GAIA::ALGO::strlen(p);
				if(len > this->size())
					return GAIA::False;
				_DataType* pTemp = this->front_ptr() + this->size() - len;
				if(GAIA::ALGO::strcmp(pTemp, p) == 0)
				{
					*pTemp = 0;
					this->resize(pTemp - this->front_ptr());
					return GAIA::True;
				}
				return GAIA::True;
			}
			GINL GAIA::BL trim_right(const __MyType& src)
			{
				if(src.empty())
					return GAIA::False;
				if(src.size() > this->size())
					return GAIA::False;
				_DataType* pTemp = this->front_ptr() + this->size() - src.size();
				if(GAIA::ALGO::strcmp(pTemp, src.front_ptr()) == 0)
				{
					*pTemp = 0;
					this->resize(pTemp - this->front_ptr());
					return GAIA::True;
				}
				return GAIA::True;
			}
			template<typename _ParamDataType> GAIA::BL trim_righti(const _ParamDataType& t)
			{
				if(this->empty())
					return GAIA::False;
				it it = this->back_it();
				for(; !it.empty(); --it)
				{
					if(GAIA::ALGO::tolower(*it) != GAIA::ALGO::tolower(t))
						break;
					*it = 0;
				}
				this->resize(this->size() - (this->back_it() - it));
				return GAIA::True;
			}
			template<typename _ParamDataType> GAIA::BL trim_righti(const _ParamDataType* p)
			{
				GAIA_AST(!!p);
				if(this->empty())
					return GAIA::False;
				_SizeType len = GAIA::ALGO::strlen(p);
				if(len > this->size())
					return GAIA::False;
				_DataType* pTemp = this->front_ptr() + this->size() - len;
				if(GAIA::ALGO::stricmp(pTemp, p) == 0)
				{
					*pTemp = 0;
					this->resize(pTemp - this->front_ptr());
					return GAIA::True;
				}
				return GAIA::True;
			}
			GINL GAIA::BL trim_righti(const __MyType& src)
			{
				if(src.empty())
					return GAIA::False;
				if(src.size() > this->size())
					return GAIA::False;
				_DataType* pTemp = this->front_ptr() + this->size() - src.size();
				if(GAIA::ALGO::stricmp(pTemp, src.front_ptr()) == 0)
				{
					*pTemp = 0;
					this->resize(pTemp - this->front_ptr());
					return GAIA::True;
				}
				return GAIA::True;
			}
			GINL GAIA::GVOID tolower(){if(this->front_ptr() != GNIL) GAIA::ALGO::tolowers(this->front_ptr());}
			GINL GAIA::GVOID toupper(){if(this->front_ptr() != GNIL) GAIA::ALGO::touppers(this->front_ptr());}
			GINL GAIA::BL isexistlower() const{if(this->front_ptr() != GNIL) return GAIA::ALGO::isexistlower(this->front_ptr()); return GAIA::False;}
			GINL GAIA::BL isexistupper() const{if(this->front_ptr() != GNIL) return GAIA::ALGO::isexistupper(this->front_ptr()); return GAIA::False;}
			GINL GAIA::BL isalllower() const{if(this->front_ptr() != GNIL) return GAIA::ALGO::isalllower(this->front_ptr()); return GAIA::False;}
			GINL GAIA::BL isallupper() const{if(this->front_ptr() != GNIL) return GAIA::ALGO::isallupper(this->front_ptr()); return GAIA::False;}
			GINL __MyType& operator = (const __MyType& src){GAIA_AST(&src != this); this->assign(src.front_ptr(), src.size()); return *this;}
			template<typename _ParamDataType> __MyType& operator = (const _ParamDataType* p){this->assign(p, (_SizeType)GAIA::ALGO::strlen(p)); return *this;}
			GINL __MyType& operator = (const GAIA::NM& t){_DataType sz[GAIA_DIGIT_TOSTRING_LEN]; GAIA::ALGO::int2str(t, sz); return this->operator = (sz);}
			GINL __MyType& operator = (const GAIA::N8& t){_DataType sz[GAIA_DIGIT_TOSTRING_LEN]; GAIA::ALGO::int2str(t, sz); return this->operator = (sz);}
			GINL __MyType& operator = (const GAIA::N16& t){_DataType sz[GAIA_DIGIT_TOSTRING_LEN]; GAIA::ALGO::int2str(t, sz); return this->operator = (sz);}
			GINL __MyType& operator = (const GAIA::N32& t){_DataType sz[GAIA_DIGIT_TOSTRING_LEN]; GAIA::ALGO::int2str(t, sz); return this->operator = (sz);}
			GINL __MyType& operator = (const GAIA::N64& t){_DataType sz[GAIA_DIGIT_TOSTRING_LEN]; GAIA::ALGO::int2str(t, sz); return this->operator = (sz);}
			GINL __MyType& operator = (const GAIA::UM& t){_DataType sz[GAIA_DIGIT_TOSTRING_LEN]; GAIA::ALGO::int2str(t, sz); return this->operator = (sz);}
			GINL __MyType& operator = (const GAIA::U8& t){_DataType sz[GAIA_DIGIT_TOSTRING_LEN]; GAIA::ALGO::int2str(t, sz); return this->operator = (sz);}
			GINL __MyType& operator = (const GAIA::U16& t){_DataType sz[GAIA_DIGIT_TOSTRING_LEN]; GAIA::ALGO::int2str(t, sz); return this->operator = (sz);}
			GINL __MyType& operator = (const GAIA::U32& t){_DataType sz[GAIA_DIGIT_TOSTRING_LEN]; GAIA::ALGO::int2str(t, sz); return this->operator = (sz);}
			GINL __MyType& operator = (const GAIA::U64& t){_DataType sz[GAIA_DIGIT_TOSTRING_LEN]; GAIA::ALGO::int2str(t, sz); return this->operator = (sz);}
			GINL __MyType& operator = (const GAIA::X128& t){if(!this->resize(32)) return *this; GAIA::ALGO::hex2str((const GAIA::U8*)&t, sizeof(t), this->front_ptr()); return *this;}
			GINL __MyType& operator = (const GAIA::F32& t){_DataType sz[GAIA_DIGIT_TOSTRING_LEN]; GAIA::ALGO::real2str(t, sz); return this->operator = (sz);}
			GINL __MyType& operator = (const GAIA::F64& t){_DataType sz[GAIA_DIGIT_TOSTRING_LEN]; GAIA::ALGO::real2str(t, sz); return this->operator = (sz);}
			GINL __MyType& operator = (const GAIA::BL& t){_DataType sz[GAIA_DIGIT_TOSTRING_LEN]; sz[0] = t ? '1' : '0'; sz[1] = '\0'; return this->operator = (sz);}
			template<typename _ParamSizeType> __MyType& operator = (const GAIA::CTN::BasicString<_DataType, _ParamSizeType>& src);
			GINL __MyType& operator += (const __MyType& src){return this->combin(src.front_ptr(), src.size());}
			template<typename _ParamDataType> __MyType& operator += (const _ParamDataType* p){return this->combin(p, GAIA::ALGO::strlen(p));}
			GINL __MyType operator + (const __MyType& src) const{return __MyType(this->front_ptr(), this->size(), src.front_ptr(), src.size());}
			template<typename _ParamDataType> __MyType operator + (const _ParamDataType* p) const{return __MyType(this->front_ptr(), this->size(), p, GAIA::ALGO::strlen(p));}
			GINL GAIA::BL operator == (const __MyType& src) const{if(this->size() != src.size()) return GAIA::False; return GAIA::ALGO::strcmp(this->front_ptr(), src.front_ptr()) == 0;}
			GINL GAIA::BL operator != (const __MyType& src) const{if(this->size() != src.size()) return GAIA::True; return GAIA::ALGO::strcmp(this->front_ptr(), src.front_ptr()) != 0;}
			GINL GAIA::BL operator >= (const __MyType& src) const{return GAIA::ALGO::strcmp(this->front_ptr(), src.front_ptr()) >= 0;}
			GINL GAIA::BL operator <= (const __MyType& src) const{return GAIA::ALGO::strcmp(this->front_ptr(), src.front_ptr()) <= 0;}
			GINL GAIA::BL operator > (const __MyType& src) const{return GAIA::ALGO::strcmp(this->front_ptr(), src.front_ptr()) > 0;}
			GINL GAIA::BL operator < (const __MyType& src) const{return GAIA::ALGO::strcmp(this->front_ptr(), src.front_ptr()) < 0;}
			template<typename _ParamDataType> GAIA::BL operator == (_ParamDataType p) const{return GAIA::ALGO::strcmp(this->front_ptr(), p) == 0;}
			template<typename _ParamDataType> GAIA::BL operator != (_ParamDataType p) const{return GAIA::ALGO::strcmp(this->front_ptr(), p) != 0;}
			template<typename _ParamDataType> GAIA::BL operator >= (_ParamDataType p) const{return GAIA::ALGO::strcmp(this->front_ptr(), p) >= 0;}
			template<typename _ParamDataType> GAIA::BL operator <= (_ParamDataType p) const{return GAIA::ALGO::strcmp(this->front_ptr(), p) <= 0;}
			template<typename _ParamDataType> GAIA::BL operator > (_ParamDataType p) const{return GAIA::ALGO::strcmp(this->front_ptr(), p) > 0;}
			template<typename _ParamDataType> GAIA::BL operator < (_ParamDataType p) const{return GAIA::ALGO::strcmp(this->front_ptr(), p) < 0;}
			template<typename _ParamSizeType> const _DataType& operator[](const _ParamSizeType& index) const{GAIA_AST(index <= this->size()); return this->front_ptr()[index];}
			template<typename _ParamSizeType> _DataType& operator[](const _ParamSizeType& index){GAIA_AST(index <= this->size()); return this->front_ptr()[index];}
			GINL operator _DataType*(){return this->front_ptr();}
			GINL operator const _DataType*() const{return this->front_ptr();}
			GINL operator GAIA::NM() const{return GAIA::ALGO::string_cast<NM>(this->front_ptr());}
			GINL operator GAIA::N8() const{return GAIA::ALGO::string_cast<N8>(this->front_ptr());}
			GINL operator GAIA::N16() const{return GAIA::ALGO::string_cast<N16>(this->front_ptr());}
			GINL operator GAIA::N32() const{return GAIA::ALGO::string_cast<N32>(this->front_ptr());}
			GINL operator GAIA::N64() const{return GAIA::ALGO::string_cast<N64>(this->front_ptr());}
			GINL operator GAIA::UM() const{return GAIA::ALGO::string_cast<UM>(this->front_ptr());}
			GINL operator GAIA::U8() const{return GAIA::ALGO::string_cast<U8>(this->front_ptr());}
			GINL operator GAIA::U16() const{return GAIA::ALGO::string_cast<U16>(this->front_ptr());}
			GINL operator GAIA::U32() const{return GAIA::ALGO::string_cast<U32>(this->front_ptr());}
			GINL operator GAIA::U64() const{return GAIA::ALGO::string_cast<U64>(this->front_ptr());}
			GINL operator GAIA::X128() const
			{
				X128 ret;
				if(this->empty())
				{
					ret.clear();
					return ret;
				}
				GAIA::ALGO::str2hex(this->front_ptr(), sizeof(ret), (GAIA::U8*)&ret);
				return ret;
			}
			GINL operator GAIA::F32() const{return GAIA::ALGO::string_cast<F32>(this->front_ptr());}
			GINL operator GAIA::F64() const{return GAIA::ALGO::string_cast<F64>(this->front_ptr());}
			GINL operator GAIA::BL() const{return GAIA::ALGO::string_cast<BL>(this->front_ptr());}
			template<typename _ParamDataType, typename _ParamSizeType> __MyType& combin(const _ParamDataType* p, const _ParamSizeType& size)
			{
				if(p == GNIL)
					return *this;
				if(*p == 0)
					return *this;
				if(size == 0)
					return *this;
				if(this->capacity() - this->size() >= size)
				{
					GAIA::ALGO::strcpy(this->front_ptr() + this->size(), p);
					this->resize(this->size() + size);
				}
				return *this;
			}
			template<typename _ParamDataType1, typename _ParamSizeType1, typename _ParamDataType2, typename _ParamSizeType2> __MyType& combin(const _ParamDataType1* p1, const _ParamSizeType1& size1, const _ParamDataType2* p2, const _ParamSizeType2& size2)
			{
				if(size1 + size2 + 1 > _Size)
					return *this;
				GAIA::BL bEmpty1 = p1 == GNIL || *p1 == 0 || size1 == 0;
				GAIA::BL bEmpty2 = p2 == GNIL || *p2 == 0 || size2 == 0;
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
					GAIA::ALGO::strcpy(this->front_ptr() + this->size(), p2);
					this->resize(size1 + size2);
					return *this;
				}
			}
		private:
			GINL GAIA::GVOID init(){m_chars[0] = 0; m_size = 0;}
		private:
			_DataType m_chars[_Size + 1];
			_SizeType m_size;
		};
		template<typename _DataType1, typename _DataType2, typename _SizeType, _SizeType size> GAIA::CTN::BasicChars<_DataType2, _SizeType, size>
			operator + (_DataType1 p, const GAIA::CTN::BasicChars<_DataType2, _SizeType, size>& chars)
		{
			GAIA::CTN::BasicChars<_DataType2, _SizeType, size> ret = p;
			ret += chars;
			return ret;
		}
	};
};

#endif
