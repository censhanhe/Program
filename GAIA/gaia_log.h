#ifndef		__GAIA_LOG_H__
#define		__GAIA_LOG_H__

namespace GAIA
{
	namespace LOG
	{
		class Log : public GAIA::Base
		{
		public:
			typedef GAIA::U64 __FilterType;
			GAIA_ENUM_BEGIN(TYPE)
				TYPE_LOG,
				TYPE_WARNING,
				TYPE_ERROR,
			GAIA_ENUM_END(TYPE)
			class CallBack : public GAIA::Base
			{
			public:
				virtual GAIA::BL LogWrite(
					const GAIA::TIME::Time& logtime,
					GAIA::LOG::Log::TYPE type,
					GAIA::LOG::Log::__FilterType filter,
					const GAIA::TCH* pszLog) = 0;
			};
		private:
			class Node : public GAIA::Base
			{
			public:
				GAIA::TIME::Time logtime;
				TYPE type;
				__FilterType filter;
				GAIA::CTN::TString strLog;
			};
			typedef GAIA::CTN::Vector<Node> __NodeList;
		public:
			class FlagEnd : public GAIA::Base
			{
			public:
			};
		public:
			GINL Log(){this->init();}
			GINL ~Log(){}
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
			GINL GAIA::GVOID SetFilter(__FilterType filter){m_filter = filter;}
			GINL __FilterType GetFilter() const{return m_filter;}
			GINL GAIA::BL Write(TYPE type, __FilterType filter, const GAIA::TCH* pszLog)
			{
				if(!(filter & m_filter))
					return GAIA::False;
				if(GAIA::ALGO::stremp(pszLog))
					return GAIA::False;
				GAIA::TIME::Time logtime;
				GAIA::SYNC::AutoLock al(m_lock);
				if(m_nodes.capacity() == 0)
				{
					if(m_pCallBack == GNIL)
						return GAIA::False;
					m_pCallBack->LogWrite(logtime, type, filter, pszLog);
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
					nr.filter = filter;
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
					for(__NodeList::_sizetype x = 0; x < m_nodes.size(); ++x)
					{
						Node& n = m_nodes[x];
						m_pCallBack->LogWrite(n.logtime, n.type, n.filter, n.strLog);
					}
				}
				m_nodes.clear();
			}
		public:
			virtual Log& operator << (GAIA::BL t){this->WriteToStringPrint(t); return *this;}
			virtual Log& operator << (GAIA::NM t){this->WriteToStringPrint(t); return *this;}
			virtual Log& operator << (GAIA::UM t){this->WriteToStringPrint(t); return *this;}
			virtual Log& operator << (GAIA::N8 t){this->WriteToStringPrint(t); return *this;}
			virtual Log& operator << (GAIA::N16 t){this->WriteToStringPrint(t); return *this;}
			virtual Log& operator << (GAIA::N32 t){this->WriteToStringPrint(t); return *this;}
			virtual Log& operator << (const GAIA::N64& t){this->WriteToStringPrint(t); return *this;}
			virtual Log& operator << (GAIA::U8 t){this->WriteToStringPrint(t); return *this;}
			virtual Log& operator << (GAIA::U16 t){this->WriteToStringPrint(t); return *this;}
			virtual Log& operator << (GAIA::U32 t){this->WriteToStringPrint(t); return *this;}
			virtual Log& operator << (const GAIA::U64& t){this->WriteToStringPrint(t); return *this;}
			virtual Log& operator << (GAIA::F32 t){this->WriteToStringPrint(t); return *this;}
			virtual Log& operator << (const GAIA::F64& t){this->WriteToStringPrint(t); return *this;}
			virtual Log& operator << (const GAIA::WCH& t){this->WriteToStringPrint(t); return *this;}
			virtual Log& operator << (const GAIA::CH* p){this->WriteToStringPrint(p); return *this;}
			virtual Log& operator << (const GAIA::WCH* p){this->WriteToStringPrint(p); return *this;}
			virtual Log& operator << (const GAIA::X128& t){this->WriteToStringPrint(t); return *this;}
			virtual Log& operator << (const GAIA::LOG::Log::FlagEnd& t)
			{
				return *this;
			}
		public:
			GINL const GAIA::LOG::Log::FlagEnd& End() const{return m_flagend;}
		private:
			GINL GAIA::GVOID init()
			{
				m_pCallBack = GNIL;
				m_filter = (__FilterType)GINVALID;
			}
			template<typename _ParamDataType> GAIA::GVOID WriteToStringPrint(_ParamDataType t)
			{
				GAIA::SYNC::AutoLock al(m_locksprt);
				m_sprt << t;
			}
		private:
			CallBack* m_pCallBack;
			__FilterType m_filter;
			__NodeList m_nodes;
			GAIA::SYNC::Lock m_lock;
			GAIA::SYNC::Lock m_locksprt;
			GAIA::PRINT::StringPrint m_sprt;
			FlagEnd m_flagend;
		};
	};
};

#endif
