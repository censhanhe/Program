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
			GINL ~BasicPool(){}
			GINL GAIA::BL empty() const
			{
				m_free.clear();
				for(_SizeType y = 0; y < m_buf.size(); y++)
				{
					BasicVector<_DataType, _SizeType, _SizeIncreaserType>& group = m_buf[y].l;
					for(_SizeType x = 0; x < group.size(); x++)
						m_free.push(&group[x]);
				}
				m_size = 0;
				m_capacity = m_buf.size();
			}
			GINL _SizeType size() const{return m_size;}
			GINL _SizeType capacity() const{return m_capacity;}
			GINL GAIA::GVOID destroy(){m_buf.destroy(); m_free.destroy();}
			GINL _DataType* alloc()
			{
				if(this->size() == this->capacity())
					this->alloc_group();
				_DataType* pTop = m_free.top();
				m_free.pop();
				return pTop;
			}
			GINL GAIA::BL release(_DataType* p){m_free.push(p);}
		private:
			class Group
			{
			public:
				BasicVector<_DataType, _SizeType, _SizeIncreaserType> group;
			};
		private:
			GINL GAIA::GVOID alloc_group()
			{
				Group group;
				m_buf.push_back(group);
				m_buf[m_buf.size() - 1].group.resize(_GroupElementSize);
			}
		private:
			BasicVector<Group, _SizeType, _SizeIncreaserType> m_buf;
			BasicStack<_DataType*, _SizeType, _SizeIncreaserType> m_free;
			_SizeType m_size;
			_SizeType m_capacity;
		};
	};
};

#endif
