//
// Created by Arjun Sunil Kumar on 4/13/25.
//

#ifndef DICT0MEM_H
#define DICT0MEM_H


/** Data structure for a database table.  Most fields will be
initialized to 0, NULL or false in dict_mem_table_create(). */
struct dict_table_t {
    /** Check if the table is compressed.
    @return true if compressed, false otherwise. */
};

/** Data structure for a column in a table */
struct dict_col_t {
    /*----------------------*/
    /** The following are copied from dtype_t,
    so that all bit-fields can be packed tightly. */
    /** @{ */
};


#endif //DICT0MEM_H
