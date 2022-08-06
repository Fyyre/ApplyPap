/*-------------------------------------------------------------------------*\
|                                                                           |
|  FILE: EXAPLAT.H                                                          |
|                                                                           |
|                                                                           |
|  RTPatch Server Apply Platform Switches                                   |
|                                                                           |
|                                                                           |
|  (C) Copyright Pocket Soft, Inc. 2001-2013.  All Rights Reserved.         |
|                                                                           |
\*-------------------------------------------------------------------------*/

# ifndef EXAPATCH_PLATFORM_INCLUDED
# define EXAPATCH_PLATFORM_INCLUDED

/* #define QWORD_IS_DWORD */
/* use when the QWORD definition is actually only 32 bits - won't work under Windows */
/* #define EXAPATCH_AVOID_UNALIGNED_ACCESS */
/* if this is used, also make sure that EXAPATCH_BIG_ENDIAN is set appropriately */

#ifndef GCC_VERSION
# ifdef __GNUC__
#  define GCC_VERSION ( __GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__ )
# else
#  define GCC_VERSION 0
# endif
#endif

#ifdef __RENESAS__
# ifdef __RL78__
#  define FARNEARSEMANTICS
#  define RESTRICTIVE_SEMANTICS
# endif
#endif

# ifdef FARNEARSEMANTICS
/* NOTE: only used in apply code */
#  define FARPTR __far
# else
#  define FARPTR
# endif

#ifdef __APPLE__
# include <TargetConditionals.h>
# ifdef TARGET_OS_IPHONE
#  if (TARGET_OS_IPHONE > 0)
#   define __IOS__
#  endif
# endif
#endif

/* # define NO_WCHAR_SUPPORT */
# ifdef NO_WCHAR_SUPPORT
#  define WC_CONST(x) x
#  define wchar_t char
# else
#  define WC_CONST(x) L ## x
# endif
/* MISRA C 2012 [20.10]: use of #/## macro in limited circumstances (wide/narrow character constants) */


#  if defined(_WIN32) || defined(WIN32)
/* NOTE: QWORD_IS_DWORD won't work under Windows, as QWORD is typedef'ed in windows.h <sigh> */
#   include <windows.h>
#   define PATH_DELIMITER L'\\'
#   define PATH_SEPARATOR L';'
typedef __int64 SQWORD;
# ifndef QWORD
typedef unsigned __int64 QWORD;
# endif
typedef __int32 SDWORD;
#   ifdef _WIN64
#    define PTR_SHIFT 3
typedef __int64 SPLATWORD;
typedef unsigned __int64 PLATWORD;
#   else
#    define PTR_SHIFT 2
typedef __int32 SPLATWORD;
typedef unsigned __int32 PLATWORD;
#   endif
#   ifdef EXAPATCH_INTERNAL_CODE
#    if !defined( _MSC_VER) || (_MSC_VER < 1400)
#     define wcscpy_s(X,Y,Z) wcscpy(X,Z)
#     define wcscat_s(X,Y,Z) wcscat(X,Z)
#     define wcsncpy_s(X,Y,Z,W) wcsncpy(X,Z,W)
#     define vswprintf_s(X,Y,Z,W) vswprintf(X,Z,W)
#     define vsprintf_s(X,Y,Z,W) vsprintf(X,Z,W)
#     define sprintf1(X,Y,Z,W) sprintf(X,Z,W)
#     define sprintf2(X,Y,Z,W,U) sprintf(X,Z,W,U)
#     define sprintf3(X,Y,Z,W,U,V) sprintf(X,Z,W,U,V) 
#     define sprintf4(X,Y,Z,W,U,V,S) sprintf(X,Z,W,U,V,S) 
#     define sprintf5(X,Y,Z,W,U,V,S,T) sprintf(X,Z,W,U,V,S,T)
#     define swprintf1(X,Y,Z,W) swprintf(X,Z,W)
#     define _getws_s(X,Y) _getws(X)
#    else
#     define sprintf1 sprintf_s
#     define sprintf2 sprintf_s
#     define sprintf3 sprintf_s
#     define sprintf4 sprintf_s
#     define sprintf5 sprintf_s
#     define swprintf1 swprintf_s
#    endif
#   endif
#  else
/* Non-Win32 definitions */
#    define MB_CAPABLE
/* define this if FUTIME is available to set file times */
/* # define FUTIME_SUPPORTED */

