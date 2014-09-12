#ifndef		__GAIA_DATA_ANALYZE_XML_H__
#define		__GAIA_DATA_ANALYZE_XML_H__

namespace GAIA
{
	namespace DATAPHASE
	{
		template<typename _StringType, typename _StringLengthType, typename _DataSizeType> class XML : public GAIA::Entity
		{
		public:
			typedef GAIA::CONTAINER::BasicString<_StringType, _StringLengthType> __StringType;
		public:
			GINL XML(){}
			GINL ~XML(){}
			GINL GAIA::BL Load(GAIA::FILESYSTEM::FileBase& file);
			GINL GAIA::BL Save(GAIA::FILESYSTEM::FileBase& file) const;
			GINL GAIA::BL Load(GAIA::CONTAINER::BasicBuffer<GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::U32>, GAIA::U32>& buf);
			GINL GAIA::BL Save(GAIA::CONTAINER::BasicBuffer<GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::U32>, GAIA::U32>& buf) const;
			GINL GAIA::BL EnumNode(__StringType& strNode);
			GINL GAIA::BL EnumNodeEnd();
			GINL GAIA::BL EnumAttr(__StringType& strAttrName, __StringType& strAttrValue);
			GINL GAIA::BL WriteNode(const __StringType& strNode);
			GINL GAIA::BL WriteNodeEnd();
			GINL GAIA::BL WriteAttr(const __StringType& strAttrName, const __StringType& strAttrValue);
			GINL _DataSizeType GetNodeCount() const;
			GINL const _StringType* GetNodeName(const _DataSizeType& uNode) const;
			GINL GAIA::BL SetNodeName(const _DataSizeType& uNode, const _StringType* pNodeName);
			GINL _DataSizeType AddNode(const _StringType* pNodeName);
			GINL GAIA::BL DeleteNode(const _DataSizeType& uNode);
			GINL GAIA::BL DeleteNodeAll();
			GINL _DataSizeType GetNodeByName(const _StringType* pNodeName);
			GINL _DataSizeType GetAttrCount(const _DataSizeType& uNode) const;
			GINL const _StringType* GetAttrName(const _DataSizeType& uNode, const _DataSizeType& uAttr) const;
			GINL const _StringType* GetAttrValue(const _DataSizeType& uNode, const _DataSizeType& uAttr) const;
			GINL GAIA::BL SetAttrName(const _DataSizeType& uNode, const _DataSizeType& uAttr, const _StringType* pAttrName);
			GINL GAIA::BL SetAttrValue(const _DataSizeType& uNode, const _DataSizeType& uAttr, const _StringType* pAttrValue);
			GINL _DataSizeType AddAttr(const _DataSizeType& uNode, const _StringType* pAttrName, const _StringType* pAttrValue);
			GINL GAIA::BL DeleteAttr(const _DataSizeType& uNode, const _DataSizeType& uAttr);
			GINL GAIA::BL DeleteAttrAll(const _DataSizeType& uNode);
			GINL _DataSizeType GetAttrByName(const _DataSizeType& uNode, const _StringType* pAttrName);
		private:
			class Attr : public GAIA::Base
			{
			public:
				_StringType* pName;
				_StringType* pValue;
			};
			class Node : public GAIA::Base
			{
			public:
				_StringType* pName;
				GAIA::CONTAINER::Vector<Attr> attrs;
			};
		private:
			GAIA::CONTAINER::Vector<Node> m_nodes;
		};
	};
};

#endif
