#include <iostream>

#include "sql/table.h"
#include "sql/iterators/basic_row_iterators.h"
#include "storage/innobase/a_handler/ha_innodb.h"


int main() {
    TABLE table;
    table.file = new ha_innobase(nullptr, nullptr);

    // Scan rows using our iterator
    ha_rows examined_rows = 0;
    TableScanIterator iter(nullptr, &table, 3.0, &examined_rows);

    if (!iter.Init()) {
        int res;
        while (!(res = iter.Read())) {
            std::cout << "Row: " << iter.m_record << std::endl;
        }
    } else {
        std::cerr << "Failed to initialize table scan.\n";
    }

    return 0;
}
