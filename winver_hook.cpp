//////////////////////////////////////////////////////////////////////////////
//
//  Detours Test Program (simple.cpp of simple.dll)
//
//  Microsoft Research Detours Package
//
//  Copyright (c) Microsoft Corporation.  All rights reserved.
//
//  This DLL will detour the Windows GetVersionEx API so that TimedSleep function
//  gets called instead.  W10GetVersionEx records the before and after times, and
//  calls the real GetVersionEx API through the TrueGetVersionEx function pointer.
//
#pragma warning(disable : 4996)

#include <stdio.h>
#include <windows.h>
#include "detours.h"

static BOOL (WINAPI * TrueGetVersionEx)(OSVERSIONINFO *osvi) = GetVersionEx;

BOOL WINAPI W10GetVersionEx(OSVERSIONINFO *osvi)
{
    BOOL ret = TrueGetVersionEx(osvi);

	osvi->dwMajorVersion = 10;
	osvi->dwMinorVersion = 0;
	osvi->dwBuildNumber  = 19045;
	
    return ret;
}

BOOL WINAPI DllMain(HINSTANCE hinst, DWORD dwReason, LPVOID reserved)
{
    LONG error;
    (void)hinst;
    (void)reserved;

    if (DetourIsHelperProcess()) {
        return TRUE;
    }

    if (dwReason == DLL_PROCESS_ATTACH) {
        DetourRestoreAfterWith();

        printf("simple" DETOURS_STRINGIFY(DETOURS_BITS) ".dll:"
               " Starting.\n");
        fflush(stdout);

        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourAttach(&(PVOID&)TrueGetVersionEx, W10GetVersionEx);
        error = DetourTransactionCommit();

        if (error == NO_ERROR) {
            printf("simple" DETOURS_STRINGIFY(DETOURS_BITS) ".dll:"
                   " Detoured GetVersionEx().\n");
        }
        else {
            printf("simple" DETOURS_STRINGIFY(DETOURS_BITS) ".dll:"
                   " Error detouring GetVersionEx(): %ld\n", error);
        }
    }
    else if (dwReason == DLL_PROCESS_DETACH) {
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourDetach(&(PVOID&)TrueGetVersionEx, W10GetVersionEx);
        error = DetourTransactionCommit();

        printf("simple" DETOURS_STRINGIFY(DETOURS_BITS) ".dll:"
               " Removed GetVersionEx() (result=%s).\n", error ? "Fail" : "Success");
        fflush(stdout);
    }
    return TRUE;
}

//
///////////////////////////////////////////////////////////////// End of File.
