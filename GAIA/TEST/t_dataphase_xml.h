#ifndef		__T_DATAPHASE_XML_H__
#define		__T_DATAPHASE_XML_H__

namespace GAIATEST
{
	GINL GAIA::N32 t_dataphase_xml(GAIA::FILESYSTEM::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;

		typedef GAIA::DATAPHASE::XML<GAIA::TCH, GAIA::SIZE, GAIA::ALGO::TwiceSizeIncreaser<GAIA::SIZE> > __XMLType;

		__XMLType xml;
		__XMLType::__ConstCharPtrType nname, aname, avalue, cmnname, cmnvalue;

		if(xml.EnumNode(nname))
		{
			GTLINE2("New XML object must cannot EnumNode!");
			++nRet;
		}
		if(xml.EnumAttr(aname, avalue))
		{
			GTLINE2("New XML object must cannot EnumAttr!");
			++nRet;
		}
		if(xml.Enum(cmnname, cmnvalue))
		{
			GTLINE2("New XML object must cannot Enum!");
			++nRet;
		}
		if(xml.Change(_T("NodeName"), GNULL))
		{
			GTLINE2("New XML object cannot change node name!");
			++nRet;
		}
		if(xml.Change(_T("AttrName"), _T("AttrValue")))
		{
			GTLINE2("New XML object cannot change attr name and value!");
			++nRet;
		}
		if(!xml.IsResetCallStack())
		{
			GTLINE2("New XML object must IsResetCallStack!");
			++nRet;
		}

		xml.Clear();
		if(xml.EnumNode(nname))
		{
			GTLINE2("XML object must cannot EnumNode after Clear!");
			++nRet;
		}
		if(xml.EnumAttr(aname, avalue))
		{
			GTLINE2("XML object must cannot EnumAttr after Clear!");
			++nRet;
		}
		if(xml.Enum(cmnname, cmnvalue))
		{
			GTLINE2("XML object must cannot Enum after Clear!");
			++nRet;
		}
		if(xml.Change(_T("NodeName"), GNULL))
		{
			GTLINE2("XML object cannot change node name after Clear!");
			++nRet;
		}
		if(xml.Change(_T("AttrName"), _T("AttrValue")))
		{
			GTLINE2("XML object cannot change attr name and value after Clear!");
			++nRet;
		}
		if(!xml.IsResetCallStack())
		{
			GTLINE2("New XML object must IsResetCallStack after Clear!");
			++nRet;
		}

		xml.Destroy();
		if(xml.EnumNode(nname))
		{
			GTLINE2("XML object must cannot EnumNode after Destroy!");
			++nRet;
		}
		if(xml.EnumAttr(aname, avalue))
		{
			GTLINE2("XML object must cannot EnumAttr after Destroy!");
			++nRet;
		}
		if(xml.Enum(cmnname, cmnvalue))
		{
			GTLINE2("XML object must cannot Enum after Destroy!");
			++nRet;
		}
		if(xml.Change(_T("NodeName"), GNULL))
		{
			GTLINE2("XML object cannot change node name after Destroy!");
			++nRet;
		}
		if(xml.Change(_T("AttrName"), _T("AttrValue")))
		{
			GTLINE2("XML object cannot change attr name and value after Destroy!");
			++nRet;
		}

		if(!xml.IsResetCallStack())
		{
			GTLINE2("New XML object must IsResetCallStack after Destroy!");
			++nRet;
		}
		if(!xml.WriteNode(_T("ROOT_NODE")))
		{
			GTLINE2("XML write node failed!");
			++nRet;
		}
		if(xml.IsResetCallStack())
		{
			GTLINE2("XML IsResetCallStack error!");
			++nRet;
		}
		if(!xml.End())
		{
			GTLINE2("XML End failed!");
			++nRet;
		}
		if(!xml.IsResetCallStack())
		{
			GTLINE2("XML IsResetCallStack error!");
			++nRet;
		}
		if(xml.WriteNode(_T("ROOT_NODE1")))
		{
			GTLINE2("XML must have one root node only!");
			++nRet;
		}
		if(!xml.IsResetCallStack())
		{
			GTLINE2("XML IsResetCallStack error!");
			++nRet;
		}

		xml.Clear();
		if(!xml.WriteNode(_T("ROOT_NODE")))
		{
			GTLINE2("XML WriteNode failed!");
			++nRet;
		}
		if(!xml.WriteAttr(_T("AttrName1"), _T("AttrName1")))
		{
			GTLINE2("XML WriteAttr failed!");
			++nRet;
		}
		if(!xml.WriteAttr(_T("AttrName2"), _T("AttrName2")))
		{
			GTLINE2("XML WriteAttr failed!");
			++nRet;
		}
		if(!xml.WriteAttr(_T("AttrName3"), _T("AttrName3")))
		{
			GTLINE2("XML WriteAttr failed!");
			++nRet;
		}
		if(xml.WriteAttr(_T("AttrName1"), _T("AttrName1")))
		{
			GTLINE2("XML WriteAttr write same name attr!");
			++nRet;
		}
		if(xml.WriteAttr(_T("AttrName2"), _T("AttrName2")))
		{
			GTLINE2("XML WriteAttr write same name attr!");
			++nRet;
		}
		if(xml.WriteAttr(_T("AttrName3"), _T("AttrName3")))
		{
			GTLINE2("XML WriteAttr write same name attr!");
			++nRet;
		}
		if(xml.IsResetCallStack())
		{
			GTLINE2("XML IsResetCallStack error!");
			++nRet;
		}
		for(GAIA::SIZE x = 0; x < 10; ++x)
		{
			if(xml.IsResetCallStack())
			{
				GTLINE2("XML IsResetCallStack error!");
				++nRet;
				break;
			}
			if(!xml.WriteNode(_T("NODE")))
			{
				GTLINE2("XML WriteNode failed!"); 
				++nRet;
				break;
			}
			if(!xml.WriteAttr(_T("AttrName11"), _T("AttrName11")))
			{
				GTLINE2("XML WriteAttr failed!");
				++nRet;
				break;
			}
			if(!xml.WriteAttr(_T("AttrName22"), _T("AttrName22")))
			{
				GTLINE2("XML WriteAttr failed!");
				++nRet;
				break;
			}
			if(!xml.WriteAttr(_T("AttrName33"), _T("AttrName33")))
			{
				GTLINE2("XML WriteAttr failed!");
				++nRet;
				break;
			}
			if(xml.WriteAttr(_T("AttrName11"), _T("AttrName11")))
			{
				GTLINE2("XML WriteAttr write same name attr!");
				++nRet;
				break;
			}
			if(xml.WriteAttr(_T("AttrName22"), _T("AttrName22")))
			{
				GTLINE2("XML WriteAttr write same name attr!");
				++nRet;
				break;
			}
			if(xml.WriteAttr(_T("AttrName33"), _T("AttrName33")))
			{
				GTLINE2("XML WriteAttr write same name attr!");
				++nRet;
				break;
			}
			GAIA::BL bExistError = GAIA::False;
			for(GAIA::SIZE y = 0; y < 10; ++y)
			{
				if(xml.IsResetCallStack())
				{
					GTLINE2("XML IsResetCallStack error!");
					++nRet;
					bExistError = GAIA::True;
					break;
				}
				if(!xml.WriteNode(_T("SUB_NODE")))
				{
					GTLINE2("XML WriteNode failed!"); 
					++nRet;
					bExistError = GAIA::True;
					break;
				}
				if(!xml.WriteAttr(_T("AttrName111"), _T("AttrName111")))
				{
					GTLINE2("XML WriteAttr failed!");
					++nRet;
					bExistError = GAIA::True;
					break;
				}
				if(!xml.WriteAttr(_T("AttrName222"), _T("AttrName222")))
				{
					GTLINE2("XML WriteAttr failed!");
					++nRet;
					bExistError = GAIA::True;
					break;
				}
				if(!xml.WriteAttr(_T("AttrName333"), _T("AttrName333")))
				{
					GTLINE2("XML WriteAttr failed!");
					++nRet;
					bExistError = GAIA::True;
					break;
				}
				if(xml.WriteAttr(_T("AttrName111"), _T("AttrName111")))
				{
					GTLINE2("XML WriteAttr write same name attr!");
					++nRet;
					bExistError = GAIA::True;
					break;
				}
				if(xml.WriteAttr(_T("AttrName222"), _T("AttrName222")))
				{
					GTLINE2("XML WriteAttr write same name attr!");
					++nRet;
					bExistError = GAIA::True;
					break;
				}
				if(xml.WriteAttr(_T("AttrName333"), _T("AttrName333")))
				{
					GTLINE2("XML WriteAttr write same name attr!");
					++nRet;
					bExistError = GAIA::True;
					break;
				}
				if(!xml.End())
				{
					GTLINE2("XML End failed!");
					++nRet;
					bExistError = GAIA::True;
					break;
				}
			}
			if(bExistError)
				break;
			if(!xml.End())
			{
				GTLINE2("XML End failed!");
				++nRet;
				break;
			}
		}
		if(!xml.End())
		{
			GTLINE2("XML End failed!");
			++nRet;
		}
		if(!xml.IsResetCallStack())
		{
			GTLINE2("XML IsResetCallStack error!");
			++nRet;
		}
		if(xml.WriteNode(_T("ROOT_NODE1")))
		{
			GTLINE2("XML must have one root node only!");
			++nRet;
		}
		if(!xml.IsResetCallStack())
		{
			GTLINE2("XML IsResetCallStack error!");
			++nRet;
		}

		return nRet;
	}
};

#endif