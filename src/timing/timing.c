//
// Created by igor on 17/10/18.
//



#include "../../lib/timing/timing.h"

__clock_t granularity() {
    __clock_t t0, t1;

    t0 = clock();
    t1 = clock();

    while (t0 == t1)
        t1 = clock();

    return t1 - t0;
}

int calcolaRip(__clock_t tMin, void (*execute)(), void (*riavvolgi)()) {
    __clock_t t0, t1, tt;
    int rip;

    /* Prima esecuzione */
    rip = 1;
    t0 = clock();
    execute();
    t1 = clock();
    riavvolgi();

    tt = t1 - t0 <= tMin ? 0 : t1 - t0;

    /* Ricerca per bisezione */
    while (tt <= tMin) {
        rip *= 2;

        for (int i = 0; i < rip; i++) {
            t0 = clock();
            execute();
            t1 = clock();
            riavvolgi();
            tt += (t1 - t0);
        }
    }

    /* Raffinamento delle ripetizioni a 5 cicli */
    int max = rip;
    int min = rip / 2;
    tt = 0;

    while (max - min >= 5) {
        rip = (max + min) / 2; /* valore mediano */
        for (int i = 0; i < rip; i++) {
            t0 = clock();
            execute();
            t1 = clock();
            riavvolgi();
            tt += (t1 - t0);
        }

        if (tt <= tMin)
            min = rip;
        else
            max = rip;
    }

    return max;
}

__clock_t calcolaTempo(void (*execute)(), void (*riavvolgi)()) {
    __clock_t g = granularity();
    int rip = calcolaRip((int) ((double) g / MAX_RELATIVE_MEASUREMENT_ERROR), execute, riavvolgi);
    __clock_t t0, t1, tt = 0, res;

    for (int i = 0; i < rip; i++) {
        t0 = clock();
        execute();
        t1 = clock();
        riavvolgi();
        tt += t1 - t0;
    }

    res = tt / rip;

    return res;
}

result misurazione(int len, int c, double za, double maxreldelta, void(*prepara)(int), void(*execute)(), void (*riavvolgi)()) {
    __clock_t t = 0;
    __clock_t sum2 = 0;
    int cn = 0;

    __clock_t m;
    double s, e, delta;

    do {
        for (int i = 0; i < c; i++) {
            prepara(len);
            m = calcolaTempo(execute, riavvolgi);
            t = t + m;
            sum2 = sum2 + (m * m);
        }
        cn = cn + c;
        e = (double) t / (double) cn;
        s = sqrt(sum2 / (double) cn - (e * e));
        delta = (1.0 / sqrt((double) cn)) * za * s;
    } while (delta / e > maxreldelta);

    result r ;
    r.e = e;
    r.delta = delta;
    return r;
}