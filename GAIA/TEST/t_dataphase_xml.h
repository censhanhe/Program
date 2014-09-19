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
		if(xml.Change(_T("NodeName"), GNIL))
		{
			GTLINE2("New XML object cannot change node name!");
			++nRet;
		}
		if(xml.Change(_T("AttrName"), _T("AttrValue")))
		{
			GTLINE2("New XML object cannot change attr name and value!");
			++nRet;
		}
		if(!xml.IsResetCursor())
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
		if(xml.Change(_T("NodeName"), GNIL))
		{
			GTLINE2("XML object cannot change node name after Clear!");
			++nRet;
		}
		if(xml.Change(_T("AttrName"), _T("AttrValue")))
		{
			GTLINE2("XML object cannot change attr name and value after Clear!");
			++nRet;
		}
		if(!xml.IsResetCursor())
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
		if(xml.Change(_T("NodeName"), GNIL))
		{
			GTLINE2("XML object cannot change node name after Destroy!");
			++nRet;
		}
		if(xml.Change(_T("AttrName"), _T("AttrValue")))
		{
			GTLINE2("XML object cannot change attr name and value after Destroy!");
			++nRet;
		}

		if(!xml.IsResetCursor())
		{
			GTLINE2("New XML object must IsResetCallStack after Destroy!");
			++nRet;
		}
		if(!xml.WriteNode(_T("ROOT_NODE")))
		{
			GTLINE2("XML write node failed!");
			++nRet;
		}
		if(xml.IsResetCursor())
		{
			GTLINE2("XML IsResetCallStack error!");
			++nRet;
		}
		if(!xml.End())
		{
			GTLINE2("XML End failed!");
			++nRet;
		}
		if(xml.IsResetCursor())
		{
			GTLINE2("XML IsResetCallStack error!");
			++nRet;
		}
		if(xml.WriteNode(_T("ROOT_NODE1")))
		{
			GTLINE2("XML must have one root node only!");
			++nRet;
		}
		if(xml.IsResetCursor())
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
		if(!xml.WriteAttr(_T("AttrName1"), _T("AttrValue1")))
		{
			GTLINE2("XML WriteAttr failed!");
			++nRet;
		}
		if(!xml.WriteAttr(_T("AttrName2"), _T("AttrValue2")))
		{
			GTLINE2("XML WriteAttr failed!");
			++nRet;
		}
		if(!xml.WriteAttr(_T("AttrName3"), _T("AttrValue3")))
		{
			GTLINE2("XML WriteAttr failed!");
			++nRet;
		}
		if(xml.WriteAttr(_T("AttrName1"), _T("AttrValue1")))
		{
			GTLINE2("XML WriteAttr write same name attr!");
			++nRet;
		}
		if(xml.WriteAttr(_T("AttrName2"), _T("AttrValue2")))
		{
			GTLINE2("XML WriteAttr write same name attr!");
			++nRet;
		}
		if(xml.WriteAttr(_T("AttrName3"), _T("AttrValue3")))
		{
			GTLINE2("XML WriteAttr write same name attr!");
			++nRet;
		}
		if(xml.IsResetCursor())
		{
			GTLINE2("XML IsResetCallStack error!");
			++nRet;
		}
		for(GAIA::SIZE x = 0; x < 3; ++x)
		{
			if(xml.IsResetCursor())
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
			if(!xml.WriteAttr(_T("AttrName11"), _T("AttrValue11")))
			{
				GTLINE2("XML WriteAttr failed!");
				++nRet;
				break;
			}
			if(!xml.WriteAttr(_T("AttrName22"), _T("AttrValue22")))
			{
				GTLINE2("XML WriteAttr failed!");
				++nRet;
				break;
			}
			if(!xml.WriteAttr(_T("AttrName33"), _T("AttrValue33")))
			{
				GTLINE2("XML WriteAttr failed!");
				++nRet;
				break;
			}
			if(xml.WriteAttr(_T("AttrName11"), _T("AttrValue11")))
			{
				GTLINE2("XML WriteAttr write same name attr!");
				++nRet;
				break;
			}
			if(xml.WriteAttr(_T("AttrName22"), _T("AttrValue22")))
			{
				GTLINE2("XML WriteAttr write same name attr!");
				++nRet;
				break;
			}
			if(xml.WriteAttr(_T("AttrName33"), _T("AttrValue33")))
			{
				GTLINE2("XML WriteAttr write same name attr!");
				++nRet;
				break;
			}
			GAIA::BL bExistError = GAIA::False;
			for(GAIA::SIZE y = 0; y < 3; ++y)
			{
				if(xml.IsResetCursor())
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
				if(!xml.WriteAttr(_T("AttrName111"), _T("AttrValue111")))
				{
					GTLINE2("XML WriteAttr failed!");
					++nRet;
					bExistError = GAIA::True;
					break;
				}
				if(!xml.WriteAttr(_T("AttrName222"), _T("AttrValue222")))
				{
					GTLINE2("XML WriteAttr failed!");
					++nRet;
					bExistError = GAIA::True;
					break;
				}
				if(!xml.WriteAttr(_T("AttrName333"), _T("AttrValue333")))
				{
					GTLINE2("XML WriteAttr failed!");
					++nRet;
					bExistError = GAIA::True;
					break;
				}
				if(xml.WriteAttr(_T("AttrName111"), _T("AttrValue111")))
				{
					GTLINE2("XML WriteAttr write same name attr!");
					++nRet;
					bExistError = GAIA::True;
					break;
				}
				if(xml.WriteAttr(_T("AttrName222"), _T("AttrValue222")))
				{
					GTLINE2("XML WriteAttr write same name attr!");
					++nRet;
					bExistError = GAIA::True;
					break;
				}
				if(xml.WriteAttr(_T("AttrName333"), _T("AttrValue333")))
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
		if(xml.IsResetCursor())
		{
			GTLINE2("XML IsResetCallStack error!");
			++nRet;
		}
		if(xml.WriteNode(_T("ROOT_NODE1")))
		{
			GTLINE2("XML must have one root node only!");
			++nRet;
		}
		if(xml.IsResetCursor())
		{
			GTLINE2("XML IsResetCallStack error!");
			++nRet;
		}

		GAIA::FILESYSTEM::File xmlfile;
		if(!xmlfile.Open(_T("../TESTRES/xmlfile.xml"), 
			GAIA::FILESYSTEM::File::OPEN_TYPE_READ |
			GAIA::FILESYSTEM::File::OPEN_TYPE_WRITE |
			GAIA::FILESYSTEM::File::OPEN_TYPE_CREATEALWAYS))
		{
			GTLINE2("Cannot open a file for save the xml.");
			++nRet;
		}
		else
		{
			typedef GAIA::CTN::Accesser<GAIA::TCH, GAIA::SIZE, GAIA::ALGO::TwiceSizeIncreaser<GAIA::SIZE> > __AccType;
			__AccType acc;
			acc.expandable(GAIA::True);
			if(!acc.bindfile(&xmlfile, __AccType::ACCESS_TYPE_READ | __AccType::ACCESS_TYPE_WRITE))
			{
				GTLINE2("Bind accesser to the file failed!");
				++nRet;
			}
			else
			{
				if(!xml.Save(acc, GAIA::CHARSET_TYPE_UTF16LE))
				{
					GTLINE2("Save xml to file failed!");
					++nRet;
				}
			}
		}
		xmlfile.Close();

		if(!xmlfile.Open(_T("../TESTRES/xmlfile.xml"),
			GAIA::FILESYSTEM::File::OPEN_TYPE_READ))
		{
			GTLINE2("Cannot open a file for load the xml.");
			++nRet;
		}
		else
		{
			typedef GAIA::CTN::Accesser<GAIA::TCH, GAIA::SIZE, GAIA::ALGO::TwiceSizeIncreaser<GAIA::SIZE> > __AccType;
			__AccType acc;
			if(!acc.bindfile(&xmlfile, __AccType::ACCESS_TYPE_READ))
			{
				GTLINE2("Bind accesser to file failed!");
				++nRet;
			}
			else
			{
				if(!xml.Load(acc))
				{
					GTLINE2("Load xml from file failed!");
					++nRet;
				}
			}
		}

		static const GAIA::TCH* CONTENT_GROUP[] = 
		{
			_T("ROOT_NODE"),
			_T("AttrName1"), _T("AttrValue1"),
			_T("AttrName2"), _T("AttrValue2"),
			_T("AttrName3"), _T("AttrValue3"),
				_T("NODE"),
				_T("AttrName11"), _T("AttrValue11"),
				_T("AttrName22"), _T("AttrValue22"),
				_T("AttrName33"), _T("AttrValue33"),
					_T("SUB_NODE"),
					_T("AttrName111"), _T("AttrValue111"),
					_T("AttrName222"), _T("AttrValue222"),
					_T("AttrName333"), _T("AttrValue333"),
					_T("SUB_NODE"),
					_T("AttrName111"), _T("AttrValue111"),
					_T("AttrName222"), _T("AttrValue222"),
					_T("AttrName333"), _T("AttrValue333"),
					_T("SUB_NODE"),
					_T("AttrName111"), _T("AttrValue111"),
					_T("AttrName222"), _T("AttrValue222"),
					_T("AttrName333"), _T("AttrValue333"),
				_T("NODE"),
				_T("AttrName11"), _T("AttrValue11"),
				_T("AttrName22"), _T("AttrValue22"),
				_T("AttrName33"), _T("AttrValue33"),
					_T("SUB_NODE"),
					_T("AttrName111"), _T("AttrValue111"),
					_T("AttrName222"), _T("AttrValue222"),
					_T("AttrName333"), _T("AttrValue333"),
					_T("SUB_NODE"),
					_T("AttrName111"), _T("AttrValue111"),
					_T("AttrName222"), _T("AttrValue222"),
					_T("AttrName333"), _T("AttrValue333"),
					_T("SUB_NODE"),
					_T("AttrName111"), _T("AttrValue111"),
					_T("AttrName222"), _T("AttrValue222"),
					_T("AttrName333"), _T("AttrValue333"),
				_T("NODE"),
				_T("AttrName11"), _T("AttrValue11"),
				_T("AttrName22"), _T("AttrValue22"),
				_T("AttrName33"), _T("AttrValue33"),
					_T("SUB_NODE"),
					_T("AttrName111"), _T("AttrValue111"),
					_T("AttrName222"), _T("AttrValue222"),
					_T("AttrName333"), _T("AttrValue333"),
					_T("SUB_NODE"),
					_T("AttrName111"), _T("AttrValue111"),
					_T("AttrName222"), _T("AttrValue222"),
					_T("AttrName333"), _T("AttrValue333"),
					_T("SUB_NODE"),
					_T("AttrName111"), _T("AttrValue111"),
					_T("AttrName222"), _T("AttrValue222"),
					_T("AttrName333"), _T("AttrValue333"),
		};
		xml.ResetCursor();
		if(!xml.IsResetCursor())
		{
			GTLINE2("XML IsResetCursor failed!");
			++nRet;
		}
		GAIA::SIZE index = 0;
		for(;;)
		{
			if(!xml.Enum(cmnname, cmnvalue))
			{
				GTLINE2("XML Enum failed!");
				++nRet;
				break;
			}
			if(GAIA::ALGO::strcmp(cmnname, CONTENT_GROUP[index++]) != 0)
			{
				GTLINE2("XML Enum content error!");
				++nRet;
				break;
			}
			if(cmnvalue != GNIL && GAIA::ALGO::strcmp(cmnvalue, CONTENT_GROUP[index++]) != 0)
			{
				GTLINE2("XML Enum content error!");
				++nRet;
				break;
			}
			if(index == sizeofarray(CONTENT_GROUP))
			{
				if(xml.Enum(cmnname, cmnvalue))
				{
					GTLINE2("XML Enum failed! all content has been enumed.");
					++nRet;
				}
				break;
			}
		}
		if(xml.IsResetCursor())
		{
			GTLINE2("XML Enum failed!");
			++nRet;
		}

		xml.ResetCursor();
		if(!xml.IsResetCursor())
		{
			GTLINE2("XML IsResetCursor failed!");
			++nRet;
		}

		return nRet;
	}
};

#endif