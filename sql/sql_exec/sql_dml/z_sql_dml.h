#ifndef Z_SQL_DML_H
#define Z_SQL_DML_H

#include "../z_sql_cmd.h"

struct LEX;
class THD;
class Sql_cmd;

class Sql_cmd_dml : public Sql_cmd {
public:
    LEX *lex;
    bool execute_inner(THD *thd);

    bool prepare(THD *thd);

    bool execute(THD *thd) override;

};

#endif //Z_SQL_DML_H
