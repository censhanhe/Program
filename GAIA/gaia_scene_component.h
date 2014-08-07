#ifndef		__GAIA_SCENE_COMPONENT_H__
#define		__GAIA_SCENE_COMPONENT_H__

namespace GAIA
{
	namespace COMPONENT
	{
		class Component : public virtual GAIA::FRAMEWORK::Instance
		{
		public:
			GINL Component();
			GINL ~Component();
			GINL virtual GAIA::BL Attach(Component* pComponent);
			GINL virtual GAIA::BL Dettach(Component* pComponent);
		};
	};
};

#endif
