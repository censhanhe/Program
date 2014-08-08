#ifndef		__GAIA_RENDER_TARGET_H__
#define		__GAIA_RENDER_TARGET_H__

namespace GAIA
{
	namespace RENDER
	{
		class Target : public virtual GAIA::RENDER::Resource
		{
		public:
			class TargetDesc : public GAIA::Base
			{
			public:
			};
		public:
			const TargetDesc& GetDesc() const{return m_desc;}
		private:
			TargetDesc m_desc;
		};
	};
};

#endif
