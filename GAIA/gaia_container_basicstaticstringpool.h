#ifndef 	__GAIA_CONTAINER_BASICSTATICSTRINGPOOL_H__
#define 	__GAIA_CONTAINER_BASICSTATICSTRINGPOOL_H__

namespace GAIA
{
	namespace CTN
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
				GPCHR_NULLSTR_RET(p, GNIL);
				Node finder;
				finder.pContainer = this;
				GAIA::BL bSelfData;
				if(!m_datalist.empty() && p >= m_datalist.front_ptr() && p <= m_datalist.back_ptr())
				{
					finder.offset = p - m_datalist.front_ptr();
					bSelfData = GAIA::True;
				}
				else
				{
					finder.offset = m_datalist.size();
					_SizeType len = GAIA::ALGO::strlen(p);
					m_datalist.push_back(p, len + 1);
					bSelfData = GAIA::False;
				}
				Node* pFinded = m_nodeset.find(finder);
				if(pFinded == GNIL)
				{
					GAIA_AST(!bSelfData);
					finder.index = m_nodelist.size();
					m_nodelist.push_back(finder);
					m_nodeset.insert(finder);
					return finder.index;
				}
				else
				{
					if(!bSelfData)
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
					return GAIA::ALGO::strcmp(
						pContainer->m_datalist.front_ptr() + offset,
						src.pContainer->m_datalist.front_ptr() + src.offset) == 0;

				}
				GINL GAIA::BL operator != (const Node& src) const{return !this->operator == (src);}
				GINL GAIA::BL operator >= (const Node& src) const
				{
					GAIA_AST(offset < pContainer->m_datalist.size());
					GAIA_AST(src.offset < src.pContainer->m_datalist.size());
					return GAIA::ALGO::strcmp(
						pContainer->m_datalist.front_ptr() + offset,
						src.pContainer->m_datalist.front_ptr() + src.offset) >= 0;
				}
				GINL GAIA::BL operator <= (const Node& src) const
				{
					GAIA_AST(offset < pContainer->m_datalist.size());
					GAIA_AST(src.offset < src.pContainer->m_datalist.size());
					return GAIA::ALGO::strcmp(
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
			typedef GAIA::CTN::BasicVector<_DataType, _SizeType, _SizeIncreaserType> __DataListType;
			typedef GAIA::CTN::BasicSet<Node, _SizeType, _SizeType, _SizeIncreaserType> __NodeSetType;
			typedef GAIA::CTN::BasicVector<Node, _SizeType, _SizeIncreaserType> __NodeListType; 
		private:
			__DataListType m_datalist;
			__NodeSetType m_nodeset;
			__NodeListType m_nodelist;
		};
	};
};

#endif
