#ifndef		__PROM_CONTEXT_FILESTRUCTURE_H__
#define		__PROM_CONTEXT_FILESTRUCTURE_H__

namespace PROM
{
	class PLC_FileStructure : public PipelineContext
	{
	public:
		GINL PLC_FileStructure(){}
		GINL ~PLC_FileStructure(){}
		virtual const GAIA::TCH* GetName() const{return _T("Prom:PLC_FileStructure");}
	public:
		typedef GAIA::CTN::Set<__FileName> __FileLinkSet;
		class Node
		{
		public:
			GAIA_CLASS_OPERATOR_COMPARE(name, name, Node);
			__FileName name;
			__FileLinkSet parents;
			__FileLinkSet childs;
		};
		typedef GAIA::CTN::Set<Node> __FileNodeSet;
	public:
		GINL GAIA::BL AddLink(const GAIA::TCH* pszParentFile, const GAIA::TCH* pszChildFile)
		{
			GPCHR_NULLSTR_RET(pszParentFile, GAIA::False);
			GPCHR_NULLSTR_RET(pszChildFile, GAIA::False);
			if(this->IsLinkExist(pszParentFile, pszChildFile))
				return GAIA::True;
			Node* pFindedParent = this->FindNode(pszParentFile);
			if(pFindedParent == GNIL)
			{
				Node n;
				n.name = pszParentFile;
				filenodeset.insert(n);
				pFindedParent = filenodeset.find(n);
			}
			Node* pFindedChild = this->FindNode(pszChildFile);
			if(pFindedChild == GNIL)
			{
				Node n;
				n.name = pszChildFile;
				filenodeset.insert(n);
				pFindedChild = filenodeset.find(n);
			}
			GPCHR_NULL_RET(pFindedParent, GAIA::False);
			GPCHR_NULL_RET(pFindedChild, GAIA::False);
			pFindedParent->childs.insert(pszChildFile);
			pFindedChild->parents.insert(pszParentFile);
			return GAIA::True;
		}
		GINL GAIA::BL IsLinkExist(const GAIA::TCH* pszParentFile, const GAIA::TCH* pszChildFile) const
		{
			GPCHR_NULLSTR_RET(pszParentFile, GAIA::False);
			GPCHR_NULLSTR_RET(pszChildFile, GAIA::False);
			const Node* pFinded = this->FindNode(pszParentFile);
			if(pFinded != GNIL)
				if(pFinded->childs.find(pszChildFile) != GNIL)
					return GAIA::True;
			return GAIA::False;
		}
		GINL const Node* FindNode(const GAIA::TCH* pszFile) const
		{
			GPCHR_NULLSTR_RET(pszFile, GNIL);
			Node finder;
			finder.name = pszFile;
			return filenodeset.find(finder);
		}
		GINL Node* FindNode(const GAIA::TCH* pszFile)
		{
			GPCHR_NULLSTR_RET(pszFile, GNIL);
			Node finder;
			finder.name = pszFile;
			return filenodeset.find(finder);
		}
	public:
		__FileNodeSet filenodeset;
	};
};

#endif