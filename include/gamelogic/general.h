#ifndef K3_GENERAL_H
#define K3_GENERAL_H

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum eGeneralRareness {
    GENERAL_RARENESS_N = 1,
    GENERAL_RARENESS_R = 2,
    GENERAL_RARENESS_SR = 3,
    GENERAL_RARENESS_SSR = 4
} GeneralRareness;

typedef enum eGeneralType {
   GENERAL_TYPE_STRERGTH = 1,
   GENERAL_TYPE_INTELLIGENCE = 2,
   GENERAL_TYPE_AGIILITY = 3
} GeneralType;

typedef struct stGeneral {
    UINT nGeneralId;

    LPWSTR lpszGeneralName;
    UINT nGeneralRareness;
    UINT nGeneralType;

    UINT nGeneralLevel;
    UINT nGeneralXP;
    UINT nGeneralStrength;
    UINT nGeneralIntelligence;
    UINT nGeneralAgility;
} General;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* K3_GENERAL_H */
