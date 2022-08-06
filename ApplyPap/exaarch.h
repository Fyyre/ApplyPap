/*-------------------------------------------------------------------------*\
|                                                                           |
|  FILE: EXAARCH.H                                                          |
|                                                                           |
|                                                                           |
|  RTPatch Server Archive Handling Header File                              |
|                                                                           |
|                                                                           |
|  (C) Copyright Pocket Soft, Inc. 2013.  All Rights Reserved.              |
|                                                                           |
\*-------------------------------------------------------------------------*/

# ifndef EXAARCH_INCLUDED
# define EXAARCH_INCLUDED

# include "exafeature.h"
# define EXAPATCH_INTERNAL_CODE
# include "exaplat.h"
# ifdef _WIN32
# include <windows.h>
# else
# include <dlfcn.h>
# include <unistd.h>
# include <time.h>
# endif

# define ARCH_START_BLOCKID_LOCAL 0x6241
# define ARCH_START2_BLOCKID_LOCAL 0x6244
# define ARCH_START3_BLOCKID_LOCAL 0x6245
# define ARCH_SUBDIR_BLOCKID_LOCAL 0x6243
# define ARCH_END_BLOCKID_LOCAL 0x6242
int ExaIsArchive( wchar_t * szFile );
int ExaExpand(wchar_t * szFile, int nArchType, wchar_t * szDir);
int ExaCompress(wchar_t * szDir, int nArchType, wchar_t * szFile);
int ExaArchSetParameters(wchar_t * szDir, int nArchType, wchar_t * szFile);
int ExaSetArchDefaults(int nArchType, int nVersion, int nLevel );
int ExaExpandExact(wchar_t * pFile, int nArchType, wchar_t * pDir );
int ExaCompressExact(wchar_t * pDir, int nArchType, wchar_t * pFile );
int ExaGetExactType( int nArchType, DWORD * pType );

#define EXAARCH_EXACTTYPE_NONE 0
#define EXAARCH_EXACTTYPE_PARAMETERS 1
#define EXAARCH_EXACTTYPE_INTERMEDIATE 2

# define EXAARCH_PARAMETERS_NOT_FOUND -5
# define EXAARCH_MEMORY_ERROR -4
# define EXAARCH_ACCESS_ERROR -3
# define EXAARCH_EXPAND_ERROR -2
# define EXAARCH_COMPRESS_ERROR -1
# define EXAARCH_NONE 0
# define EXAARCH_SUCCESS 0
# define EXAARCH_ZIP 1
# define EXAARCH_TAR 2
# define EXAARCH_TGZ 3
# define EXAARCH_TBZ 4
# define EXAARCH_7Z 5

# endif	/* !EXAARCH_INCLUDED */
