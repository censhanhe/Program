#ifndef		__GAIA_RENDER_SHADER_H__
#define		__GAIA_RENDER_SHADER_H__

namespace GAIA
{
	namespace RENDER
	{
		class Shader : public virtual GAIA::RENDER::Resource
		{
		public:
			class ShaderDesc : public GAIA::Base
			{
			public:
			};
		public:
			const ShaderDesc& GetDesc() const{return m_desc;}
		private:
			ShaderDesc m_desc;
		};
	};
};

#endif