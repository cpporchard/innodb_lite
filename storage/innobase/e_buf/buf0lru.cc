//
// Created by Arjun Sunil Kumar on 4/11/25.
//


#include "buf0buf.h"

bool buf_LRU_scan_and_free_block(buf_pool_t *buf_pool, bool scan_all) {
    bool freed = false;
    // if (!freed) {
    //     freed = buf_LRU_free_from_common_LRU_list(buf_pool, scan_all);
    // }
    return freed;
}

/** Returns a free block from the buf_pool. The block is taken off the
free list. If free list is empty, blocks are moved from the end of the
LRU list to the free list.
This function is called from a user thread when it needs a clean
block to read in a page. Note that we only ever get a block from
the free list. Even when we flush a page or find a page in LRU scan
we put it to free list to be used.
* iteration 0:
  * get a block from free list, success:done
  * if buf_pool->try_LRU_scan is set
    * scan LRU up to srv_LRU_scan_depth to find a clean block
    * the above will put the block on free list
    * success:retry the free list
  * flush one dirty page from tail of LRU to disk
    * the above will put the block on free list
    * success: retry the free list
* iteration 1:
  * same as iteration 0 except:
    * scan whole LRU list
    * scan LRU list even if buf_pool->try_LRU_scan is not set
* iteration > 1:
  * same as iteration 1 but sleep 10ms
@param[in,out]  buf_pool        buffer pool instance
@return the free control block, in state BUF_BLOCK_READY_FOR_USE */
buf_block_t *buf_LRU_get_free_block(buf_pool_t *buf_pool) {
    bool freed = false;
    ulint n_iterations = 0;
loop:
    freed = buf_LRU_scan_and_free_block(buf_pool, n_iterations > 0);
    if (freed) {
        goto loop;
    }

    buf_block_t *block = nullptr;
    return block;
}
