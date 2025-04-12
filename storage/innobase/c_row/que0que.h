//
// Created by Arjun Sunil Kumar on 4/11/25.
//

#ifndef QUE0QUE_H
#define QUE0QUE_H


/* Query graph query thread node: the fields are protected by the
trx_t::mutex with the exceptions named below */

struct que_thr_t {
    // que_common_t common;   /*!< type: QUE_NODE_THR */
    // ulint magic_n;         /*!< magic number to catch memory
    //                        corruption */
    // que_node_t *child;     /*!< graph child node */
    // que_t *graph;          /*!< graph where this node belongs */
    // que_thr_state_t state; /*!< state of the query thread */
};

#endif //QUE0QUE_H
