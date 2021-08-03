#pragma once

#include <cstring>
#include <string>
#include <vector>
#include <tuple>

#if !PLATFORM_MSW
#	define vsprintf_s vsnprintf
#endif

#if !defined(__verify_fmt)
#   if defined(_MSC_VER)
#   	define __verify_fmt(fmtpos, vapos)
#   else
#   	define __verify_fmt(fmtpos, vapos)  __attribute__ ((format (printf, fmtpos, vapos)))
#   endif
#endif

#if PLATFORM_MSCRT
#   if !defined(strcasecmp) 
#   	define strcasecmp(a,b)		_stricmp(a,b)
#   endif
#   if !defined(strcasestr)
#   	define strcasestr(a,b)		_stristr(a,b)
       extern char *_stristr(const char *haystack, const char *needle);
#   endif
#   if !defined(strncasecmp)
#   	define strncasecmp(a,b,c)	_strnicmp(a,b,c)
#   endif
#endif

#if !defined(HAS_strcasestr)
#   define HAS_strcasestr   1
#endif

#if !HAS_strcasestr
/*
 * Find the first occurrence of find in s, ignore case.
 */
inline const char *strcasestr(const char *s, const char *find) {
	char c, sc;
	size_t len;

	if ((c = *find++) != 0) {
		c = (char)tolower((unsigned char)c);
		len = strlen(find);
		do {
			do {
				if ((sc = *s++) == 0)
					return (NULL);
			} while ((char)tolower((unsigned char)sc) != c);
		} while (strncasecmp(s, find, len) != 0);
		s--;
	}
	return ((char *)s);
}
#endif

// Neat!  Returns the case option as a string matching precisely the case label. Useful for logging
// hardware registers and for converting sparse enumerations into strings (enums where simple char*
// arrays fail).
#define CaseReturnString(caseName)        case caseName: return # caseName

// filename illegals, for use with ReplaceCharSet, to replace with underscore (_)
static const char msw_fname_illegalChars[] = "\\/:?\"<>|";

///////////////////////////////////////////////////////////////////////////////////////////////////
// StringConversionMagick - struct meant for use as an aide in function parameter passing only.
//
// Rationale:
//   C++ has a rule that we can't use references as the fmt parameter to a varadic function,
//   which prevents us from making a nice API that can accept std::string or const char* implicitly.
//   In the past I've worked around this by making my own wrapper class for std::string that has
//   an implicit conversion operator for const char*(), but that's a pretty heavyweight approach that
//   makes it really hard for libraries to inter-operate with other libs that expect plain old
//   std::string.  So now I'm going with this, let's see what happens!  --jstine
//
struct StringConversionMagick
{
	const char*			m_cstr   = nullptr;
	const std::string*	m_stdstr = nullptr;
	int                 m_length = -1;

	StringConversionMagick(const std::string& str) {
		m_stdstr = &str;
	}

	StringConversionMagick(const char* const (&str)) {
		m_cstr   = str;
	}

	template<int size>
	StringConversionMagick(const char (&str)[size]) {
		m_cstr   = str;
		m_length = size-1;
	}

	const char* c_str() const {
		return m_stdstr ? m_stdstr->c_str() : m_cstr;
	}

	bool empty() const {
		if (m_stdstr) {
			return m_stdstr->empty();
		}
		return !m_cstr || !m_cstr[0];
	}

	auto length() const {
		if (m_stdstr) return m_stdstr->length();
		return (m_length < 0) ? strlen(m_cstr) : m_length;
	}
};

namespace StringUtil {

	inline bool BeginsWith(const std::string& left, char right) {
		return !left.empty() && (left[0] == right);
	}

	inline bool BeginsWith(const std::string& left, const std::string& right) {
		return left.compare( 0, right.length(), right) == 0;
	}

	inline bool EndsWith(const std::string& left, const std::string& right) {
		intmax_t startpos = left.length() - right.length();
		if (startpos<0) return false;
		return left.compare( startpos, right.length(), right ) == 0;
	}

