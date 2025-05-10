#include "a1_sql_lex.h"
#include "../sql_io/a2_table.h"
#include "sql_dcl_later/auth/auth_common.h"
#include "sql_ddl/sql_db.h"
#include "sql_tcl/a0_transaction.h"
#include <cassert>
#include "../sql_exec/b0_sql_class.h"

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
bool parse_sql(THD *thd, Parser_state *parser_state);

void dispatch_sql_command(THD *thd, Parser_state *parser_state, bool is_retry);

int mysql_execute_command(THD *thd, bool first_level);

bool do_command(THD *thd) {
    COM_DATA com_data;
    enum enum_server_command command = COM_SLEEP;
    return dispatch_command(thd, &com_data, command);
}

bool dispatch_command(THD *thd, const COM_DATA *com_data, enum enum_server_command command) {
    Parser_state parser_state;
    parse_sql(thd, &parser_state);
    dispatch_sql_command(thd, &parser_state, /*is_retry=*/true);
    return true;
}

bool parse_sql(THD *thd, Parser_state *parser_state) {
    const bool mysql_parse_status = thd->sql_parser();
    return mysql_parse_status;
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
            if (!(res = mysql_create_user(thd, lex->users_list, true, false))) {
            }
            break;
        }
        case SQLCOM_REVOKE:
        case SQLCOM_GRANT: {
            // Later
        }


        // DDL
        case SQLCOM_CREATE_DB: {
            HA_CREATE_INFO create_info;
            res = mysql_create_db(thd, lex->name.str, &create_info);
            break;
        }

        // DDL + DQL + DML
        case SQLCOM_CREATE_TABLE:
        case SQLCOM_CREATE_INDEX:
        case SQLCOM_DROP_INDEX:

        case SQLCOM_SELECT:

        case SQLCOM_INSERT:
        case SQLCOM_DELETE:
        case SQLCOM_UPDATE: {
            res = lex->m_sql_cmd->execute(thd);
            break;
        }

        // TCL - Regular
        case SQLCOM_UNLOCK_TABLES: {
            break;
        case SQLCOM_LOCK_TABLES:
            res = trans_commit_implicit(thd);
            thd->locked_tables_list.unlock_locked_tables(thd);
            thd->mdl_context.release_transactional_locks();
            break;
        }
        case SQLCOM_BEGIN:
            if (trans_begin(thd, 0)) goto error;
            break;
        case SQLCOM_COMMIT: {
            if (trans_commit(thd)) goto error;
            thd->mdl_context.release_transactional_locks();
            /* Begin transaction with the same isolation level. */
            bool tx_chain = true;
            if (tx_chain) {
                if (trans_begin(thd)) goto error;
            }
            break;
        }
        case SQLCOM_ROLLBACK: {
            if (trans_rollback(thd)) goto error;
            thd->mdl_context.release_transactional_locks();
            /* Begin transaction with the same isolation level. */
            bool tx_chain = true;
            if (tx_chain) {
                if (trans_begin(thd)) goto error;
            }
            break;
        }

        // TCL - XA
        case SQLCOM_XA_START:
        case SQLCOM_XA_END:
        case SQLCOM_XA_PREPARE:
        case SQLCOM_XA_COMMIT:
        case SQLCOM_XA_ROLLBACK:
        case SQLCOM_XA_RECOVER: {
            res = lex->m_sql_cmd->execute(thd);
            break;
        }

        default:
            assert(0); /* Impossible */
            break;
    }
error:
    res = true;
    return 1;
}
