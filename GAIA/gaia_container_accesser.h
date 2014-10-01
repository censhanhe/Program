#ifndef 	__GAIA_CONTAINER_ACCESSER_H__
#define 	__GAIA_CONTAINER_ACCESSER_H__

namespace GAIA
{
	namespace CTN
	{
		template<typename _DataType, typename _SizeType, typename _SizeIncreaserType> class Accesser : public GAIA::Entity
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
			typedef _SizeIncreaserType _sizeincreasertype;
		public:
			typedef Accesser<_DataType, _SizeType, _SizeIncreaserType> __MyType;
		private:
			class Node : public GAIA::Entity
			{
			private:
				friend class Accesser;
			public:
				GINL Node& operator = (const Node& src)
				{
					GAIA_AST(&src != this);
					GAIA_AST(!!m_acc);
					if(m_acc != GNIL && m_index != src.m_index)
						(*this) = (const _DataType&)src;
					return *this;
				}
				GINL Node& operator = (const _DataType& src)
				{
					GAIA_AST(!!m_acc);
					m_acc->set(m_index, src);
					return *this;
				}
				GINL operator _DataType() const
				{
					GAIA_AST(!!m_acc);
					_DataType ret;
					m_acc->get(m_index, ret);
					return ret;
				}
				GINL GAIA::BL operator == (const Node& src) const
				{
					GAIA_AST(m_acc == src.m_acc);
					return GSCAST(_DataType)(*this) == GSCAST(_DataType)(src);
				}
				GINL GAIA::BL operator != (const Node& src) const{return !this->operator == (src);}
				GINL GAIA::BL operator >= (const Node& src) const
				{
					GAIA_AST(m_acc == src.m_acc);
					return GSCAST(_DataType)(*this) >= GSCAST(_DataType)(src);
				}
				GINL GAIA::BL operator <= (const Node& src) const
				{
					GAIA_AST(m_acc == src.m_acc);
					return GSCAST(_DataType)(*this) <= GSCAST(_DataType)(src);
				}
				GINL GAIA::BL operator > (const Node& src) const{return !this->operator <= (src);}
				GINL GAIA::BL operator < (const Node& src) const{return !this->operator >= (src);}
			private:
				GINL Node(){this->init();}
			private:
				GINL GAIA::GVOID init(){m_acc = GNIL; m_index = 0;}
			private:
				__MyType* m_acc;
				_SizeType m_index;
			};
			class ConstNode : public GAIA::Entity
			{
			private:
				friend class Accesser;
			public:
				GINL ConstNode& operator = (const ConstNode& src)
				{
					GAIA_AST(&src != this);
					GAIA_AST(!!m_acc);
					if(m_acc != GNIL && m_index != src.m_index)
						(*this) = (const _DataType&)src;
					return *this;
				}
				GINL operator _DataType() const
				{
					GAIA_AST(!!m_acc);
					_DataType ret;
					m_acc->get(m_index, ret);
					return ret;
				}
				GINL GAIA::BL operator == (const ConstNode& src) const
				{
					GAIA_AST(m_acc == src.m_acc);
					return GSCAST(_DataType)(*this) == GSCAST(_DataType)(src);
				}
				GINL GAIA::BL operator != (const ConstNode& src) const{return !this->operator == (src);}
				GINL GAIA::BL operator >= (const ConstNode& src) const
				{
					GAIA_AST(m_acc == src.m_acc);
					return GSCAST(_DataType)(*this) >= GSCAST(_DataType)(src);
				}
				GINL GAIA::BL operator <= (const ConstNode& src) const
				{
					GAIA_AST(m_acc == src.m_acc);
					return GSCAST(_DataType)(*this) <= GSCAST(_DataType)(src);
				}
				GINL GAIA::BL operator > (const ConstNode& src) const{return !this->operator <= (src);}
				GINL GAIA::BL operator < (const ConstNode& src) const{return !this->operator >= (src);}
			private:
				GINL ConstNode(){this->init();}
				GINL ConstNode& operator = (const _DataType& src)
				{
					GAIA_AST(&src != this);
					GAIA_AST(!!m_acc);
					m_acc->set(m_index, src);
					return *this;
				}
			private:
				GINL GAIA::GVOID init(){m_acc = GNIL; m_index = 0;}
			private:
				const __MyType* m_acc;
				_SizeType m_index;
			};
		public:
			GINL Accesser(){this->init();}
			GINL Accesser(GAIA::N32 n){GAIA_AST(n == GNIL); this->operator = (n);}
			GINL Accesser(const __MyType& src){this->operator = (src);}
			GINL ~Accesser(){this->destroy();}
			GINL GAIA::BL bindmem(_DataType* p, const _SizeType& size, GAIA::UM atm)
			{
				if(p == GNIL)
				{
					GAIA_AST(atm | ACCESS_TYPE_WRITE);
					if(size != 0)
						return GAIA::False;
					this->expandable(GAIA::True);
				}
				else
				{
					if(size <= 0)
						return GAIA::False;
				}
				this->destroy();
				m_p = p;
				m_size = size;
				m_bindtype = BIND_TYPE_MEM;
				m_atm = atm;
				return GAIA::True;
			}
			GINL GAIA::BL bindfile(GAIA::FSYS::FileBase* pFile, GAIA::UM atm)
			{
				if(pFile == GNIL)
				{
					GAIA_AST(atm | ACCESS_TYPE_WRITE);
					this->expandable(GAIA::True);
					pFile = new GAIA::FSYS::File;
					GAIA::UM opentype = 0;
					if(atm & ACCESS_TYPE_READ)
						opentype |= GAIA::FSYS::File::OPEN_TYPE_READ;
					if(atm & ACCESS_TYPE_WRITE)
						opentype |= GAIA::FSYS::File::OPEN_TYPE_WRITE;
					opentype |= GAIA::FSYS::File::OPEN_TYPE_CREATEALWAYS;
					GAIA::MATH::RID128 rid128;
					rid128.uuid();
					GAIA::TCH szTempFileName[37];
					rid128.tostring(szTempFileName);
					GAIA::ALGO::strcat(szTempFileName, _T(".acc"));
					if(!pFile->Open(szTempFileName, opentype))
						return GAIA::False;
				}
				this->destroy();
				GAIA_AST(pFile->IsOpen());
				if(!pFile->IsOpen())
					return GAIA::False;
				m_file = pFile;
				m_size = pFile->Size();
				m_bindtype = BIND_TYPE_FILE;
				m_atm = atm;
				return GAIA::True;
			}
			GINL BIND_TYPE bindtype() const{return m_bindtype;}
			GINL GAIA::UM access_type_mask() const{return m_atm;}
			GINL GAIA::BL isbinded() const{return m_bindtype != BIND_TYPE_INVALID;}
			GINL _DataType* bindmem() const{return m_p;}
			GINL GAIA::FSYS::FileBase* bindfile() const{return m_file;}
			GINL GAIA::BL empty() const{if(this->expandable() && m_index >= 0) return GAIA::False; return !this->is_valid_index(m_index);}
			GINL GAIA::GVOID destroy()
			{
				m_bindtype = BIND_TYPE_INVALID;
				m_atm = ACCESS_TYPE_INVALID;
				m_p = GNIL;
				m_file = GNIL;
				m_size = 0;
				m_offset = 0;
				m_stride = sizeof(_DataType);
				m_index = 0;
			}
			GINL const _SizeType& size() const{return m_size;}
			GINL GAIA::BL offset(const _SizeType& offset)
			{
				GAIA_AST(offset >= 0);
				if(offset < 0)
					return GAIA::False;
				m_offset = offset;
				m_index = 0;
				return GAIA::True;
			}
			GINL const _SizeType& offset() const{return m_offset;}
			GINL GAIA::BL stride(const _SizeType& stride)
			{
				GAIA_AST(stride > 0);
				if(stride <= 0)
					return GAIA::False;
				GAIA_AST(stride >= sizeof(_DataType));
				if(stride < sizeof(_DataType))
					return GAIA::False;
				m_stride = stride;
				return GAIA::True;
			}
			GINL const _SizeType& stride() const{return m_stride;}
			GINL GAIA::BL index(const _SizeType& index)
			{
				m_index = index;
				return GAIA::True;
			}
			GINL const _SizeType& index() const{return m_index;}
			GINL GAIA::GVOID expandable(GAIA::BL b){m_expandable = b;}
			GINL GAIA::BL expandable() const{return m_expandable;}
			GINL Node operator * (){return (*this)[0];}
			GINL ConstNode operator * () const{return (*this)[0];}
			GINL Node operator [] (const _SizeType& index){Node n; n.m_acc = this; n.m_index = index; return n;}
			GINL ConstNode operator [] (const _SizeType& index) const{ConstNode n; n.m_acc = this; n.m_index = index; return n;}
			GINL __MyType& operator = (GAIA::N32 n){this->init(); return *this;}
			GINL __MyType& operator = (const __MyType& src)
			{
				GAIA_AST(&src != this);
				m_bindtype = src.m_bindtype;
				m_atm = src.m_atm;
				m_p = src.m_p;
				m_file = src.m_file;
				m_size = src.m_size;
				m_offset = src.m_offset;
				m_stride = src.m_stride;
				m_index = src.m_index;
				m_expandable = src.m_expandable;
				return *this;
			}
			GINL __MyType& operator ++ ()
			{
				++m_index;
				return *this;
			}
			GINL __MyType& operator -- ()
			{
				--m_index;
				return *this;
			}
			GINL __MyType operator ++ (GAIA::N32)
			{
				__MyType ret = *this;
				++(*this);
				return ret;
			}
			GINL __MyType operator -- (GAIA::N32)
			{
				__MyType ret = *this;
				--(*this);
				return ret;
			}
			GINL __MyType& operator += (const _SizeType& size)
			{
				m_index += size;
				return *this;
			}
			GINL __MyType& operator -= (const _SizeType& size)
			{
				m_index -= size;
				return *this;
			}
			GINL _SizeType operator - (const __MyType& src){return this->index() - src.index();}
			GINL __MyType operator + (const _SizeType& size){__MyType ret; ret = *this; ret += size; return ret;}
			GINL __MyType operator - (const _SizeType& size){__MyType ret; ret = *this; ret -= size; return ret;}
			GINL GAIA::BL operator == (GAIA::N32 n) const{GAIA_AST(n == GNIL); return this->empty();}
			GINL GAIA::BL operator != (GAIA::N32 n) const{GAIA_AST(n == GNIL); return !this->empty();}
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
				return this->practice_offset(m_index) == src.practice_offset(src.index());
			}
			GINL GAIA::BL operator != (const __MyType& src) const{return !this->operator == (src);}
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
				return this->practice_offset(m_index) >= src.practice_offset(src.index());
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
				return this->practice_offset(m_index) <= src.practice_offset(src.index());
			}
			GINL GAIA::BL operator > (const __MyType& src) const{return !this->operator <= (src);}
			GINL GAIA::BL operator < (const __MyType& src) const{return !this->operator >= (src);}
			GINL GAIA::BL operator ! () const{return this->empty();}
			template<typename _ParamDataType, typename _ParamSizeType, typename _ParamSizeIncreaserType>
				GAIA::BL convert_from(const GAIA::CTN::Accesser<_ParamDataType, _ParamSizeType, _ParamSizeIncreaserType>& src)
			{
				m_bindtype = GSCAST(__MyType::BIND_TYPE)(src.bindtype());
				m_atm = src.access_type_mask();
				m_p = GRCAST(_DataType*)(src.bindmem());
				m_file = src.bindfile();
				m_size = src.size();
				m_offset = src.offset();
				m_stride = sizeof(_DataType);
				m_index = 0;
				m_expandable = src.expandable();
				return GAIA::True;
			}
			GINL _SizeType write(const GAIA::GVOID* p, const _SizeType& size)
			{
				GPCHR_NULL_RET(p, GINVALID);
				GPCHR_BELOWEQUALZERO_RET(size, GINVALID);
				GPCHR_TRUE_RET(this->stride() != sizeof(_DataType), GINVALID);
				GPCHR_FALSE_RET((size % this->stride()) == 0, GINVALID);
				_SizeType pracsize = size;
				_SizeType pracoffset = this->practice_offset(m_index);
				if(pracsize > this->size() - pracoffset)
				{
					pracsize = this->size() - pracoffset;
					GAIA_AST(pracsize % this->stride() == 0);
				}
				GAIA_AST(pracsize <= size);
				switch(m_bindtype)
				{
				case BIND_TYPE_MEM:
					{
						if(pracsize == size)
						{
							GAIA::ALGO::xmemcpy(GRCAST(GAIA::U8*)(m_p) + pracoffset, p, size);
							m_index += size / this->stride();
							return size;
						}
						else if(pracsize < size)
						{
							if(this->expandable())
							{
								_SizeIncreaserType increaser;
								_SizeType newsize = increaser.Increase(this->size());
								newsize = GAIA::ALGO::maximize(newsize, GSCAST(_SizeType)(pracoffset + size));
								if(newsize % this->stride() != 0)
									newsize += this->stride() - newsize % this->stride();
								this->expandmem(newsize);
								GAIA::ALGO::xmemcpy(GRCAST(GAIA::U8*)(m_p) + pracoffset, p, size);
								m_index += size / this->stride();
								return size;
							}
							else
							{
								if(pracsize == 0)
									return 0;
								GAIA::ALGO::xmemcpy(GRCAST(GAIA::U8*)(m_p) + pracoffset, p, pracsize);
								m_index += pracsize / this->stride();
								return pracsize;
							}
						}
					}
					break;
				case BIND_TYPE_FILE:
					{
						if(m_file->Tell() != pracoffset)
						{
							if(!m_file->Seek(SEEK_TYPE_BEGIN, pracoffset))
							{
								GAIA_AST(GAIA::ALWAYSFALSE);
								return GINVALID;
							}
						}
						if(pracsize == size)
						{
							m_index += size / this->stride();
							return GSCAST(_SizeType)(m_file->Write(p, size));
						}
						else if(pracsize < size)
						{
							if(this->expandable())
							{
								this->expandfile(pracoffset + size);
								m_index += size / this->stride();
								return GSCAST(_SizeType)(m_file->Write(p, size));
							}
							else
							{
								if(pracsize == 0)
									return 0;
								m_index += pracsize / this->stride();
								return GSCAST(_SizeType)(m_file->Write(p, pracsize));
							}
						}
					}
					break;
				default:
					return GINVALID;
				}
				return GINVALID;
			}
			GINL _SizeType read(GAIA::GVOID* p, const _SizeType& size)
			{
				GPCHR_NULL_RET(p, GINVALID);
				GPCHR_BELOWEQUALZERO_RET(size, GINVALID);
				GPCHR_TRUE_RET(this->stride() != sizeof(_DataType), GINVALID);
				GPCHR_FALSE_RET((size % this->stride()) == 0, GINVALID);
				_SizeType pracsize = size;
				_SizeType pracoffset = this->practice_offset(m_index);
				if(pracsize > this->size() - pracoffset)
				{
					pracsize = this->size() - pracoffset;
					GAIA_AST(pracsize % this->stride() == 0);
				}
				GAIA_AST(pracsize <= size);
				if(pracsize == 0)
					return 0;
				switch(m_bindtype)
				{
				case BIND_TYPE_MEM:
					{
						GAIA::ALGO::xmemcpy(p, GRCAST(GAIA::U8*)(m_p) + pracoffset, pracsize);
						m_index += pracsize / this->stride();
						return pracsize;
					}
					break;
				case BIND_TYPE_FILE:
					{
						if(m_file->Tell() != pracoffset)
						{
							if(!m_file->Seek(SEEK_TYPE_BEGIN, pracoffset))
							{
								GAIA_AST(GAIA::ALWAYSFALSE);
								return GINVALID;
							}
						}
						m_index += pracsize / this->stride();
						return GSCAST(_SizeType)(m_file->Read(p, pracsize));
					}
					break;
				default:
					return GINVALID;
				}
			#if GAIA_COMPILER != GAIA_COMPILER_CL // For CL C4702 Warning.
				return GINVALID;
			#endif
			}
			template<typename _ParamDataType> GAIA::BL write(const _ParamDataType& ob){return this->write(&ob, sizeof(ob)) == sizeof(ob);}
			template<typename _ParamDataType> GAIA::BL read(_ParamDataType& ob){return this->read(&ob, sizeof(ob)) == sizeof(ob);}
		private:
			GINL GAIA::GVOID init()
			{
				m_expandable = GAIA::False;
				this->destroy();
			}
			GINL GAIA::BL is_valid_index(const _SizeType& index) const
			{
				if(index < 0)
					return GAIA::False;
				if(this->practice_offset(index + 1) > this->size())
					return GAIA::False;
				return GAIA::True;
			}
			GINL _SizeType practice_offset(const _SizeType& index) const{return m_offset + index * m_stride;}
			GINL GAIA::BL set(const _SizeType& index, const _DataType& src)
			{
				if(!this->isbinded() || !this->is_valid_index(m_index + index))
				{
					if(this->expandable())
					{
						_SizeType pracoffset = this->practice_offset(m_index + index);
						switch(this->bindtype())
						{
						case BIND_TYPE_MEM:
							{
								_SizeIncreaserType increaser;
								_SizeType newsize = increaser.Increase(this->size());
								newsize = GAIA::ALGO::maximize(newsize, GSCAST(_SizeType)(pracoffset + sizeof(_DataType)));
								if(newsize % this->stride() != 0)
									newsize += this->stride() - newsize % this->stride();
								this->expandmem(newsize);
							}
							break;
						case BIND_TYPE_FILE:
							{
								this->expandfile(pracoffset + sizeof(_DataType));
							}
							break;
						default:
							GAIA_AST(GAIA::ALWAYSFALSE);
							return GAIA::False;
						}
					}
					else
					{
						GAIA_AST(GAIA::False);
						return GAIA::False;
					}
				}
				switch(this->bindtype())
				{
				case BIND_TYPE_MEM:
					{
						*GRCAST(_DataType*)(GRCAST(GAIA::U8*)(m_p) + this->practice_offset(m_index + index)) = src;
						break;
					}
				case BIND_TYPE_FILE:
					{
						_SizeType pracoffset = this->practice_offset(m_index + index);
						if(m_file->Tell() != pracoffset)
						{
							if(!m_file->Seek(SEEK_TYPE_BEGIN, pracoffset))
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
						dst = *GRCAST(_DataType*)(GRCAST(GAIA::U8*)(m_p) + this->practice_offset(m_index + index));
						break;
					}
				case BIND_TYPE_FILE:
					{
						_SizeType pracoffset = this->practice_offset(m_index + index);
						if(m_file->Tell() != pracoffset)
						{
							if(!m_file->Seek(SEEK_TYPE_BEGIN, pracoffset))
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
			GINL GAIA::GVOID expandmem(const _SizeType& newsize)
			{
				GAIA_AST(newsize > this->size());
				GAIA_AST(newsize % this->stride() == 0);
				_DataType* pNew = GRCAST(_DataType*)(GAIA_MALLOC(GAIA::U8, newsize));
				GAIA_AST(pNew != GNIL);
				if(pNew == GNIL)
					return;
				if(m_p != GNIL)
				{
					GAIA::ALGO::xmemcpy(pNew, m_p, this->size());
					GAIA_MFREE(m_p);
				}
				m_p = pNew;
				m_size = newsize;
			}
			GINL GAIA::GVOID expandfile(const _SizeType& newsize)
			{
				GAIA_AST(newsize > this->size());
				m_size = newsize;
			}
		private:
			BIND_TYPE m_bindtype;
			GAIA::UM m_atm; // atm means access type mask.
			_DataType* m_p;
			GAIA::FSYS::FileBase* m_file;
			_SizeType m_size;
			_SizeType m_offset;
			_SizeType m_stride;
			_SizeType m_index;
			GAIA::BL m_expandable;
		};
	};
};

#endif
