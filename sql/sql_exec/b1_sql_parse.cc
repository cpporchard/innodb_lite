#define DEBUG_SYNC(_thd_, _sync_point_name_)                 \
do {                                                         \
} while (0)
#include "b0_sql_lex.h"
#include "../sql_io/table.h"


class Table_ref;
class THD;

int mysql_execute_command(THD *thd, bool first_level) {
    int res = false;
    LEX *const lex = thd->lex;
    // Query_block *const query_block = lex->query_block;
    // Table_ref *const first_table = query_block->get_table_list();

    DEBUG_SYNC(thd, "execute_command_before_main_switch");

    switch (lex->sql_command) {

        case SQLCOM_CREATE_USER: {
            if (check_access(thd, INSERT_ACL, "mysql", nullptr, nullptr, true, true) &&
                check_global_access(thd, CREATE_USER_ACL))
                break;
            /* Conditionally writes to binlog */
            const HA_CREATE_INFO create_info(*lex->create_info);
            if (!(res = mysql_create_user(
                      thd, lex->users_list,
                      create_info.options & HA_LEX_CREATE_IF_NOT_EXISTS, false))) {}

            break;
        }
        case SQLCOM_REVOKE:
        case SQLCOM_GRANT: {
            // /* GRANT ... AS preliminery checks */
            // if (lex->grant_as.grant_as_used) {
            //     if ((first_table || query_block->db)) {
            //         my_error(ER_UNSUPPORTED_USE_OF_GRANT_AS, MYF(0));
            //         goto error;
            //     }
            // }
            // /*
            //   Skip access check if we're granting a proxy
            // */
            // if (lex->type != TYPE_ENUM_PROXY) {
            //     /*
            //       If there are static grants in the GRANT statement or there are no
            //       dynamic privileges we perform check_access on GRANT_OPTION based on
            //       static global privilege level and set the DA accordingly.
            //     */
            //     if (lex->grant > 0 || lex->dynamic_privileges.elements == 0) {
            //         /*
            //           check_access sets DA error message based on GRANT arguments.
            //         */
            //         if (check_access(
            //             thd, lex->grant | lex->grant_tot_col | GRANT_ACL,
            //             first_table ? first_table->db : query_block->db,
            //             first_table ? &first_table->grant.privilege : nullptr,
            //             first_table ? &first_table->grant.m_internal : nullptr,
            //             first_table ? false : true, false)) {
            //             goto error;
            //         }
            //     }
            //     /*
            //       ..else we still call check_access to load internal structures, but
            //       defer checking of global dynamic GRANT_OPTION to mysql_grant. We still
            //       ignore checks if this was a grant of a proxy.
            //     */
            //     else {
            //         /*
            //           check_access will load grant.privilege and grant.m_internal with
            //           values which are used later during column privilege checking. The
            //           return value isn't interesting as we'll check for dynamic global
            //           privileges later.
            //         */
            //         check_access(thd, lex->grant | lex->grant_tot_col | GRANT_ACL,
            //                      first_table ? first_table->db : query_block->db,
            //                      first_table ? &first_table->grant.privilege : nullptr,
            //                      first_table ? &first_table->grant.m_internal : nullptr,
            //                      first_table ? false : true, true);
            //     }
            // }
            //
            // /* Replicate current user as grantor */
            // thd->binlog_invoker();
            //
            // if (thd->security_context()->user().str) // If not replication
            // {
            //     LEX_USER *user, *tmp_user;
            //     bool first_user = true;
            //
            //     List_iterator<LEX_USER> user_list(lex->users_list);
            //     while ((tmp_user = user_list++)) {
            //         if (!(user = get_current_user(thd, tmp_user))) goto error;
            //         if (specialflag & SPECIAL_NO_RESOLVE &&
            //                 hostname_requires_resolving(user->host.str))
            //             push_warning(thd, Sql_condition::SL_WARNING,
            //                          ER_WARN_HOSTNAME_WONT_WORK,
            //                          ER_THD(thd, ER_WARN_HOSTNAME_WONT_WORK));
            //         // Are we trying to change a password of another user
            //         assert(user->host.str != nullptr);
            //
            //         /*
            //           GRANT/REVOKE PROXY has the target user as a first entry in the list.
            //          */
            //         if (lex->type == TYPE_ENUM_PROXY && first_user) {
            //             first_user = false;
            //             if (acl_check_proxy_grant_access(thd, user->host.str,
            //                                              user->user.str,
            //                                              lex->grant & GRANT_ACL))
            //                 goto error;
            //         }
            //     }
            // }
            // if (first_table) {
            //     if (lex->dynamic_privileges.elements > 0) {
            //         if (thd->lex->grant_if_exists) {
            //             push_warning_printf(thd, Sql_condition::SL_WARNING,
            //                                 ER_ILLEGAL_PRIVILEGE_LEVEL,
            //                                 ER_THD(thd, ER_ILLEGAL_PRIVILEGE_LEVEL),
            //                                 all_tables->table_name);
            //         } else {
            //             my_error(ER_ILLEGAL_PRIVILEGE_LEVEL, MYF(0),
            //                      all_tables->table_name);
            //             goto error;
            //         }
            //     }
            //     if (lex->type == TYPE_ENUM_PROCEDURE ||
            //         lex->type == TYPE_ENUM_FUNCTION) {
            //         uint grants = lex->all_privileges
            //                           ? (PROC_OP_ACLS) | (lex->grant & GRANT_ACL)
            //                           : lex->grant;
            //         if (check_grant_routine(thd, grants | GRANT_ACL, all_tables,
            //                                 lex->type == TYPE_ENUM_PROCEDURE, false))
            //             goto error;
            //         /* Conditionally writes to binlog */
            //         res = mysql_routine_grant(
            //             thd, all_tables, lex->type == TYPE_ENUM_PROCEDURE,
            //             lex->users_list, grants, lex->sql_command == SQLCOM_REVOKE, true,
            //             lex->all_privileges);
            //         if (!res) my_ok(thd);
            //     } else {
            //         if (check_grant(thd, (lex->grant | lex->grant_tot_col | GRANT_ACL),
            //                         all_tables, false, UINT_MAX, false))
            //             goto error;
            //         /* Conditionally writes to binlog */
            //         res = mysql_table_grant(
            //             thd, all_tables, lex->users_list, lex->columns, lex->grant,
            //             lex->sql_command == SQLCOM_REVOKE, lex->all_privileges);
            //     }
            // } else {
            //     if (lex->columns.elements ||
            //         (lex->type && lex->type != TYPE_ENUM_PROXY)) {
            //         my_error(ER_ILLEGAL_GRANT_FOR_TABLE, MYF(0));
            //         goto error;
            //     } else {
            //         /* Dynamic privileges are allowed only for global grants */
            //         if (query_block->db && lex->dynamic_privileges.elements > 0) {
            //             String privs;
            //             bool comma = false;
            //             for (const LEX_CSTRING &priv: lex->dynamic_privileges) {
            //                 if (comma) privs.append(",");
            //                 privs.append(priv.str, priv.length);
            //                 comma = true;
            //             }
            //             if (thd->lex->grant_if_exists) {
            //                 push_warning_printf(
            //                     thd, Sql_condition::SL_WARNING, ER_ILLEGAL_PRIVILEGE_LEVEL,
            //                     ER_THD(thd, ER_ILLEGAL_PRIVILEGE_LEVEL), privs.c_ptr());
            //             } else {
            //                 my_error(ER_ILLEGAL_PRIVILEGE_LEVEL, MYF(0), privs.c_ptr());
            //                 goto error;
            //             }
            //         }
            //         /* Conditionally writes to binlog */
            //         res = mysql_grant(
            //             thd, query_block->db, lex->users_list, lex->grant,
            //             lex->sql_command == SQLCOM_REVOKE, lex->type == TYPE_ENUM_PROXY,
            //             lex->dynamic_privileges, lex->all_privileges, &lex->grant_as);
            //     }
            // }
            // break;
        }

        case SQLCOM_CREATE_DB: {
            const char *alias;
            if (!(alias = thd->strmake(lex->name.str, lex->name.length)) ||
                (check_and_convert_db_name(&lex->name, false) !=
                 Ident_name_check::OK))
                break;
            if (check_access(thd, CREATE_ACL, lex->name.str, nullptr, nullptr, true,
                             false))
                break;
            /*
              As mysql_create_db() may modify HA_CREATE_INFO structure passed to
              it, we need to use a copy of LEX::create_info to make execution
              prepared statement- safe.
            */
            HA_CREATE_INFO create_info(*lex->create_info);
            res = mysql_create_db(
                thd, (lower_case_table_names == 2 ? alias : lex->name.str),
                &create_info);
            break;
        }

        case SQLCOM_INSERT:
        case SQLCOM_DELETE:
        case SQLCOM_UPDATE:
        case SQLCOM_CREATE_TABLE:
        case SQLCOM_CREATE_INDEX:
        case SQLCOM_DROP_INDEX: {
            assert(first_table == all_tables && first_table != nullptr);
            assert(lex->m_sql_cmd != nullptr);
            res = lex->m_sql_cmd->execute(thd);
            break;
        }

        case SQLCOM_PREPARE: {
            mysql_sql_stmt_prepare(thd);
            break;
        }
        case SQLCOM_EXECUTE: {
            mysql_sql_stmt_execute(thd);
            break;
        }
        case SQLCOM_DEALLOCATE_PREPARE: {
            mysql_sql_stmt_close(thd);
            break;
        }
        case SQLCOM_UNLOCK_TABLES: {
            if (thd->variables.option_bits & OPTION_TABLE_LOCK) {
                /*
                  Can we commit safely? If not, return to avoid releasing
                  transactional metadata locks.
                */
                if (trans_check_state(thd)) return -1;
                res = trans_commit_implicit(thd);
                thd->locked_tables_list.unlock_locked_tables(thd);
                thd->mdl_context.release_transactional_locks();
                thd->variables.option_bits &= ~(OPTION_TABLE_LOCK);
            }
            if (thd->global_read_lock.is_acquired())
                thd->global_read_lock.unlock_global_read_lock(thd);
            if (res) goto error;
            my_ok(thd);
            break;
            case SQLCOM_LOCK_TABLES:
                /*
                  Can we commit safely? If not, return to avoid releasing
                  transactional metadata locks.
                */
                    if (trans_check_state(thd)) return -1;
            /* We must end the transaction first, regardless of anything */
            res = trans_commit_implicit(thd);
            thd->locked_tables_list.unlock_locked_tables(thd);
            /* Release transactional metadata locks. */
            thd->mdl_context.release_transactional_locks();
            if (res) goto error;

            if (open_temporary_tables(thd, all_tables)) goto error;

            if (lock_tables_precheck(thd, all_tables)) goto error;

            thd->variables.option_bits |= OPTION_TABLE_LOCK;

            res = lock_tables_open_and_lock_tables(thd, all_tables);

            if (res) {
                thd->variables.option_bits &= ~(OPTION_TABLE_LOCK);
            } else {
                my_ok(thd);
            }
            break;
        }

        case SQLCOM_BEGIN:
            if (trans_begin(thd, lex->start_transaction_opt)) goto error;
            break;
        case SQLCOM_COMMIT: {
            assert(thd->lock == nullptr ||
                   thd->locked_tables_mode == LTM_LOCK_TABLES);
            const bool tx_chain =
            (lex->tx_chain == TVL_YES ||
             (thd->variables.completion_type == 1 && lex->tx_chain != TVL_NO));
            const bool tx_release =
            (lex->tx_release == TVL_YES ||
             (thd->variables.completion_type == 2 && lex->tx_release != TVL_NO));
            if (trans_commit(thd)) goto error;
            thd->mdl_context.release_transactional_locks();
            /* Begin transaction with the same isolation level. */
            if (tx_chain) {
                if (trans_begin(thd)) goto error;
            } else {
                /* Reset the isolation level and access mode if no chaining
                 * transaction.*/
                trans_reset_one_shot_chistics(thd);
            }
            /* Disconnect the current client connection. */
            if (tx_release) thd->killed = THD::KILL_CONNECTION;
            my_ok(thd);
            break;
        }
        case SQLCOM_ROLLBACK: {
            assert(thd->lock == nullptr ||
                   thd->locked_tables_mode == LTM_LOCK_TABLES);
            const bool tx_chain =
            (lex->tx_chain == TVL_YES ||
             (thd->variables.completion_type == 1 && lex->tx_chain != TVL_NO));
            const bool tx_release =
            (lex->tx_release == TVL_YES ||
             (thd->variables.completion_type == 2 && lex->tx_release != TVL_NO));
            if (trans_rollback(thd)) goto error;
            thd->mdl_context.release_transactional_locks();
            /* Begin transaction with the same isolation level. */
            if (tx_chain) {
                if (trans_begin(thd)) goto error;
            } else {
                /* Reset the isolation level and access mode if no chaining
                 * transaction.*/
                trans_reset_one_shot_chistics(thd);
            }
            /* Disconnect the current client connection. */
            if (tx_release) thd->killed = THD::KILL_CONNECTION;
            my_ok(thd);
            break;

            default:
                assert(0); /* Impossible */
            my_ok(thd);
            break;
        }
        goto finish;
    }

}