/* define this if the filesystem is case-sensitive */
# ifndef __APPLE__
#  define SENSITIVE_FNAMES
# endif

/* define this if 64-bit file offsets are supported (ANSI doesn't have this)*/
# ifndef __FreeBSD__
#  define SEEK64
#  ifdef SEEK64
#   ifdef __APPLE__
#    ifndef _DARWIN_FEATURE_64_BIT_INODE
#     define _DARWIN_FEATURE_64_BIT_INODE
#    endif
#   endif
#  endif
# endif

/* define this if the platform is Big Endian */
/* # define PLAT_BIG_ENDIAN*/
# include <stddef.h>
# include <stdlib.h>
# if !defined( __APPLE__) && !defined(__FreeBSD__) && !defined(ATTOPATCH)
# include <malloc.h>
# endif
# ifndef NO_WCHAR_SUPPORT
# include <wchar.h>
# include <wctype.h>
# endif
# include <stdio.h>
# include <string.h>
# ifndef ATTOPATCH
# include <sys/types.h>
# include <sys/stat.h>
# endif
# ifdef __APPLE__
# define fstat64 fstat
# define stat64 stat
# endif
# ifndef ATTOPATCH
# include <utime.h>
# endif
# include <errno.h>
/*# include <sys/utime.h>*/

# ifndef WINCE
#  if defined( __APPLE__) || defined(__FreeBSD__) || defined(__ANDROID__)
#  include <sys/param.h>
#  include <sys/mount.h>
#  include <unistd.h>
#   ifndef __ANDROID__
# define O_LARGEFILE 0
#   endif
# define open64 open
# define lseek64 lseek 
# define off64_t unsigned long long
#  else
#   ifndef ATTOPATCH
#    include <sys/statfs.h>
#    include <sys/unistd.h>
#   endif
#  endif
#  ifdef __ANDROID__
#  include <fcntl.h>
#  else
#   ifndef ATTOPATCH
#  include <sys/fcntl.h>
# endif
#  endif
# ifndef ATTOPATCH
#  include <dirent.h>
#  include <pthread.h>
# endif
# endif /* WINCE */

