#include <Windows.h>

#include "global.h"

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpszCmdLine,
                   int nCmdShow) {

    g_hInstance = hInstance;
    (VOID)hPrevInstance;
    (VOID)lpszCmdLine;
    (VOID)nCmdShow;

    return 0;
}
