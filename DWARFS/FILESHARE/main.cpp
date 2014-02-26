#include 	<iostream>
#include	<string>
#include	"fsha.h"
using namespace std;

int main()
{
	FSHA::FileShare fsha;
	FSHA::FileShare::FileShareDesc desc;
	fsha.Initialize(desc);
	cout << "Welcome FileShare" << endl;
	for(;;)
	{
		string str_cmd;
		for(;;)
		{
			string str;
			cin >> str;
			if(str.length() == 0)
				continue;
			if(!str_cmd.empty())
				str_cmd += " ";
			str_cmd += str;
			for(;;)
			{
				GAIA::N32 nIndex = str_cmd.find(';');
				if(nIndex == -1)
					break;
				string str_cmd_cur = str_cmd.substr(0, nIndex);
				str_cmd.erase(0, nIndex + 1);
				if(str_cmd_cur == "q")
					goto FUNCTION_END;
				else
				{
					if(!fsha.Command(str_cmd_cur.c_str()))
						cout << "Invalid command!" << endl;
				}
			}
		}
	}
FUNCTION_END:
	fsha.Release();
	return 0;
}
