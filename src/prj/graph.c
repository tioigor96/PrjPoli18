//
// Created by igor on 15/10/18.
//
#include "../../lib/prj/graph.h"


VEdet *makeGraph(CLBST_root *cnt, unsigned long int min, unsigned long int max,
                 int (*cmp)(void *, void *)) {
    leafLst *leafs = CLBST_getLeaf(&cnt);
    multiPartentPath *paths = allparents_path(leafs, cmp), *savepaths = paths;
    VE *G = NULL;
    VEdet *loc = calloc(1, sizeof(VEdet));
#ifdef valgrind_compliant
    CLBST_leafLst_destroy(leafs);
#endif
    for (multiPartentPath *i = paths; i; i = i->next) {
        loc->v += 1;
        VE *ga = calloc(1, sizeof(VE));
        ga->v = i->single->leafField;

        ga->n = G;
        G = ga;
        for (multiPartentPath *j = i->next; j; j = j->next) {
            unsigned long int d = 0;
            if ((d = is_path_connect(i->single, j->single, cmp, max)) && d >= min) {
                loc->e += 1;
                edge *ea = calloc(1, sizeof(edge));
                ea->v = j->single->leafField;
                ea->n = G->es;
                G->es = ea;
            }
        }

    }
#ifdef valgrind_compliant
    destroy_multiPartentPath(savepaths);
#endif
    loc->g = G;

    return loc;

}

void destroy_edges(VE *local) {
    while (local->es) {
        edge *aux = local->es;
        local->es = local->es->n;
        free(aux);
    }
}

void destroy_graph(VE *g) {
    while (g) {
        VE *aux = g;
        g = g->n;
        destroy_edges(aux);
        free(aux);
    }
}

void destroy_VEdet(VEdet *loc) {
    destroy_graph(loc->g);
    free(loc);
}