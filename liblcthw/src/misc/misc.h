#ifndef LCTHW_MISC_H
#define LCTHW_MISC_H

#include <stdlib.h>

#define cfree(p) if ((p) != NULL) { free((void *)(p)); (p) = NULL; }
#define NL printf("\n")

#define inline

#define MIN(x,y) ((x) < (y)) ? (x) : (y)

#endif
