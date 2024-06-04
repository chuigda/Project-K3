#include "minidb.h"
#include "fileutil.h"
#include "strutil.h"

static LPWSTR countCommaUntilLineFeed(LPWSTR lpszData, INTPTR pCount);

PMINIDB OpenMiniDB(LPCWSTR lpszFileName) {
    LPSTR lpszFileContent = ReadFileAll(lpszFileName);
    if (lpszFileContent == NULL) {
        return NULL;
    }

    LPWSTR lpszFileContentW = U8StringToWide(lpszFileContent);
    if (lpszFileContentW == NULL) {
        HeapFree(GetProcessHeap(), 0, lpszFileContent);
        return NULL;
    }

    HeapFree(GetProcessHeap(), 0, lpszFileContent);

    PMINIDB pDB = (PMINIDB)malloc(sizeof(MiniDB));
    if (pDB == NULL) {
        HeapFree(GetProcessHeap(), 0, lpszFileContentW);
        return NULL;
    }

    pDB->lpszFileContent = lpszFileContentW;
    pDB->pItems = NULL;

    PWCHAR pcLineStart = lpszFileContentW;
    while (*pcLineStart != '\0') {
        INT nFields;
        PWCHAR pcNextLineStart = countCommaUntilLineFeed(pcLineStart, &nFields);
        if (nFields == 0) {
            pcLineStart = pcNextLineStart;
            continue;
        }

        PMINIDBITEM pItem = (PMINIDBITEM)malloc(sizeof(MiniDBItem) + sizeof(LPWSTR) * nFields);
        if (pItem == NULL) {
            CloseMiniDB(pDB);
            HeapFree(GetProcessHeap(), 0, lpszFileContent);
            return NULL;
        }

        pItem->pNext = pDB->pItems;
        pDB->pItems = pItem;

        LPWSTR *arrlpszFields = pItem->arrlpszFields;
        for (INT i = 0; i < nFields; i++) {
            arrlpszFields[i] = pcLineStart;
            while (*pcLineStart != L',' && *pcLineStart != L'\n' && *pcLineStart != L'\0') {
                pcLineStart++;
            }

            if (*pcLineStart == L',' || *pcLineStart == L'\n') {
                *pcLineStart = L'\0';
                pcLineStart++;
            }
        }
    }
}

static LPWSTR countCommaUntilLineFeed(LPWSTR lpszData, INTPTR pCount) {
    *pCount = 0;
    while (*lpszData != L'\0' && *lpszData != L'\n') {
        if (*lpszData == L',') {
            (*pCount)++;
        }
        lpszData++;
    }

    if (*lpszData == L'\n') {
        lpszData++;
    }

    return lpszData;
}
