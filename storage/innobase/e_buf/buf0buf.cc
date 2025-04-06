//
// Created by Arjun Sunil Kumar on 4/5/25.
//


#include "buf0buf.h"
#include "../b0_trx/trx0trx.h"

template <typename Mutex>
void mutex_enter_inline(Mutex *m, ut::Location loc) {}
#define mutex_enter(M) mutex_enter_inline(M, UT_LOCATION_HERE)
#define mutex_exit(M) (M)

/** Moves a page to the start of the buffer pool LRU list if it is too old.
This high-level function can be used to prevent an important page from
slipping out of the buffer pool. The page must be fixed to the buffer pool.
@param[in,out]  bpage   buffer block of a file page */
static void buf_page_make_young_if_needed(buf_page_t *bpage) {
    // if (buf_page_peek_if_too_old(bpage)) {
    //     buf_page_make_young(bpage);
    // }
}

/** Wait for the block to be read in.
@param[in]      block   The block to check */
static void buf_wait_for_read(buf_block_t *block) {
    /* Note:
    This unlocked read of IO fix is safe as we have the block buf-fixed. The page
    can only transition away from the IO_READ state, and once this is done, it
    will not be IO_READ again as long as we have it buf-fixed.

    The repeated reads of io_fix will not be optimized out because it's an atomic
    variable.*/
    // while (block->page.was_io_fix_read()) {
    //     /* Page is X-latched on block->lock until the read is completed.
    //     Let's just wait for S-lock on block->lock, it will be granted as soon as the
    //     read completes. */
    //     rw_lock_s_lock(&block->lock, UT_LOCATION_HERE);
    //     rw_lock_s_unlock(&block->lock);
    // }
}

template <typename T>
bool Buf_fetch<T>::is_optimistic() const {
    return (m_mode == Page_fetch::IF_IN_POOL ||
            m_mode == Page_fetch::PEEK_IF_IN_POOL);
}

dberr_t Buf_fetch_normal::get(buf_block_t *&block) {
    for (;;) {
        // ut_ad(!rw_lock_own(buf_page_hash_lock_get(m_buf_pool, m_page_id), RW_LOCK_S));
        block = new buf_block_t{};
        break;
    }
    return 1;
}

template <typename T>
void Buf_fetch<T>::mtr_add_page(buf_block_t *block) {
    mtr_memo_type_t fix_type;
    mtr_memo_push(m_mtr, block, fix_type);
}

template<typename T>
buf_block_t *Buf_fetch<T>::single_page() {
    buf_block_t *block;

    for (;;) {
        if (static_cast<T *>(this)->get(block) == -1) {
            return nullptr;
        }
        if (is_optimistic()) {
            const auto bpage = &block->page;
            auto block_mutex = buf_page_get_mutex(bpage);

            mutex_enter(block_mutex);
            const auto state = buf_page_get_io_fix(bpage);
            mutex_exit(block_mutex);

            if (state == BUF_IO_READ) {
                buf_block_unfix(block);
                return (nullptr);
            }
        }
        break;
    }

    const auto access_time = buf_page_is_accessed(&block->page);

    if (access_time == std::chrono::steady_clock::time_point{}) {
        // buf_page_mutex_enter(block);
        // buf_page_set_accessed(&block->page);
        // buf_page_mutex_exit(block);
    }

    if (m_mode != Page_fetch::PEEK_IF_IN_POOL && m_mode != Page_fetch::SCAN) {
        buf_page_make_young_if_needed(&block->page);
    }

    /* We have to wait here because the IO_READ state was set under the protection
    of the hash_lock and not the block->mutex and block->lock. */
    buf_wait_for_read(block);

    mtr_add_page(block);

    return block;
}



/**
    The first parameter page_id specifies the required page number, and this page_id is usually obtained through the upper B Tree retrieval.
    The third parameter rw_latch specifies the read-write Latch mode to be added to the page.
    The second last parameter MTR is the Mini-Transaction mentioned above.
    When the same MTR accesses multiple pages, this MTR structure is passed on each call to buf_page_get_gen.
 */
buf_block_t *buf_page_get_gen(const page_id_t &page_id,
                              const page_size_t &page_size,
                              ulint rw_latch,
                              buf_block_t *guess, Page_fetch mode, ut::Location location,
                              mtr_t *mtr,
                              bool dirty_with_no_latch) {
    Buf_fetch_normal fetch(page_id, page_size);

    fetch.m_rw_latch = rw_latch;
    fetch.m_guess = guess;
    fetch.m_file = location.filename;
    fetch.m_line = location.line;
    fetch.m_mtr = mtr;
    fetch.m_dirty_with_no_latch = dirty_with_no_latch;

    return fetch.single_page();
}
