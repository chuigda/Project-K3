#ifndef K3_RECORD_H
#define K3_RECORD_H

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct stRecord Record, *PRecord;

PRecord CreateRecord(PFNUSERCLEANUP pfnUserCleanup);
VOID FreeRecord(PRecord pRecord);

BOOL RecordContains(PRecord pRecord, LPCWSTR lpszKey);
LPVOID GetRecordValue(PRecord pRecord, LPCWSTR lpszKey);
VOID RecordInsert(PRecord pRecord, LPCWSTR lpszKey, LPVOID lpvValue, UINT nSize);
VOID RecordRemove(PRecord pRecord, LPCWSTR lpszKey);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* K3_RECORD_H */
