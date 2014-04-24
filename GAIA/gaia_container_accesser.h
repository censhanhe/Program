#ifndef 	__GAIA_CONTAINER_ACCESSER_H__
#define 	__GAIA_CONTAINER_ACCESSER_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template<typename _DataType, typename _SizeType> class Accesser : public GAIA::Base
		{
		public:
			GAIA_ENUM_BEGIN(BIND_TYPE)
				BIND_TYPE_MEM,
				BIND_TYPE_FILE,
			GAIA_ENUM_END(BIND_TYPE)

			GAIA_ENUM_BEGIN(ACCESS_TYPE)
				ACCESS_TYPE_READ = 1 << 0,
				ACCESS_TYPE_WRITE = 1 << 1,
			GAIA_ENUM_END(ACCESS_TYPE)
		public:
			typedef _DataType _datatype;
			typedef _SizeType _sizetype;
		public:
			typedef Accesser<_DataType, _SizeType> __MyType;
		private:
			class Node : public GAIA::Base
			{
			private:
				friend class Accesser;
			public:
				GINL Node& operator = (const Node& src)
				{
					GAIA_AST(m_acc != GNULL);
					if(m_acc != GNULL && m_index != src.m_index)
						(*this) = (const _DataType&)src;
					return *this;
				}
				GINL Node& operator = (const _DataType& src)
				{
					GAIA_AST(m_acc != GNULL);
					m_acc->set(m_index, src);
					return *this;
				}
				GINL operator _DataType() const
				{
					GAIA_AST(m_acc != GNULL);
					_DataType ret;
					m_acc->get(m_index, ret);
					return ret;
				}
				GINL GAIA::BL operator == (const Node& src) const
				{
					GAIA_AST(m_acc == src.m_acc);
					return (_DataType)(*this) == (_DataType)src;
				}
				GINL GAIA::BL operator != (const Node& src) const{return !(this->operator = (src));}
				GINL GAIA::BL operator >= (const Node& src) const
				{
					GAIA_AST(m_acc == src.m_acc);
					return (_DataType)(*this) >= (_DataType)src;
				}
				GINL GAIA::BL operator <= (const Node& src) const
				{
					GAIA_AST(m_acc == src.m_acc);
					return (_DataType)(*this) <= (_DataType)src;
				}
				GINL GAIA::BL operator > (const Node& src) const{return !(this->operator <= (src));}
				GINL GAIA::BL operator < (const Node& src) const{return !(this->operator >= (src));}
			private:
				GINL Node(){this->init();}
			private:
				GINL GAIA::GVOID init(){m_acc = GNULL; m_index = 0;}
			private:
				__MyType* m_acc;
				_SizeType m_index;
			};
			class ConstNode : public GAIA::Base
			{
			private:
				friend class Accesser;
			public:
				GINL ConstNode& operator = (const ConstNode& src)
				{
					GAIA_AST(m_acc != GNULL);
					if(m_acc != GNULL && m_index != src.m_index)
						(*this) = (const _DataType&)src;
					return *this;
				}
				GINL operator _DataType() const
				{
					GAIA_AST(m_acc != GNULL);
					_DataType ret;
					m_acc->get(m_index, ret);
					return ret;
				}
			private:
				GINL ConstNode(){this->init();}
				GINL ConstNode& operator = (const _DataType& src)
				{
					GAIA_AST(m_acc != GNULL);
					m_acc->set(m_index, src);
					return *this;
				}
			private:
				GINL GAIA::GVOID init(){m_acc = GNULL; m_index = 0;}
			private:
				const __MyType* m_acc;
				_SizeType m_index;
			};
		public:
			GINL Accesser(){this->init();}
			GINL Accesser(const __MyType& src){this->init(); this->operator = (src);}
			GINL ~Accesser(){this->destroy();}
			GINL GAIA::BL bind(_DataType* p, const _SizeType& size, GAIA::UM access_type_mask)
			{
				this->destroy();
				if(p == GNULL)
					return GAIA::False;
				if(size <= 0)
					return GAIA::False;
				m_p = p;
				m_size = size;
				m_bindtype = BIND_TYPE_MEM;
				m_atm = access_type_mask;
				return GAIA::True;
			}
			GINL GAIA::BL bind(GAIA::FILESYSTEM::File& file, GAIA::UM access_type_mask)
			{
				this->destroy();
				GAIA_AST(file.IsOpen());
				if(!file.IsOpen())
					return GAIA::False;
				m_file = &file;
				m_size = file.Size();
				m_bindtype = BIND_TYPE_FILE;
				m_atm = access_type_mask;
				return GAIA::True;
			}
			GINL BIND_TYPE bindtype() const{return m_bindtype;}
			GINL GAIA::UM access_type_mask() const{return m_atm;}
			GINL GAIA::BL isbinded() const{return m_bindtype != BIND_TYPE_INVALID;}
			GINL _DataType* bindmem() const{return m_p;}
			GINL GAIA::FILESYSTEM::File* bindfile() const{return m_file;}
			GINL GAIA::BL empty() const{return !this->is_valid_index(m_index);}
			GINL GAIA::GVOID destroy(){this->init();}
			GINL const _SizeType& size() const{return m_size;}
			GINL GAIA::BL offset(const _SizeType& offset)
			{
				GAIA_AST(this->isbinded());
				if(!this->isbinded())
					return GAIA::False;
				GAIA_AST(offset >= 0);
				if(offset < 0)
					return GAIA::False;
				GAIA_AST(offset <= m_size);
				if(offset > m_size)
					return GAIA::False;
				m_offset = offset;
				m_index = 0;
				return GAIA::True;
			}
			GINL const _SizeType& offset() const{return m_offset;}
			GINL GAIA::BL stride(const _SizeType& stride)
			{
				GAIA_AST(this->isbinded());
				if(!this->isbinded())
					return GAIA::False;
				GAIA_AST(stride > 0);
				if(stride <= 0)
					return GAIA::False;
				GAIA_AST(stride >= sizeof(_DataType));
				if(stride < sizeof(_DataType))
					return GAIA::False;
				GAIA_AST(stride <= m_size - m_offset);
				if(stride > m_size - m_offset)
					return GAIA::False;
				m_stride = stride;
				return GAIA::True;
			}
			GINL const _SizeType& stride() const{return m_stride;}
			GINL GAIA::BL index(const _SizeType& index)
			{
				GAIA_AST(this->isbinded());
				if(!this->isbinded())
					return GAIA::False;
				m_index = index;
				return GAIA::True;
			}
			GINL const _SizeType& index() const{return m_index;}
			GINL Node operator * (){return (*this)[0];}
			GINL ConstNode operator * () const{return (*this)[0];}
			GINL Node operator [] (const _SizeType& index){Node n; n.m_acc = this; n.m_index = index; return n;}
			GINL ConstNode operator [] (const _SizeType& index) const{ConstNode n; n.m_acc = this; n.m_index = index; return n;}
			GINL __MyType& operator = (const __MyType& src)
			{
				m_bindtype = src.m_bindtype;
				m_atm = src.m_atm;
				m_p = src.m_p;
				m_file = src.m_file;
				m_size = src.m_size;
				m_offset = src.m_offset;
				m_stride = src.m_stride;
				m_index = src.m_index;
				return *this;
			}
			GINL __MyType& operator ++ ()
			{
				GAIA_AST(this->isbinded());
				if(this->isbinded())
					++m_index;
				return *this;
			}
			GINL __MyType& operator -- ()
			{
				GAIA_AST(this->isbinded());
				if(this->isbinded())
					--m_index;
				return *this;
			}
			GINL __MyType& operator += (const _SizeType& size)
			{
				GAIA_AST(this->isbinded());
				if(this->isbinded())
					m_index += size;
				return *this;
			}
			GINL __MyType& operator -= (const _SizeType& size)
			{
				GAIA_AST(this->isbinded());
				if(this->isbinded())
					m_index -= size;
				return *this;
			}
			GINL _SizeType operator + (const __MyType& src){return this->index() + src.index();}
			GINL _SizeType operator - (const __MyType& src){return this->index() - src.index();}
			GINL __MyType operator + (const _SizeType& size){__MyType ret; ret += size; return ret;}
			GINL __MyType operator - (const _SizeType& size){__MyType ret; ret -= size; return ret;}
			GINL GAIA::BL operator == (const __MyType& src) const
			{
				if(m_bindtype != src.m_bindtype)
					return GAIA::False;
				switch(m_bindtype)
				{
				case BIND_TYPE_MEM:
					{
						if(m_p != src.m_p)
							return GAIA::False;
					}
					break;
				case BIND_TYPE_FILE:
					{
						if(m_file != src.m_file)
							return GAIA::False;
					}
					break;
				default:
					GAIA_AST(GAIA::ALWAYSFALSE);
					return GAIA::False;
				}
				if(this->practice_offset() != src.practice_offset())
					return GAIA::False;
				return GAIA::True;
			}
			GINL GAIA::BL operator != (const __MyType& src) const{return !(this->operator = (src));}
			GINL GAIA::BL operator >= (const __MyType& src) const
			{
				if(m_bindtype > src.m_bindtype)
					return GAIA::True;
				else if(m_bindtype < src.m_bindtype)
					return GAIA::False;
				switch(m_bindtype)
				{
				case BIND_TYPE_MEM:
					{
						if(m_p > src.m_p)
							return GAIA::True;
						else if(m_p < src.m_p)
							return GAIA::False;
					}
					break;
				case BIND_TYPE_FILE:
					{
						if(m_file > src.m_file)
							return GAIA::True;
						else if(m_file < src.m_file)
							return GAIA::False;
					}
					break;
				default:
					GAIA_AST(GAIA::ALWAYSFALSE);
					return GAIA::False;
				}
				if(this->practice_offset() < src.practice_offset())
					return GAIA::False;
				return GAIA::True;
			}
			GINL GAIA::BL operator <= (const __MyType& src) const
			{
				if(m_bindtype < src.m_bindtype)
					return GAIA::True;
				else if(m_bindtype > src.m_bindtype)
					return GAIA::False;
				switch(m_bindtype)
				{
				case BIND_TYPE_MEM:
					{
						if(m_p < src.m_p)
							return GAIA::True;
						else if(m_p > src.m_p)
							return GAIA::False;
					}
					break;
				case BIND_TYPE_FILE:
					{
						if(m_file < src.m_file)
							return GAIA::True;
						else if(m_file > src.m_file)
							return GAIA::False;
					}
					break;
				default:
					GAIA_AST(GAIA::ALWAYSFALSE);
					return GAIA::False;
				}
				if(this->practice_offset() > src.practice_offset())
					return GAIA::False;
				return GAIA::True;
			}
			GINL GAIA::BL operator > (const __MyType& src) const{return !(this->operator <= (src));}
			GINL GAIA::BL operator < (const __MyType& src) const{return !(this->operator >= (src));}
		private:
			GINL GAIA::GVOID init()
			{
				m_bindtype = BIND_TYPE_INVALID;
				m_atm = ACCESS_TYPE_INVALID;
				m_p = GNULL;
				m_file = GNULL;
				m_size = 0;
				m_offset = 0;
				m_stride = sizeof(_DataType);
				m_index = 0;
			}
			GINL GAIA::BL is_valid_index(const _SizeType& index) const
			{
				if(index < 0)
					return GAIA::False;
				if(m_offset + index * m_stride + m_stride > m_size)
					return GAIA::False;
				return GAIA::True;
			}
			GINL _SizeType practice_offset(const _SizeType& index) const
			{
				GAIA_AST(this->is_valid_index(index));
				return m_offset + index * m_stride;
			}
			GINL GAIA::BL set(const _SizeType& index, const _DataType& src)
			{
				GAIA_AST(this->isbinded());
				if(!this->isbinded())
					return GAIA::False;
				GAIA_AST(this->is_valid_index(m_index + index));
				if(!this->is_valid_index(m_index + index))
					return GAIA::False;
				switch(this->bindtype())
				{
				case BIND_TYPE_MEM:
					{
						*(_DataType*)((GAIA::U8*)m_p + this->practice_offset(m_index + index)) = src;
						break;
					}
				case BIND_TYPE_FILE:
					{
						_SizeType poffset = this->practice_offset(m_index + index);
						if(m_file->Tell() != poffset)
						{
							if(!m_file->Seek(SEEK_TYPE_BEGIN, poffset))
							{
								GAIA_AST(GAIA::ALWAYSFALSE);
								return GAIA::False;
							}
						}
						if(m_file->Write(&src, sizeof(src)) != sizeof(src))
						{
							GAIA_AST(GAIA::ALWAYSFALSE);
							return GAIA::False;
						}
						break;
					}
				default:
					GAIA_AST(GAIA::ALWAYSFALSE);
					return GAIA::False;
				}
				return GAIA::True;
			}
			GINL GAIA::BL get(const _SizeType& index, _DataType& dst) const
			{	
				GAIA_AST(this->isbinded());
				if(!this->isbinded())
					return GAIA::False;
				GAIA_AST(this->is_valid_index(m_index + index));
				if(!this->is_valid_index(m_index + index))
					return GAIA::False;
				switch(this->bindtype())
				{
				case BIND_TYPE_MEM:
					{
						dst = *(_DataType*)((GAIA::U8*)m_p + this->practice_offset(m_index + index));
						break;
					}
				case BIND_TYPE_FILE:
					{
						_SizeType poffset = this->practice_offset(m_index + index);
						if(m_file->Tell() != poffset)
						{
							if(!m_file->Seek(SEEK_TYPE_BEGIN, poffset))
							{
								GAIA_AST(GAIA::ALWAYSFALSE);
								return GAIA::False;
							}
						}
						if(m_file->Read(&dst, sizeof(dst)) != sizeof(dst))
						{
							GAIA_AST(GAIA::ALWAYSFALSE);
							return GAIA::False;
						}
						break;
					}
				default:
					GAIA_AST(GAIA::ALWAYSFALSE);
					return GAIA::False;
				}
				return GAIA::True;
			}
		private:
			GINL __MyType& operator ++ (GAIA::N32)
			{
				GAIA_AST(GAIA::ALWAYSFALSE);
				++(*this);
				return *this;
			}
			GINL __MyType& operator -- (GAIA::N32)
			{
				GAIA_AST(GAIA::ALWAYSFALSE);
				--(*this);
				return *this;
			}
		private:
			BIND_TYPE m_bindtype;
			GAIA::UM m_atm; // atm means access type mask.
			_DataType* m_p;
			GAIA::FILESYSTEM::File* m_file;
			_SizeType m_size;
			_SizeType m_offset;
			_SizeType m_stride;
			_SizeType m_index;
		};
	};
};

#endif
