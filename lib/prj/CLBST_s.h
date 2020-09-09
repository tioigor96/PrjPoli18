//
// Created by igor on 26/09/18.
//

#ifndef PRJPOLI18_CLBST_S_H
#define PRJPOLI18_CLBST_S_H

#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <string.h>

#ifndef valgrind_compliant
#define valgrind_compliant
#endif

typedef struct _CBST_node CBST_node;

struct _CBST_node {
    void *f;                    //*field
    unsigned int count;         //counter
    struct _CBST_node *l;       //*left node
    struct _CBST_node *r;       //*right node
    struct _CBST_node *p;       //*parent node
};


/**
 * Struct for linear insertion in BST (if we have a range)
 * *root: contain root of BST
 * *hm: contain the poiters to each leaf in Domain of BST
 * *hashFn: how to find the position in hm for a field in BST.
 */
struct _CLBST_container {
    CBST_node *root;
    CBST_node ***hm;
    int elm;

    int (*hashFn)(void *);          //return value [0 ; |D|]

    int (*compareTo)(void *, void *);

    void *rootF;
};

typedef struct _CLBST_container CLBST_root;

/**
 * List for return leaf of CBST;
 * *l: leaf
 * *n: next
 */
struct _leafLst {
    CBST_node *l;
    struct _leafLst *n;
};
typedef struct _leafLst leafLst;


/**
 * Return a CBST_root with initialized params for linear insertion (Θ(n)).
 * [BST have a Θ(h)*Θ(n) time!]
 * Time: Θ(1)
 * @param hm
 * @param hashFn
 * @return
 */
CLBST_root *CLBST_init(size_t cards, int (*hashFn)(void *), int(*cmpTo)(void *, void *));

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
 * @return 1 if add, -1 if accumulated, 0 if do nothing
 */
int CLBST_insert(CLBST_root **cnt, void *nf);

/**
 * Get last insertion for lst in CBST.
 * Time: Θ(1).
 * @param cnt
 * @param lst
 * @return
 */
CBST_node *CLBST_getLast(CLBST_root **cnt, void *lst);

/**
 * Get list of leaf present in CBST.
 * Time: Θ(|Σ|).
 * @param cnt
 * @return
 */
leafLst *CLBST_getLeaf(CLBST_root **cnt);

/**
 * Destroy leaf list
 * Time: O(|Σ|)
 * @param lst
 */
void CLBST_leafLst_destroy(leafLst *lst);

#endif //PRJPOLI18_CLBST_S_H
