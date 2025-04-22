#include "handler.h"


#define MYSQL_TABLE_IO_WAIT(OP, INDEX, RESULT, PAYLOAD) PAYLOAD


int handler::ha_rnd_init(bool scan) {
    return rnd_init(scan);
}

int handler::ha_rnd_next(uchar *buf) {
    int result;
    result = rnd_next(buf);

    // // Set status for the need to update generated fields
    // m_update_generated_read_fields = table->has_gcol();
    //
    // MYSQL_TABLE_IO_WAIT(PSI_TABLE_FETCH_ROW, MAX_KEY, result, { result = rnd_next(buf); })
    // if (!result && m_update_generated_read_fields) {
    //     result = update_generated_read_fields(buf, table);
    //     m_update_generated_read_fields = false;
    // }

    return result;
}

int handler::ha_extra(enum ha_extra_function operation) {
    return extra(operation);
}

int ha_commit_low(THD *thd, bool all, bool run_after_commit) {
}
int ha_rollback_low(THD *thd, bool all) {}