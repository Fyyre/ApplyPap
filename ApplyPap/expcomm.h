/*-------------------------------------------------------------------------*\
|                                                                           |
|  FILE: EXPCOMM.H                                                          |
|                                                                           |
|                                                                           |
|  RTPatch Server Build/Apply DLL Common Declarations Header File           |
|                                                                           |
|                                                                           |
|  (C) Copyright Pocket Soft, Inc. 2001-2014.  All Rights Reserved.         |
|                                                                           |
\*-------------------------------------------------------------------------*/
# ifndef EXAPATCH_COMMON_INCLUDED

# define EXAPATCH_COMMON_INCLUDED

# include "exafeature.h"
# include "exaplat.h"
# include "exputils.h"
# include "experror.h"
# include "expfmt.h"


# ifdef EXAPATCH_ARCHIVE_SUPPORT
# include "exaarch.h"
# endif

# define EXAPATCH_LIBRARY_VERSION 0x929
/* other version numbers are build API version (expbuild.h) and apply API version (expapply.h) */

typedef struct _ExaPatchCommLink {
struct _ExaPatchCommLink * Next;
void * Node;
} ExaPatchCommLink;


typedef struct _ExaPatchDiscriminator {
UCHAR OldByte;
UCHAR NewByte;
DWORD OldIndex;
DWORD NewIndex;
QWORD Pos;
} ExaPatchDiscriminator;

typedef struct _ExaPatchByteHandling {
UINT dwSize;
DWORD dwType;
QWORD qwOldPos;
QWORD qwNewPos;
QWORD qwLength;
WCHAR * lpFileName;
} ExaPatchByteHandling;

typedef struct _ExaPatchExtendedHeader {
USHRT ID;
QWORD qwSize;
void * HeaderBlock;
} ExaPatchExtendedHeader;

typedef struct _ExaPatchFileInfo {
DWORD	dwNumOldFiles;
WCHAR **	lpOldPathArray;
ExaPatchStream * OldStream;
ExaPatchFileAttrib * lpOldAttribArray;
ExaPatchFileChecksum * lpOldCksumArray;
DWORD	dwNumNewFiles;
WCHAR **	lpNewPathArray;
ExaPatchStream * NewStream;
ExaPatchFileAttrib * lpNewAttribArray;
ExaPatchFileChecksum * lpNewCksumArray;
DWORD dwNumDiscrims;
ExaPatchDiscriminator * lpDiscArray;
DWORD Reserved[4];
} ExaPatchFileInfo;

typedef struct _ExaPatchCommFileEntryInfo {
DWORD dwSize;
ExaPatchFileInfo Files;
DWORD dwNumBH;
ExaPatchByteHandling * BHPtr;
WCHAR * lpEntryName;
SQWORD nSubDirIndex;
SQWORD nSystemIndex;
DWORD dwAttribWhich;
DWORD dwAttribRetain;
WCHAR * lpDoBefore;
WCHAR * lpDoAfter;
DWORD dwWhichFileFlags;
DWORD dwFileFlags;
DWORD dwNumEHBlocks;
ExaPatchExtendedHeader * EHBlockPtr;
DWORD dwNumHistoryVersions;
QWORD qwHistorySize;
QWORD qwHistoryFileSizes[2];
QWORD qwHistoryFileNums[2];
DWORD Reserved[4];
} ExaPatchCommFileEntryInfo;

typedef struct _ExaPatchSystemInfo {
DWORD dwSize;
DWORD	dwNumSystems;
WCHAR ** 	lpTagArray;
WCHAR ** 	lpNameArray;
DWORD *		lpBaseArray;
INT * lpKeyTypeArray;
DWORD * lpKeyBaseArray;
WCHAR ** lpParm1Array;
WCHAR ** lpParm2Array;
WCHAR ** lpParm3Array;
QWORD * lpSizeArray;
} ExaPatchSystemInfo;

typedef struct _ExaPatchSubDirInfo {
UINT	dwSize;
DWORD	dwNumSubDirs;
WCHAR ** 	lpPathArray;
} ExaPatchSubDirInfo;

