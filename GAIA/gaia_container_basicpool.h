#ifndef 	__GAIA_CONTAINER_BASICPOOL_H__
#define 	__GAIA_CONTAINER_BASICPOOL_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template<typename _DataType, typename _SizeType, typename _SizeIncreaserType> class BasicPool : public GAIA::Base
		{
		public:
			typedef _DataType _datatype;
			typedef _SizeType _sizetype;
			typedef _SizeIncreaserType _sizeincreasertype;
		public:
			typedef BasicPool<_DataType, _SizeType, _SizeIncreaserType> __MyType;
			typedef BasicVector<_DataType, _SizeType, _SizeIncreaserType> __ElementListType;
			typedef BasicVector<_SizeType, _SizeType, _SizeIncreaserType> __IndexListType;
		public:
			GINL BasicPool(){this->init();}
			GINL ~BasicPool(){this->destroy();}
			GINL GAIA::BL empty() const{return this->size() == 0;}
			GINL GAIA::GVOID clear()
			{
				m_free.clear();
				for(_SizeType y = 0; y < m_buf.size(); ++y)
				{
					__ElementListType& listEle = m_buf[y]->listEle;
					for(_SizeType x = 0; x < listEle.size(); ++x)
						m_free.push(&listEle[x]);
				}
			}
			GINL _SizeType size() const{return this->capacity() - m_free.size();}
			GINL const _SizeType& capacity() const{return m_use.size();}
			GINL GAIA::GVOID destroy()
			{
				for(_SizeType x = 0; x < m_buf.size(); ++x)
					delete m_buf[x];
				m_buf.destroy();
				m_use.destroy();
				m_free.destroy();
			}
			GINL _DataType* alloc()
			{
				if(this->size() == this->capacity())
					this->alloc_group();
				_DataType* pTop = m_free.top();
				m_free.pop();
				return pTop;
			}
			GINL GAIA::BL release(_DataType* p){m_free.push(p); return GAIA::True;}
			GINL _DataType& operator[](const _SizeType& index){return *m_use[index];}
			GINL const _DataType& operator[](const _SizeType& index) const{return *m_use[index];}
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
					BasicVector<_DataType*, _SizeType, _SizeIncreaserType> listFree;
					for(_SizeType x = 0; x < m_free.size(); ++x)
						listFree.push_back(m_free[x]);
					listFree.sort();
					for(_SizeType x = 0; x < this->capacity(); ++x)
					{
						_DataType* t = const_cast<_DataType*>(&(*this)[x]);
						if(listFree.search(t) == GINVALID)
							result.push_back(x);
					}
				}
			}
		private:
			GINL GAIA::GVOID init(){}
			GINL GAIA::GVOID alloc_group()
			{
				Group* pGroup = new Group;
				_SizeIncreaserType increaser;
				_SizeType newsize = increaser.Increase(m_use.size());
				pGroup->listEle.resize(newsize - m_use.size());
				for(_SizeType x = 0; x < pGroup->listEle.size(); ++x)
				{
					m_use.push_back(&pGroup->listEle[x]);
					m_free.push(&pGroup->listEle[x]);
				}
				m_buf.push_back(pGroup);
			}
		private:
			class Group : public GAIA::Base
			{
			public:
				__ElementListType listEle;
			};
		private:
			BasicVector<Group*, _SizeType, _SizeIncreaserType> m_buf;
			BasicVector<_DataType*, _SizeType, _SizeIncreaserType> m_use;
			BasicStack<_DataType*, _SizeType, _SizeIncreaserType> m_free;
		};
	};
};

#endif
