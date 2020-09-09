//
// Created by igor on 18/08/18.
//

#include "../../lib/CLBST/CLBST.h"


// ####### Private functions

//HashMap List
HM_DLST *HM_LSTPTR_insert_queue(HM_LSTPTR *cell, CBST_node *new) {
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

HM_DLST *HM_LSTPTR_insert_middle(HM_LSTPTR *cell, HM_DLST *ref, CBST_node *new) {

    assert(cell && ref);

    HM_DLST *tmpL = calloc(1, sizeof(HM_DLST));

    tmpL->node = new;
    new->hm_dlst = tmpL;

    tmpL->n = ref;
    tmpL->p = ref->p;
    ref->p = tmpL;

    if (ref == cell->f) {
        cell->f = tmpL;
    }

    return tmpL;
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
CBST_node *CBST_destroy(CBST_node *root) {
    if (root != NULL) {
        CBST_destroy(root->l);   //destroy left child
        CBST_destroy(root->r);   //destroy right child
        root->hm_dlst = NULL;
        free(root->f);
        free(root);      //destroy this node
    }
    return NULL;
}

void BST_general_print(CBST_node *root, void (*toPrint)(void *)) {
    if (root != NULL) {
        BST_general_print(root->l, toPrint);
        for (int i = 0; i < root->count; i++)
            toPrint(root->f);
        BST_general_print(root->r, toPrint);
    }
}

// ####### End

CLBST_root *CLBST_init(int cards, int (*hashFn)(void *), int(*cmpTo)(void *, void *), size_t(*fnFieldSize)(void *)) {
    CLBST_root *cnt = calloc(1, sizeof(CLBST_root));
    cnt->elm = cards;
    cnt->hashFn = hashFn;
    cnt->hm = calloc((size_t) cards, sizeof(HM_LSTPTR));
    cnt->compareTo = cmpTo;
    cnt->fieldSizeFn = fnFieldSize;

    return cnt;
}

CLBST_root *CLBST_destroy(CLBST_root *cnt) {
    cnt->root = CBST_destroy(cnt->root);
    cnt->compareTo = NULL;
    HM_LSTPTR_destroy(cnt->hm, cnt->elm);
    cnt->hashFn = NULL;
    cnt->rootF = NULL;
    free(cnt);
    return NULL;
}

void CLBST_insert(CLBST_root **cnt, void *nf) {

    //have i a LBST istance?
    if (nf == NULL || *(cnt) == NULL) {
        return;
    }

    CBST_node *new = calloc(1, sizeof(CBST_node));
    new->f = nf;
    new->count = 1;

    //BASE: i haven't already a CBST
    if ((*(cnt))->root == NULL) {
        new->hm_dlst = HM_LSTPTR_insert_queue(&(*(cnt))->hm[(*(cnt))->hashFn(nf)], new);
        (*(cnt))->root = new;
        (*(cnt))->rootF = nf;
        return;
    }

    //DEFINE INTERVALS
    int min = ((*(cnt))->compareTo(nf, (*(cnt))->rootF) <= 0) ? 0 : (*(cnt))->hashFn((*(cnt))->rootF);
    //define position of root;
    /*int i_root = (*(cnt))->hashFn((*(cnt))->rootF);*/
    //max not need, because i search first to l, after to right. if precondition is respected, i can ignore max
    /*int max = (*cnt)->elm;*/
    //find position's new in hm
    int i = (*(cnt))->hashFn(nf);

    //CASE1     (l'ultimo nodo per nf è init e ho spazio a sx)
    //has new->p same field of new?
    if ((*(cnt))->hm[i].f != NULL && (*(cnt))->hm[i].lst->node->l == NULL) {
        //precondition check: i need hm[j].lst->l is null. if not, some errors
        assert((*(cnt))->hm[i].f != NULL && (*(cnt))->hm[i].lst->node->l == NULL);
        assert((*(cnt))->compareTo((*(cnt))->hm[i].lst->node->f, nf) == 0);

        // increment counter because new->f has same of hm[i].lst->node->f for compareTo
        (*(cnt))->hm[i].lst->node->count += 1;

        //free useless space for new and nf
        free(nf);
        free(new);
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
            new->hm_dlst = HM_LSTPTR_insert_queue(&(*(cnt))->hm[i], new);
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
            new->hm_dlst = HM_LSTPTR_insert_queue(&(*(cnt))->hm[i], new);
            new->p = (*(cnt))->hm[j].lst->node;     // set parent
            return;
        }
    }
}

CBST_node *CLBST_find(CLBST_root *cnt, void *f) {
    return ((cnt->hm[cnt->hashFn(f)].f) != NULL) ? (*cnt).hm[(*cnt).hashFn(f)].f->node : NULL;
}

void CLBST_delete(CLBST_root **cnt, void *f) {
    if (f == NULL || *(cnt) == NULL) {
        return;
    }

    //find node position
    CBST_node *todlt = NULL, *y = NULL, *x = NULL;
    if ((todlt = CLBST_find(*(cnt), f)) == NULL)     //check if f is in tree
        return;

    //case 1: node has multiple same field in sx (counter > 1), so predecessor is itself.
    //          not need to modify hm: is correctly setted
    if (todlt->count > 1) {
        todlt->count -= 1;
        return;
    }

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

    //case 2: todlt->counter == 1, y->counter>1. so todlt->f = y->f, delete todlt->f, y->counter-1.
    if (y && y->count > 1) {
        assert(todlt->count == 1);

        //case 2.1: y is the left child of todlt, so i need to delete todlt
        if (y == todlt->l) {
            assert(y->r==NULL);
            //unlink todlt and set y as child
            y->r = todlt->r;
            y->p = todlt->p;

            if (todlt->p != NULL) { //am I Groot?
                if(todlt->p->l == todlt)
                    todlt->p->l = y;
                else
                    todlt->p->r = y;
            } else {    //i'm Groot!
                (*cnt)->root = y;
                (*cnt)->rootF = y->f;
            }

            //unlink hm_pos
            HM_LSTPTR_unlink(&((*cnt)->hm[pos]), hm_pos);

            //free some other
            free(hm_pos);
            free(yf);
            free(todlt);

            return;
        } else {    //case 2.2: y is the left child of todlt, so i don't delete a real node

            //duplicate y->f and update counter for y
            size_t fieldSize = (*(cnt))->fieldSizeFn(y->f);
            todlt->f = memcpy(calloc(1, fieldSize), y->f, fieldSize);
            y->count -= 1;
            assert(y->count >= 1);

            //unlink hm_pos
            HM_LSTPTR_unlink(&((*cnt)->hm[pos]), hm_pos);

            //duplicate node for y for respect hm for bst
            todlt->hm_dlst = HM_LSTPTR_insert_middle(&((*cnt)->hm[(*cnt)->hashFn(y->f)]), y->hm_dlst, todlt);

            //frees
            free(hm_pos);
            free(yf);

            return;
        }
    }

    //case 3.x: need to remove fisically a node in tree.
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
        size_t fieldSize = (*(cnt))->fieldSizeFn(y->f);
        todlt->f = y->f;
        todlt->hm_dlst = y->hm_dlst;    //set again the position for hm in CLBST node
        todlt->hm_dlst->node = todlt;   //set again the position for CLSBT node in hm
    }

    //unlink node in hm
    HM_LSTPTR_unlink(&((*cnt)->hm[pos]), hm_pos);

    //but if todlt->f is the field of BST root?
    if ((*cnt)->rootF != NULL && (*cnt)->rootF != (*cnt)->root->f) {
        (*cnt)->rootF = (*cnt)->root->f;
    }

    //so the CLBST and HM node is isolated
    free(yf);
    free(hm_pos);
    free(y);
}

void CLBST_print(CLBST_root *cnt, void(*printF)(void *)) {
    BST_general_print(cnt->root, printF);
}
