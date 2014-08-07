#ifndef		__GAIA_MVC_VIEWLINKER_H__
#define		__GAIA_MVC_VIEWLINKER_H__

namespace GAIA
{
	namespace MVC
	{
		class View;
		class ViewLinker : public GAIA::FRAMEWORK::Instance
		{
			friend class GAIA::MVC::View;
		private:
			class ViewNode
			{
			public:
				GAIA::MVC::View* pView;
			};
			typedef GAIA::CONTAINER::Vector<ViewNode> __ViewList;
		public:
			GINL ViewLinker(){}
			GINL ~ViewLinker(){}
		private:
			GINL GAIA::BL LinkView(GAIA::MVC::View& view)
			{
				__ViewList::it it = m_views.front_it();
				while(!it.empty())
				{
					ViewNode& n = *it;
					if(n.pView == &view)
						return GAIA::False;
					++it;
				}
				it = m_views.front_it();
				while(!it.empty())
				{
					ViewNode& n = *it;
					if(n.pView == GNULL)
					{
						n.pView = &view;
						return GAIA::True;
					}
					++it;
				}
				ViewNode n;
				n.pView = &view;
				m_views.push_back(n);
				return GAIA::True;
			}
			GINL GAIA::BL UnlinkView(GAIA::MVC::View& view)
			{
				__ViewList::it it = m_views.front_it();
				while(!it.empty())
				{
					ViewNode& n = *it;
					if(n.pView == &view)
					{
						n.pView = GNULL;
						return GAIA::True;
					}
					++it;
				}
				return GAIA::False;
			}
			GINL GAIA::BL IsLinkedView(GAIA::MVC::View& view) const
			{
				__ViewList::const_it it = m_views.const_front_it();
				while(!it.empty())
				{
					const ViewNode& n = *it;
					if(n.pView == &view)
						return GAIA::True;
				}
				return GAIA::False;
			}
			GINL GAIA::BL CollectLinkedViews(GAIA::CONTAINER::Vector<GAIA::MVC::View*>& listResult);
		private:
			__ViewList m_views;
		};
	};
};

#endif