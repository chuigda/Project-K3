#ifndef K3_MAPDATA_H
#define K3_MAPDATA_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct stMapData {
    UINT nOwnership;
    UINT nPopulation;
    UINT nAgriculture;
    UINT nCommerce;
} MapData, *PMAPDATA;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* K3_MAPDATA_H */
