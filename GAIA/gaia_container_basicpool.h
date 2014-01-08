#ifndef 	__GAIA_CONTAINER_BASICPOOL_H__
#define 	__GAIA_CONTAINER_BASICPOOL_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template <typename _DataType, typename _SizeType, typename _SizeIncreaserType, _SizeType _GroupElementSize> class BasicPool
		{
		public:
			GINL BasicPool(){m_size = m_capacity = 0;}
			GINL ~BasicPool(){this->destroy();}
			GINL GAIA::BL empty() const{if(m_size == 0) return GAIA::True; return GAIA::False;}
			GINL GAIA::GVOID clear()
			{
				m_free.clear();
				for(_SizeType y = 0; y < m_buf.size(); y++)
				{
					BasicVector<_DataType, _SizeType, _SizeIncreaserType>& listEle = m_buf[y]->listEle;
					for(_SizeType x = 0; x < listEle.size(); x++)
						m_free.push(&listEle[x]);
				}
				m_size = 0;
				m_capacity = m_buf.size();
			}
			GINL _SizeType size() const{return m_size;}
			GINL _SizeType capacity() const{return m_capacity;}
			GINL GAIA::GVOID destroy()
			{
				for(_SizeType x = 0; x < m_buf.size(); x++)
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
		private:
			class Group
			{
			public:
				BasicVector<_DataType, _SizeType, _SizeIncreaserType> listEle;
			};
		private:
			GINL GAIA::GVOID alloc_group()
			{
				Group* pGroup = new Group;
				pGroup->listEle.resize(_GroupElementSize);
				for(_SizeType x = 0; x < _GroupElementSize; x++)
					m_free.push(&pGroup->listEle[x]);
				m_buf.push_back(pGroup);
				m_capacity += _GroupElementSize;
			}
		private:
			BasicVector<Group*, _SizeType, _SizeIncreaserType> m_buf;
			BasicStack<_DataType*, _SizeType, _SizeIncreaserType> m_free;
			_SizeType m_size;
			_SizeType m_capacity;
		};
	};
};

#endif
