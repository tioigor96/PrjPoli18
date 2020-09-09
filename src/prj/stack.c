//
// Created by igor on 27/09/18.
//

#include "../../lib/prj/stack.h"

void *pop(stackcnt *st) {
    if (st == NULL || st->stack == NULL) {
        return NULL;
    }

    void *p = st->stack->stuck;
    stacked *head = st->stack;

    st->stack = head->p;
    st->in--;

    free(head);


    return p;
}

void push(stackcnt *st, void *p) {
    if (st == NULL) {
        return;
    }

    stacked *nh = calloc(1, sizeof(stacked));

    nh->stuck = p;
    nh->p = st->stack;

    st->stack = nh;
    st->in++;
}

unsigned int size(stackcnt *sc) {
    return sc->in;
}