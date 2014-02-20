#ifndef 	__GAIA_CONTAINER_STORAGE_H__
#define 	__GAIA_CONTAINER_STORAGE_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template<typename _SizeType, typename _SizeIncreaserType, _SizeType _PageSize, _SizeType _GroupElementSize> class Storage
		{
		public:
			typedef _SizeType _sizetype;
		public:
			static const _SizeType _pagesize = _PageSize;
		public:
			class Node
			{
			private:
				friend class Storage;
			public:
				GINL Node(){}
				GINL Node(const Node& src){this->operator = (src);}
				GINL ~Node(){}
				GINL const _SizeType& head() const{return m_head;}
				GINL const _SizeType& size() const{return m_size;}
				GINL const _SizeType& capacity() const{return m_capacity;}
				GINL Node& operator = (const Node& src){m_head = src.m_head; m_size = src.m_size; m_capacity = src.m_capacity; return *this;}
				GINL GAIA::BL operator == (const Node& src) const{return m_head == src.m_head;}
				GINL GAIA::BL operator != (const Node& src) const{return m_head != src.m_head;}
				GINL GAIA::BL operator >= (const Node& src) const{return m_head >= src.m_head;}
				GINL GAIA::BL operator <= (const Node& src) const{return m_head <= src.m_head;}
				GINL GAIA::BL operator > (const Node& src) const{return m_head > src.m_head;}
				GINL GAIA::BL operator < (const Node& src) const{return m_head < src.m_head;}
			private:
				_SizeType m_head;
				_SizeType m_size;
				_SizeType m_capacity;
			};
			class NodeSize
			{
			private:
				friend class Storage;
			public:
				GINL NodeSize(){this->init();}
				GINL NodeSize(const NodeSize& src){this->operator = (src);}
				GINL NodeSize(const Node& src){this->operator = (src);}
				GINL ~NodeSize(){}
				GINL const Node& node() const{return m_n;}
				GINL NodeSize& operator = (const NodeSize& src){m_n = src.m_n; return *this;}
				GINL NodeSize& operator = (const Node& src){m_n = src; return *this;}
				GINL GAIA::BL operator == (const NodeSize& src) const{return m_n.size() == src.m_n.size();}
				GINL GAIA::BL operator != (const NodeSize& src) const{return m_n.size() != src.m_n.size();}
				GINL GAIA::BL operator >= (const NodeSize& src) const{return m_n.size() >= src.m_n.size();}
				GINL GAIA::BL operator <= (const NodeSize& src) const{return m_n.size() <= src.m_n.size();}
				GINL GAIA::BL operator > (const NodeSize& src) const{return m_n.size() > src.m_n.size();}
				GINL GAIA::BL operator < (const NodeSize& src) const{return m_n.size() < src.m_n.size();}
			private:
				GINL GAIA::GVOID init(){m_pNode = GNULL;}
			private:
				Node m_n;
			};
		public:
			typedef Storage<_SizeType, _SizeIncreaserType, _PageSize, _GroupElementSize> __MyType;
			typedef BasicAVLTree<Node, _SizeType, _SizeType, _SizeIncreaserType, _GroupElementSize> __AddrAVLTreeType;
			typedef BasicAVLTree<NodeSize, _SizeType, _SizeType, _SizeIncreaserType, _GroupElementSize> __SizeAVLTreeType;
		public:
			GINL Storage(){this->init();}
			GINL Storage(const __MyType& src){this->init(); this->operator = (src);}
			GINL ~Storage(){}
			GINL GAIA::BL empty() const{return m_size == 0;}
			GINL _SizeType size() const{return m_size;}
			GINL _SizeType capacity() const{return m_capacity;}
			GINL GAIA::BL increase_reserve(const _SizeType& start, const _SizeType& size)
			{
				if(size == 0)
					return GAIA::False;
				Node n;
				n.m_head = start;
				__AddrAVLTreeType::it it = m_origin_a.lower_bound(n);
				if(!it.empty())
				{
					if(start + size > (*it).head())
						return GAIA::False;
				}
				it = m_origin_a.upper_bound(n);
				if(!it.empty())
				{
					if((*it).head() + (*it).capacity() > start)
						return GAIA::False;
				}
				n.m_size = 0;
				n.m_capacity = size;
				m_capacity += size;

				return GAIA::True;
			}
			GINL GAIA::GVOID clear()
			{
				m_size = 0;
				m_using_a.clear();
				m_free_s.clear();
				__AddrAVLTreeType::it it = m_origin_a.front_it();
				while(!it.empty())
				{
					Node& n = *it;
					NodeSize ns = n;
					m_free_s.insert(ns);
					++it;
				}
			}
			GINL GAIA::GVOID destroy()
			{
				m_origin_a.destroy();
				m_using_a.destroy();
				m_free_s.destroy();
				this->init();
			}
			GINL Node* insert(const _SizeType& size)
			{
			}
			GINL GAIA::BL erase(const _SizeType& head)
			{
			}
			GINL Node* find(const _SizeType& head) const
			{
			}
			GINL GAIA::GVOID optimize()
			{
			}
			GINL __MyType& operator = (const __MyType& src)
			{
				m_origin_a = src.m_origin_a;
				m_using_a = src.m_using_a;
				m_free_s = src.m_free_s;
				return *this;
			}
		private:
			GINL GAIA::GVOID init(){m_size = 0; m_capacity = 0;}
		private:
			__AddrAVLTreeType m_origin_a;
			__AddrAVLTreeType m_using_a;
			__SizeAVLTreeType m_free_s;
			_SizeType m_size;
			_SizeType m_capacity;
		};
	};
};

#endif
