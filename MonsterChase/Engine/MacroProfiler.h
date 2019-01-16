#pragma once
#include"Accumulator.h"
#define ENABLE_PROFILING

#define CONCAT_HELPER(left, right) left##right
#define CONCAT(left, right) CONCAT_HELPER(left, right)

#if defined( ENABLE_PROFILING )

#define PROFILE_UNSCOPED(name) static Accumulator CONCAT(__Accumulator,__LINE__)(name); ScopedTimer CONCAT(__Timer,__LINE__)(CONCAT(__Accumulator,__LINE__));

#define PROFILE_SCOPE_BEGIN(name)   { static Accumulator CONCAT(__Accumulator,__LINE__)(name); ScopedTimer CONCAT(__Timer,__LINE__)(CONCAT(__Accumulator,__LINE__));

#define PROFILE_SCOPE_END()	   }

#else // ENABLE_PROFILING not defined

#define PROFILE_SCOPE_BEGIN(str)		__noop
#define PROFILE_SCOPE_END		__noop
#define PROFILE_UNSCOPED(str)		__noop

#endif