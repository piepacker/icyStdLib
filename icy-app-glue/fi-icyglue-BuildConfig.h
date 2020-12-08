#pragma once

// Default BuildConfig Template for Icy Libraries and Apps.



#if PLATFORM_MSW
#   if !defined(_SECURE_SCL_THROWS)
#	    define _SECURE_SCL_THROWS        0
#	endif
#   if !defined(_HAS_EXCEPTIONS)
#	    define _HAS_EXCEPTIONS           0
#	endif
#   if !defined(_ITERATOR_DEBUG_LEVEL)
#	    define _ITERATOR_DEBUG_LEVEL     0
#	endif
#	if !defined(_CRT_SECURE_NO_WARNINGS)
#		define _CRT_SECURE_NO_WARNINGS	 1
#	endif
#endif


// Enable printf redirection to Microsoft OS debugger (via OutputDebugString)
#include "fi-printf-redirect.h"
