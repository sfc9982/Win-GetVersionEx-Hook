#pragma warning(disable : 4996)

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

int __cdecl main()
{
	OSVERSIONINFO osvi;

    ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

    GetVersionEx(&osvi);

    printf("Windows Version: %ld.%ld.%ld\n", osvi.dwMajorVersion, osvi.dwMinorVersion, osvi.dwBuildNumber);
	
    return 0;
}
//
///////////////////////////////////////////////////////////////// End of File.
