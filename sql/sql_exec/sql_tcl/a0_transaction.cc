#include <sys/types.h>

#include "../../sql_io/b1_table.h"

int ha_commit_trans(THD *thd, bool all, bool ignore_global_read_lock = false);

bool trans_begin(THD *thd, uint flags = 0) {
    return true;
}

bool trans_commit(THD *thd, bool ignore_global_read_lock) {
    int res = ha_commit_trans(thd, true, ignore_global_read_lock);
}

bool trans_commit_implicit(THD *thd, bool ignore_global_read_lock = false){
    return true;
}

bool trans_rollback(THD *thd) {
    return true;
}
