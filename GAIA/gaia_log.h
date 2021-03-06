#ifndef		__GAIA_LOG_H__
#define		__GAIA_LOG_H__

namespace GAIA
{
	namespace LOG
	{
		class Log : public GAIA::Base
		{
		public:
			typedef GAIA::U32 __FilterType;
			GAIA_ENUM_BEGIN(TYPE)
				TYPE_LOG = 1 << 0,
				TYPE_WARNING = 1 << 1,
				TYPE_ERROR = 1 << 2,
			GAIA_ENUM_END(TYPE)
			class CallBack : public GAIA::Base
			{
			public:
				virtual GAIA::BL WriteLog(
					const GAIA::TIME::Time& logtime,
					GAIA::LOG::Log::TYPE type,
					GAIA::LOG::Log::__FilterType userfilter,
					const GAIA::TCH* pszLog) = 0;
				virtual GAIA::BL FlushLog() = 0;
			};
		private:
			/* Internal data structure. */
			typedef GAIA::CTN::BasicChars<GAIA::TCH, GAIA::N32, 2> __LineBreakFlagType;
			class Node : public GAIA::Base
			{
			public:
				GAIA::TIME::Time logtime;
				TYPE type;
				__FilterType userfilter;
				GAIA::CTN::TString strLog;
			};
			typedef GAIA::CTN::Vector<Node> __NodeList;
		public:
			/* Stream output flag. */
			class FlagType : public GAIA::Base
			{
				friend class Log;
			private:
				GAIA::LOG::Log::TYPE m_type;
			};
			class FlagUserFilter : public GAIA::Base
			{
				friend class Log;
			private:
				GAIA::LOG::Log::__FilterType m_filter;
			};
			class FlagEnd : public GAIA::Base
			{
				friend class Log;
			private:
			};
		public:
			/* Base function. */
			GINL Log(){this->init();}
			GINL ~Log(){this->Flush();}
			GINL GAIA::GVOID SetBufferSize(const __NodeList::_sizetype& size)
			{
				if(size == m_nodes.size())
					return;
				if(!m_nodes.empty())
					this->Flush();
				m_nodes.reserve(size);
			}
			GINL __NodeList::_sizetype GetBufferSize() const{return m_nodes.size();}
			GINL GAIA::GVOID SetCallBack(CallBack* pCallBack){m_pCallBack = pCallBack;}
			GINL CallBack* GetCallBack() const{return m_pCallBack;}
			GINL GAIA::GVOID SetTypeFilter(const __FilterType& filter){m_typefilter = filter;}
			GINL const __FilterType& GetTypeFilter() const{return m_typefilter;}
			GINL GAIA::GVOID SetUserFilter(const __FilterType& filter){m_userfilter = filter;}
			GINL const __FilterType& GetUserFilter() const{return m_userfilter;}
			GINL GAIA::BL SetLineBreak(const GAIA::TCH* pszLineBreak)
			{
				if(GAIA::ALGO::stremp(pszLineBreak))
					return GAIA::False;
				if(GAIA::ALGO::strcmp(pszLineBreak, GAIA_FILELINEBREAK_RN) != 0 && 
					GAIA::ALGO::strcmp(pszLineBreak, GAIA_FILELINEBREAK_R) != 0 && 
					GAIA::ALGO::strcmp(pszLineBreak, GAIA_FILELINEBREAK_N) != 0)
					return GAIA::False;
				m_linebreak = pszLineBreak;
				return GAIA::True;
			}
			GINL const GAIA::TCH* GetLineBreak() const{return m_linebreak;}
			GINL GAIA::BL Write(TYPE type, __FilterType userfilter, const GAIA::TCH* pszLog)
			{
				if(!(type & this->GetTypeFilter()))
					return GAIA::False;
				if(!(userfilter & this->GetUserFilter()))
					return GAIA::False;
				if(GAIA::ALGO::stremp(pszLog))
					return GAIA::False;
				GAIA::TIME::Time logtime;
				logtime.systime();
				GAIA::SYNC::AutoLock al(m_lock);
				GAIA_AST(!m_bCallBacking);
				if(m_bCallBacking)
					return GAIA::False;
				if(m_nodes.capacity() == 0)
				{
					if(m_pCallBack == GNIL)
						return GAIA::False;
					m_bCallBacking = GAIA::True;
					{
						m_pCallBack->WriteLog(logtime, type, userfilter, pszLog);
					}
					m_bCallBacking = GAIA::False;
					m_pCallBack->FlushLog();
				}
				else
				{
					if(m_nodes.size() == m_nodes.capacity())
						this->Flush();
					Node n;
					m_nodes.push_back(n);
					Node& nr = m_nodes.back();
					nr.logtime = logtime;
					nr.type = type;
					nr.userfilter = userfilter;
					nr.strLog = pszLog;
				}
				return GAIA::True;
			}
			GINL GAIA::GVOID Flush()
			{
				if(m_nodes.empty())
					return;
				GAIA::SYNC::AutoLock al(m_lock);
				if(m_pCallBack != GNIL)
				{
					m_bCallBacking = GAIA::True;
					{
						for(__NodeList::_sizetype x = 0; x < m_nodes.size(); ++x)
						{
							Node& n = m_nodes[x];
							m_pCallBack->WriteLog(n.logtime, n.type, n.userfilter, n.strLog);
						}
					}
					m_bCallBacking = GAIA::False;
					m_pCallBack->FlushLog();
				}
				m_nodes.clear();
			}
		public:
			/* Stream output. */
			virtual Log& operator << (GAIA::BL t){this->WriteToStringStream(t); return *this;}
			virtual Log& operator << (GAIA::NM t){this->WriteToStringStream(t); return *this;}
			virtual Log& operator << (GAIA::UM t){this->WriteToStringStream(t); return *this;}
			virtual Log& operator << (GAIA::N8 t){this->WriteToStringStream(t); return *this;}
			virtual Log& operator << (GAIA::N16 t){this->WriteToStringStream(t); return *this;}
			virtual Log& operator << (GAIA::N32 t){this->WriteToStringStream(t); return *this;}
			virtual Log& operator << (const GAIA::N64& t){this->WriteToStringStream(t); return *this;}
			virtual Log& operator << (GAIA::U8 t){this->WriteToStringStream(t); return *this;}
			virtual Log& operator << (GAIA::U16 t){this->WriteToStringStream(t); return *this;}
			virtual Log& operator << (GAIA::U32 t){this->WriteToStringStream(t); return *this;}
			virtual Log& operator << (const GAIA::U64& t){this->WriteToStringStream(t); return *this;}
			virtual Log& operator << (GAIA::F32 t){this->WriteToStringStream(t); return *this;}
			virtual Log& operator << (const GAIA::F64& t){this->WriteToStringStream(t); return *this;}
			virtual Log& operator << (const GAIA::WCH& t){this->WriteToStringStream(t); return *this;}
			virtual Log& operator << (const GAIA::CH* p){this->WriteToStringStream(p); return *this;}
			virtual Log& operator << (const GAIA::WCH* p){this->WriteToStringStream(p); return *this;}
			virtual Log& operator << (const GAIA::X128& t){this->WriteToStringStream(t); return *this;}
			virtual Log& operator << (const GAIA::LOG::Log::FlagType& t)
			{
				this->EnterLock();
				m_flagtype = t;
				return *this;
			}
			virtual Log& operator << (const GAIA::LOG::Log::FlagUserFilter& t)
			{
				this->EnterLock();
				m_flaguserfilter = t;
				return *this;
			}
			virtual Log& operator << (const GAIA::LOG::Log::FlagEnd& t)
			{
				/* Enter lock and output. */
				this->EnterLock();
				this->Write(m_flagtype.m_type, m_flaguserfilter.m_filter, m_sprt.GetString());
				GAIA::STREAM::StringStream::__CharType szEmpty[1];
				szEmpty[0] = '\0';
				m_sprt.SetString(szEmpty);
				m_flagtype.m_type = TYPE_LOG;
				m_flaguserfilter.m_filter = (__FilterType)GINVALID;

				/* Release the lock. */
				GAIA_AST((GAIA::N64)m_lockcnt >= 0);
				for(;;)
				{
					GAIA::N64 nNew = m_lockcnt.Decrease();
					if(nNew < 0)
					{
						GAIA_AST(nNew == -1);
						m_lockcnt.Increase();
						break;
					}
					m_lock.Leave();
					if(nNew == 0)
						break;
				}
				return *this;
			}
			GINL GAIA::LOG::Log::FlagType Type(TYPE t)
			{
				FlagType ret;
				ret.m_type = t;
				return ret;
			}
			GINL GAIA::LOG::Log::FlagUserFilter UserFilter(const __FilterType& filter)
			{
				FlagUserFilter ret;
				ret.m_filter = filter;
				return ret;
			}
			GINL GAIA::LOG::Log::FlagEnd End() const
			{
				FlagEnd ret;
				return ret;
			}
		public:
			/* Helper function. */
			GINL const GAIA::TCH* GetLogTypeString(TYPE type) const
			{
				switch(type)
				{
				case TYPE_LOG:
					return _T("Log");
				case TYPE_WARNING:
					return _T("War");
				case TYPE_ERROR:
					return _T("Err");
				default:
					return GNILTSTR;
				}
			}
		private:
			GINL GAIA::GVOID init()
			{
				m_linebreak = _T(GAIA_FILELINEBREAK);
				m_pCallBack = GNIL;
				m_typefilter = (__FilterType)GINVALID;
				m_userfilter = (__FilterType)GINVALID;
				m_bCallBacking = GAIA::False;
				m_flagtype.m_type = TYPE_LOG;
				m_flaguserfilter.m_filter = (__FilterType)GINVALID;
			}
			template<typename _ParamDataType> GAIA::GVOID WriteToStringStream(_ParamDataType t)
			{
				this->EnterLock();
				m_sprt << t;
			}
			GINL GAIA::GVOID EnterLock()
			{
				m_lock.Enter();
				m_lockcnt.Increase();
			}
		private:
			__LineBreakFlagType m_linebreak;
			CallBack* m_pCallBack;
			__FilterType m_typefilter;
			__FilterType m_userfilter;
			__NodeList m_nodes;
			GAIA::SYNC::Lock m_lock;
			GAIA::SYNC::Atomic m_lockcnt;
			GAIA::BL m_bCallBacking;
			GAIA::STREAM::StringStream m_sprt;
			FlagType m_flagtype;
			FlagUserFilter m_flaguserfilter;
		};
	};
};

#endif
