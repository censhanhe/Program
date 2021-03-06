#ifndef		__GAIA_CONTAINER_BASICCHARSSTRING_H__
#define		__GAIA_CONTAINER_BASICCHARSSTRING_H__

namespace GAIA
{
	namespace CTN
	{
		template<typename _DataType, typename _SizeType, _SizeType _Size> class BasicCharsString : public GAIA::Entity
		{
		public:
			typedef _DataType _datatype;
			typedef _SizeType _sizetype;
		public:
			typedef BasicCharsString<_DataType, _SizeType, _Size> __MyType;
		private:
			static const GAIA::U32 GAIA_DIGIT_TOSTRING_LEN = 64;
			static const _SizeType _size = _Size;
		public:
			class it : public GAIA::ITERATOR::Iterator<_DataType>
			{
			private:
				friend class BasicCharsString;
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
				friend class BasicCharsString;
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
			GINL BasicCharsString(){}
			template<typename _ParamDataType> BasicCharsString(const _ParamDataType* p){this->operator = (p);}
			GINL BasicCharsString(const __MyType& src){this->operator = (src);}
			GINL BasicCharsString(const GAIA::NM& t){this->operator = (t);}
			GINL BasicCharsString(const GAIA::N8& t){this->operator = (t);}
			GINL BasicCharsString(const GAIA::N16& t){this->operator = (t);}
			GINL BasicCharsString(const GAIA::N32& t){this->operator = (t);}
			GINL BasicCharsString(const GAIA::N64& t){this->operator = (t);}
			GINL BasicCharsString(const GAIA::UM& t){this->operator = (t);}
			GINL BasicCharsString(const GAIA::U8& t){this->operator = (t);}
			GINL BasicCharsString(const GAIA::U16& t){this->operator = (t);}
			GINL BasicCharsString(const GAIA::U32& t){this->operator = (t);}
			GINL BasicCharsString(const GAIA::U64& t){this->operator = (t);}
			GINL BasicCharsString(const GAIA::X128& t){this->operator = (t);}
			GINL BasicCharsString(const GAIA::F32& t){this->operator = (t);}
			GINL BasicCharsString(const GAIA::F64& t){this->operator = (t);}
			GINL BasicCharsString(const GAIA::BL& t){this->operator = (t);}
			template<typename _ParamDataType1, typename _ParamSizeType1, typename _ParamDataType2, typename _ParamSizeType2> BasicCharsString(const _ParamDataType1* p1, const _ParamSizeType1& size1, const _ParamDataType2* p2, const _ParamSizeType2& size2)
			{
				if(size1 + size2 > m_chars.capacity())
					m_string.combin(p1, size1, p2, size2);
				else
					m_chars.combin(p1, size1, p2, size2);
			}
			template<typename _ParamSizeType, _ParamSizeType _ParamSize> BasicCharsString(const GAIA::CTN::BasicChars<_DataType, _ParamSizeType, _ParamSize>& src){this->operator = (src);}
			template<typename _ParamSizeType> BasicCharsString(const GAIA::CTN::BasicString<_DataType, _ParamSizeType>& src){this->operator = (src);}
			GINL ~BasicCharsString(){this->destroy();}
			GINL GAIA::GVOID proxy(const _DataType* p, const _SizeType& size, const _SizeType& capacity)
			{
				this->destroy();
				m_string.proxy(p, size, capacity);
			}
			GINL GAIA::GVOID proxy(const _DataType* p)
			{
				this->destroy();
				m_string.proxy(p);
			}
			GINL GAIA::BL empty() const{if(m_string.capacity() != 0) return m_string.empty(); return m_chars.empty();}
			GINL _SizeType size() const{if(m_string.capacity() != 0) return m_string.size(); return m_chars.size();}
			GINL _SizeType capacity() const{return GAIA::ALGO::maximize(m_string.capacity(), m_chars.capacity());}
			GINL GAIA::GVOID resize(const _SizeType& size)
			{
				if(size > m_chars.capacity())
				{
					m_chars.clear();
					m_string.resize(size);
				}
				else
				{
					m_string.clear();
					m_chars.resize(size);
				}
			}
			GINL GAIA::GVOID reserve(const _SizeType& size)
			{
				if(size > m_chars.capacity())
				{
					m_chars.clear();
					m_string.reserve(size);
				}
				else
				{
					m_string.destroy();
					m_chars.clear();
				}
			}
			GINL GAIA::GVOID clear(){m_chars.clear(); m_string.clear();}
			GINL GAIA::GVOID destroy()
			{
				m_chars.clear();
				m_string.destroy();
			}
			GINL GAIA::U32 type() const{if(m_string.capacity() != 0) return m_string.type(); return m_chars.type();}
			template<typename _ParamDataType> __MyType& assign(const _ParamDataType* p, const _SizeType& size)
			{
				if(p == GNIL || size == 0)
				{
					this->clear();
					return *this;
				}
				this->clear();
				if(size > m_chars.capacity())
					m_string.assign(p, size);
				else
					m_chars.assign(p, size);
				return *this;
			}
			GINL _DataType* front_ptr(){if(m_string.capacity() != 0) return m_string.front_ptr(); return m_chars.front_ptr();}
			GINL _DataType* back_ptr(){if(m_string.capacity() != 0) return m_string.back_ptr(); return m_chars.back_ptr();}
			GINL const _DataType* front_ptr() const{if(m_string.capacity() != 0) return m_string.front_ptr(); return m_chars.front_ptr();}
			GINL const _DataType* back_ptr() const{if(m_string.capacity() != 0) return m_string.back_ptr(); return m_chars.back_ptr();}
			GINL _DataType& front(){if(m_string.capacity() != 0) return m_string.front(); return m_chars.front();}
			GINL const _DataType& front() const{if(m_string.capacity() != 0) return m_string.front(); return m_chars.front();}
			GINL _DataType& back(){if(m_string.capacity() != 0) return m_string.back(); return m_chars.back();}
			GINL const _DataType& back() const{if(m_string.capacity() != 0) return m_string.back(); return m_chars.back();}
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
			GINL GAIA::GVOID inverse(){if(m_string.capacity() != 0) m_string.inverse(); else m_chars.inverse();}
			template<typename _ParamDataType> GAIA::BL insert(const _ParamDataType& t, const _SizeType& index)
			{
				if(m_string.capacity() != 0)
					return m_string.insert(t, index);
				else
				{
					if(m_chars.size() + 1 > m_chars.capacity())
					{
						if(!m_chars.empty())
							m_string = m_chars.front_ptr();

						if(m_string.insert(t, index))
						{
							m_chars.clear();
							return GAIA::True;
						}
						else
						{
							m_string.clear();
							return GAIA::False;
						}
					}
					else
						return m_chars.insert(t, index);
				}
			}
			template<typename _ParamDataType> GAIA::BL insert(const _ParamDataType* p, const _SizeType& index)
			{
				if(m_string.capacity() != 0)
					return m_string.insert(p, index);
				else
				{
					if(GAIA::ALGO::strlen(p) + m_chars.size() > m_chars.capacity())
					{
						if(!m_chars.empty())
							m_string = m_chars.front_ptr();

						if(m_string.insert(p, index))
						{
							m_chars.clear();
							return GAIA::True;
						}
						else
						{
							m_string.clear();
							return GAIA::False;
						}
					}
					else
						return m_chars.insert(p, index);
				}
			}
			GINL GAIA::BL insert(const __MyType& src, const _SizeType& index)
			{
				if(m_string.capacity() != 0)
					return m_string.insert(src.front_ptr(), index);
				else
				{
					if(src.size() + m_chars.size() > m_chars.capacity())
					{
						if(!m_chars.empty())
							m_string = m_chars.front_ptr();
						
						if(m_string.insert(src.front_ptr(), index))
						{
							m_chars.clear();
							return GAIA::True;
						}
						else
						{
							m_string.clear();
							return GAIA::False;
						}
					}
					else
						return m_chars.insert(src.front_ptr(), index);
				}
			}
			template<typename _ParamSizeType> GAIA::BL erase_index(const _ParamSizeType& index)
			{
				if(m_string.capacity() != 0)
					return m_string.erase_index(index);
				return m_chars.erase_index(index);
			}
			template<typename _ParamSizeType1, typename _ParamSizeType2> GAIA::BL erase_index(const _ParamSizeType1& index_start, const _ParamSizeType2& index_end)
			{
				if(m_string.capacity() != 0)
					return m_string.erase_index(index_start, index_end);
				return m_chars.erase_index(index_start, index_end);
			}
			template<typename _ParamDataType> _SizeType erase(const _ParamDataType& t, const _SizeType& index)
			{
				if(m_string.capacity() != 0)
					return m_string.erase(t, index);
				return m_chars.erase(t, index);
			}
			template<typename _ParamDataType> _SizeType erase(const _ParamDataType* p, const _SizeType& index)
			{
				if(m_string.capacity() != 0)
					return m_string.erase(p, index);
				return m_chars.erase(p, index);
			}
			GINL _SizeType erase(const __MyType& src, const _SizeType& index)
			{
				if(m_string.capacity() != 0)
					return m_string.erase(src.front_ptr(), index);
				return m_chars.erase(src.front_ptr(), index);
			}
			template<typename _ParamDataType> _SizeType find(const _ParamDataType& t, const _SizeType& index) const
			{
				if(m_string.capacity() != 0)
					return m_string.find(t, index);
				return m_chars.find(t, index);
			}
			template<typename _ParamDataType> _SizeType find(const _ParamDataType* p, const _SizeType& index) const
			{
				if(m_string.capacity() != 0)
					return m_string.find(p, index);
				return m_chars.find(p, index);
			}
			GINL _SizeType find(const __MyType& src, const _SizeType& index) const
			{
				if(m_string.capacity() != 0)
					return m_string.find(src, index);
				return m_chars.find(src, index);
			}
			template<typename _ParamDataType> _SizeType rfind(const _ParamDataType& t, const _SizeType& index) const
			{
				if(m_string.capacity() != 0)
					return m_string.rfind(t, index);
				return m_chars.rfind(t, index);
			}
			template<typename _ParamDataType> _SizeType rfind(const _ParamDataType* p, const _SizeType& index) const
			{
				if(m_string.capacity() != 0)
					return m_string.rfind(p, index);
				return m_chars.rfind(p, index);
			}
			GINL _SizeType rfind(const __MyType& src, const _SizeType& index) const
			{
				if(m_string.capacity() != 0)
					return m_string.rfind(src.front_ptr(), index);
				return m_chars.rfind(src.front_ptr(), index);
			}
			GINL _SizeType replace(const _DataType& src, const _DataType& dst)
			{
				if(m_string.capacity() != 0)
					return m_string.replace(src, dst);
				return m_chars.replace(src, dst);
			}
			template<typename _ParamDataType> _SizeType replace(const _ParamDataType* pSrc, const _ParamDataType* pDst)
			{
				if(m_string.capacity() != 0)
					return m_string.replace(pSrc, pDst);
				return m_chars.replace(pSrc, pDst);
			}
			GINL _SizeType replace(const __MyType& src, const __MyType& dst)
			{
				if(m_string.capacity() != 0)
					return m_string.replace(src.front_ptr(), dst.front_ptr());
				return m_chars.replace(src.front_ptr(), dst.front_ptr());
			}
			GINL __MyType& left(const _SizeType& index)
			{
				if(m_string.capacity() != 0)
					m_string.left(index);
				else
					m_chars.left(index);
				return *this;
			}
			GINL __MyType& right(const _SizeType& index)
			{
				if(m_string.capacity() != 0)
					m_string.right(index);
				else
					m_chars.right(index);
				return *this;
			}
			GINL __MyType& mid(const _SizeType& index_start, const _SizeType& index_end)
			{
				if(m_string.capacity() != 0)
					m_string.mid(index_start, index_end);
				else
					m_chars.mid(index_start, index_end);
				return *this;
			}
			template<typename _ParamSizeType> GAIA::BL trim_left_index(const _ParamSizeType& index)
			{
				if(m_string.capacity() != 0)
					return m_string.trim_left_index(index);
				return m_chars.trim_left_index(index);
			}
			template<typename _ParamDataType> GAIA::BL trim_left(const _ParamDataType& t)
			{
				if(m_string.capacity() != 0)
					return m_string.trim_left(t);
				return m_chars.trim_left(t);
			}
			template<typename _ParamDataType> GAIA::BL trim_left(const _ParamDataType* p)
			{
				if(m_string.capacity() != 0)
					return m_string.trim_left(p);
				return m_chars.trim_left(p);
			}
			GINL GAIA::BL trim_left(const __MyType& src)
			{
				if(m_string.capacity() != 0)
					return m_string.trim_left(src.front_ptr());
				return m_chars.trim_left(src.front_ptr());
			}
			template<typename _ParamDataType> GAIA::BL trim_lefti(const _ParamDataType& t)
			{
				if(m_string.capacity() != 0)
					return m_string.trim_lefti(t);
				return m_chars.trim_lefti(t);
			}
			template<typename _ParamDataType> GAIA::BL trim_lefti(const _ParamDataType* p)
			{
				if(m_string.capacity() != 0)
					return m_string.trim_lefti(p);
				return m_chars.trim_lefti(p);
			}
			GINL GAIA::BL trim_lefti(const __MyType& src)
			{
				if(m_string.capacity() != 0)
					return m_string.trim_lefti(src.front_ptr());
				return m_chars.trim_lefti(src.front_ptr());
			}
			template<typename _ParamSizeType> GAIA::BL trim_right_index(const _ParamSizeType& index)
			{
				if(m_string.capacity() != 0)
					return m_string.trim_right_index(index);
				return m_chars.trim_right_index(index);
			}
			template<typename _ParamDataType> GAIA::BL trim_right(const _ParamDataType& t)
			{
				if(m_string.capacity() != 0)
					return m_string.trim_right(t);
				return m_chars.trim_right(t);
			}
			template<typename _ParamDataType> GAIA::BL trim_right(const _ParamDataType* p)
			{
				if(m_string.capacity() != 0)
					return m_string.trim_right(p);
				return m_chars.trim_right(p);
			}
			GINL GAIA::BL trim_right(const __MyType& src)
			{
				if(m_string.capacity() != 0)
					return m_string.trim_right(src.front_ptr());
				return m_chars.trim_right(src.front_ptr());
			}
			template<typename _ParamDataType> GAIA::BL trim_righti(const _ParamDataType& t)
			{
				if(m_string.capacity() != 0)
					return m_string.trim_righti(t);
				return m_chars.trim_righti(t);
			}
			template<typename _ParamDataType> GAIA::BL trim_righti(const _ParamDataType* p)
			{
				if(m_string.capacity() != 0)
					return m_string.trim_righti(p);
				return m_chars.trim_righti(p);
			}
			GINL GAIA::BL trim_righti(const __MyType& src)
			{
				if(m_string.capacity() != 0)
					return m_string.trim_righti(src.front_ptr());
				return m_chars.trim_righti(src.front_ptr());
			}
			GINL GAIA::GVOID tolower()
			{
				if(m_string.capacity() != 0)
					m_string.tolower();
				else
					m_chars.tolower();
			}
			GINL GAIA::GVOID toupper()
			{
				if(m_string.capacity() != 0)
					m_string.toupper();
				else
					m_chars.toupper();
			}
			GINL GAIA::BL isexistlower() const
			{
				if(m_string.capacity() != 0)
					return m_string.isexistlower();
				return m_chars.isexistlower();
			}
			GINL GAIA::BL isexistupper() const
			{
				if(m_string.capacity() != 0)
					return m_string.isexistupper();
				return m_chars.isexistupper();
			}
			GINL GAIA::BL isalllower() const
			{
				if(m_string.capacity() != 0)
					return m_string.isalllower();
				return m_chars.isalllower();
			}
			GINL GAIA::BL isallupper() const
			{
				if(m_string.capacity() != 0)
					return m_string.isallupper();
				return m_chars.isallupper();
			}
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
			GINL __MyType& operator = (const GAIA::X128& t)
			{
				this->resize(32);
				GAIA::ALGO::hex2str((const GAIA::U8*)&t, sizeof(t), this->front_ptr());
				return *this;
			}
			GINL __MyType& operator = (const GAIA::F32& t){_DataType sz[GAIA_DIGIT_TOSTRING_LEN]; GAIA::ALGO::real2str(t, sz); return this->operator = (sz);}
			GINL __MyType& operator = (const GAIA::F64& t){_DataType sz[GAIA_DIGIT_TOSTRING_LEN]; GAIA::ALGO::real2str(t, sz); return this->operator = (sz);}
			GINL __MyType& operator = (const GAIA::BL& t){_DataType sz[GAIA_DIGIT_TOSTRING_LEN]; sz[0] = t ? '1' : '0'; sz[1] = '\0'; return this->operator = (sz);}
			template<typename _ParamSizeType, _ParamSizeType _ParamSize> __MyType& operator = (const GAIA::CTN::BasicChars<_DataType, _ParamSizeType, _ParamSize>& src){this->operator = (src.front_ptr()); return *this;}
			template<typename _ParamSizeType> __MyType& operator = (const GAIA::CTN::BasicString<_DataType, _ParamSizeType>& src){this->operator = (src.front_ptr()); return *this;}
			GINL __MyType& operator += (const __MyType& src)
			{
				if(m_string.capacity() != 0)
					m_string += src.front_ptr();
				else
				{
					if(m_chars.size() + src.size() > m_chars.capacity())
					{
						m_string = m_chars.front_ptr();
						m_string += src.front_ptr();
						m_chars.clear();
					}
					else
						m_chars += src.front_ptr();
				}
				return *this;
			}
			template<typename _ParamDataType> __MyType& operator += (const _ParamDataType* p)
			{
				if(m_string.capacity() != 0)
					m_string += p;
				else
				{
					if(m_chars.size() + GAIA::ALGO::strlen(p) > m_chars.capacity())
					{
						m_string = m_chars.front_ptr();
						m_string += p;
						m_chars.clear();
					}
					else
						m_chars += p;
				}
				return *this;
			}
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
		private:
			GAIA::CTN::BasicChars<_DataType, _SizeType, _Size> m_chars;
			GAIA::CTN::BasicString<_DataType, _SizeType> m_string;
		};
		template<typename _DataType1, typename _DataType2, typename _SizeType, _SizeType _Size> GAIA::CTN::BasicCharsString<_DataType2, _SizeType, _Size>
			operator + (_DataType1 p, const GAIA::CTN::BasicCharsString<_DataType2, _SizeType, _Size>& str)
		{
			GAIA::CTN::BasicCharsString<_DataType2, _SizeType, _Size> ret = p;
			ret += str;
			return ret;
		}
	};
};

#endif