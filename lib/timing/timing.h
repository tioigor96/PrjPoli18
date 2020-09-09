//
// Created by igor on 21/10/18.
//

#ifndef PRJPOLI18_TIMING_H
#define PRJPOLI18_TIMING_H

#include <time.h>
#include <math.h>
#include <stdlib.h>

#define MAX_RELATIVE_MEASUREMENT_ERROR 0.02

struct _result {
    double e;
    double delta;
};
typedef struct _result result;

__clock_t granularity();

int calcolaRip(__clock_t tMin, void (*execute)(), void (*riavvolgi)());

__clock_t calcolaTempo(void (*execute)(), void (*riavvolgi)());

result misurazione(int len, int c, double za, double maxreldelta, void(*prepara)(int), void(*execute)(), void (*riavvolgi)());

#endif //PRJPOLI18_TIMING_H
