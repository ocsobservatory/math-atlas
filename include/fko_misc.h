#ifndef FKO_MISC_H
#define FKO_MISC_H
#include "fko_inst.h"

INSTQ *PrintComment(INSTQ *prev, INSTQ *next, ...);
void fko_error(int errno, ...);
void fko_warn(int errno, ...);
int const2shift(int c);
struct loopq *NewLoop(int flag);

#endif
