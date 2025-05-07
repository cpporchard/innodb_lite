
#include "b0_sql_lex.h"
#include "../sql_io/table.h"
#include "sql_dcl_later/auth/auth_common.h"
#include "sql_ddl/sql_db.h"

#define DEBUG_SYNC(_thd_, _sync_point_name_)                 \
do {                                                         \
} while (0)

class Table_ref;
class THD;

struct COM_INIT_DB_DATA {
    const char *db_name;
    unsigned long length;
};

union COM_DATA {
    COM_INIT_DB_DATA com_init_db;
};

enum enum_server_command {
    /**
      Currently refused by the server. See ::dispatch_command.
      Also used internally to mark the start of a session.
    */
    COM_SLEEP,
};

bool dispatch_command(THD *thd, const COM_DATA *com_data, enum enum_server_command command);

void dispatch_sql_command(THD *thd, Parser_state *parser_state, bool is_retry);

int mysql_execute_command(THD *thd, bool first_level);

bool do_command(THD *thd) {
    COM_DATA com_data;
    enum enum_server_command command = COM_SLEEP;
    return dispatch_command(thd, &com_data, command);
}

bool dispatch_command(THD *thd, const COM_DATA *com_data, enum enum_server_command command) {
    Parser_state parser_state;
    dispatch_sql_command(thd, &parser_state, /*is_retry=*/true);
}

void dispatch_sql_command(THD *thd, Parser_state *parser_state, bool is_retry) {
    mysql_execute_command(thd, true);
}

int mysql_execute_command(THD *thd, bool first_level) {
    int res = false;
    LEX *const lex = thd->lex;
    // Query_block *const query_block = lex->query_block;
    // Table_ref *const first_table = query_block->get_table_list();

    DEBUG_SYNC(thd, "execute_command_before_main_switch");

    switch (lex->sql_command) {

        // DCL
        case SQLCOM_CREATE_USER: {
            if (!(res = mysql_create_user(thd, lex->users_list,true, false))) {
            }
            break;
        }
        case SQLCOM_REVOKE:
        case SQLCOM_GRANT: {
            // Later
        }


        case SQLCOM_CREATE_DB: {
            HA_CREATE_INFO create_info;
            res = mysql_create_db(thd,  lex->name.str, &create_info);
            break;
        }

        // case SQLCOM_INSERT:
        // case SQLCOM_DELETE:
        // case SQLCOM_UPDATE:
        // case SQLCOM_CREATE_TABLE:
        // case SQLCOM_CREATE_INDEX:
        // case SQLCOM_DROP_INDEX: {
        //     assert(first_table == all_tables && first_table != nullptr);
        //     assert(lex->m_sql_cmd != nullptr);
        //     res = lex->m_sql_cmd->execute(thd);
        //     break;
        // }
        //
        // case SQLCOM_PREPARE: {
        //     mysql_sql_stmt_prepare(thd);
        //     break;
        // }
        // case SQLCOM_EXECUTE: {
        //     mysql_sql_stmt_execute(thd);
        //     break;
        // }
        // case SQLCOM_DEALLOCATE_PREPARE: {
        //     mysql_sql_stmt_close(thd);
        //     break;
        // }
        // case SQLCOM_UNLOCK_TABLES: {
        //     if (thd->variables.option_bits & OPTION_TABLE_LOCK) {
        //         /*
        //           Can we commit safely? If not, return to avoid releasing
        //           transactional metadata locks.
        //         */
        //         if (trans_check_state(thd)) return -1;
        //         res = trans_commit_implicit(thd);
        //         thd->locked_tables_list.unlock_locked_tables(thd);
        //         thd->mdl_context.release_transactional_locks();
        //         thd->variables.option_bits &= ~(OPTION_TABLE_LOCK);
        //     }
        //     if (thd->global_read_lock.is_acquired())
        //         thd->global_read_lock.unlock_global_read_lock(thd);
        //     if (res) goto error;
        //     my_ok(thd);
        //     break;
        // case SQLCOM_LOCK_TABLES:
        //     /*
        //       Can we commit safely? If not, return to avoid releasing
        //       transactional metadata locks.
        //     */
        //     if (trans_check_state(thd)) return -1;
        //     /* We must end the transaction first, regardless of anything */
        //     res = trans_commit_implicit(thd);
        //     thd->locked_tables_list.unlock_locked_tables(thd);
        //     /* Release transactional metadata locks. */
        //     thd->mdl_context.release_transactional_locks();
        //     if (res) goto error;
        //
        //     if (open_temporary_tables(thd, all_tables)) goto error;
        //
        //     if (lock_tables_precheck(thd, all_tables)) goto error;
        //
        //     thd->variables.option_bits |= OPTION_TABLE_LOCK;
        //
        //     res = lock_tables_open_and_lock_tables(thd, all_tables);
        //
        //     if (res) {
        //         thd->variables.option_bits &= ~(OPTION_TABLE_LOCK);
        //     } else {
        //         my_ok(thd);
        //     }
        //     break;
        // }
        //
        // case SQLCOM_BEGIN:
        //     if (trans_begin(thd, lex->start_transaction_opt)) goto error;
        //     break;
        // case SQLCOM_COMMIT: {
        //     assert(thd->lock == nullptr ||
        //         thd->locked_tables_mode == LTM_LOCK_TABLES);
        //     const bool tx_chain =
        //     (lex->tx_chain == TVL_YES ||
        //      (thd->variables.completion_type == 1 && lex->tx_chain != TVL_NO));
        //     const bool tx_release =
        //     (lex->tx_release == TVL_YES ||
        //      (thd->variables.completion_type == 2 && lex->tx_release != TVL_NO));
        //     if (trans_commit(thd)) goto error;
        //     thd->mdl_context.release_transactional_locks();
        //     /* Begin transaction with the same isolation level. */
        //     if (tx_chain) {
        //         if (trans_begin(thd)) goto error;
        //     } else {
        //         /* Reset the isolation level and access mode if no chaining
        //          * transaction.*/
        //         trans_reset_one_shot_chistics(thd);
        //     }
        //     /* Disconnect the current client connection. */
        //     if (tx_release) thd->killed = THD::KILL_CONNECTION;
        //     my_ok(thd);
        //     break;
        // }
        // case SQLCOM_ROLLBACK: {
        //     assert(thd->lock == nullptr ||
        //         thd->locked_tables_mode == LTM_LOCK_TABLES);
        //     const bool tx_chain =
        //     (lex->tx_chain == TVL_YES ||
        //      (thd->variables.completion_type == 1 && lex->tx_chain != TVL_NO));
        //     const bool tx_release =
        //     (lex->tx_release == TVL_YES ||
        //      (thd->variables.completion_type == 2 && lex->tx_release != TVL_NO));
        //     if (trans_rollback(thd)) goto error;
        //     thd->mdl_context.release_transactional_locks();
        //     /* Begin transaction with the same isolation level. */
        //     if (tx_chain) {
        //         if (trans_begin(thd)) goto error;
        //     } else {
        //         /* Reset the isolation level and access mode if no chaining
        //          * transaction.*/
        //         trans_reset_one_shot_chistics(thd);
        //     }
        //     /* Disconnect the current client connection. */
        //     if (tx_release) thd->killed = THD::KILL_CONNECTION;
        //     my_ok(thd);
        //     break;
        //
        // default:
        //     assert(0); /* Impossible */
        //     my_ok(thd);
        //     break;
        // }
        //     goto finish;
    }
}
