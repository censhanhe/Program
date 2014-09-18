#ifndef		__GAIA_DATAPHASE_XML_H__
#define		__GAIA_DATAPHASE_XML_H__

namespace GAIA
{
	namespace DATAPHASE
	{
		template<typename _CharType, typename _SizeType, typename _SizeIncreaserType> class XML : public GAIA::Entity
		{
		public:
			typedef _CharType _chartype;
			typedef _SizeType _datasizetype;
			typedef _SizeIncreaserType _sizeincreasertype;
		public:
			typedef XML<_CharType, _SizeType, _SizeIncreaserType> __MyType;
			typedef const _CharType* __ConstCharPtrType;
			typedef GAIA::CTN::Accesser<_CharType, _SizeType> __AccesserType;
		public:
			GINL XML(){this->init();}
			GINL ~XML(){this->Destroy();}
			GINL GAIA::BL Load(const __AccesserType& acc)
			{
				this->Destroy();

				return GAIA::True;
			}
			GINL GAIA::BL Save(__AccesserType& acc, GAIA::CHARSET_TYPE cst)
			{
				if(m_root == GNULL)
					return GAIA::False;
				if(cst != CHARSET_TYPE_ANSI && 
					cst != CHARSET_TYPE_UTF7 && 
					cst != CHARSET_TYPE_UTF8 && 
					cst != CHARSET_TYPE_UTF16LE && 
					cst != CHARSET_TYPE_UTF16BE)
					return GAIA::False;
				static const GAIA::TCH* VERSION_STRING = _T("1.0");
				GAIA::ALGO::strcpy(acc, _T("<?xml version=\""));
				acc += GAIA::ALGO::strlen(_T("<?xml version=\""));
				GAIA::ALGO::strcpy(acc, VERSION_STRING);
				acc += GAIA::ALGO::strlen(VERSION_STRING);
				GAIA::ALGO::strcpy(acc, _T("\" encoding=\""));
				acc += GAIA::ALGO::strlen(_T("\" encoding=\""));
				GAIA::ALGO::strcpy(acc, GAIA::CHARSET_CODEPAGE_NAMEA[cst] + 1);
				acc += GAIA::ALGO::strlen(GAIA::CHARSET_CODEPAGE_NAMEA[cst] + 1);
				GAIA::ALGO::strcpy(acc, _T("\"?>"));
				acc += GAIA::ALGO::strlen(_T("\"?>"));
				GAIA::ALGO::strcpy(acc, m_lineflag.front_ptr());
				acc += m_lineflag.size();
				if(!this->SaveNode(0, m_root, acc))
					return GAIA::False;
				return GAIA::True;
			}
			GINL GAIA::GVOID Destroy()
			{
				this->ResetCursor();
				m_npool.destroy();
				m_root = GNULL;
				m_ssp.destroy();
			}
			GINL GAIA::GVOID Clear()
			{
				this->ResetCursor();
				m_npool.clear();
				m_root = GNULL;
				m_ssp.clear();
			}
			GINL GAIA::BL EnumNode(__ConstCharPtrType& pNodeName)
			{
				if(m_bEnd)
					return GAIA::False;
				m_attrcursor = 0;
				if(m_callstack.empty())
				{
					if(m_root == NULL)
						return GAIA::False;
					CallStack cs;
					cs.pNode = m_root;
					cs.index = 0;
					m_callstack.push_back(cs);
				}
				else
				{
					CallStack& curcs = m_callstack.back();
					if(curcs.index >= curcs.pNode->nodes.size())
						return GAIA::False;
					while(curcs.pNode->nodes[curcs.index] == GNULL)
					{
						++curcs.index;
						if(curcs.index >= curcs.pNode->nodes.size())
							return GAIA::False;
					}
					CallStack cs;
					cs.pNode = curcs.pNode->nodes[curcs.index];
					cs.index = 0;
					m_callstack.push_back(cs);
					++curcs.index;
				}
				pNodeName = m_ssp.get(m_callstack.back().pNode->name);
				return GAIA::True;
			}
			GINL GAIA::BL EnumAttr(__ConstCharPtrType& pAttrName, __ConstCharPtrType& pAttrValue)
			{
				if(m_bEnd)
					return GAIA::False;
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
				++m_attrcursor;
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
					if(this->IsAttrExist(pNode, pName))
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
					GAIA_ASTDEBUG(m_root == GNULL);
					if(m_root != GNULL)
					{
						m_npool.release(pNewNode);
						return GAIA::False;
					}
					m_root = pNewNode;
				}
				else
					m_callstack.back().pNode->nodes.push_back(pNewNode);
				CallStack cs;
				cs.pNode = pNewNode;
				cs.index = 0;
				m_callstack.push_back(cs);
				return GAIA::True;
			}
			GINL GAIA::BL WriteAttr(const _CharType* pAttrName, const _CharType* pAttrValue)
			{
				GPCHR_NULLSTRPTR_RET(pAttrName, GAIA::False);
				GPCHR_NULL_RET(pAttrName, GAIA::False);
				if(m_callstack.empty())
					return GAIA::False;
				if(this->IsAttrExist(m_callstack.back().pNode, pAttrName))
					return GAIA::False;
				Attr a;
				a.name = m_ssp.alloc(pAttrName);
				a.value = m_ssp.alloc(pAttrValue);
				m_callstack.back().pNode->attrs.push_back(a);
				return GAIA::True;
			}
			GINL GAIA::BL End()
			{
				GAIA_ASTDEBUG(!m_callstack.empty());
				if(m_callstack.size() == 1)
					m_bEnd = GAIA::True;
				return m_callstack.pop_back();
				m_attrcursor = 0;
			}
			GINL GAIA::GVOID ResetCursor(){m_callstack.clear(); m_attrcursor = 0; m_bEnd = GAIA::False;}
			GINL GAIA::BL IsResetCursor() const{return m_callstack.empty() && !m_bEnd;}
			GINL GAIA::BL SetLineFlag(const _CharType* p)
			{
				GPCHR_NULLSTRPTR_RET(p, GAIA::False);
				if(GAIA::ALGO::strcmp(p, _T("\r")) != 0 &&
					GAIA::ALGO::strcmp(p, _T("\n")) != 0 &&
					GAIA::ALGO::strcmp(p, _T("\r\n")) != 0)
					return GAIA::False;
				m_lineflag = p;
				return GAIA::True;
			}
			GINL const _CharType* GetLineFlag() const{return m_lineflag;}
		private:
			class Node;
			class Attr;
			class CallStack;
			typedef GAIA::CTN::BasicStaticStringPool<_CharType, _SizeType, _SizeIncreaserType> __SSPType;
			typedef GAIA::CTN::BasicPool<Node, _SizeType, _SizeIncreaserType> __NodePoolType;
			typedef GAIA::CTN::BasicVector<Node*, _SizeType, _SizeIncreaserType> __NodeListType;
			typedef GAIA::CTN::BasicStack<CallStack, _SizeType, _SizeIncreaserType> __NodeStackType;
			typedef GAIA::CTN::BasicVector<Attr, _SizeType, _SizeIncreaserType> __AttrListType;
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
			GINL GAIA::GVOID init()
			{
				this->ResetCursor();
				m_root = GNULL;
				m_lineflag = _T("\r\n");
			}
			GINL GAIA::BL IsAttrExist(const Node* pNode, const _CharType* pAttrName) const
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
			GINL GAIA::BL SaveNode(const GAIA::SIZE& sDepth, const Node* pNode, __AccesserType& acc) const
			{
				for(GAIA::SIZE x = 0; x < sDepth; ++x)
				{
					*acc = '\t'; ++acc;
				}
				*acc = '<'; ++acc;
				const _CharType* pNodeName = m_ssp.get(pNode->name);
				GAIA_AST(pNode != GNULL);
				GAIA::SIZE sNodeLen = GAIA::ALGO::strlen(pNodeName);
				GAIA::ALGO::strcpy(acc, pNodeName);
				acc += sNodeLen;
				for(_SizeType x = 0; x < pNode->attrs.size(); ++x)
				{
					const Attr& attr = pNode->attrs[x];
					if(attr.name == GINVALID)
						continue;
					*acc = ' '; ++acc;
					const _CharType* pAttrName = m_ssp.get(attr.name);
					const _CharType* pAttrValue = m_ssp.get(attr.value);
					GAIA_AST(pAttrName != GNULL);
					GAIA_AST(pAttrValue != GNULL);
					GAIA::SIZE sAttrNameLen = GAIA::ALGO::strlen(pAttrName);
					GAIA::SIZE sAttrValueLen = GAIA::ALGO::strlen(pAttrValue);
					GAIA::ALGO::strcpy(acc, pAttrName);
					acc += sAttrNameLen;
					*acc = '='; ++acc;
					*acc = '\"'; ++acc;
					if(sAttrValueLen != 0)
					{
						GAIA::ALGO::strcpy(acc, pAttrValue);
						acc += sAttrValueLen;
					}
					*acc = '\"'; ++acc;
				}
				GAIA::BL bExistChildNode = GAIA::False;
				for(_SizeType x = 0; x < pNode->nodes.size(); ++x)
				{
					Node* pChildNode = pNode->nodes[x];
					if(pChildNode == GNULL)
						continue;
					if(!bExistChildNode)
					{
						*acc = '>'; ++acc;
						GAIA::ALGO::strcpy(acc, m_lineflag.front_ptr());
						acc += m_lineflag.size();
						bExistChildNode = GAIA::True;
					}
					if(!this->SaveNode(sDepth + 1, pChildNode, acc))
						return GAIA::False;
				}
				if(bExistChildNode)
				{
					for(GAIA::SIZE x = 0; x < sDepth; ++x)
					{
						*acc = '\t';
						++acc;
					}
					*acc = '<'; ++acc;
					*acc = '/'; ++acc;
					GAIA::ALGO::strcpy(acc, pNodeName);
					acc += sNodeLen;
					*acc = '>'; ++acc;
				}
				else
				{
					*acc = '/'; ++acc;
					*acc = '>'; ++acc;
				}
				GAIA::ALGO::strcpy(acc, m_lineflag.front_ptr());
				acc += m_lineflag.size();
				return GAIA::True;
			}
		private:
			__NodePoolType m_npool;
			Node* m_root;
			__SSPType m_ssp;
			__NodeStackType m_callstack;
			typename __AttrListType::_sizetype m_attrcursor;
			GAIA::BL m_bEnd;
			GAIA::CTN::BasicChars<_CharType, _SizeType, 2> m_lineflag;
		};
	};
};

#endif