# if defined ( _M_ALPHA ) || defined (_ARM_) || defined ( ARM ) || defined (_SH4_) || defined ( SH4 )
#  define UNALIGNED __unaligned
# else
#  define UNALIGNED
# endif
# define PATH_DELIMITER WC_CONST('/')
# define PATH_SEPARATOR WC_CONST(':')
#define TRUE 1
#define FALSE 0
#define INVALID_HANDLE_VALUE ((void FARPTR *) 0xffffffff)
# ifndef MAX_PATH
#  ifdef UNIX_SUPPORT
#   define MAX_PATH 512
#  else
#   define MAX_PATH FILENAME_MAX*2
#  endif
# endif
# ifdef _LP64
#  define PTR_SHIFT 3
#  include <stdint.h>
typedef uint32_t DWORD;
typedef int32_t SDWORD;
# ifdef QWORD_IS_DWORD
typedef int32_t SQWORD;
typedef uint32_t QWORD;
# else
typedef int64_t SQWORD;
#  ifndef QWORD
typedef uint64_t QWORD;
#  endif
# endif
typedef uint64_t PLATWORD;
typedef int64_t SPLATWORD;
#  define CALLBACK
typedef uint32_t FARPTR * LPDWORD;
# else
#  define PTR_SHIFT 2
#  include <stdint.h>
#  ifdef __GNUC__
/* use tightly-sized GNU extensions if possible */
typedef uint32_t DWORD;
typedef int32_t SDWORD;
# ifdef QWORD_IS_DWORD
typedef int32_t SQWORD;
typedef uint32_t QWORD;
# else
typedef int64_t SQWORD;
#  ifndef QWORD
typedef uint64_t QWORD;
#  endif
# endif
typedef uint32_t PLATWORD;
typedef int32_t SPLATWORD;
typedef uint32_t FARPTR * LPDWORD;
#  else
#   if defined(__RENESAS__) && defined( __RL78__ )
/* tightly-sized extensions available here as well */
# define EXAPATCH_AVOID_UNALIGNED_ACCESS
typedef uint32_t DWORD;
typedef int32_t SDWORD;
# ifdef QWORD_IS_DWORD
typedef int32_t SQWORD;
typedef uint32_t QWORD;
# else
typedef int64_t SQWORD;
#  ifndef QWORD
typedef uint64_t QWORD;
#  endif
# endif
typedef uint32_t PLATWORD;
typedef int32_t SPLATWORD;
typedef uint32_t FARPTR * LPDWORD;
#   else
typedef unsigned long DWORD;
typedef long SDWORD;
# ifdef QWORD_IS_DWORD
typedef long SQWORD;
typedef unsigned long QWORD;
# else
typedef long long SQWORD;
typedef unsigned long long QWORD;
# endif
typedef unsigned long PLATWORD;
typedef long SPLATWORD;
typedef unsigned long FARPTR * LPDWORD;
#   endif
#  endif
# endif
#  define CALLBACK
typedef void FARPTR * LPVOID;
/* only do these typedef's if there isn't already a macro */
# ifndef UCHAR
typedef unsigned char UCHAR;
# endif
# ifndef UINT
typedef unsigned int UINT;
# endif
# ifndef INT
typedef int INT;
# endif
typedef wchar_t WCHAR;

typedef struct _FILETIME {
	DWORD dwLowDateTime; 
	DWORD dwHighDateTime;
} FILETIME;

# ifdef EXAPATCH_INTERNAL_CODE
#  ifdef __ANDROID__
#   define wcscpy_s(X,Y,Z) wcscpyAndroid(X,Z)
#   define wcscat_s(X,Y,Z) wcscatAndroid(X,Z)
#   define wcsncpy_s(X,Y,Z,W) wcsncpyAndroid(X,Z,W)
#  else
#   define wcscpy_s(X,Y,Z) wcscpy(X,Z)
#   define wcscat_s(X,Y,Z) wcscat(X,Z)
#   define wcsncpy_s(X,Y,Z,W) wcsncpy(X,Z,W)
#  endif
#   define vswprintf_s(X,Y,Z,W) vswprintf(X,Z,W)
#   define vsprintf_s(X,Y,Z,W) vsprintf(X,Z,W)
#   define sprintf1(X,Y,Z,W) sprintf(X,Z,W)
#   define sprintf2(X,Y,Z,W,U) sprintf(X,Z,W,U)
#   define sprintf3(X,Y,Z,W,U,V) sprintf(X,Z,W,U,V) 
#   define sprintf4(X,Y,Z,W,U,V,S) sprintf(X,Z,W,U,V,S) 
# ifdef __ANDROID__
#   define sprintf5(X,Y,Z,W,U,V,S,T) sprintf5Android(X,Z,W,U,V,S,T)
#   define swprintf1(X,Y,Z,W) swprintf1Android(X,Z,(void *)W)
# else
#   define sprintf5(X,Y,Z,W,U,V,S,T) sprintf(X,Z,W,U,V,S,T)
#   define swprintf1(X,Y,Z,W) swprintf(X,Z,W)
# endif
#   define _getws_s(X,Y) _getws(X)
# endif

