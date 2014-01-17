#ifndef 	__GAIA_CONTAINER_BASICPOOL_H__
#define 	__GAIA_CONTAINER_BASICPOOL_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template <typename _DataType, typename _SizeType, typename _SizeIncreaserType, _SizeType _GroupElementSize> class BasicPool
		{
		public:
			typedef _DataType _datatype;
			typedef _SizeType _sizetype;
			typedef _SizeIncreaserType _sizeincreasertype;
		public:
			static const _SizeType _groupelementsize = _GroupElementSize;
		public:
			typedef BasicPool<_DataType, _SizeType, _SizeIncreaserType, _GroupElementSize> __MyType;
			typedef GAIA::CONTAINER::BasicVector<_SizeType, _SizeType, _SizeIncreaserType> __IndexListType;
		public:
			GINL BasicPool(){this->init();}
			GINL ~BasicPool(){this->destroy();}
			GINL GAIA::BL empty() const{if(this->size() == 0) return GAIA::True; return GAIA::False;}
			GINL GAIA::GVOID clear()
			{
				m_free.clear();
				for(_SizeType y = 0; y < m_buf.size(); ++y)
				{
					BasicVector<_DataType, _SizeType, _SizeIncreaserType>& listEle = m_buf[y]->listEle;
					for(_SizeType x = 0; x < listEle.size(); ++x)
						m_free.push(&listEle[x]);
				}
				m_size = 0;
				m_capacity = m_buf.size() * _GroupElementSize;
			}
			GINL _SizeType size() const{return m_size;}
			GINL _SizeType capacity() const{return m_capacity;}
			GINL GAIA::GVOID destroy()
			{
				for(_SizeType x = 0; x < m_buf.size(); ++x)
					delete m_buf[x];
				m_buf.destroy();
				m_free.destroy();
				m_size = 0;
				m_capacity = 0;
			}
			GINL _DataType* alloc()
			{
				if(this->size() == this->capacity())
					this->alloc_group();
				_DataType* pTop = m_free.top();
				m_free.pop();
				++m_size;
				return pTop;
			}
			GINL GAIA::BL release(_DataType* p){m_free.push(p); --m_size; return GAIA::True;}
			GINL _DataType& operator[](const _SizeType& index)
			{
				return m_buf[index / _GroupElementSize]->listEle[index % _GroupElementSize];
			}
			GINL const _DataType& operator[](const _SizeType& index) const
			{
				return m_buf[index / _GroupElementSize]->listEle[index % _GroupElementSize];
			}
			GINL GAIA::GVOID collect_valid_index_list(__IndexListType& result) const
			{
				result.clear();
				if(m_free.empty())
				{
					for(_SizeType x = 0; x < this->capacity(); ++x)
						result.push_back(x);
				}
				else
				{
					typedef _DataType* LPDATATYPE;
					const LPDATATYPE* pFront = m_free.front_ptr();
					const LPDATATYPE* pBack = m_free.back_ptr();
					for(_SizeType x = 0; x < this->capacity(); ++x)
					{
						const _DataType& t = m_buf[x / _GroupElementSize]->listEle[x % _GroupElementSize];
						if(GAIA::ALGORITHM::find(pFront, pBack, (LPDATATYPE)&t) == GNULL)
							result.push_back(x);
					}
				}
			}
		private:
			GINL GAIA::GVOID init(){m_size = m_capacity = 0;}
			GINL GAIA::GVOID alloc_group()
			{
				Group* pGroup = new Group;
				pGroup->listEle.resize(_GroupElementSize);
				for(_SizeType x = 0; x < _GroupElementSize; ++x)
					m_free.push(&pGroup->listEle[x]);
				m_buf.push_back(pGroup);
				m_capacity += _GroupElementSize;
			}
		private:
			class Group
			{
			public:
				BasicVector<_DataType, _SizeType, _SizeIncreaserType> listEle;
			};
		private:
			BasicVector<Group*, _SizeType, _SizeIncreaserType> m_buf;
			BasicStack<_DataType*, _SizeType, _SizeIncreaserType> m_free;
			_SizeType m_size;
			_SizeType m_capacity;
		};
	};
};

#endif
