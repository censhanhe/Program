#ifndef 	__GAIA_CONTAINER_BASICSTRINGPOOL_H__
#define 	__GAIA_CONTAINER_BAISCSTRINGPOOL_H__

namespace GAIA
{
	namespace CTN
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
			GINL _SizeType practice_size() const{return m_nodelist.size() - m_freestack.size();}
			GINL _SizeType capacity() const{return m_nodelist.capacity();}
			GINL GAIA::GVOID reserve(const _SizeType& size){this->destroy(); m_nodelist.reserve(size); m_freestack.reserve(size);}
			GINL GAIA::GVOID clear()
			{
				this->destroy_content_all();
				m_nodelist.clear();
				m_freestack.clear();
				m_nodeset.clear();
			}
			GINL GAIA::GVOID destroy()
			{
				this->destroy_content_all();
				m_nodelist.destroy();
				m_freestack.destroy();
				m_nodeset.destroy();
			}
			GINL _SizeType alloc(const _DataType* p)
			{
				GPCHR_NULLSTRPTR_RET(p, GNIL);
				Node finder;
				finder.data = GCCAST(_DataType*)(p);
				NodeCmp* pFinded = m_nodeset.find(finder);
				if(pFinded != GNIL)
				{
					++m_nodelist[pFinded->index].refcounter;
					return pFinded->index;
				}
				finder.data = GAIA::ALGO::strnew(p);
				finder.refcounter = 1;
				if(m_freestack.empty())
				{
					finder.index = m_nodelist.size();
					m_nodelist.push_back(finder);
				}
				else
				{
					finder.index = m_freestack.back();
					m_nodelist[finder.index] = finder;
					m_freestack.pop_back();
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
					m_freestack.push_back(finder.index);
					GAIA_MFREE(finder.data);
					finder.data = GNIL;
				}
				return GAIA::True;
			}
			GINL _SizeType string_size() const{return m_nodelist.size();}
			GINL const _DataType* get(const _SizeType& index) const{return m_nodelist[index].data;}
			GINL __MyType& operator = (const __MyType& src)
			{
				this->clear();
				for(_SizeType x = 0; x < src.string_size(); ++x)
					this->alloc(src.get(x));
				return *this;
			}
			GAIA_CLASS_OPERATOR_COMPARE(m_nodeset, m_nodeset, __MyType);
		private:
			class NodeCmp : public GAIA::Base
			{
			public:
				GINL NodeCmp& operator = (const NodeCmp& src){data = src.data; index = src.index; return *this;}
				GINL GAIA::BL operator == (const NodeCmp& src) const{GAIA_AST(data != GNIL); GAIA_AST(src.data != GNIL); return GAIA::ALGO::strcmp(data, src.data) == 0;}
				GINL GAIA::BL operator != (const NodeCmp& src) const{return !this->operator == (src);}
				GINL GAIA::BL operator >= (const NodeCmp& src) const{GAIA_AST(data != GNIL); GAIA_AST(src.data != GNIL); return GAIA::ALGO::strcmp(data, src.data) >= 0;}
				GINL GAIA::BL operator <= (const NodeCmp& src) const{GAIA_AST(data != GNIL); GAIA_AST(src.data != GNIL); return GAIA::ALGO::strcmp(data, src.data) <= 0;}
				GINL GAIA::BL operator > (const NodeCmp& src) const{return !this->operator <= (src);}
				GINL GAIA::BL operator < (const NodeCmp& src) const{return !this->operator >= (src);}
			public:
				_DataType* data;
				_SizeType index;
			};
			class Node : public NodeCmp
			{
			public:
				GINL Node& operator = (const Node& src){this->NodeCmp::operator = (src); refcounter = src.refcounter; return *this;}
			public:
				_RefCounterType refcounter;
			};
			typedef GAIA::CTN::BasicVector<Node, _SizeType, _SizeIncreaserType> __NodeListType;
			typedef GAIA::CTN::BasicStack<_SizeType, _SizeType, _SizeIncreaserType> __FreeIndexStackType;
			typedef GAIA::CTN::BasicSet<NodeCmp, _SizeType, _SizeType, _SizeIncreaserType> __NodeSetType;
		private:
			GINL GAIA::GVOID destroy_content_all()
			{
				typename __NodeSetType::it it = m_nodeset.front_it();
				for(; !it.empty(); ++it)
				{
					NodeCmp& n = *it;
					GAIA_MFREE(n.data);
				}
			}
		private:
			__NodeListType m_nodelist;
			__FreeIndexStackType m_freestack;
			__NodeSetType m_nodeset;
		};
	};
};

#endif
