#include <Windows.h>

#include "global.h"
#include "fileutil.h"
#include "strutil.h"

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpszCmdLine,
                   int nCmdShow) {

    g_hInstance = hInstance;
    (VOID)hPrevInstance;
    (VOID)lpszCmdLine;
    (VOID)nCmdShow;

    LPSTR* arrlpszLines = ReadFileLines(L"map/map-site.txt");
    if (arrlpszLines == NULL) {
        return 1;
    }

    for (int i = 0; arrlpszLines[i] != NULL; i++) {
        LPWSTR lpszLine = U8StringToWide(arrlpszLines[i]);
        if (lpszLine == NULL) {
            return 1;
        }

        MessageBoxW(NULL, lpszLine, L"Line", MB_OK);
        HeapFree(GetProcessHeap(), 0, lpszLine);
    }

    FreeFileLines(arrlpszLines);
    return 0;
}
