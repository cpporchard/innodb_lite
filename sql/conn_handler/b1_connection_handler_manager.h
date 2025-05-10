//
// Created by Arjun Sunil Kumar on 5/6/25.
//

#ifndef CONNECTION_HANDLER_MANAGER_H
#define CONNECTION_HANDLER_MANAGER_H
#include "zz_channel_info.h"
#include "b0_connection_handler.h"


/**
  This is a singleton class that provides various connection management
  related functionalities, most importantly dispatching new connections
  to the currently active Connection_handler.
*/
class Connection_handler_manager {
  static Connection_handler_manager *m_instance;

  // Pointer to current connection handler in use
  Connection_handler *m_connection_handler;

public:

  /**
    Constructor to instantiate an instance of this class.
  */
  Connection_handler_manager(Connection_handler *connection_handler)
  : m_connection_handler(connection_handler){}

  static Connection_handler_manager *get_instance() {
    return m_instance;
  }

  bool init();

  /**
  Process a new incoming connection.

  @param channel_info    Pointer to Channel_info object containing
                         connection channel information.
*/
  void process_new_connection(Channel_info *channel_info);
};


#endif //CONNECTION_HANDLER_MANAGER_H
