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
		virtual GAIA::BL Receive(GAIA::NETWORK::Handle& h, const GAIA::U8* p, GAIA::U32 size)
		{
			const GAIA::NETWORK::Addr& na = h.GetRemoteAddress();
			GAIA::NETWORK::Addr curna;
			curna.ip.FromString("127.0.0.1");
			curna.uPort = 0;
			if(curna.ip != na.ip)
				return GAIA::False;
			if(size <= 0)
				return GAIA::False;
			m_recv.push_back(p, size);
			return GAIA::True;
		}
	public:
		GINL GAIA::SIZE GetReceiveCount() const
		{
			GAIA::SIZE sLen = GAIA::ALGO::strlen("HelloWorld");
			if(m_recv.size() % sLen != 0)
				return m_recv.size() / sLen;
			GAIA::SIZE ret = 0;
			for(GAIA::SIZE x = 0; x < m_recv.size(); x += sLen)
			{
				if(GAIA::ALGO::strcmpl(m_recv.front_ptr() + x, "HelloWorld", sLen) != 0)
					return ret;
				++ret;
			}
			return ret;
		}
	private:
		GINL GAIA::GVOID init()
		{
		}
	private:
		GAIA::CTN::Vector<GAIA::U8> m_recv;
	};

	class NHandle : public GAIA::NETWORK::Handle
	{
	public:
		GINL NHandle(){this->init();}
		GINL virtual GAIA::GVOID LostConnection(const GAIA::NETWORK::Addr& na, GAIA::BL bRecvTrueSendFalse)
		{
			m_bIsLostConnection = GAIA::True;
		}
		GINL GAIA::BL IsLostConnection() const{return m_bIsLostConnection;}
	private:
		GINL GAIA::GVOID init()
		{
			m_bIsLostConnection = GAIA::False;
		}
	private:
		GAIA::BL m_bIsLostConnection;
	};

	class NListener : public GAIA::NETWORK::Listener
	{
	public:
		GINL NListener(NSender* pSender, NReceiver* pReceiver)
		{
			GAIA_AST(pSender != GNIL);
			GAIA_AST(pReceiver != GNIL);
			this->init();
			m_pSender = pSender;
			m_pReceiver = pReceiver;
		}
		virtual GAIA::BL Accept(GAIA::NETWORK::Handle& h)
		{
			const GAIA::NETWORK::Addr& na = h.GetRemoteAddress();
			GAIA::NETWORK::Addr curna;
			curna.ip.FromString("127.0.0.1");
			curna.uPort = 0;
			if(curna.ip != na.ip)
				return GAIA::False;
			++m_sConnectCount;
			h.SetSender(m_pSender);
			h.SetReceiver(m_pReceiver);
			return GAIA::True;
		}
	public:
		GINL GAIA::SIZE GetConnectCount() const{return m_sConnectCount;}
	private:
		GINL GAIA::GVOID init()
		{
			m_sConnectCount = 0;
			m_pSender = GNIL;
			m_pReceiver = GNIL;
		}
	private:
		GAIA::SIZE m_sConnectCount;
		NSender* m_pSender;
		NReceiver* m_pReceiver;
	};

	GINL GAIA::N32 t_network(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;

		static const GAIA::TCH* IPADDRESS_STRING = _T("127.0.0.1:8488");

		NSender* pSender = new NSender;
		NReceiver* pReceiver = new NReceiver;
		NListener* pListener = new NListener(pSender, pReceiver);
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

		GAIA::SYNC::xsleep(100);

		/* Stability link test. */
		{
			pHandle->SetSender(pSender);
			pHandle->SetReceiver(pReceiver);

			NHandle::ConnectDesc descConn;
			descConn.reset();
			descConn.addr.FromString(IPADDRESS_STRING);
			descConn.bStabilityLink = GAIA::True;
			if(!pHandle->Connect(descConn))
			{
				GTLINE2("Network sender connect failed!");
				++nRet;
			}

			for(GAIA::SIZE x = 0; x < 1000; ++x)
			{
				if(!pHandle->Send(GRCAST(const GAIA::U8*)("HelloWorld"), GAIA::ALGO::strlen("HelloWorld")))
				{
					GTLINE2("Network handle send failed!");
					++nRet;
					break;
				}
			}

			GAIA::SYNC::xsleep(2000);
			if(pListener->GetConnectCount() != 1)
			{
				GTLINE2("Network sender connect failed!");
				++nRet;
			}
			if(pReceiver->GetReceiveCount() != 1000)
			{
				GTLINE2("Network receive failed!");
				++nRet;
			}
			if(pHandle->IsLostConnection())
			{
				GTLINE2("Network lost connection!");
				++nRet;
			}
		}

		/* No-Stability link test. */
		{
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