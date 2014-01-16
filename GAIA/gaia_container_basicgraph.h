#ifndef		__GAIA_CONTAINER_BASICGRAPH_H__
#define		__GAIA_CONTAINER_BASICGRAPH_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template <typename _DataType, typename _DistanceType, typename _SizeType, typename _SizeIncreaserType> class BasicGraphNode
		{
			BasicVector<_DataType, _SizeType, _SizeIncreaserType> m_links;
		};
		template <typename _DataType, typename _DistanceType, typename _SizeType, typename _SizeIncreaserType, _SizeType _GroupElementSize> class BasicGraph
		{
		public:
			typedef BasicGraphNode<_DataType, _DistanceType, _SizeType, _SizeIncreaserType> __Node;
			typedef BasicGraph<_DataType, _DistanceType, _SizeType, _SizeIncreaserType, _GroupElementSize> __MyType;
			typedef BasicVector<__Node*, _SizeType, _SizeIncreaserType> __NodeListType;
			typedef BasicVector<__NodeListType, _SizeType, _SizeIncreaserType> __PathListType;
			typedef BasicPool<__Node, _SizeType, _SizeIncreaserType, _GroupElementSize> __PoolType;
		public:
			GINL BasicGraph();
			GINL BasicGraph(const __MyType& src);
			GINL ~BasicGraph();
			GINL _SizeType size() const;
			GINL _SizeType capacity() const;
			GINL GAIA::GVOID destroy();
			GINL GAIA::GVOID clear();
			GINL GAIA::GVOID resize(const _SizeType& size);
			GINL GAIA::GVOID reserve(const _SizeType& size);
			GINL __Node* insert(const _DataType& t);
			GINL GAIA::GVOID erase(__Node& n);
			GINL GAIA::BL link(__Node& n1, __Node& n2);
			GINL GAIA::BL unlink(__Node& n1, __Node& n2);
			GINL GAIA::BL islinked(__Node& n1, __Node& n2) const;
			GINL _SizeType getlinkcount(__Node& n) const;
			GINL __Node* getlink(__Node& n, const _SizeType& index) const;
			GINL GAIA::GVOID find(const __Node* pSrc, const _DataType& t, __NodeListType& result) const;
			GINL GAIA::GVOID paths(const __Node& src, const __Node& dst, __PathListType& result) const;
			GINL GAIA::GVOID paths(const __Node& src, const _DataType& t, __PathListType& result) const;
			GINL GAIA::GVOID paths(const _DataType& src, const _DataType& dst, __PathListType& result) const;
			GINL _DistanceType minimize_in(const __Node& src, const _DataType& dst, __NodeListType& result) const;
			GINL _DistanceType maximize_in(const __Node& src, const _DataType& dst, __NodeListType& result) const;
			GINL _DistanceType minimize_in(const __Node& src, const __Node& dst, __NodeListType& result) const;
			GINL _DistanceType maximize_in(const __Node& src, const __Node& dst, __NodeListType& result) const;
			GINL _DistanceType minimize_in(const _DataType& src, const _DataType& dst, __NodeListType& result) const;
			GINL _DistanceType maximize_in(const _DataType& src, const _DataType& dst, __NodeListType& result) const;
			GINL _DistanceType minimize_out(const _DataType& src, __Node& result) const;
			GINL _DistanceType maximize_out(const _DataType& src, __Node& result) const;
			GINL _DistanceType minimize_out(const _DataType& src, const _DataType& dst) const; // src is out of the graph, dst is in the graph.
			GINL _DistanceType maximize_out(const _DataType& src, const _DataType& dst) const; // src is out of the graph, dst is in the graph.
		private:
			__NodeListType m_roots;
			__PoolType m_pool;
		};
	};
};

#endif