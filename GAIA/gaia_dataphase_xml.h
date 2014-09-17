#ifndef		__GAIA_DATAPHASE_XML_H__
#define		__GAIA_DATAPHASE_XML_H__

namespace GAIA
{
	namespace DATAPHASE
	{
		template<typename _CharType, typename _DataSizeType, typename _SizeIncreaserType> class XML : public GAIA::Entity
		{
		public:
			typedef _CharType _chartype;
			typedef _DataSizeType _datasizetype;
			typedef _SizeIncreaserType _sizeincreasertype;
		public:
			typedef XML<_CharType, _DataSizeType, _SizeIncreaserType> __MyType;
			typedef const _CharType* __ConstCharPtrType;
			typedef GAIA::CTN::Accesser<_CharType, _DataSizeType> __AccesserType;
		public:
			GINL XML(){this->init();}
			GINL ~XML(){this->Destroy();}
			GINL GAIA::BL Load(const __AccesserType& acc)
			{
				return GAIA::True;
			}
			GINL GAIA::BL Save(__AccesserType& acc)
			{
				return GAIA::True;
			}
			GINL GAIA::GVOID Destroy()
			{
				this->ResetCallStack();
				m_npool.destroy();
				m_nodes.destroy();
				m_ssp.destroy();
			}
			GINL GAIA::GVOID Clear()
			{
				this->ResetCallStack();
				m_npool.clear();
				m_nodes.clear();
				m_ssp.clear();
			}
			GINL GAIA::BL EnumNode(__ConstCharPtrType& pNodeName)
			{
				m_attrcursor = 0;
				if(m_callstack.empty())
				{
					if(m_nodes.empty())
						return GAIA::False;
					CallStack cs;
					cs.pNode = m_nodes.front();
					cs.index = 0;
					m_callstack.push_back(cs);
				}
				else
				{
					CallStack& curcs = m_callstack.back();
					if(curcs.index + 1 >= curcs.pNode->nodes.size())
						return GAIA::False;
					while(curcs.pNode->nodes[++curcs.index]->name == GINVALID)
					{
						if(curcs.index + 1 >= curcs.pNode->nodes.size())
							return GAIA::False;
					}
					CallStack cs;
					cs.pNode = curcs.pNode->nodes[curcs.index];
					cs.index = 0;
					m_callstack.push_back(cs);
				}
				pNodeName = m_ssp.get(m_callstack.back().pNode->name);
				return GAIA::True;
			}
			GINL GAIA::BL EnumAttr(__ConstCharPtrType& pAttrName, __ConstCharPtrType& pAttrValue)
			{
				if(m_callstack.empty())
					return GAIA::False;
				__AttrListType& attrs = m_callstack.back().pNode->attrs;
				if(m_attrcursor >= attrs.size())
					return GAIA::False;
				while(attrs[m_attrcursor].name == GINVALID)
				{
					++m_attrcursor;
					if(m_attrcursor >= attrs.size())
						return GAIA::False;
				}
				pAttrName = m_ssp.get(attrs[m_attrcursor].name);
				pAttrValue = m_ssp.get(attrs[m_attrcursor].value);
				GAIA_AST(pAttrName != GNULL);
				GAIA_AST(pAttrValue != GNULL);
				return GAIA::True;
			}
			GINL GAIA::BL Enum(__ConstCharPtrType& pName, __ConstCharPtrType& pValue) // If pValue is GNULL, it means enum a node.
			{
				if(this->EnumAttr(pName, pValue))
					return GAIA::True;
				for(;;)
				{
					if(this->EnumNode(pName))
					{
						pValue = GNULL;
						return GAIA::True;
					}
					if(!this->End())
						return GAIA::False;
				}
				return GAIA::False;
			}
			GINL GAIA::BL Change(const _CharType* pName, const _CharType* pValue) // If pValue is GNULL, it means change a node name.
			{
				GPCHR_NULLSTRPTR_RET(pName, GAIA::False);
				if(m_callstack.empty())
					return GAIA::False;
				Node* pNode = m_callstack.back().pNode;
				GAIA_AST(pNode->name != GINVALID);
				if(pValue == GNULL)
					pNode->name = m_ssp.alloc(pName);
				else
				{
					if(this->is_attr_exit(pNode, pName))
						return GAIA::False;
					if(m_attrcursor >= pNode->attrs.size())
						return GAIA::False;
					Attr& attr = pNode->attrs[m_attrcursor];
					attr.name = m_ssp.alloc(pName);
					attr.value = m_ssp.alloc(pValue);
				}
				return GAIA::True;
			}
			GINL GAIA::BL WriteNode(const _CharType* pNode)
			{
				GPCHR_NULLSTRPTR_RET(pNode, GAIA::False);
				Node* pNewNode = m_npool.alloc();
				pNewNode->name = m_ssp.alloc(pNode);
				if(m_callstack.empty())
				{
					GAIA_ASTDEBUG(m_nodes.empty());
					if(!m_nodes.empty())
					{
						m_npool.release(pNewNode);
						return GAIA::False;
					}
					m_nodes.push_back(pNewNode);
				}
				else
					m_callstack.back().pNode->nodes.push_back(pNewNode);
				CallStack cs;
				cs.pNode = pNewNode;
				cs.index = GINVALID;
				m_callstack.push_back(cs);
				return GAIA::True;
			}
			GINL GAIA::BL WriteAttr(const _CharType* pAttrName, const _CharType* pAttrValue)
			{
				GPCHR_NULLSTRPTR_RET(pAttrName, GAIA::False);
				GPCHR_NULL_RET(pAttrName, GAIA::False);
				if(m_callstack.empty())
					return GAIA::False;
				if(this->is_attr_exit(m_callstack.back().pNode, pAttrName))
					return GAIA::False;
				Attr a;
				a.name = m_ssp.alloc(pAttrName);
				a.value = m_ssp.alloc(pAttrValue);
				m_callstack.back().pNode->attrs.push_back(a);
				return GAIA::True;
			}
			GINL GAIA::BL End(){GAIA_ASTDEBUG(!m_callstack.empty()); return m_callstack.pop_back(); m_attrcursor = 0;}
			GINL GAIA::GVOID ResetCallStack(){m_callstack.clear(); m_attrcursor = 0;}
			GINL GAIA::BL IsResetCallStack() const{return m_callstack.empty();}
		private:
			class Node;
			class Attr;
			class CallStack;
			typedef GAIA::CTN::BasicStaticStringPool<_CharType, _DataSizeType, _SizeIncreaserType> __SSPType;
			typedef GAIA::CTN::BasicPool<Node, _DataSizeType, _SizeIncreaserType> __NodePoolType;
			typedef GAIA::CTN::BasicVector<Node*, _DataSizeType, _SizeIncreaserType> __NodeListType;
			typedef GAIA::CTN::BasicStack<CallStack, _DataSizeType, _SizeIncreaserType> __NodeStackType;
			typedef GAIA::CTN::BasicVector<Attr, _DataSizeType, _SizeIncreaserType> __AttrListType;
			class Attr : public GAIA::Base
			{
			public:
				typename __SSPType::_sizetype name;
				typename __SSPType::_sizetype value;
			};
			class Node : public GAIA::Base
			{
			public:
				typename __SSPType::_sizetype name;
				__AttrListType attrs;
				__NodeListType nodes;
			};
			class CallStack : public GAIA::Base
			{
			public:
				Node* pNode;
				typename __NodeListType::_sizetype index;
			};
		private:
			GINL GAIA::GVOID init(){this->ResetCallStack();}
			GINL GAIA::BL is_attr_exit(const Node* pNode, const _CharType* pAttrName) const
			{
				GAIA_AST(pNode != GNULL);
				GAIA_AST(pAttrName != GNULL);
				for(__AttrListType::_sizetype x = 0; x < pNode->attrs.size(); ++x)
				{
					const Attr& a = pNode->attrs[x];
					if(GAIA::ALGO::strcmp(m_ssp.get(a.name), pAttrName) == 0)
						return GAIA::True;
				}
				return GAIA::False;
			}
		private:
			__NodePoolType m_npool;
			__NodeListType m_nodes;
			__SSPType m_ssp;
			__NodeStackType m_callstack;
			typename __AttrListType::_sizetype m_attrcursor;
		};
	};
};

#endif
