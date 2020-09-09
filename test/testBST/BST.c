//
// Created by igor on 03/03/18.
//
#include <memory.h>
#include "../../lib/BST/BST.h"


/**
 * How we compare chars with lambda-function
 * @param c1
 * @param c2
 * @return
 */
int char_compareTo(void *o1, void *o2) {
    char c1 = *((char *) o1);
    char c2 = *((char *) o2);

    if (c1 == c2) {
        return 0;
    } else if (c1 < c2) {
        return -1;
    } else {
        return 1;
    }
}

BST_node *BST_insert(BST_node *root, char c) {
    BST_node *new = calloc(1, sizeof(BST_node));
    //calloc do some operation by default... NULL is 0!
    /* new->p = NULL;
     new->l = NULL;
     new->r = NULL;*/
    char *ptr = malloc(sizeof(char));
    (*ptr) = c;
    new->f = ptr;
    root = BST_general_insert(root, new, char_compareTo);
    return root;

}

BST_node *BST_find(BST_node *root, char c) {
    BST_node *find = calloc(1, sizeof(BST_node));
    char *ptr = malloc(sizeof(char));
    (*ptr) = c;
    find->f = ptr;
    root = BST_general_find(root, find, char_compareTo);     //in root i would find the ptr to node
    free(find);                     //free useless node
    free(ptr);
    return root;
}

BST_node *BST_delete(BST_node *root, char c) {
    BST_node *todlt = BST_find(root, c);

    if (todlt != NULL)
        root = BST_general_delete(root, todlt, char_compareTo);

    return root;
}

unsigned int printDot(BST_node *root, unsigned int init) {
    if (root == NULL) {
        printf("\t%d [label=\"NIL\"];\n", init);
        return init;
    }

    char fld = *((char *) root->f);

    int local = init++;

    printf("\t%d [label=\"%c\"];\n", local, fld);

    if(root->l) {
        printf("\t%d -> %d\n", local, init);
        init = printDot(root->l, init);
        init++;
    }

    if(root->r){
        printf("\t%d -> %d\n", local, init);
        init = printDot(root->r, init);
        init++;
    }

    return init;
}

int main() {
    BST_node *root = NULL;

/*    root = BST_insert(root, 'c');
    root = BST_insert(root, 'b');
    root = BST_insert(root, 'c');
    root = BST_insert(root, 'd');
    BST_node *b = BST_find(root, 'b');
    BST_node *c = BST_find(root, 'c');*/

    root = BST_insert(root, 'd');
    root = BST_insert(root, 'a');
    root = BST_insert(root, 'a');
    root = BST_insert(root, 'a');
    root = BST_insert(root, 'd');
    root = BST_insert(root, 'd');
    root = BST_insert(root, 'd');
    root = BST_insert(root, 'b');
    root = BST_insert(root, 'b');
    root = BST_insert(root, 'd');
    root = BST_insert(root, 'e');


    /*BST_node *b = BST_find(root, 'b');
    BST_node *c = BST_find(root, 'd');
    BST_node *c1 = BST_find(b, 'd');*/


    //i'm sorry mom for my bad dreams
    void str_print(void *f) {
        printf("%c\n", *((char *) f));
    }

    BST_general_print(root, str_print);

    root = BST_delete(root, 'd');
    printf("----------\n");
    BST_general_print(root, str_print);

    root = BST_delete(root, 'c');
    printf("----------\n");
    BST_general_print(root, str_print);

    root = BST_delete(root, 'd');
    printf("----------\n");
    BST_general_print(root, str_print);

    root = BST_delete(root, 'b');
    printf("----------\n");
    BST_general_print(root, str_print);

    root = BST_destroy(root);

    //edfddeecaefdafda
    root = BST_insert(root, 'e');
    root = BST_insert(root, 'd');
    root = BST_insert(root, 'f');
    root = BST_insert(root, 'd');
    root = BST_insert(root, 'd');
    root = BST_insert(root, 'e');
    root = BST_insert(root, 'e');
    root = BST_insert(root, 'c');
    root = BST_insert(root, 'a');
    root = BST_insert(root, 'e');
    root = BST_insert(root, 'f');
    root = BST_insert(root, 'd');
    root = BST_insert(root, 'a');
    root = BST_insert(root, 'f');
    root = BST_insert(root, 'd');
    root = BST_insert(root, 'a');


    printDot(root, 1);

    root = BST_destroy(root);

    //macro testing
    char *str1 = malloc(5), *str2 = malloc(6);
    strcpy(str1, "ciao");
    strcpy(str2, "mondo");


    printf("%s\n", _(_(str1, " "), str2));

    return 0;

}