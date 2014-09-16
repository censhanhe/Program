#ifndef		__GAIA_CONTAINER_BASICORDERLESS_H__
#define		__GAIA_CONTAINER_BASICORDERLESS_H__

namespace GAIA
{
	namespace CTN
	{
		template<typename _DataType, typename _SizeType, typename _SizeIncreaserType> class BasicOrderless : public GAIA::Entity
		{
		public:
			typedef _DataType _datatype;
			typedef _SizeType _sizetype;
			typedef _SizeIncreaserType _sizeincreasertype;
		public:
			typedef BasicOrderless<_DataType, _SizeType, _SizeIncreaserType> __MyType;
		public:
			GINL BasicOrderless(){}
			GINL BasicOrderless(const __MyType& src){this->operator = (src);}
			GINL ~BasicOrderless(){}
			GINL const _SizeType& capacity() const{return m_use.capacity();}
			GINL const _SizeType& size() const{return m_use.size();}
			GINL _SizeType practice_size() const{return m_use.size() - m_free.size();}
			GINL GAIA::GVOID clear(){m_state.clear(); m_use.clear(); m_free.clear();}
			GINL GAIA::GVOID destroy(){m_state.destroy(); m_use.destroy(); m_free.destroy();}
			GINL GAIA::BL empty() const{return m_use.size() - m_free.size() == 0;}
			GINL GAIA::BL exist(const _SizeType& index) const{return m_state.exist(index);}
			GINL _SizeType insert(const _DataType& t)
			{
				if(!m_free.empty())
				{
					_SizeType index = m_free.back();
					m_free.pop_back();
					m_use[index] = t;
					m_state.set(index);
					return index;
				}
				m_use.push_back(t);
				m_state.push_back(GAIA::True);
				return m_use.size() - 1;
			}
			GINL GAIA::BL erase_index(const _SizeType& index)
			{
				if(!this->exist(index))
					return GAIA::False;
				m_free.push_back(index);
				m_state.reset(index);
				return GAIA::True;
			}
			GINL GAIA::BL erase(const _DataType& t)
			{
				for(_SizeType x = 0; x < m_use.size(); ++x)
				{
					if(!this->exist(x))
						continue;
					if(m_use[x] == t)
					{
						if(!this->erase_index(x))
							return GAIA::False;
					}
				}
				return GAIA::True;
			}
			GINL _SizeType find(const _DataType& t) const
			{
				for(_SizeType x = 0; x < m_use.size(); ++x)
				{
					if(this->exist(x))
					{
						if(m_use[x] == t)
							return x;
					}
				}
				return GINVALID;
			}
			GINL _SizeType count(const _DataType& t) const
			{
				_SizeType ret = 0;
				for(_SizeType x = 0; x < m_use.size(); ++x)
				{
					if(this->exist(x))
					{
						if(m_use[x] == t)
							++ret;
					}
				}
				return ret;
			}
			GINL __MyType& operator = (const __MyType& src)
			{
				this->clear();
				for(_SizeType x = 0; x < src.size(); ++x)
				{
					if(src.exist(x))
						this->insert(src[x]);
				}
				return *this;
			}
			GINL _DataType& operator[](const _SizeType& index)
			{
				GAIA_AST(m_state.exist(index));
				return m_use[index];
			}
			GINL const _DataType& operator[](const _SizeType& index) const
			{
				GAIA_AST(m_state.exist(index));
				return m_use[index];
			}
		private:
			BasicBitset<_SizeType, _SizeIncreaserType> m_state;
			BasicVector<_DataType, _SizeType, _SizeIncreaserType> m_use;
			BasicStack<_SizeType, _SizeType, _SizeIncreaserType> m_free;
		};
	};
};

#endif
