#ifndef K3_MINIDB_H
#define K3_MINIDB_H

#include <Windows.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct stMiniDBItem {
    struct stMiniDBItem *pNext;
    LPWSTR arrlpszFields[];
} MiniDBItem, *PMINIDBITEM;

typedef struct stMiniDB {
    LPWSTR lpszFileContent;
    MiniDBItem *pItems;
} MiniDB, *PMINIDB;

PMINIDB OpenMiniDB(LPCWSTR lpszFileName);
BOOL PersistMiniDB(PMINIDB pDB, LPCWSTR lpszFileName);
VOID CloseMiniDB(PMINIDB pDB);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* K3_MINIDB_H */
