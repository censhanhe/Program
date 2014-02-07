#ifndef		__GAIA_CONTAINER_BASICMULTISET_H__
#define		__GAIA_CONTAINER_BASICMULTISET_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template <typename _DataType, typename _SizeType, typename _HeightType, typename _SizeIncreaserType, _SizeType _GroupElementSize> class BasicMultiSet
		{
		public:
			typedef _DataType _datatype;
			typedef _SizeType _sizetype;
			typedef _HeightType _heighttype;
			typedef _SizeIncreaserType _sizeincreasertype;
		public:
			static const _SizeType _groupelementsize = _GroupElementSize;
		public:
			typedef BasicMultiSet<_DataType, _SizeType, _HeightType, _SizeIncreaserType, _GroupElementSize> __MyType;
			typedef BasicMultiAVLTree<_DataType, _SizeType, _HeightType, _SizeIncreaserType, _GroupElementSize> __MultiAVLTreeType;
			typedef BasicVector<Pair<_DataType, _SizeType>, _SizeType, _SizeIncreaserType> __DataListType;
		public:
			GINL BasicMultiSet(){}
			GINL BasicMultiSet(const __MyType& src){this->operator = (src);}
			GINL ~BasicMultiSet(){}
			GINL GAIA::BL empty() const{return m_mavltree.empty();}
			GINL _SizeType size() const{return m_mavltree.size();}
			GINL _SizeType capacity() const{return m_mavltree.capacity();}
			GINL GAIA::GVOID clear(){m_mavltree.clear();}
			GINL GAIA::GVOID destroy(){m_mavltree.destroy();}
			GINL GAIA::BL insert(const _DataType& t){return m_mavltree.insert(t);}
			GINL GAIA::BL erase(const _DataType& t){return m_mavltree.erase(t);}
			GINL GAIA::BL erase(const Pair<_DataType, _SizeType>& t){return m_mavltree.erase(t);}
			GINL _SizeType count(const _DataType& t) const{return m_mavltree.count(t);}
			GINL GAIA::BL find(const _DataType& t, __DataListType& result) const{return m_mavltree.find(t, result);}
			GINL __MyType& operator = (const __MyType& src){m_mavltree = src.m_mavltree; return *this;}
		private:
		private:
			__MultiAVLTreeType m_mavltree;
		};
	};
};

#endif
