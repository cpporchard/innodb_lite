//
// Created by Arjun Sunil Kumar on 5/7/25.
//

#ifndef ITEM_H
#define ITEM_H

class Item: public Parse_tree_node {
    /**
      If this Item is being materialized into a temporary table, returns the
      field that is being materialized into. (Typically, this is the
      “result_field” members for items that have one.)
     */
    virtual Field *get_tmp_table_field() {
        return nullptr;
    }

};

#endif //ITEM_H
