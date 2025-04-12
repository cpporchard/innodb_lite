#ifndef TRX0TRX_H
#define TRX0TRX_H
#include <cstddef>
#include <cstdint>

#define ulint unsigned long

struct trx_t {
    ulint start_line;       /*!< Track where it was started from */
    const char *start_file; /*!< Filename where it was started */
};

/** The generic InnoDB system object identifier data type */
typedef uint64_t ib_id_t;

/** Rollback pointer (DB_ROLL_PTR, DATA_ROLL_PTR) */
typedef ib_id_t roll_ptr_t;

namespace ut {
    struct Location {
        const char *filename;
        size_t line;
    };
}

void trx_start_if_not_started_low(trx_t *trx, bool read_write);

static inline void trx_start_if_not_started(trx_t *t, bool rw, ut::Location l) {
    t->start_line = l.line;
    t->start_file = l.filename;
    trx_start_if_not_started_low(t, rw);
}

class TrxInInnoDB {
public:
    static void begin_stmt(trx_t *trx) { enter(trx, false); }
    static void end_stmt(trx_t *trx) { exit(trx); }

private:
    static void enter(trx_t *trx, bool disable) {}
    static void exit(trx_t *trx) {}
};


#endif //TRX0TRX_H
