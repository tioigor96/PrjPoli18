//
// Created by igor on 27/09/18.
//

#ifndef PRJPOLI18_STACK_H
#define PRJPOLI18_STACK_H

#include <stdlib.h>

struct _stacked {
    struct _stacked *p;
    void *stuck;
};
typedef struct _stacked stacked;

struct _stackcnt {
    stacked *stack;
    unsigned int in;
};
typedef struct _stackcnt stackcnt;

void *pop(stackcnt *cnt);

void push(stackcnt *st, void *p);

unsigned int size(stackcnt *sc);

#endif //PRJPOLI18_STACK_H
