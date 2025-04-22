#ifndef TABLE_INCLUDED
#define TABLE_INCLUDED
#include <memory>

#include "handler.h"
#include "xa.h"
#include "transaction_info.h"
#include "iterators/basic_row_iterators.h"


class handler;

struct TABLE_SHARE {
};

struct TABLE {
    handler *file{nullptr};
    uchar * record;
};


class THD {
public:
    int killed{0};
    std::unique_ptr<Transaction_ctx> m_transaction;
    Transaction_ctx *get_transaction() { return m_transaction.get(); }
};

#endif  // TABLE_INCLUDED
