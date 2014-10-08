#ifndef		__GAIA_TASK_TASK_H__
#define		__GAIA_TASK_TASK_H__

namespace GAIA
{
	namespace TASK
	{
		class Task
		{
		public:
			GINL Task();
			GINL ~Task();

			virtual GAIA::BL Update();
		};
	};
};

#endif
