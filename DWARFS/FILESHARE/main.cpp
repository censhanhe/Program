#include 	<iostream>
#include	<string>
using namespace std;

#include	"fsha.h"
#include	"../../GAIA/gaia_global_impl.h"

int main()
{
#if GAIA_OS == GAIA_OS_WINDOWS
	WSAData wsadata;
	WSAStartup(MAKEWORD(2, 2), &wsadata);
#endif

	cout << "Welcome FileShare(v" << DWARFS_FSHA::VERSION_STRING << ")" << endl << endl;
	DWARFS_FSHA::FileShare fsha;
	DWARFS_FSHA::FileShare::FileShareDesc desc;

	GAIA::UM uProcessID = GAIA::PROCESS::processid();
	cout << "Current Process ID = " << uProcessID << endl << endl;

#ifdef FSHA_DEBUG
	cout << "Warning! FSHA_DEBUG macro is openned!" << endl << endl;
#endif

	cout << "Local machine ip list:" << endl;
	GAIA::CONTAINER::Vector<GAIA::NETWORK::IP> listIP;
	GAIA::GCH szHostName[260];
	GAIA::NETWORK::GetHostName(szHostName, 260);
	GAIA::NETWORK::GetHostIPList(szHostName, listIP);
	for(GAIA::N32 x = 0; x < listIP.size(); ++x)
	{
		GAIA::GCH szIP[128];
		listIP[x].ToString(szIP);
		cout << x << ") " << szIP << endl;
	}
	cout << "Default Port is " << DWARFS_FSHA::MAINRECVPORT << endl;
	cout << endl;

	GAIA::GCH szIP[128];
INPUT_IP:
	cout << "Input the ip address or select one of local ip:";
	cin >> szIP;
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
		cout << ":";
		string str_cmd;
		for(;;) // Collect all word to command lines.
		{
			string str;
			cin >> str;
			if(str.length() == 0)
				continue;
			if(!str_cmd.empty())
				str_cmd += " ";
			str_cmd += str;
			GAIA::BL bExistCmd = GAIA::False;
			for(;;) // If exist valid command line, execute it.
			{
				GAIA::N32 nIndex = (GAIA::N32)str_cmd.find(';');
				if(nIndex == -1)
					break;
				string str_cmd_cur = str_cmd.substr(0, nIndex);
				str_cmd.erase(0, nIndex + 1);
				if(str_cmd_cur == "q")
					goto FUNCTION_END;
				else
				{
					if(!fsha.Command(str_cmd_cur.c_str()))
						cout << endl << "Invalid command!" << endl;
					bExistCmd = GAIA::True;
				}
			}
			if(bExistCmd)
				cout << ":";
		}
	}
FUNCTION_END:
	fsha.Shutdown();
	fsha.Release();
#if GAIA_OS == GAIA_OS_WINDOWS
	WSACleanup();
#endif
	return 0;
}
