//
// Created by igor on 15/10/18.
//

#ifndef PRJPOLI18_GRAPH_H
#define PRJPOLI18_GRAPH_H

#ifndef valgrind_compliant
#define valgrind_compliant
#endif

#include "../../lib/prj/CLBST_s.h"
#include "../../lib/prj/getparents.h"

/**
 * Structure for edges
 *  - v: pointer to vertex (field)
 *  - n: next
 */
struct _edge {
    void *v;
    struct _edge *n;
};
typedef struct _edge edge;

/**
 * Structure for vertex and his edges
 *  - v: pointer to vertex (field)
 *  - es: pointer to edges
 *  - n: next vertex
 */
struct _VE {
    void *v;
    edge *es;
    struct _VE *n;
};
typedef struct _VE VE;

/**
 * Structure with graph described with VE struct and his data:
 *  - g: g described from vertex
 *  - v: number of vertex
 *  - e: number of edges
 */
struct _VEdet {
    VE *g;
    unsigned long int v;
    unsigned long int e;
};
typedef struct _VEdet VEdet;

/**
 * Make graph from CLBST container
 * Time: O(|Σ|!/2!(|Σ|-2)!) + 2*O(2|Σ|**2 - |Σ|) + Θ(|Σ|) + O(|Σ|) = O(|Σ|**2 - |Σ|)
 * @param cnt
 * @param size
 * @param min
 * @param max
 * @param cmp
 * @return
 */
VEdet *makeGraph(CLBST_root *cnt, unsigned long int min, unsigned long int max, int (*cmp)(void *, void *));

/**
 * Destroy all edges for single vertex
 * Time: O(|Σ|)
 * @param local
 */
void destroy_edges(VE *local);

/**
 * Destroy all graph described from vertex
 * Time: O(|Σ|)*O(|Σ|-1) = O(|Σ|**2 - |Σ|)
 * @param g
 */
void destroy_graph(VE *g);

/**
 * Destroy graph and metadata
 * Time: O(|Σ|**2 - |Σ|)
 * @param loc
 */
void destroy_VEdet(VEdet *loc);

#endif //PRJPOLI18_GRAPH_H
