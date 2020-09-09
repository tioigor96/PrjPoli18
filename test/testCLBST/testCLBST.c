//
// Created by igor on 18/08/18.
//

#include <stdio.h>
#include <string.h>
#include "../../lib/CLBST/CLBST.h"
#include "../../lib/RandomMaker/Random.h"

char **makeWord(int len) {
    char **cil = calloc(sizeof(char *), len);
    for (int i = 0; i < len; i++) {
        char *l = calloc(sizeof(char), 1);
        *l = ((urnd().res % 26) + 'a');
        cil[i] = l;
    }

    return cil;
}

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

    size_t fieldSize(void *p) {
        return sizeof(char);
    }

    unsigned int printDot(CBST_node *root, unsigned int init) {
        if (root == NULL) {
            printf("\t%d [label=\"NIL\"];\n", init);
            return init;
        }

        char fld = *((char *) root->f);

        int local = init++;

        printf("\t%d [label=\"%c #: %d\"];\n", local, fld, root->count);

        printf("\t%d -- %d\n", local, init);
        init = printDot(root->l, init);
        init++;

        printf("\t%d -- %d\n", local, init);
        init = printDot(root->r, init);
        init++;

        return init;
    }

    openRandom();

    //edfddeecaefdafda
    CLBST_root *cnt = CLBST_init(26, hashFn, char_compareTo, fieldSize);
    CLBST_insert(&cnt, memcpy(malloc(1), "e", 1));
    CLBST_insert(&cnt, memcpy(malloc(1), "d", 1));
    CLBST_insert(&cnt, memcpy(malloc(1), "f", 1));
    CLBST_insert(&cnt, memcpy(malloc(1), "d", 1));
    CLBST_insert(&cnt, memcpy(malloc(1), "d", 1));
    CLBST_insert(&cnt, memcpy(malloc(1), "e", 1));
    CLBST_insert(&cnt, memcpy(malloc(1), "e", 1));
    CLBST_insert(&cnt, memcpy(malloc(1), "c", 1));
    CLBST_insert(&cnt, memcpy(malloc(1), "a", 1));
    CLBST_insert(&cnt, memcpy(malloc(1), "e", 1));
    CLBST_insert(&cnt, memcpy(malloc(1), "f", 1));
    CLBST_insert(&cnt, memcpy(malloc(1), "d", 1));
    CLBST_insert(&cnt, memcpy(malloc(1), "a", 1));
    CLBST_insert(&cnt, memcpy(malloc(1), "f", 1));
    CLBST_insert(&cnt, memcpy(malloc(1), "d", 1));
    CLBST_insert(&cnt, memcpy(malloc(1), "a", 1));

    printDot(cnt->root, 1);

    cnt = CLBST_destroy(cnt);



/*    for (int i = 0; i < 10000; i++) {
        char **word = makeWord(40);
        CLBST_root *cnt = CLBST_init(26, hashFn, char_compareTo, fieldSize);

        for (int j = 0; j < 40; j++)
            CLBST_insert(&cnt, word[j]);
        char eliminami = ((urnd().res % 26) + 'a');

        printf("graph PRECLBST%d {\n", i);
        printDot(cnt->root, 1);
        printf("}\n");

        printf("%d: %c\n",i,eliminami);
        CLBST_delete(&cnt, &eliminami);

        printf("graph POSTCLBST%d {\n", i);
        printDot(cnt->root, 1);
        printf("}\n");
        cnt = CLBST_destroy(cnt);

    }*/

//    CLBST_insert(&cnt, memcpy(malloc(1), "g", 1));
//    CLBST_insert(&cnt, memcpy(malloc(1), "r", 1));
//    CLBST_insert(&cnt, memcpy(malloc(1), "a", 1));
//    CLBST_insert(&cnt, memcpy(malloc(1), "n", 1));
//    CLBST_insert(&cnt, memcpy(malloc(1), "a", 1));
//    CLBST_insert(&cnt, memcpy(malloc(1), "t", 1));
//    CLBST_insert(&cnt, memcpy(malloc(1), "a", 1));
//    CLBST_insert(&cnt, memcpy(malloc(1), "g", 1));
//    CLBST_insert(&cnt, memcpy(malloc(1), "r", 1));
//    CLBST_insert(&cnt, memcpy(malloc(1), "a", 1));
//    CLBST_insert(&cnt, memcpy(malloc(1), "n", 1));
//    CLBST_insert(&cnt, memcpy(malloc(1), "a", 1));
//    CLBST_insert(&cnt, memcpy(malloc(1), "t", 1));
//    CLBST_insert(&cnt, memcpy(malloc(1), "a", 1));
//    CLBST_insert(&cnt, memcpy(malloc(1), "e", 1));
//    CLBST_insert(&cnt, memcpy(malloc(1), "e", 1));
//    CLBST_insert(&cnt, memcpy(malloc(1), "a", 1));
//    CLBST_insert(&cnt, memcpy(malloc(1), "m", 1));
//    CLBST_insert(&cnt, memcpy(malloc(1), "b", 1));
//    CLBST_insert(&cnt, memcpy(malloc(1), "b", 1));
//    CLBST_insert(&cnt, memcpy(malloc(1), "e", 1));
//    CLBST_insert(&cnt, memcpy(malloc(1), "e", 1));
//
//    CLBST_insert(&cnt, memcpy(malloc(1), "e", 1));
//    CLBST_insert(&cnt, memcpy(malloc(1), "d", 1));
//    CLBST_insert(&cnt, memcpy(malloc(1), "e", 1));
//    CLBST_insert(&cnt, memcpy(malloc(1), "b", 1));
//    CLBST_insert(&cnt, memcpy(malloc(1), "b", 1));
//    CLBST_insert(&cnt, memcpy(malloc(1), "a", 1));
//    CLBST_insert(&cnt, memcpy(malloc(1), "c", 1));
//
//    printf("graph {\n");
//    printDot(cnt->root, 1);
//    printf("}\n");
//    CLBST_delete(&cnt, &"d");
//
//    printf("graph {\n");
//    printDot(cnt->root, 1);
//    printf("}\n");

/*
    //tree init
    int i=0;
    printf("graph CLBST%d {\n", i);
    printDot(cnt->root, 1);
    printf("}\n");

    //delete 4e
    for (i = 1; i < 5; i++) {
        CLBST_delete(&cnt, &"e");
        printf("graph CLBST%d {\n", i);
        printDot(cnt->root, 1);
        printf("}\n");
    }

    //delete 2b
    CLBST_delete(&cnt, &"b");
    printf("graph CLBST%d {\n", i++);
    printDot(cnt->root, 1);
    printf("}\n");

    CLBST_delete(&cnt, &"b");
    printf("graph CLBST%d {\n", i++);
    printDot(cnt->root, 1);
    printf("}\n");

    //delete m
    CLBST_delete(&cnt, &"m");
    printf("graph CLBST%d {\n", i++);
    printDot(cnt->root, 1);
    printf("}\n");

    //delete a
    CLBST_delete(&cnt, &"a");
    printf("graph CLBST%d {\n", i);
    printDot(cnt->root, 1);
    printf("}\n");
*/

//        cnt = CLBST_destroy(cnt);

    return 0;
}