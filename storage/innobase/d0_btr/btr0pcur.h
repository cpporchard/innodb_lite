//
// Created by Arjun Sunil Kumar on 4/5/25.
//

#ifndef BTR0PCUR_H
#define BTR0PCUR_H
#include <cstddef>
#include <cstdlib>

#include "../f_page/page0cur.h"
#include "../d2_mtr_later/mtr0mtr.h"

typedef std::byte rec_t;

#define dict_index_t int
#define dberr_t int
#define ulint unsigned long

/** The tree cursor: the definition appears here only for the compiler to know struct size! */
struct btr_cur_t {
    dict_index_t *index{nullptr};
};

struct btr_pcur_t {
    void init(size_t read_level = 0);

    void open_at_side(bool from_left, dict_index_t *index, ulint latch_mode, bool init_pcur, ulint level, mtr_t *mtr);

    void close();

    btr_cur_t *get_btr_cur();

    page_cur_t *get_page_cur();

    page_t *get_page();

    const rec_t *get_rec() const;

    bool is_after_last_on_page() const;

    bool is_after_last_in_tree(mtr_t *mtr) const;

    void move_to_next_page(mtr_t *mtr);

    void move_to_next_on_page();

    bool move_to_next(mtr_t *mtr);
};

inline bool btr_pcur_t::is_after_last_on_page() const {
    return rand();
}

inline bool btr_pcur_t::is_after_last_in_tree(mtr_t *mtr) const {
    return rand();
}

inline void btr_pcur_t::move_to_next_on_page() {
    return;
}

inline bool btr_pcur_t::move_to_next(mtr_t *mtr) {
    if (is_after_last_on_page()) {
        if (is_after_last_in_tree(mtr)) {
            return (false);
        }

        move_to_next_page(mtr);
        return (true);
    }

    move_to_next_on_page();
    return (true);
}


#endif //BTR0PCUR_H
