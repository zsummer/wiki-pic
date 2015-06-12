#ifdef WIN32
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
#include <windows.h>
#include <DbgHelp.h>
#include <string>
#pragma comment(lib, "Dbghelp")
#else
#include <execinfo.h>
#include <unistd.h>
#endif
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

void tracebackHandler()
{
#ifdef WIN32
    DWORD  error;
    HANDLE hProcess;

    SymSetOptions(SYMOPT_UNDNAME | SYMOPT_DEFERRED_LOADS);

    hProcess = GetCurrentProcess();

    if (!SymInitialize(hProcess, NULL, TRUE))
    {
        // SymInitialize failed
        error = GetLastError();
        printf("SymInitialize returned error : %d\n", error);
        return ;
    }

    typedef USHORT(WINAPI *CaptureStackBackTraceType)(__in ULONG, __in ULONG, __out PVOID*, __out_opt PULONG);
    CaptureStackBackTraceType capture = (CaptureStackBackTraceType)(GetProcAddress(LoadLibraryA("kernel32.dll"), "RtlCaptureStackBackTrace"));
    if (capture == NULL) return ;
    const int stackMax = 128;
    void* trace[stackMax];
    int count = (capture)(0, stackMax, trace, NULL);
    //    int count = (CaptureStackBackTrace)(0, stackMax, trace, NULL);
    for (int i = 0; i < count; i++)
    {
        ULONG64 buffer[(sizeof(SYMBOL_INFO)+MAX_SYM_NAME*sizeof(TCHAR)+sizeof(ULONG64)-1) / sizeof(ULONG64)];
        PSYMBOL_INFO pSymbol = (PSYMBOL_INFO)buffer;
        pSymbol->SizeOfStruct = sizeof(SYMBOL_INFO);
        pSymbol->MaxNameLen = MAX_SYM_NAME;
        std::string stack;
        DWORD64 dwDisplacement = 0;

        if (SymFromAddr(hProcess, (DWORD64)trace[i], &dwDisplacement, pSymbol))
        {
            int t = GetLastError();
            stack += pSymbol->Name;
            stack += "\n";
        }
        else
        {
            int t = GetLastError();
            continue;
        }

        IMAGEHLP_LINE64 lineInfo = { sizeof(IMAGEHLP_LINE64) };
        DWORD dwLineDisplacement;


        if (SymGetLineFromAddr64(hProcess, (DWORD64)trace[i], &dwLineDisplacement, &lineInfo))
        {
            char buf[1024] = { 0 };
            sprintf(buf, "    file:%s\n    line %u\n", lineInfo.FileName, lineInfo.LineNumber);
            stack += buf;
        }
        std::cout << stack << std::endl;
    }
#else
    void *stack[200];
    size_t size = backtrace(stack, 200);
    char **stackSymbol = backtrace_symbols(stack, size);
    for (size_t i = 0; i < size && stackSymbol != NULL; i++)
    {
        std::cout << "bt[" << i << "] " << stackSymbol[i] << std::endl;
    }
    free(stackSymbol);
#endif
}


void test(int a)
{
    tracebackHandler();
}
int main(int argc, char *argv[])
{
    test(1);

    return 0;
}

/*
g++ stack.cpp -g -O0
gdb info line * 0x40000000
google coredumper
*/