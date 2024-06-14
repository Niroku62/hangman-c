#ifndef OS_CHECK_H
#define OS_CHECK_H

#if defined(__unix__) || defined(__linux__)
	#define IS_LINUX
#elif defined(_WIN32) || defined(_WIN64)
	#define IS_WINDOWS
#else
	#define IS_UNKNOWN_OS
#endif

#endif // #ifndef OS_CHECK_H
