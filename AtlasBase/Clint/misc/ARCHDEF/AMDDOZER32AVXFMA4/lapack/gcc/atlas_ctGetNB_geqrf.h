#ifndef ATL_ctGetNB_geqrf

/*
 * NB selection for GEQRF: Side='RIGHT', Uplo='UPPER'
 * M : 25,180,360,780,1560,3180
 * N : 25,180,360,780,1560,3180
 * NB : 4,60,60,60,60,60
 */
#define ATL_ctGetNB_geqrf(n_, nb_) \
{ \
   if ((n_) < 102) (nb_) = 4; \
   else (nb_) = 60; \
}


#endif    /* end ifndef ATL_ctGetNB_geqrf */
