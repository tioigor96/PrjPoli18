//
// Created by igor on 08/10/18.
//

#include "../../lib/prj/getparents.h"

parentPath *getparents_path(CBST_node *node, int (*cmpTo)(void *, void *)) {

    if (!node) {
        return NULL;
    }

    void *leaf = node->f;

    parentPath *coda = calloc(1, sizeof(parentPath));
    coda->field = node->f;
    coda->len = node->count;

    CBST_node *prec = node;
    node = node->p;

    while (node) {
        parentPath *aux = calloc(1, sizeof(parentPath));

        aux->field = node->f;
        aux->len = cmpTo(prec->f, node->f) < 0 ? node->count : 1;

        aux->next = coda;
        coda = aux;
        prec = node;
        node = node->p;
    }

    coda->leafField = leaf;

    return coda;

}

multiPartentPath *allparents_path(leafLst *nodes, int (*cmpTo)(void *, void *)) {

    if (!nodes) {
        return NULL;
    }

    multiPartentPath *head = calloc(1, sizeof(multiPartentPath)), *aux = head;

    aux->single = getparents_path(nodes->l, cmpTo);
    nodes = nodes->n;

    while (nodes) {
        multiPartentPath *a1 = calloc(1, sizeof(multiPartentPath));
        a1->single = getparents_path(nodes->l, cmpTo);
        nodes = nodes->n;
        aux->next = a1;
        aux = a1;
    }

    return head;
}

int is_path_connect(parentPath *to, parentPath *from, int (*cmp)(void *, void *), unsigned long int max) {
    while (to && from && cmp(to->field, from->field) == 0 && to->len == from->len) {
        to = to->next;
        from = from->next;
    }

    unsigned long int dist = 0;

    if (cmp(to->field, from->field) == 0) {
        dist = (from->len > to->len ? from->len - to->len : to->len - from->len);

        to = to->next;
        from = from->next;
    }


    while (from || to) {
        if (dist > max) return 0;
        if (from) {
            dist += from->len;
            from = from->next;
        }
        if (dist > max) return 0;
        if (to) {
            dist += to->len;
            to = to->next;
        }
    }

    return dist > max ? 0 : dist;

}

void destroy_singlePath(parentPath *path) {
    while (path) {
        parentPath *aux = path;
        path = path->next;
        free(aux);
    }
}

void destroy_multiPartentPath(multiPartentPath *paths) {
    while (paths) {
        multiPartentPath *aux = paths;
        paths = paths->next;
        destroy_singlePath(aux->single);
        free(aux);
    }

}