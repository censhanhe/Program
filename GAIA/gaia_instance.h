#ifndef		__GAIA_FRAMEWORK_INSTANCE_H__
#define		__GAIA_FRAMEWORK_INSTANCE_H__

namespace GAIA
{
	namespace FWORK
	{
		class Instance : public RefObject
		{
		private:
			friend class GAIA::FWORK::Factory;
		public:
			GINL Instance(){this->init();}
			GINL ~Instance(){}
			virtual GAIA::FWORK::ClsID GetClassID() const = 0;
			GINL GAIA::FWORK::Factory* GetFactory() const{return m_pFactory;}
		protected:
			virtual GAIA::GVOID RefObjectDestruct(){if(this->IsInstanceBegin()) this->InstanceEnd();}
			virtual GAIA::BL InstanceBegin(GAIA::GVOID* pParameter)
			{
				if(m_bBegin)
					return GAIA::False;
				m_bBegin = GAIA::True;
				return GAIA::True;
			}
			virtual GAIA::BL InstanceEnd()
			{
				if(!m_bBegin)
					return GAIA::False;
				m_bBegin = GAIA::False;
				return GAIA::True;
			}
			virtual GAIA::BL IsInstanceBegin() const{return m_bBegin;}
		private:
			GINL GAIA::GVOID init(){m_pFactory = GNIL; m_bBegin = GAIA::False;}
			GINL GAIA::GVOID SetFactory(GAIA::FWORK::Factory* pFactory){m_pFactory = pFactory;}
		private:
			GAIA::FWORK::Factory* m_pFactory;
			GAIA::U8 m_bBegin : 1;
		};
	};
};

#endif
