#ifndef K3_FILEUTIL_H
#define K3_FILEUTIL_H

#include <Windows.h>

#ifdef __cplusplus
extern "C" {
#endif

LPSTR ReadFileAll(LPCWSTR lpszFileName);
LPSTR* ReadFileLines(LPCWSTR lpszFileName);
VOID FreeFileLines(LPSTR* arrlpszLines);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* K3_FILEUTIL_H */
