#ifndef K3_STRUTIL_H
#define K3_STRUTIL_H

#include <Windows.h>

#ifdef __cplusplus
extern "C" {
#endif

LPWSTR U8StringToWide(LPCSTR lpszU8String);
INT ParseIntW(LPCWSTR lpwcBegin, LPCWSTR lpwcEnd);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* K3_STRUTIL_H */
