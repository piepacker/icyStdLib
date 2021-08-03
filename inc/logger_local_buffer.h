#pragma once

#include <string>

#if !PLATFORM_MSW
#	define vsprintf_s vsnprintf
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
// logger_local_buffer
//
// Mission critical logging facility. Avoids heap alloc for the common-case short string printout.
// Falls back on heap alloc for large buffers. Effectively a lightweight temporary-scope string
// builder with a few logger-specific functions.
//
// This class could be generalized further into a string builder, I suppose, but it's lightweight
// enough and it might be handy to specialize the behavior for logging purposes without fear of
// mucking up other non-logging string building operations. This is the rationale behind giving it
// a logger namespace.
//
struct logger_local_buffer
{
	static const int  bufsize = 1536;

	char			buffer[bufsize + 2];				// always leave room for newline and /0
	int				wpos	= 0;
	std::string*	longbuf = nullptr;					// used only if buffer[] exceeded.

	logger_local_buffer() {
		buffer[0] = 0;
	}

	void clear    ();
	void append	  (const char* msg);
	void appendfv (const char* fmt, va_list args);
	void formatv  (const char* fmt, va_list args);
	void appendf  (const char* fmt, ...);
	void format   (const char* fmt, ...);
	void append   (char c);

	void write_to (FILE* fp) const;

	~logger_local_buffer() {
		delete longbuf;
	}
};
