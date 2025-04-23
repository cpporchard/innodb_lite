#ifndef HA_INNODB_H
#define HA_INNODB_H
#include <sys/types.h>
#include "../../../sql/sql_exec/sql_tcl/b_handler.h"


struct TABLE;
struct handlerton;
struct TABLE_SHARE;

class ha_innobase : public b_handler {
public:
    ha_innobase(handlerton *hton, TABLE_SHARE *table_arg);

    ~ha_innobase() override;

    int write_row(uchar *record);


    // int create(const char *name, TABLE *form, HA_CREATE_INFO *, dd::Table *table_def) override;
    //
    // int open(const char *name, int mode, uint test_if_locked, const dd::Table *table_def) override;
    //
    // int close() override;

    // int write_row(uchar *buf) override;
    //
    // int update_row(const uchar *old_data, uchar *new_data) override;
    //
    // int delete_row(const uchar *buf) override;

    // int rnd_init(bool scan);
    //
    // int rnd_next(uchar *buf);

    int rnd_init(bool scan) override;

    int rnd_next(uchar *buf) override;

    int general_fetch(uchar *buf, uint direction, uint match_mode);

    void update_thd(THD *thd);

    void update_thd();

    int extra(enum ha_extra_function operation);
};

#endif //HA_INNODB_H
