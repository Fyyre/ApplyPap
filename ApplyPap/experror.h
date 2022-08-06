/*-------------------------------------------------------------------------*\
|                                                                           |
|  FILE: EXPERROR.H                                                         |
|                                                                           |
|                                                                           |
|  RTPatch Server Build/Apply DLL Error Code Header File                    |
|                                                                           |
|                                                                           |
|  (C) Copyright Pocket Soft, Inc. 2001-2014.  All Rights Reserved.         |
|                                                                           |
\*-------------------------------------------------------------------------*/
# ifndef EXAPATCH_ERRORS_INCLUDED

# define EXAPATCH_ERRORS_INCLUDED

/* CONSTANTS */
/* Error Codes */

# define EXAPATCH_SUCCESS 0
# define EXAPATCH_UNSPECIFIED_ERROR 1
# define EXAPATCH_OUT_OF_MEMORY 2
# define EXAPATCH_READ_FAILED 3
# define EXAPATCH_WRITE_FAILED 4
# define EXAPATCH_DISK_FULL 5
# define EXAPATCH_SEEK_FAILED 6
# define EXAPATCH_OPEN_FAILED 7
# define EXAPATCH_INVALID_PARAMETER 8
# define EXAPATCH_INTERNAL_ERROR 9
# define EXAPATCH_SET_ATTRIB_FAILED 10
# define EXAPATCH_GET_ATTRIB_FAILED 11
# define EXAPATCH_INVALID_HANDLE 12
# define EXAPATCH_BUSY 13
# define EXAPATCH_RESOURCES_UNAVAILABLE 14
# define EXAPATCH_INVALID_PASSWORD 15
# define EXAPATCH_UNEXPECTED_EOF 16
# define EXAPATCH_USER_CANCEL 17
# define EXAPATCH_CHARSET_ERROR 18
# define EXAPATCH_INVALID_FILE_LIST 19
# define EXAPATCH_CORRUPT_PATCH_FILE 20
# define EXAPATCH_INVALID_PATCH_FILE 21
# define EXAPATCH_ENTRY_NOT_FOUND 22
# define EXAPATCH_ENCRYPTION_FAILURE 23
# define EXAPATCH_NOT_HANDLED_BY_USER 24
# define EXAPATCH_FILE_NOT_FOUND 25
# define EXAPATCH_SPAWN_FAILED 26
# define EXAPATCH_CANT_BUILD_TEMPFILE 27
# define EXAPATCH_DELETE_FAILED 28
# define EXAPATCH_RENAME_FAILED 29
# define EXAPATCH_ALREADY_PATCHED 30
# define EXAPATCH_INVALID_FILE_FOUND 31
# define EXAPATCH_FILE_MANIPULATION_FAILED 32
# define EXAPATCH_NOT_SUPPORTED 33
# define EXAPATCH_DEVICE_MAPPING_FAILED 34
# define EXAPATCH_MANDATORY_EH_NOT_HANDLED 35
# define EXAPATCH_INSUFFICIENT_DISK_SPACE 36
# define EXAPATCH_UNABLE_TO_CREATE_DIRECTORY 37
# define EXAPATCH_UNABLE_TO_REMOVE_DIRECTORY 38
# define EXAPATCH_NO_ENTRY_WRITTEN 39
# define EXAPATCH_POST_PATCH_VERIFY_FAILED 40
# define EXAPATCH_MULTITHREADING_ERROR 41
# define EXAPATCH_ADS_ERROR 42
# define EXAPATCH_EA_ERROR 43
# define EXAPATCH_HOOK_ABORT 44
# define EXAPATCH_REGSCRIPT_ERROR 45

# define EXAPATCH_WARNING_FILE_NOT_FOUND 1
# define EXAPATCH_WARNING_FILE_ALREADY_PATCHED 2
# define EXAPATCH_WARNING_SELFREG_FAILED 3
# define EXAPATCH_WARNING_LOCKDIR_DELETE_FAILED 4
# define EXAPATCH_WARNING_LOCKDIR_ADD_FAILED 5
# define EXAPATCH_WARNING_LOCKDIR_PERM_FAILED 6
# define EXAPATCH_WARNING_INVALID_FILE_FOUND 7

# define EXAPATCH_BUILD_WARNING_CAP_EXCEEDED 0x1
# define EXAPATCH_BUILD_WARNING_ARCH_PARMS_NOT_FOUND 0x2

# endif	/* EXAPATCH_ERRORS_INCLUDED */
