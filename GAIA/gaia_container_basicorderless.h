#ifndef		__GAIA_CONTAINER_BASICORDERLESS_H__
#define		__GAIA_CONTAINER_BASICORDERLESS_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template <typename _DataType, typename _SizeType, typename _SizeIncreaserType, _DataType _DefaultValue> class BasicOrderless
		{
		public:
			typedef _DataType _datatype;
			typedef _SizeType _sizetype;
			typedef _SizeIncreaserType _sizeincreasertype;

		public:
			GINL BasicOrderless(){}
			GINL BasicOrderless(const BasicOrderless<_DataType, _SizeType, _SizeIncreaserType, _DefaultValue>& src){this->operator = (src);}
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
					_SizeType index = m_free.top();
					m_free.pop();
					m_use[index] = t;
					return index;
				}
				m_use.push_back(t);
				return m_use.size() - 1;
			}
			GINL GAIA::BL removei(const _SizeType& index)
			{
				GAIA_ASSERT(m_use[index] != _DefaultValue);
				if(m_use[index] == _DefaultValue)
					return GAIA::False;
				m_free.push(index);
				m_use[index] = _DefaultValue;
				return GAIA::True;
			}
			GINL GAIA::BL remove(const _DataType& t)
			{
				for(_SizeType x = 0; x < m_use.size(); ++x)
				{
					if(m_use[x] == _DefaultValue)
						continue;
					if(m_use[x] == t)
						return this->removei(x);
				}
				return GAIA::False;
			}
			GINL _SizeType find(const _DataType& t) const{return m_use.find(t);}
			GINL _SizeType count(const _DataType& t) const{return m_use.count(t);}
			GINL BasicOrderless<_DataType, _SizeType, _SizeIncreaserType, _DefaultValue>& operator = (const BasicOrderless<_DataType, _SizeType, _SizeIncreaserType, _DefaultValue>& src){m_use = src.m_use; m_free = src.m_free;}
			GINL _DataType& operator[](const _SizeType& index){return m_use[index];}
			GINL const _DataType& operator[](const _SizeType& index) const{return m_use[index];}
		private:
			BasicVector<_DataType, _SizeType, _SizeIncreaserType> m_use;
			BasicStack<_SizeType, _SizeType, _SizeIncreaserType> m_free;
		};
	};
};

#endif