#ifndef		__T_SENDMAIL_H__
#define		__T_SENDMAIL_H__

namespace DWARFSTEST
{
	GINL GAIA::N32 t_sendmail(GAIA::FILESYSTEM::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;

	//#if GAIA_OS == GAIA_OS_WINDOWS
	//	WORD wVersionRequested;
	//	WSADATA wsaData;
	//	GAIA::N32 nError;
	//	wVersionRequested = MAKEWORD(2, 2);
	//	nError = WSAStartup(wVersionRequested, &wsaData);
	//#endif

	//	DWARFS_MISC::SendMail sm;
	//	sm.username("stormtotemworks@163.com");
	//	sm.password("qwerasdfzxcv");
	//	sm.smtp_address("smtp.163.com");
	//	sm.smtp_port(25);
	//	sm.sender_mail_address("stormtotemworks@163.com");
	//	sm.receiver_mail_address("xingyue@stormtotem.net");
	//	sm.sender_name("admin");
	//	sm.title("Mail Test Title");
	//	sm.content("Mail test content.\nMail test content.\n");
	//	sm.add_attach("d:\\xy\\test.jpg");
	//	sm.add_attach("d:\\xy\\test1.jpg");
	//	sm.send(GNULL, GNULL);

	//#if GAIA_OS == GAIA_OS_WINDOWS
	//	WSACleanup();
	//#endif

		return nRet;
	}
};

#endif
