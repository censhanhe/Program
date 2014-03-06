#include 	<iostream>
#include	<string>
#include	"fsha.h"
using namespace std;

int main()
{
	cout << "Welcome FileShare(v" << FSHA::VERSION_STRING << ")" << endl;
	FSHA::FileShare fsha;
	FSHA::FileShare::FileShareDesc desc;
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
	return 0;
}
