#ifndef		__GAIA_DATA_ANALYZE_XML_H__
#define		__GAIA_DATA_ANALYZE_XML_H__

namespace GAIA
{
	namespace DATAPHASE
	{
		template<typename _StringType, typename _StringLengthType, typename _DataSizeType, typename _SizeIncreaserType> class XML : public GAIA::Entity
		{
		public:
			typedef XML<_StringType, _StringLengthType, _DataSizeType, _SizeIncreaserType> __MyType;
			typedef const _StringType* _ConstStringPtrType;
		public:
			GINL XML(){}
			GINL ~XML(){}
			GINL GAIA::BL Load(GAIA::FILESYSTEM::FileBase& file);
			GINL GAIA::BL Save(GAIA::FILESYSTEM::FileBase& file) const;
			GINL GAIA::BL Load(GAIA::CONTAINER::BasicBuffer<GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::U32>, GAIA::U32>& buf);
			GINL GAIA::BL Save(GAIA::CONTAINER::BasicBuffer<GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::U32>, GAIA::U32>& buf) const;
			GINL GAIA::BL EnumNode(_ConstStringPtrType& pNodeName);
			GINL GAIA::BL EnumNodeEnd();
			GINL GAIA::BL EnumAttr(_ConstStringPtrType& pAttrName, _ConstStringPtrType& pAttrValue);
			GINL GAIA::BL WriteNode(const _StringType* pNode);
			GINL GAIA::BL WriteNodeEnd();
			GINL GAIA::BL WriteAttr(const _StringType* pAttrName, const _StringType* pAttrValue);
			GINL _DataSizeType GetNodeCount() const{return m_nodes.size();}
			GINL const _StringType* GetNodeName(const _DataSizeType& node) const
			{
				Node& n = m_nodes[node];
				if(n.name == GINVALID)
					return GNULL;
				return m_ssp.string[n.name];
			}
			GINL GAIA::BL SetNodeName(const _DataSizeType& node, const _StringType* pNodeName)
			{
				GPCHR_NULLSTRPTR_RET(pNodeName, GAIA::False);
				Node& n = m_nodes[node];
				if(n.name == GINVALID)
					return GAIA::False;
				n.name = m_ssp.request(pNodeName);
				return GAIA::True;
			}
			GINL GAIA::BL InsertNode(const _DataSizeType& node, const _StringType* pNodeName)
			{
				GPCHR_NULLSTRPTR_RET(pNodeName, GAIA::False);
				if(node > m_nodes.size())
					return GAIA::False;
				if(node == m_nodes.size() || m_nodes[node].name != GINVALID)
				{
					Node newn;
					newn.name = GINVALID;
					m_nodes.insert(newn, node);
					m_nodes[node].name = m_ssp.request(pNodeName);
				}
				else
					m_nodes[node].name = m_ssp.request(pNodeName);
				return GAIA::True;
			}
			GINL GAIA::BL DeleteNode(const _DataSizeType& node)
			{
				if(!this->DeleteAttrAll(node))
					return GAIA::False;
				Node& n = m_nodes[node];
				if(n.name == GINVALID)
					return GAIA::False;
				n.name = GINVALID;
				return GAIA::True;
			}
			GINL GAIA::BL DeleteNodeAll()
			{
				if(m_nodes.empty())
					return GAIA::False;
				m_nodes.clear();
				m_ssp.clear();
				return GAIA::True;
			}
			GINL _DataSizeType GetNodeByName(const _DataSizeType& node, const _StringType* pNodeName) const
			{
				GPCHR_NULLSTRPTR_RET(pNodeName, GINVALID);
				typename __NodeListType::const_it cit = m_nodes.const_front_it();
				cit += node;
				for(; !cit.empty(); ++cit)
				{
					const Node& n = *cit;
					if(n.name == GINVALID)
						continue;
					if(GAIA::ALGORITHM::strcmp(m_ssp.string(n.name), pNodeName) == 0)
						return cit - m_nodes.const_front_it();
				}
				return GINVALID;
			}
			GINL _DataSizeType GetAttrCount(const _DataSizeType& node) const
			{
				Node& n = m_nodes[node];
				return n.attrs.size();
			}
			GINL const _StringType* GetAttrName(const _DataSizeType& node, const _DataSizeType& attr) const
			{
				Node& n = m_nodes[node];
				if(n.name == GINVALID)
					return GNULL;
				Attr& a = n.attrs[attr];
				if(a.name == GINVALID)
					return GNULL;
				return m_ssp.string(a.name);
			}
			GINL const _StringType* GetAttrValue(const _DataSizeType& node, const _DataSizeType& attr) const
			{
				Node& n = m_nodes[node];
				if(n.name == GINVALID)
					return GNULL;
				Attr& a = n.attrs[attr];
				if(a.name == GINVALID)
					return GNULL;
				return m_ssp.string(a.value);
			}
			GINL GAIA::BL SetAttrName(const _DataSizeType& node, const _DataSizeType& attr, const _StringType* pAttrName)
			{
				GPCHR_NULLSTRPTR_RET(pAttrName, GAIA::False);
				Node& n = m_nodes[node];
				if(n.name == GINVALID)
					return GAIA::False;
				Attr& a = n.attrs[attr];
				if(a.name == GINVALID)
					return GAIA::False;
				a.name = m_ssp.request(pAttrName);
				return GAIA::True;
			}
			GINL GAIA::BL SetAttrValue(const _DataSizeType& node, const _DataSizeType& attr, const _StringType* pAttrValue)
			{
				GPCHR_NULLSTRPTR_RET(pAttrValue, GAIA::False);
				Node& n = m_nodes[node];
				if(n.name == GINVALID)
					return GAIA::False;
				Attr& a = n.attrs[attr];
				if(a.name == GINVALID)
					return GAIA::False;
				a.value = m_ssp.request(pAttrValue);
				return GAIA::True;
			}
			GINL GAIA::BL InsertAttr(const _DataSizeType& node, const _DataSizeType& attr, const _StringType* pAttrName, const _StringType* pAttrValue)
			{
				GPCHR_NULLSTRPTR_RET(pAttrName, GAIA::False);
				GPCHR_NULLSTRPTR_RET(pAttrValue, GAIA::False);
				Node& n = m_nodes[node];
				if(n.name == GINVALID)
					return GAIA::False;
				if(attr > n.attrs.size())
					return GAIA::False;
				if(attr == n.attrs.size() || n.attrs[attr].name != GINVALID)
				{
					Attr newa;
					n.attrs.insert(newa, attr);
					n.attrs[attr].name = m_ssp.request(pAttrName);
					n.attrs[attr].value = m_ssp.request(pAttrValue);
				}
				else
				{
					n.attrs[attr].name = m_ssp.request(pAttrName);
					n.attrs[attr].value = m_ssp.request(pAttrValue);
				}
				return GAIA::True;
			}
			GINL GAIA::BL DeleteAttr(const _DataSizeType& node, const _DataSizeType& attr)
			{
				Node& n = m_nodes[node];
				if(n.name == GINVALID)
					return GAIA::False;
				Attr& a = n.attrs[attr];
				if(a.name == GINVALID)
					return GAIA::False;
				a.name = GINVALID;
				a.value = GINVALID;
				return GAIA::True;
			}
			GINL GAIA::BL DeleteAttrAll(const _DataSizeType& node)
			{
				Node& n = m_nodes[node];
				if(n.name == GINVALID)
					return GAIA::False;
				if(n.attrs.empty())
					return GAIA::False;
				n.attrs.clear();
				return GAIA::True;
			}
			GINL _DataSizeType GetAttrByName(const _DataSizeType& node, const _StringType* pAttrName) const
			{
				GPCHR_NULLSTRPTR_RET(pAttrName, GINVALID);
				Node& n = m_nodes[node];
				if(n.name == GINVALID)
					return GINVALID;
				typename __AttrListType::const_it cit = n.attrs.const_front_it();
				for(; !cit.empty(); ++cit)
				{
					const Attr& a = *cit;
					if(a.name == GINVALID)
						continue;
					if(GAIA::ALGORITHM::strcmp(m_ssp.string(a.name), pAttrName) == 0)
						return cit - n.attrs.const_front_it();
				}
				return GINVALID;
			}
		private:
			typedef GAIA::CONTAINER::BasicStaticStringPool<_StringType, _DataSizeType, _SizeIncreaserType> __SSPType;
			class Attr : public GAIA::Base
			{
			public:
				typename __SSPType::_sizetype name;
				typename __SSPType::_sizetype value;
			};
			typedef GAIA::CONTAINER::BasicVector<Attr, _DataSizeType, _SizeIncreaserType> __AttrListType;
			class Node : public GAIA::Base
			{
			public:
				typename __SSPType::sizetype name;
				__AttrListType attrs;
			};
			typedef GAIA::CONTAINER::BasicVector<Node, _DataSizeType, _SizeIncreaserType> __NodeListType;
		private:
			 __NodeListType m_nodes;
			 __SSPType m_ssp;
		};
	};
};

#endif
