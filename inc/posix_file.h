#pragma once

// Lightweight macro-based POSIX cross-compilation header

#include "fi-platform-defines.h"


#if PLATFORM_PS4    // Sony Playstation
#	include "sce/posix_file_ps4.h"
#endif

#include <cstdint>

// off_t is too poorly defined to be of use. Let's define our own based on intmax_t.
using x_off_t = intmax_t;

#if PLATFORM_MSW
#	include <fcntl.h>
#	include <io.h>
#   include <cstdio>
#   include <sys/stat.h>

    // windows POSIX libs are lacking the fancy new pread() function. >_<
    extern size_t _pread(int fd, void* dest, size_t count, x_off_t pos);

    // Windows has this asinine non-standard notion of text mode POSIX files and, worse, makes the
    // non-standard behavior the DEFAULT behavior.  What the bloody hell, Microsoft?  Your're drunk.
    // Go Home.  --jstine

#	define posix_open(fn,flags,mode)   _open(fn,(flags) | _O_BINARY, mode)
#	define posix_read   _read
#	define posix_pread  _pread
#	define posix_write  _write
#	define posix_close  _close
#	define posix_lseek  _lseeki64
#	define posix_unlink _unlink
#	define O_DIRECT		(0)		// does not exist on windows
#	define DEFFILEMODE  (_S_IREAD | _S_IWRITE)

#elif PLATFORM_POSIX

#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <cerrno>
#include <cstring>

#	define posix_open   open
#	define posix_read   read
#	define posix_pread  pread
#	define posix_write  write
#	define posix_close  close
#	define posix_lseek  lseek
#	define posix_unlink unlink

#else

#	error Unsupported platform.

#endif

// Lightweight helper class for POSIX stat, just to put things in a little more friendly container.
struct CStatInfo
{
	uint32_t    st_mode;
	intmax_t    st_size;

	time_t      time_accessed;
	time_t      time_modified;
	time_t      time_created;

	bool IsFile     () const;
	bool IsDir      () const;
	bool Exists     () const;

	bool operator==(const CStatInfo& r) const {
		return (
			(st_mode		== r.st_mode			) &&
			(st_size		== r.st_size			) &&
			(time_accessed	== r.time_accessed		) &&
			(time_modified	== r.time_modified		) &&
			(time_created	== r.time_created		)
		);
	}

	bool operator!=(const CStatInfo& r) const {
		return !this->operator==(r);
	}
};


extern int				posix_link		(const char* existing_file, const char* link);
extern CStatInfo		posix_fstat		(int fd);
extern CStatInfo		posix_stat		(const char* fullpath);
