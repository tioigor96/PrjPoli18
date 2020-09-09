//
// Created by igor on 02/03/18.
//

#include "../../lib/BST/BST.h"


BST_node *BST_general_insert(BST_node *root, BST_node *new, int (*compareTo)(void *, void *)) {

    if (new == NULL) {
        return NULL;
    }

    if (root == NULL) {         //there is no root in tree
        root = new;
    } else {                    //a root is present
        BST_node *parent = NULL;
        BST_node *find = root;
        while (find != NULL) {  //find position
            if (compareTo(new->f, find->f) <= 0) {
                parent = find;
                find = find->l;
            } else {
                parent = find;
                find = find->r;
            }
        }

        new->p = parent;        //set parent
        if (compareTo(new->f, parent->f) <= 0) {
            parent->l = new;
        } else {
            parent->r = new;
        }
    }

    return root;
}

BST_node *BST_destroy(BST_node *root) {
    if (root != NULL) {
        BST_destroy(root->l);   //destroy left child
        BST_destroy(root->r);   //destroy right child
        free(root->f);
        free(root);      //destroy this node
    }
    return NULL;
}

BST_node *BST_general_find(BST_node *root, BST_node *find, int(*compareTo)(void *, void *)) {
    if (find == NULL || root == NULL) {     //somebody do wrong things?
        return NULL;
    } else {
        while (root != NULL) {
            if (compareTo(root->f, find->f) == 0) {         //case equal
                return root;
            } else if (compareTo(find->f, root->f) < 0) {    //case less then root
                root = root->l;
            } else {                                //case great then root
                root = root->r;
            }
        }
    }

    return NULL;
}

BST_node *BST_parent(BST_node *root) {
    if (root != NULL) {
        return root->p;
    }
    return NULL;
}

BST_node *BST_min(BST_node *root) {
    while (root->l != NULL)
        root = root->l;
    return root;
}

BST_node *BST_max(BST_node *root) {
    while (root->r != NULL)
        root = root->r;
    return root;
}

BST_node *BST_general_delete(BST_node *root, BST_node *todlt, int(*compareTo)(void *, void *)) {
    if (root == NULL || todlt == NULL) {
        return root;
    }

    BST_node *y = NULL, *x = NULL;
    void *yf = todlt->f;        // i'll always delete the field

    if (todlt->l == NULL || todlt->r == NULL) { // i'm a full node, seminode or leaf
        y = todlt;
    } else {
        y = BST_max(todlt->l);
    }

    if (y->l != NULL) {
        x = y->l;
    } else {
        x = y->r;
    }

    if (x != NULL) {
        x->p = y->p;
    }

    //set parent (y is l or r child, or a root)
    if (y->p == NULL) {
        root = x;
    } else if (y == y->p->l) {
        y->p->l = x;
    } else {
        y->p->r = x;
    }

    if (y != x) {
        todlt->f = y->f;
    }

    //so the node is isolated
    free(yf);
    free(y);

    return root;
}

void BST_general_print(BST_node *root, void (*toPrint)(void *)) {
    if (root != NULL) {
        BST_general_print(root->l, toPrint);
        toPrint(root->f);
        BST_general_print(root->r, toPrint);
    }
}