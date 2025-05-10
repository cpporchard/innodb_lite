//
// Created by Arjun Sunil Kumar on 5/4/25.
//

#ifndef QUERY_RESULT_H
#define QUERY_RESULT_H
#include "../../../sql_io/c1_item.h"
#include "../../b0_sql_class.h"

/*
  This is used to get result from a query
*/

class THD;
class Query_expression;

class Query_result {
protected:
  Query_expression *unit;
public:
  // virtual bool prepare(THD *, const mem_root_deque<Item *> &,Query_expression *u) {
  //   unit = u;
  //   return false;
  // }

  virtual bool start_execution(THD *) { return false; }
  virtual bool send_data(THD *thd, const mem_root_deque<Item *> &items) = 0;

};


class Query_result_send : public Query_result {
  bool send_data(THD *thd, const mem_root_deque<Item *> &items) override;
};

#endif //QUERY_RESULT_H
