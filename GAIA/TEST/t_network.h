#ifndef		__T_NETWORK_H__
#define		__T_NETWORK_H__

namespace GAIA_TEST
{
	class NSender : public GAIA::NETWORK::Sender
	{
	public:
		GINL NSender(){this->init();}
	private:
		GINL GAIA::GVOID init()
		{
		}
	private:
	};

	class NReceiver : public GAIA::NETWORK::Receiver
	{
	public:
		GINL NReceiver(){this->init();}
		virtual GAIA::BL Receive(GAIA::NETWORK::Handle& s, const GAIA::U8* p, GAIA::U32 size)
		{
			return GAIA::False;
		}
	public:
		GINL GAIA::SIZE GetReceiveCount() const{}
	private:
		GINL GAIA::GVOID init()
		{
			m_sRecvCount = 0;
		}
	private:
		GAIA::SIZE m_sRecvCount;
	};

	class NHandle : public GAIA::NETWORK::Handle
	{
	public:
		GINL virtual GAIA::GVOID LostConnection(const GAIA::NETWORK::Addr& na, GAIA::BL bRecvTrueSendFalse)
		{
		}
	};

	class NListener : public GAIA::NETWORK::Listener
	{
	public:
		GINL NListener(){this->init();}
		virtual GAIA::BL Accept(GAIA::NETWORK::Handle& h)
		{
			const GAIA::NETWORK::Addr& na = h.GetRemoteAddress();
			GAIA::NETWORK::Addr curna;
			curna.ip.FromString("127.0.0.1");
			curna.uPort = 0;
			if(curna.ip != na.ip)
				return GAIA::False;
			++m_sConnectCount;
			return GAIA::True;
		}
	public:
		GINL GAIA::SIZE GetConnectCount() const{return m_sConnectCount;}
	private:
		GINL GAIA::GVOID init()
		{
			m_sConnectCount = 0;
		}
	private:
		GAIA::SIZE m_sConnectCount;
	};

	GINL GAIA::N32 t_network(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;

		static const GAIA::TCH* IPADDRESS_STRING = _T("127.0.0.1:8488");

		NSender* pSender = new NSender;
		NReceiver* pReceiver = new NReceiver;
		NListener* pListener = new NListener;
		NHandle* pHandle = new NHandle;

		NListener::ListenDesc descListen;
		descListen.reset();
		descListen.addr.FromString(IPADDRESS_STRING);
		pListener->SetDesc(descListen);

		if(!pSender->Begin())
		{
			GTLINE2("Network sender begin failed!");
			++nRet;
		}
		if(!pReceiver->Begin())
		{
			GTLINE2("Network receiver begin failed!");
			++nRet;
		}
		if(!pListener->Begin())
		{
			GTLINE2("Network listener begin failed!");
			++nRet;
		}

		NHandle::ConnectDesc descConn;
		descConn.reset();
		descConn.addr.FromString(IPADDRESS_STRING);
		if(!pHandle->Connect(descConn))
		{
			GTLINE2("Network sender connect failed!");
			++nRet;
		}

		GAIA::SYNC::xsleep(100);
		if(pListener->GetConnectCount() != 1)
		{
			GTLINE2("Network sender connect failed!");
			++nRet;
		}

		if(!pSender->End())
		{
			GTLINE2("Network sender end failed!");
			++nRet;
		}
		if(!pReceiver->End())
		{
			GTLINE2("Network receiver end failed!");
			++nRet;
		}
		if(!pListener->End())
		{
			GTLINE2("Network listener end failed!");
			++nRet;
		}

		GAIA_DELETE_SAFE(pSender);
		GAIA_DELETE_SAFE(pReceiver);
		GAIA_DELETE_SAFE(pListener);
		GAIA_RELEASE_SAFE(pHandle);

		return nRet;
	}
};

#endif