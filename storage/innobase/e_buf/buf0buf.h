#include <cstdint>
#include "../f_page/page0cur.h"
#include "../d2_mtr_later/mtr0mtr.h"
#include "../d0_btr/btr0pcur.h"


#ifndef BUF0BUF_H
#define BUF0BUF_H

/** Page number */
typedef uint32_t page_no_t;
/** Tablespace identifier */
typedef uint32_t space_id_t;

class buf_page_t {
};

class page_id_t {

public:
    space_id_t m_space;
    page_no_t m_page_no;

    page_id_t(space_id_t space, page_no_t page_no)
        : m_space(space), m_page_no(page_no) {}
};

//In many scenarios, a block is a page.
struct buf_block_t {
    buf_page_t page;
};


/** This class implements the rules for fetching the pages from the buffer
pool depending on the context. It will set the page latches as requested,
detect and handle stale reads and initiate read requests if required. */
template <typename T>
struct Buf_fetch {
 public:
  /** Constructor.
  @param[in] page_id            ID of page to fetch.
  @param[in] page_size          Size of page on disk. */
  Buf_fetch(const page_id_t &page_id, const page_size_t &page_size) noexcept
      : m_page_id(page_id),
        m_page_size(page_size){}

  /** For fetching a single page.
  @return block from pool on success or nullptr on failure. */
  buf_block_t *single_page();

 private:
  /**  Lookup page in the hash table.
  @return block if found or nullptr if not found. */
  buf_block_t *lookup();

  /** Get page if it's in the buffer pool or set a watch on it.
  @return block that is being watched or nullptr. */
  buf_block_t *is_on_watch();

  /** Initiate a read request from persistent store. */
  void read_page();

  dberr_t zip_page_handler(buf_block_t *&fix_block);

  /** Check block state.
  @return DB_SUCCESS or error code. */
  dberr_t check_state(buf_block_t *&block);

  /** Temporary table pages have different latching rules because they are
  not redo logged.
  @param[in,out] block          Temporary tablespace to fetch. */
  void temp_space_page_handler(buf_block_t *block);

  /** Add the page to the mini-transaction along with latching context.
  @param[in,out] block          Block for which to add the latching context. */
  void mtr_add_page(buf_block_t *block);

  /** Check if fetch mode is an optimistic fetch.
  @return true if it's an optimistic fetch. */
  bool is_optimistic() const;

  /** Check if the fetch mode is OK with freed pages.
  @return true if freed pages are OK. */
  [[nodiscard]] bool is_possibly_freed() const noexcept;

#if defined UNIV_DEBUG || defined UNIV_IBUF_DEBUG
  dberr_t debug_check(buf_block_t *fix_block);
#endif /* UNIV_DEBUG || UNIV_IBUF_DEBUG */

 public:
  /** ID of page to lookup. */
  const page_id_t &m_page_id;
  /** Size of page on disk. */
  const page_size_t &m_page_size;
  /** true if page belongs to a temporary tablespace. */
  const bool m_is_temp_space{};
  /** Latch mode required on the page. */
  ulint m_rw_latch;
  /** Hint about page to fetch. */
  buf_block_t *m_guess{};

  /** File from where called. */
  const char *m_file{};
  /** Line number in file from where called. */
  ulint m_line{};
  /** Mini-transaction covering the fetch. */
  mtr_t *m_mtr{};
  /** Mark page as dirty even if page is being pinned without any latch. */
  bool m_dirty_with_no_latch{};
  /** Number of retries before giving up. */
  size_t m_retries{};
  /** Buffer pool to fetch from. */
  // buf_pool_t *m_buf_pool{};
  // /** Hash table lock. */
  // rw_lock_t *m_hash_lock{};

  friend T;
};


#endif //BUF0BUF_H
