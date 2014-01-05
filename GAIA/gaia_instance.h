#ifndef		__GAIA_FRAMEWORK_INSTANCE_H__
#define		__GAIA_FRAMEWORK_INSTANCE_H__

namespace GAIA
{
	namespace FRAMEWORK
	{
		class Instance
		{
		public:
			Instance(){m_nRef = 1; m_bDestructing = GAIA::False;}
			virtual ~Instance(){}
			virtual ClsID GetClassID() const = 0;
			GAIA::GVOID Reference(){m_nRef++;}
			GAIA::GVOID Release(){m_nRef--; if(m_nRef == 0 && !m_bDestructing){m_bDestructing = true; delete this;}}
			GAIA::N32 GetRef() const{return m_nRef;}
		private:
			GAIA::N32 m_nRef;
			GAIA::N8 m_bDestructing : 1;		
		};
	};
};

#endif
