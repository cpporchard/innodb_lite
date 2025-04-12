#ifndef HANDLER_INCLUDED
#define HANDLER_INCLUDED
#include "table.h"

struct TABLE_SHARE;
struct TABLE;
struct THD;

struct handlerton {
};

typedef unsigned char uchar; /* Short for unsigned char */
#define thr_lock_type int


enum ha_extra_function {
    HA_EXTRA_FLUSH
};


class handler {
public:
    TABLE_SHARE *table_share; /* The table definition */
    TABLE *table; /* The current open table */
    handlerton *ht; /* storage engine of this handler */


    handler(handlerton *ht_arg, TABLE_SHARE *share_arg)
        : table_share(share_arg),
          table(nullptr),
          ht(ht_arg) {
    }

    virtual ~handler(void) {
    }


    // int ha_open(TABLE *table, const char *name, int mode, int test_if_locked, const dd::Table *table_def);
    //
    // int ha_close(void);

    int ha_rnd_init(bool scan);

    int ha_rnd_end();

    int ha_rnd_next(uchar *buf);

    int ha_extra(enum ha_extra_function operation);


    virtual int rnd_init(bool scan) = 0;

    virtual int rnd_next(uchar *buf) = 0;

    virtual int extra(enum ha_extra_function operation [[maybe_unused]]) {
        return 0;
    }


    /**
      Start a statement when table is locked

      This method is called instead of external lock when the table is locked
      before the statement is executed.
    */
    virtual int start_stmt(THD *thd [[maybe_unused]],
                           thr_lock_type lock_type [[maybe_unused]]) {
        return 0;
    }
};

#endif
