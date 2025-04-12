//
// Created by Arjun Sunil Kumar on 4/11/25.
//

#ifndef DATA0DATA_H
#define DATA0DATA_H

/** Structure for an SQL data tuple of fields (logical record) */
struct dtuple_t {
    // /** info bits of an index record: the default is 0; this field is used if an
    // index record is built from a data tuple */
    // uint16_t info_bits;
    //
    // /** Number of fields in dtuple */
    // uint16_t n_fields;
    //
    // /** number of fields which should be used in comparison services of rem0cmp.*;
    // the index search is performed by comparing only these fields, others are
    // ignored; the default value in dtuple creation is the same value as n_fields */
    // uint16_t n_fields_cmp;
    //
    // /** Fields. */
    // dfield_t *fields;
    //
    // /** Number of virtual fields. */
    // uint16_t n_v_fields;
    //
    // /** Fields on virtual column */
    // dfield_t *v_fields;
    //
    // /** Data tuples can be linked into a list using this field */
    // UT_LIST_NODE_T(dtuple_t) tuple_list;
};

/** Storage format for overflow data in a big record, that is, a
clustered index record which needs external storage of data fields */
struct big_rec_t {
};

#endif //DATA0DATA_H
