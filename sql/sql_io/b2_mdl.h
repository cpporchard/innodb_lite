//
// Created by Arjun Sunil Kumar on 5/7/25.
//

#ifndef MDL_H
#define MDL_H

// Meta Data Lock
class MDL_context {
public:
    void release_transactional_locks();
};

#endif //MDL_H
