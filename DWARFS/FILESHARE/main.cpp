#include 	<iostream>
#include	<string>
using namespace std;

#define		GAIA_PLATFORM_NETWORK
#include	"fsha.h"
#include	"../../GAIA/gaia_global_impl.h"

#if GAIA_CHARSET == GAIA_CHARSET_ANSI
#	define tcout cout
#	define tcin cin
#	define tstring string
#elif GAIA_CHARSET == GAIA_CHARSET_UNICODE
#	define tcout wcout
#	define tcin wcin
#	define tstring wstring
#endif

int main()
{
	tcout << _T("Welcome FileShare(v") << DWARFS_FSHA::VERSION_STRING << _T(")") << endl << endl;
	DWARFS_FSHA::FileShare fsha;
	DWARFS_FSHA::FileShare::FileShareDesc desc;

	GAIA::UM uProcessID = GAIA::PROCESS::processid();
	tcout << _T("Current Process ID = ") << uProcessID << endl << endl;

#ifdef FSHA_DEBUG
	tcout << _T("Warning! FSHA_DEBUG macro is openned!") << endl << endl;
#endif

	tcout << _T("Local machine ip list:") << endl;
	GAIA::CTN::Vector<GAIA::NETWORK::IP> listIP;
	GAIA::CH szHostName[260];
	GAIA::NETWORK::GetHostName(szHostName, 260);
	GAIA::NETWORK::GetHostIPList(szHostName, listIP);
	for(GAIA::N32 x = 0; x < listIP.size(); ++x)
	{
		GAIA::TCH szIP[128];
		listIP[x].ToString(szIP);
		tcout << x << _T(") ") << szIP << endl;
	}
	tcout << _T("Default Port is ") << DWARFS_FSHA::MAINRECVPORT << endl;
	tcout << endl;

	GAIA::TCH szIP[128];
INPUT_IP:
	tcout << _T("Input the ip address or select one of local ip:");
	tcin >> szIP;
	if(szIP[1] == 0)
	{
		GAIA::N32 index = szIP[0] - '0';
		if(index >= listIP.size())
			goto INPUT_IP;
		if(index < 0)
			goto INPUT_IP;
		desc.selfaddr.ip = listIP[index];
		desc.selfaddr.uPort = DWARFS_FSHA::MAINRECVPORT;
	}
	else
	{
		if(!desc.selfaddr.FromString(szIP))
			goto INPUT_IP;
	}

	fsha.Initialize(desc);
	fsha.Startup();
	for(;;) // Work loop.
	{
		tcout << _T(":");
		tstring str_cmd;
		for(;;) // Collect all word to command lines.
		{
			tstring str;
			tcin >> str;
			if(str.length() == 0)
				continue;
			if(!str_cmd.empty())
				str_cmd += _T(" ");
			str_cmd += str;
			GAIA::BL bExistCmd = GAIA::False;
			for(;;) // If exist valid command line, execute it.
			{
				GAIA::N32 nIndex = (GAIA::N32)str_cmd.find(';');
				if(nIndex == -1)
					break;
				tstring str_cmd_cur = str_cmd.substr(0, nIndex);
				str_cmd.erase(0, nIndex + 1);
				if(str_cmd_cur == _T("q"))
					goto FUNCTION_END;
				else
				{
					if(!fsha.Command(str_cmd_cur.c_str()))
						tcout << endl << _T("Invalid command!") << endl;
					bExistCmd = GAIA::True;
				}
			}
			if(bExistCmd)
				tcout << _T(":");
		}
	}
FUNCTION_END:
	fsha.Shutdown();
	fsha.Release();

	return 0;
}
