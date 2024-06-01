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
            HeapFree(GetProcessHeap(), 0, lpszLine);
            FreeMap(pMap);
            FreeFileLines(arrlpszLines);
            return NULL;
        }

        pMap->arrpMapSites[i] = pMapSite;
        i++;
        HeapFree(GetProcessHeap(), 0, lpszLine);
    }

    FreeFileLines(arrlpszLines);
    return pMap;
}

static MapSite* ParseMapSite(LPWSTR lpszLine) {
    BYTE bCommaCount = 0;
    for (BYTE i = 0; lpszLine[i] != L'\0'; i++) {
        if (lpszLine[i] == L',') {
            bCommaCount++;
        }
    }

    if (bCommaCount < 2) {
        return NULL;
    }

    BYTE bConnectionCount = bCommaCount - 1;
    MapSite* pMapSite = (MapSite*)HeapAlloc(
        GetProcessHeap(),
        HEAP_ZERO_MEMORY,
        sizeof(MapSite) + bConnectionCount * sizeof(BYTE));

    if (pMapSite == NULL) {
        return NULL;
    }

    /* line format: id,name,conn1,conn2,...,connx */
    LPWSTR lpcCommaLoc = wcschr(lpszLine, L',');
    if (lpcCommaLoc == NULL) {
        HeapFree(GetProcessHeap(), 0, pMapSite);
        return NULL;
    }
    LPWSTR lpszName = lpcCommaLoc + 1;
    lpcCommaLoc = wcschr(lpszName, L',');
    if (lpcCommaLoc == NULL) {
        HeapFree(GetProcessHeap(), 0, pMapSite);
        return NULL;
    }

    UINT nNameLen = lpcCommaLoc - lpszName;
    LPWSTR lpszNameDup = (LPWSTR)HeapAlloc(GetProcessHeap(),
                                           0,
                                           (nNameLen + 1) * sizeof(WCHAR));
    if (lpszNameDup == NULL) {
        HeapFree(GetProcessHeap(), 0, pMapSite);
        return NULL;
    }
    wcsncpy(lpszNameDup, lpszName, nNameLen);

    pMapSite->lpszName = lpszNameDup;
    pMapSite->bConnectionCount = bConnectionCount;

    LPWSTR lpcCurrentLoc = lpcCommaLoc + 1;
    for (BYTE i = 0; i < bConnectionCount; i++) {
        lpcCommaLoc = wcschr(lpcCurrentLoc, L',');
        if (lpcCommaLoc == NULL) {
            if (i != bConnectionCount - 1) {
                HeapFree(GetProcessHeap(), 0, pMapSite->lpszName);
                HeapFree(GetProcessHeap(), 0, pMapSite);
                return NULL;
            }

            lpcCommaLoc = wcschr(lpcCurrentLoc, L'\0');
        }

        pMapSite->arrbConnections[i] = (BYTE)ParseIntW(lpcCurrentLoc,
                                                       lpcCommaLoc);
        lpcCurrentLoc = lpcCommaLoc + 1;
    }

    return pMapSite;
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
    HeapFree(GetProcessHeap(), 0, pMapSite->lpszName);
    HeapFree(GetProcessHeap(), 0, pMapSite);
}
