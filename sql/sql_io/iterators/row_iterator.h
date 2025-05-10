#ifndef SQL_ITERATORS_ROW_ITERATOR_H_
#define SQL_ITERATORS_ROW_ITERATOR_H_

#include "../b1_table.h"

struct THD;
struct TABLE;

class RowIterator {
public:
    explicit RowIterator(THD *thd) : m_thd(thd) {
    }

    virtual ~RowIterator() = default;

    RowIterator(const RowIterator &) = delete;

    RowIterator(RowIterator &&) = default;

    virtual bool Init() = 0;

    virtual int Read() = 0;

    // virtual void UnlockRow() = 0;

protected:
    THD *thd() const { return m_thd; }

private:
    THD *const m_thd;
};

class TableRowIterator : public RowIterator {
public:
    TableRowIterator(THD *thd, TABLE *table) : RowIterator(thd), m_table(table) {
    }

    // void UnlockRow() override;

protected:
    TABLE *table() const { return m_table; }

private:
    TABLE *const m_table;
};

#endif  // SQL_ITERATORS_ROW_ITERATOR_H_
