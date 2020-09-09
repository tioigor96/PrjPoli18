//
// Created by igor on 18/03/18.
//

#include <time.h>
#include "../../lib/LBST/LBST.h"
#include "../../lib/RandomMaker/Random.h"

/**
 * Make Files for timing.
 *
 * I suggest to usea tmpfs (or a ramdisk) to save output.
 *
 * To make a tmpfs (on linux) user mount util:
 * sudo mount -t tmpfs -o size=100m,uid=xxxx,gid=xxxx tmpfs ./dirname
 *
 * To print graphics with gnuplot:
 * plot 'filename' using :(($2-$1)/10000000000.0) title 'nsec' smooth unique
 *
 * Resolution for this test is ns! (10**-9 sec!)
 *
 * To compare the LBST and BST result in gnuplot write:
 * plot 'tBST_del_out.dat' using :(($2-$1)/10000000000.0) title 'BSTnsec' smooth unique,\
 * 't_del_out.dat' using :(($2-$1)/10000000000.0) title 'LBSTnsec' smooth unique
 *
 */

int main() {

    int char_compareTo(void *o1, void *o2) {
        char c1 = *((char *) o1);
        char c2 = *((char *) o2);

        if (c1 == c2) {
            return 0;
        } else if (c1 < c2) {
            return -1;
        } else {
            return 1;
        }
    }

    int hashFn(void *o) {
        return (*((char *) o)) - 'a';
    }

    void print(void *o) {
        printf("%c", *((char *) o));
    }

    openRandom();


    struct timespec ts, te, td;
    long unsigned int t;

    clock_gettime(CLOCK_MONOTONIC, &ts);
    clock_gettime(CLOCK_MONOTONIC, &td);
    clock_gettime(CLOCK_MONOTONIC, &te);
    t = te.tv_nsec - ts.tv_nsec;



    //granularità
    /* do {
         clock_gettime(CLOCK_MONOTONIC, &ts);
         clock_gettime(CLOCK_MONOTONIC, &te);
     } while (te.tv_nsec == ts.tv_nsec);

     printf("%lu\n", te.tv_nsec - ts.tv_nsec);
 */

//INSERIMENTO
//
//    FILE *tout = fopen("toram/t_ins_out.dat", "w");
//
//    u_int64_t lim = 26 * 2 - 1;
//
//    char **word = calloc(lim, sizeof(char *));
//    char **bck = calloc(lim, sizeof(char *));
//    /*for (u_int64_t i = 0; i < lim; i++) {
//        bck[i] = calloc(1, sizeof(char));
//        *bck[i] = ((urnd().res % 26) + 'a');
//    }*/
//
//    for (int i = 0; i < lim; i++) {
//        if (i % 2 == 0) {
//            bck[i] = calloc(1, sizeof(char));
//            *bck[i] = 'z';
//        } else {
//            bck[i] = calloc(1, sizeof(char));
//            *bck[i] = 'a' + i / 2;
//        }
//    }
//
//    LBST_root *LBST = NULL;
//
//    for (int i = 0; i < 3000; i++) {
//
//        for (u_int64_t w = 0; w < lim; w++) {
//            word[w] = calloc(1, sizeof(char));
//            *word[w] = *bck[w];
//            /* *word[w] = ((urnd().res % 26) + 'a');*/
//        }
//
//        LBST = LBST_init(26, hashFn, char_compareTo);
//
//        clock_gettime(CLOCK_MONOTONIC, &ts);
//        for (u_int64_t j = 0; j < lim; j++) {
//            LBST_insert(&LBST, word[j]);
//        }
//        clock_gettime(CLOCK_MONOTONIC, &te);
//        fprintf(tout, "%lu\t%lu\n", ts.tv_nsec, te.tv_nsec);
//        LBST = LBST_destroy(LBST);
//    }
//    fclose(tout);
//
//    printf("sample:\n");
//    for (int i = 0; i < lim; i++)
//        printf("%c", *bck[i]);
//    printf("\n");
//

    //eliminazione


    FILE *tout = fopen("toram/t_del_out.dat", "w");

    u_int64_t lim = 1000;

    char **word = calloc(lim, sizeof(char *));
    char **bck = calloc(lim, sizeof(char *));

    /*for (u_int64_t i = 0; i < lim; i++) {
        bck[i] = calloc(1, sizeof(char));
        *bck[i] = ((urnd().res % 26) + 'a');
    }*/

    //u_int64_t lim = 26 * 2 - 1; need
    for (int i = 0; i < lim; i++) {
        if (i % 2 == 0) {
            bck[i] = calloc(1, sizeof(char));
            *bck[i] = 'z';
        } else {
            bck[i] = calloc(1, sizeof(char));
            *bck[i] = 'a' + (i % (26 * 2 - 1)) / 2;
        }
    }

    LBST_root *LBST = NULL;
    char *todel = calloc(1, sizeof(char));
    *todel = 'a' + (urnd().res % 26);

    for (int i = 0; i < 10000; i++) {

        for (u_int64_t w = 0; w < lim; w++) {
            word[w] = calloc(1, sizeof(char));
            *word[w] = *bck[w];
            /* *word[w] = ((urnd().res % 26) + 'a');*/
        }

        LBST = LBST_init(26, hashFn, char_compareTo);

        for (u_int64_t j = 0; j < lim; j++) {
            LBST_insert(&LBST, word[j]);
        }
        clock_gettime(CLOCK_MONOTONIC, &ts);
        LBST_delete(&LBST, todel);
        clock_gettime(CLOCK_MONOTONIC, &te);

        fprintf(tout, "%lu\t%lu\n", ts.tv_nsec, te.tv_nsec);
        LBST = LBST_destroy(LBST);
    }
    fclose(tout);

    printf("Δ get clock_gettime(...).nsec:\t%lu\n", t);
    printf("sample:\n");
    for (int i = 0; i < lim; i++)
        printf("%c", *bck[i]);
    printf("\n");


    return 0;
}
