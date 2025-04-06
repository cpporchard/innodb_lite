#include "mtr0mtr.h"


/** Release latches and decrement the buffer fix count.
@param[in]      slot    memo slot */
static void memo_slot_release(mtr_memo_slot_t *slot) {
    switch (slot->type) {
        // case MTR_MEMO_S_LOCK:
        //     rw_lock_s_unlock(reinterpret_cast<rw_lock_t *>(slot->object));
        //
        // case MTR_MEMO_SX_LOCK:
        //     rw_lock_sx_unlock(reinterpret_cast<rw_lock_t *>(slot->object));
        // break;
        //
        // case MTR_MEMO_X_LOCK:
        //     rw_lock_x_unlock(reinterpret_cast<rw_lock_t *>(slot->object));
        // break;

    }
}

/**
Pushes an object to an mtr memo stack. */
void mtr_t::memo_push(void *object, mtr_memo_type_t type) {

    // mtr_memo_slot_t *slot;
    // slot = m_impl.m_memo.push<mtr_memo_slot_t *>(sizeof(*slot));
    //
    // slot->type = type;
    // slot->object = object;
}