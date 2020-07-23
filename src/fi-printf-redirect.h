#pragma once

#if !defined(REDEFINE_PRINTF)
#	if defined(_MSC_VER)
#		define REDEFINE_PRINTF		1
#	endif
#endif

#if !defined(__verify_fmt)
#	if defined(_MSC_VER)
#		define __verify_fmt(fmtpos, vapos)
#	else
#		define __verify_fmt(fmtpos, vapos)  __attribute__ ((format (printf, fmtpos, vapos)))
#	endif
#endif

// On Windows it's handy to have printf() automatically redirect itself into the Visual Studio Output window
// and the only sane way to accomplish that seems to be by replacing printf() with a macro.
#if REDEFINE_PRINTF
#include <stdio.h>		// must include before macro definition
#if defined(__cplusplus)
#	define _extern_c		extern "C"
#else
#	define _extern_c
#endif
_extern_c int _fi_redirect_printf   (const char* fmt, ...);
_extern_c int _fi_redirect_vfprintf (FILE* handle, const char* fmt, va_list args);
_extern_c int _fi_redirect_fprintf  (FILE* handle, const char* fmt, ...);
_extern_c int _fi_redirect_puts     (char const* _Buffer);
_extern_c int _fi_redirect_fputs    (char const* _Buffer, FILE* _Stream);

#define printf(fmt, ...)		_fi_redirect_printf  (fmt, ## __VA_ARGS__)
#define fprintf(fp, fmt, ...)	_fi_redirect_fprintf (fp, fmt, ## __VA_ARGS__)
#define vfprintf(fp, fmt, args)	_fi_redirect_vfprintf(fp, fmt, args)
#define puts(msg)				_fi_redirect_puts    (msg);
#define fputs(msg, fp)			_fi_redirect_fputs   (msg, fp);
#undef _extern_c
#endif