# ifndef ATTOPATCH
# define CRITICAL_SECTION pthread_mutex_t
# ifndef RESTRICTIVE_SEMANTICS
typedef CRITICAL_SECTION * LPCRITICAL_SECTION;
# endif
# define InitializeCriticalSection(x) pthread_mutex_init(x, NULL)
# define EnterCriticalSection(x) pthread_mutex_lock(x)
# define LeaveCriticalSection(x) pthread_mutex_unlock(x)
# define DeleteCriticalSection(x) pthread_mutex_destroy(x)
# endif /* !ATTOPATCH */

# define IsBadReadPtr(x,y) ((x)==NULL)

/* These are not always defined */
# ifndef S_IREAD 
#  define S_IREAD  0x0100
# endif
# ifndef S_IFDIR 
#  define S_IFDIR  0x4000
# endif
# ifndef S_IFREG 
#  define S_IFREG  0x8000 
# endif
# ifndef O_BINARY 
#  define O_BINARY 0x8000
# endif

#define HANDLE void FARPTR *
# ifndef BOOL
#   define BOOL unsigned int
# endif
#endif
# ifndef CLEANCODE
#  define PWORD PLATWORD
#  define SPWORD SPLATWORD
# endif
/*
end non-Win32-specific definitions
*/
# ifndef USHRT
// this looks wrong, but it's correct - occasionally USHRT has already been #define'd
// at this point - in that case, don't do the (better) typedef
typedef unsigned short USHRT;
# endif
# ifndef SHRT
// this looks wrong, but it's correct - occasionally USHRT has already been #define'd
// at this point - in that case, don't do the (better) typedef
typedef short SHRT;
# endif
/* # define EXAPATCH_BIG_ENDIAN */
# ifdef EXAPATCH_BIG_ENDIAN
#		define WORD_SWAP(x) ((0xffU&((x)>>8))|(0xff00U&((x)<<8)))
#		define DWORD_SWAP(x) ((0xffU&((x)>>24))|(0xff00U&((x)>>8))|(0xff0000U&((x)<<8))|(0xff000000U&((x)<<24)))
#	else
#		define WORD_SWAP(x)	(x)
#		define DWORD_SWAP(x) (x)
#	endif
/* MISRA C 2012 [4.9]: use of function-like macro in limited circumstances to enable code re-use on big-endian platforms */

# ifdef EXAPATCH_AVOID_UNALIGNED_ACCESS
#  ifdef EXAPATCH_BIG_ENDIAN
#   define AUA_DW_LSB 3
#   define AUA_DW_NLSB 2
#   define AUA_DW_NMSB 1
#   define AUA_DW_MSB 0
#   define AUA_W_LSB 1
#   define AUA_W_MSB 0
#  else
#   define AUA_DW_LSB 0
#   define AUA_DW_NLSB 1
#   define AUA_DW_NMSB 2
#   define AUA_DW_MSB 3
#   define AUA_W_LSB 0
#   define AUA_W_MSB 1
#  endif
#  define AUA_DW_PUT(x,y) ((unsigned char *)(x))[AUA_DW_LSB]=(unsigned char)((y)&0xffU);\
	((unsigned char *)(x))[AUA_DW_NLSB]=(unsigned char)(((y)&0xff00U)>>8);\
	((unsigned char *)(x))[AUA_DW_NMSB]=(unsigned char)(((y)&0xff0000U)>>16);\
	((unsigned char *)(x))[AUA_DW_MSB]=(unsigned char)(((y)&0xff000000U)>>24);
#  define AUA_DW_LE_PUT(x,y) ((unsigned char *)(x))[0]=(unsigned char)((y)&0xffU);\
	((unsigned char *)(x))[1]=(unsigned char)(((y)&0xff00U)>>8);\
	((unsigned char *)(x))[2]=(unsigned char)(((y)&0xff0000U)>>16);\
	((unsigned char *)(x))[3]=(unsigned char)(((y)&0xff000000U)>>24);
