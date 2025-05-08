// #include "../z_sql_dml.h"
// class THD;
//
//
// bool Sql_cmd_dml::execute_inner(THD *thd) {
     // Query_expression *unit = lex->unit;
//
//     if (unit->optimize(thd, /*materialize_destination=*/nullptr,/*finalize_access_paths=*/true)) return true;
//
//
//     // Create iterators for the chosen query plan before execution.
//     if (unit->create_iterators(thd)) return true;
//
//     if (unit->execute(thd)) return true;
//
//     notify_plugins_after_select(thd, lex->m_sql_cmd);
// }
//
//
// bool Sql_cmd_dml::execute(THD *thd) {
//     prepare(thd);
//
//     if (open_tables_for_query(thd, lex->query_tables, 0)) goto err;
//
//     // Use the hypergraph optimizer for the SELECT statement, if enabled.
//     thd->optimizer_switch_flag(OPTIMIZER_SWITCH_HYPERGRAPH_OPTIMIZER);
//
//     // Bind table and field information
//     if (restore_cmd_properties(thd)) goto err;
//
//     if (!is_empty_query()) {
//         if (lock_tables(thd, lex->query_tables, lex->table_count, 0)) goto err;
//     }
//
//     // Perform statement-specific execution
//     if (execute_inner(thd)) goto err;
//
// err:
//     return true;
// }
