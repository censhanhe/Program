#ifndef 	__GAIA_CONTAINER_BASICSTATICSTRINGPOOL_H__
#define 	__GAIA_CONTAINER_BASICSTATICSTRINGPOOL_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template<typename _DataType, typename _SizeType, typename _SizeIncreaserType> class BasicStaticStringPool : public GAIA::Entity
		{
		public:
			typedef _DataType _datatype;
			typedef _SizeType _sizetype;
			typedef _SizeIncreaserType _sizeincreasertype;
		public:
			typedef BasicStaticStringPool<_DataType, _SizeType, _SizeIncreaserType> __MyType;
		public:
			GINL BasicStaticStringPool(){}
			GINL ~BasicStaticStringPool(){}
			GINL GAIA::BL empty() const{return this->size() == 0;}
			GINL _SizeType size() const{return m_datalist.size();}
			GINL _SizeType capacity() const{return m_datalist.capacity();}
			GINL GAIA::GVOID reserve(const _SizeType& size){this->destroy(); m_datalist.reserve(size);}
			GINL GAIA::GVOID clear(){m_datalist.clear(); m_nodeset.clear(); m_nodelist.clear();}
			GINL GAIA::GVOID destroy(){m_datalist.destroy(); m_nodeset.destroy(); m_nodelist.destroy();}
			GINL _SizeType string_size() const{return m_nodelist.size();}
			GINL const _DataType* get(const _SizeType& index) const{return m_datalist.front_ptr() + m_nodelist[index].offset;}
			GINL _SizeType alloc(const _DataType* p)
			{
				GPCHR_NULLSTRPTR_RET(p, GNULL);
				Node finder;
				finder.pContainer = this;
				finder.offset = m_datalist.size();
				_SizeType len = GAIA::ALGORITHM::strlen(p);
				m_datalist.push_back(p, len + 1);
				Node* pFinded = m_nodeset.find(finder);
				if(pFinded == GNULL)
				{
					finder.index = m_nodelist.size();
					m_nodelist.push_back(finder);
					m_nodeset.insert(finder);
					return finder.index;
				}
				else
				{
					m_datalist.resize(finder.offset);
					return pFinded->index;
				}
			}
			GINL __MyType& operator = (const __MyType& src)
			{
				this->clear();
				for(_SizeType x = 0; x < src.string_size(); ++x)
					this->alloc(src.get(x));
				return *this;
			}
			GAIA_CLASS_OPERATOR_COMPARE(m_nodeset, m_nodeset, __MyType);
		private:
			class Node : public GAIA::Base
			{
			public:
				GINL Node& operator = (const Node& src){pContainer = src.pContainer; offset = src.offset; index = src.index; return *this;}
				GINL GAIA::BL operator == (const Node& src) const
				{
					GAIA_AST(offset < pContainer->m_datalist.size());
					GAIA_AST(src.offset < src.pContainer->m_datalist.size());
					return GAIA::ALGORITHM::strcmp(
						pContainer->m_datalist.front_ptr() + offset,
						src.pContainer->m_datalist.front_ptr() + src.offset) == 0;

				}
				GINL GAIA::BL operator != (const Node& src) const{return !this->operator == (src);}
				GINL GAIA::BL operator >= (const Node& src) const
				{
					GAIA_AST(offset < pContainer->m_datalist.size());
					GAIA_AST(src.offset < src.pContainer->m_datalist.size());
					return GAIA::ALGORITHM::strcmp(
						pContainer->m_datalist.front_ptr() + offset,
						src.pContainer->m_datalist.front_ptr() + src.offset) >= 0;
				}
				GINL GAIA::BL operator <= (const Node& src) const
				{
					GAIA_AST(offset < pContainer->m_datalist.size());
					GAIA_AST(src.offset < src.pContainer->m_datalist.size());
					return GAIA::ALGORITHM::strcmp(
						pContainer->m_datalist.front_ptr() + offset,
						src.pContainer->m_datalist.front_ptr() + src.offset) <= 0;
				}
				GINL GAIA::BL operator > (const Node& src) const{return !this->operator <= (src);}
				GINL GAIA::BL operator < (const Node& src) const{return !this->operator >= (src);}
			public:
				__MyType* pContainer;
				_SizeType offset;
				_SizeType index;
			};
			typedef GAIA::CONTAINER::BasicVector<_DataType, _SizeType, _SizeIncreaserType> __DataListType;
			typedef GAIA::CONTAINER::BasicSet<Node, _SizeType, _SizeType, _SizeIncreaserType> __NodeSetType;
			typedef GAIA::CONTAINER::BasicVector<Node, _SizeType, _SizeIncreaserType> __NodeListType; 
		private:
			__DataListType m_datalist;
			__NodeSetType m_nodeset;
			__NodeListType m_nodelist;
		};
	};
};

#endif