#  define AUA_DW_GET(x) (((DWORD)((x)[AUA_DW_LSB]))|(((DWORD)((x)[AUA_DW_NLSB]))<<8)|(((DWORD)((x)[AUA_DW_NMSB]))<<16)|(((DWORD)((x)[AUA_DW_MSB]))<<24))
#  define AUA_DW_LE_GET(x) (((DWORD)((x)[0]))|(((DWORD)((x)[1]))<<8)|(((DWORD)((x)[2]))<<16)|(((DWORD)((x)[3]))<<24))
#  define AUA_W_PUT(x,y) ((unsigned char *)(x))[AUA_W_LSB]=(unsigned char)((y)&0xffU);\
	((unsigned char *)(x))[AUA_W_MSB]=(unsigned char)(((y)&0xff00U)>>8);
#  define AUA_W_LE_PUT(x,y) ((unsigned char *)(x))[0]=(unsigned char)((y)&0xffU);\
	((unsigned char *)(x))[1]=(unsigned char)(((y)&0xff00U)>>8);
#  define AUA_W_GET(x) (((unsigned short)((x)[AUA_W_LSB]))|(((unsigned short)((x)[AUA_W_MSB]))<<8))
#  define AUA_W_LE_GET(x) (((unsigned short)((x)[0]))|(((unsigned short)((x)[1]))<<8))
# endif


# ifdef EXAPATCH_INTERNAL_CODE
#  ifdef __ANDROID__
#   define PSmbstowcs mbstowcsAndroid
#   define PSwcstombs wcstombsAndroid
#   define PSwcslen wcslenAndroid
#   define PSwcscpy wcscpyAndroid
#   define PSwcsncpy wcsncpyAndroid
#   define PSwcscat wcscatAndroid
#   define PSwcsrchr wcsrchrAndroid
#   define PSwcschr wcschrAndroid
#   define PSwcscmp wcscmpAndroid
#   define PStowlower towlowerAndroid
#   define PSFNwcscmp wcscmpAndroid

/* Android-specific wide-char handling (built-in is badly broken)
 routines in jnishim.c */
size_t mbstowcsAndroid( wchar_t *wcstr, const char *mbstr, size_t max );
size_t wcstombsAndroid( char *mbstr, const wchar_t * wcstr, size_t max );
size_t wcslenAndroid( const wchar_t * wcstr );
wchar_t * wcscpyAndroid( wchar_t * restrict dest, const wchar_t * restrict src );
wchar_t * wcsncpyAndroid( wchar_t * restrict dest, const wchar_t *restrict src, size_t n);
wchar_t * wcscatAndroid( wchar_t * restrict dest, const wchar_t * restrict src );
wchar_t * wcsrchrAndroid( const wchar_t * wcstr, wchar_t c );
wchar_t * wcschrAndroid( const wchar_t * wcstr, wchar_t c );
int wcscmpAndroid( const wchar_t * ws1, const wchar_t * ws2 );
wchar_t towlowerAndroid( wchar_t wc );
int swprintf1Android( wchar_t * dest, const wchar_t * fmt, void * arg );	/* arg may in fact be DWORD, wchar_t * or char * */
int sprintf5Android( char * dest, const char * fmt, DWORD dw1, char c1, DWORD dw2, char c2, wchar_t * string );
/* NOTE: sprintf5 is only used in one place and the replacement routine is *only* suitable for
  replacing that particular call. */



#  else
#   define PSmbstowcs mbstowcs
#   define PSwcstombs wcstombs
#   define PSwcslen wcslen
#   define PSwcscpy wcscpy
#   define PSwcsncpy wcsncpy
#   define PSwcscat wcscat
#   define PSwcsrchr wcsrchr
#   define PSwcschr wcschr
#   define PSwcscmp wcscmp
#   ifdef SENSITIVE_FNAMES
#     define PSFNwcscmp wcscmp
#   else
#    ifdef __APPLE__
int PSFNwcscmp(const wchar_t * s1, const wchar_t * s2 ); /* defined in exafname.c */
#    else
#     define PSFNwcscmp _wcsicmp
#    endif
#   endif
#   define PStowlower towlower
#  endif
# endif

#endif
