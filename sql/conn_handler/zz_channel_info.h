//
// Created by Arjun Sunil Kumar on 5/6/25.
//

#ifndef CHANNEL_INFO_H
#define CHANNEL_INFO_H

class THD;
/**
  This abstract base class represents connection channel information
  about a new connection. Its subclasses encapsulate differences
  between different connection channel types.

  Currently we support local and TCP/IP sockets (all platforms),
  named pipes and shared memory (Windows only).
*/
class Channel_info {
public:
    virtual THD *create_thd();
};

#endif //CHANNEL_INFO_H
