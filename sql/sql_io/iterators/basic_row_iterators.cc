#include "basic_row_iterators.h"
#include <string>
#include "../../sql_exec/b0_sql_class.h"

using std::string;

#define ha_rows unsigned long long
#define HA_ERR_RECORD_DELETED 1

TableScanIterator::TableScanIterator(THD *thd, TABLE *table,
                                     double expected_rows,
                                     ha_rows *examined_rows)
    : TableRowIterator(thd, table),
      m_record(table->record) {
}

TableScanIterator::~TableScanIterator() = default;

bool TableScanIterator::Init() {
    return false;
}

int TableScanIterator::Read() {
    int tmp;

    while ((tmp = table()->file->ha_rnd_next(m_record))) {
        if (tmp == HA_ERR_RECORD_DELETED && !thd()->killed) continue;
        return 0;
    }
    return 0;
}
