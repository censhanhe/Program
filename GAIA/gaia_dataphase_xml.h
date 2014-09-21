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
			typedef GAIA::CTN::Accesser<GAIA::U8, _SizeType, _SizeIncreaserType> __BinaryAccesserType;
			typedef GAIA::CTN::BasicString<_CharType, _SizeType> __StringType;
		public:
			GINL XML(){this->init();}
			GINL ~XML(){this->Destroy();}
			GINL GAIA::BL Load(__AccesserType& acc)
			{
				__BinaryAccesserType tacc = acc;
				CHUNK_TYPE cts;
				if(tacc.read(&cts, sizeof(cts)) != sizeof(cts))
					return GAIA::False;
				if(cts == CHUNK_TYPE_XML)
					return this->LoadBinary(acc);
				else
					return this->LoadText(acc);
			}
			GINL GAIA::BL LoadText(__AccesserType& acc)
			{
				/* Destroy first. */
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
				if(!this->LoadNodeText(acc))
					return GAIA::False;
				return GAIA::True;
			}
			GINL GAIA::BL SaveText(__AccesserType& acc, GAIA::CHARSET_TYPE cst)
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
				if(!this->SaveNodeText(0, *m_root, acc))
					return GAIA::False;
				return GAIA::True;
			}
			GINL GAIA::BL LoadBinary(__AccesserType& acc)
			{
				/* Destroy first. */
				this->Destroy();

				/* Convert to binary acc. */
				__BinaryAccesserType tacc = acc;

				/* Load chunk head. */
				GAIA::FSYS::CHUNK_TYPE ct;
				if(!tacc.read(ct))
					return GAIA::False;
				if(ct != GAIA::FSYS::CHUNK_TYPE_XML)
					return GAIA::False;
				GAIA::FSYS::CHUNK_SIZE cs;
				if(!tacc.read(cs))
					return GAIA::False;
				GAIA_AST(cs != GINVALID);

				/* Load static string pool. */
				_SizeType stringsize;
				if(!tacc.read(stringsize))
					return GAIA::False;
				for(_SizeType x = 0; x < stringsize; ++x)
				{
					GAIA::U16 uStringLen;
					if(!tacc.read(uStringLen))
						return GAIA::False;
					if(uStringLen <= CACHE_VALUE_SIZE)
					{
						tacc.read(m_szTempValue, uStringLen);
						m_szTempValue[uStringLen] = '\0';
						m_ssp.alloc(m_szTempValue);
					}
					else
					{
						m_strTempValue.resize(uStringLen);
						tacc.read(m_strTempValue.front_ptr(), uStringLen);
						m_ssp.alloc(m_strTempValue.front_ptr());
					}
				}

				/* Load node. */
				GAIA::BL bExistRoot;
				if(!tacc.read(bExistRoot))
					return GAIA::False;
				if(!bExistRoot)
					return GAIA::False;
				return this->LoadNodeBinary(tacc);
			}
			GINL GAIA::BL SaveBinary(__AccesserType& acc)
			{
				if(m_root == GNIL)
					return GAIA::False;
				__BinaryAccesserType tacc = acc;

				/* Save chunk head. */
				if(!tacc.write(GAIA::FSYS::CHUNK_TYPE_XML))
					return GAIA::False;
				GAIA::FSYS::CHUNK_SIZE chunk_size = GINVALID;
				_SizeType chunk_size_index = tacc.index();
				if(!tacc.write(chunk_size))
					return GAIA::False;

				/* Construct static string pool. */
				__SSPType ssp;
				__ConstCharPtrType pName, pValue;
				while(this->Enum(pName, pValue))
				{
					ssp.alloc(pName);
					if(pValue != GNIL)
						ssp.alloc(pValue);
				}

				/* Save static string pool. */
				_SizeType stringsize = ssp.string_size();
				if(!tacc.write(stringsize))
					return GAIA::False;
				for(_SizeType x = 0; x < stringsize; ++x)
				{
					__ConstCharPtrType pString = ssp.get(x);
					GAIA_AST(pString != GNIL);
					GAIA::U16 uStringLen = GSCAST(GAIA::U16)(GAIA::ALGO::strlen(pString));
					if(!tacc.write(uStringLen))
						return GAIA::False;
					if(tacc.write(pString, uStringLen * sizeof(_CharType)) != uStringLen * sizeof(_CharType))
						return GAIA::False;
				}

				/* Save node. */
				if(m_root != GNIL)
				{
					GAIA::BL bExistRoot = GAIA::True;
					if(!tacc.write(bExistRoot))
						return GAIA::False;
					if(!this->SaveNodeBinary(ssp, *m_root, tacc))
						return GAIA::False;
				}
				else
				{
					GAIA::BL bExistRoot = GAIA::False;
					if(!tacc.write(bExistRoot))
						return GAIA::False;
				}

				/* Write chunk size. */
				chunk_size = GSCAST(GAIA::FSYS::CHUNK_SIZE)(tacc.index());
				tacc.index(chunk_size_index);
				if(!tacc.write(chunk_size))
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
					if(this->IsAttrExist(*pNode, pName))
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
				if(this->IsAttrExist(*m_callstack.back().pNode, pAttrName))
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
			GINL GAIA::BL IsAttrExist(const Node& node, const _CharType* pAttrName) const
			{
				GAIA_AST(pAttrName != GNIL);
				for(__AttrListType::_sizetype x = 0; x < node.attrs.size(); ++x)
				{
					const Attr& a = node.attrs[x];
					if(GAIA::ALGO::strcmp(m_ssp.get(a.name), pAttrName) == 0)
						return GAIA::True;
				}
				return GAIA::False;
			}
			GINL _SizeType GetAttrPracCount(const Node& node) const
			{
				_SizeType ret = 0;
				for(_SizeType x = 0; x < node.attrs.size(); ++x)
				{
					const Attr& attr = node.attrs[x];
					if(attr.name == GINVALID)
						continue;
					GAIA_AST(attr.value != GINVALID);
					++ret;
				}
				return ret;
			}
			GINL _SizeType GetChildNodePracCount(const Node& node) const
			{
				_SizeType ret = 0;
				for(_SizeType x = 0; x < node.nodes.size(); ++x)
				{
					if(node.nodes[x] != GNIL)
						++ret;
				}
				return ret;
			}
			GINL GAIA::BL LoadAttrText(__AccesserType& acc)
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
					if(newacc - acc > CACHE_NAME_SIZE)
					{
						m_strTempName.clear();
						m_strTempName.resize(newacc - acc);
						GAIA::ALGO::strcpy(m_strTempName.front_ptr(), acc, newacc - acc);
						pAttrName = m_strTempName;
					}
					else
					{
						GAIA::ALGO::strcpy(m_szTempName, acc, newacc - acc);
						pAttrName = m_szTempName;
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
					if(newacc - acc > CACHE_NAME_SIZE)
					{
						m_strTempValue.clear();
						m_strTempValue.resize(newacc - acc);
						GAIA::ALGO::strcpy(m_strTempValue.front_ptr(), acc, newacc - acc);
						pAttrValue = m_strTempValue;
					}
					else
					{
						GAIA::ALGO::strcpy(m_szTempValue, acc, newacc - acc);
						pAttrValue = m_szTempValue;
					}
					acc = newacc;
					++acc;

					/* Write attr. */
					this->WriteAttr(pAttrName, pAttrValue);
				}
				return GAIA::True;
			}
			GINL GAIA::BL LoadNodeText(__AccesserType& acc)
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
				if(newacc - acc > CACHE_NAME_SIZE)
				{
					m_strTempName.clear();
					m_strTempName.resize(newacc - acc);
					GAIA::ALGO::strcpy(m_strTempName.front_ptr(), acc, newacc - acc);
					this->WriteNode(m_strTempName);
				}
				else
				{
					GAIA::ALGO::strcpy(m_szTempName, acc, newacc - acc);
					this->WriteNode(m_szTempName);
				}
				acc = newacc;

				/* Load attributes. */
				if(!this->LoadAttrText(acc))
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
					if(!this->LoadNodeText(acc))
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
			GINL GAIA::BL SaveNodeText(const GAIA::SIZE& sDepth, const Node& node, __AccesserType& acc) const
			{
				/* Write tabs by depth. */
				for(GAIA::SIZE x = 0; x < sDepth; ++x)
				{
					*acc = '\t';
					++acc;
				}

				/* Write node name. */
				*acc = '<'; ++acc;
				const _CharType* pNodeName = m_ssp.get(node.name);
				_SizeType sNodeLen = GAIA::ALGO::strlen(pNodeName);
				acc = GAIA::ALGO::stradd(acc, pNodeName);

				/* Write node attr.*/
				for(_SizeType x = 0; x < node.attrs.size(); ++x)
				{
					const Attr& attr = node.attrs[x];
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
				for(_SizeType x = 0; x < node.nodes.size(); ++x)
				{
					Node* pChildNode = node.nodes[x];
					if(pChildNode == GNIL)
						continue;
					if(!bExistChildNode)
					{
						*acc = '>'; ++acc;
						acc = GAIA::ALGO::stradd(acc, m_lineflag.front_ptr());
						bExistChildNode = GAIA::True;
					}
					if(!this->SaveNodeText(sDepth + 1, *pChildNode, acc))
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
			GINL GAIA::BL LoadNodeBinary(__BinaryAccesserType& acc)
			{
				/* Load node name. */
				_SizeType nodenameindex;
				if(!acc.read(nodenameindex))
					return GAIA::False;
				__ConstCharPtrType pNodeName = m_ssp.get(nodenameindex);
				GAIA_AST(pNodeName != GNIL);
				this->WriteNode(pNodeName);

				/* Load node attr. */
				_SizeType attrpraccount;
				if(!acc.read(attrpraccount))
					return GAIA::False;
				for(_SizeType x = 0; x < attrpraccount; ++x)
				{
					_SizeType attrnameindex;
					if(!acc.read(attrnameindex))
						return GAIA::False;
					_SizeType attrvalueindex;
					if(!acc.read(attrvalueindex))
						return GAIA::False;
					__ConstCharPtrType pAttrName = m_ssp.get(attrnameindex);
					__ConstCharPtrType pAttrValue = m_ssp.get(attrvalueindex);
					GAIA_AST(pAttrName != GNIL);
					GAIA_AST(pAttrValue != GNIL);
					this->WriteAttr(pAttrName, pAttrValue);
				}

				/* Load child node. */
				_SizeType childnodepraccount;
				if(!acc.read(childnodepraccount))
					return GAIA::False;
				for(_SizeType x = 0; x < childnodepraccount; ++x)
				{
					if(!this->LoadNodeBinary(acc))
						return GAIA::False;
				}

				this->End();
				return GAIA::True;
			}
			GINL GAIA::BL SaveNodeBinary(__SSPType& ssp, const Node& node, __BinaryAccesserType& acc) const
			{
				/* Save node name. */
				__ConstCharPtrType pNodeName = m_ssp.get(node.name);
				GAIA_AST(!GAIA::ALGO::stremp(pNodeName));
				_SizeType nodenameindex = ssp.alloc(pNodeName);
				if(!acc.write(nodenameindex))
					return GAIA::False;

				/* Save node attr. */
				_SizeType attrpraccount = this->GetAttrPracCount(node);
				if(!acc.write(attrpraccount))
					return GAIA::False;
				for(_SizeType x = 0; x < node.attrs.size(); ++x)
				{
					const Attr& attr = node.attrs[x];
					if(attr.name == GINVALID)
						continue;
					__ConstCharPtrType pAttrName = m_ssp.get(attr.name);
					__ConstCharPtrType pAttrValue = m_ssp.get(attr.value);
					GAIA_AST(!GAIA::ALGO::stremp(pAttrName));
					GAIA_AST(pAttrValue != GNIL);
					_SizeType attrnameindex = ssp.alloc(pAttrName);
					_SizeType attrvalueindex = ssp.alloc(pAttrValue);
					if(!acc.write(attrnameindex))
						return GAIA::False;
					if(!acc.write(attrvalueindex))
						return GAIA::False;
				}

				/* Save child node. */
				_SizeType childnodepraccount = this->GetChildNodePracCount(node);
				if(!acc.write(childnodepraccount))
					return GAIA::False;
				for(_SizeType x = 0; x < node.nodes.size(); ++x)
				{
					const Node* pChild = node.nodes[x];
					if(pChild == GNIL)
						continue;
					GAIA_AST(pChild->name != GINVALID);
					if(!this->SaveNodeBinary(ssp, *pChild, acc))
						return GAIA::False;
				}

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
			static const _SizeType CACHE_NAME_SIZE = 128;
			static const _SizeType CACHE_VALUE_SIZE = 1024;
			_CharType m_szTempName[CACHE_NAME_SIZE + 1];
			_CharType m_szTempValue[CACHE_VALUE_SIZE + 1];
			__StringType m_strTempName;
			__StringType m_strTempValue;
		};
	};
};

#endif
