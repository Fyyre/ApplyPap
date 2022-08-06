//
// ApplyPAP Utilities by Fyyre
//

# include "expapply.h"
# include <stdio.h>
# include <stdlib.h>

#pragma comment(lib, "expapply.lib")

int CALLBACK FeedBack(DWORD ID, LPVOID Ptr, PLATWORD Handle);
DWORD GlobalProgress = 0;
DWORD LocalProgress;

int main(int argn, char* argv[])
{
	PLATWORD ApplyChannel;
	ExaPatchStream* PatchFile = NULL;
	wchar_t ApplyDir[260];
	int Code;

	if (argn != 3)
	{
		printf("ApplyPap by Fyyre\n");
		return(-1);
	}

	ExaPatchApplyOpenFileArrayAsStreamA(&PatchFile, (unsigned char**)&argv[1], 1, EXP_OPEN_READONLY, NULL);
	ApplyChannel = ExaPatchApplyOpen();
	ExaPatchApplySetBuffering(ApplyChannel, 25, FALSE);

	if (ApplyChannel == 0) return(-1);

	if (0 == MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, argv[2], -1, ApplyDir, 260))
	{
		Code = ExaPatchApplyDoEntireFile(ApplyChannel,
			PatchFile,
			ApplyDir,
			NULL,
			NULL,
			NULL,
			0,
			EXP_PATCH_APPLY_PATHSEARCH, /* Disable PATH searching (long) */
			&FeedBack,
			0);
	}
	else
	{
		Code = ExaPatchApplyDoEntireFile(ApplyChannel,
			PatchFile,
			ApplyDir,
			NULL,
			NULL,
			NULL,
			0,
			EXP_PATCH_APPLY_PATHSEARCH, /* Disable PATH searching (long) */
			&FeedBack,
			0);
	}

	if (PatchFile)
	{
		ExaPatchApplyCloseStream(PatchFile);
		PatchFile = NULL;
	}

	ExaPatchApplyClose(ApplyChannel);
	return(Code);
}

int CALLBACK FeedBack(DWORD ID, LPVOID Ptr, PLATWORD Handle)
{
	wchar_t* wcPtr;
	wchar_t** wcPtrPtr;
	DWORD* dwPtr;
	DWORD TempLocal, TempGlobal;

	switch (ID)
	{
	case EXP_PATCH_PROGRESS:
		dwPtr = (DWORD*)Ptr;
		TempGlobal = (100 * dwPtr[0]) >> 15;
		TempLocal = (100 * dwPtr[1]) >> 15;
		if ((TempGlobal != GlobalProgress) || (TempLocal != LocalProgress))
		{
			GlobalProgress = TempGlobal;
			LocalProgress = TempLocal;
			printf("Progress: %ld%% - %ld%%\r", (long)GlobalProgress, (long)LocalProgress);
		}
		break;
	case EXP_PATCH_FILE_START:
		wcPtr = (wchar_t*)Ptr;
		LocalProgress = 0xffffffff;
		printf("Start: %ls\n", wcPtr);
		break;
	case EXP_PATCH_FILE_FINISH:
		printf("\nFinish\n");
		break;
	case EXP_PATCH_INFO:
		wcPtr = (wchar_t*)Ptr;
		printf("Info: %ls\n", wcPtr);
		break;
	case EXP_PATCH_COMMENT:
		wcPtr = (wchar_t*)Ptr;
		printf("Comment: %ls\n", wcPtr);
		break;
	case EXP_PATCH_COPYRIGHT:
		wcPtr = (wchar_t*)Ptr;
		printf("Copyright: %ls\n", wcPtr);
		break;
	case EXP_PATCH_PASSWORD:
		wcPtr = (wchar_t*)Ptr;
		printf("Enter password:");
		_getws_s(wcPtr, 512);
		break;
	case EXP_PATCH_INVALID_PASSWORD:
		printf("Invalid Password\n");
		break;
	case EXP_PATCH_SYSTEM_CONFIRM:
		wcPtrPtr = (wchar_t**)Ptr;
		printf("System Confirmation: %ls is located at %ls?\n", wcPtrPtr[0], wcPtrPtr[1]);
		break;
	case EXP_PATCH_SYSTEM_PROMPT:
		wcPtrPtr = (wchar_t**)Ptr;
		wcPtr = wcPtrPtr[2];
		printf("Enter location of system %ls:", wcPtrPtr[0]);
		_getws_s(wcPtr, 512);
		break;
	case EXP_PATCH_DELAYED_PATCHING:
		printf("Delayed Patching Used\n");
		break;
	case EXP_PATCH_SEARCHING:
		printf("Searching for Systems to Patch...\n");
		break;
	case EXP_PATCH_EXTENDED_HEADER:
		return EXP_CALLBACK_CONTINUE;
		break;
	case EXP_PATCH_FILE_MANIPULATION:
		return EXP_CALLBACK_CONTINUE;
		break;
	}
	return(EXP_CALLBACK_OK);
}
