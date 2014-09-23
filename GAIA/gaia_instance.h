#ifndef		__GAIA_FRAMEWORK_INSTANCE_H__
#define		__GAIA_FRAMEWORK_INSTANCE_H__

namespace GAIA
{
	namespace FWORK
	{
		class Instance : public RefObject
		{
		private:
			friend class Factory;
		public:
			GINL Instance(){this->init();}
			GINL ~Instance(){}
			virtual GAIA::FWORK::ClsID GetClassID() const = 0;
		protected:
			virtual GAIA::GVOID Destruct(){if(this->IsBegin()) this->End();}
		protected:
			virtual GAIA::BL Begin(GAIA::GVOID* pParameter)
			{
				if(m_bBegin)
					return GAIA::False;
				m_bBegin = GAIA::True;
				return GAIA::True;
			}
			virtual GAIA::BL End()
			{
				if(!m_bBegin)
					return GAIA::False;
				m_bBegin = GAIA::False;
				return GAIA::True;
			}
			virtual GAIA::BL IsBegin() const{return m_bBegin;}
		private:
			GINL GAIA::GVOID init(){m_bBegin = GAIA::False;}
		private:
			GAIA::U8 m_bBegin : 1;
		};
	};
};

#endif
