#ifndef MTR0MTR_H
#define MTR0MTR_H

#define ulint unsigned long


/** Push an object to an mtr memo stack. */
#define mtr_memo_push(m, o, t) (m)->memo_push(o, t)

/** Types for the mlock objects to store in the mtr memo; NOTE that the
first 3 values must be RW_S_LATCH, RW_X_LATCH, RW_NO_LATCH */
enum mtr_memo_type_t {
    MTR_MEMO_S_LOCK = 64,
    MTR_MEMO_X_LOCK = 128,
    MTR_MEMO_SX_LOCK = 256
};

/** Mini-transaction handle and buffer */
struct mtr_t {

public:
    /** Push an object to an mtr memo stack.
    @param object object
    @param type   object type: MTR_MEMO_S_LOCK, ... */
    void memo_push(void *object, mtr_memo_type_t type);

};

/** Mini-transaction memo stack slot. */
struct mtr_memo_slot_t {
    /** type of the stored object (MTR_MEMO_S_LOCK, ...) */
    ulint type;
};

#endif //MTR0MTR_H
