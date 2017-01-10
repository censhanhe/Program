#ifndef		__GAIA_FRAMEWORK_FACTORY_IMPL_H__
#define		__GAIA_FRAMEWORK_FACTORY_IMPL_H__

namespace GAIA
{
	namespace FWORK
	{
		GINL Instance* GAIA::FWORK::Factory::CreateInstance(const ClsID& cid, GAIA::GVOID* pParameter)
		{
			if(cid.IsInvalid())
				return GNIL;

			/* Check the cid is registed. */
			if(!this->IsRegistedClsID(cid))
				return GNIL;

			/* Find create instance proc and allocate instance. */
			Instance* pRet = GNIL;
			{
				CLSIDNODE finder;
				finder.cid = cid;
				CLSIDNODE* pFinded = GNIL;
				if(this->IsBeginRegistClsID())
					pFinded = m_PrepareRegClsIDSet.find(finder);
				else
				{
					__ClsIDListType::_sizetype index = m_RegClsIDList.search(finder);
					if(index != GINVALID)
						pFinded = &m_RegClsIDList[index];
				}
				if(pFinded != GNIL && pFinded->proc != GNIL)
				{
					pRet = pFinded->proc();
				#ifdef GAIA_DEBUG_SELFCHECKROUTINE
					if(pRet != GNIL)
					{
						GAIA_AST(pRet->GetClassID() == cid);
						if(pRet->GetClassID() != cid)
						{
							pRet->Release();
							return GNIL;
						}
					}
				#endif
				}
			}

			/* If cannot create instance by internal proc, create it by user. */
			if(pRet == GNIL)
			{
				for(LIST_CREATECALLBACK::_sizetype x = 0; x < m_listCreateCB.size(); ++x)
				{
					CreateCallBack* pCallBack = m_listCreateCB[x];
					pRet = pCallBack->Create(this, cid);
					if(pRet != GNIL)
						break;
				}
			}

			/* Instance initialize. */
			if(pRet != GNIL)
			{
				pRet->SetFactory(this);
				if(!pRet->InstanceBegin(pParameter))
				{
					pRet->Release();
					pRet = GNIL;
				}
			}

			return pRet;
		}
		GINL Instance* GAIA::FWORK::Factory::RequestInstance(const ClsID& cid, GAIA::GVOID* pParameter)
		{
			return GNIL;
		}
		GINL GAIA::GVOID GAIA::FWORK::Factory::GenerateCreator()
		{
			GAIA_AST(!this->IsBeginRegistClsID());
			if(this->IsBeginRegistClsID())
				return;

#define GAIA_MAPPING_CREATEINSTANCEPROC(declcid)\
			{\
				CLSIDNODE finder;\
				finder.cid = declcid;\
				__ClsIDListType::_sizetype index = m_RegClsIDList.search(finder);\
				if(index != GINVALID)\
					m_RegClsIDList[index].proc = GAIA::FWORK::INSTCREATOR::declcid##_PROC;\
			}

			GAIA_MAPPING_CREATEINSTANCEPROC(CLSID_DATATRAFFIC_GATEWAYMEM);
			GAIA_MAPPING_CREATEINSTANCEPROC(CLSID_DATATRAFFIC_GATEWAYSHAREMEM);
			GAIA_MAPPING_CREATEINSTANCEPROC(CLSID_DATATRAFFIC_GATEWAYFILE);
			GAIA_MAPPING_CREATEINSTANCEPROC(CLSID_DATATRAFFIC_ROUTEMEM);
			GAIA_MAPPING_CREATEINSTANCEPROC(CLSID_DATATRAFFIC_ROUTENET);
			GAIA_MAPPING_CREATEINSTANCEPROC(CLSID_DATATRAFFIC_TRANSMISSIONIDM);

			GAIA_MAPPING_CREATEINSTANCEPROC(CLSID_IO_FILEIO);
			GAIA_MAPPING_CREATEINSTANCEPROC(CLSID_IO_MEMIO);
			GAIA_MAPPING_CREATEINSTANCEPROC(CLSID_IO_SCREENIO);

			GAIA_MAPPING_CREATEINSTANCEPROC(CLSID_SERIALIZER);

			GAIA_MAPPING_CREATEINSTANCEPROC(CLSID_UI_CANVAS);
			GAIA_MAPPING_CREATEINSTANCEPROC(CLSID_UI_PAINTER);
			GAIA_MAPPING_CREATEINSTANCEPROC(CLSID_UI_FORM);
			GAIA_MAPPING_CREATEINSTANCEPROC(CLSID_UI_PUSHBUTTON);
			GAIA_MAPPING_CREATEINSTANCEPROC(CLSID_UI_RADIOBUTTON);
			GAIA_MAPPING_CREATEINSTANCEPROC(CLSID_UI_CHECKBUTTON);
			GAIA_MAPPING_CREATEINSTANCEPROC(CLSID_UI_LABEL);
			GAIA_MAPPING_CREATEINSTANCEPROC(CLSID_UI_EDIT);
			GAIA_MAPPING_CREATEINSTANCEPROC(CLSID_UI_DOCUMENT);
			GAIA_MAPPING_CREATEINSTANCEPROC(CLSID_UI_PROGRESSBAR);

			GAIA_MAPPING_CREATEINSTANCEPROC(CLSID_STATE_STATE);
			GAIA_MAPPING_CREATEINSTANCEPROC(CLSID_STATE_STATECTN);
			GAIA_MAPPING_CREATEINSTANCEPROC(CLSID_STATE_STATEMGR);

			GAIA_MAPPING_CREATEINSTANCEPROC(CLSID_TIMER_TIMER);
			GAIA_MAPPING_CREATEINSTANCEPROC(CLSID_TIMER_TIMERMGR);
		}
	};
};

#endif