	inline bool EndsWith(const std::string& left, char right) {
		return !left.empty() && (left[left.length()-1] == right);
	}

	extern void				AppendFmtV	(std::string& result, const StringConversionMagick& fmt, va_list list);
	extern std::string		FormatV		(const StringConversionMagick& fmt, va_list list);

	extern void				AppendFmt	(std::string& result, const char* fmt, ...)		__verify_fmt(2,3);
	extern std::string		Format		(const char* fmt, ...)							__verify_fmt(1,2);
	extern std::string  	trim		(const std::string& s, const char* delims = " \t\r\n");
	extern std::string  	toLower		(std::string s);
	extern std::string  	toUpper		(std::string s);
	extern std::string  	ReplaceCharSet(std::string srccopy, const char* to_replace, char new_ch);

	extern bool getBoolean(const StringConversionMagick& left, bool* parse_error=nullptr);
	inline std::tuple<bool, bool> getBoolean(const StringConversionMagick& left, bool defbool) {
		bool error;
		auto result = getBoolean(left, &error);
		return { error ? defbool : result, error };
	}


	inline std::string	ReplaceString(std::string subject, const std::string& search, const std::string& replace) {
		size_t pos = 0;
		while ((pos = subject.find(search, pos)) != std::string::npos) {
			subject.replace(pos, search.length(), replace);
			pos += replace.length();
		}
		return subject;
	}

	inline std::string	ReplaceCase(std::string subject, const std::string& search, const std::string& replace) {
		const char* pos = subject.data();

		while ((pos = strcasestr(pos, search.c_str()))) {
			subject.replace(pos-subject.c_str(), search.length(), replace);
			pos += search.length();
		}
		return subject;
	}
}

extern uint32_t cppStrToU32(const StringConversionMagick& src, char** endptr = nullptr);

extern int strcpy_ajek(char* dest, int destlen, const char* src);
template<int size> inline int strcpy_ajek(char (&dest)[size], const char* src)
{
	return strcpy_ajek(dest, size, src);
}

// This verification extension is available as a separate icy-gist since it is non-trivial to implement inline.
#if !defined(VERIFY_PRINTF_ON_MSVC)
#	define VERIFY_PRINTF_ON_MSVC(...)	(void(0))
#endif

// Macros
//  cFmtStr - Format String with c_str (ASCII-Z) return type  <-- useful for printf, most C APIs
//  sFmtStr - Format String with STL return type	<-- mostly to provide matching API for cFmtStr macro

#if defined(VERIFY_PRINTF_ON_MSVC)
#	define sFmtStr(...)		            (VERIFY_PRINTF_ON_MSVC(__VA_ARGS__), StringUtil::Format(__VA_ARGS__)        )
#	define cFmtStr(...)		            (VERIFY_PRINTF_ON_MSVC(__VA_ARGS__), StringUtil::Format(__VA_ARGS__).c_str())
#	define AppendFmtStr(dest, fmt, ...)	(VERIFY_PRINTF_ON_MSVC(fmt, __VA_ARGS__), StringUtil::AppendFmt(dest, fmt, ## __VA_ARGS__))
#else
#	define sFmtStr(...)		            (StringUtil::Format(__VA_ARGS__)        )
#	define cFmtStr(...)		            (StringUtil::Format(__VA_ARGS__).c_str())
#	define AppendFmtStr(dest, fmt, ...)	(StringUtil::AppendFmt(dest, fmt, ## __VA_ARGS__))
#endif

// Custom string to integer conversions: sj for intmax_t, uj for uintmax_t
// Also support implicit conversion from std::string
inline intmax_t strtosj(const StringConversionMagick& src, char** meh, int radix) {
	return strtoll(src.c_str(), meh, radix);
}

inline uintmax_t strtouj(const StringConversionMagick& src, char** meh, int radix) {
	return strtoul(src.c_str(), meh, radix);
}
