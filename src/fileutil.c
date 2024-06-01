#include "fileutil.h"

LPSTR ReadFileAll(LPCWSTR lpszFileName) {
    HANDLE hFile = CreateFileW(lpszFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        return NULL;
    }

    DWORD dwFileSize = GetFileSize(hFile, NULL);
    if (dwFileSize == INVALID_FILE_SIZE) {
        CloseHandle(hFile);
        return NULL;
    }

    LPSTR lpszFile = (LPSTR)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, dwFileSize + 1);
    if (lpszFile == NULL) {
        CloseHandle(hFile);
        return NULL;
    }

    DWORD dwBytesRead;
    if (!ReadFile(hFile, lpszFile, dwFileSize, &dwBytesRead, NULL)) {
        HeapFree(GetProcessHeap(), 0, lpszFile);
        CloseHandle(hFile);
        return NULL;
    }

    CloseHandle(hFile);
    return lpszFile;
}

LPSTR* ReadFileLines(LPCWSTR lpszFileName) {
    LPSTR lpszFile = ReadFileAll(lpszFileName);
    if (lpszFile == NULL) {
        return NULL;
    }

    DWORD dwLineCount = 0;
    for (DWORD i = 0; i < strlen(lpszFile); i++) {
        if (lpszFile[i] == '\n') {
            dwLineCount++;
        }
    }

    LPSTR* arrlpszLines = (LPSTR*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, (dwLineCount + 1) * sizeof(LPSTR));
    if (arrlpszLines == NULL) {
        HeapFree(GetProcessHeap(), 0, lpszFile);
        return NULL;
    }

    LPSTR lpszLine = strtok(lpszFile, "\n");
    for (DWORD i = 0; lpszLine != NULL; i++) {
        arrlpszLines[i] = lpszLine;
        lpszLine = strtok(NULL, "\n");
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
