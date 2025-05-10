//
// Created by Arjun Sunil Kumar on 5/7/25.
//

#include "a_socket_connection.h"

#include <new>

#include "zz_channel_info.h"

struct MYSQL_SOCKET {
};

/**
  This class abstracts the info. about TCP/IP socket mode of communication with
  the server.
*/
class Channel_info_tcpip_socket : public Channel_info {
    // connect socket object
    MYSQL_SOCKET m_connect_sock;
    bool m_is_admin_conn;

public:
    Channel_info_tcpip_socket(MYSQL_SOCKET connect_socket, bool is_admin_conn)
    : m_connect_sock(connect_socket), m_is_admin_conn(is_admin_conn) {}

};

Channel_info *Mysqld_socket_listener::listen_for_connection_event() {
    Channel_info *channel_info = nullptr;
    MYSQL_SOCKET connect_sock;
    channel_info = new (std::nothrow) Channel_info_tcpip_socket(connect_sock, true);

    return channel_info;
}

