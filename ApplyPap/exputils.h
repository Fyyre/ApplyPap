/*-------------------------------------------------------------------------*\
|                                                                           |
|  FILE: EXPUTILS.H                                                         |
|                                                                           |
|                                                                           |
|  RTPatch Server Build/Apply DLL Common Utilities API Header File          |
|                                                                           |
|                                                                           |
|  (C) Copyright Pocket Soft, Inc. 2001-2014.  All Rights Reserved.         |
|                                                                           |
\*-------------------------------------------------------------------------*/
# ifndef EXAPATCH_UTILS_INCLUDED

# define EXAPATCH_UTILS_INCLUDED

# include "exafeature.h"
# include "exaplat.h"
# if !defined(_WIN32) && !defined(ATTOPATCH)
# include <sys/types.h>
# ifndef NOACL
#  if !defined( __ANDROID__) || defined(ANDROID_ACL)
#  include <sys/acl.h>
#  endif
# endif
# endif


/*
 STRUCTURES
*/
typedef struct _ExaPatchFileAttrib {
DWORD Flags;
DWORD Attributes;
FILETIME ChangedTime;
FILETIME CreateTime;
QWORD Size;
} ExaPatchFileAttrib;

# ifndef ATTOPATCH
typedef struct _ExaPatchFileSecurity {
DWORD WhatToSet;
# ifndef _WIN32
uid_t Owner;
gid_t Group;
# ifndef NOACL
#  if !defined( __ANDROID__ ) || defined( ANDROID_ACL )
acl_t ACL;
#  endif
# endif
# ifdef __APPLE__
#  if !defined( __IOS__ ) || defined( IOS_TC )
DWORD Type;
DWORD Creator;
#  endif
# endif
# endif
void * pSD;
} ExaPatchFileSecurity;
# endif /* !ATTOPATCH */

typedef struct _ExaPatchStream {
UINT dwSize;
DWORD Type;	
HANDLE FileHandle;
INT (CALLBACK * Read)(HANDLE hStream, void * pBuffer, DWORD dwCount, LPDWORD pdwAmtRead);	
/*
 returns an error code
                              Buffer  Size   ReturnSize
*/
INT (CALLBACK * Write)(HANDLE hStream, const void * pBuffer, DWORD dwCount, LPDWORD pdwAmtWritten);
/*
                              Buffer  Size   ReturnSize
*/
INT (CALLBACK * Seek)(HANDLE hStream, QWORD qwPos, DWORD dwOrigin, QWORD * pqwReturnPos);
/*
                              Pos    Origin  ReturnPos
*/
INT (CALLBACK * AttribGet)(HANDLE hStream, ExaPatchFileAttrib * pAttrib);
INT (CALLBACK * AttribSet)(HANDLE hStream, const ExaPatchFileAttrib * pAttrib);
INT (CALLBACK * Close)(HANDLE hStream);
DWORD Flags; /* 1 -> file handle is a true duplicate */
QWORD UserStreamPos;
struct _ExaPatchStream * Link;
QWORD Size;
QWORD CompositeOrigin;
QWORD FileOrigin;
void * Buffer;
DWORD BufferSize;
QWORD BufferOrigin;
QWORD SpecialGapPos;
QWORD CurPos;
struct _ExaPatchStream * CurCpt;
} ExaPatchStream;
/* MISRA C 2012 [1.1, 1.2]: use of non-ANSI keyword when needed under Windows (CALLBACK includes __stdcall) */

typedef struct _ExaPatchFileChecksum {
UCHAR Cksum[10];
} ExaPatchFileChecksum;

/*
 CONSTANTS
 Seek Types
*/
# define EXAPATCH_SEEK_BEGIN 0
# define EXAPATCH_SEEK_CUR 1
# define EXAPATCH_SEEK_END 2

/*
 Stream Types
*/
# define EXP_STREAM_FILE 0U
# define EXP_STREAM_COMPOSITE 1U
# define EXP_STREAM_GAP 2U
# define EXP_STREAM_SPECIAL_GAP 3U
# define EXP_STREAM_USER 4U
# define EXP_STREAM_TYPE_BITS 0xfU
# define EXP_STREAM_BUFFERED 0x10U
# define EXP_STREAM_SPECIAL_BUFFERED 0x20U
# define EXP_STREAM_SB_RESERVED 0x40U
# define EXP_STREAM_SB_RSVD2 0x80U

/*
 Attrib Flags
*/
# define EXP_ATTRIB_ALL 0xf
# define EXP_ATTRIB_ATTRIBUTE	0x1
# define EXP_ATTRIB_CHANGED_DATE	0x2
# define EXP_ATTRIB_CREATE_DATE	0x4
# define EXP_ATTRIB_SIZE		0x8
# define EXP_ATTRIB_SECURITY 0x10 /* NOTE: not included in EXP_ATTRIB_ALL - this is intentional */

