#ifndef		__GAIA_FRAMEWORK_INSTANCE_H__
#define		__GAIA_FRAMEWORK_INSTANCE_H__

namespace GAIA
{
	namespace FRAMEWORK
	{
		class Instance : public Object
		{
		private:
			friend class Factory;
		public:
			Instance(){m_nRef = 1; m_bDestructing = GAIA::False;}
			virtual ~Instance(){}
			virtual ClsID GetClassID() const = 0;
			GAIA::GVOID Reference(){m_nRef++;}
			GAIA::GVOID Release(){m_nRef--; if(m_nRef == 0 && !m_bDestructing){if(this->IsBegin()) this->End(); m_bDestructing = true; delete this;}}
			GAIA::N32 GetRef() const{return m_nRef;}
		protected:
			virtual GAIA::BL Begin(GAIA::GVOID* pParameter) = 0;
			virtual GAIA::BL End() = 0;
			virtual GAIA::BL IsBegin() const = 0;
		private:
			GAIA::N32 m_nRef;
			GAIA::N8 m_bDestructing : 1;		
		};
	};
};

#endif
