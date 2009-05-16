/* config.h.  Generated by configure.  */
/* config.h.in.  Generated from configure.in by autoheader.  */
#define PACKAGE "libxml2"
#define VERSION "2.7.2"

#if !defined(_WIN32) && !defined(__APPLE__)
/* Define if IPV6 support is there */
# define SUPPORT_IP6 1


/* Define if getaddrinfo is there */
# define HAVE_GETADDRINFO 1
#endif

/* Define to 1 if you have the <ansidecl.h> header file. */
#if defined(__WIN32)
#if __GNUC__ < 4
# define HAVE_ANSIDECL_H 1
#endif
#endif

/* Define to 1 if you have the <arpa/inet.h> header file. */
#if !defined(_WIN32)
#define HAVE_ARPA_INET_H 1

/* Define to 1 if you have the <arpa/nameser.h> header file. */
#define HAVE_ARPA_NAMESER_H 1
#endif

/* Whether struct sockaddr::__ss_family exists */
/* #undef HAVE_BROKEN_SS_FAMILY */

/* Define to 1 if you have the `class' function. */
/* #undef HAVE_CLASS */

/* Define to 1 if you have the <ctype.h> header file. */
#define HAVE_CTYPE_H 1

/* Define to 1 if you have the <dirent.h> header file. */
#define HAVE_DIRENT_H 1

/* Define to 1 if you have the <dlfcn.h> header file. */
#if !defined(_WIN32)
# define HAVE_DLFCN_H 1


/* Have dlopen based dso */
# define HAVE_DLOPEN 1
#endif

/* Define to 1 if you have the <dl.h> header file. */
/* #undef HAVE_DL_H */

/* Define to 1 if you have the <errno.h> header file. */
#define HAVE_ERRNO_H 1

/* Define to 1 if you have the <fcntl.h> header file. */
#define HAVE_FCNTL_H 1

/* Define to 1 if you have the `finite' function. */
#define HAVE_FINITE 1

/* Define to 1 if you have the <float.h> header file. */
#define HAVE_FLOAT_H 1

/* Define to 1 if you have the `fpclass' function. */
#if defined(_WIN32)
# define HAVE_FPCLASS 1
#endif

/* Define to 1 if you have the `fprintf' function. */
#define HAVE_FPRINTF 1

/* Define to 1 if you have the `fp_class' function. */
/* #undef HAVE_FP_CLASS */

/* Define to 1 if you have the <fp_class.h> header file. */
/* #undef HAVE_FP_CLASS_H */

/* Define to 1 if you have the `ftime' function. */
#if !defined(__APPLE__)
# define HAVE_FTIME 1
#endif


/* Define if getaddrinfo is there */
#if !defined(_WIN32) && !defined(__APPLE__)
# define HAVE_GETADDRINFO 1
#endif

/* Define to 1 if you have the `gettimeofday' function. */
#if !defined(_WIN32)
#define HAVE_GETTIMEOFDAY 1
#endif

/* Define to 1 if you have the <ieeefp.h> header file. */
/* #undef HAVE_IEEEFP_H */

/* Define to 1 if you have the <inttypes.h> header file. */
#if !defined(_WIN32)
#define HAVE_INTTYPES_H 1

/* Define if isinf is there */
#define HAVE_ISINF 1
#endif

/* Define if isnan is there */
#define HAVE_ISNAN 

/* Define to 1 if you have the `isnand' function. */
/* #undef HAVE_ISNAND */

/* Define if history library is there (-lhistory) */
/* #undef HAVE_LIBHISTORY */

/* Define if pthread library is there (-lpthread) */
//#if !defined(_WIN32) && !defined(__APPLE__)
//# define HAVE_LIBPTHREAD 0
//#endif

/* Define if readline library is there (-lreadline) */
/* #undef HAVE_LIBREADLINE */

/* Have compression library */
# define HAVE_LIBZ 1

/* Define to 1 if you have the <limits.h> header file. */
#define HAVE_LIMITS_H 1

/* Define to 1 if you have the `localtime' function. */
#define HAVE_LOCALTIME 1

/* Define to 1 if you have the <malloc.h> header file. */
#define HAVE_MALLOC_H 1

/* Define to 1 if you have the <math.h> header file. */
#define HAVE_MATH_H 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the <nan.h> header file. */
/* #undef HAVE_NAN_H */

/* Define to 1 if you have the <ndir.h> header file, and it defines `DIR'. */
/* #undef HAVE_NDIR_H */

/* Define to 1 if you have the <netdb.h> header file. */
#if !defined(_WIN32)
# define HAVE_NETDB_H 1

