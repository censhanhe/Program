#ifndef 	__GAIA_CONTAINER_BASICSTATICSTRINGPOOL_H__
#define 	__GAIA_CONTAINER_BASICSTATICSTRINGPOOL_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template<typename _DataType, typename _SizeType, typename _OffsetType, typename _SizeIncreaserType> class BasicStaticStringPool : public GAIA::Entity
		{
		public:
			typedef _DataType _datatype;
			typedef _SizeType _sizetype;
			typedef _OffsetType _offsettype;
			typedef _SizeIncreaserType _sizeincreasertype;
		public:
			typedef BasicStaticStringPool<_DataType, _SizeType, _OffsetType, _SizeIncreaserType> __MyType;
		public:
			GINL BasicStaticStringPool(){}
			GINL ~BasicStaticStringPool(){}
			GINL GAIA::BL empty() const{return this->size() == 0;}
			GINL _SizeType size() const{return m_datalist.size();}
			GINL _SizeType capacity() const{return m_datalist.capacity();}
			GINL GAIA::GVOID reserve(const _SizeType& size){}
			GINL GAIA::GVOID clear(){m_datalist.clear(); m_nodeset.clear(); m_nodelist.clear();}
			GINL GAIA::GVOID destroy(){m_datalist.destroy(); m_nodeset.destroy(); m_nodelist.destroy();}
			GINL _SizeType string_size() const{return m_nodelist.size();}
			GINL const _DataType* string(const _SizeType& index) const{return m_datalist.front_ptr() + m_nodelist[index].index;}
			GINL _DataType* request(const _DataType* p){}
			GINL __MyType& operator = (const __MyType& src){}
			GINL GAIA::BL operator == (const __MyType& src) const{}
			GINL GAIA::BL operator != (const __MyType& src) const{}
			GINL GAIA::BL operator >= (const __MyType& src) const{}
			GINL GAIA::BL operator <= (const __MyType& src) const{}
			GINL GAIA::BL operator > (const __MyType& src) const{}
			GINL GAIA::BL operator < (const __MyType& src) const{}
		private:
			class Node : public GAIA::Base
			{
			public:
				GINL Node& operator = (const Node& src){pContainer = src.pContainer; index = src.index; return *this;}
				GINL GAIA::BL operator == (const __MyType::Node& src) const
				{
					GAIA_AST(pContainer == src.pContainer);
					return GAIA::ALGORITHM::strcmp(
						pContainer->m_datalist.front_ptr() + index,
						src.pContainer->m_datalist.front_ptr() + src.index) == 0;

				}
				GINL GAIA::BL operator != (const __MyType::Node& src) const{return !this->operator == (src);}
				GINL GAIA::BL operator >= (const __MyType::Node& src) const
				{
					GAIA_AST(pContainer == src.pContainer);
					return GAIA::ALGORITHM::strcmp(
						pContainer->m_datalist.front_ptr() + index,
						src.pContainer->m_datalist.front_ptr() + src.index) >= 0;
				}
				GINL GAIA::BL operator <= (const __MyType::Node& src) const
				{
					GAIA_AST(pContainer == src.pContainer);
					return GAIA::ALGORITHM::strcmp(
						pContainer->m_datalist.front_ptr() + index,
						src.pContainer->m_datalist.front_ptr() + src.index) <= 0;
				}
				GINL GAIA::BL operator > (const __MyType::Node& src) const{return !this->operator <= (src);}
				GINL GAIA::BL operator < (const __MyType::Node& src) const{return !this->operator >= (src);}
			public:
				__MyType* pContainer;
				_OffsetType index;
			};
			typedef GAIA::CONTAINER::BasicVector<_DataType, _SizeType, _SizeIncreaserType> __DataListType;
			typedef GAIA::CONTAINER::BasicSet<_DataType, _SizeType, _SizeType, _SizeIncreaserType> __NodeSetType;
			typedef GAIA::CONTAINER::BasicVector<_DataType, _SizeType, _SizeIncreaserType> __NodeListType; 
		private:
			__DataListType m_datalist;
			__NodeSetType m_nodeset;
			__NodeListType m_nodelist;
		};
	};
};

#endif
