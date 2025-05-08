//
// Created by Arjun Sunil Kumar on 5/7/25.
//

#ifndef A1_SQL_SELECT_H
#define A1_SQL_SELECT_H

#include "../z_sql_dml.h"

class Item;
class Query_result;
class THD;


class Select_lex_visitor {
public:
    virtual bool visits_in_prefix_order() const { return true; }

    /// Called for all nodes of all expression trees (i.e. Item trees).
    bool visit(Item *item) { return visit_item(item); }
protected:
    virtual bool visit_item(Item *) { return false; }

};

class Sql_cmd_select : public Sql_cmd_dml {
public:
    explicit Sql_cmd_select(Query_result *result_arg) : Sql_cmd_dml() {
        // result = result_arg;
    }

    bool accept(THD *thd, Select_lex_visitor *visitor);

protected:
};

#endif //A1_SQL_SELECT_H
