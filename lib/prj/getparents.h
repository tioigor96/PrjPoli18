//
// Created by igor on 08/10/18.
//

#ifndef PRJPOLI18_GETPARENTS_H
#define PRJPOLI18_GETPARENTS_H

#include "CLBST_s.h"

/**
 * Structure for list of node in root leaf path:
 *  - len: weight of CBST node encountered in path
 *  - field: field of CBST node
 *  - leafField: the last field in list
 *  - next: [...]
 */
struct parent_node {
    unsigned int len;
    void *field;
    void *leafField;
    struct parent_node *next;
};
typedef struct parent_node parentPath;

/**
 * Structure for list with list:
 *  - single: path from root to leaf in CBST (see single->leafField for see which leaf you're going to)
 *  - next: [...]
 */
struct multi_parent_node {
    parentPath *single;
    struct multi_parent_node *next;
};
typedef struct multi_parent_node multiPartentPath;

/**
 * Get all path for each leaf in CBST
 * Time: O(|Σ|)*O(2|Σ|-1) = O(2|Σ|**2 - |Σ|)
 * @param node
 * @param cmpTo
 * @return
 */
multiPartentPath *allparents_path(leafLst *node, int (*cmpTo)(void *, void *));

/**
 * Test how far two root-leaf path are away (with superior limitation)
 * Time: [def: len(from/to): how many nodes are present in from/to list]
 *       max(len(from),len(to)) = max(O(2|Σ|-1),O(2|Σ|-1)) = O(2|Σ|-1)
 * @param to
 * @param from
 * @param cmp
 * @param max
 * @return
 */
int is_path_connect(parentPath *to, parentPath *from, int (*cmp)(void *, void *), unsigned long int max);

/**
 * Destroy single root-leaf path list.
 * Time: O(2|Σ|-1)
 * @param path
 */
void destroy_singlePath(parentPath *path);

/**
 * Destroy all root-leaf paths list.
 * Time: O(|Σ|)*O(2|Σ|-1) = O(2|Σ|**2 - |Σ|)
 * @param paths
 */
void destroy_multiPartentPath(multiPartentPath *paths);

#endif //PRJPOLI18_GETPARENTS_H
