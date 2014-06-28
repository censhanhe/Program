#ifndef		__GAIA_CONTAINER_BASICSTRING_H__
#define		__GAIA_CONTAINER_BASICSTRING_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template<typename _DataType, typename _SizeType> class BasicString : public GAIA::Entity
		{
		public:
			typedef _DataType _datatype;
			typedef _SizeType _sizetype;
		public:
			typedef BasicString<_DataType, _SizeType> __MyType;
		private:
			static const GAIA::U32 GAIA_DIGIT_TOSTRING_LEN = 64;
		public:
			class it : public GAIA::ITERATOR::Iterator<_DataType>
			{
			private:
				friend class BasicString;
			public:
				GINL it(){this->init();}
				GINL virtual ~it(){}
				GINL virtual GAIA::BL empty() const{return m_pContainer == GNULL;}
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
					if(m_pContainer == GNULL)
						return *this;
					m_index += c;
					if(m_index >= m_pContainer->size() || m_index < 0)
						this->init();
					return *this;
				}
				GINL it& operator -= (const _SizeType& c)
				{
					if(m_pContainer == GNULL)
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
				GINL GAIA::GVOID init(){m_pContainer = GNULL; m_index = 0;}
			private:
				_SizeType m_index;
				__MyType* m_pContainer;
			};
			class const_it : public GAIA::ITERATOR::ConstIterator<_DataType>
			{
			private:
				friend class BasicString;
			public:
				GINL const_it(){this->init();}
				GINL virtual ~const_it(){}
				GINL virtual GAIA::BL empty() const{return m_pContainer == GNULL;}
				GINL virtual const _DataType& operator * () const{GAIA_AST(!!m_pContainer); return (*m_pContainer)[m_index];}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator ++ (){GAIA_AST(!!m_pContainer); ++m_index; if(m_index >= m_pContainer->size()) this->init(); return *this;}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator -- (){GAIA_AST(!!m_pContainer); --m_index; if(m_index >= m_pContainer->size() || m_index < 0) this->init(); return *this;}
				GINL virtual GAIA::ITERATOR::ConstIterator<_DataType>& operator = (const GAIA::ITERATOR::ConstIterator<_DataType>& src){GAIA_AST(&src != this); return this->operator = (*static_cast<const const_it*>(&src));}
				GINL virtual GAIA::BL operator == (const GAIA::ITERATOR::ConstIterator<_DataType>& src) const{return this->operator == (*static_cast<const const_it*>(&src));}
				GINL virtual GAIA::BL operator != (const GAIA::ITERATOR::ConstIterator<_DataType>& src) const{return this->operator != (*static_cast<const const_it*>(&src));}
				GINL const_it& operator = (const const_it& src){GAIA_AST(&src != this); m_index = src.m_index; m_pContainer = src.m_pContainer; return *this;}
				GINL const_it& operator += (const _SizeType& c)
				{
					if(m_pContainer == GNULL)
						return *this;
					m_index += c;
					if(m_index >= m_pContainer->size() || m_index < 0)
						this->init();
					return *this;
				}
				GINL const_it& operator -= (const _SizeType& c)
				{
					if(m_pContainer == GNULL)
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
				GINL GAIA::GVOID init(){m_pContainer = GNULL; m_index = 0;}
			private:
				_SizeType m_index;
				const __MyType* m_pContainer;
			};
		public:
			GINL BasicString(){this->init();}
			GINL BasicString(const _DataType* p){this->init(); this->operator = (p);}
			GINL BasicString(const __MyType& src){this->init(); this->operator = (src);}
			GINL BasicString(const GAIA::NM& t){this->init(); this->operator = (t);}
			GINL BasicString(const GAIA::N8& t){this->init(); this->operator = (t);}
			GINL BasicString(const GAIA::N16& t){this->init(); this->operator = (t);}
			GINL BasicString(const GAIA::N32& t){this->init(); this->operator = (t);}
			GINL BasicString(const GAIA::N64& t){this->init(); this->operator = (t);}
			GINL BasicString(const GAIA::UM& t){this->init(); this->operator = (t);}
			GINL BasicString(const GAIA::U8& t){this->init(); this->operator = (t);}
			GINL BasicString(const GAIA::U16& t){this->init(); this->operator = (t);}
			GINL BasicString(const GAIA::U32& t){this->init(); this->operator = (t);}
			GINL BasicString(const GAIA::U64& t){this->init(); this->operator = (t);}
			GINL BasicString(const GAIA::X128& t){this->init(); this->operator = (t);}
			GINL BasicString(const GAIA::F32& t){this->init(); this->operator = (t);}
			GINL BasicString(const GAIA::F64& t){this->init(); this->operator = (t);}
			GINL BasicString(const GAIA::BL& t){this->init(); this->operator = (t);}
			GINL BasicString(const _DataType* p1, const _SizeType& size1, const _DataType* p2, const _SizeType& size2){this->init(); this->combin(p1, size1, p2, size2);}
			template<typename _ParamSizeType, _ParamSizeType _Size> BasicString(const GAIA::CONTAINER::BasicChars<_DataType, _ParamSizeType, _Size>& src){this->operator = (src);}
			GINL ~BasicString(){this->destroy();}
			GINL GAIA::BL empty() const{if(this->size() == 0) return GAIA::True; return this->front_ptr()[0] == 0;}
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
				if(m_pFront != GNULL)
					m_pFront[size] = 0;
			}
			GINL GAIA::GVOID reserve(const _SizeType& size)
			{
				this->destroy();
				if(size > 0)
				{
					m_capacity = size + 1;
					m_size = 0;
			#ifdef GAIA_MODULE_BASEDATATYPEONLY
					m_pFront = GAIA_MALLOC(_DataType, m_capacity);
			#else
					m_pFront = new _DataType[m_capacity];
			#endif
					m_pFront[size] = 0;
				}
			}
			GINL GAIA::GVOID clear(){m_size = 0; if(m_pFront != GNULL) m_pFront[0] = 0;}
			GINL GAIA::GVOID destroy()
			{
				m_size = m_capacity = 0;
				if(m_pFront != GNULL)
				{
				#ifdef GAIA_MODULE_BASEDATATYPEONLY
					GAIA_MFREE(m_pFront);
				#else
					delete[] m_pFront;
				#endif
					m_pFront = GNULL;
				}
			}
			GINL GAIA::U32 type() const{return GAIA::ALGORITHM::strtype(m_pFront);}
			GINL _DataType* front_ptr(){return m_pFront;}
			GINL _DataType* back_ptr(){if(this->empty()) return GNULL; return m_pFront + this->size() - 1;}
			GINL const _DataType* front_ptr() const{return m_pFront;}
			GINL const _DataType* back_ptr() const{if(this->empty()) return GNULL; return m_pFront + this->size() - 1;}
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
					ret.m_pContainer = GNULL;
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
					ret.m_pContainer = GNULL;
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
					ret.m_pContainer = GNULL;
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
					ret.m_pContainer = GNULL;
				}
				else
				{
					ret.m_index = this->size() - 1;
					ret.m_pContainer = this;
				}
				return ret;
			}
			GINL GAIA::GVOID inverse(){if(this->size() > 1) GAIA::ALGORITHM::inverse(m_pFront, m_pFront + this->size() - 1);}
			GINL GAIA::BL insert(const _DataType& t, const _SizeType& index)
			{
				if(index > this->size())
					return GAIA::False;
				if(this->size() == this->capacity())
					this->exten(1);
				this->resize(this->size() + 1);
				if(this->size() - 1 - index != 0)
				{
					GAIA::ALGORITHM::move_next(
						this->front_ptr() + this->size() - 1,
 						this->size() - 1 - index);
				}
				this->operator[](index) = t;
				return GAIA::True;
			}
			GINL GAIA::BL insert(const _DataType* p, const _SizeType& index)
			{
				if(index > this->size())
					return GAIA::False;
				GAIA_AST(!!p);
				if(p == GNULL)
					return GAIA::False;
				if(*p == 0)
					return GAIA::True;
				_SizeType newsize = GAIA::ALGORITHM::strlen(p);
				if(this->size() == this->capacity())
					this->exten(newsize);
				this->resize(this->size() + newsize);
				if(this->size() - newsize - index != 0)
				{
					GAIA::ALGORITHM::move_next(
						this->front_ptr() + this->size() - 1,
						this->front_ptr() + this->size() - newsize - 1,
						this->size() - newsize - index);
				}
				GAIA::ALGORITHM::copy(this->front_ptr() + index, p, newsize);
				return GAIA::True;
			}
			GINL GAIA::BL insert(const __MyType& src, const _SizeType& index)
			{
				if(index > this->size())
					return GAIA::False;
				if(src.empty())
					return GAIA::True;
				if(this->size() == this->capacity())
					this->exten(src.size());
				this->resize(this->size() + src.size());
				if(this->size() - src.size() - index != 0)
				{
					GAIA::ALGORITHM::move_next(
						this->front_ptr() + this->size() - 1,
						this->front_ptr() + this->size() - src.size() - 1,
						this->size() - src.size() - index);
				}
				GAIA::ALGORITHM::copy(this->front_ptr() + index, src.front_ptr(), src.size());
				return GAIA::True;
			}
			template<typename _ParamSizeType> GINL GAIA::BL erase_index(const _ParamSizeType& index)
			{
				if(index >= 0 && index < this->size())
				{
					if(this->size() - index - 1 != 0)
						GAIA::ALGORITHM::move_prev(this->front_ptr() + index, this->size() - index - 1);
					this->resize(this->size() - 1);
				}
				return GAIA::False;
			}
			template<typename _ParamSizeType1, typename _ParamSizeType2> GINL GAIA::BL erase_index(const _ParamSizeType1& index_start, const _ParamSizeType2& index_end)
			{
				GAIA_AST(index_start <= index_end);
				if(index_start >= 0 && index_start < this->size() &&
					index_end >= index_start && index_end < this->size())
				{
					if(this->size() - index_start - 1 != 0)
					{
						GAIA::ALGORITHM::move_prev(
							this->front_ptr() + index_start,
							this->front_ptr() + index_end + 1,
							this->size() - index_end - 1);
					}
					this->resize(this->size() - (index_end - index_start) - 1);
					return GAIA::True;
				}
				return GAIA::False;
			}
			GINL _SizeType erase(const _DataType& t, const _SizeType& index)
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
			GINL _SizeType erase(const _DataType* p, const _SizeType& index)
			{
				GAIA_AST(!!p);
				if(!p) return 0;
				GAIA_AST(index >= 0 && index < this->size());
				_SizeType ret = 0;
				if(index >= 0 && index < this->size())
				{
					_SizeType tindex = index;
					_SizeType len = GAIA::ALGORITHM::strlen(p);
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
			GINL _SizeType find(const _DataType& t, const _SizeType& index) const
			{
				if(this->empty())
					return (_SizeType)GINVALID;
				if(index >= this->size())
					return (_SizeType)GINVALID;
				const _DataType* pFinded = GAIA::ALGORITHM::find(this->front_ptr() + index, this->back_ptr() + 1, t);
				if(pFinded == GNULL)
					return (_SizeType)GINVALID;
				return pFinded - m_pFront;
			}
			GINL _SizeType find(const _DataType* p, const _SizeType& index) const
			{
				GAIA_AST(!!p);
				if(p == GNULL)
					return (_SizeType)GINVALID;
				if(this->empty())
					return (_SizeType)GINVALID;
				if(index >= this->size())
					return (_SizeType)GINVALID;
				const _DataType* pFinded = GAIA::ALGORITHM::strstr(m_pFront + index, p);
				if(pFinded == GNULL)
					return (_SizeType)GINVALID;
				return pFinded - m_pFront;
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
				const _DataType* pFinded = GAIA::ALGORITHM::strstr(m_pFront + index, src.front_ptr());
				if(pFinded == GNULL)
					return (_SizeType)GINVALID;
				return pFinded - m_pFront;
			}
			GINL _SizeType rfind(const _DataType& t, const _SizeType& index) const
			{
				if(this->empty())
					return (_SizeType)GINVALID;
				if(index >= this->size())
					return (_SizeType)GINVALID;
				const _DataType* pFinded = GAIA::ALGORITHM::rfind(m_pFront, m_pFront + index, t);
				if(pFinded == GNULL)
					return (_SizeType)GINVALID;
				return pFinded - m_pFront;
			}
			GINL _SizeType rfind(const _DataType* p, const _SizeType& size, const _SizeType& index) const
			{
				GAIA_AST(!!p);
				if(p == GNULL)
					return (_SizeType)GINVALID;
				if(this->empty())
					return (_SizeType)GINVALID;
				if(index >= this->size())
					return (_SizeType)GINVALID;
				const _DataType* pFinded = GAIA::ALGORITHM::rfinds(m_pFront, m_pFront + index, p, size);
				if(pFinded == GNULL)
					return (_SizeType)GINVALID;
				return pFinded - m_pFront;
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
				const _DataType* pFinded = GAIA::ALGORITHM::rfinds(m_pFront, m_pFront + index, src.front_ptr(), src.size());
				if(pFinded == GNULL)
					return (_SizeType)GINVALID;
				return pFinded - m_pFront;
			}
			GINL _SizeType replace(const _DataType& src, const _DataType& dst)
			{
				if(this->empty())
					return 0;
				return GAIA::ALGORITHM::replace(this->front_ptr(), this->size(), src, dst);
			}
			GINL _SizeType replace(const _DataType* pSrc, const _DataType* pDst)
			{
				GAIA_AST(!!pSrc);
				GAIA_AST(!!pDst);
				if(this->empty())
					return 0;
				if(GAIA::ALGORITHM::stremp(pSrc))
					return 0;
				_SizeType srclen = GAIA::ALGORITHM::strlen(pSrc);
				if(srclen == 0)
					return 0;
				_SizeType dstlen = GAIA::ALGORITHM::strlen(pDst);
				_SizeType ret = 0;
				_SizeType tindex = 0;
				while((tindex = this->find(pSrc, tindex)) != GINVALID)
				{
					this->erase_index(tindex, tindex + srclen - 1);
					if(dstlen != 0)
						this->insert(pDst, tindex);
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
						this->insert(dst, tindex);
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
				GAIA::ALGORITHM::move_prev(this->front_ptr(), this->front_ptr() + index + 1, this->size() - index);
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
				GAIA::ALGORITHM::move_prev(this->front_ptr(), this->front_ptr() + index_start, tempsize);
				this->operator[](tempsize) = 0;
				this->resize(tempsize);
				return *this;
			}
			template<typename _ParamSizeType> GINL GAIA::BL trim_left(const _ParamSizeType& index)
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
			GINL GAIA::BL trim_left(const _DataType& t)
			{
				if(this->empty())
					return GAIA::False;
				_DataType* pTemp = m_pFront;
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
			GINL GAIA::BL trim_lefti(const _DataType& t)
			{
				if(this->empty())
					return GAIA::False;
				_DataType* pTemp = m_pFront;
				while(*pTemp != 0)
				{
					if(GAIA::ALGORITHM::tolower(*pTemp) != GAIA::ALGORITHM::tolower(t))
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
			GINL GAIA::BL trim_lefti(const _DataType* p)
			{
				GAIA_AST(!!p);
				if(this->empty())
					return GAIA::False;
				_DataType* pTemp = this->front_ptr();
				while(*pTemp != 0 && *p != 0)
				{
					if(GAIA::ALGORITHM::tolower(*pTemp) != GAIA::ALGORITHM::tolower(*p))
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
			GINL GAIA::BL trim_lefti(const __MyType& src)
			{
				if(src.empty())
					return GAIA::False;
				return this->trim_lefti(src.front_ptr());
			}
			template<typename _ParamSizeType> GINL GAIA::BL trim_right(const _ParamSizeType& index)
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
			GINL GAIA::BL trim_right(const _DataType& t)
			{
				if(this->empty())
					return GAIA::False;
				it it = this->back_it();
				while(!it.empty())
				{
					if(*it != t)
						break;
					*it = 0;
					--it;
				}
				this->resize(this->size() - (this->back_it() - it));
				return GAIA::True;
			}
			GINL GAIA::BL trim_right(const _DataType* p)
			{
				GAIA_AST(!!p);
				if(this->empty())
					return GAIA::False;
				_SizeType len = GAIA::ALGORITHM::strlen(p);
				if(len > this->size())
					return GAIA::False;
				_DataType* pTemp = this->front_ptr() + this->size() - len;
				if(GAIA::ALGORITHM::strcmp(pTemp, p) == 0)
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
				if(GAIA::ALGORITHM::strcmp(pTemp, src.front_ptr()) == 0)
				{
					*pTemp = 0;
					this->resize(pTemp - this->front_ptr());
					return GAIA::True;
				}
				return GAIA::True;
			}
			GINL GAIA::BL trim_righti(const _DataType& t)
			{
				if(this->empty())
					return GAIA::False;
				it it = this->back_it();
				while(!it.empty())
				{
					if(GAIA::ALGORITHM::tolower(*it) != GAIA::ALGORITHM::tolower(t))
						break;
					*it = 0;
					--it;
				}
				this->resize(this->size() - (this->back_it() - it));
				return GAIA::True;
			}
			GINL GAIA::BL trim_righti(const _DataType* p)
			{
				GAIA_AST(!!p);
				if(this->empty())
					return GAIA::False;
				_SizeType len = GAIA::ALGORITHM::strlen(p);
				if(len > this->size())
					return GAIA::False;
				_DataType* pTemp = this->front_ptr() + this->size() - len;
				if(GAIA::ALGORITHM::stricmp(pTemp, p) == 0)
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
				if(GAIA::ALGORITHM::stricmp(pTemp, src.front_ptr()) == 0)
				{
					*pTemp = 0;
					this->resize(pTemp - this->front_ptr());
					return GAIA::True;
				}
				return GAIA::True;
			}
			GINL GAIA::GVOID tolower(){if(m_pFront != GNULL) GAIA::ALGORITHM::tolowers(m_pFront);}
			GINL GAIA::GVOID toupper(){if(m_pFront != GNULL) GAIA::ALGORITHM::touppers(m_pFront);}
			GINL GAIA::BL isexistlower() const{if(m_pFront != GNULL) return GAIA::ALGORITHM::isexistlower(m_pFront); return GAIA::False;}
			GINL GAIA::BL isexistupper() const{if(m_pFront != GNULL) return GAIA::ALGORITHM::isexistupper(m_pFront); return GAIA::False;}
			GINL GAIA::BL isalllower() const{if(m_pFront != GNULL) return GAIA::ALGORITHM::isalllower(m_pFront); return GAIA::False;}
			GINL GAIA::BL isallupper() const{if(m_pFront != GNULL) return GAIA::ALGORITHM::isallupper(m_pFront); return GAIA::False;}
			GINL __MyType& operator = (const __MyType& src){GAIA_AST(&src != this); this->assign(src, src.size()); return *this;}
			GINL __MyType& operator = (const _DataType* p){this->assign(p, (_SizeType)GAIA::ALGORITHM::strlen(p)); return *this;}
			GINL __MyType& operator = (const GAIA::NM& t){_DataType sz[GAIA_DIGIT_TOSTRING_LEN]; GAIA::ALGORITHM::int2str(t, sz); return this->operator = (sz);}
			GINL __MyType& operator = (const GAIA::N8& t){_DataType sz[GAIA_DIGIT_TOSTRING_LEN]; GAIA::ALGORITHM::int2str(t, sz); return this->operator = (sz);}
			GINL __MyType& operator = (const GAIA::N16& t){_DataType sz[GAIA_DIGIT_TOSTRING_LEN]; GAIA::ALGORITHM::int2str(t, sz); return this->operator = (sz);}
			GINL __MyType& operator = (const GAIA::N32& t){_DataType sz[GAIA_DIGIT_TOSTRING_LEN]; GAIA::ALGORITHM::int2str(t, sz); return this->operator = (sz);}
			GINL __MyType& operator = (const GAIA::N64& t){_DataType sz[GAIA_DIGIT_TOSTRING_LEN]; GAIA::ALGORITHM::int2str(t, sz); return this->operator = (sz);}
			GINL __MyType& operator = (const GAIA::UM& t){_DataType sz[GAIA_DIGIT_TOSTRING_LEN]; GAIA::ALGORITHM::int2str(t, sz); return this->operator = (sz);}
			GINL __MyType& operator = (const GAIA::U8& t){_DataType sz[GAIA_DIGIT_TOSTRING_LEN]; GAIA::ALGORITHM::int2str(t, sz); return this->operator = (sz);}
			GINL __MyType& operator = (const GAIA::U16& t){_DataType sz[GAIA_DIGIT_TOSTRING_LEN]; GAIA::ALGORITHM::int2str(t, sz); return this->operator = (sz);}
			GINL __MyType& operator = (const GAIA::U32& t){_DataType sz[GAIA_DIGIT_TOSTRING_LEN]; GAIA::ALGORITHM::int2str(t, sz); return this->operator = (sz);}
			GINL __MyType& operator = (const GAIA::U64& t){_DataType sz[GAIA_DIGIT_TOSTRING_LEN]; GAIA::ALGORITHM::int2str(t, sz); return this->operator = (sz);}
			GINL __MyType& operator = (const GAIA::X128& t)
			{
				this->resize(32);
				GAIA::ALGORITHM::hex2str((const GAIA::U8*)&t, sizeof(t), this->front_ptr());
				return *this;
			}
			GINL __MyType& operator = (const GAIA::F32& t){_DataType sz[GAIA_DIGIT_TOSTRING_LEN]; GAIA::ALGORITHM::real2str(t, sz); return this->operator = (sz);}
			GINL __MyType& operator = (const GAIA::F64& t){_DataType sz[GAIA_DIGIT_TOSTRING_LEN]; GAIA::ALGORITHM::real2str(t, sz); return this->operator = (sz);}
			GINL __MyType& operator = (const GAIA::BL& t){_DataType sz[GAIA_DIGIT_TOSTRING_LEN]; GAIA::ALGORITHM::int2str(t, sz); return this->operator = (sz);}
			template<typename _ParamSizeType, _ParamSizeType _Size> __MyType& operator = (const GAIA::CONTAINER::BasicChars<_DataType, _ParamSizeType, _Size>& src);
			GINL __MyType& operator += (const __MyType& src){return this->combin(src, src.size());}
			GINL __MyType& operator += (const _DataType* p){return this->combin(p, GAIA::ALGORITHM::strlen(p));}
			GINL __MyType operator + (const __MyType& src) const{return __MyType(this->front_ptr(), this->size(), src.front_ptr(), src.size());}
			GINL __MyType operator + (const _DataType* p) const{return __MyType(this->front_ptr(), this->size(), p, GAIA::ALGORITHM::strlen(p));}
			GINL GAIA::BL operator == (const __MyType& src) const{if(this->size() != src.size()) return GAIA::False; return GAIA::ALGORITHM::strcmp(this->front_ptr(), src.front_ptr()) == 0;}
			GINL GAIA::BL operator != (const __MyType& src) const{if(this->size() != src.size()) return GAIA::True; return GAIA::ALGORITHM::strcmp(this->front_ptr(), src.front_ptr()) != 0;}
			GINL GAIA::BL operator >= (const __MyType& src) const{return GAIA::ALGORITHM::strcmp(this->front_ptr(), src.front_ptr()) >= 0;}
			GINL GAIA::BL operator <= (const __MyType& src) const{return GAIA::ALGORITHM::strcmp(this->front_ptr(), src.front_ptr()) <= 0;}
			GINL GAIA::BL operator > (const __MyType& src) const{return GAIA::ALGORITHM::strcmp(this->front_ptr(), src.front_ptr()) > 0;}
			GINL GAIA::BL operator < (const __MyType& src) const{return GAIA::ALGORITHM::strcmp(this->front_ptr(), src.front_ptr()) < 0;}
			template<typename _ParamDataType> GINL GAIA::BL operator == (_ParamDataType p) const{return GAIA::ALGORITHM::strcmp(this->front_ptr(), p) == 0;}
			template<typename _ParamDataType> GINL GAIA::BL operator != (_ParamDataType p) const{return GAIA::ALGORITHM::strcmp(this->front_ptr(), p) != 0;}
			template<typename _ParamDataType> GINL GAIA::BL operator >= (_ParamDataType p) const{return GAIA::ALGORITHM::strcmp(this->front_ptr(), p) >= 0;}
			template<typename _ParamDataType> GINL GAIA::BL operator <= (_ParamDataType p) const{return GAIA::ALGORITHM::strcmp(this->front_ptr(), p) <= 0;}
			template<typename _ParamDataType> GINL GAIA::BL operator > (_ParamDataType p) const{return GAIA::ALGORITHM::strcmp(this->front_ptr(), p) > 0;}
			template<typename _ParamDataType> GINL GAIA::BL operator < (_ParamDataType p) const{return GAIA::ALGORITHM::strcmp(this->front_ptr(), p) < 0;}
			template<typename _ParamSizeType> GINL const _DataType& operator[](const _ParamSizeType& index) const{GAIA_AST(index <= this->size()); return m_pFront[index];}
			template<typename _ParamSizeType> GINL _DataType& operator[](const _ParamSizeType& index){GAIA_AST(index <= this->size()); return m_pFront[index];}
			GINL operator _DataType*(){return m_pFront;}
			GINL operator const _DataType*() const{return m_pFront;}
			GINL operator GAIA::NM() const{return GAIA::ALGORITHM::string_cast<NM>(m_pFront);}
			GINL operator GAIA::N8() const{return GAIA::ALGORITHM::string_cast<N8>(m_pFront);}
			GINL operator GAIA::N16() const{return GAIA::ALGORITHM::string_cast<N16>(m_pFront);}
			GINL operator GAIA::N32() const{return GAIA::ALGORITHM::string_cast<N32>(m_pFront);}
			GINL operator GAIA::N64() const{return GAIA::ALGORITHM::string_cast<N64>(m_pFront);}
			GINL operator GAIA::UM() const{return GAIA::ALGORITHM::string_cast<UM>(m_pFront);}
			GINL operator GAIA::U8() const{return GAIA::ALGORITHM::string_cast<U8>(m_pFront);}
			GINL operator GAIA::U16() const{return GAIA::ALGORITHM::string_cast<U16>(m_pFront);}
			GINL operator GAIA::U32() const{return GAIA::ALGORITHM::string_cast<U32>(m_pFront);}
			GINL operator GAIA::U64() const{return GAIA::ALGORITHM::string_cast<U64>(m_pFront);}
			GINL operator GAIA::X128() const
			{
				X128 ret;
				if(this->empty())
				{
					ret.clear();
					return ret;
				}
				GAIA::ALGORITHM::str2hex(this->front_ptr(), sizeof(ret), (GAIA::U8*)&ret);
				return ret;
			}
			GINL operator GAIA::F32() const{return GAIA::ALGORITHM::string_cast<F32>(m_pFront);}
			GINL operator GAIA::F64() const{return GAIA::ALGORITHM::string_cast<F64>(m_pFront);}
			GINL operator GAIA::BL() const{return GAIA::ALGORITHM::string_cast<BL>(m_pFront);}
		private:
			GINL GAIA::GVOID init(){m_pFront = GNULL; m_size = m_capacity = 0;}
			GINL GAIA::GVOID exten(const _SizeType& size)
			{
				GAIA_AST(size >= 0);
				if(size == 0)
					return;
			#ifdef GAIA_MODULE_BASEDATATYPEONLY
				_DataType* pNew = GAIA_MALLOC(_DataType, this->capacity() + size + 1);
			#else
				_DataType* pNew = new _DataType[this->capacity() + size + 1];
			#endif
				if(!this->empty())
					GAIA::ALGORITHM::strcpy(pNew, this->front_ptr());
				m_capacity = this->capacity() + size + 1;
				if(m_pFront != GNULL)
			#ifdef GAIA_MODULE_BASEDATATYPEONLY
					GAIA_MFREE(m_pFront);
			#else
					delete[] m_pFront;
			#endif
				m_pFront = pNew;
			}
			GINL __MyType& assign(const _DataType* p, const _SizeType& size)
			{
				if(p == GNULL || size == 0)
				{
					this->clear();
					return *this;
				}
				this->clear();
				this->resize(size);
				GAIA::ALGORITHM::strcpy(m_pFront, p);
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
				else
				{
					this->exten(size - (this->capacity() - this->size()));
					GAIA::ALGORITHM::strcpy(this->front_ptr() + this->size(), p);
					this->resize(this->size() + size);
				}
				return *this;
			}
			GINL __MyType& combin(const _DataType* p1, const _SizeType& size1, const _DataType* p2, const _SizeType& size2)
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
					GAIA::ALGORITHM::strcpy(this->front_ptr() + this->size(), p2);
					this->resize(size1 + size2);
					return *this;
				}
			}
		private:
			_DataType* m_pFront;
			_SizeType m_size;
			_SizeType m_capacity;
		};
		template<typename _DataType1, typename _DataType2, typename _SizeType> GAIA::CONTAINER::BasicString<_DataType2, _SizeType>
			operator + (_DataType1 p, const GAIA::CONTAINER::BasicString<_DataType2, _SizeType>& str)
		{
			GAIA::CONTAINER::BasicString<_DataType2, _SizeType> ret = p;
			ret += str;
			return ret;
		}
	};
};

#endif
