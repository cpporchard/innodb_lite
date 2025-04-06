#ifndef SQL_ITERATORS_BASIC_ROW_ITERATORS_H_
#define SQL_ITERATORS_BASIC_ROW_ITERATORS_H_
#include "row_iterator.h"

typedef unsigned char uchar;
#define ha_rows unsigned long long

class TableScanIterator final : public TableRowIterator {
public:
    TableScanIterator(THD *thd, TABLE *table, double expected_rows, ha_rows *examined_rows);

    ~TableScanIterator() override;

    bool Init() override;

    int Read() override;

    uchar *const m_record;
};

#endif
