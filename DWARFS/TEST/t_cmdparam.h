#ifndef		__T_CMDPARAM_H__
#define		__T_CMDPARAM_H__

namespace DWARFSTEST
{
	GINL GAIA::N32 t_cmdparam(GAIA::FILESYSTEM::File& file, GAIA::PRINT::Print& prt)
	{
		GAIA::N32 nRet = 0;

		DWARFS_MISC::CmdParam cp;
		if(cp.is_begin_decl())
		{
			GTLINE2("New CmdParam 's decl is not empty!");
			++nRet;
		}
		cp.clear_decl();
		cp.clear_cmd();
		cp.begin_decl();
		{
			if(!cp.is_begin_decl())
			{
				GTLINE2("CmdParam begined decl bug is_begin_decl return GAIA::False!");
				++nRet;
			}
			/*
			*	TEST CASE:
			*		-D[1,] -d[1,] -r -m -o[1,] -omax[1,] -s[1,1]
			*		MUTEX GROUP:-D -d
			*		MUTEX GROUP:-o -s
			*		COOP GROUP:-o -omax
			*/
			if(cp.cmd_decl("-D", "Force delete files.", 1, GINVALID, DWARFS_MISC::CmdParam::CMD_TYPE_INVALID) == GINVALID)
			{
				GTLINE2("CmdParam cmd_decl failed!");
				++nRet;
			}
			if(!cp.cmd_param_decl("-D", 1, GINVALID, 0, GINVALID, "FileName", DWARFS_MISC::CmdParam::PARAM_TYPE_MUSTEXISTFILE))
			{
				GTLINE2("CmdParam cmd_param_decl failed!");
				++nRet;
			}
			if(cp.cmd_decl("-d", "Delete files.", 1, GINVALID, DWARFS_MISC::CmdParam::CMD_TYPE_INVALID) == GINVALID)
			{
				GTLINE2("CmdParam cmd_decl failed!");
				++nRet;
			}
			if(!cp.cmd_param_decl("-d", 1, GINVALID, 0, GINVALID, "FileName", DWARFS_MISC::CmdParam::PARAM_TYPE_MUSTEXISTFILE))
			{
				GTLINE2("CmdParam cmd_param_decl failed!");
				++nRet;
			}
			if(cp.cmd_decl("-r", "Recursive search files.", 0, 0, DWARFS_MISC::CmdParam::CMD_TYPE_INVALID) == GINVALID)
			{
				GTLINE2("CmdParam cmd_decl failed!");
				++nRet;
			}
			if(cp.cmd_decl("-m", "Show message.", 0, 0, DWARFS_MISC::CmdParam::CMD_TYPE_INVALID) == GINVALID)
			{
				GTLINE2("CmdParam cmd_decl failed!");
				++nRet;
			}
			if(cp.cmd_decl("-o", "Set output file.", 1, 1, DWARFS_MISC::CmdParam::CMD_TYPE_INVALID) == GINVALID)
			{
				GTLINE2("CmdParam cmd_decl failed!");
				++nRet;
			}
			if(!cp.cmd_param_decl("-o", 0, 0, 0, GINVALID, "FileName", DWARFS_MISC::CmdParam::PARAM_TYPE_MUSTEXISTFILE))
			{
				GTLINE2("CmdParam cmd_param_decl failed!");
				++nRet;
			}
			if(cp.cmd_decl("-omax", "Set output file's max size.", 1, 1, DWARFS_MISC::CmdParam::CMD_TYPE_INVALID) == GINVALID)
			{
				GTLINE2("CmdParam cmd_decl failed!");
				++nRet;
			}
			if(!cp.cmd_param_decl("-omax", 1, 1, 0, 0, "Max output file size.", DWARFS_MISC::CmdParam::PARAM_TYPE_INT))
			{
				GTLINE2("CmdParam cmd_param_decl failed!");
				++nRet;
			}
			if(cp.cmd_decl("-s", "Set output stream", 1, 1, DWARFS_MISC::CmdParam::CMD_TYPE_INVALID) == GINVALID)
			{
				GTLINE2("CmdParam cmd_decl failed!");
				++nRet;
			}
			if(!cp.cmd_param_decl("-s", 1, 1, 0, GINVALID, "StreamName", DWARFS_MISC::CmdParam::PARAM_TYPE_STRING))
			{
				GTLINE2("CmdParam cmd_param_decl failed!");
				++nRet;
			}
			cp.cmd_mutex_decl("-d", "-D");
			cp.cmd_mutex_decl("-o", "-s");
			cp.cmd_coop_decl("-o", "-omax");
			cp.cmd_coop_decl("-o", "-omax");
		}
		cp.end_decl();

		if(cp.finddecl("-D", 1) == GINVALID)
		{
			GTLINE2("CmdParam finddecl failed!");
			++nRet;
		}
		if(cp.finddecl("-d", 1) == GINVALID)
		{
			GTLINE2("CmdParam finddecl failed!");
			++nRet;
		}
		if(cp.finddecl("-r", 0) == GINVALID)
		{
			GTLINE2("CmdParam finddecl failed!");
			++nRet;
		}
		if(!cp.build("-D text.txt -r -m -o output.txt -omax 123"))
		{
			GTLINE2("CmdParam build failed!");
			++nRet;
		}
		for(GAIA::SIZE x = 0; x < cp.cmd_size(); ++x)
		{
			const GAIA::GCH* pszCmd = cp.cmd(x);
			GAIA_AST(!GAIA::ALGORITHM::stremp(pszCmd));
			prt << pszCmd << " ";
			for(GAIA::SIZE y = 0; y < cp.param_size(x); ++y)
			{
				const GAIA::GCH* pszParam = cp.param(x, y);
				GAIA_AST(!GAIA::ALGORITHM::stremp(pszParam));
				prt << pszParam << " ";
			}
			prt << "\n";
		}
		cp.clear_cmd();
		cp.clear_decl();

		return nRet;
	}
};

#endif