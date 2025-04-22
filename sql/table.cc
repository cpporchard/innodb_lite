//
// Created by Arjun Sunil Kumar on 4/22/25.
//

#include "table.h"

Ha_trx_info_list Transaction_ctx::ha_trx_info(enum_trx_scope scope) {
    return Ha_trx_info_list{};
};