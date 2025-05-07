//
// Created by Arjun Sunil Kumar on 5/4/25.
//

#include "conn_handler/a_connection_acceptor.h"
#include "conn_handler/a_socket_connection.h"

static Connection_acceptor<Mysqld_socket_listener> *mysqld_socket_acceptor = nullptr;

int main(int argc, char **argv) { mysqld_socket_acceptor = new Connection_acceptor(new Mysqld_socket_listener());
    mysqld_socket_acceptor->connection_event_loop();
    return 1;
}

