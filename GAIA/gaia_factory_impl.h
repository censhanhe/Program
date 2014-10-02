#ifndef		__GAIA_FACTORY_IMPL_H__
#define		__GAIA_FACTORY_IMPL_H__

namespace GAIA
{
	namespace FWORK
	{
		GINL Instance* GAIA::FWORK::Factory::CreateInstance(const ClsID& cid, GAIA::GVOID* pParameter)
		{
			if(cid.IsInvalid())
				return GNIL;
			Instance* pRet = GNIL;
			if(GAIA::ALWAYSFALSE){}

			/* Data traffic. */
			else if(cid == GAIA::FWORK::CLSID_DATATRAFFIC_GATEWAYMEM)
				pRet = new GAIA::DATATRAFFIC::GatewayMem;
			else if(cid == GAIA::FWORK::CLSID_DATATRAFFIC_GATEWAYSHAREMEM)
				pRet = new GAIA::DATATRAFFIC::GatewayShareMem;
			else if(cid == GAIA::FWORK::CLSID_DATATRAFFIC_GATEWAYFILE)
				pRet = new GAIA::DATATRAFFIC::GatewayFile;
			else if(cid == GAIA::FWORK::CLSID_DATATRAFFIC_ROUTEMEM)
				pRet = new GAIA::DATATRAFFIC::RouteMem;
			else if(cid == GAIA::FWORK::CLSID_DATATRAFFIC_ROUTENET)
				pRet = new GAIA::DATATRAFFIC::RouteNet;
			else if(cid == GAIA::FWORK::CLSID_DATATRAFFIC_TRANSMISSIONIDM)
				pRet = new GAIA::DATATRAFFIC::TransmissionIDM;

			/* IO. */
			else if(cid == GAIA::FWORK::CLSID_IO_FILEIO)
				pRet = new GAIA::IO::FileIO;
			else if(cid == GAIA::FWORK::CLSID_IO_MEMIO)
				pRet = new GAIA::IO::MemIO;
			else if(cid == GAIA::FWORK::CLSID_IO_SCREENIO)
				pRet = new GAIA::IO::ScreenIO;

			/* Serializer. */
			else if(cid == GAIA::FWORK::CLSID_SERIALIZER)
				pRet = new GAIA::SERIALIZER::Serializer;

			/* UI. */
			else if(cid == GAIA::FWORK::CLSID_UI_CANVAS)
				pRet = new GAIA::UI::Canvas;

			/* Render. */
			else if(cid == GAIA::FWORK::CLSID_RENDER_2D_DDRAW)
				pRet = new GAIA::RENDER::Render2DDDraw;
			else if(cid == GAIA::FWORK::CLSID_RENDER_2D_GDIPLUS)
				pRet = new GAIA::RENDER::Render2DGDIPlus;
			else if(cid == GAIA::FWORK::CLSID_RENDER_3D_DX9)
				pRet = new GAIA::RENDER::Render3DDX9;
			else if(cid == GAIA::FWORK::CLSID_RENDER_3D_DX10)
				pRet = new GAIA::RENDER::Render3DDX10;
			else if(cid == GAIA::FWORK::CLSID_RENDER_3D_DX11)
				pRet = new GAIA::RENDER::Render3DDX11;
			else if(cid == GAIA::FWORK::CLSID_RENDER_3D_GL1)
				pRet = new GAIA::RENDER::Render3DGL1;
			else if(cid == GAIA::FWORK::CLSID_RENDER_3D_GL2)
				pRet = new GAIA::RENDER::Render3DGL2;
			else if(cid == GAIA::FWORK::CLSID_RENDER_3D_GL3)
				pRet = new GAIA::RENDER::Render3DGL3;
			else if(cid == GAIA::FWORK::CLSID_RENDER_3D_GLES1)
				pRet = new GAIA::RENDER::Render3DGLES1;
			else if(cid == GAIA::FWORK::CLSID_RENDER_3D_GLES2)
				pRet = new GAIA::RENDER::Render3DGLES2;
			else if(cid == GAIA::FWORK::CLSID_RENDER_3D_GLES3)
				pRet = new GAIA::RENDER::Render3DGLES3;

			if(pRet == GNIL)
			{
				for(LIST_CREATECALLBACK::_sizetype x = 0; x < m_listCreateCB.size(); ++x)
				{
					FactoryCreateCallBack* pCallBack = m_listCreateCB[x];
					pRet = pCallBack->Create(this, cid);
					if(pRet != GNIL)
						break;
				}
			}

			if(pRet != GNIL)
			{
				pRet->SetFactory(this);
				if(!pRet->Begin(pParameter))
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
	};
};

#endif