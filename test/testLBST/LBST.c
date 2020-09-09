//
// Created by igor on 06/03/18.
//

#include "../../lib/LBST/LBST.h"
#include <string.h>

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


    LBST_root *cnt = LBST_init(26, hashFn, char_compareTo);

    /*LBST_insert(&cnt, strcpy(malloc(1), "g"));
    LBST_insert(&cnt, strcpy(malloc(1), "r"));
    LBST_insert(&cnt, strcpy(malloc(1), "a"));
    LBST_insert(&cnt, strcpy(malloc(1), "n"));
    LBST_insert(&cnt, strcpy(malloc(1), "a"));
    LBST_insert(&cnt, strcpy(malloc(1), "t"));
    LBST_insert(&cnt, strcpy(malloc(1), "a"));
    LBST_insert(&cnt, strcpy(malloc(1), "g"));
    LBST_insert(&cnt, strcpy(malloc(1), "r"));
    LBST_insert(&cnt, strcpy(malloc(1), "a"));
    LBST_insert(&cnt, strcpy(malloc(1), "n"));
    LBST_insert(&cnt, strcpy(malloc(1), "a"));
    LBST_insert(&cnt, strcpy(malloc(1), "t"));
    LBST_insert(&cnt, strcpy(malloc(1), "a"));*/


    void print(void *o) {
        printf("%c\n", *((char *) o));
    }

    LBST_print(cnt, print);
    printf("-----------------\n");

    LBST_insert(&cnt, strcpy(malloc(1), "g"));
    LBST_print(cnt, print);
    printf("-----------------\n");

    LBST_insert(&cnt, strcpy(malloc(1), "r"));
    LBST_print(cnt, print);
    printf("-----------------\n");

    LBST_insert(&cnt, strcpy(malloc(1), "a"));
    LBST_print(cnt, print);
    printf("-----------------\n");

    char *vittima = malloc(1);

    *vittima = 'c';
    LBST_find(cnt, vittima);

    LBST_delete(&cnt, vittima);
    LBST_print(cnt, print);
    printf("-----------------\n");

    *vittima = 'g';
    LBST_delete(&cnt, vittima);
    LBST_print(cnt, print);
    printf("-----------------\n");

    *vittima = 'a';
    LBST_delete(&cnt, vittima);
    LBST_print(cnt, print);
    printf("-----------------\n");

    LBST_insert(&cnt, strcpy(malloc(1), "g"));
    LBST_print(cnt, print);
    printf("-----------------\n");

    *vittima = 'r';
    LBST_delete(&cnt, vittima);
    LBST_print(cnt, print);
    printf("-----------------\n");

    cnt = LBST_destroy(cnt);

    return 0;
}