//
// Created by Arjun Sunil Kumar on 4/5/25.
//

#ifndef PAGE0PAGE_H
#define PAGE0PAGE_H

static inline byte *page_get_infimum_rec(byte *page) {
    return page + page_get_infimum_offset(page);
}

#endif //PAGE0PAGE_H
