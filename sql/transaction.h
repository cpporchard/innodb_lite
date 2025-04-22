#pragma once
#include <sys/types.h>


class THD;

bool trans_begin(THD *thd, uint flags = 0);
bool trans_commit(THD *thd, bool ignore_global_read_lock = false);
bool trans_commit_implicit(THD *thd, bool ignore_global_read_lock = false);
bool trans_rollback(THD *thd);
bool trans_rollback_implicit(THD *thd);

bool trans_commit_stmt(THD *thd, bool ignore_global_read_lock = false);
bool trans_rollback_stmt(THD *thd);