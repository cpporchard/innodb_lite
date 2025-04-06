#ifndef TABLE_INCLUDED
#define TABLE_INCLUDED
#include "handler.h"
#include "iterators/basic_row_iterators.h"


class handler;

struct TABLE_SHARE {
};

struct TABLE {
    handler *file{nullptr};
    uchar * record;
};


struct THD {
    int killed{0};
};

#endif  // TABLE_INCLUDED
