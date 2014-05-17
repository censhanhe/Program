#ifndef 	__DWARFS_MISC_CMDPARAM_H__
#define 	__DWARFS_MISC_CMDPARAM_H__

namespace DWARFS_MISC
{
	class CmdParam
	{
	public:
		GINL CmdParam(){this->init();}
		GINL ~CmdParam(){}

	public: /* For format declaration. */
		GAIA_ENUM_BEGIN(CMD_TYPE)
			CMD_TYPE_MUSTEXIST,
		GAIA_ENUM_END(CMD_TYPE)

		GAIA_ENUM_BEGIN(PARAM_TYPE)
			PARAM_TYPE_FILE,
			PARAM_TYPE_MUSTEXISTFILE,
			PARAM_TYPE_MUSTNOTEXISTFILE,
			PARAM_TYPE_INT,
			PARAM_TYPE_ENUM,
		GAIA_ENUM_END(PARAM_TYPE)

		GINL GAIA::BL begin_decl()
		{
			if(this->is_begin_decl())
				return GAIA::False;
			m_bBeginDecl = GAIA::True;
			return GAIA::True;
		}
		GINL GAIA::BL end_decl()
		{
			if(!this->is_begin_decl())
				return GAIA::False;
			m_opt_decls.clear();
			for(__CmdDeclListType::_sizetype x = 0; x < m_decls.size(); ++x)
				m_opt_decls.push_back(&m_decls[x]);
			m_opt_decls.sort();
			m_opt_cmds.clear();
			for(__CmdListType::_sizetype x = 0; x < m_cmds.size(); ++x)
				m_opt_cmds.push_back(&m_cmds[x]);
			m_opt_cmds.sort();
			m_bBeginDecl = GAIA::False;
			return GAIA::True;
		}
		GINL GAIA::BL is_begin_decl() const{return m_bBeginDecl;}
		GINL GAIA::SIZE cmd_decl(
			const GAIA::GCH* pszCmd, 
			const GAIA::GCH* pszDesc,
			const GAIA::SIZE& min_param_size, 
			const GAIA::SIZE& max_param_size, 
			CMD_TYPE t)
		{
			GAIA_AST(!GAIA::ALGORITHM::stremp(pszCmd));
			if(GAIA::ALGORITHM::stremp(pszCmd))
				return GINVALID;
			GAIA_AST(!GAIA::ALGORITHM::stremp(pszDesc));
			if(GAIA::ALGORITHM::stremp(pszDesc))
				return GINVALID;
			GAIA_AST(min_param_size >= 0);
			if(min_param_size < 0)
				return GINVALID;
			GAIA_AST(max_param_size >= 0 || max_param_size == GINVALID);
			if(max_param_size < 0 && max_param_size != GINVALID)
				return GINVALID;
			GAIA_AST(min_param_size <= max_param_size || max_param_size == GINVALID);
			if(min_param_size > max_param_size && max_param_size != GINVALID)
				return GINVALID;
			CmdDecl temp;
			temp.index = GINVALID;
			temp.cmd = pszCmd;
			temp.desc = pszDesc;
			temp.type = t;
			temp.min_param_size = min_param_size;
			temp.max_param_size = max_param_size;
			for(__CmdDeclListType::_sizetype x = 0; x < m_decls.size(); ++x)
			{
				if(m_decls[x] == temp)
					return GINVALID;
			}
			m_decls.push_back(temp);
			return m_decls.size() - 1;
		}
		GINL GAIA::GVOID cmd_param_decl(
			const GAIA::GCH* pszCmd,
			const GAIA::SIZE& min_param_size,
			const GAIA::SIZE& max_param_size,
			const GAIA::SIZE& start_param_index,
			const GAIA::SIZE& end_param_index,
			const GAIA::GCH* pszDesc,
			PARAM_TYPE t)
		{
			GAIA_AST(!GAIA::ALGORITHM::stremp(pszCmd));
			if(GAIA::ALGORITHM::stremp(pszCmd))
				return;
			GAIA_AST(min_param_size >= 0);
			if(min_param_size < 0)
				return;
			GAIA_AST(max_param_size >= 0 || max_param_size == GINVALID);
			if(max_param_size < 0 && max_param_size != GINVALID)
				return;
			GAIA_AST(min_param_size <= max_param_size || max_param_size == GINVALID);
			if(min_param_size > max_param_size && max_param_size != GINVALID)
				return;
			GAIA_AST(start_param_index >= 0);
			if(start_param_index < 0)
				return;
			GAIA_AST(end_param_index >= 0 || end_param_index == GINVALID);
			if(end_param_index < 0 && end_param_index != GINVALID)
				return;
			GAIA_AST(start_param_index <= end_param_index || end_param_index == GINVALID);
			if(start_param_index > end_param_index && end_param_index != GINVALID)
				return;
			CmdDecl* pCmd = GNULL;
			for(__CmdDeclListType::_sizetype x = 0; x < m_decls.size(); ++x)
			{
				CmdDecl& temp = m_decls[x];
				if(temp.cmd == pszCmd &&
					temp.min_param_size == min_param_size && 
					temp.max_param_size == max_param_size)
				{
					pCmd = &temp;
					break;
				}	
			}
			if(pCmd == GNULL)
				return;
			ParamDecl temp;
			temp.start_param_index = start_param_index;
			temp.end_param_index = end_param_index;
			if(!GAIA::ALGORITHM::stremp(pszDesc))
				temp.desc = pszDesc;
			temp.type = t;
			for(__ParamDeclListType::_sizetype x = 0; x < pCmd->paramdecls.size(); ++x)	
			{
				if(pCmd->paramdecls[x] == temp)
					return;
			}
			pCmd->paramdecls.push_back(temp);
		}
		GINL GAIA::GVOID cmd_mutex_decl(const GAIA::GCH* pszCmd1, const GAIA::GCH* pszCmd2)
		{
			GAIA_AST(!GAIA::ALGORITHM::stremp(pszCmd1));
			if(GAIA::ALGORITHM::stremp(pszCmd1))
				return;
			GAIA_AST(!GAIA::ALGORITHM::stremp(pszCmd2));
			if(GAIA::ALGORITHM::stremp(pszCmd2))
				return;
			if(GAIA::ALGORITHM::strcmp(pszCmd1, pszCmd2) > 0)
				GAIA::ALGORITHM::swap(pszCmd1, pszCmd2);
			for(__CmdMutexListType::_sizetype x = 0; x < m_mutex_decls.size(); ++x)
			{
				CmdMutex& temp = m_mutex_decls[x];
				if(temp.cmd1 == pszCmd1 && 
					temp.cmd2 == pszCmd2)
					return;
			}
			CmdMutex temp;
			m_mutex_decls.push_back(temp);
			temp.cmd1 = pszCmd1;
			temp.cmd2 = pszCmd2;
		}
		GINL GAIA::GVOID cmd_coop_decl(const GAIA::GCH* pszCmd1, const GAIA::GCH* pszCmd2)
		{
			GAIA_AST(!GAIA::ALGORITHM::stremp(pszCmd1));
			if(GAIA::ALGORITHM::stremp(pszCmd1))
				return;
			GAIA_AST(!GAIA::ALGORITHM::stremp(pszCmd2));
			if(GAIA::ALGORITHM::stremp(pszCmd2))
				return;
			if(GAIA::ALGORITHM::strcmp(pszCmd1, pszCmd2) > 0)
				GAIA::ALGORITHM::swap(pszCmd1, pszCmd2);
			for(__CmdCoopListType::_sizetype x = 0; x < m_coop_decls.size(); ++x)
			{
				CmdCoop& temp = m_coop_decls[x];
				if(temp.cmd1 == pszCmd1 && 
					temp.cmd2 == pszCmd2)
					return;
			}
			CmdCoop temp;
			m_coop_decls.push_back(temp);
			temp.cmd1 = pszCmd1;
			temp.cmd2 = pszCmd2;
		}
		GINL GAIA::GVOID clear_decl()
		{
			m_decls.clear();
			m_opt_decls.clear();
			m_mutex_decls.clear();
			m_coop_decls.clear();
		}

