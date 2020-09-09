//
// Created by igor on 18/08/18.
//

#ifndef PRJPOLI18_CLBST_H
#define PRJPOLI18_CLBST_H

#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <string.h>

typedef struct _HM_DLST HM_DLST;
typedef struct _CBST_node CBST_node;
typedef struct _HM_LSTPTR HM_LSTPTR;

struct _CBST_node {
    void *f;                    //*field
    unsigned int count;         //counter
    HM_DLST *hm_dlst;
    struct _CBST_node *l;       //*left node
    struct _CBST_node *r;       //*right node
    struct _CBST_node *p;       //*parent node
};

struct _HM_DLST {
    CBST_node *node;
    struct _HM_DLST *n;
    struct _HM_DLST *p;
};

struct _HM_LSTPTR {
    HM_DLST *f;
    HM_DLST *lst;
};

/**
 * Struct for linear insertion in BST (if we have a range)
 * *root: contain root of BST
 * *hm: contain the poiters to each leaf in Domain of BST
 * *hashFn: how to find the position in hm for a field in BST.
 */
struct _CLBST_container {
    CBST_node *root;
    HM_LSTPTR *hm;
    int elm;

    int (*hashFn)(void *);          //return value [0 ; |D|]

    int (*compareTo)(void *, void *);

    size_t (*fieldSizeFn)(void *);

    void *rootF;
};

typedef struct _CLBST_container CLBST_root;

/**
 * Return a CBST_root with initialized params for linear insertion (Θ(n)).
 * [BST have a Θ(h)*Θ(n) time!]
 * Time: Θ(1)
 * @param hm
 * @param hashFn
 * @return
 */
CLBST_root *CLBST_init(int cards, int (*hashFn)(void *), int(*cmpTo)(void *, void *),
                       size_t(*fnFieldSize)(void *));

/**
 * Destroy correlate CBST and info about that.
 * Time: 2*Θ(n)*Θ(|Σ|) (with n nodes)
 * @param cnt
 * @return
 */
CLBST_root *CLBST_destroy(CLBST_root *cnt);

/**
 * Linear insertion for CBST.
 * If nf is still a leaf, insert increment node->counter and delete nf
 * Time: Ο(max([σ_0 , σ_r],[σ_(r+1), σ_|Σ|])
 * @param cnt
 * @param nf
 * @return
 */
void CLBST_insert(CLBST_root **cnt, void *nf);

/**
 * Return the first element in CLBST for that element (NOT CHECKED IF f IS IN DOMAIN FOR hashFn!).
 * Time: Θ(1)
 * @param cnt
 * @param f
 * @return
 */
CBST_node *CLBST_find(CLBST_root *cnt, void *f);

/**
 * Delete the specified element f if present in CLBST.
 * Time: Ο(max([σ_0 , σ_r],[σ_(r+1), σ_|Σ|])
 * @param cnt
 * @param f
 */
void CLBST_delete(CLBST_root **cnt, void *f);

/**
 * Procedure for print all CBST with lambda.
 * Time: Θ(n) (with n nodes)
 * @param cnt
 * @param printF
 */
void CLBST_print(CLBST_root *cnt, void(*printF)(void *));


#endif //PRJPOLI18_CLBST_H
