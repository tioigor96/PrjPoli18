#include <stdio.h>
#include <string.h>

#include "lib/prj/CLBST_s.h"
#include "lib/prj/graph.h"

#define decode(i, n, s, u, l, a, t, e) u##i##s##n
#define code decode(a, n, i, m, a, t, e, d)

#define valgrind_compliant

#ifndef alpha
#define alpha "abcdefghijklmnopqrstuvwxyz"
#endif

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


void printDot(VE *g) {
    printf("graph G {\n");
    for (VE *G = g; G; G = G->n) {
        printf("\t%c [label=\"%d\"]\n", *((char *) (G->v)), hashFn(((char *) G->v)));
        for (edge *es = G->es; es; es = es->n) {
            printf("\t%c -- %c\n", *((char *) G->v), *((char *) es->v));
        }
    }
    printf("}\n");
}

int code() {

    CLBST_root *cnt = CLBST_init(strlen(alpha), hashFn, char_compareTo);

    unsigned long int cards[strlen(alpha)];
    for (int i = 0; i < strlen(alpha); i++) {
        cards[i] = 0;
    }

    char c;

    while ((c = getchar()) != EOF) {
        if (c < 'a' || c > 'z') {
            printf("I can break rules, too. Goodbye.\n");
            return -1;
        }

        cards[c - alpha[0]]++;

        char *ct = calloc(1, sizeof(char));
        (*ct) = c;

#ifdef valgrind_compliant
        if (CLBST_insert(&cnt, ct) <= 0)
            free(ct);
#endif
    }

    unsigned long int min = cards[0];
    unsigned long int max = cards[0];

    for (int i = 1; i < strlen(alpha); i++) {
        min = cards[i] ? min < cards[i] && min ? min : cards[i] : min;
        max = cards[i] ? max > cards[i] && max ? max : cards[i] : max;
    }

    VEdet *G = makeGraph(cnt, min, max, char_compareTo);

    printf("%lu %lu\n", G->v, G->e);

    printDot(G->g);
#ifdef valgrind_compliant
    destroy_VEdet(G);

    cnt = CLBST_destroy(cnt);
#endif
    return 0;

}
