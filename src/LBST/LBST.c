//
// Created by igor on 05/03/18.
//

#include "../../lib/LBST/LBST.h"

// ####### Private functions

//HashMap List
HM_DLST *HM_LSTPTR_insert(HM_LSTPTR *cell, BST_node *new) {
    HM_DLST *tmp = calloc(1, sizeof(HM_DLST));
    if (cell->f == NULL) {     //create first node
        cell->f = tmp;
        //calloc do some magic
        /*cell->lst->n = NULL;
        cell->lst->p = NULL;*/
    } else {                //new node is coming!
        tmp->p = cell->lst;
        cell->lst->n = tmp;
    }

    cell->lst = tmp;
    cell->lst->node = new;

    return tmp;
}

HM_DLST *HM_LSTPTR_unlink(HM_LSTPTR *cell, HM_DLST *node) {
    if (cell->f != node && cell->lst != node) {  //central occurrence
        node->p->n = node->n;
        node->n->p = node->p;
    } else {
        if (cell->f == node) {  //is the first occurrence
            cell->f = node->n;
            if (node->n != NULL) {
                node->n->p = NULL;
            }
        }

        if (cell->lst == node) {//is the last occurrence
            cell->lst = node->p;
            if (node->p != NULL) {
                node->p->n = NULL;
            }
        }
    }
    return node;
}


void HM_LSTPTR_destroy(HM_LSTPTR cell[], int dim) {
    for (int i = 0; i < dim; i++) {
        for (HM_DLST *aux = cell[i].f; aux != NULL;) {
            HM_DLST *next = aux->n;
            free(aux);
            aux = next;
        }
    }
    free(cell);
}

//BST
BST_node *BST_destroy(BST_node *root) {
    if (root != NULL) {
        BST_destroy(root->l);   //destroy left child
        BST_destroy(root->r);   //destroy right child
        root->hm_dlst = NULL;
        free(root->f);
        free(root);      //destroy this node
    }
    return NULL;
}

void BST_general_print(BST_node *root, void (*toPrint)(void *)) {
    if (root != NULL) {
        BST_general_print(root->l, toPrint);
        toPrint(root->f);
        BST_general_print(root->r, toPrint);
    }
}

// ####### End

LBST_root *LBST_init(int cards, int (*hashFn)(void *), int(*cmpTo)(void *, void *)) {
    LBST_root *cnt = calloc(1, sizeof(LBST_root));
    cnt->elm = cards;
    cnt->hashFn = hashFn;
    cnt->hm = calloc((size_t) cards, sizeof(HM_LSTPTR));
    cnt->compareTo = cmpTo;

    return cnt;
}

LBST_root *LBST_destroy(LBST_root *cnt) {
    cnt->root = BST_destroy(cnt->root);
    cnt->compareTo = NULL;
    HM_LSTPTR_destroy(cnt->hm, cnt->elm);
    cnt->hashFn = NULL;
    cnt->rootF = NULL;
    free(cnt);
    return NULL;
}

void LBST_insert(LBST_root **cnt, void *nf) {

    //have i a LBST istance?
    if (nf == NULL || *(cnt) == NULL) {
        return;
    }

    BST_node *new = calloc(1, sizeof(BST_node));
    new->f = nf;

    //BASE: i haven't already a BST
    if ((*(cnt))->root == NULL) {
        new->hm_dlst = HM_LSTPTR_insert(&(*(cnt))->hm[(*(cnt))->hashFn(nf)], new);
        (*(cnt))->root = new;
        (*(cnt))->rootF = nf;
        return;
    }

    //DEFINE INTERVALS
    //min for pre:
    //int min = ((*(cnt))->compareTo(nf, (*(cnt))->rootF) <= 0) ? 0 : (*(cnt))->hashFn((*(cnt))->rootF) + 1;
    int min = ((*(cnt))->compareTo(nf, (*(cnt))->rootF) <= 0) ? 0 : (*(cnt))->hashFn((*(cnt))->rootF);
    //define position of root;
    /*int i_root = (*(cnt))->hashFn((*(cnt))->rootF);*/
    //max not need, because i search first to l, after to right. if precondition is respected, i can ignore max
    /*int max = (*cnt)->elm;*/
    //find position's new in hm
    int i = (*(cnt))->hashFn(nf);

/*    //precondition check
    if ((*(cnt))->compareTo(nf, (*(cnt))->rootF) <= 0) { //i'm a left node
        //precondition: (*(cnt))->root->l != null
        if (!(*(cnt))->root->l) {               //root->l is null
            (*(cnt))->root->l = new;                    //insert for respect precondition
            new->hm_dlst = HM_LSTPTR_insert(&(*(cnt))->hm[i], new);
            new->p = (*(cnt))->root;
            return;
        }
    } else {
        //precondition: (*(cnt))->root->r != null
        if (!(*(cnt))->root->r) {               //root->r is null
            (*(cnt))->root->r = new;                    //insert for respect precondition
            new->hm_dlst = HM_LSTPTR_insert(&(*(cnt))->hm[i], new);
            new->p = (*(cnt))->root;
            return;
        }
    }
*/
    //PRECONDITIONS ARE OK
    //CASE1     (l'ultimo nodo per nf è init e ho spazio a sx)
    //has new->p same field of new?
    if ((*(cnt))->hm[i].f != NULL && (*(cnt))->hm[i].lst->node->l == NULL) {
        //precondition check: i need hm[j].lst->l is null. if not, some errors
        assert((*(cnt))->hm[i].f != NULL && (*(cnt))->hm[i].lst->node->l == NULL);

        new->p = (*(cnt))->hm[i].lst->node;
        (*(cnt))->hm[i].lst->node->l = new;
        //set node's ptr for hashmap and add new in hashmap list
        new->hm_dlst = HM_LSTPTR_insert(&(*(cnt))->hm[i], new);
        return;
    }

    //CASE 2/3:      new->p hasn't the same field of new

    //CASE2         I can connect new in a right of leaf->field < new->field
    //can j connect to right of other element?
    for (int j = i - 1; j >= min; j--) {
        if ((*(cnt))->hm[j].f != NULL) {
            if ((*(cnt))->hm[j].f->node->r != NULL)     //i need the right node is empty. if not, some other after nf
                break;                                  //for hashFn was added before me. So i'm in case 3.

            (*(cnt))->hm[j].f->node->r = new;      //i will connect to first istance of the first element on left of new
            new->hm_dlst = HM_LSTPTR_insert(&(*(cnt))->hm[i], new);
            new->p = (*(cnt))->hm[j].f->node;           // set parent
            return;
        }
    }

    //CASE 3
    //no, i can't, i'll connect to left for some leaf.
    for (int j = i + 1; /*j < max*/ ; j++) {
        if ((*(cnt))->hm[j].f != NULL) {
            //precondition check: i need hm[j].lst->l is null. if not, some errors
            assert((*(cnt))->hm[j].f != NULL && (*(cnt))->hm[j].lst->node->l == NULL);

            (*(cnt))->hm[j].lst->node->l = new;     //i will connect to last istance of the first element on right of new
            new->hm_dlst = HM_LSTPTR_insert(&(*(cnt))->hm[i], new);
            new->p = (*(cnt))->hm[j].lst->node;     // set parent
            return;
        }
    }
}

