#ifndef K3_COMMON_H
#define K3_COMMON_H

#include <Windows.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef VOID (*PFNUSERCLEANUP)(LPVOID lpvValue);

typedef struct stRGB {
    BYTE bRed;
    BYTE bGreen;
    BYTE bBlue;
} RGB;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* K3_COMMON_H */
