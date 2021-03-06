#ifndef		__GAIA_LAYOUT_H__
#define		__GAIA_LAYOUT_H__

namespace GAIA
{
	namespace LAYOUT
	{
		class Layout : public virtual GAIA::FWORK::Instance
		{
		private:
			class WidgetNode
			{
			public:
				GAIA::LAYOUT::Widget* pWidget;
			};
			typedef GAIA::CTN::Vector<WidgetNode> __WidgetType;
		public:
			GINL Layout(){this->init();}
			GINL ~Layout(){this->RemoveWidgetAll();}
			GINL GAIA::BL AddWidget(GAIA::LAYOUT::Widget& lw)
			{
				if(this->IsWidgetExist(lw))
					return GAIA::False;
				lw.Reference();
				__WidgetType::it it = m_widgets.front_it();
				for(; !it.empty(); ++it)
				{
					WidgetNode& n = *it;
					if(n.pWidget == GNIL)
					{
						n.pWidget = &lw;
						return GAIA::True;
					}
				}
				WidgetNode n;
				n.pWidget = &lw;
				m_widgets.push_back(n);
				return GAIA::True;
			}
			GINL GAIA::BL RemoveWidget(GAIA::LAYOUT::Widget& lw)
			{
				__WidgetType::it it = m_widgets.front_it();
				for(; !it.empty(); ++it)
				{
					WidgetNode& n = *it;
					if(n.pWidget == &lw)
					{
						n.pWidget->Release();
						n.pWidget = GNIL;
						return GAIA::True;
					}
				}
				return GAIA::False;
			}
			GINL GAIA::BL IsWidgetExist(GAIA::LAYOUT::Widget& lw) const
			{
				__WidgetType::const_it it = m_widgets.const_front_it();
				for(; !it.empty(); ++it)
				{
					const WidgetNode& n = *it;
					if(n.pWidget == &lw)
						return GAIA::True;
				}
				return GAIA::False;
			}
			GINL GAIA::BL RemoveWidgetAll()
			{
				GAIA::BL bRet = GAIA::False;
				__WidgetType::it it = m_widgets.front_it();
				for(; !it.empty(); ++it)
				{
					WidgetNode& n = *it;
					if(n.pWidget != GNIL)
					{
						n.pWidget->Release();
						n.pWidget = GNIL;
						bRet = GAIA::True;
					}
				}
				m_widgets.destroy();
				return bRet;
			}
			GINL GAIA::BL CollectWidget(GAIA::CTN::Vector<GAIA::LAYOUT::Widget*>& listResult) const
			{
				GAIA::BL bRet = GAIA::False;
				__WidgetType::const_it it = m_widgets.const_front_it();
				for(; !it.empty(); ++it)
				{
					const WidgetNode& n = *it;
					if(n.pWidget != GNIL)
					{
						n.pWidget->Reference();
						listResult.push_back(n.pWidget);
						bRet = GAIA::True;
					}
				}
				return bRet;
			}
		public:
			virtual GAIA::BL UpdateLayout() = 0; // If there are some widget been reposition or resize, return GAIA::True, or will return GAIA::False.
		private:
			GINL GAIA::GVOID init(){}
		private:
			__WidgetType m_widgets;
		};
	};
};

#endif