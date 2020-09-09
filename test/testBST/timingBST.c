//
// Created by igor on 20/03/18.
//

#include <time.h>
#include "../../lib/BST/BST.h"
#include "../../lib/RandomMaker/Random.h"
#include <string.h>

#include <errno.h>

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

BST_node *BST_insert(BST_node *root, char c) {
    BST_node *new = calloc(1, sizeof(BST_node));
    //calloc do some operation by default... NULL is 0!
    /* new->p = NULL;
     new->l = NULL;
     new->r = NULL;*/
    char *ptr = malloc(sizeof(char));
    (*ptr) = c;
    new->f = ptr;
    root = BST_general_insert(root, new, char_compareTo);
    return root;

}

BST_node *BST_find(BST_node *root, char c) {
    BST_node *find = calloc(1, sizeof(BST_node));
    char *ptr = malloc(sizeof(char));
    (*ptr) = c;
    find->f = ptr;
    root = BST_general_find(root, find, char_compareTo);     //in root i would find the ptr to node
    free(find);                     //free useless node
    free(ptr);
    return root;
}

BST_node *BST_delete(BST_node *root, char c) {
    BST_node *todlt = BST_find(root, c);

    if (todlt != NULL)
        root = BST_general_delete(root, todlt, char_compareTo);

    return root;
}

u_int64_t lim;
u_int64_t wlim;
char *word = NULL;
char *filedest = NULL;

/*
   //wrost case!
   for (int i = 0; i < lim; i++) {
            if (i % 2 == 0) {
                word[i] = 'z';
            } else {
                word[i] = 'a' + (i % (26 * 2 - 1)) / 2;
            }
        }
 */

unsigned char options(int argc, char **argv) {

    void printHelp() {
        printf("Options:\n\t-w:\twhat word do you want for test\n");
        printf("\t-c:\tnumber of tests\n");
        printf("\t-r:\trandomize word in test\n");
        printf("\t-o:\toutput file name\n");
        printf("\t-i:\tinsert test (REQUIRED)\n");
        printf("\t-d:\tdelete test (REQUIRED)\n");
        printf("\t-h:\tshow this help\n");
    }
    /**
     * BITWISE: from lsb to MSB;
     * 0x01:    test case is defined
     * 0x02:    number of test is set
     * 0x04:    randomize test case
     * 0x08:    output file name is specified
     * 0x10:    insert test
     * 0x20:    delete test
     */
    char opt = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-w") == 0) {
            if ((opt & 0x01)) {
                i++;
                continue;
            }
            word = argv[++i];
            wlim = strlen(word);
            opt += 0x01;
        } else if (strcmp(argv[i], "-c") == 0) {
            if ((opt & 0x02)) {
                i++;
                continue;
            }
            lim = atoi(argv[++i]);
            opt += 0x02;
        } else if (strcmp(argv[i], "-r") == 0) {
            if ((opt & 0x04)) continue;

            wlim = urnd().res % (1 << 10);

            word = calloc(wlim, sizeof(char));
            for (u_int64_t i = 0; i < wlim; i++) {
                word[i] = ((urnd().res % 26) + 'a');
            }
            lim = urnd().res % (1 << 16);

            opt += opt & 0x01 ? 0 : 0x01;
            opt += opt & 0x02 ? 0 : 0x04;
            opt += opt & 0x04 ? 0 : 0x01;
        } else if (strcmp(argv[i], "-o") == 0) {
            if ((opt & 0x08)) {
                i++;
                continue;
            }
            filedest = argv[++i];
            opt += 0x08;
        } else if (strcmp(argv[i], "-i") == 0 && !(opt & 0x20)) {
            if ((opt & 0x10)) continue;
            opt += 0x10;
        } else if (strcmp(argv[i], "-d") == 0 && !(opt & 0x10)) {
            if ((opt & 0x20)) continue;
            opt += 0x20;
        } else {
            printHelp();
        }
    }

    if (!(opt & 0x01) && !word) {
        wlim = urnd().res % (1 << 10);
        word = calloc(wlim, sizeof(char));
        for (u_int64_t i = 0; i < wlim; i++) {
            word[i] = ((urnd().res % 26) + 'a');
        }
    }

    if (!(opt & 0x02) && !(opt & 0x04)) {
        lim = urnd().res % (1 << 10);
    }

    if (!(opt & 0x08)) {
        filedest = "out.dat";
    }

    if (!(opt & 0x10) && !(opt & 0x20)) {
        printHelp();
    }

    return opt;
}

void init() {
    openRandom();
}

int main(int argc, char **argv) {

    init();
    unsigned char opt = options(argc, argv);

    if (!(opt & 0x10) && !(opt & 0x20)) {
        exit(EXIT_FAILURE);
    }

    struct timespec ts, te, td;
    long unsigned int t;
    BST_node *BST = NULL;

    FILE *tout = fopen(filedest, "w");
    if (!tout) {
        printf("errno:%d", errno);
        exit(EXIT_FAILURE);
    }

    clock_gettime(CLOCK_MONOTONIC, &ts);
    clock_gettime(CLOCK_MONOTONIC, &td);
    clock_gettime(CLOCK_MONOTONIC, &te);
    t = te.tv_nsec - ts.tv_nsec;

    //INSERIMENTO
    if (opt & 0x10) {

        for (int i = 0; i < lim; i++) {

            clock_gettime(CLOCK_MONOTONIC, &ts);
            for (u_int64_t j = 0; j < wlim; j++) {
                BST = BST_insert(BST, word[j]);
            }
            clock_gettime(CLOCK_MONOTONIC, &te);
            fprintf(tout, "%lu\t%lu\n", ts.tv_nsec, te.tv_nsec);
            BST = BST_destroy(BST);
        }
    }
    //eliminazione

    if (opt & 0x20) {
        char todel = 'a' + (urnd().res % 26);

        for (int i = 0; i < lim; i++) {

            for (u_int64_t j = 0; j < wlim; j++) {
                BST = BST_insert(BST, word[j]);
            }

            clock_gettime(CLOCK_MONOTONIC, &ts);
            BST_delete(BST, todel);
            clock_gettime(CLOCK_MONOTONIC, &te);

            fprintf(tout, "%lu\t%lu\n", ts.tv_nsec, te.tv_nsec);
            BST = BST_destroy(BST);
        }
    }
    fclose(tout);

    printf("Δ get clock_gettime(...).nsec:\t%lu\n", t);
    printf("sample:\n");
    for (int i = 0; i < wlim; i++)
        printf("%c", word[i]);
    printf("\n");


    return 0;
}