typedef struct _ExaPatchCommFileHeaderInfo {
DWORD dwSize;
DWORD dwGlobalFlags;
DWORD dwReserved;				// bit 0 => parent extension present
DWORD dwPlatformFlags;
DWORD dwFileFlags;
DWORD dwAttribRetain;
WCHAR * lpBackupDirectory;
DWORD dwRegScript1Size;
DWORD dwRegScript1Num;
UCHAR * lpRegScript1;
DWORD dwRegScript2Size;
DWORD dwRegScript2Num;
UCHAR * lpRegScript2;
ExaPatchSystemInfo * Systems;
ExaPatchSubDirInfo * SubDirs;
WCHAR ** Comments;
WCHAR * lpPassword;
QWORD PWHash;
QWORD PWHash2;
WCHAR * lpGlobalPreHook;
WCHAR * lpGlobalPostHook;
INT nRootType;
DWORD dwRootBase;
WCHAR * lpRootParm1;
WCHAR * lpRootParm2;
WCHAR * lpRootParm3;
QWORD qwEASize;
UCHAR * lpEABlock;
DWORD dwNumEHBlocks;
ExaPatchExtendedHeader * EHBlockPtr;
QWORD qwOldDisk;
QWORD qwNewDisk;
QWORD qwMaxDisk;
QWORD qwBigDisk;
QWORD qwOldNum;
QWORD qwNewNum;
QWORD qwNumEntries;
DWORD Reserved[4];
} ExaPatchCommFileHeaderInfo;

/* CONSTANTS */
/* ByteHandling Types */
# define EXP_BYTE_IGNORE 0
# define EXP_BYTE_RETAIN 1
# define EXP_BYTE_READ 2
# define EXP_BYTE_NEWIGNORE 3

/*FileFlags */
#define EXP_FILE_BACKUP		0x1
#define EXP_FILE_CHECKATTRIB		0x2
#define EXP_FILE_CHECKTIMEDATE		0x4
#define EXP_FILE_IGNOREMISSING		0x8
#define EXP_FILE_PATHSEARCH		0x10
#define EXP_FILE_SUBDIRSEARCH		0x20
#define EXP_FILE_ADDWITHFILE		0x40
#define EXP_FILE_ADDTODIR		0x80
#define EXP_FILE_SUBDIRTYPE		0xc0
#define EXP_FILE_CREATESUBDIR		0x100
#define EXP_FILE_NOWARNINGS		0x200
#define EXP_FILE_SHAREDFILE		0x400
#define EXP_FILE_SELFREG				0x800
#define EXP_FILE_ALLOWDELAY	0x1000
#define EXP_FILE_DESTKEY_RESERVED 0x6000
#define EXP_FILE_ARCHIVE_RESERVED 0x8000
#define EXP_FILE_DESTKEY_LATE_COPY 0x10000
#define EXP_FILE_DESTKEY_MAY_EXIST 0x20000
#define EXP_FILE_DESTKEY_ALWAYS_COPY 0x40000
#define EXP_FILE_UPDATE_LINK 0x80000
#define EXP_FILE_FORCECOPY 0x100000
#define EXP_FILE_SELFREGWARNING 0x200000
#define EXP_FILE_UPDATETIMESTAMP 0x400000 /* user should not set this directly */
#define EXP_FILE_VERIFYONLY 0x800000 /* user should not set this directly */

