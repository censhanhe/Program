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
			typedef GAIA::CTN::Accesser<_CharType, _SizeType, _SizeIncreaserType> __AccesserType;
			typedef GAIA::CTN::BasicString<_CharType, _SizeType> __StringType;
		public:
			GINL XML(){this->init();}
			GINL ~XML(){this->Destroy();}
			GINL GAIA::BL Load(__AccesserType& acc)
			{
				this->Destroy();

				/* Load file header. */
				__AccesserType newacc = GAIA::ALGO::strdrop(acc, _T("<"));
				if(newacc == GNIL)
					return GAIA::False;
				if(newacc != acc)
					acc = newacc;
				if(acc[1] != '?')
					return GAIA::False;
				newacc = GAIA::ALGO::strch(acc, '>');
				if(newacc == GNIL)
					return GAIA::False;
				acc =  newacc;

				/* Load node. */
				if(!this->LoadNode(acc))
					return GAIA::False;
				return GAIA::True;
			}
			GINL GAIA::BL Save(__AccesserType& acc, GAIA::CHARSET_TYPE cst)
			{
				if(m_root == GNIL)
					return GAIA::False;

				/* Save file header. */
				if(cst != CHARSET_TYPE_ANSI && 
					cst != CHARSET_TYPE_UTF7 && 
					cst != CHARSET_TYPE_UTF8 && 
					cst != CHARSET_TYPE_UTF16LE && 
					cst != CHARSET_TYPE_UTF16BE)
					return GAIA::False;
				static const _CharType* VERSION_STRING = _T("1.0");
				acc = GAIA::ALGO::stradd(acc, _T("<?xml version=\""));
				acc = GAIA::ALGO::stradd(acc, VERSION_STRING);
				acc = GAIA::ALGO::stradd(acc, _T("\" encoding=\""));
				acc = GAIA::ALGO::stradd(acc, GAIA::CHARSET_CODEPAGE_NAMEA[cst] + 1);
				acc = GAIA::ALGO::stradd(acc, _T("\"?>"));
				acc = GAIA::ALGO::stradd(acc, m_lineflag.front_ptr());

				/* Save node. */
				if(!this->SaveNode(0, m_root, acc))
					return GAIA::False;
				return GAIA::True;
			}
			GINL GAIA::GVOID Destroy()
			{
				this->ResetCursor();
				m_npool.destroy();
				m_root = GNIL;
				m_ssp.destroy();
			}
			GINL GAIA::GVOID Clear()
			{
				this->ResetCursor();
				m_npool.clear();
				m_root = GNIL;
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
					while(curcs.pNode->nodes[curcs.index] == GNIL)
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
				GAIA_AST(pAttrName != GNIL);
				GAIA_AST(pAttrValue != GNIL);
				return GAIA::True;
			}
			GINL GAIA::BL Enum(__ConstCharPtrType& pName, __ConstCharPtrType& pValue) // If pValue is GNIL, it means enum a node.
			{
				if(this->EnumAttr(pName, pValue))
					return GAIA::True;
				for(;;)
				{
					if(this->EnumNode(pName))
					{
						pValue = GNIL;
						return GAIA::True;
					}
					if(!this->End())
						return GAIA::False;
				}
				return GAIA::False;
			}
			GINL GAIA::BL Change(const _CharType* pName, const _CharType* pValue) // If pValue is GNIL, it means change a node name.
			{
				GPCHR_NULLSTRPTR_RET(pName, GAIA::False);
				if(m_callstack.empty())
					return GAIA::False;
				Node* pNode = m_callstack.back().pNode;
				GAIA_AST(pNode->name != GINVALID);
				if(pValue == GNIL)
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
					GAIA_ASTDEBUG(m_root == GNIL);
					if(m_root != GNIL)
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
			GINL const _CharType* NameFamily(const _CharType* pNF, const _CharType* pConditionName, const _CharType* pConditionValue) const
			{
				GPCHR_NULLSTRPTR_RET(pNF, GNIL);
				return GNIL;
			}
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
				m_root = GNIL;
				m_lineflag = _T("\r\n");
			}
			GINL GAIA::BL IsAttrExist(const Node* pNode, const _CharType* pAttrName) const
			{
				GAIA_AST(pNode != GNIL);
				GAIA_AST(pAttrName != GNIL);
				for(__AttrListType::_sizetype x = 0; x < pNode->attrs.size(); ++x)
				{
					const Attr& a = pNode->attrs[x];
					if(GAIA::ALGO::strcmp(m_ssp.get(a.name), pAttrName) == 0)
						return GAIA::True;
				}
				return GAIA::False;
			}
			GINL GAIA::BL LoadAttr(__AccesserType& acc)
			{
				for(;;)
				{
					/* Drop invalid character. */
					while(!acc.empty())
					{
						_CharType ch = *acc;
						if(ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n')
							++acc;
						else if(ch == '/' || ch == '>')
							return GAIA::True;
						else
							break;
					}

					/* Load attr name. */
					__AccesserType newacc = GAIA::ALGO::strdrop(acc, _T("="));
					if(newacc == GNIL)
						return GAIA::False;
					const _CharType* pAttrName = GNIL;
					if(newacc - acc > CACHE_ATTRNAME_SIZE)
					{
						m_strTempAttrName.clear();
						m_strTempAttrName.resize(newacc - acc);
						GAIA::ALGO::strcpy(m_strTempAttrName.front_ptr(), acc, newacc - acc);
						pAttrName = m_strTempAttrName;
					}
					else
					{
						GAIA::ALGO::strcpy(m_szTempAttrName, acc, newacc - acc);
						pAttrName = m_szTempAttrName;
					}
					acc = newacc;

					/* Load attr value. */
					const _CharType* pAttrValue = GNIL;
					newacc = GAIA::ALGO::strdrop(acc, _T("\""));
					if(newacc == GNIL)
						return GAIA::False;
					acc = newacc;
					++acc;
					newacc = GAIA::ALGO::strdrop(acc, _T("\""));
					if(newacc == GNIL)
						return GAIA::False;
					if(newacc - acc > CACHE_ATTRNAME_SIZE)
					{
						m_strTempAttrValue.clear();
						m_strTempAttrValue.resize(newacc - acc);
						GAIA::ALGO::strcpy(m_strTempAttrValue.front_ptr(), acc, newacc - acc);
						pAttrValue = m_strTempAttrValue;
					}
					else
					{
						GAIA::ALGO::strcpy(m_szTempAttrValue, acc, newacc - acc);
						pAttrValue = m_szTempAttrValue;
					}
					acc = newacc;
					++acc;

					/* Write attr. */
					this->WriteAttr(pAttrName, pAttrValue);
				}
				return GAIA::True;
			}
			GINL GAIA::BL LoadNode(__AccesserType& acc)
			{
				/* Load node name. */
				__AccesserType newacc = GAIA::ALGO::strdrop(acc, _T("<"));
				if(newacc == GNIL)
					return GAIA::False;
				acc = newacc;
				++acc;
				newacc = GAIA::ALGO::strdrop(acc, _T(" /"));
				if(newacc == GNIL)
					return GAIA::False;
				if(newacc - acc > CACHE_NODENAME_SIZE)
				{
					m_strTempNodeName.clear();
					m_strTempNodeName.resize(newacc - acc);
					GAIA::ALGO::strcpy(m_strTempNodeName.front_ptr(), acc, newacc - acc);
					this->WriteNode(m_strTempNodeName);
				}
				else
				{
					GAIA::ALGO::strcpy(m_szTempNodeName, acc, newacc - acc);
					this->WriteNode(m_szTempNodeName);
				}
				acc = newacc;

				/* Load attributes. */
				if(!this->LoadAttr(acc))
					return GAIA::False;

				/* Load child node. */
				for(;;)
				{
					newacc = GAIA::ALGO::strdrop(acc, _T("/<"));
					if(newacc == GNIL)
						return GAIA::False;
					if(*newacc == '/' || *(newacc + 1) == '/')
					{
						acc = newacc;
						break;
					}
					if(!this->LoadNode(acc))
						return GAIA::False;
				}

				/* Move to node end. */
				newacc = GAIA::ALGO::strdrop(acc, _T(">"));
				if(newacc == GNIL)
					return GAIA::False;
				acc = newacc;

				/* End. */
				this->End();
				return GAIA::True;
			}
			GINL GAIA::BL SaveNode(const GAIA::SIZE& sDepth, const Node* pNode, __AccesserType& acc) const
			{
				/* Write tabs by depth. */
				for(GAIA::SIZE x = 0; x < sDepth; ++x)
				{
					*acc = '\t';
					++acc;
				}

				/* Write node name. */
				*acc = '<'; ++acc;
				const _CharType* pNodeName = m_ssp.get(pNode->name);
				GAIA_AST(pNode != GNIL);
				_SizeType sNodeLen = GAIA::ALGO::strlen(pNodeName);
				acc = GAIA::ALGO::stradd(acc, pNodeName);

				/* Write node attr.*/
				for(_SizeType x = 0; x < pNode->attrs.size(); ++x)
				{
					const Attr& attr = pNode->attrs[x];
					if(attr.name == GINVALID)
						continue;
					*acc = ' '; ++acc;
					const _CharType* pAttrName = m_ssp.get(attr.name);
					const _CharType* pAttrValue = m_ssp.get(attr.value);
					GAIA_AST(pAttrName != GNIL);
					GAIA_AST(pAttrValue != GNIL);
					_SizeType sAttrNameLen = GAIA::ALGO::strlen(pAttrName);
					_SizeType sAttrValueLen = GAIA::ALGO::strlen(pAttrValue);
					acc = GAIA::ALGO::stradd(acc, pAttrName);
					*acc = '='; ++acc;
					*acc = '\"'; ++acc;
					if(sAttrValueLen != 0)
						acc = GAIA::ALGO::stradd(acc, pAttrValue);
					*acc = '\"'; ++acc;
				}

				/* Write child node. */
				GAIA::BL bExistChildNode = GAIA::False;
				for(_SizeType x = 0; x < pNode->nodes.size(); ++x)
				{
					Node* pChildNode = pNode->nodes[x];
					if(pChildNode == GNIL)
						continue;
					if(!bExistChildNode)
					{
						*acc = '>'; ++acc;
						acc = GAIA::ALGO::stradd(acc, m_lineflag.front_ptr());
						bExistChildNode = GAIA::True;
					}
					if(!this->SaveNode(sDepth + 1, pChildNode, acc))
						return GAIA::False;
				}

				/* Write node end flag. */
				if(bExistChildNode)
				{
					for(GAIA::SIZE x = 0; x < sDepth; ++x)
					{
						*acc = '\t';
						++acc;
					}
					*acc = '<'; ++acc;
					*acc = '/'; ++acc;
					acc = GAIA::ALGO::stradd(acc, pNodeName);
					*acc = '>'; ++acc;
				}
				else
				{
					*acc = '/'; ++acc;
					*acc = '>'; ++acc;
				}
				acc = GAIA::ALGO::stradd(acc, m_lineflag.front_ptr());

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
		private: // Temp member variables.
			static const _SizeType CACHE_NODENAME_SIZE = 128;
			static const _SizeType CACHE_ATTRNAME_SIZE = 128;
			static const _SizeType CACHE_ATTRVALUE_SIZE = 1024;
			_CharType m_szTempNodeName[CACHE_NODENAME_SIZE + 1];
			_CharType m_szTempAttrName[CACHE_ATTRNAME_SIZE + 1];
			_CharType m_szTempAttrValue[CACHE_ATTRVALUE_SIZE + 1];
			__StringType m_strTempNodeName;
			__StringType m_strTempAttrName;
			__StringType m_strTempAttrValue;
		};
	};
};

#endif
