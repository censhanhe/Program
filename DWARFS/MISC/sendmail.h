#ifndef		__DWARFS_SEND_MAIL_H__
#define		__DWARFS_SEND_MAIL_H__

namespace DWARFS_MISC
{
	class SendMail
	{
	private:
		class SendMailNReceiver : public GAIA::NETWORK::NetworkReceiver
		{
		public:
			GINL SendMailNReceiver(SendMail* pSendMail){m_pSendMail = pSendMail;}
			virtual GAIA::BL Receive(GAIA::NETWORK::NetworkHandle& s, const GAIA::U8* p, GAIA::U32 size)
			{
				GPCHR_NULL_RET(m_pSendMail, GAIA::False);
				return m_pSendMail->OnReceive(s, p, size);
			}
		private:
			SendMail* m_pSendMail;
		};
	public:
		typedef GAIA::CH __CharType;
		typedef GAIA::CTN::BasicChars<__CharType, GAIA::N32, 1024> __CharsType;
		typedef GAIA::CTN::BasicString<__CharType, GAIA::N32> __StringType;
		typedef GAIA::TCH __FileNameCharType;
		typedef GAIA::CTN::TString __FileNameStringType;

	public:
		GINL GAIA::GVOID username(const __CharType* pszUserName){m_username = pszUserName;}
		GINL const __CharType* username() const{return m_username;}
		GINL GAIA::GVOID password(const __CharType* pszPassword){m_password = pszPassword;}
		GINL const __CharType* password() const{return m_password;}
		GINL GAIA::GVOID smtp_address(const __CharType* pszSMTPAddress){m_smtp_address = pszSMTPAddress;}
		GINL const __CharType* smtp_address() const{return m_smtp_address;}
		GINL GAIA::GVOID smtp_port(GAIA::U16 uPort){m_smtp_port = uPort;}
		GINL GAIA::U16 smtp_port() const{return m_smtp_port;}
		GINL GAIA::GVOID sender_mail_address(const __CharType* pszMailAddress){m_sender_mail_address = pszMailAddress;}
		GINL const __CharType* send_mail_address() const{return m_sender_mail_address;}
		GINL GAIA::GVOID receiver_mail_address(const __CharType* pszMailAddress){m_receiver_mail_address = pszMailAddress;}
		GINL const __CharType* receiver_mail_address() const{return m_receiver_mail_address;}
		GINL GAIA::GVOID sender_name(const __CharType* pszSenderName){m_sender_name = pszSenderName;}
		GINL const __CharType* sender_name() const{return m_sender_name;}
		GINL GAIA::GVOID title(const __CharType* pszTitle){m_title = pszTitle;}
		GINL const __CharType* title() const{return m_title;}
		GINL GAIA::GVOID content(const __CharType* pszContent){m_content = pszContent;}
		GINL const __CharType* content() const{return m_content;}
		GINL GAIA::BL add_attach(const __FileNameCharType* pszFileName)
		{
			GPCHR_NULLSTRPTR_RET(pszFileName, GAIA::False);
			if(this->get_attach_by_name(pszFileName) != GINVALID)
				return GAIA::False;
			GAIA::SIZE uValidIndex = GINVALID;
			for(GAIA::SIZE x = 0; x < m_attachs.size(); ++x)
			{
				if(m_attachs[x].empty())
				{
					uValidIndex = x;
					break;
				}
			}
			if(uValidIndex == GINVALID)
				m_attachs.push_back(pszFileName);
			else
				m_attachs[uValidIndex] = pszFileName;
			return GAIA::True;
		}
		GINL GAIA::BL delete_attach(const __FileNameCharType* pszFileName)
		{
			GPCHR_NULLSTRPTR_RET(pszFileName, GAIA::False);
			GAIA::SIZE uIndex = this->get_attach_by_name(pszFileName);
			if(uIndex == GINVALID)
				return GAIA::False;
			m_attachs[uIndex].clear();
			return GAIA::True;
		}
		GINL GAIA::GVOID delete_attach_all(){m_attachs.clear();}
		GINL GAIA::SIZE get_attach_count() const{return m_attachs.size();}
		GINL const __FileNameCharType* get_attach(const GAIA::SIZE& index) const
		{
			if(index >= m_attachs.size())
				return GNIL;
			return m_attachs[index];
		}
		GINL GAIA::SIZE get_attach_by_name(const __FileNameCharType* pszFileName)
		{
			GPCHR_NULLSTRPTR_RET(pszFileName, GAIA::False);
			for(GAIA::SIZE x = 0; x < m_attachs.size(); ++x)
			{
				if(m_attachs[x] == pszFileName)
					return x;
			}
			return GINVALID;
		}
		GINL GAIA::BL send(GAIA::NETWORK::NetworkSender* pNetworkSender, GAIA::NETWORK::NetworkReceiver* pNetworkReceiver)
		{
			/* Parameter checkup. */
			if(m_username.empty())
				return GAIA::False;
			if(m_password.empty())
				return GAIA::False;
			if(m_smtp_address.empty())
				return GAIA::False;
			if(m_sender_mail_address.empty())
				return GAIA::False;
			if(m_receiver_mail_address.empty())
				return GAIA::False;
			if(m_sender_name.empty())
				return GAIA::False;
			if(m_title.empty())
				return GAIA::False;
			if(m_content.empty())
				return GAIA::False;

			/* Connect. */
			GAIA::NETWORK::NetworkHandle h;
			GAIA::NETWORK::NetworkHandle::ConnectDesc cnndesc;
			GAIA::CTN::Vector<GAIA::NETWORK::IP> listIPResult;
			GAIA::NETWORK::GetHostIPList(m_smtp_address, listIPResult);
			if(listIPResult.size() == 0)
				return GAIA::False;
			cnndesc.addr.ip = listIPResult[0];
			cnndesc.addr.uPort = m_smtp_port;
			cnndesc.bStabilityLink = GAIA::True;
			if(!h.Connect(cnndesc))
				return GAIA::False;

			GAIA::NETWORK::NetworkSender sender;
			GAIA::BL bSenderChange = GAIA::False;
			if(pNetworkSender == GNIL)
			{
				pNetworkSender = &sender;
				bSenderChange = GAIA::True;
			}
			SendMailNReceiver receiver(this);
			GAIA::BL bRecverChange = GAIA::False;
			if(pNetworkReceiver == GNIL)
			{
				pNetworkReceiver = &receiver;
				bRecverChange = GAIA::True;
			}

			h.SetSender(pNetworkSender);
			h.SetReceiver(pNetworkReceiver);

			if(bSenderChange)
				pNetworkSender->Begin();
			if(bRecverChange)
				pNetworkReceiver->Begin();

			/* Login. */
			GAIA::CH szTemp[1024];
			GAIA::SIZE uNewSize;
			__StringType strRecv;
			if(!this->PopRecv(strRecv, GAIA::U32MAXSIZE))
				goto FUNCTION_END;

			h.Send((const GAIA::U8*)"HELO EHLO\r\n", sizeof("HELO EHLO\r\n") - 1);
			if(!this->PopRecv(strRecv, GAIA::U32MAXSIZE))
				goto FUNCTION_END;

			h.Send((const GAIA::U8*)"AUTH LOGIN\r\n", sizeof("AUTH LOGIN\r\n") - 1);
			if(!this->PopRecv(strRecv, GAIA::U32MAXSIZE))
				goto FUNCTION_END;

			uNewSize = GAIA::DATAPHASE::Char2Base64(szTemp, 1024, m_username.front_ptr(), m_username.size());
			szTemp[uNewSize++] = '\r';
			szTemp[uNewSize++] = '\n';
			szTemp[uNewSize] = '\0';
			h.Send((const GAIA::U8*)szTemp, uNewSize);
			if(!this->PopRecv(strRecv, GAIA::U32MAXSIZE))
				goto FUNCTION_END;

			uNewSize = GAIA::DATAPHASE::Char2Base64(szTemp, 1024, m_password.front_ptr(), m_password.size());
			szTemp[uNewSize++] = '\r';
			szTemp[uNewSize++] = '\n';
			szTemp[uNewSize] = '\0';
			h.Send((const GAIA::U8*)szTemp, uNewSize);
			if(!this->PopRecv(strRecv, GAIA::U32MAXSIZE))
				goto FUNCTION_END;

			/* Send mail. */
			{
				__CharsType from = "MAIL FROM:<";
				from += m_sender_mail_address;
				from += ">\r\n";
				h.Send((const GAIA::U8*)from.front_ptr(), from.size());
				if(!this->PopRecv(strRecv, GAIA::U32MAXSIZE))
					goto FUNCTION_END;
			}

			{
				__CharsType to = "RCPT TO:<";
				to += m_receiver_mail_address;
				to += ">\r\n";
				h.Send((const GAIA::U8*)to.front_ptr(), to.size());
				if(!this->PopRecv(strRecv, GAIA::U32MAXSIZE))
					goto FUNCTION_END;
			}

			h.Send((const GAIA::U8*)"DATA\r\n", sizeof("DATA\r\n") - 1);
			if(!this->PopRecv(strRecv, GAIA::U32MAXSIZE))
				goto FUNCTION_END;

			{
				__CharsType sender = "From:\"";
				sender += m_sender_name;
				sender += "\"<";
				sender += m_sender_mail_address;
				sender += ">\r\n";
				h.Send((const GAIA::U8*)sender.front_ptr(), sender.size());
			}

			{
				__CharsType receiver = "To:\"";
				receiver += m_receiver_mail_address;
				receiver += "\"<";
				receiver += m_receiver_mail_address;
				receiver += ">\r\n";
				h.Send((const GAIA::U8*)receiver.front_ptr(), receiver.size());
			}

			{
				__CharsType title = "Subject:";
				title += m_title;
				title += "\r\nMime-Version: 1.0\r\nContent-Type: multipart/mixed; boundary=\"INVT\"\r\n\r\n";
				h.Send((const GAIA::U8*)title.front_ptr(), title.size());
			}

			{
				__StringType content = "--INVT\r\nContent-Type: text/plain;\r\n charset=\"utf8\"\r\n\r\n";
				content += m_content;
				content += "\r\n\r\n";
				h.Send((const GAIA::U8*)content.front_ptr(), content.size());
			}

			/* Send attachments. */
			for(GAIA::SIZE x = 0; x < m_attachs.size(); ++x)
			{
				const __FileNameStringType& strFile = m_attachs[x];
				GAIA::FILESYSTEM::File file;
				if(!file.Open(strFile, GAIA::FILESYSTEM::File::OPEN_TYPE_READ))
					continue;
				GAIA::N64 nSize = file.Size();
				if(nSize == 0 || nSize == GINVALID)
					continue;

				const __FileNameStringType::_datatype* pFileName = GAIA::ALGO::strfilename(strFile.front_ptr());
				if(pFileName == GNIL)
					continue;
			#if GAIA_CHARSET == GAIA_CHARSET_ANSI
				__CharsType attach = "--INVT\r\nContent-Type: application/octet-stream;\r\n name=\"";
				attach += pFileName;
				attach += "\"\r\nContent-Transfer-Encoding: base64\r\nContent-Disposition: attachment;\r\n filename=\"";
				attach += pFileName;
				attach += "\"\r\n\r\n";
			#elif GAIA_CHARSET == GAIA_CHARSET_UNICODE
				__CharType szFileName[GAIA::FILESYSTEM::MAXPL];
				GAIA::LOCALE::w2m(pFileName, szFileName, GAIA::FILESYSTEM::MAXPL, GAIA::CHARSET_TYPE_UTF8);
				__CharsType attach = "--INVT\r\nContent-Type: application/octet-stream;\r\n name=\"";
				attach += szFileName;
				attach += "\"\r\nContent-Transfer-Encoding: base64\r\nContent-Disposition: attachment;\r\n filename=\"";
				attach += szFileName;
				attach += "\"\r\n\r\n";
			#endif
				h.Send((const GAIA::U8*)attach.front_ptr(), attach.size());

				static const GAIA::N64 PATCH_SIZE = 1024 * 128;
				GAIA::CTN::Vector<GAIA::U8> buf;
				GAIA::CTN::Vector<GAIA::U8> buf64;
				buf.resize(PATCH_SIZE + 2);
				buf64.resize(buf.size() * 2 + 4);
				GAIA::N64 nReaded = 0;
				while((nReaded = file.Read(buf.front_ptr(), PATCH_SIZE)) > 0)
				{
					GAIA::SIZE nBuf64Size = GAIA::DATAPHASE::Char2Base64(
						(GAIA::CH*)buf64.front_ptr(),
						buf64.size(),
						(const GAIA::CH*)buf.front_ptr(),
						buf.size());
					buf64[nBuf64Size++] = '\r';
					buf64[nBuf64Size++] = '\n';
					h.Send(buf64.front_ptr(), nBuf64Size);
				}
			}

			/* Send end. */
			h.Send((const GAIA::U8*)"--INVT--\r\n.\r\n", sizeof("--INVT--\r\n.\r\n") - 1);
			if(!this->PopRecv(strRecv, GAIA::U32MAXSIZE))
				goto FUNCTION_END;

			h.Send((const GAIA::U8*)"QUIT\r\n", sizeof("QUIT\r\n") - 1);
			if(!this->PopRecv(strRecv, GAIA::U32MAXSIZE))
				goto FUNCTION_END;

			/* Disconnect. */
		FUNCTION_END:
			h.SetSender(GNIL);
			h.SetReceiver(GNIL);

			if(bSenderChange)
				pNetworkSender->End();
			if(bRecverChange)
				pNetworkReceiver->End();

			h.Disconnect();

			return GAIA::True;
		}

