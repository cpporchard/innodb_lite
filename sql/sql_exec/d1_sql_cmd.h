//
// Created by Arjun Sunil Kumar on 4/22/25.
//

#ifndef SQL_COMMAND_H
#define SQL_COMMAND_H

class THD;

class Sql_cmd {
private:
    Sql_cmd(const Sql_cmd &);   // No copy constructor wanted
    void operator=(Sql_cmd &);  // No assignment operator wanted

public:
    virtual bool execute(THD *thd) = 0;

};

#endif //SQL_COMMAND_H
