#include "z_transaction_info.h"

Ha_trx_info_list Transaction_ctx::ha_trx_info(enum_trx_scope scope) {
    return Ha_trx_info_list{};
}

void Transaction_ctx::cleanup() {

};
