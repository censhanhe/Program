#ifndef		__GAIA_MVC_VIEWLINKER_H__
#define		__GAIA_MVC_VIEWLINKER_H__

namespace GAIA
{
	namespace MVC
	{
		class View;
		class ViewLinker : public virtual GAIA::FWORK::Instance
		{
			friend class GAIA::MVC::View;
		private:
			class ViewNode
			{
			public:
				GAIA::MVC::View* pView;
			};
			typedef GAIA::CTN::Vector<ViewNode> __ViewList;
		public:
			GINL ViewLinker(){}
			GINL ~ViewLinker(){}
		private:
			GINL GAIA::BL LinkView(GAIA::MVC::View& view)
			{
				__ViewList::it it = m_views.front_it();
				for(; !it.empty(); ++it)
				{
					ViewNode& n = *it;
					if(n.pView == &view)
						return GAIA::False;
				}
				it = m_views.front_it();
				for(; !it.empty(); ++it)
				{
					ViewNode& n = *it;
					if(n.pView == GNIL)
					{
						n.pView = &view;
						return GAIA::True;
					}
				}
				ViewNode n;
				n.pView = &view;
				m_views.push_back(n);
				return GAIA::True;
			}
			GINL GAIA::BL UnlinkView(GAIA::MVC::View& view)
			{
				__ViewList::it it = m_views.front_it();
				for(; !it.empty(); ++it)
				{
					ViewNode& n = *it;
					if(n.pView == &view)
					{
						n.pView = GNIL;
						return GAIA::True;
					}
				}
				return GAIA::False;
			}
			GINL GAIA::BL IsLinkedView(GAIA::MVC::View& view) const
			{
				__ViewList::const_it it = m_views.const_front_it();
				for(; !it.empty(); ++it)
				{
					const ViewNode& n = *it;
					if(n.pView == &view)
						return GAIA::True;
				}
				return GAIA::False;
			}
			GINL GAIA::BL CollectLinkedViews(GAIA::CTN::Vector<GAIA::MVC::View*>& listResult);
		private:
			__ViewList m_views;
		};
	};
};

#endif