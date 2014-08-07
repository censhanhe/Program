#ifndef		__GAIA_MVC_VIEWLINKER_IMPL_H__
#define		__GAIA_MVC_VIEWLINKER_IMPL_H__

namespace GAIA
{
	namespace MVC
	{
		GINL GAIA::BL ViewLinker::CollectLinkedViews(GAIA::CONTAINER::Vector<GAIA::MVC::View*>& listResult)
		{
			GAIA::BL bRet = GAIA::False;
			__ViewList::it it = m_views.front_it();
			while(!it.empty())
			{
				ViewNode& n = *it;
				if(n.pView != GNULL)
				{
					n.pView->Reference();
					listResult.push_back(n.pView);
					bRet = GAIA::True;
				}
				++it;
			}
			return bRet;
		}
	};
};

#endif