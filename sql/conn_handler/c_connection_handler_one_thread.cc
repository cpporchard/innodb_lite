#include "c_connection_handler_impl.h"
#include "z_channel_info.h"
#include "../sql_exec/b1_sql_parse.h"

bool One_thread_connection_handler::add_connection(Channel_info* channel_info) {
    THD *thd = channel_info->create_thd();

    if (do_command(thd)) {
        return false;
    }
    return true;
}