		GINL GAIA::BL OnReceive(GAIA::NETWORK::NetworkHandle& s, const GAIA::U8* p, GAIA::U32 size)
		{
			if(size > 0)
			{
				GAIA_AST(p != GNIL);
				m_combinbuf.write(p, size);
				for(GAIA::SIZE x = 1; x < m_combinbuf.write_size(); ++x)
				{
					if(m_combinbuf[x - 1] == '\r' &&
						m_combinbuf[x] == '\n')
					{
						GAIA::SYNC::AutoLock al(m_lock);
						m_recv.assign((__CharType*)m_combinbuf.front_ptr(), x + 1);
						m_tempbuf = m_combinbuf;
						m_combinbuf.clear();
						if(m_tempbuf.write_size() - x - 1 > 0)
							m_combinbuf.write(m_tempbuf.front_ptr() + x + 1, m_tempbuf.write_size() - x - 1);
						m_event.Fire();
					}
				}
			}
			return GAIA::True;
		}
		GINL GAIA::BL PopRecv(__StringType& strRecv, GAIA::U32 uMilliSecond)
		{
			if(!m_event.Wait(uMilliSecond))
				return GAIA::False;
			GAIA::SYNC::AutoLock al(m_lock);
			strRecv = m_recv;
			m_recv.clear();
			return GAIA::True;
		}
	private:
		__StringType m_username;
		__StringType m_password;
		__StringType m_smtp_address;
		GAIA::U16 m_smtp_port;
		__StringType m_sender_mail_address;
		__StringType m_receiver_mail_address;
		__StringType m_sender_name;
		__StringType m_title;
		__StringType m_content;
		GAIA::CTN::Vector<__FileNameStringType> m_attachs;
		GAIA::CTN::Buffer m_combinbuf;
		GAIA::CTN::Buffer m_tempbuf;
		GAIA::SYNC::Lock m_lock;
		GAIA::SYNC::Event m_event;
		__StringType m_recv;
	};
};

#endif
