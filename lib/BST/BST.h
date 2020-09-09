//
// Created by igor on 02/03/18.
//

#ifndef PRJPOLI18_BST_H
#define PRJPOLI18_BST_H

#include <stdio.h>
#include <malloc.h>

#ifndef LEN
#define LEN(x) strlen(x)
#endif

#ifndef CA
#define CA(x) calloc(x,sizeof(char))
#endif

#ifndef CO
#define CO(x, y) strcpy(x,y)
#endif

#ifndef _
#define _(x, y) strcat(CO(CA(LEN(x) + LEN(y)),x),y)
#endif

/**
 * Struct for BST's node.
 * f: field in node
 * l: left node
 * r: right node
 * p: parent node
 */
struct _BST_node {
    void *f;
    struct _BST_node *l;        //*left node
    struct _BST_node *r;        //*right node
    struct _BST_node *p;        //*parent node
};
typedef struct _BST_node BST_node;

/**
 * General method with lambda-function to insert into a BSTree a new node.
 * @param root
 * @param new
 * @param compareTo: function to compare fields
 * @return root
 */
BST_node *BST_general_insert(BST_node *root, BST_node *new, int (*compareTo)(void *, void *));

/**
 * Delete the BSTree from memory
 * @param root
 */
BST_node *BST_destroy(BST_node *root);


/**
 * General method with lambda-function to search into a BSTree the FIRST node.
 * @param root
 * @param find
 * @param compareTo
 * @return
 */
BST_node *BST_general_find(BST_node *root, BST_node *find, int(*compareTo)(void *, void *));

/**
 * Return the parent for a node.
 * @param root
 * @return
 */
BST_node *BST_parent(BST_node *root);

/**
 * Return the leaf in BST with minimum in BST(root)
 * @param root
 * @return
 */
BST_node *BST_min(BST_node *root);


BST_node *BST_parent(BST_node *root);

/**
 * Return the leaf in BST with maximum in BST(root)
 * @param root
 * @return
 */
BST_node *BST_max(BST_node *root);


/**
 * General method with lambda-function to delete a node with that field in BST
 * @param root
 * @param todlt
 * @param compareTo
 * @return
 */
BST_node *BST_general_delete(BST_node *root, BST_node *todlt, int(*compareTo)(void *, void *));

/**
 * General method with lambda-function to print a BST
 * @param root
 * @param toPrint
 */
void BST_general_print(BST_node *root, void (*toPrint)(void *));

#endif //PRJPOLI18_BST_H
