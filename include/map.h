#ifndef K3_MAP_H
#define K3_MAP_H

#include <Windows.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct stMapSite {
   LPCSTRW lpszName;
   BYTE bConnectionCount;
   BYTE arrbConnections[];
} MapSite;

typedef struct stMap {
   MapSite* arrpMapSites[];
} Map;

Map* ReadMapFromFile(LPCSTRW lpszFileName);
VOID FreeMap(Map* pMap);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* K3_MAP_H */
