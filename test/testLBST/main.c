//
// Created by igor on 21/08/18.
//

#include <string.h>
#include "../../lib/LBST/LBST.h"

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

    unsigned int printDot(BST_node *root, int init) {
        if (root == NULL) {
            printf("\t%d [label=\"NIL\"];\n",init);
            return init;
        }

        char fld = *((char *) root->f);

        int local = init++;

        printf("\t%d [label=\"%c\"];\n", local, fld);

        printf("\t%d->%d\n", local, init);
        init = printDot(root->l, init);
        init++;
//        if(root->l){
//            printf("\t%d->%d\n", local, init);
//            init = printDot(root->l, init);
//            init++;
//        } else {
//            printf("\t%d->%d\n", local, 0);
//        }


        printf("\t%d->%d\n", local, init);
        init = printDot(root->r, init);
        init++;

//        if(root->r){
//            printf("\t%d->%d\n", local, init);
//            init = printDot(root->r, init);
//            init++;
//        } else {
//            printf("\t%d->%d\n", local, 0);
//        }


        return init;
    }

    LBST_root *cnt = LBST_init(26, hashFn, char_compareTo);

    LBST_insert(&cnt, memcpy(malloc(1), "a", 1));
    LBST_insert(&cnt, memcpy(malloc(1), "a", 1));
    LBST_insert(&cnt, memcpy(malloc(1), "a", 1));
    LBST_insert(&cnt, memcpy(malloc(1), "a", 1));
    LBST_insert(&cnt, memcpy(malloc(1), "e", 1));
    LBST_insert(&cnt, memcpy(malloc(1), "c", 1));
    LBST_insert(&cnt, memcpy(malloc(1), "b", 1));
    LBST_insert(&cnt, memcpy(malloc(1), "d", 1));
    LBST_insert(&cnt, memcpy(malloc(1), "g", 1));
    LBST_insert(&cnt, memcpy(malloc(1), "f", 1));
    LBST_insert(&cnt, memcpy(malloc(1), "h", 1));
//    LBST_insert(&cnt, memcpy(malloc(1), "a", 1));
//    LBST_insert(&cnt, memcpy(malloc(1), "t", 1));
//    LBST_insert(&cnt, memcpy(malloc(1), "a", 1));

    printf("digraph LBST {\n");
    printDot(cnt->root, 1);
    printf("}\n");

    cnt = LBST_destroy(cnt);

    return 0;
}