/* GlobalFlags */
#define EXP_GLOBAL_MESSAGE		0x1
#define EXP_GLOBAL_UNDO		0x2
#define EXP_GLOBAL_USER_NONE		0x0
#define EXP_GLOBAL_USER_BACKUP		0x4
#define EXP_GLOBAL_USER_BASIC		0x8
#define EXP_GLOBAL_USER_ADVANCED	0xC
#define EXP_GLOBAL_VERBOSE		0x10
#define EXP_GLOBAL_HISTORY		0x20
#define EXP_GLOBAL_ERRORFILE		0x40
#define EXP_GLOBAL_CONFIRM		0x80
#define EXP_GLOBAL_ALLOWDUP		0x100
#define EXP_GLOBAL_NOTZCHECK		0x200
#define EXP_GLOBAL_NOALLOWSPLIT	0x400
#define EXP_GLOBAL_ALLOWDELAY 0x800
#define EXP_GLOBAL_IGNORELINKS 0x1000
#define EXP_GLOBAL_LINKUNIQUE 0x2000
#define EXP_GLOBAL_PRESERVELINKS 0x4000
#define EXP_GLOBAL_PROCESSLINKS 0x8000
#define EXP_GLOBAL_PLATFLAGS 0xff0000
#define EXP_GLOBAL_FORCEDELAY 0x1000000
#define EXP_GLOBAL_FORCECOPY 0x2000000
#define EXP_GLOBAL_ARCHIVE 0x4000000
#define EXP_GLOBAL_RESILIENT 0x8000000
#define EXP_GLOBAL_ALLOWPAD 0x10000000
#define EXP_GLOBAL_NOWARNINGS 0x20000000
#define EXP_GLOBAL_UNDOUTF8 0x40000000

/* PlatformFlags */
#define EXP_PLAT_DOS			0x10000
#define EXP_PLAT_WIN			0x10000
#define EXP_PLAT_UNIX			0x20000
#define EXP_PLAT_MAC			0x40000
#define EXP_PLAT_OS2			0x80000

/* OpenFlags */
#define EXP_OPEN_READONLY 0x1
#define EXP_OPEN_APPEND 0x2

/* Key Types */
#define EXP_KEYTYPE_NONE -1
#define EXP_KEYTYPE_INI 0x0
#define EXP_KEYTYPE_HKCR 0x1
#define EXP_KEYTYPE_HKCC 0x2
#define EXP_KEYTYPE_HKCU 0x3
#define EXP_KEYTYPE_HKLM 0x4
#define EXP_KEYTYPE_HKDD 0x6
#define EXP_KEYTYPE_WIN 0x7
#define EXP_KEYTYPE_SYS 0x8
#define EXP_KEYTYPE_HKU 0x9
#define EXP_KEYTYPE_ENV 0xa
#define EXP_KEYTYPE_CSIDL 0xb

/*StatusFlags */
#define EXP_STATUS_ALL 0x3fU
#define EXP_STATUS_CONTENTS 0x1U
#define EXP_STATUS_NAME 0x2U
#define EXP_STATUS_ATTRIB 0x4U
#define EXP_STATUS_TIMESTAMP 0x8U
#define EXP_STATUS_EA 0x10U
#define EXP_STATUS_ADS 0x20U
#define EXP_STATUS_RESERVED 0x40U
#define EXP_STATUS_RESERVED2 0x80U

/*ParseFlags*/
#define EXP_PARSE_ALT 0x1

/* Special EH IDs */
#define UPDATE_LINK_TARGET_BLOCKID_LOCAL 0x754c
#define UPDATE_DLINK_TARGET_BLOCKID_LOCAL 0x754d
#define OWNERGROUP_BLOCKID_LOCAL 0x6f67
#define ARCH_COST_BLOCKID_GLOBAL 0x6244
#define LOCKDIR_BLOCKID_GLOBAL 0x644c
#define	LOCKDIRPERM_BLOCKID_GLOBAL 0x704c
#define IN_PLACE_BLOCKID_LOCAL 0x5049

/* in expcomm.c */

INT ExaPatchCommFreeParsedEntry(
	ExaPatchCommFileEntryInfo * Entry
	);

INT ExaPatchCommFreeParsedHeader(
	ExaPatchCommFileHeaderInfo * Entry
	);

INT ExaPatchCommParseHeader(
	ExaPatchStream * FileToParse,
	ExaPatchCommFileHeaderInfo * HeaderPtr,
	DWORD dwParseFlags,
	DWORD dwParseIndex
	);

# endif
