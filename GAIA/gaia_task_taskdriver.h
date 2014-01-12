#ifndef		__GAIA_TASK_TASKDRIVER_H__
#define		__GAIA_TASK_TASKDRIVER_H__

namespace GAIA
{
	namespace TASK
	{
		class TaskDriver
		{
		public:
			GINL TaskDriver();
			GINL ~TaskDriver();

			GINL GAIA::BL InsertTask();
		};
	};
};

#endif