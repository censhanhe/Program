#ifndef		__GAIA_RENDER_IMAGEWORK_H__
#define		__GAIA_RENDER_IMAGEWORK_H__

namespace GAIA
{
	namespace RENDER
	{
		class ImageWork : public virtual GAIA::FWORK::Instance
		{
		public:
			typedef GAIA::CTN::Accesser<GAIA::U8, GAIA::SIZE, GAIA::ALGO::TwiceSizeIncreaser<GAIA::SIZE> > __AccesserType;

		public:
			class Layer : public virtual GAIA::FWORK::Instance
			{
			public:
				class Filter : public virtual GAIA::FWORK::Instance
				{
				public:
				};
				class BlurFilter : public virtual Filter
				{
				public:
				};
				class GrayFilter : public virtual Filter
				{
				public:
				};
				class InnerShadowFilter : public virtual Filter
				{
				public:
				};
				class OutterShadowFilter : public virtual Filter
				{
				public:
				};
				class CameoFilter : public virtual Filter
				{
				public:
				};
				class AntiAliasFilter : public virtual Filter
				{
				public:
				};

			public:
				typedef GAIA::CTN::Vector<Layer*> __LayerList;
				typedef GAIA::CTN::Vector<Filter*> __FilterList;

			public:
				GAIA_ENUM_BEGIN(MIX_METHOD)
					MIX_METHOD_REPLACE,
					MIX_METHOD_LINEAR,
					MIX_METHOD_ADD,
					MIX_METHOD_SUB,
					MIX_METHOD_MUL,
					MIX_METHOD_DIV,
					MIX_METHOD_INV,
					MIX_METHOD_MASK,
				GAIA_ENUM_END(MIX_METHOD)

			public:
				GINL GAIA::GVOID SetName(const GAIA::TCH* pszName);
				GINL const GAIA::TCH* GetName() const;

				GINL GAIA::BL SetParent(Layer* pLayer);
				GINL Layer* GetParent() const;
				GINL GAIA::SIZE CollectChild(__LayerList& res);

				GINL Filter* CreateFilter();
				GINL GAIA::BL DeleteFilter(Filter* pFilter);
				GINL GAIA::BL DeleteFilterAll();
				GINL GAIA::SIZE CollectFilter(__FilterList& res);

				GINL GAIA::BL InsertFilterToQueue(const GAIA::SIZE& index, Filter* pFilter);
				GINL GAIA::BL RemoveFilterFromQueue(const GAIA::SIZE& index);
				GINL GAIA::BL RemoveFilterFromQueueAll();

				GINL GAIA::GVOID SetOpacity(const GAIA::REAL& r);
				GINL GAIA::REAL GetOpacity() const;
				GINL GAIA::GVOID SetMixMethod(MIX_METHOD mm);
				GINL MIX_METHOD GetMixMethod() const;
			};
			class BitmapLayer : public virtual Layer
			{
			public:
			};
			class ParametricLayer : public virtual Layer
			{
			public:
			};

		public:
			typedef GAIA::CTN::Vector<Layer*> __LayerList;

		public:
			GINL ImageWork(){}
			GINL ~ImageWork(){}
			
			GINL GAIA::BL Load(__AccesserType& acc);
			GINL GAIA::BL Save(__AccesserType& acc);
			GINL GAIA::BL LoadLayer(__AccesserType& acc, Layer* pLayer);
			GINL GAIA::BL SaveLayer(__AccesserType& acc, Layer* pLayer);

			GINL Layer* CreateLayer() const;
			GINL GAIA::BL DeleteLayer(Layer* pLayer);
			GINL GAIA::BL DeleteLayerAll();
			GINL GAIA::SIZE CollectLayer(__LayerList& res);

		private:
		};
	};
};

#endif