/*
 Non-Win32 Security Flags
*/
# define EXP_SECURITY_OWNER 0x1
# define EXP_SECURITY_GROUP 0x2
# define EXP_SECURITY_ACL 0x4
# define EXP_SECURITY_TC 0x8

/*
 File Attributes
*/
# define EXP_ATTRIBUTE_READONLY 0x1
# define EXP_ATTRIBUTE_HIDDEN 0x2
# define EXP_ATTRIBUTE_SYSTEM 0x4
# define EXP_ATTRIBUTE_SECURITY 0x8
# define EXP_ATTRIBUTE_SHAREABLE 0x80 /* No longer supported */
# define EXP_ATTRIBUTE_TEMPORARY 0x100
# define EXP_ATTRIBUTE_INDEX 0x2000
# define EXP_ATTRIBUTE_WIN32_CHANGEABLE 0x2107
# define EXP_ATTRIBUTE_CHECKED 0x2157
# define EXP_ATTRIBUTE_WORLD 0x70000
# define EXP_ATTRIBUTE_WORLD_X 0x10000
# define EXP_ATTRIBUTE_WORLD_W 0x20000
# define EXP_ATTRIBUTE_WORLD_R 0x30000
# define EXP_ATTRIBUTE_GROUP 0x380000
# define EXP_ATTRIBUTE_GROUP_X 0x80000
# define EXP_ATTRIBUTE_GROUP_W 0x100000
# define EXP_ATTRIBUTE_GROUP_R 0x200000
# define EXP_ATTRIBUTE_OWNER 0x1c00000
# define EXP_ATTRIBUTE_OWNER_X 0x400000
# define EXP_ATTRIBUTE_OWNER_W 0x800000
# define EXP_ATTRIBUTE_OWNER_R 0x1000000
# define EXP_ATTRIBUTE_PERMISSIONS 0xdff0000

/*
 Checksum types
*/
# define EXP_CHECKSUM_NEW 0x80

/*
 ROUTINES

 Streams (exastream.c)
*/
INT InitExaStream( ExaPatchStream * Stream );
INT ReadExaStream( ExaPatchStream * Stream, void * Buffer, DWORD Count, LPDWORD lpCount );
INT WriteExaStream( ExaPatchStream * Stream, const void * Buffer, DWORD Count, LPDWORD lpCount );
INT SeekExaStream( ExaPatchStream * Stream, QWORD Position, DWORD Origin, QWORD * lpPos );
INT CloseExaStream( ExaPatchStream * Stream );
# ifndef ATTOPATCH
INT CloneExaStream( ExaPatchStream ** DestStream, const ExaPatchStream * SrcStream, DWORD DupFlag );
INT FreeClonedExaStream( ExaPatchStream * Stream );
# endif
INT GetExaStreamAttrib( ExaPatchStream * Stream, ExaPatchFileAttrib * Attrib );
INT SetExaStreamAttrib( ExaPatchStream * Stream, const ExaPatchFileAttrib * Attrib );
INT MakeExaStreamFromFileArray( ExaPatchStream * Stream, DWORD NumHandles, HANDLE * HandlePtr, QWORD * SizePtr );
INT ForceExaStreamZeroes( ExaPatchStream * Stream, QWORD Pos, QWORD Size, QWORD * SpecialPosPtr );
INT SetExaStreamBuffering( ExaPatchStream * Stream, DWORD Flag );
INT GetNextExaStreamSpecial( const ExaPatchStream * Stream, QWORD CurPos, QWORD * OffsetPtr, QWORD * LenPtr, QWORD * PosPtr );
INT ForceExaStreamBuffering( ExaPatchStream * Stream, DWORD dwBufferSize );
# ifdef EXAPATCH_SPECIALSTREAM_SUPPORT
INT ExaStreamSupplyBuffer( ExaPatchStream * Stream, void * Buffer, DWORD dwBufferSize );
# endif
# ifdef EXAPATCH_ACLCACHE_SUPPORT
INT ExaStreamAclCacheOn( void );
	/*
		thread-safe and uses a lock count - CacheOff must be called once for each successful call to CacheOn
	*/
INT ExaStreamAclCacheOff( void );
INT ExaStreamAclCacheQuery( void ); 
	/* 
		returns EXAPATCH_SUCCESS if cache is on, and increments lock count, so that CacheOff must be called 
		returns EXAPATCH_UNSPECIFIED_ERROR if cache is off
	*/
# endif

# define EXAPATCH_STREAM_DEFAULT_BUFSIZE 0x40000

/*
 Memory (examem.c)
*/
INT ExaMemInit( PLATWORD InitSize, HANDLE * HandlePtr, UINT SerializeFlag );
INT ExaMemAlloc( HANDLE Handle, PLATWORD Size, void * * PtrPtr );
INT ExaMemFree( HANDLE Handle, void * Ptr );
PLATWORD ExaMemSize( HANDLE Handle, void * Ptr );
INT ExaMemAllocBig( HANDLE Handle, PLATWORD Size, PLATWORD MaxSize, void * * PtrPtr );
INT ExaMemReallocBig( HANDLE Handle, PLATWORD Size, void * * PtrPtr );
PLATWORD ExaMemSizeBig( HANDLE Handle, void * Ptr );
INT ExaMemFreeBig( HANDLE Handle, void * Ptr );
INT ExaMemShutDown( HANDLE Handle );
void ExaMemLog( char * Fmt, ... );

