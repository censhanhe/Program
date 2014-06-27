#ifndef		__GAIA_ALLOCATOR_H__
#define		__GAIA_ALLOCATOR_H__

namespace GAIA
{
	namespace ALLOCATOR
	{
#if GAIA_OS == GAIA_OS_WINDOWS
#	if GAIA_PROFILE == GAIA_PROFILE_DEBUG
		inline GAIA::N32 crt_alloc_hook(
			GAIA::N32 nAllocType,
			GAIA::GVOID* pUserData,
#		if GAIA_MACHINE == GAIA_MACHINE32
			GAIA::U32 size,
#		elif GAIA_MACHINE == GAIA_MACHINE64
			GAIA::U64 size,
#		endif
			GAIA::N32 nBlockType,
			GAIA::NM nRequestNum,
			const GAIA::U8* pszFileName,
			GAIA::N32 nCodeLine)
		{
			static GAIA::U64 s_uAllocCount = 0;
			static GAIA::U64 s_uReallocCount = 0;
			static GAIA::U64 s_uFreeCount = 0;
			if(nAllocType == _HOOK_ALLOC)
				++s_uAllocCount;
			else if(nAllocType == _HOOK_REALLOC)
				++s_uReallocCount;
			else if(nAllocType == _HOOK_FREE)
				++s_uFreeCount;
			return GAIA::True;
		}
#	endif
#endif

		class Allocator : public RefObject
		{
		public:
			GINL Allocator()
			{
#if GAIA_OS == GAIA_OS_WINDOWS
#	if GAIA_PROFILE == GAIA_PROFILE_DEBUG
				_CrtSetAllocHook(crt_alloc_hook);
#	endif
#endif
			}
			virtual GAIA::GVOID* memory_alloc(const GAIA::UM& size) = 0;
			virtual GAIA::GVOID memory_release(GAIA::GVOID* p) = 0;
			virtual GAIA::UM memory_size(GAIA::GVOID* p) = 0;
			virtual GAIA::UM capacity() = 0;
			virtual GAIA::UM size() = 0;
			virtual GAIA::UM use_size() = 0;
			virtual GAIA::UM piece_size() = 0;
			virtual GAIA::U64 alloc_times() = 0;
		private:
		};
	};
};

#endif
