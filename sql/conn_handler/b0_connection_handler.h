//
// Created by Arjun Sunil Kumar on 5/6/25.
//

#ifndef CONNECTION_HANDLER_H
#define CONNECTION_HANDLER_H

class Channel_info;

/**
  This abstract base class represents how connections are processed,
  most importantly how they map to OS threads.
*/
class Connection_handler {
public:
  friend class Connection_handler_manager;

  Connection_handler() = default;
  virtual ~Connection_handler() = default;

  virtual bool add_connection(Channel_info* channel_info) = 0;
};

#endif //CONNECTION_HANDLER_H
