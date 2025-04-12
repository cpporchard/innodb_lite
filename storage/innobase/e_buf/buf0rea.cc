#include "buf0buf.h"


/** read only pages belonging to the insert buffer tree */
constexpr uint32_t BUF_READ_IBUF_PAGES_ONLY = 131;
/** read any page */
constexpr uint32_t BUF_READ_ANY_PAGE = 132;

buf_page_t *buf_page_init_for_read(ulint mode, const page_id_t &page_id, const page_size_t &page_size, bool unzip);

//
// Created by Arjun Sunil Kumar on 4/6/25.
//
ulint buf_read_page_low(dberr_t *err, bool sync, ulint type, ulint mode,
                        const page_id_t &page_id, const page_size_t &page_size,
                        bool unzip) {
    buf_page_t *bpage;
    bpage = buf_page_init_for_read(mode, page_id, page_size, unzip);

    // *err = fil_io(request, sync, page_id, page_size, 0, page_size.physical(), dst, bpage);

    return 0;
}

bool buf_read_page(const page_id_t &page_id, const page_size_t &page_size) {
    ulint count;
    dberr_t err;

    count = buf_read_page_low(&err, true, 0, BUF_READ_ANY_PAGE, page_id,
                              page_size, false);
    return true;
}
