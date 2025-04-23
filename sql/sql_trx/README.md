## TODO

## Concepts
🔁 Regular COMMIT Path (non-XA)

```text
// Entry from SQL
mysql_execute_command()                   // sql/sql_parse.cc
├── trans_commit()                        // sql/transaction.cc
│   └── ha_commit_trans(thd, true, ...)   // sql/handler.cc
│       ├── tc_log->prepare(...)          // sql/tc_log.cc
│       ├── tc_log->commit(...)           // sql/tc_log.cc
│       └── trx_commit_for_mysql()       // InnoDB: storage/innobase/trx/

```

🔁 XA COMMIT Flow (2PC)
```text
Sql_cmd_xa_commit::execute()             // sql/xa/sql_xa_commit.cc
├── trans_xa_commit()                    // sql/xa/xa.cc
│   └── ha_commit_trans(thd, true, ...)  // sql/handler.cc
│       ├── tc_log->prepare(...)         // sql/tc_log.cc
│       ├── tc_log->commit(...)          // sql/tc_log.cc
│       └── SE-specific trx_commit_for_mysql() or equivalent
```

```text
                          +------------------------+
                          |      SQL Command       |
                          +----------+-------------+
                                     |
            +------------------------+--------------------------+
            |                                                   |
  +---------v----------+                              +---------v-------------------------+
  |     COMMIT;        |                              |        XA COMMIT 'xid';           |
  +--------------------+                              +-----------------------------------+
            |                                                   |
  +---------v----------+                              +---------v-------------------------+
  |  trans_commit()     |                              |   trans_xa_commit()              |
  | (sql/transaction.cc)|                              |   (sql/xa/xa.cc)                 |
  +---------------------+                              +----------------+-----------------+
            |                                                        |
  +---------v----------+                                +------------v-------------+
  | ha_commit_trans()  |                                |   tc_log->prepare()      | ← Phase 1
  | (calls SE commit)  |                                |   tc_log->commit()       | ← Phase 2
  +--------------------+                                +------------+-------------+
            |                                                        |
  +---------v----------+                                +------------v-------------+
  | SE Commit (InnoDB) |                                | SE Commit (InnoDB)        |
  | trx_commit_for_*() |                                | trx_commit_for_*()        |
  +--------------------+                                +--------------------------+
```