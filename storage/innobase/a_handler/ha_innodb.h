#ifndef HA_INNODB_H
#define HA_INNODB_H
#include <sys/types.h>
#include "../../../sql/handler.h"


struct TABLE;
struct handlerton;
struct TABLE_SHARE;

class ha_innobase : public handler {
public:
    ha_innobase(handlerton *hton, TABLE_SHARE *table_arg);

    ~ha_innobase() override;


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

    int rnd_init(bool scan);

    int rnd_next(uchar *buf);

    int general_fetch(uchar *buf, uint direction, uint match_mode);
};

#endif //HA_INNODB_H
