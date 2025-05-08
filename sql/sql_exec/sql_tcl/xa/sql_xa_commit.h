#pragma once
#include "../../../sql_exec/z_sql_cmd.h"

class THD;

enum xa_option_words {
    XA_NONE,
    XA_JOIN,
    XA_RESUME,
    XA_ONE_PHASE,
    XA_SUSPEND,
    XA_FOR_MIGRATE
  };

class Sql_cmd_xa_commit :  public Sql_cmd {
    enum xa_option_words m_xa_opt;
public:
    bool execute(THD *thd);

    bool trans_xa_commit(THD *thd);

    bool process_attached_xa_commit(THD *thd) const;
};
