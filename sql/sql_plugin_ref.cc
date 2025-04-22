#include "sql_plugin_ref.h"

#include <sys/types.h>

#include "table.h"
//
// Created by Arjun Sunil Kumar on 4/22/25.
//
bool plugin_foreach_with_mask(THD *thd, plugin_foreach_func **funcs, int type,
                              uint state_mask, void *arg) {
    return true;
};

bool plugin_foreach_with_mask(THD *thd, plugin_foreach_func *func, int type,
                              uint state_mask, void *arg) {
    plugin_foreach_func *funcs[] = {func, nullptr};

    return plugin_foreach_with_mask(thd, funcs, type, state_mask, arg);
}

