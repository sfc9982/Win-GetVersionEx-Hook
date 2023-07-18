// ReSharper disable CppDeprecatedEntity
#pragma warning(disable : 4996)

#include <cstdio>
#include <iostream>
#include <windows.h>

#include "Shlwapi.h"
#pragma comment(lib, "Shlwapi.lib")

int __cdecl main() {
    OSVERSIONINFO osvi;

    ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

    GetVersionExW(&osvi);
    DWORD ubr      = 0;
    DWORD ubr_size = sizeof(ubr);
    SHRegGetValue(
            HKEY_LOCAL_MACHINE,
            L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion",
            L"UBR",
            SRRF_RT_REG_DWORD,
            nullptr,
            &ubr,
            &ubr_size);


    printf("Windows Version: %ld.%ld.%ld.%ld\n", osvi.dwMajorVersion, osvi.dwMinorVersion, osvi.dwBuildNumber, ubr);

    return 0;
}
