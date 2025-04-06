#ifndef TABLE_INCLUDED
#define TABLE_INCLUDED
#include "handler.h"

struct handler;

struct TABLE_SHARE {

};

struct TABLE {
    handler *file{nullptr};
};


struct THD {
    int killed{0};
};

#endif  // TABLE_INCLUDED