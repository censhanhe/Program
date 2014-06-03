#ifndef 	__DWARFS_MISC_CMDPARAM_H__
#define 	__DWARFS_MISC_CMDPARAM_H__

namespace DWARFS_MISC
{
	class CmdParam : public GAIA::Base
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
			PARAM_TYPE_STRING,
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
			GAIA_AST(this->is_begin_decl());
			if(!this->is_begin_decl())
				return GINVALID;
			CmdDecl temp;
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
			temp.index = m_decls.size();
			m_decls.push_back(temp);
			return m_decls.size() - 1;
		}
		GINL GAIA::BL cmd_param_decl(
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
				return GAIA::False;
			GAIA_AST(min_param_size >= 0);
			if(min_param_size < 0)
				return GAIA::False;
			GAIA_AST(max_param_size >= 0 || max_param_size == GINVALID);
			if(max_param_size < 0 && max_param_size != GINVALID)
				return GAIA::False;
			GAIA_AST(min_param_size <= max_param_size || max_param_size == GINVALID);
			if(min_param_size > max_param_size && max_param_size != GINVALID)
				return GAIA::False;
			GAIA_AST(start_param_index >= 0);
			if(start_param_index < 0)
				return GAIA::False;
			GAIA_AST(end_param_index >= 0 || end_param_index == GINVALID);
			if(end_param_index < 0 && end_param_index != GINVALID)
				return GAIA::False;
			GAIA_AST(start_param_index <= end_param_index || end_param_index == GINVALID);
			if(start_param_index > end_param_index && end_param_index != GINVALID)
				return GAIA::False;
			GAIA_AST(this->is_begin_decl());
			if(!this->is_begin_decl())
				return GAIA::False;
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
				return GAIA::False;
			ParamDecl temp;
			temp.start_param_index = start_param_index;
			temp.end_param_index = end_param_index;
			if(!GAIA::ALGORITHM::stremp(pszDesc))
				temp.desc = pszDesc;
			temp.type = t;
			for(__ParamDeclListType::_sizetype x = 0; x < pCmd->paramdecls.size(); ++x)	
			{
				if(pCmd->paramdecls[x] == temp)
					return GAIA::False;
			}
			pCmd->paramdecls.push_back(temp);
			return GAIA::True;
		}
		GINL GAIA::GVOID cmd_mutex_decl(const GAIA::GCH* pszCmd1, const GAIA::GCH* pszCmd2)
		{
			GAIA_AST(!GAIA::ALGORITHM::stremp(pszCmd1));
			if(GAIA::ALGORITHM::stremp(pszCmd1))
				return;
			GAIA_AST(!GAIA::ALGORITHM::stremp(pszCmd2));
			if(GAIA::ALGORITHM::stremp(pszCmd2))
				return;
			GAIA_AST(this->is_begin_decl());
			if(!this->is_begin_decl())
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
			m_mutex_decls.back().cmd1 = pszCmd1;
			m_mutex_decls.back().cmd2 = pszCmd2;
		}
		GINL GAIA::GVOID cmd_coop_decl(const GAIA::GCH* pszCmd1, const GAIA::GCH* pszCmd2)
		{
			GAIA_AST(!GAIA::ALGORITHM::stremp(pszCmd1));
			if(GAIA::ALGORITHM::stremp(pszCmd1))
				return;
			GAIA_AST(!GAIA::ALGORITHM::stremp(pszCmd2));
			if(GAIA::ALGORITHM::stremp(pszCmd2))
				return;
			GAIA_AST(this->is_begin_decl());
			if(!this->is_begin_decl())
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
			m_coop_decls.back().cmd1 = pszCmd1;
			m_coop_decls.back().cmd2 = pszCmd2;
		}
		GINL GAIA::GVOID clear_decl()
		{
			m_decls.clear();
			m_opt_decls.clear();
			m_mutex_decls.clear();
			m_coop_decls.clear();
		}
		GINL GAIA::SIZE finddecl(const GAIA::GCH* pszCmdName, const GAIA::SIZE& min_param_size) const
		{
			GAIA_AST(!GAIA::ALGORITHM::stremp(pszCmdName));
			if(GAIA::ALGORITHM::stremp(pszCmdName))
				return GINVALID;
			GAIA_AST(!this->is_begin_decl());
			if(this->is_begin_decl())
				return GINVALID;
			CmdDecl cmddecl;
			cmddecl.cmd = pszCmdName;
			cmddecl.min_param_size = min_param_size;
			__CmdDeclOPTListType::_datatype t = &cmddecl;
			__CmdDeclOPTListType::const_it it = m_opt_decls.upper_bound(t);
			if(it.empty())
				return GINVALID;
			if((**it).cmd != pszCmdName)
				return GINVALID;
			return (**it).index;
		}

	public:	/* Command access interface. */
		GINL GAIA::BL build(const GAIA::GCH* pszCmd, GAIA::PRINT::PrintBase& prt)
		{
			GAIA_AST(!this->is_begin_decl());
			if(this->is_begin_decl())
				return GAIA::False;
			GAIA_AST(!GAIA::ALGORITHM::stremp(pszCmd));
			if(GAIA::ALGORITHM::stremp(pszCmd))
				return GAIA::False;

			GAIA::BL bCheckSuccess = GAIA::False;

			/* Construct word list. */
			__ParamListType words;
			const GAIA::GCH* p = pszCmd;
			const GAIA::GCH* pLast = p;
			__StringType str;
			while(*p != 0 || pLast != p)
			{
				if(*p == '\r' || *p == '\n' || *p == ' ' || *p == '\t' || *p == '\0')
				{
					if(p > pLast)
					{
						str.resize(p - pLast);
						GAIA::ALGORITHM::xmemcpy(str.front_ptr(), pLast, (p - pLast) * sizeof(__StringType::_datatype));
						__StringType::_sizetype index_begin = 0, index_end = str.size() - 1;
						for(; index_begin < str.size(); ++index_begin)
						{
							if(str[index_begin] != '\r' && 
								str[index_begin] != '\n' && 
								str[index_begin] != ' ' && 
								str[index_begin] != '\t')
								break;
						}
						for(;;)
						{
							if(str[index_end] != '\r' && 
								str[index_end] != '\n' && 
								str[index_end] != ' ' && 
								str[index_end] != '\t')
								break;
							--index_end;
							if(index_end == GINVALID)
								break;
						}
						if(index_begin != str.size() && index_end != GINVALID)
						{
							str.mid(index_begin, index_end);
							words.push_back(str);
						}
						if(*p == 0)
						{
							pLast = p;
							break;
						}
						else
							pLast = p + 1;
					}
				}
				++p;
			}

			/* Analyze to command. */
			__ParamListType::_sizetype head_index = 0;
			for(__ParamListType::_sizetype x = 0; x < words.size(); ++x)
			{
				GAIA::BL bMatch = GAIA::False;
				__StringType& word = words[x];
				if(m_decls.empty())
					bMatch = GAIA::True;
				else
				{
					if(this->finddecl(word, GAIA::MAXSIZE) != GINVALID)
						bMatch = GAIA::True;
				}
				if(bMatch)
				{
					Cmd cmd;
					cmd.index = m_cmds.size();
					cmd.cmd = word;
					m_cmds.push_back(cmd);
				}
				else
				{
					if(m_cmds.empty())
					{
						prt << "CmdParam:Invalid command or parameter without command! \"" << word.front_ptr() << "\"\n";
						goto FUNCTION_END;
					}
					m_cmds.back().params.push_back(word);
				}
			}

			/* Checkup. */
			for(__CmdListType::_sizetype x = 0; x < m_cmds.size(); ++x)
			{
				const Cmd& temp = m_cmds[x];
				GAIA::SIZE uDecl = this->finddecl(temp.cmd, temp.params.size());
				if(uDecl == GINVALID)
				{
					prt << "CmdParam:Invalid command! \"" << temp.cmd.front_ptr() << "\"\n";
					goto FUNCTION_END;
				}
				CmdDecl& decl = m_decls[uDecl];
				if(temp.params.size() < decl.min_param_size)
				{
					prt << "CmdParam:Insufficient parameter count! \"" << temp.cmd.front_ptr() << "\"" << 
						" [" << decl.min_param_size << ", " << decl.max_param_size << "]" << "\n";
					goto FUNCTION_END;
				}
				if(decl.max_param_size != GINVALID)
				{
					if(temp.params.size() > decl.max_param_size)
					{
						prt << "CmdParam:Insufficient parameter count! \"" << temp.cmd.front_ptr() << "\"" << 
							" [" << decl.min_param_size << ", " << decl.max_param_size << "]" << "\n";
						goto FUNCTION_END;
					}
				}
			}
			for(GAIA::SIZE x = 0; x < m_decls.size(); ++x)
			{
				CmdDecl& decl = m_decls[x];
				if(decl.type == CMD_TYPE_MUSTEXIST)
				{
					GAIA::BL bExist = GAIA::False;
					for(GAIA::SIZE y = 0; y < m_cmds.size(); ++y)
					{
						const Cmd& temp = m_cmds[x];
						if(temp.cmd == decl.cmd)
						{
							bExist = GAIA::True;
							break;
						}
					}
					if(!bExist)
					{
						prt << "CmdParam:Must exist command! \"" << decl.cmd.front_ptr() << "\"\n";
						goto FUNCTION_END;
					}
				}
			}

			/* Checkup mutex and coop. */
			for(__CmdListType::_sizetype x = 0; x < m_cmds.size(); ++x)
			{
				Cmd& temp = m_cmds[x];
				for(__CmdMutexListType::_sizetype y = 0; y < m_mutex_decls.size(); ++y)
				{
					const CmdMutex& cm = m_mutex_decls[y];
					const __StringType* pCmd = GNULL;
					if(cm.cmd1 == temp.cmd)
						pCmd = &cm.cmd2;
					else if(cm.cmd2 == temp.cmd)
						pCmd = &cm.cmd1;
					if(pCmd != GNULL)
					{
						for(__CmdListType::_sizetype z = 0; z < m_cmds.size(); ++z)
						{
							if(z == x)
								continue;
							if(m_cmds[z].cmd == *pCmd)
							{
								prt << "CmdParam:Command mutex! \"" << temp.cmd.front_ptr() << "\" " << "and" << "\"" << pCmd->front_ptr() << "\"\n";
								goto FUNCTION_END;
							}
						}
					}
				}
				for(__CmdCoopListType::_sizetype y = 0; y < m_coop_decls.size(); ++y)
				{
					const CmdCoop& cc = m_coop_decls[y];
					const __StringType* pCmd = GNULL;
					if(cc.cmd1 == temp.cmd)
						pCmd = &cc.cmd2;
					else if(cc.cmd2 == temp.cmd)
						pCmd = &cc.cmd1;
					if(pCmd != GNULL)
					{
						GAIA::BL bExist = GAIA::False;
						for(__CmdListType::_sizetype z = 0; z < m_cmds.size(); ++z)
						{
							if(z == x)
								continue;
							if(m_cmds[z].cmd == *pCmd)
							{
								bExist = GAIA::True;
								break;
							}
						}
						if(!bExist)
						{
							prt << "CmdParam:Command coop! \"" << temp.cmd.front_ptr() << "\" " << "and" << "\"" << pCmd->front_ptr() << "\"\n";
							goto FUNCTION_END;
						}
					}
				}
			}

			/* Optimize. */
			m_opt_cmds.clear();
			for(__CmdListType::_sizetype x = 0; x < m_cmds.size(); ++x)
			{
				__CmdOPTListType::_datatype t;
				t = &m_cmds[x];
				m_opt_cmds.push_back(t);
			}
			m_opt_cmds.sort();

			/* Sign to success. */
			bCheckSuccess = GAIA::True;

		FUNCTION_END:
			if(!bCheckSuccess)
			{
				this->clear_cmd();
				return GAIA::False;
			}
			return GAIA::True;
		}
		GINL GAIA::GVOID clear_cmd()
		{
			m_cmds.clear();
			m_opt_cmds.clear();
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
			GAIA_AST(!this->is_begin_decl());
			if(this->is_begin_decl())
				return GINVALID;
			__CmdOPTListType::_datatype t;
			Cmd cmd;
			cmd.cmd = pszCmd;
			t = &cmd;
			__CmdOPTListType::const_it it = m_opt_cmds.lower_bound(t);
			if(it.empty())
				return GINVALID;
			if((**it).cmd != pszCmd)
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
