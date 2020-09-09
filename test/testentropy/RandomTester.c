//
// Created by igor on 02/03/18.
//

/*
 * Main to test random generator and to get entropy for "dev/urandom".
 * Is considered secure random generator if no one have root access to local machine.
 *
 * USAGE: This file make a 'local.dat' and 'local_ord.dat' if generate a sequence of number,
 * otherwise generate only 'local.dat'.
 * Use The 'local.dat' for entropy calculator, to get the entropy of the random Generator, and
 * use 'local.dat' and 'local_ord.dat' for see (with gnuplot or other graphical plotter)
 * the distribution of generated numbers and if it generate always the same numbers.
 *
 * For example, with  gnuplot, the command are:
 * <<
 * user@machinename:localdir$ gnuplot
 * gnuplot> plot 'local.dat'
 * gnuplot> plot 'local_ord.dat'
 * >>
 *
 * For entropy calculation, compile ent with make (simply, "make").
 * After, digit:
 * <<
 * ./ent -c local.dat
 * >>
 *
 * ENT refers to http://www.fourmilab.ch/random/ .
 */

#include <stdio.h>
#include <malloc.h>
#include "../../lib/RandomMaker/Random.h"


int *counting_sort(int *array, int array_length, int array_max);

int main() {
    openRandom();
    FILE *fd = fopen("local.dat", "w");

    //for numbers, uncomment the following section
    /*int array[1000000];
    for (int i = 0; i < 1000000; i++) {
        array[i] = (urnd().res) % 1000000;
        fprintf(fd, "%d\n", array[i]);
    }

    fclose(fd);

    int *s_a = counting_sort(array, 1000000, 1000000 - 1);

    fd = fopen("local_ord.dat", "w");
    for (int i = 0; i < 1000000; i++) {
        fprintf(fd, "%d\n", s_a[i]);
    }
    fclose(fd);*/

    //for chars (ASCII standard) uncomment the following section
    for (unsigned long long i = 0; i < 1000000000; i++) {
        struct RndRes t = urnd();
        __uint32_t array = t.res;
        fprintf(fd, "%c%c%c%c", (((__uint32_t) array) >> 24) % 128,
                (((__uint32_t) array) << 8 >> 24) % 128,
                (((__uint32_t) array) << 16 >> 24) % 128,
                (((__uint32_t) array) << 24 >> 24) % 128);
    }

    fclose(fd);

}

int *counting_sort(int *array, int array_length, int array_max) {

    array_max++;

    int *map = calloc(array_max, sizeof(int));

    // build map from original array
    for (int i = 0; i < array_length; i++) {
        map[array[i]]++;
    }

    // setup output array
    int *sorted = malloc(sizeof(*sorted) * array_length);
    int index = 0;

    // build sorted array from map
    for (int i = 0; i < array_max; i++) {
        while (map[i] > 0) {
            sorted[index] = i;
            index++;
            map[i]--;
        }
    }

    return sorted;
}