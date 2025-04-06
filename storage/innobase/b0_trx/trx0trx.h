#ifndef TRX0TRX_H
#define TRX0TRX_H
#define ulint unsigned long

struct trx_t {
    ulint start_line;       /*!< Track where it was started from */
    const char *start_file; /*!< Filename where it was started */
};

namespace ut {
    struct Location {
        const char *filename;
        size_t line;
    };
}

/** Starts the transaction if it is not yet started.
@param[in] trx Transaction
@param[in] read_write True if read write transaction */
void trx_start_if_not_started_low(trx_t *trx, bool read_write) {
}

static inline void trx_start_if_not_started(trx_t *t, bool rw, ut::Location l) {
    t->start_line = l.line;
    t->start_file = l.filename;
    trx_start_if_not_started_low(t, rw);
}



#endif //TRX0TRX_H
