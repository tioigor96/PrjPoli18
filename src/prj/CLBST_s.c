//
// Created by igor on 26/09/18.
//

//
// Created by igor on 18/08/18.
//

#include "../../lib/prj/CLBST_s.h"


// ####### Private functions
//HashMap List
void *HM_insert(CBST_node ***cell, CBST_node *new, unsigned int pos) {
    if (cell[0][pos] == NULL) {
        cell[0][pos] = new;
    }
    cell[1][pos] = new;
}

void HM_destroy(CBST_node ***cell) {
    free(cell[0]);
    free(cell[1]);
    free(cell);
}

//BST
CBST_node *CBST_destroy(CBST_node *root) {
    if (root != NULL) {
        CBST_destroy(root->l);   //destroy left child
        CBST_destroy(root->r);   //destroy right child
        free(root->f);
        free(root);      //destroy this node
    }
    return NULL;
}

// ####### End

CLBST_root *CLBST_init(size_t cards, int (*hashFn)(void *), int(*cmpTo)(void *, void *)) {
    CLBST_root *cnt = calloc(1, sizeof(CLBST_root));
    cnt->elm = cards;
    cnt->hashFn = hashFn;

    //hm:
    // - 0: fst
    // - 1: lst
    cnt->hm = (CBST_node ***) calloc(2, sizeof(CBST_node **));      //allocate 2 array pointer
    cnt->hm[0] = (CBST_node **) calloc(cards, sizeof(CBST_node *)); //allocate 1 array pointer of card elms
    cnt->hm[1] = (CBST_node **) calloc(cards, sizeof(CBST_node *)); //allocate 1 array pointer of card elms

    cnt->compareTo = cmpTo;

    return cnt;
}

CLBST_root *CLBST_destroy(CLBST_root *cnt) {
    cnt->root = CBST_destroy(cnt->root);
    cnt->compareTo = NULL;
    HM_destroy(cnt->hm);
    cnt->hashFn = NULL;
    cnt->rootF = NULL;
    free(cnt);
    return NULL;
}


int CLBST_insert(CLBST_root **cnt, void *nf) {

    //have i a LBST istance?
    if (nf == NULL || *(cnt) == NULL) {
        return 0;
    }

    //BASE: i haven't already a CBST
    if ((*(cnt))->root == NULL) {

        CBST_node *new = calloc(1, sizeof(CBST_node));
        new->f = nf;
        new->count = 1;

        HM_insert((*cnt)->hm, new, (*cnt)->hashFn(nf));
        (*(cnt))->root = new;
        (*(cnt))->rootF = nf;
        return 1;
    }

    //DEFINE INTERVALS
    int min = ((*(cnt))->compareTo(nf, (*(cnt))->rootF) <= 0) ? 0 : (*(cnt))->hashFn((*(cnt))->rootF);

    int i = (*(cnt))->hashFn(nf);

    //CASE1
    if ((*(cnt))->hm[0][i] != NULL && (*(cnt))->hm[1][i]->l == NULL) {
        (*(cnt))->hm[1][i]->count += 1;
        return -1;
    }

    //CASE 2/3:      new->p hasn't the same field of new
    CBST_node *new = calloc(1, sizeof(CBST_node));
    new->f = nf;
    new->count = 1;

    //CASE2
    for (int j = i - 1; j >= min; j--) {
        if ((*(cnt))->hm[0][j] != NULL) {
            if ((*(cnt))->hm[0][j]->r != NULL)     //i need the right node is empty. if not, some other after nf
                break;                                  //for hashFn was added before me. So i'm in case 3.

            (*(cnt))->hm[0][j]->r = new;      //i will connect to first istance of the first element on left of new
            HM_insert((*cnt)->hm, new, (*cnt)->hashFn(nf));
            new->p = (*(cnt))->hm[0][j];           // set parent
            return 1;
        }
    }

    //CASE 3
    for (int j = i + 1; /*j < max*/ ; j++) {
        if ((*(cnt))->hm[0][j] != NULL) {

            (*(cnt))->hm[1][j]->l = new;     //i will connect to last istance of the first element on right of new
            HM_insert((*cnt)->hm, new, (*cnt)->hashFn(nf));
            new->p = (*(cnt))->hm[1][j];     // set parent
            return 1;
        }
    }
}

CBST_node *CLBST_getLast(CLBST_root **cnt, void *lst) {
    return (*cnt)->hm[1][(*cnt)->hashFn(lst)];
}

leafLst *CLBST_getLeaf(CLBST_root **cnt) {
    leafLst *head = NULL;
    leafLst *p = NULL;

    for (int i = 0; i < (*cnt)->elm; i++) {

        CBST_node *l = (*cnt)->hm[1][i];

        if (l != NULL) {
            if (l->l == NULL && ((l->count == 1 && l->r == NULL) || l->count > 1)) {

                if (head == NULL) {
                    head = calloc(1, sizeof(leafLst));
                    head->l = l;
                    p = head;
                } else {
                    p->n = calloc(1, sizeof(leafLst));
                    p = p->n;
                    p->l = l;
                }

            }
        }
    }

    return head;
}

void CLBST_leafLst_destroy(leafLst *lst) {
    while (lst) {
        leafLst *aux = lst;
        lst = lst->n;
        free(aux);
    }
}
