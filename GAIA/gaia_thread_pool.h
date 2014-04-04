#ifndef 	__GAIA_THREAD_POOL_H__
#define 	__GAIA_THREAD_POOL_H__

namespace GAIA
{
	namespace THREAD
	{
		class ThreadPoolTask
		{
		public:
			GINL ThreadPoolTask(){}
			GINL ~ThreadPoolTask(){}
			GINL GAIA::GVOID SetPriority();
			GINL GAIA::GVOID GetPriority();
			virtual GAIA::BL WorkProcedule() = 0; // If return GAIA::True, the task is complete and remove from task queue.
		private:
		};
		class ThreadPool
		{
		public:
			GINL ThreadPool(){}
			GINL ~ThreadPool(){}
			GINL GAIA::GVOID SetThreadCount(const GAIA::U32& size);
			GINL const GAIA::U32& GetThreadCount() const;
			GINL GAIA::GVOID Begin();
			GINL GAIA::GVOID End();
			GINL GAIA::BL IsBegin() const;
			GINL GAIA::BL AddTask(ThreadPoolTask& t);
			GINL GAIA::BL RemoveTask(ThreadPoolTask& t);
			GINL GAIA::BL IsTaskExist(ThreadPoolTask& t) const;
		private:
		};
	};
};

#endif
