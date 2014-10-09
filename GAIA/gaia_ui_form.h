#ifndef		__GAIA_UI_FORM_H__
#define		__GAIA_UI_FORM_H__

namespace GAIA
{
	namespace UI
	{
		class Form : public virtual GAIA::MVC::View, public virtual GAIA::LAYOUT::Widget2D, public virtual GAIA::COLLISIONER::Bounder
		{
		public:
			typedef GAIA::UI::Form __MyType;
			typedef GAIA::MATH::VEC3<GAIA::REAL> __PosType;
			typedef GAIA::MATH::VEC3<GAIA::REAL> __SizeType;
			typedef GAIA::MATH::VEC3<GAIA::REAL> __RotateType;
			typedef GAIA::MATH::ARGB<GAIA::U8> __ColorType;
			typedef GAIA::CTN::Vector<__MyType*> __ChildListType;
		public:
			class Desc : public virtual GAIA::FWORK::InstanceDesc
			{
			public:
				virtual GAIA::GVOID reset()
				{
					pszName = GNIL;
				}
				virtual GAIA::BL check() const
				{
					if(GAIA::ALGO::stremp(pszName))
						return GAIA::False;
					return GAIA::True;
				}
				const GAIA::TCH* pszName;
			};
		public:
			/* Base. */
			GINL Form(){this->init();}
			GINL ~Form(){}

			/* Location management. */
			GINL GAIA::BL Position(const __PosType& pos){m_pos = pos;}
			GINL const __PosType& Position() const{return m_pos;}
			GINL GAIA::BL Size(const __SizeType& size){m_size = size;}
			GINL const __SizeType& Size() const{return m_size;}
			GINL GAIA::BL Rotate(const __RotateType& rotate){m_rotate = rotate;}
			GINL const __RotateType& Rotate() const{return m_rotate;}

			/* Link management. */
			GINL GAIA::BL SetParent(__MyType* pParent)
			{
				if(pParent == GNIL)
				{
					if(m_parent == GNIL)
						return GAIA::True;
					else
					{
						GAIA::SIZE nFinded = m_parent->m_childs.find(this, 0);
						if(nFinded == GINVALID)
						{
							GAIA_AST(GAIA::ALWAYSFALSE);
							return GAIA::False;
						}
						m_parent->m_childs[nFinded] = GNIL;
						m_parent = GNIL;
						this->Release();
					}
				}
				else
				{
					if(m_parent != GNIL)
					{
						if(!this->SetParent(GNIL))
							return GAIA::False;
					}

					this->Reference();
					GAIA::SIZE nFreeIndex = pParent->m_childs.find(GNIL, 0);
					if(nFreeIndex == GINVALID)
						pParent->m_childs.push_back(this);
					else
						pParent->m_childs[nFreeIndex] = this;
				}
			}
			GINL __MyType* GetParent() const
			{
				if(m_parent != GNIL)
					m_parent->Reference();
				return m_parent;
			}
			GINL __MyType* GetRoot()
			{
				__MyType* pForm = this;
				for(; pForm->GetParent() != GNIL; )
					pForm = pForm->GetParent();
				return pForm;
			}
			GINL GAIA::BL CollectChild(__ChildListType& listResult) const
			{
				GAIA::BL bExist = GAIA::False;
				for(__ChildListType::_sizetype x = 0; x < m_childs.size(); ++x)
				{
					__MyType* pForm = m_childs[x];
					if(pForm != GNIL)
					{
						listResult.push_back(pForm);
						pForm->Reference();
						bExist = GAIA::True;
					}
				}
				return bExist;
			}

			/* Msg management. */
			GINL GAIA::GVOID EnableCallbackMsg(GAIA::BL bEnable){m_bEnableCallBackMsg = bEnable;}
			GINL GAIA::BL IsEnableCallBackMsg() const{return m_bEnableCallBackMsg;}

			/* Model management. */
			GINL GAIA::GVOID Active(GAIA::BL bActive){m_bActive = bActive;}
			GINL GAIA::BL Active() const{return m_bActive;}
			GINL GAIA::GVOID Focus(GAIA::BL bFocus){m_bFocus = bFocus;}
			GINL GAIA::BL Focus() const{return m_bFocus;}
			GINL GAIA::GVOID FocusAble(GAIA::BL bFocusAble){m_bFocusAble = bFocusAble;}
			GINL GAIA::BL FocusAble() const{return m_bFocusAble;}
			GINL GAIA::GVOID Capture(GAIA::BL bCapture){m_bCapture = bCapture;}
			GINL GAIA::BL Capture() const{return m_bCapture;}
			GINL GAIA::GVOID Modal(GAIA::BL bModal){m_bModal = bModal;}
			GINL GAIA::BL Modal() const{return m_bModal;}

			/* Display management. */
			GINL GAIA::BL Show(GAIA::BL bShow){m_bShow = bShow;}
			GINL GAIA::BL IsShow() const{return m_bShow;}
			GINL GAIA::BL Color(const __ColorType& cr){m_cr = cr;}
			GINL const __ColorType& Color() const{return m_cr;}

			/* Scissor management. */
			GINL GAIA::GVOID EnableScissor(GAIA::BL bEnable){m_bScissor = bEnable;}
			GINL GAIA::BL IsEnableScissor() const{return m_bScissor;}
			
		public:
			virtual GAIA::BL Create(const __MyType::Desc& desc)
			{
				if(!desc.check())
					return GAIA::False;
				if(!GAIA::ALGO::stremp(m_desc.pszName))
					return GAIA::False;
				m_desc = desc;
				m_desc.pszName = GAIA::ALGO::strnew(m_desc.pszName);
				return GAIA::True;
			}
			virtual GAIA::BL Destroy()
			{
				if(GAIA::ALGO::stremp(m_desc.pszName))
					return GAIA::False;
				GAIA_MFREE_SAFE(m_desc.pszName);
				m_desc.reset();
				return GAIA::True;
			}
			virtual GAIA::BL IsCreated() const{return !GAIA::ALGO::stremp(m_desc.pszName);}
			virtual const __MyType::Desc& GetDesc() const{return m_desc;}

		private:
			GINL GAIA::GVOID init()
			{
				m_desc.reset();
				m_pos = (__PosType::_datatype)0;
				m_size = (__SizeType::_datatype)0;
				m_rotate = (__RotateType::_datatype)0;
				m_parent = GNIL;
				m_cr = 0xFF;
				m_bEnableCallBackMsg = GAIA::True;
				m_bActive = GAIA::False;
				m_bFocus = GAIA::False;
				m_bFocusAble = GAIA::False;
				m_bCapture = GAIA::False;
				m_bModal = GAIA::False;
				m_bShow = GAIA::False;
				m_bScissor = GAIA::True;
			}

		private:
			__MyType::Desc m_desc;
			__PosType m_pos;
			__SizeType m_size;
			__RotateType m_rotate;
			__ChildListType m_childs;
			__MyType* m_parent;

			__ColorType m_cr;

			GAIA::U8 m_bEnableCallBackMsg : 1;
			GAIA::U8 m_bActive : 1;
			GAIA::U8 m_bFocus : 1;
			GAIA::U8 m_bFocusAble : 1;
			GAIA::U8 m_bCapture : 1;
			GAIA::U8 m_bModal : 1;
			GAIA::U8 m_bShow : 1;
			GAIA::U8 m_bScissor : 1;
		};
	};
};

#endif