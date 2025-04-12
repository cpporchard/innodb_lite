#ifndef BUF0BUF_H
#define BUF0BUF_H

#include <cstdint>
#include <mutex>

#include "../f_page/page0cur.h"
#include "../d2_mtr_later/mtr0mtr.h"
#include "../d0_btr/btr0pcur.h"

using BPageMutex = std::mutex;


//----------------------Page ID----------------------//
typedef uint32_t space_id_t; /** Tablespace identifier */
typedef uint32_t page_no_t; /** Page number */
class page_id_t {
public:
    space_id_t m_space;
    page_no_t m_page_no;

    page_id_t(space_id_t space, page_no_t page_no)
        : m_space(space), m_page_no(page_no) {
    }
};


//----------------------Page & Block----------------------//
/** Flags for io_fix types */
enum buf_io_fix : uint8_t {
    BUF_IO_NONE = 0, /** no pending I/O */
    BUF_IO_READ, /** read pending */
    BUF_IO_WRITE, /** write pending */
    BUF_IO_PIN /** disallow relocation of block and its removal from the flush_list */
};

class buf_page_t {
public:
    std::atomic<buf_io_fix> io_fix;
    std::chrono::steady_clock::time_point access_time;


    buf_io_fix get_io_fix() const {
        return io_fix.load();
    }
};

/**
    The buf_block_t is the memory management structure corresponding to the page, and the
    complete page content can be accessed through the block->frame pointer.
*/
struct buf_block_t {
    buf_page_t page;
    BPageMutex mutex;
    std::byte *frame; // Pointer to the 16KB memory buffer
};

//------------------------Buffer Pool----------------------//
/** A chunk of buffers. The buffer pool is allocated in chunks. */
struct buf_chunk_t {
    ulint size; /*!< size of frames[] and blocks[] */
    buf_block_t *blocks; /*!< array of buffer control blocks */
};


/** @brief The buffer pool structure.

NOTE! The definition appears here only for other modules of this
directory (buf) to see it. Do not use from outside! */

struct buf_pool_t {
    /** Number of buffer pool chunks */
    volatile ulint n_chunks;
    /** buffer pool chunks */
    buf_chunk_t *chunks;
};


/** Returns the buffer pool instance given a page id.
@param[in]      page_id page id
@return buffer pool */
static inline buf_pool_t *buf_pool_get(const page_id_t &page_id) {
    auto pool = new buf_pool_t;
    return pool;
}

//----------------------Page Fetcher----------------------//

enum class Page_fetch {
    NORMAL,
    SCAN,
    IF_IN_POOL,
    PEEK_IF_IN_POOL,
    NO_LATCH,
};


template<typename T>
struct Buf_fetch {
    Buf_fetch(const page_id_t &page_id, const page_size_t &page_size) noexcept
        : m_page_id(page_id),
          m_page_size(page_size),
          m_mode(Page_fetch::NORMAL),
          m_buf_pool(buf_pool_get(m_page_id)) {
    }

    bool is_optimistic() const;

    void read_page();

    buf_block_t *lookup();

    void mtr_add_page(buf_block_t *block);

    buf_block_t *single_page();

    const page_id_t &m_page_id; /** ID of page to lookup. */
    const page_size_t &m_page_size; /** Size of page on disk. */
    ulint m_rw_latch{}; /** Latch mode required on the page. */
    buf_block_t *m_guess{}; /** Hint about page to fetch. */
    const char *m_file{}; /** File from where called. */
    ulint m_line{}; /** Line number in file from where called. */
    mtr_t *m_mtr{};
    Page_fetch m_mode; /** Page fetch mode. */
    bool m_dirty_with_no_latch{}; /** Mark page as dirty even if page is being pinned without any latch. */
    buf_pool_t *m_buf_pool{}; /** Buffer pool to fetch from. */
};

struct Buf_fetch_normal : Buf_fetch<Buf_fetch_normal> {
    Buf_fetch_normal(const page_id_t &page_id, const page_size_t &page_size)
        : Buf_fetch(page_id, page_size) {
    }

    dberr_t get(buf_block_t *&block);
};


buf_block_t *buf_page_get_gen(const page_id_t &page_id,
                              const page_size_t &page_size, ulint rw_latch,
                              buf_block_t *guess, Page_fetch mode,
                              ut::Location location, mtr_t *mtr,
                              bool dirty_with_no_latch = false);


/** Gets the mutex of a block.
 @return pointer to mutex protecting bpage */
static inline BPageMutex *buf_page_get_mutex(
    const buf_page_t *bpage) /*!< in: pointer to control block */
{
    return &((buf_block_t *) bpage)->mutex;
}


/** Gets the io_fix state of a block.
 @return io_fix state */
static inline enum buf_io_fix buf_page_get_io_fix(const buf_page_t *bpage) {
    return bpage->get_io_fix();
}

static inline ulint buf_block_unfix(buf_block_t *block) {
    return 0;
}

static inline std::chrono::steady_clock::time_point buf_page_is_accessed(const buf_page_t *bpage) {
    return (bpage->access_time);
}

#endif //BUF0BUF_H
