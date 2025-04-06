//
// Created by Arjun Sunil Kumar on 4/5/25.
//


#include "buf0buf.h"

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
    if (static_cast<T *>(this)->get(block) == DB_NOT_FOUND) {
      return nullptr;
    }

    if (is_optimistic()) {
      auto mutex = buf_page_get_mutex(&block->page);
      mutex_enter(mutex);
      auto state = buf_page_get_io_fix(&block->page);
      mutex_exit(mutex);

      if (state == BUF_IO_READ) {
        buf_block_unfix(block);
        return nullptr;
      }
    }

    if (check_state(block) == DB_SUCCESS) {
      break;
    }
  }

  if (buf_page_is_accessed(&block->page) ==
      std::chrono::steady_clock::time_point{}) {
    buf_page_mutex_enter(block);
    buf_page_set_accessed(&block->page);
    buf_page_mutex_exit(block);
      }

  if (m_mode != Page_fetch::PEEK_IF_IN_POOL &&
      m_mode != Page_fetch::SCAN) {
    buf_page_make_young_if_needed(&block->page);
      }

  buf_wait_for_read(block);

  if (m_dirty_with_no_latch) {
    block->made_dirty_with_no_latch = true;
  }

  mtr_add_page(block);

  if (m_mode != Page_fetch::PEEK_IF_IN_POOL &&
      m_mode != Page_fetch::POSSIBLY_FREED_NO_READ_AHEAD &&
      buf_page_is_accessed(&block->page) ==
          std::chrono::steady_clock::time_point{}) {
    buf_read_ahead_linear(m_page_id, m_page_size, ibuf_inside(m_mtr));
          }

  return block;
}


buf_block_t *buf_page_get_gen(const page_id_t &page_id,
                              const page_size_t &page_size, ulint rw_latch,
                              buf_block_t *guess, Page_fetch mode,
                              ut::Location location, mtr_t *mtr,
                              bool dirty_with_no_latch) {
#ifdef UNIV_DEBUG
  ut_ad(mtr->is_active());

  ut_ad(rw_latch == RW_S_LATCH || rw_latch == RW_X_LATCH ||
        rw_latch == RW_SX_LATCH || rw_latch == RW_NO_LATCH);

  ut_ad(!ibuf_inside(mtr) ||
        ibuf_page_low(page_id, page_size, false, location, nullptr));

  switch (mode) {
    case Page_fetch::NO_LATCH:
      ut_ad(rw_latch == RW_NO_LATCH);
      break;
    case Page_fetch::NORMAL:
    case Page_fetch::SCAN:
    case Page_fetch::IF_IN_POOL:
    case Page_fetch::PEEK_IF_IN_POOL:
    case Page_fetch::IF_IN_POOL_OR_WATCH:
    case Page_fetch::POSSIBLY_FREED:
    case Page_fetch::POSSIBLY_FREED_NO_READ_AHEAD:
      break;
    default:
      ib::fatal(UT_LOCATION_HERE, ER_IB_ERR_UNKNOWN_PAGE_FETCH_MODE)
          << "Unknown fetch mode: " << (int)mode;
      ut_error;
  }

  bool found;
  const page_size_t &space_page_size =
      fil_space_get_page_size(page_id.space(), &found);

  ut_ad(!found || page_size.equals_to(space_page_size));
#endif /* UNIV_DEBUG */

  if (mode == Page_fetch::NORMAL && !fsp_is_system_temporary(page_id.space())) {
    Buf_fetch_normal fetch(page_id, page_size);

    fetch.m_rw_latch = rw_latch;
    fetch.m_guess = guess;
    fetch.m_mode = mode;
    fetch.m_file = location.filename;
    fetch.m_line = location.line;
    fetch.m_mtr = mtr;
    fetch.m_dirty_with_no_latch = dirty_with_no_latch;

    return (fetch.single_page());

  }
}
