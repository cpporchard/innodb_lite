## Concepts

### Read View
![https://liuyangming.tech/07-2019/InnoDB-overview.html](img.png)

### How is the history version constructed?

row_vers_build_for_consistent_read()

ROLL_PTR (pointer to an undo log record)

[ 55th bit is_insert | 48-54 bit rseg_id (7 bits) | 16-47 bit page_no (32 bits) | 0-15 bit offset (16 bits) ]


### What is read view

Read view captures the set of txn ids which was active when the snapshot was created (hence there changes,
should not be seen)

low_limit_id, up_limit_id, low_limit_no are used to speed up visibility check.

The purge view used when walking through the history chain during purge, is the oldest read view.

MVCC, locking and isolation levels provide a consistent view of the data to the transaction.