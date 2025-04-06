//
// Created by Arjun Sunil Kumar on 4/5/25.
//

#ifndef TRX0TRX_H
#define TRX0TRX_H

static inline void trx_start_if_not_started(trx_t *t, bool rw, ut::Location l) {
    t->start_line = l.line;
    t->start_file = l.filename;
    trx_start_if_not_started_low(t, rw);
}


#endif //TRX0TRX_H
