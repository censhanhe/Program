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
		public:
			GINL Accesser(){this->init();}
			GINL Accesser(const __MyType& src){this->init(); this->operator = (src);}
			GINL ~Accesser(){this->destroy();}
			GINL GAIA::BL bind(GAIA::FILESYSTEM::File* pFile)
			{
				this->destory();
				if(pFile == GNULL)
					return GAIA::False;
				if(!pFile->IsOpen())
					return GAIA::False;
				m_file = pFile;
				m_size = pFile->Size();
				return GAIA::True;
			}
			GINL GAIA::BL bind(_DataType* p, const _SizeType& size)
			{
				this->destroy();
				if(p == GNULL)
					return GAIA::False;
				if(size <= 0)
					return GAIA::False;
				m_p = p;
				m_size = size;
				return GAIA::True;
			}
			GINL BIND_TYPE bindtype() const{return m_bindtype;}
			GINL GAIA::BL isbinded() const{return m_bindtype != BIND_TYPE_INVALID;}
			GINL _DataType* bindmem() const{return m_p;}
			GINL GAIA::FILESYSTEM::File* bindfile() const{return m_file;}
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
			GINL _DataType& operator * (){return (*this)[0];}
			GINL const _DataType& operator * () const{return (*this)[0];}
			GINL _DataType& operator [] (const _SizeType& index)
			{
				GAIA_AST(this->isbinded());
				if(!this->isbinded())
					return *(_DataType*)0;
				GAIA_AST(this->is_index_valid(index));
				if(!this->is_index_valid(index))
					return *(_DataType*)0;
				switch(this->bindtype())
				{
				case BIND_TYPE_MEM:
					return *(_DataType*)((GAIA::U8)m_p + this->practice_offset());
				case BIND_TYPE_FILE:
					{
						_SizeType poffset = this->practice_offset();
						if(m_file->Tell() != poffset())
						{
							if(!m_file->Seek(SEEK_TYPE_BEGIN, poffset))
							{
								GAIA_AST(GAIA::ALWAYSFALSE);
								return *(_DataType*)0;
							}
						}
						if(!m_file->Read(&m_t, sizeof(m_t)))
						{
							GAIA_AST(GAIA::ALWAYSFALSE);
							return *(_DataType*)0;
						}
						return m_t;
					}
				default:
					GAIA_AST(GAIA::ALWAYSFALSE);
					return *(_DataType*)0;
				}
			}
			GINL const _DataType& operator [] (const _SizeType& index) const{return (*const_cast<__MyType*>(this))[index];}
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
			GINL GAIA::BL is_index_valid(const _SizeType& index) const
			{
				if(index < 0)
					return GAIA::False;
				if(m_offset + index * m_stride + m_stride > m_size)
					return GAIA::False;
				return GAIA::True;
			}
			GINL _SizeType practice_offset() const
			{
				GAIA_AST(this->is_index_valid());
				return m_offset + m_index * m_stride;
			}
		private:
			BIND_TYPE m_bindtype;
			GAIA::UM m_atm; // atm means access type mask.
			_DataType* m_p;
			GAIA::FILESYSTEM::File* m_file;
			_DataType m_t;
			_SizeType m_size;
			_SizeType m_offset;
			_SizeType m_stride;
			_SizeType m_index;
		};
	};
};

#endif
