//
// Created by Arjun Sunil Kumar on 4/22/25.
//

#ifndef SQL_PLUGIN_REF_H
#define SQL_PLUGIN_REF_H
#include <sys/types.h>

#include "../../sql_io/a_table.h"

struct st_plugin_int {
    void *data{nullptr};           /* plugin type specific, e.g. handlerton */
};
typedef struct st_plugin_int **plugin_ref;
typedef bool(plugin_foreach_func)(THD *thd, plugin_ref plugin, void *arg);
#define plugin_foreach(A, B, C, D) \
plugin_foreach_with_mask(A, B, C, PLUGIN_IS_READY, D)
extern bool plugin_foreach_with_mask(THD *thd, plugin_foreach_func *func,
                                     int type, uint state_mask, void *arg);
#define MYSQL_STORAGE_ENGINE_PLUGIN 1     /* Storage Engine               */
#define PLUGIN_IS_READY 8
template <typename T>
inline T plugin_data(st_plugin_int **ref) {
    return static_cast<T>(ref[0]->data);
}

#endif //SQL_PLUGIN_REF_H