	public:	/* Command access interface. */
		GINL GAIA::BL load(const GAIA::GCH* pszCmd)
		{
			GAIA_AST(!GAIA::ALGORITHM::stremp(pszCmd));
			if(GAIA::ALGORITHM::stremp(pszCmd))
				return GAIA::False;
			return GAIA::True;
		}

		GINL GAIA::BL checkup() const
		{
			return GAIA::True;
		}

		GINL GAIA::SIZE cmd_size() const
		{
			return m_cmds.size();
		}
		const GAIA::GCH* cmd(const GAIA::SIZE& cmd) const
		{
			if(cmd >= this->cmd_size())
				return GNULL;
			return m_cmds[cmd].cmd.front_ptr();
		}
		GINL GAIA::SIZE param_size(const GAIA::SIZE& cmd) const
		{
			if(cmd >= this->cmd_size())
				return GNULL;
			return m_cmds[cmd].params.size();
		}
		const GAIA::GCH* param(const GAIA::SIZE& cmd, const GAIA::SIZE& param) const
		{
			if(cmd >= this->cmd_size())
				return GNULL;
			if(param >= this->param_size(cmd))
				return GNULL;
			return m_cmds[cmd].params[param].front_ptr();
		}
		GINL GAIA::SIZE findcmd(const GAIA::GCH* pszCmd) const
		{
			GAIA_AST(!GAIA::ALGORITHM::stremp(pszCmd));
			if(GAIA::ALGORITHM::stremp(pszCmd))
				return GINVALID;
			__CmdOPTListType::_datatype t;
			Cmd cmd;
			cmd.cmd = pszCmd;
			t = &cmd;
			__CmdOPTListType::const_it it = m_opt_cmds.lower_bound(t);
			if(it.empty())
				return GINVALID;
			return (**it).index;
		}

