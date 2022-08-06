/*-------------------------------------------------------------------------*\
|                                                                           |
|  FILE: EXPAPPLY.H                                                         |
|                                                                           |
|                                                                           |
|  RTPatch Server Apply DLL Application Programming Interface Header File   |
|                                                                           |
|                                                                           |
|  (C) Copyright Pocket Soft, Inc. 2001-2014.  All Rights Reserved.         |
|                                                                           |
\*-------------------------------------------------------------------------*/
# ifndef EXAPATCH_APPLY_INCLUDED

# define EXAPATCH_APPLY_INCLUDED
# include "exafeature.h"
# include "exaplat.h"
# include "exputils.h"
# include "experror.h"
# include "expcomm.h"


/*-----------------------------------------------------------------------*\
|  C++ name mangling prevention -- beginning of block                     |
\*-----------------------------------------------------------------------*/
# ifdef __cplusplus
  extern "C" {
# endif /*__cplusplus */

# ifndef EXP_DLLIMPORT
#  ifdef _WIN32
#   ifdef EXAPATCH_INTERNAL
#    define EXP_DLLIMPORT _declspec(dllexport) CALLBACK
#   else
#    define EXP_DLLIMPORT _declspec(dllimport) CALLBACK
#   endif
#  else
# 	define EXP_DLLIMPORT
#   define EXP_DLLEXPORT
#  endif
# endif

# define EXAPATCH_APPLY_API_VERSION 0x202L

/* STRUCTURES */

typedef struct _ExaPatchApplyIgnoreRegion {
QWORD Offset;
QWORD Length;
struct _ExaPatchApplyIgnoreRegion * Next;
} ExaPatchApplyIgnoreRegion;

typedef struct _ExaPatchApplyFileManipulation {
WCHAR * OldFile;
WCHAR * IntFile;
WCHAR * IntFile2;
WCHAR * NewFile;
WCHAR * BackupFile;
WCHAR * BackupFile2;
DWORD FileManipFlags;
DWORD WhichRetain;
struct _ExaPatchApplyFileManipulation * NextManip;
struct _ExaPatchApplyFileManipulation * PrevManip;
DWORD FileManipType;
} ExaPatchApplyFileManipulation;

typedef struct _ExaPatchApplyDupListEntry {
WCHAR * FileName;
struct _ExaPatchApplyDupListEntry * NextEntry;
} ExaPatchApplyDupListEntry;

typedef struct _ExaPatchApplyTempListEntry {
WCHAR * FileName;
WCHAR * OldFile;
struct _ExaPatchApplyTempListEntry * NextEntry;
} ExaPatchApplyTempListEntry;

typedef struct _ExaPatchApplyFileEntryInfo {
ExaPatchCommFileEntryInfo Comm;
DWORD dwHistoryCurrentVersion;
QWORD qwEntryNum;
QWORD qwEntryPos; /* beginning of entry header */
QWORD qwEntrySize; /* size after entry header (includes header for HISTORY) */
ExaPatchApplyIgnoreRegion ** OldRegionListArray; /* caller sets to NULL */
ExaPatchApplyIgnoreRegion ** NewRegionListArray; /* caller sets to NULL */
USHRT wPatchType;
USHRT wModFlags;
} ExaPatchApplyFileEntryInfo;

typedef struct _ExaPatchApplyFileHeaderInfo {
ExaPatchCommFileHeaderInfo Comm;
WCHAR * ApplyDirectory; /* set by caller if desired */
WCHAR * BackupDirectory; /* set by caller if desired */
WCHAR * SingleFileName; /* set by caller (if necessary) */
WCHAR * DrivesToCheck; /* set by caller if desired */
ExaPatchApplyFileManipulation * ManipList; 
ExaPatchApplyFileManipulation * ManipTail; 
ExaPatchApplyFileManipulation * LocalManipList;
ExaPatchApplyFileManipulation * LocalManipTail;
ExaPatchApplyFileManipulation * RegList;
ExaPatchApplyFileManipulation * RegTail;
ExaPatchApplyDupListEntry * DupList;
ExaPatchApplyTempListEntry * TempList;
SDWORD RegUndoID;
QWORD qwNextEntryNum;
DWORD IndivFlagsOverridden;
DWORD ApplyFlags;
DWORD ApplyForceFlags;
DWORD dwBW;
ExaPatchStream * BackupCmdFile;
ExaPatchStream * ErrorFile;
void * ErrorBuffer;
WCHAR * BackupCFName;
WCHAR * ActualApplyDir;
WCHAR * ErrorFileName;
WCHAR * ScratchDir;
WCHAR ** SystemDirs;
QWORD Stats[7];
/* Comm.dwReserved, bit 0 must be set to indicate existence of these fields */
DWORD dwExtensionSize;
PLATWORD hUnique;
void * pArchiveInfo;
WCHAR * DKApplyDir;
WCHAR * DKRmDir;
} ExaPatchApplyFileHeaderInfo;

#define HUNIQUE_SIZE (sizeof(DWORD)+sizeof(PLATWORD))
#define ARCHIVE_SIZE (sizeof(DWORD)+sizeof(PLATWORD)+sizeof(void *))
#define DESTKEY_SIZE (sizeof(DWORD)+sizeof(PLATWORD)+sizeof(void *)+(2U*sizeof(WCHAR *)))
#define CUR_EXTENSION_SIZE DESTKEY_SIZE

/* CONSTANTS */
/* FileManipFlags */
#define EXP_PATCH_MANIP_DELETERENAME 0x1
#define EXP_PATCH_MANIP_SELFREG 0x2
#define EXP_PATCH_MANIP_SHARED 0x4
#define EXP_PATCH_MANIP_BACKUP 0x8
#define EXP_PATCH_MANIP_RETAIN 0x10

#define EXP_PATCH_MANIP_PHASE1 0x20 	/* unregister, unshare, backup "old" file */
#define EXP_PATCH_MANIP_PHASE2 0x40		/* rename "old" file to "Int2" file */
#define EXP_PATCH_MANIP_PHASE3 0x80		/* get attrib from "Int2" or "old",
																				rename "Int" file to "new" file 
																				(delete target if necessary), 
																				set attrib, register, share */
#define EXP_PATCH_MANIP_PHASE4 0x100	/* delete "old" or "Int2" file */
#define EXP_PATCH_MANIP_UNDO_PHASE1 0x200 /* re-register, re-share "old" file */
#define EXP_PATCH_MANIP_UNDO_PHASE2 0x400 /* rename "Int2" back to "old" (delete target if necessary) */
#define EXP_PATCH_MANIP_UNDO_PHASE3 0x800 /* un-share, un-register, rename "new" back to "Int" */
#define EXP_PATCH_MANIP_SPECIAL_HANDLING 0x1000
																					/* This bit indicates that the "int" file 
																						is really the "old" file.  If something goes
																						wrong, it shouldn't be deleted */
#define EXP_PATCH_MANIP_OK_TO_DELETE_OLD 0x2000
																					/* This bit is used to indicate that the
																					Old file is not being retained for file sharing reasons.
																					Only used with a Change patch in conjunction with
																					renaming AND with a delete patch */
#define EXP_PATCH_MANIP_TYPE_SET	 0x4000
																					/* Indicates that the FileManipType field is valid */
#define EXP_PATCH_MANIP_PRESERVELINKS_SEMANTICS 0x8000
																					/* set in phase 1 to indicate the use of the alternative PRESERVELINKS semantics */
#define EXP_PATCH_MANIP_SEMANTICS_SET 0x10000
#define EXP_PATCH_MANIP_TREAT_AS_FILE 0x20000 /* set to indicate the use of updatelinks processing */
#define EXP_PATCH_MANIP_USING_TEMPDIR 0x40000 /* set to indicate the use of the TEMPDIR */
#define EXP_PATCH_MANIP_OLDISLINK 0x80000
#define EXP_PATCH_MANIP_RESILIENT 0x100000
#define EXP_PATCH_MANIP_SELFREGWARNING 0x200000


/* if Delay is allowed, we will use phase 1 (failure causes undo), 
		followed by phase 3 (which isn't allowed to fail) */

/* if No Delay is allowed, will use all four phases in order.  
		Any failures (except in phase 4) will cause previous 
		operations to be undone */

/* ApplyFlags */
#define EXP_PATCH_APPLY_BACKUP 0x1
#define EXP_PATCH_APPLY_ERRORFILE 0x2
#define EXP_PATCH_APPLY_ONEFILEONLY 0x4
#define EXP_PATCH_APPLY_VERIFYONLY 0x8
#define EXP_PATCH_APPLY_CONFIRMSYSTEMS 0x10
#define EXP_PATCH_APPLY_IGNOREMISSING 0x20
#define EXP_PATCH_APPLY_KEEPTEMP 0x40
#define EXP_PATCH_APPLY_LISTONLY 0x80
#define EXP_PATCH_APPLY_MESSAGES 0x100
#define EXP_PATCH_APPLY_PATHSEARCH 0x200
#define EXP_PATCH_APPLY_QUIET 0x400
#define EXP_PATCH_APPLY_SUBDIRSEARCH 0x800
#define EXP_PATCH_APPLY_TIMEZONEIGNORE 0x1000
#define EXP_PATCH_APPLY_UNDO 0x2000
#define EXP_PATCH_APPLY_VERBOSE 0x4000
#define EXP_PATCH_APPLY_USERFILEMANIP 0x8000
#define EXP_PATCH_APPLY_FULLPATHDISPLAY 0x10000
#define EXP_PATCH_APPLY_ALLOWDELAY 0x20000
#define EXP_PATCH_APPLY_REMOTE_TMPDIR 0x40000
#define EXP_PATCH_APPLY_RESERVED 0x80000
#define EXP_PATCH_APPLY_FORCEDELAY 0x100000
#define EXP_PATCH_APPLY_FORCENOCHECKTD 0x200000
#define EXP_PATCH_APPLY_FORCEUNDOUTF8 0x400000


/* Callback IDs */
#define EXP_PATCH_WARNING_CALLBACK 0x1
	/* Ptr points to an array of two pointers */
	/* to wide strings (prefix, text) followed */
	/* by a DWORD warning code */
#define EXP_PATCH_ERROR_CALLBACK 0x2
	/* Ptr points to an array of two pointers */
	/* to wide strings (prefix, text) followed */
	/* by a DWORD error code */
#define EXP_PATCH_PROGRESS 0x3
	/* Ptr points to an array of two DWORDs, */
	/* Global Progress, Local Progress */
#define EXP_PATCH_FILE_START 0x4
	/* Ptr points to a wide string containing the entry name */
#define EXP_PATCH_FILE_FINISH 0x5
	/* Ptr is NULL */
#define EXP_PATCH_INFO 0x6
	/* Ptr points to a wide string containing the informational message */
#define EXP_PATCH_COMMENT 0x7
	/* Ptr points to a wide string containing the comment */
#define EXP_PATCH_COPYRIGHT 0x8
	/* Ptr points to a wide string containing the copyright message */
#define EXP_PATCH_INVALID_PATCH_FILE 0x9
	/* Ptr is NULL */
#define EXP_PATCH_PASSWORD 0xa
	/* Ptr points to a 256-character wide string buffer into which */
	/* to place the password */
#define EXP_PATCH_INVALID_PASSWORD 0xb
	/* Ptr is NULL */
#define EXP_PATCH_SYSTEM_CONFIRM 0xc
	/* Ptr points to an array of two pointers */
	/* to wide strings (system name, system location) */
#define EXP_PATCH_SYSTEM_PROMPT 0xd
	/* Ptr points to an array of three pointers */
	/* to wide strings (system name, system tag, */
	/* return buffer).  The return buffer is 512 wide */
	/* characters in size. */
#define EXP_PATCH_DELAYED_PATCHING 0xe
	/* Ptr is NULL */
#define EXP_PATCH_SEARCHING 0xf
	/* Ptr is NULL */
#define EXP_PATCH_EXTENDED_HEADER 0x10
	/* Ptr points to an array of three pointers */
	/* (ExaPatchExtendedHeader, ExaPatchApplyFileHeaderInfo, */
	/* ExaPatchApplyFileEntryInfo).  The third pointer */
	/* will always be NULL for HEADER-type blocks */
#define EXP_PATCH_FILE_MANIPULATION 0x11
	/* Ptr points to an ExaPatchApplyFileManipulation structure */
#define EXP_PATCH_FILE_STATS 0x12
	/* Ptr points to an array of QWORDs that contain the patch header stats*/
#define EXP_PATCH_PROGRESS_COMMIT 0x13
	/* Ptr points to a single DWORD, */
	/* Global Progress of the file commits */
#define EXP_PATCH_UNDO_MARK 0x14
	/* Ptr is NULL */
	/* Last point of patch process where UNDO can succeed */
#define EXP_PATCH_NUM_ENTRIES 0x15
	/* Ptr points to a single QWORD */
	/* Number of entries in the patch */
#define EXP_PATCH_UNDOING_PATCH 0x16
	/* Ptr is NULL */
	/* An error occurred during the commit phase and UNDO is on */

/* Callback return values */
#define EXP_CALLBACK_OK 0x0
#define EXP_CALLBACK_ABORT 0x1
#define EXP_CALLBACK_CONTINUE 0x2 /* only used with EXP_PATCH_SYSTEM_CONFIRM, */
		/* EXP_PATCH_EXTENDED_HEADER */
		/* and EXP_PATCH_FILE_MANIPULATION */

/* WhatToCheck Flags */
#define EXP_APPLY_CHECK_TIME 0x1
#define EXP_APPLY_CHECK_IGNORETIMEZONE 0x2
#define EXP_APPLY_CHECK_CHECKSUM 0x4
#define EXP_APPLY_CHECK_ATTRIB 0x8
#define EXP_APPLY_CHECK_SIZE 0x10
#define EXP_APPLY_CHECK_PROCESSLINKS 0x20

/* ROUTINES */
/* 	Non-handle-based routines (user must synchronize) */
INT /* ErrCode */
	EXP_DLLIMPORT
	ExaPatchApplyOpenFileArrayAsStreamA(
	ExaPatchStream ** FileStreamPtr,
	UCHAR ** FileNameArray,
	DWORD NumFiles,
	DWORD OpenFlags,
	QWORD * SizeArray	/* may be NULL for read-only files */
	);

INT /* ErrCode */
	EXP_DLLIMPORT
	ExaPatchApplyOpenFileArrayAsStreamW(
	ExaPatchStream ** FileStreamPtr,
	WCHAR ** FileNameArray,
	DWORD NumFiles,
	DWORD OpenFlags,
	QWORD * SizeArray /* may be NULL for read-only files */
	);
/* MISRA C 2012 [5.1, 5.2, 5.4, 5.5]: 35-character identifier clash is necessary for legacy reasons */
INT /* ErrCode */
	EXP_DLLIMPORT
	ExaPatchApplyCloseStream(
	ExaPatchStream * FileStream
	);

# ifdef EXAPATCH_DETAILED_APPLY_API_SUPPORT
INT /* ErrCode */
	EXP_DLLIMPORT
	ExaPatchApplyFreeParsedEntry(
	ExaPatchApplyFileEntryInfo * Entry
	);

INT /* ErrCode */
	EXP_DLLIMPORT
	ExaPatchApplyFreeParsedHeader(
	ExaPatchApplyFileHeaderInfo * HeaderPtr
	);

INT /* ErrCode */
	EXP_DLLIMPORT
	ExaPatchApplyVerifyFile(
	WCHAR * FullPath,
	ExaPatchFileInfo * InfoPtr,
	DWORD dwIndex,
	DWORD dwOldOrNew,
	DWORD dwNumBH,
	ExaPatchByteHandling * BHPtr,
	DWORD dwWhatToCheck
	);
# endif

/* 	Handle-based routines (synchronized) */
PLATWORD /* Handle */
	EXP_DLLIMPORT
	ExaPatchApplyOpen( void );

INT /* ErrCode */
	EXP_DLLIMPORT
	ExaPatchApplyClose( PLATWORD Handle );

INT /* ErrCode */
	EXP_DLLIMPORT
	ExaPatchApplySetBuffering( PLATWORD Handle, QWORD qwBreak, BOOL bAmt );
	/* if bAmt is nonzero, qwBreak is interpreted as an amount, if bAmt is zero, it is taken to be an integral percentage of system memory */

# ifdef EXAPATCH_DETAILED_APPLY_API_SUPPORT
INT /* ErrCode */
	EXP_DLLIMPORT
	ExaPatchApplyStartFile( 
		PLATWORD Handle,
		ExaPatchStream * FileToParse,
		ExaPatchApplyFileHeaderInfo * HeaderPtr,
		DWORD ApplyFlags,
		DWORD ApplyFlagsToForce,
		INT (CALLBACK *ProgressCallBack)(DWORD ID, 
			LPVOID Ptr, PLATWORD Handle),
		PLATWORD CallbackHandle
		);

INT /* ErrCode */
	EXP_DLLIMPORT
	ExaPatchApplyFinishFile( 
		PLATWORD Handle,
		ExaPatchApplyFileHeaderInfo * HeaderPtr,
		DWORD SuccessFlag,
		INT (CALLBACK *ProgressCallBack)(DWORD ID, 
			LPVOID Ptr, PLATWORD Handle),
		PLATWORD CallbackHandle
		);
# endif

INT /* ErrCode */
	EXP_DLLIMPORT
	ExaPatchApplyDoEntireFile( 
		PLATWORD Handle,
		ExaPatchStream * FileToApply,
		WCHAR * ApplyDirectory,
		WCHAR * BackupDirectory,
		WCHAR * SingleFile,
		WCHAR * DrivesToCheck,
		DWORD ApplyFlags,
		DWORD ApplyFlagsToForce,
		INT (CALLBACK *ProgressCallBack)(DWORD ID, 
			LPVOID Ptr, PLATWORD Handle),
		PLATWORD CallbackHandle
		);
/* MISRA C 2012 [1.1, 1.2]: use of non-ANSI keyword when needed under Windows (CALLBACK includes __stdcall) */
# ifdef EXAPATCH_CONTAINER_SUPPORT
INT /* ErrCode */
	EXP_DLLIMPORT
	ExaPatchApplySelectPatch(
		PLATWORD Handle,
		DWORD dwIndex );
# endif
# ifdef EXAPATCH_DETAILED_APPLY_API_SUPPORT
INT /* ErrCode */
	EXP_DLLIMPORT
	ExaPatchApplyParseEntryInfo( 
		PLATWORD Handle,
		ExaPatchStream * FileToParse,
		ExaPatchApplyFileHeaderInfo * HeaderPtr,
		ExaPatchApplyFileEntryInfo * EntryPtr
		);

INT /* ErrCode */
	EXP_DLLIMPORT
	ExaPatchApplyDoEntry( 
		PLATWORD Handle,
		ExaPatchStream * FileToApply,
		ExaPatchApplyFileHeaderInfo * HeaderPtr,
		INT (CALLBACK *ProgressCallBack)(DWORD ID, 
			LPVOID Ptr, PLATWORD Handle),
		PLATWORD CallbackHandle
		);

INT /* ErrCode */
	EXP_DLLIMPORT
	ExaPatchApplyStartEntry( 
		PLATWORD Handle,
    ExaPatchStream * FileToApply,
		ExaPatchApplyFileHeaderInfo * HeaderPtr,
		ExaPatchApplyFileEntryInfo * EntryPtr,
		INT (CALLBACK *ProgressCallBack)(DWORD ID, 
			LPVOID Ptr, PLATWORD Handle),
		PLATWORD CallbackHandle
		);

INT /* ErrCode */
	EXP_DLLIMPORT
	ExaPatchApplyFinishEntry( 
		PLATWORD Handle,
    ExaPatchStream * FileToApply,
		ExaPatchApplyFileHeaderInfo * HeaderPtr,
		ExaPatchApplyFileEntryInfo * EntryPtr,
		INT (CALLBACK *ProgressCallBack)(DWORD ID, 
			LPVOID Ptr, PLATWORD Handle),
		PLATWORD CallbackHandle,
		DWORD SuccessFlag
		);
# endif
INT /* ErrCode */
	EXP_DLLIMPORT
	ExaPatchApplyDoEntryRaw( 
		PLATWORD Handle,
		ExaPatchStream * FileToApply,
		ExaPatchApplyFileHeaderInfo * HeaderPtr,
# ifdef ATTOPATCH
		const ExaPatchApplyFileEntryInfo * EntryPtr,
# else
		ExaPatchApplyFileEntryInfo * EntryPtr,
# endif
		ExaPatchStream * OldStream,
		ExaPatchStream * NewStream,
		INT (CALLBACK *ProgressCallBack)(DWORD ID, 
			LPVOID Ptr, PLATWORD Handle),
		PLATWORD CallbackHandle
		);

# ifdef EXAPATCH_SPECIALSTREAM_SUPPORT
INT /* ErrCode */
	EXP_DLLIMPORT
	ExaPatchApplySupplyBuffer(
		PLATWORD Handle,
		void * Buffer,
		DWORD dwBufferSize
		);
# endif

# ifdef EXAPATCH_TEMPDIR_SUPPORT
INT /* ErrCode */
	EXP_DLLIMPORT
	ExaPatchApplySetTempDir(
		PLATWORD Handle,
		WCHAR * TempDir
		);
# endif
/* New in version 8.45 - API 2.00 */
DWORD /* version DWORD - high word is apply API version, low word is library version
					each version has high byte = major version, low byte = minor version */
	EXP_DLLIMPORT
	ExaPatchApplyGetVersion(
	void );

/* New in version 8.46 - API 2.01 */
int /* ErrCode */
	EXP_DLLIMPORT
	ExaPatchApplySetInPlaceParms( PWORD Handle, 
		DWORD dwBlockSize, /* 64K max - must be a multiple of patch file block size; set bit 0 to require a rollback patch */
		DWORD dwWindowSize ); /* will be adjusted down to be a multiple of dwBlockSize; must be at least patch file window size */
	/* applies until taken off with (*,0,0) */

/* New in version 8.46 - API 2.01 */
int /* ErrCode */
	EXP_DLLIMPORT
	ExaPatchApplySetInPlaceStart( PWORD Handle, QWORD qwOldStart, QWORD qwNewEnd );
	/* applies until used on an entry */

/* New in version 8.46 - API 2.01 */
int /* ErrCode */
	EXP_DLLIMPORT
	ExaPatchApplyVerifyInPlaceRaw( PWORD Handle, ExaPatchStream * PatchFile, ExaPatchStream * VerifyFile, QWORD * pqwBoundary );
	/*	if EXAPATCH_SUCCESS is returned, then a (possibly hybrid) valid stream was encountered. In that case,
		*pqwBoundary is set to indicate the extent to which updating has occurred.
		0 => entirely OLD file
		the size of the NEW file or larger => entirely NEW file.
		Otherwise, the stream is a hybrid stream and pqwBoundary is suitable to be passed as either qwOldStart
		or qwNewEnd, depending on the backup block semantics
	*/

# ifndef ATTOPATCH
/* New in version 8.64 - API 2.02 */
INT /* ErrCode */
	EXP_DLLIMPORT
	ExaPatchApplySetErrorFilename(
		PLATWORD Handle,
		WCHAR * ErrorFile
		);
# endif

/*-----------------------------------------------------------------------*\
    C++ name mangling prevention -- end of block
\*-----------------------------------------------------------------------*/
# ifdef __cplusplus
  }
# endif /*__cplusplus */

# endif
