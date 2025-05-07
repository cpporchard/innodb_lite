//
// Created by Arjun Sunil Kumar on 5/6/25.
//

#ifndef CONNECTION_ACCEPTOR_H
#define CONNECTION_ACCEPTOR_H
#include "b1_connection_handler_manager.h"

template<typename Listener>
class Connection_acceptor {
    Listener *m_listener;

public:
    Connection_acceptor(Listener *listener) : m_listener(listener) {}

    ~Connection_acceptor() { delete m_listener; }

    /* Accessor function for _connection_events_loop_aborted flag */
    [[nodiscard]] inline bool connection_events_loop_aborted() {
        return true;
        // return connection_events_loop_aborted_flag.load();
    }

    /**
      Connection acceptor loop to accept connections from clients.
    */
    void connection_event_loop() {
        Connection_handler_manager *mgr =Connection_handler_manager::get_instance();

        while (!connection_events_loop_aborted()) {
            Channel_info *channel_info = m_listener->listen_for_connection_event();
            if (channel_info != nullptr) mgr->process_new_connection(channel_info);
        }
    }
};

#endif //CONNECTION_ACCEPTOR_H