BST_node *LBST_find(LBST_root *cnt, void *f) {
    return ((cnt->hm[cnt->hashFn(f)].f) != NULL) ? (*cnt).hm[(*cnt).hashFn(f)].f->node : NULL;
}

void LBST_delete(LBST_root **cnt, void *f) {
    if (f == NULL || *(cnt) == NULL) {
        return;
    }

    //find node position
    BST_node *todlt = NULL, *y = NULL, *x = NULL;
    if ((todlt = LBST_find(*(cnt), f)) == NULL)     //check if f is in tree
        return;

    HM_DLST *hm_pos = todlt->hm_dlst;
    void *yf = todlt->f;
    int pos = (*(cnt))->hashFn(f);

    if (todlt->l == NULL || todlt->r == NULL) { // i'm a node w 1 child or a leaf
        y = todlt;
    } else {
        //find predecessor
        if ((*(cnt))->hm[pos].lst != hm_pos) {  // i don't select the last instance of field
            y = hm_pos->n->node;
        } else {                                // unfortunately i selected the last one
            int min = ((*(cnt))->compareTo(f, (*(cnt))->rootF) <= 0) ? 0 : (*(cnt))->hashFn((*(cnt))->rootF) + 1;
            for (int j = pos - 1; j >= min; j--) {
                if ((*cnt)->hm[j].f != NULL) {
                    y = (*(cnt))->hm[j].f->node;
                    break;
                }
            }
        }
    }

    x = y->l != NULL ? y->l : y->r;

    if (x != NULL) {
        x->p = y->p;
    }

    //set parent (y is l or r child, or root)
    if (y->p == NULL) {         // y is root! so i've only one node in LBST
        (*(cnt))->root = x;
        if (x == NULL) {        // is todlt the last node in LBST?
            (*cnt)->rootF = NULL;
        }
    } else if (y == y->p->l) {
        y->p->l = x;
    } else {
        y->p->r = x;
    }

    if (y != x) {               //here i change the status of HM, so do some tricks
        todlt->f = y->f;
        todlt->hm_dlst = y->hm_dlst;    //set again the position for hm in LBST node
        todlt->hm_dlst->node = todlt;   //set again the position for LSBT node in hm
    }

    //unlink node in hm
    /*if ((*cnt)->hm[pos].f == hm_pos) {  //is the first occurrence
        (*cnt)->hm[pos].f = hm_pos->n;
        if (hm_pos->n != NULL) {
            hm_pos->n->p = NULL;
        }
    }

    if ((*cnt)->hm[pos].lst == hm_pos) {//is the last occurrence
        (*cnt)->hm[pos].lst = hm_pos->p;
        if (hm_pos->p != NULL) {
            hm_pos->p->n = NULL;
        }
    }

    if ((*cnt)->hm[pos].f == hm_pos && (*cnt)->hm[pos].lst == hm_pos) {  //central occurrence
        hm_pos->p->n = hm_pos->n;
        hm_pos->n->p = hm_pos->p;

    }*/
    HM_LSTPTR_unlink(&((*cnt)->hm[pos]), hm_pos);

    //but if todlt->f is the field of BST root?
    if ((*cnt)->rootF != NULL && (*cnt)->rootF != (*cnt)->root->f) {
        (*cnt)->rootF = (*cnt)->root->f;
    }

    //so the LBST and HM node is isolated
    free(yf);
    free(hm_pos);
    free(y);
}

void LBST_print(LBST_root *cnt, void(*printF)(void *)) {
    BST_general_print(cnt->root, printF);
}