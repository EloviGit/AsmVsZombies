#ifndef __SHARED_AVZ_SEH_H__
#define __SHARED_AVZ_SEH_H__

#include "windows.h"
#include <DbgHelp.h>
#include <string>
#include <fstream>

#define _CRT_SECURE_NO_WARNINGS 1


class ASeh {
    static LRESULT CALLBACK SEHWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    static long __stdcall UnhandledExceptionFilter(LPEXCEPTION_POINTERS lpExceptPtr);
    static void DoHandleDebugEvent(LPEXCEPTION_POINTERS lpEP);
    static bool GetLogicalAddress(void* addr, char* szModule, DWORD len, DWORD& section, DWORD& offset);
    static const char* GetFilename(const char* thePath);
    static void ShowErrorDialog(const char* theErrorTitle, const char* theErrorText);
    static bool CheckImageHelp();
    static std::string IntelWalk(PCONTEXT theContext, int theSkipCount);
    static std::string ImageHelpWalk(PCONTEXT theContext, int theSkipCount);

public:
    ASeh();
    ~ASeh();
} inline__aSeh;

#endif
