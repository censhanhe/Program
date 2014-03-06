#ifndef		__GAIA_RENDER_PIPELINE_H__
#define		__GAIA_RENDER_PIPELINE_H__

namespace GAIA
{
	namespace RENDER
	{
		class PipelineStageDesc
		{
		public:
		};

		class Pipeline
		{
		public:
			GINL Pipeline();
			GINL ~Pipeline();

			GINL GAIA::GVOID InsertStage(GAIA::U32 uIndex, const PipelineStageDesc& desc);
			GINL GAIA::GVOID DeleteStage();
			GINL GAIA::GVOID CollectStage();
			GINL GAIA::GVOID EnableStage();
			GINL GAIA::GVOID IsEnableStage() const;

			GINL GAIA::GVOID Execute();

			GINL GAIA::GVOID SetCamera(GAIA::SCENE::Camera* pCamera);
			GINL GAIA::SCENE::Camera* GetCamera() const;

			GINL GAIA::BL LinkPipeline(Pipeline* pPL);
			GINL GAIA::BL UnlinkPipeline(Pipeline* pPL);
			GINL GAIA::BL CollectPipeline();
		};
	};
};

#endif