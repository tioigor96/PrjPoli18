//
// Created by igor on 05/03/18.
//

#ifndef PRJPOLI18_LBST_H
#define PRJPOLI18_LBST_H

#include <stdio.h>
#include <malloc.h>
#include <assert.h>

typedef struct _HM_DLST HM_DLST;
typedef struct _BST_node BST_node;
typedef struct _HM_LSTPTR HM_LSTPTR;

struct _BST_node {
    void *f;
    HM_DLST *hm_dlst;
    struct _BST_node *l;        //*left node
    struct _BST_node *r;        //*right node
    struct _BST_node *p;        //*parent node
};

struct _HM_DLST {
    BST_node *node;
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
struct _LBST_container {
    BST_node *root;
    HM_LSTPTR *hm;
    int elm;

    int (*hashFn)(void *);          //return value [0 ; |D|]

    int (*compareTo)(void *, void *);

    void *rootF;
};

typedef struct _LBST_container LBST_root;

/**
 * Return a LBST_root with initialized params for linear insertion (Θ(n)).
 * [BST have a Θ(h)*Θ(n) time!]
 * Time: Θ(1)
 * @param hm
 * @param hashFn
 * @return
 */
LBST_root *LBST_init(int cards, int (*hashFn)(void *), int(*cmpTo)(void *, void *));

/**
 * Destroy correlate BST and info about that.
 * Time: 2*Θ(n)*Θ(|Σ|) (with n nodes)
 * @param cnt
 * @return
 */
LBST_root *LBST_destroy(LBST_root *cnt);

/**
 * Linear insertion for BST.
 * Time: Ο(max([σ_0 , σ_r],[σ_(r+1), σ_|Σ|])
 * @param cnt
 * @param nf
 * @return
 */
void LBST_insert(LBST_root **cnt, void *nf);

/**
 * Return the first element in LBST for that element (NOT CHECKED IF f IS IN DOMAIN FOR hashFn!).
 * Time: Θ(1)
 * @param cnt
 * @param f
 * @return
 */
BST_node *LBST_find(LBST_root *cnt, void *f);

/**
 * Delete the specified element f if present in LBST.
 * Time: Ο(max([σ_0 , σ_r],[σ_(r+1), σ_|Σ|])
 * @param cnt
 * @param f
 */
void LBST_delete(LBST_root **cnt, void *f);

/**
 * Procedure for print all BST with lambda.
 * Time: Θ(n) (with n nodes)
 * @param cnt
 * @param printF
 */
void LBST_print(LBST_root *cnt, void(*printF)(void *));

#endif //PRJPOLI18_LBST_H
