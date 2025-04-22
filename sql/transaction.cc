
#include "table.h"
#include "handler.h"

int ha_commit_trans(THD *thd, bool all, bool ignore_global_read_lock = false);

bool trans_commit(THD *thd, bool ignore_global_read_lock) {
   int res = ha_commit_trans(thd, true, ignore_global_read_lock);
}