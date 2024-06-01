#include "strutil.h"

LPWSTR U8StringToWide(LPCSTR lpszU8String) {
    int nWideLen = MultiByteToWideChar(CP_UTF8, 0, lpszU8String, -1, NULL, 0);
    if (nWideLen == 0) {
        return NULL;
    }

    LPWSTR lpszWide = (LPWSTR)HeapAlloc(GetProcessHeap(),
                                        HEAP_ZERO_MEMORY,
                                        nWideLen * sizeof(WCHAR));
    if (lpszWide == NULL) {
        return NULL;
    }

    MultiByteToWideChar(CP_UTF8, 0, lpszU8String, -1, lpszWide, nWideLen);
    return lpszWide;
}

INT ParseIntW(LPCWSTR lpwcBegin, LPCWSTR lpwcEnd) {
    INT nResult = 0;
    for (LPCWSTR lpwcIter = lpwcBegin; lpwcIter != lpwcEnd; lpwcIter++) {
        if (*lpwcIter < L'0' || *lpwcIter > L'9') {
            return 0;
        }

        nResult = nResult * 10 + (*lpwcIter - L'0');
    }

    return nResult;
}
