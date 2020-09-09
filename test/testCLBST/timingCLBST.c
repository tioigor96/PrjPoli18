//
// Created by igor on 24/08/18.
//

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>
#include "../../lib/RandomMaker/Random.h"
#include "../../lib/CLBST/CLBST.h"

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

size_t fieldSize(void *p) {
    return sizeof(char);
}


char **makeWord(int len) {
    char **cil = calloc(sizeof(char *), len);
    for (int i = 0; i < len; i++) {
        char *l = calloc(sizeof(char), 1);
        *l = ((urnd().res % 26) + 'a');
        cil[i] = l;
    }

    return cil;
}

//char **makeLimit(int len) {
//    char **cil = calloc(sizeof(char *), len);
//    for (int i = 0; i < len; i++) {
//        char *l = calloc(sizeof(char), 1);
//
//        *l = i % 2 == 0 ? ('z') : ('a' + (i % (26 * 2 - 1)) / 2);
//        cil[i] = l;
//    }
//
//    return cil;
//}

int main() {

    struct timespec ts, te;
    struct timeval ts1, te1;

    CLBST_root *cnt = NULL;

    FILE *fr = fopen("toram/CLBST_i_r.dat", "w");

    openRandom();

//    for (int i = 1; i < 10001; i++) {
//        cnt = CLBST_init(26, hashFn, char_compareTo, fieldSize);
//        char **word = makeWord(i);
//
//        //clock_gettime(CLOCK_MONOTONIC, &ts);
//        gettimeofday(&ts1, NULL);
//        for (int j = 0; j < i; j++) {
//            CLBST_insert(&cnt, word[j]);
//        }
//        gettimeofday(&te1, NULL);
//        //clock_gettime(CLOCK_MONOTONIC, &te);
//        if (te1.tv_usec - ts1.tv_usec > 0)
//            //fprintf(fr, "%lu\t%lu\n", ts.tv_nsec, te.tv_nsec);
//            fprintf(fr, "%ld\t%ld\n", ts1.tv_usec, te1.tv_usec);
//        else
//            printf("giro? %lu, %lu\n", ts1.tv_usec, te1.tv_usec);
//
//        cnt = CLBST_destroy(cnt);
//    }

//control for see if node is really <52(=51)
//    for (int k = 0; k < 1000; k++) {
//        cnt = CLBST_init(26, hashFn, char_compareTo, fieldSize);
//        //char **word = makeWord(1000);
//        char **word = makeLimit(1000);
//        for (int q = 0; q < 1000; q++)
//            printf("%c", word[q][0]);
//
//        for (int j = 0; j < 1000; j++) {
//            CLBST_insert(&cnt, word[j]);
//        }
//
//        int counter = 0;
//        for (int i = 0; i < 26; i++) {
//            HM_DLST *aux = cnt->hm[i].f;
//            while (aux) {
//                counter++;
//                aux = aux->n;
//            }
//        }
//        printf("%d\n", counter);
//        assert(counter < 52);
//        cnt = CLBST_destroy(cnt);
//    }

//get addr for simple tree
    cnt = CLBST_init(26, hashFn, char_compareTo, fieldSize);
    char **word = makeWord(1000);

    for (int j = 0; j < 1000; j++) {
        CLBST_insert(&cnt, word[j]);
    }
/*

    for (int i = 0; i < 26; i++) {
        HM_DLST *aux = cnt->hm[i].f;
        while (aux) {
            printf("addr:%8p\trem:%ld\n", aux->node, (((u_int64_t) (aux->node)) >> 4 & 0xFF) % 52);
            aux = aux->n;
        }
    }
*/

    void mapTest(CBST_node *root) {
        if (root) {
            /*unsigned long hash = 5381;
            unsigned char c = 0;
            unsigned char *str = (unsigned char *) root;
            while (c = *str++) {
                hash = ((hash << 5) + hash) + c;

            }
            hash = hash % 52;
            printf("hash=%lu\n", (hash < 0) ? hash * -1 : hash);*/
            printf("%lu\n",(((u_int64_t)root)>>5<<56>>56));
            mapTest(root->l);
            mapTest(root->r);
        }
    }

    mapTest(cnt->root);

    /*printf("HM_DLST:%lu\n", sizeof(HM_DLST));
    printf("HM_LSTPTR:%lu\n", sizeof(HM_LSTPTR));
    printf("CBST_NODE:%lu\n", sizeof(CBST_node));
    printf("CLBST_root:%lu\n", sizeof(CLBST_root));
    printf("sizeof int:%lu\n", sizeof(int));
    printf("sizeof long int:%lu\n", sizeof(long int));
    printf("sizeof unsigned int:%lu\n", sizeof(unsigned int));
    printf("sizeof unsigned long int:%lu\n", sizeof(unsigned long int));
    printf("sizeof u_int64_t:%lu\n", sizeof(u_int64_t));
    printf("sizeof *CBST_NODE:%lu\n", sizeof(CBST_node *));*/


    return 0;
}