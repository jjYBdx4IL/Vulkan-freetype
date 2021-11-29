#pragma once

#if defined(_DEBUG) && defined(_WIN32)

#include <windows.h>
#include <strsafe.h>

#include <stdio.h>
#include <malloc.h>


#define DBGL(kwszDebugFormatString, ...) _DBGPRINT(__FUNCTIONW__, __LINE__, kwszDebugFormatString, __VA_ARGS__)
#define DBG(kwszDebugFormatString, ...) _DBGPRINT(__FUNCTION__, __LINE__, kwszDebugFormatString, __VA_ARGS__)

VOID _DBGPRINT(LPCWSTR kwszFunction, INT iLineNumber, LPCWSTR kwszDebugFormatString, ...) \
{
    INT cbFormatString = 0;
    va_list args;
    PWCHAR wszDebugString = NULL;
    size_t st_Offset = 0;

    va_start(args, kwszDebugFormatString);

    cbFormatString = _scwprintf(L"[%s:%d] ", kwszFunction, iLineNumber) * sizeof(WCHAR);
    cbFormatString += _vscwprintf(kwszDebugFormatString, args) * sizeof(WCHAR) + 2;

    /* Depending on the size of the format string, allocate space on the stack or the heap. */
    wszDebugString = (PWCHAR)_malloca(cbFormatString);

    /* Populate the buffer with the contents of the format string. */
    StringCbPrintfW(wszDebugString, cbFormatString, L"[%s:%d] ", kwszFunction, iLineNumber);
    StringCbLengthW(wszDebugString, cbFormatString, &st_Offset);
    StringCbVPrintfW(&wszDebugString[st_Offset / sizeof(WCHAR)], cbFormatString - st_Offset, kwszDebugFormatString, args);

    OutputDebugStringW(wszDebugString);

    _freea(wszDebugString);
    va_end(args);
}
VOID _DBGPRINT(LPCSTR kwszFunction, INT iLineNumber, LPCSTR kwszDebugFormatString, ...) \
{
    INT cbFormatString = 0;
    va_list args;
    PCHAR wszDebugString = NULL;
    size_t st_Offset = 0;

    va_start(args, kwszDebugFormatString);

    cbFormatString = _scprintf("[%s:%d] ", kwszFunction, iLineNumber) * sizeof(WCHAR);
    cbFormatString += _vscprintf(kwszDebugFormatString, args) * sizeof(WCHAR) + 2;

    /* Depending on the size of the format string, allocate space on the stack or the heap. */
    wszDebugString = (PCHAR)_malloca(cbFormatString);

    /* Populate the buffer with the contents of the format string. */
    StringCbPrintf(wszDebugString, cbFormatString, "[%s:%d] ", kwszFunction, iLineNumber);
    StringCbLength(wszDebugString, cbFormatString, &st_Offset);
    StringCbVPrintf(&wszDebugString[st_Offset / sizeof(WCHAR)], cbFormatString - st_Offset, kwszDebugFormatString, args);

    OutputDebugString(wszDebugString);

    _freea(wszDebugString);
    va_end(args);
}

#elif defined(_DEBUG)
#include <stdio.h>
#define DBG(kwszDebugFormatString, ...) sprintf(kwszDebugFormatString, __VA_ARGS__)
#else
#define DBG( kwszDebugFormatString, ... ) ;;
#endif
