//
// Created by Arjun Sunil Kumar on 4/5/25.
//

#ifndef PAGE0PAGE_H
#define PAGE0PAGE_H
#include <cstddef>
typedef std::byte rec_t;

static inline std::byte *page_get_infimum_rec(std::byte *page) {
    return page;
}

static inline bool page_rec_is_infimum(const rec_t *rec) /*!< in: record */
{
    // ut_ad(page_rec_check(rec));
    // return (page_rec_is_infimum_low(page_offset(rec)));
    return true;
}

static inline bool page_rec_is_supremum(const rec_t *rec) /*!< in: record */
{
    // ut_ad(page_rec_check(rec));
    // return (page_rec_is_supremum_low(page_offset(rec)));
    return true;
}

#endif //PAGE0PAGE_H
