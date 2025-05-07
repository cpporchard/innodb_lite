//
// Created by Arjun Sunil Kumar on 5/7/25.
//

#ifndef SQL_DB_H
#define SQL_DB_H

class THD;
/**
  Struct to hold information about the table that should be created.
 */
struct HA_CREATE_INFO {
};

bool mysql_create_db(THD *thd, const char *db, HA_CREATE_INFO *create_info);

#endif //SQL_DB_H
