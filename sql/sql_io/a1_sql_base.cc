/**
  Open all tables in list

  @param[in]     thd      Thread context.
  @param[in,out] start    List of tables to be open (it can be adjusted for
                          statement that uses tables only implicitly, e.g.
                          for "SELECT f1()").
  @param[out]    counter  Number of tables which were open.
  @param[in]     flags    Bitmap of flags to modify how the tables will be
                          open, see open_table() description for details.
  @param[in]     prelocking_strategy  Strategy which specifies how prelocking
                                      algorithm should work for this statement.

  @note
    Unless we are already in prelocked mode and prelocking strategy prescribes
    so this function will also precache all SP/SFs explicitly or implicitly
    (via views and triggers) used by the query and add tables needed for their
    execution to table list. Statement that uses SFs, invokes triggers or
    requires foreign key checks will be marked as requiring prelocking.
    Prelocked mode will be enabled for such query during lock_tables() call.

    If query for which we are opening tables is already marked as requiring
    prelocking it won't do such precaching and will simply reuse table list
    which is already built.

  @retval  false  Success.
  @retval  true   Error, reported.
*/

#include "a1_sql_base.h"

#include <sys/types.h>

#include "a2_table.h"

bool open_tables_for_query(THD *thd, Table_ref *tables, int flags){
    return true;
}

bool open_tables(THD *thd, Table_ref **start, uint *counter, uint flags,
                 Prelocking_strategy *prelocking_strategy) {
}


/**
  Open a base table.

  @param thd            Thread context.
  @param table_list     Open first table in list.
  @param ot_ctx         Context with flags which modify how open works
                        and which is used to recover from a failed
                        open_table() attempt.
                        Some examples of flags:
                        MYSQL_OPEN_IGNORE_FLUSH - Open table even if
                        someone has done a flush. No version number
                        checking is done.
                        MYSQL_OPEN_HAS_MDL_LOCK - instead of acquiring
                        metadata locks rely on that caller already has
                        appropriate ones.

  Uses a cache of open tables to find a TABLE instance not in use.

  If Table_ref::open_strategy is set to OPEN_IF_EXISTS, the table is
  opened only if it exists. If the open strategy is OPEN_STUB, the
  underlying table is never opened. In both cases, metadata locks are
  always taken according to the lock strategy.

  @retval true  Open failed. "action" parameter may contain type of action
                needed to remedy problem before retrying again.
  @retval false Success. Members of Table_ref structure are filled
  properly (e.g.  Table_ref::table is set for real tables and
                Table_ref::view is set for views).
*/

bool open_table(THD *thd, Table_ref *table_list, Open_table_context *ot_ctx) {

    // table->file->ha_extra(HA_EXTRA_RESET_STATE);
}