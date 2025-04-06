//
// Created by Arjun Sunil Kumar on 4/5/25.
//


#include "buf0buf.h"
#include "../b0_trx/trx0trx.h"

dberr_t Buf_fetch_normal::get(buf_block_t *&block) {
  return 1;
}

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
