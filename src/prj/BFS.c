//
// Created by igor on 27/09/18.
//
#include "../../lib/prj/BFS.h"

unsigned long int *BFS_limited(CBST_node *leaf, unsigned char sze, unsigned long int limit,
                               unsigned char (*map_bfs)(void *)) {

    char *s = calloc(sze, sizeof(char));
    unsigned long int *d = calloc(sze, sizeof(unsigned long int));

    stackcnt stack;
    stack.in = 0;
    stack.stack = NULL;

    d[map_bfs(leaf->f)] = leaf->count - 1;
    s[map_bfs(leaf->f)] = 1;

    push(&stack, leaf);

    while (size(&stack) > 0) {
        CBST_node *v = pop(&stack);
        CBST_node *i = v->p;
        CBST_node *j = v->r;
        CBST_node *k = v->l;

        void up(CBST_node *l) {
            if (l == NULL) {
                return;
            }
            unsigned char pos = map_bfs(l->f);
            if (!s[pos] && (d[map_bfs(v->f)] + l->count) < limit) {
                d[pos] = d[map_bfs(v->f)] + l->count;
                s[pos] = 1;
                push(&stack, l);
            }
        }

        up(i);
        up(j);
        up(k);

        s[map_bfs(v->f)] = 2;
    }

    free(s);

    return d;
}