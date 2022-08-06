/*-------------------------------------------------------------------------*\
|                                                                           |
|  FILE: EXPFMT.H                                                           |
|                                                                           |
|                                                                           |
|  RTPatch Server Formatting/Parsing Helper Routines                        |
|                                                                           |
|                                                                           |
|  (C) Copyright Pocket Soft, Inc. 2001-2015.  All Rights Reserved.         |
|                                                                           |
\*-------------------------------------------------------------------------*/
# ifndef EXAPATCH_FMT_INCLUDED

# define EXAPATCH_FMT_INCLUDED

# include "exputils.h"

# define EXAPATCH_MAGIC 0x584b
# define EXAPATCH_VERSION 0x101
# define EXAPATCH_CONTAINER_MAGIC 0x594b

# define EXAPATCH_EOF_TYPE 0
# define EXAPATCH_ADC_TYPE 1
# define EXAPATCH_TEMP_TYPE 2
# define EXAPATCH_HISTORY_TYPE 3

/* FILE_FORMAT_CODE */
/* Header offsets */
# define EXAPATCH_FIXED_HDR_SIZE 0x58
# define EXAPATCH_MAGIC_OFFSET 0x0
# define EXAPATCH_FMT_OFFSET 0x2
# define EXAPATCH_ATTRIB_OFFSET 0x4
# define EXAPATCH_BASE_HDR_OPT_OFFSET 0x6
# define EXAPATCH_GLOBAL_FLAGS_OFFSET 0x8
# define EXAPATCH_FILE_FLAGS_OFFSET 0xc
# define EXAPATCH_DISKSPACE_OFFSET 0x10
# define EXAPATCH_NUM_ENTRIES_OFFSET 0x40
# define EXAPATCH_OPT_HDR_SIZE_OFFSET 0x48
# define EXAPATCH_BASE_HDR_SIZE_OFFSET 0x50
/* System Size Indices */
# define EXAPATCH_SYSTEM_OLD_DISK 0
# define EXAPATCH_SYSTEM_NEW_DISK 1
# define EXAPATCH_SYSTEM_MAX_DISK 2
# define EXAPATCH_SYSTEM_BIG_DISK 3
# define EXAPATCH_SYSTEM_OLD_NUM 4
# define EXAPATCH_SYSTEM_NEW_NUM 5

/* maximum sizes */
# define MAX_EA_SIZE 0x2000000
# define MAX_EH_SIZE 0x2000000
# define MAX_SCRIPT_SIZE 0x2000000
# define MAX_SYS_BASE 0x10000
# define MAX_FLAG_VAL 0x80
# define MAX_NUM_SYS 0x100000
# define MAX_NUM_SUBDIR 0x100000
# define MAX_NUM_COMMENTS 0x100000
# define MAX_NUM_BH 0x1000000
# define MAX_GRP_FILES 0x100000

/* expfmt.c */
# ifndef ATTOPATCH
INT	GetVarIndex( ExaPatchStream * Stream, QWORD * IndexPtr );
INT PutVarIndex( ExaPatchStream * Stream, QWORD Index );
INT GetVarStr( ExaPatchStream * Stream, wchar_t ** PtrPtr );
INT PutVarStr( ExaPatchStream * Stream, wchar_t * Ptr );
# endif
/*
INT IncQword( ExaPatchStream * Stream, QWORD Pos, QWORD Increment );
INT IncDword( ExaPatchStream * Stream, QWORD Pos, DWORD Increment );
INT SetQword( ExaPatchStream * Stream, QWORD Pos, QWORD Amount );
INT SetDword( ExaPatchStream * Stream, QWORD Pos, DWORD Amount ); 
*/
INT PutWord( ExaPatchStream * Stream, USHRT Amount );
INT PutDword( ExaPatchStream * Stream, DWORD Amount );
INT PutQword( ExaPatchStream * Stream, QWORD Amount );
INT GetWord( ExaPatchStream * Stream, USHRT * AmtPtr );
INT GetDword( ExaPatchStream * Stream, DWORD * AmtPtr );
INT GetQword( ExaPatchStream * Stream, QWORD * AmtPtr );
INT GetBytes( ExaPatchStream * Stream, void * Ptr, DWORD Size );
INT PutBytes( ExaPatchStream * Stream, const void * Ptr, DWORD Size );

/* expcrypt.c */
INT CrunchPW( wchar_t * Password, QWORD * Hash1, QWORD * Hash2 );
INT UsePW( void * Buffer, QWORD * Hash1, QWORD * Hash2 );
INT CryptPW( void * Buffer, QWORD * Hash1, QWORD * Hash2 );

# endif /* EXAPATCH_FMT_INCLUDED */
