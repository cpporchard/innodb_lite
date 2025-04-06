//
// Created by Arjun Sunil Kumar on 4/5/25.
//


#include "buf0buf.h"
#include "../b0_trx/trx0trx.h"

/** @name Modes for buf_page_get_gen */
/** @{ */
enum class Page_fetch {
  /** Get always */
  NORMAL,

  /** Same as NORMAL, but hint that the fetch is part of a large scan.
  Try not to flood the buffer pool with pages that may not be accessed again
  any time soon. */
  SCAN,

  /** get if in pool */
  IF_IN_POOL,

  /** get if in pool, do not make the block young in the LRU list */
  PEEK_IF_IN_POOL,

  /** get and bufferfix, but set no latch; we have separated this case, because
  it is error-prone programming not to set a latch, and it  should be used with
  care */
  NO_LATCH,

  /** Get the page only if it's in the buffer pool, if not then set a watch on
  the page. */
  IF_IN_POOL_OR_WATCH,

  /** Like Page_fetch::NORMAL, but do not mind if the file page has been
  freed. */
  POSSIBLY_FREED,

  /** Like Page_fetch::POSSIBLY_FREED, but do not initiate read ahead. */
  POSSIBLY_FREED_NO_READ_AHEAD,
};



struct Buf_fetch_normal : public Buf_fetch<Buf_fetch_normal> {
  /** Constructor.
  @param[in] page_id            Page ID of page to fetch.
  @param[in] page_size          Size of page on disk. */
  Buf_fetch_normal(const page_id_t &page_id, const page_size_t &page_size)
      : Buf_fetch(page_id, page_size) {}

  /** Fetch a block from the hash table or read from disk if necessary.
  @param[out] block             Block to fetch.
  @return DB_SUCCESS or error code. */
  dberr_t get(buf_block_t *&block) noexcept;
};

template <typename T>
buf_block_t *Buf_fetch<T>::single_page() {
  buf_block_t *block;

  for (;;) {
    if (static_cast<T *>(this)->get(block) == -1) {
      return nullptr;
    }

    // if (is_optimistic()) {
    //   auto mutex = buf_page_get_mutex(&block->page);
    //   mutex_enter(mutex);
    //   auto state = buf_page_get_io_fix(&block->page);
    //   mutex_exit(mutex);
    //
    //   if (state == BUF_IO_READ) {
    //     buf_block_unfix(block);
    //     return nullptr;
    //   }
    // }
    //
    // if (check_state(block) == DB_SUCCESS) {
    //   break;
    // }
  }

  // if (buf_page_is_accessed(&block->page) ==
  //     std::chrono::steady_clock::time_point{}) {
  //   buf_page_mutex_enter(block);
  //   buf_page_set_accessed(&block->page);
  //   buf_page_mutex_exit(block);
  //     }
  //
  // if (m_mode != Page_fetch::PEEK_IF_IN_POOL &&
  //     m_mode != Page_fetch::SCAN) {
  //   buf_page_make_young_if_needed(&block->page);
  //     }
  //
  // buf_wait_for_read(block);
  //
  // if (m_dirty_with_no_latch) {
  //   block->made_dirty_with_no_latch = true;
  // }
  //
  // mtr_add_page(block);
  //
  // if (m_mode != Page_fetch::PEEK_IF_IN_POOL &&
  //     m_mode != Page_fetch::POSSIBLY_FREED_NO_READ_AHEAD &&
  //     buf_page_is_accessed(&block->page) ==
  //         std::chrono::steady_clock::time_point{}) {
  //   buf_read_ahead_linear(m_page_id, m_page_size, ibuf_inside(m_mtr));
  //         }

  return block;
}


buf_block_t *buf_page_get_gen(const page_id_t &page_id,
                              const page_size_t &page_size, ulint rw_latch,
                              buf_block_t *guess, Page_fetch mode,
                              ut::Location location, mtr_t *mtr,
                              bool dirty_with_no_latch) {

  if (mode == Page_fetch::NORMAL ) {
    Buf_fetch_normal fetch(page_id, page_size);

    fetch.m_rw_latch = rw_latch;
    fetch.m_guess = guess;
    fetch.m_file = location.filename;
    fetch.m_line = location.line;
    fetch.m_mtr = mtr;
    fetch.m_dirty_with_no_latch = dirty_with_no_latch;

    return (fetch.single_page());

  }
  return nullptr;
}
