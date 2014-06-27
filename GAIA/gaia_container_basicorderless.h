#ifndef		__GAIA_CONTAINER_BASICORDERLESS_H__
#define		__GAIA_CONTAINER_BASICORDERLESS_H__

namespace GAIA
{
	namespace CONTAINER
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
			GINL GAIA::GVOID clear(){m_use.clear(); m_free.clear();}
			GINL GAIA::GVOID destroy(){m_use.destroy(); m_free.destroy();}
			GINL GAIA::BL empty() const{return m_use.empty();}
			GINL _SizeType insert(const _DataType& t)
			{
				if(!m_free.empty())
				{
					_SizeType index = m_free.back();
					m_free.pop_back();
					m_use[index] = t;
					return index;
				}
				m_use.push_back(t);
				return m_use.size() - 1;
			}
			GINL GAIA::BL erase_index(const _SizeType& index)
			{
				m_free.push_back(index);
				m_use[index] = GNULL;
				return GAIA::True;
			}
			GINL GAIA::BL erase(const _DataType& t)
			{
				for(_SizeType x = 0; x < m_use.size(); ++x)
				{
					if(m_use[x] == t)
						return this->erase_index(x);
				}
				return GAIA::False;
			}
			GINL _SizeType find(const _DataType& t) const{return m_use.find(t, 0);}
			GINL _SizeType count(const _DataType& t) const{return m_use.count(t);}
			GINL __MyType& operator = (const __MyType& src){GAIA_AST(&src != this); m_use = src.m_use; m_free = src.m_free;}
			GINL _DataType& operator[](const _SizeType& index){return m_use[index];}
			GINL const _DataType& operator[](const _SizeType& index) const{return m_use[index];}
		private:
			BasicVector<_DataType, _SizeType, _SizeIncreaserType> m_use;
			BasicStack<_SizeType, _SizeType, _SizeIncreaserType> m_free;
		};
	};
};

#endif
