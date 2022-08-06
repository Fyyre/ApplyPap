/*-------------------------------------------------------------------------*\
|                                                                           |
|  FILE: DFCVFY.H                                                           |
|                                                                           |
|                                                                           |
|  RTPatch Server Verify DLL Application Programming Interface Header File  |
|                                                                           |
|                                                                           |
|  (C) Copyright Pocket Soft, Inc. 2001-2015.  All Rights Reserved.         |
|                                                                           |
\*-------------------------------------------------------------------------*/
# ifndef EXAPATCH_VERIFY_INCLUDED

# define EXAPATCH_VERIFY_INCLUDED
# include "expapply.h"

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


int EXP_DLLIMPORT ExaPatchVerifyFile( wchar_t * FullPath, 
                                     int (CALLBACK *ProgressCallBack)(DWORD,LPVOID,DWORD),
                                     DWORD CallbackHandle );

/*-----------------------------------------------------------------------*\
    C++ name mangling prevention -- end of block
\*-----------------------------------------------------------------------*/
# ifdef __cplusplus
  }
# endif /*__cplusplus */

# endif /* EXAPATCH_VERIFY_INCLUDED */
