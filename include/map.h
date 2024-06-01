#ifndef K3_MAP_H
#define K3_MAP_H

#include <Windows.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct stMapSite {
    LPWSTR lpszName;
    LPVOID lpvData;
    BYTE bConnectionCount;
    BYTE arrbConnections[];
} MapSite;

typedef struct stMap {
    BYTE bSiteCount;
    MapSite* arrpMapSites[];
} Map;

Map* ReadMapFromFile(LPCWSTR lpszFileName);
VOID FreeMap(Map* pMap);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* K3_MAP_H */
