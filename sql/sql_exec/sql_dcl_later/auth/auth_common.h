//
// Created by Arjun Sunil Kumar on 5/7/25.
//

#ifndef AUTH_COMMON_H
#define AUTH_COMMON_H

struct LEX_USER;

bool mysql_create_user(THD *thd, List<LEX_USER> &list, bool if_not_exists,bool is_role);

#endif //AUTH_COMMON_H
