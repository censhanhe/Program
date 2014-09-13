#ifndef 	__GAIA_CONTAINER_BASICSTRINGPOOL_H__
#define 	__GAIA_CONTAINER_BAISCSTRINGPOOL_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template<typename _DataType, typename _SizeType, typename _RefCounterType, typename _SizeIncreaserType> class BasicStringPool : public GAIA::Entity
		{
		public:
			typedef _DataType _datatype;
			typedef _SizeType _sizetype;
			typedef _RefCounterType _refcountertype;
			typedef _SizeIncreaserType _sizeincreasertype;
		public:
			typedef BasicStringPool<_DataType, _SizeType, _RefCounterType, _SizeIncreaserType> __MyType;
		public:
			GINL BasicStringPool(){}
			GINL ~BasicStringPool(){this->destroy();}
			GINL GAIA::BL empty() const{return this->size() == 0;}
			GINL _SizeType size() const{return m_nodelist.size();}
			GINL _SizeType capacity() const{return m_nodelist.capacity();}
			GINL GAIA::GVOID reserve(const _SizeType& size){this->destroy(); m_nodelist.reserve(size); m_freelist.reserve(size); m_nodeset.reserve(size);}
			GINL GAIA::GVOID clear()
			{
				this->destroy_content_all();
				m_nodelist.clear();
				m_freelist.clear();
				m_nodeset.clear();
			}
			GINL GAIA::GVOID destroy()
			{
				this->destroy_content_all();
				m_nodelist.destroy();
				m_freelist.destroy();
				m_nodeset.destroy();
			}
			GINL _SizeType request(const _DataType* p)
			{
				GPCHR_NULLSTRPTR_RET(p, GNULL);
				Node finder;
				finder.p = p;
				Node* pFinded = m_nodeset.find(finder);
				if(pFinded != GNULL)
				{
					++m_nodelist[pFinded->index].refcounter;
					return pFinded->index;
				}
				finder.refcounter = 1;
				if(m_freelist.empty())
				{
					finder.index = m_nodelist.size();
					m_nodelist.push_back(finder);
				}
				else
				{
					finder.index = m_freelist.top();
					m_nodelist[finder.index] = finder;
				}
				m_nodeset.insert(finder);
				return finder.index;
			}
			GINL GAIA::BL release(const _SizeType& index)
			{
				Node& finder = m_nodelist[index];
				GAIA_AST(finder.refcounter != 0);
				if(finder.refcounter == 0)
					return GAIA::False;
				--finder.refcounter;
				if(finder.refcounter == 0)
				{
					m_nodeset.erase(finder);
					m_freelist.push(finder.index);
				}
				return GAIA::True;
			}
			GINL _SizeType string_size() const{return m_nodelist.size();}
			GINL const _DataType* string(const _SizeType& index) const{return m_nodelist[index].data;}
		private:
			class Node
			{
			public:
				GINL Node& operator = (const Node& src){data = src.data; index = src.index; refcounter = src.refcounter; return *this;}
				GINL GAIA::BL operator == (const Node& src) const{GAIA_AST(data != GNULL); GAIA_AST(src.data != GNULL); return GAIA::ALGORITHM::strcmp(data, src.data) == 0;}
				GINL GAIA::BL operator != (const Node& src) const{return !this->operator == (src);}
				GINL GAIA::BL operator >= (const Node& src) const{GAIA_AST(data != GNULL); GAIA_AST(src.data != GNULL); return GAIA::ALGORITHM::strcmp(data, src.data) >= 0;}
				GINL GAIA::BL operator <= (const Node& src) const{GAIA_AST(data != GNULL); GAIA_AST(src.data != GNULL); return GAIA::ALGORITHM::strcmp(data, src.data) <= 0;}
				GINL GAIA::BL operator > (const Node& src) const{return !this->operator <= (src);}
				GINL GAIA::BL operator < (const Node& src) const{return !this->operator >= (src);}
			public:
				_DataType* data;
				_SizeType index;
				_RefCounterType refcounter;
			};
			typedef GAIA::CONTAINER::BasicVector<Node, _SizeType, _SizeIncreaserType> __NodeListType;
			typedef GAIA::CONTAINER::BasicStack<_SizeType, _SizeType, _SizeIncreaserType> __FreeIndexListType;
			typedef GAIA::CONTAINER::BasicSet<Node, _SizeType, _SizeType, _SizeIncreaserType> __NodeSetType;
		private:
			GINL GAIA::GVOID destroy_content_all()
			{
				typename __NodeSetType::it it = m_nodeset.front_it();
				while(!it.empty())
				{
					Node& n = *it;
					GAIA_MFREE(n.data);
					++it;
				}
			}
		private:
			__NodeListType m_nodelist;
			__FreeIndexListType m_freelist;
			__NodeSetType m_nodeset;
		};
	};
};

#endif
