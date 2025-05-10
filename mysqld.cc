#include <iostream>

#include "sql/sql_io/a_table.h"
#include "sql/sql_io/iterators/basic_row_iterators.h"
#include "storage/innobase/a0_handler/ha_innodb.h"


int main() {
    TABLE table;
    table.record = new uchar[100]; // Allocate memory for the record
    table.file = new ha_innobase(nullptr, nullptr);

    ha_rows examined_rows = 0;
    TableScanIterator iter(nullptr, &table, 3.0, &examined_rows);

    if (iter.Init())
        return 1;

    while (iter.Read() == 0) {
        std::cout << "Row: " << iter.m_record << std::endl;
    }

    return 0;
}
