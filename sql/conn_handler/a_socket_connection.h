//
// Created by Arjun Sunil Kumar on 5/6/25.
//

#ifndef SOCKET_CONNECTION_H
#define SOCKET_CONNECTION_H
#include "zz_channel_info.h"

/**
  This class represents the Mysqld_socket_listener which prepares the
  listener sockets to receive connection events from the client. The
  Mysqld_socket_listener may be composed of either or both a tcp socket
  which listens on a default mysqld tcp port or a user specified  port
  via mysqld command-line and a unix socket which is bound to a mysqld
  default pathname.
*/
class Mysqld_socket_listener {
public:
  /**
    The body of the event loop that listen for connection events from clients.

    @retval Channel_info   Channel_info object abstracting the connected client
                           details for processing this connection.
  */
  Channel_info *listen_for_connection_event();
};

#endif //SOCKET_CONNECTION_H
