//
// Created by Arjun Sunil Kumar on 5/6/25.
//

#include "b1_connection_handler_manager.h"
#include "c_connection_handler_impl.h"

class Channel_info;

Connection_handler_manager *Connection_handler_manager::m_instance = nullptr;


bool Connection_handler_manager::init() {
    Connection_handler *connection_handler = nullptr;
    connection_handler = new (std::nothrow) One_thread_connection_handler();
    m_instance = new (std::nothrow) Connection_handler_manager(connection_handler);
    return true;
}


void Connection_handler_manager::process_new_connection(Channel_info *channel_info) {
    // if (connection_events_loop_aborted() || !check_and_incr_conn_count(channel_info->is_admin_connection())) {
    //     channel_info->send_error_and_close_channel(ER_CON_COUNT_ERROR, 0, true);
    //     delete channel_info;
    //     return;
    // }

    if (m_connection_handler->add_connection(channel_info)) {
        // inc_aborted_connects();
        // delete channel_info;
    }
}