/*
 CheckSums (exacksum.c)
*/
INT ExaCSCheckSum(
	UCHAR * Buffer,
	DWORD Length,
	ExaPatchFileChecksum * CSPtr,
	INT Type
	);
INT ExaCSUnCheckSum(
	UCHAR * Buffer,
	DWORD Length,
	QWORD Offset,
	ExaPatchFileChecksum * CSPtr
	);
/*
 FileNames (exafname.c)
*/
# ifndef ATTOPATCH
HANDLE ExaOpen( const wchar_t * FileName, DWORD dwReadOnly, DWORD dwAppend );
INT ExaClose( HANDLE hFile );
INT ExaDelete( const wchar_t * FileName ); 
INT ExaIsFileHidden( const wchar_t * FileName );
/*
		 no delay
*/
INT ExaRename( const wchar_t * FileName1, const wchar_t * FileName2 ); 
/* 
 no delay
*/
wchar_t * ExaBaseName( wchar_t * FileName, wchar_t SepChar );
INT ExaFullyQualify( const wchar_t * FileName, wchar_t **RetPtr);
INT ExaDirMerge( const wchar_t * DirName, const wchar_t *FileName, wchar_t **RetPtr, wchar_t SepChar );
INT ExaBuildTempName( wchar_t * DirName, DWORD Num, wchar_t SepChar );
INT ExaExists( const wchar_t * FileName );
INT ExaFileExists( const wchar_t * FileName );
INT ExaDirExists( const wchar_t * FileName );
INT ExaIsSymlink( const wchar_t * FileName );
INT ExaCopyFile( const wchar_t * Source, const wchar_t * Dest, DWORD dwEADSFlag, DWORD dwLinkFlag, DWORD dwOGFlag );
# ifndef ATTOPATCH
INT ExaSetFileAttrib( const wchar_t * FileName, ExaPatchFileAttrib * Attrib, ExaPatchFileSecurity * pFS, DWORD dwLink );
INT ExaGetFileAttrib( const wchar_t * FileName, ExaPatchFileAttrib * Attrib, ExaPatchFileSecurity * pFS, DWORD dwLink );
INT ExaFreeFileSecurity( ExaPatchFileSecurity * pFS );
# endif
INT ExaMakeDir( wchar_t * Directory );
INT ExaMakeDirEx( wchar_t * Directory, wchar_t ** pTopDir ); /* returns top-most parent that needed to be created */
INT ExaRmDir( const wchar_t * Directory );
# ifdef EXAPATCH_UPDATELINK_SUPPORT
INT ExaGetLinkTarget(const wchar_t * pFileName,char * pBuffer, DWORD dwSize, DWORD * pdwSizeNeeded);
INT ExaSetLinkTarget(const wchar_t * pFileName, const char * pBuffer, DWORD dwDirFlag);
# endif
# ifdef EXAPATCH_OWNERGROUP_SUPPORT
INT ExaGetOwnerGroupNum(const wchar_t * pFileName, DWORD * pdwOwner, DWORD * pdwGroup);
INT ExaSetOwnerGroupNum(const wchar_t * pFileName, DWORD dwOwner, DWORD dwGroup );
# endif
/* free space mechanism */
/* Typedefs */

typedef struct _MOUNTPOINT {
struct _MOUNTPOINT * pNext;
struct _MOUNTPOINT * pPrev;
struct _PHYSDRIVE * pPhys;
wchar_t * szWideName;
# ifdef _WIN32
char * szNarrowName;
# endif
} MOUNTPOINT, * PMOUNTPOINT;

typedef struct _PHYSDRIVE {
struct _PHYSDRIVE * pNext;
struct _PHYSDRIVE * pPrev;
# ifdef _WIN32
wchar_t * szWideNormalName;
char * szNarrowNormalName;
# else
dev_t st_dev;
# endif
wchar_t * szDevName;
QWORD qwNumFiles;
QWORD qwFileSizeNeeded;
QWORD qwBytesNeeded;
QWORD qwBytesPresent;
} PHYSDRIVE, * PPHYSDRIVE;

INT ExaDevInit( BOOL bLimited );
INT ExaDevClose( void );
INT ExaDevRegNeeds( wchar_t * szPath, QWORD qwFileSize, QWORD qwNumFiles );
INT ExaDevCheckNeeds( void );
PMOUNTPOINT ExaDevGetMP( void );
PPHYSDRIVE ExaDevGetPD( void );
INT ExaDevCompare( wchar_t * szPath1, wchar_t * szPath2 );
# endif /* !ATTOPATCH */

# endif	/* EXAPATCH_UTILS_INCLUDED */
