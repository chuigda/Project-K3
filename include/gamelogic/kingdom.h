#ifndef K3_KINGDOM_H
#define K3_KINGDOM_H

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct stKingdom {
    UINT nKingdomID;
    RGB rgbKingdomColor;

    LPWSTR lpszKingdomName;
    LPWSTR lpszKingdomDescription;
} Kingdom, *PKINGDOM;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* K3_KINGDOM_H */
