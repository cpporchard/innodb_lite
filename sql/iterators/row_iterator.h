#ifndef SQL_ITERATORS_ROW_ITERATOR_H_
#define SQL_ITERATORS_ROW_ITERATOR_H_

#include "../table.h"

class RowIterator {
public:
    explicit RowIterator(THD *thd) : m_thd(thd) {
    }

    virtual ~RowIterator() = default;

    RowIterator(const RowIterator &) = delete;

    RowIterator(RowIterator &&) = default;

    virtual bool Init() = 0;

    virtual int Read() = 0;


    // In certain queries, such as SELECT FOR UPDATE, UPDATE or DELETE queries,
    // reading rows will automatically take locks on them. (This means that the
    // set of locks taken will depend on whether e.g. the optimizer chose a table
    // scan or used an index, due to InnoDB's row locking scheme with “gap locks”
    // for B-trees instead of full predicate locks.)
    //
    // However, under some transaction isolation levels (READ COMMITTED or
    // less strict), it is possible to release such locks if and only if the row
    // failed a WHERE predicate, as only the returned rows are protected,
    // not _which_ rows are returned. Thus, if Read() returned a row that you did
    // not actually use, you should call UnlockRow() afterwards, which allows the
    // storage engine to release the row lock in such situations.
    //
    // TableRowIterator has a default implementation of this; other iterators
    // should usually either forward the call to their source iterator (if any)
    // or just ignore it. The right behavior depends on the iterator.
    virtual void UnlockRow() = 0;

protected:
    THD *thd() const { return m_thd; }

private:
    THD *const m_thd;
};

class TableRowIterator : public RowIterator {
public:
    TableRowIterator(THD *thd, TABLE *table) : RowIterator(thd), m_table(table) {
    }

    void UnlockRow() override;

protected:
    TABLE *table() const { return m_table; }

private:
    TABLE *const m_table;
};

#endif  // SQL_ITERATORS_ROW_ITERATOR_H_
