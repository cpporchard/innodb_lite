#ifndef TABLE_INCLUDED
#define TABLE_INCLUDED
#include <memory>

#include "b0_mdl.h"
#include "../sql_exec/sql_tcl/b_handler.h"
#include "../sql_exec/sql_tcl/a0_xa.h"
#include "../sql_exec/sql_tcl/z_transaction_info.h"
#include "iterators/basic_row_iterators.h"


struct LEX;
class b_handler;

struct TABLE_SHARE {
};

struct TABLE {
    b_handler *file{nullptr};
    uchar * record;
};

struct LEX_USER {
};




#endif  // TABLE_INCLUDED
