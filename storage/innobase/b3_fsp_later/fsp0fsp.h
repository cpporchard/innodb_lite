//
// Created by Arjun Sunil Kumar on 4/12/25.
//

#ifndef FSP0FSP_H
#define FSP0FSP_H
#include <cstddef>
#include <cstdint>

/** @name File segment header
The file segment header points to the inode describing the file segment. */
/** @{ */
/** Data type for file segment header */
typedef std::byte fseg_header_t;

/** Tablespace identifier */
typedef uint32_t space_id_t;

/* Note that inside MySQL 'byte' is defined as char on Linux! */
using byte = unsigned char;

/*                      FILE SEGMENT INODE
                        ==================

Segment inode which is created for each segment in a tablespace. NOTE: in
purge we assume that a segment having only one currently used page can be
freed in a few steps, so that the freeing cannot fill the file buffer with
bufferfixed file pages. */

typedef byte fseg_inode_t;


#endif //FSP0FSP_H
