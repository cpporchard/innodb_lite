#include "buf0buf.h"

//
// Created by Arjun Sunil Kumar on 4/6/25.
//
ulint buf_read_page_low(dberr_t *err, bool sync, ulint type, ulint mode,
                        const page_id_t &page_id, const page_size_t &page_size,
                        bool unzip) {

    // bpage = buf_page_init_for_read(mode, page_id, page_size, unzip);
    //
    // *err = fil_io(request, sync, page_id, page_size, 0, page_size.physical(), dst, bpage);

}