#include "fileutil.h"

LPSTR ReadFileAll(LPCWSTR lpszFileName) {
    HANDLE hFile = CreateFileW(lpszFileName,
                               GENERIC_READ,
                               FILE_SHARE_READ,
                               NULL,
                               OPEN_EXISTING,
                               FILE_ATTRIBUTE_NORMAL,
                               NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        return NULL;
    }

    DWORD dwFileSize = GetFileSize(hFile, NULL);
    if (dwFileSize == INVALID_FILE_SIZE) {
        CloseHandle(hFile);
        return NULL;
    }

    LPSTR lpszFileContent = (LPSTR)HeapAlloc(GetProcessHeap(),
                                             HEAP_ZERO_MEMORY,
                                             dwFileSize + 1);
    if (lpszFileContent == NULL) {
        CloseHandle(hFile);
        return NULL;
    }

    DWORD dwBytesRead;
    if (!ReadFile(hFile, lpszFileContent, dwFileSize, &dwBytesRead, NULL)) {
        HeapFree(GetProcessHeap(), 0, lpszFileContent);
        CloseHandle(hFile);
        return NULL;
    }

    CloseHandle(hFile);
    return lpszFileContent;
}

LPSTR* ReadFileLines(LPCWSTR lpszFileName) {
    LPSTR lpszFileContent = ReadFileAll(lpszFileName);
    if (lpszFileContent == NULL) {
        return NULL;
    }

    DWORD dwLineCount = 0;
    for (DWORD i = 0; i < strlen(lpszFileContent); i++) {
        if (lpszFileContent[i] == '\n') {
            dwLineCount++;
        }
    }

    LPSTR* arrlpszLines = (LPSTR*)HeapAlloc(GetProcessHeap(),
                                            HEAP_ZERO_MEMORY,
                                            (dwLineCount + 1) * sizeof(LPSTR));
    if (arrlpszLines == NULL) {
        HeapFree(GetProcessHeap(), 0, lpszFileContent);
        return NULL;
    }

    INT nLineCount = 0;
    LPSTR lpszLineStart = lpszFileContent;
    while (*lpszFileContent != 0) {
        if (*lpszFileContent == '\n') {
            *lpszFileContent = 0;
            arrlpszLines[nLineCount++] = lpszLineStart;
            lpszFileContent++;
            lpszLineStart = lpszFileContent;
        } else {
            lpszFileContent++;
        }
    }

    return arrlpszLines;
}

VOID FreeFileLines(LPSTR* arrlpszLines) {
    if (!arrlpszLines) {
        return;
    }

    HeapFree(GetProcessHeap(), 0, arrlpszLines[0]);
    HeapFree(GetProcessHeap(), 0, arrlpszLines);
}
