#ifndef		__GAIA_RENDER_RENDER_H__
#define		__GAIA_RENDER_RENDER_H__

namespace GAIA
{
	namespace RENDER
	{
		GAIA_ENUM_BEGIN(RENDER_STATEWORD)
			RENDER_STATEWORD_NONE,
			RENDER_STATEWORD_ON,
			RENDER_STATEWORD_OFF,
			RENDER_STATEWORD_LOWEST,
			RENDER_STATEWORD_LOWER,
			RENDER_STATEWORD_LOW,
			RENDER_STATEWORD_MID,
			RENDER_STATEWORD_HIGH,
			RENDER_STATEWORD_HIGHER,
			RENDER_STATEWORD_HIGHEST,
		GAIA_ENUM_END(RENDER_STATEWORD)
		static const GAIA::CH* RENDER_STATEWORD_STRING[] = 
		{
			"invalid",	// RENDER_STATEWORD_INVALID,
			"none",		// RENDER_STATEWORD_NONE
			"on",		// RENDER_STATEWORD_ON
			"off",		// RENDER_STATEWORD_OFF
			"lowest",	// RENDER_STATEWORD_LOWEST
			"lower",	// RENDER_STATEWORD_LOWER
			"low",		// RENDER_STATEWORD_LOW
			"mid",		// RENDER_STATEWORD_MID
			"high",		// RENDER_STATEWORD_HIGH
			"higher",	// RENDER_STATEWORD_HIGHER
			"highest",	// RENDER_STATEWORD_HIGHEST
		};

		class Render : public virtual GAIA::FWORK::Instance
		{
		public:
			typedef GAIA::RENDER::Render __MyType;

		public:
			class RenderDesc : public virtual GAIA::FWORK::InstanceDesc
			{
			public:
				virtual GAIA::GVOID reset(){pCanvas = GNIL;}
				virtual GAIA::BL check() const
				{
					if(pCanvas == GNIL)
						return GAIA::False;
					if(!pCanvas->IsCreated())
						return GAIA::False;
					return GAIA::True;
				}
			public:
				GAIA::UI::Canvas* pCanvas;
			};

			class Context : public virtual GAIA::RENDER::RenderResource
			{
			public:
				class ContextDesc : public virtual GAIA::FWORK::InstanceDesc
				{
				public:
					virtual GAIA::GVOID reset(){}
					virtual GAIA::BL check() const{return GAIA::True;}
				};
			public:
				virtual GAIA::BL Create(const GAIA::RENDER::Render::Context::ContextDesc& desc) = 0;
				virtual GAIA::GVOID Destroy() = 0;
				virtual const ContextDesc& GetDesc() const = 0;
			};

			class ImageFormatDesc : public virtual GAIA::FWORK::InstanceDesc
			{
			public:
				GAIA_ENUM_BEGIN(CHANNEL_DATATYPE)
					CHANNEL_DATATYPE_INTEGER,
					CHANNEL_DATATYPE_FLOAT32,
					CHANNEL_DATATYPE_FLOAT64,
				GAIA_ENUM_END(CHANNEL_DATATYPE)
				GAIA_ENUM_BEGIN(CHANNEL_FUNCTION)
					CHANNEL_FUNCTION_COLOR,
					CHANNEL_FUNCTION_DATA,
				GAIA_ENUM_END(CHANNEL_FUNCTION)
				GAIA_ENUM_BEGIN(COMPRESS_TYPE)
					COMPRESS_TYPE_NONE,
					COMPRESS_TYPE_INDEXED,
					COMPRESS_TYPE_DXT1_NOALPHA,
					COMPRESS_TYPE_DXT1,
					COMPRESS_TYPE_DXT3,
					COMPRESS_TYPE_DXT5,
				GAIA_ENUM_END(COMPRESS_TYPE)
			public:
				virtual GAIA::GVOID reset()
				{
					channeldatatype = CHANNEL_DATATYPE_INTEGER;
					channelfunction = CHANNEL_FUNCTION_COLOR;
					compresstype = COMPRESS_TYPE_NONE;
					uChannelCount = 4;
					uBPC[0] = uBPC[1] = uBPC[2] = uBPC[3] = 8;
				}
				virtual GAIA::BL check() const
				{
					if(!GAIA_ENUM_VALID(CHANNEL_DATATYPE, channeldatatype))
						return GAIA::False;
					if(!GAIA_ENUM_VALID(CHANNEL_FUNCTION, channelfunction))
						return GAIA::False;
					if(!GAIA_ENUM_VALID(COMPRESS_TYPE, compresstype))
						return GAIA::False;
					if(uChannelCount == 0)
						return GAIA::False;
					for(GAIA::SIZE x = 0; x < sizeofarray(uBPC); ++x)
					{
						if(uBPC[x] == 0 || uBPC[x] > 32)
							return GAIA::False;
					}
					return GAIA::True;
				}
			public:
				CHANNEL_DATATYPE channeldatatype;
				CHANNEL_FUNCTION channelfunction;
				COMPRESS_TYPE compresstype;
				GAIA::U8 uBPC[4]; // Bit count per channel. 0 is alpha 1 is red, 2 is green, 3 is blue.
				GAIA::U8 uChannelCount;
			};

		public:
			virtual GAIA::BL Create(const GAIA::RENDER::Render::RenderDesc& desc) = 0;
			virtual GAIA::BL Destroy() = 0;
			virtual GAIA::BL IsCreated() const = 0;
			virtual const GAIA::RENDER::Render::RenderDesc& GetDesc() const = 0;

			virtual GAIA::RENDER::Render::Context* CreateContext(const GAIA::RENDER::Render::Context::ContextDesc& desc) = 0;

			virtual GAIA::BL BeginStatePipeline() = 0;
			virtual GAIA::BL EndStatePipeline() = 0;
			virtual GAIA::BL IsBeginStatePipeline() const = 0;

			virtual GAIA::GVOID Flush(GAIA::BL bWait) = 0;
		};
	};
};

#endif
