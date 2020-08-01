#pragma once

#if defined(_MSC_VER) && !defined(PLATFORM_MSW)
#   define PLATFORM_MSW    1
#endif

#if defined(_MSC_VER)
#	pragma warning(disable:4100)	// unreferenced formal parameter
#	pragma warning(disable:4127)	// conditional expression is constant
#	pragma warning(disable:4200)	// nonstandard extension used : zero-sized array in struct/union
#	pragma warning(disable:4201)	// nonstandard extension used : nameless struct/union
#	pragma warning(disable:4238)	// nonstandard extension used : class rvalue used as lvalue
#	pragma warning(disable:4239)	// nonstandard extension used : conversion from T to T&
#	pragma warning(disable:4505)	// unreferenced local function has been removed
#	pragma warning(disable:4514)	// unreferenced inline function has been removed
#	pragma warning(disable:4702)	// unreachable code
#	pragma warning(disable:4786)	// identifier was truncated to '255' characters in debug info
#	pragma warning(disable:4100)	// unreferenced formal parameter
#	pragma warning(disable:4512)	// assignment operator could not be generated
#	pragma warning(disable:4390)	// empty controlled statement found
#	pragma warning(disable:4267)	// conversion from 'unsigned' to 'signed', possible loss of data  (too many false positives to be useful, leads to lots of ill-advised casts to avoid them which mask more serious errors --jstine)
#	pragma warning(disable:4244)	// conversion from 'int' to 'float', possible loss of data  (it's not even consistent, issues this waring for vars but not integer literal assignments! --jstine)
#	pragma warning(disable:4305)	// 'argument': truncation from 'double' to 'float'
#elif __clang__
//format of clang pragmas to disable warnings is #pragma GCC diagnostic ignored "-Wall"
#	pragma GCC diagnostic ignored "-Wunused-private-field"
#	pragma GCC diagnostic ignored "-Woverloaded-virtual"
#	pragma GCC diagnostic ignored "-Wreorder"
#	pragma GCC diagnostic ignored "-Wunused-variable"
#	pragma GCC diagnostic ignored "-Wchar-subscripts"
#	pragma GCC diagnostic ignored "-Wvarargs"
#	pragma GCC diagnostic ignored "-Wunused-function"
#	pragma GCC diagnostic ignored "-Wself-assign"
#	pragma GCC diagnostic ignored "-Wunused-value"
// we don't want to do this globally because it finds good things.
//#pragma GCC diagnostic ignored "-Wtautological-undefined-compare"
#endif