/* Define to 1 if you have the <netinet/in.h> header file. */
# define HAVE_NETINET_IN_H 1
#endif

/* Define to 1 if you have the `printf' function. */
#define HAVE_PRINTF 1

/* Define if <pthread.h> is there */
#if !defined(_WIN32)
//# define HAVE_PTHREAD_H 1

/* Define to 1 if you have the <resolv.h> header file. */
# define HAVE_RESOLV_H 1
#endif

/* Have shl_load based dso */
/* #undef HAVE_SHLLOAD */

/* Define to 1 if you have the `signal' function. */
#define HAVE_SIGNAL 1

/* Define to 1 if you have the <signal.h> header file. */
#define HAVE_SIGNAL_H 1

/* Define to 1 if you have the `snprintf' function. */
#define HAVE_SNPRINTF 1

/* Define to 1 if you have the `sprintf' function. */
#define HAVE_SPRINTF 1

/* Define to 1 if you have the `sscanf' function. */
#define HAVE_SSCANF 1

/* Define to 1 if you have the `stat' function. */
#define HAVE_STAT 1

/* Define to 1 if you have the <stdarg.h> header file. */
#define HAVE_STDARG_H 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the `strdup' function. */
#define HAVE_STRDUP 1

/* Define to 1 if you have the `strerror' function. */
#define HAVE_STRERROR 1

/* Define to 1 if you have the `strftime' function. */
#define HAVE_STRFTIME 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the `strndup' function. */
#if !defined(_WIN32) && !defined(__APPLE__)
# define HAVE_STRNDUP 1
#endif

/* Define to 1 if you have the <sys/dir.h> header file, and it defines `DIR'.
   */
/* #undef HAVE_SYS_DIR_H */

/* Define to 1 if you have the <sys/mman.h> header file. */
#if !defined(_WIN32)
# define HAVE_SYS_MMAN_H 1
#endif

/* Define to 1 if you have the <sys/ndir.h> header file, and it defines `DIR'.
   */
/* #undef HAVE_SYS_NDIR_H */

/* Define to 1 if you have the <sys/select.h> header file. */
#if !defined(_WIN32)
# define HAVE_SYS_SELECT_H 1

/* Define to 1 if you have the <sys/socket.h> header file. */
# define HAVE_SYS_SOCKET_H 1
#endif

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/timeb.h> header file. */
#define HAVE_SYS_TIMEB_H 1

/* Define to 1 if you have the <sys/time.h> header file. */
#define HAVE_SYS_TIME_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <time.h> header file. */
#define HAVE_TIME_H 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Whether va_copy() is available */
#define HAVE_VA_COPY 1

/* Define to 1 if you have the `vfprintf' function. */
#define HAVE_VFPRINTF 1

/* Define to 1 if you have the `vsnprintf' function. */
#define HAVE_VSNPRINTF 1

/* Define to 1 if you have the `vsprintf' function. */
#define HAVE_VSPRINTF 1

/* Define to 1 if you have the <zlib.h> header file. */
#define HAVE_ZLIB_H 1

/* Define to 1 if you have the `_stat' function. */
#if defined(_WIN32) || defined(__APPLE__)
#define HAVE__STAT 1
#endif

/* Whether __va_copy() is available */
/* #undef HAVE___VA_COPY */

/* Name of package */
#define PACKAGE "libxml2"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT ""

/* Define to the full name of this package. */
#define PACKAGE_NAME ""

/* Define to the full name and version of this package. */
#define PACKAGE_STRING ""

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME ""

/* Define to the version of this package. */
#define PACKAGE_VERSION ""

/* Define to 1 if the C compiler supports function prototypes. */
#define PROTOTYPES 1

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1


/* Version number of package */
#define VERSION "2.6.27"

/* Determine what socket length (socklen_t) data type is */
#if defined(_WIN32)
# define XML_SOCKLEN_T int
#else
# define XML_SOCKLEN_T socklen_t
#endif

/* Define like PROTOTYPES; this can be used by system headers. */
#define __PROTOTYPES 1

#if defined(_WIN32)
/* Using the Win32 Socket implementation */
#define _WINSOCKAPI_ 1

/* Win32 Std C name mangling work-around */
#define snprintf _snprintf

/* ss_family is not defined here, use __ss_family instead */
/* #undef ss_family */

/* Win32 Std C name mangling work-around */
#define vsnprintf _vsnprintf

/*# define HAVE_WIN32_THREADS 1*/
# define _REENTRANT 1
#endif

#define LIBXML_STATIC 1
