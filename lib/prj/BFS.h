//
// Created by igor on 27/09/18.
//

#ifndef PRJPOLI18_BFS_H
#define PRJPOLI18_BFS_H

#include "../../lib/prj/CLBST_s.h"
#include "../../lib/prj/stack.h"

/**
 * BFS to with sup limit for CBST. Time: O(|V|+|E|)= O((2|Σ|-1)+2(|Σ|-1))=O(4|Σ|-3)
 * @param leaf : where start
 * @param sze : number of nodes
 * @param limit : superior limit for iteration
 * @param map_bfs : how to get univocal mapping for each node
 * @return
 */
unsigned long int *BFS_limited(CBST_node *leaf, unsigned char sze, unsigned long int limit, unsigned char (*map_bfs)(void *));

#endif //PRJPOLI18_BFS_H
