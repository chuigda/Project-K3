#include "map.h"

#include "fileutil.h"
#include "strutil.h"

static MapSite* ParseMapSite(LPWSTR lpszLine);
static VOID FreeMapSite(MapSite* pMapSite);

Map* ReadMapFromFile(LPCWSTR lpszFileName) {
    LPSTR* arrlpszLines = ReadFileLines(lpszFileName);
    if (arrlpszLines == NULL) {
        return NULL;
    }

    BYTE bSiteCount = 0;
    for (BYTE i = 0; arrlpszLines[i] != NULL; i++) {
        bSiteCount++;
    }

    Map* pMap = (Map*)HeapAlloc(GetProcessHeap(),
                                HEAP_ZERO_MEMORY,
                                sizeof(Map) + bSiteCount * sizeof(MapSite*));
    if (pMap == NULL) {
        FreeFileLines(arrlpszLines);
        return NULL;
    }

    pMap->bSiteCount = bSiteCount;
    for (BYTE i = 0; i < bSiteCount;) {
        LPWSTR lpszLine = U8StringToWide(arrlpszLines[i]);
        if (lpszLine == NULL) {
            FreeMap(pMap);
            FreeFileLines(arrlpszLines);
            return NULL;
        }

        if (wcslen(lpszLine) == 0) {
            continue;
        }

        MapSite *pMapSite = ParseMapSite(lpszLine);
        if (pMapSite == NULL) {
            FreeMap(pMap);
            FreeFileLines(arrlpszLines);
            return NULL;
        }

        pMap->arrpMapSites[i] = pMapSite;
    }
}

static MapSite* ParseMapSite(LPWSTR lpszLine) {

}

VOID FreeMap(Map* pMap) {
    for (BYTE i = 0; i < pMap->bSiteCount; i++) {
        if (pMap->arrpMapSites[i]) {
            FreeMapSite(pMap->arrpMapSites[i]);
        }
    }

    HeapFree(GetProcessHeap(), 0, pMap);
}

static VOID FreeMapSite(MapSite* pMapSite) {
    HeapFree(GetProcessHeap(), 0, pMapSite);
}