	private:
		typedef GAIA::CONTAINER::AString __StringType;
		class ParamDecl
		{
		public:
			GAIA_CLASS_OPERATOR_COMPARE2(start_param_index, start_param_index, end_param_index, end_param_index, ParamDecl);
			GAIA::SIZE start_param_index;
			GAIA::SIZE end_param_index;
			__StringType desc;
			PARAM_TYPE type;
		};
		typedef GAIA::CONTAINER::Vector<ParamDecl> __ParamDeclListType;
		class CmdDecl
		{
		public:
			GAIA_CLASS_OPERATOR_COMPARE2(cmd, cmd, min_param_size, min_param_size, CmdDecl);
			GAIA::SIZE index;
			__StringType cmd;
			__StringType desc;
			CMD_TYPE type;
			__ParamDeclListType::_sizetype min_param_size;
			__ParamDeclListType::_sizetype max_param_size;
			__ParamDeclListType paramdecls;
		};
		typedef GAIA::CONTAINER::Vector<CmdDecl> __CmdDeclListType;
		typedef GAIA::CONTAINER::Vector<__StringType> __ParamListType;
		class Cmd
		{
		public:
			GAIA_CLASS_OPERATOR_COMPARE(cmd, cmd, Cmd);
			GAIA::SIZE index;
			__StringType cmd;
			__ParamListType params;
		};
		typedef GAIA::CONTAINER::Vector<Cmd> __CmdListType;
		typedef GAIA::CONTAINER::Vector<GAIA::CONTAINER::Ref<CmdDecl> > __CmdDeclOPTListType;
		typedef GAIA::CONTAINER::Vector<GAIA::CONTAINER::Ref<Cmd> > __CmdOPTListType;
		class CmdMutex
		{
		public:
			GAIA_CLASS_OPERATOR_COMPARE(cmd1, cmd1, CmdMutex);
			__StringType cmd1;
			__StringType cmd2;
		};
		class CmdCoop
		{
		public:
			GAIA_CLASS_OPERATOR_COMPARE(cmd1, cmd1, CmdCoop);
			__StringType cmd1;
			__StringType cmd2;
		};
		typedef GAIA::CONTAINER::Vector<CmdMutex> __CmdMutexListType;
		typedef GAIA::CONTAINER::Vector<CmdCoop> __CmdCoopListType;

	private:
		GINL GAIA::GVOID init(){m_bBeginDecl = GAIA::False;}

	private:
		GAIA::BL m_bBeginDecl;
		__CmdDeclListType m_decls;
		__CmdDeclOPTListType m_opt_decls;
		__CmdMutexListType m_mutex_decls;
		__CmdCoopListType m_coop_decls;
		__CmdListType m_cmds;
		__CmdOPTListType m_opt_cmds;
	};
};

#endif
