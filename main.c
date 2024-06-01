#include <Windows.h>

#include "global.h"
#include "map.h"

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpszCmdLine,
                   int nCmdShow) {

    g_hInstance = hInstance;
    (VOID)hPrevInstance;
    (VOID)lpszCmdLine;
    (VOID)nCmdShow;

    Map *pMap = ReadMapFromFile(L"map/map-site.txt");
    for (BYTE i = 0; i < pMap->bSiteCount; i++) {
        MapSite *pMapSite = pMap->arrpMapSites[i];
        wprintf(L"SITE %d has %d CONNECTIONS:", i, pMapSite->bConnectionCount);
        for (BYTE j = 0; j < pMapSite->bConnectionCount; j++) {
            wprintf(L" %d", pMapSite->arrbConnections[j]);
        }

        wprintf(L"\n");
    }
    FreeMap(pMap);

    return 0;
}
