#include "../z_sql_dml.h"
#include "../../../sql_io/a1_sql_base.h"
#include "../../a1_sql_lex.h"
#include "../../b0_sql_class.h"

class THD;


bool Sql_cmd_dml::execute_inner(THD *thd) {
     Query_expression *unit = lex->unit;

    if (unit->optimize(thd, /*materialize_destination=*/nullptr,/*finalize_access_paths=*/true)) return true;


    // Create iterators for the chosen query plan before execution.
    if (unit->create_iterators(thd)) return true;

    if (unit->execute(thd)) return true;

    // notify_plugins_after_select(thd, lex->m_sql_cmd);
}

bool Sql_cmd_dml::prepare(THD *thd) {
    LEX *lex = thd->lex;
    if (open_tables_for_query( thd, lex->query_tables,1)) {
        return true;
    }
    // if (sql_command_code() == SQLCOM_SELECT) DEBUG_SYNC(thd, "after_table_open");

}

bool Sql_cmd_dml::execute(THD *thd) {

    prepare(thd);

    if (open_tables_for_query(thd, lex->query_tables, 0)) goto err;

    // Use the hypergraph optimizer for the SELECT statement, if enabled.
    // thd->optimizer_switch_flag(true);

    // Bind table and field information
    // if (restore_cmd_properties(thd)) goto err;

    // if (!is_empty_query()) {
    //     if (lock_tables(thd, lex->query_tables, lex->table_count, 0)) goto err;
    // }

    // Perform statement-specific execution
    if (execute_inner(thd)) goto err;

err:
    return true;
}
