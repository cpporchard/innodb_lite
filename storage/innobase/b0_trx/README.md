
## Resources

### Todo
- [ ] https://blog.csdn.net/weixin_35500243/article/details/113277478
- [ ] https://zhuanlan.zhihu.com/p/40208895
- [ ] https://www.racecoder.com/archives/1070/


## Concepts

### Txn Flow

![https://topic.it168.com/factory/DTCC2013/doc/a30.pdf](img.png)

### Locks

![https://liuyangming.tech/07-2019/InnoDB-overview.html](img_1.png)

### Flow

![https://liuyangming.tech/07-2019/InnoDB-overview.html](img_2.png)

### Undo Log
![https://www.alibabacloud.com/blog/an-in-depth-analysis-of-undo-logs-in-innodb_598966](img_3.png)

![https://www.alibabacloud.com/blog/an-in-depth-analysis-of-undo-logs-in-innodb_598966](img_4.png)

![https://www.alibabacloud.com/blog/an-in-depth-analysis-of-undo-logs-in-innodb_598966](img_5.png)

![https://blog.jcole.us/2014/04/16/the-basics-of-the-innodb-undo-logging-and-history-system/](img_7.png)

![https://www.racecoder.com/archives/1070/](img_11.png)

### Group Commit (Mostly Dist Txn)

![https://hackmysql.com/group-commit-and-trx-dependency-tracking/](img_6.png)


### tc_log

It is not part of ha_xxx. It is part of xa.cc
![https://blog.csdn.net/weixin_35500243/article/details/113277478](img_8.png)

### trx_sys

![https://zhuanlan.zhihu.com/p/40208895](img_10.png)

```text
Central place that maintains all the txn lists.
However, it doesn't do conflict detection. It is done when row locks are acquired.


Why is trx_sys critical?
- It enables MVCC (Multi-Version Concurrency Control) by managing snapshots and read views
- It allows the purge thread to clean undo logs only when no active transaction needs them
- It keeps transactions isolated while coordinating their lifecycle (start, commit, rollback)
- It supports crash recovery by tracking undo log metadata


It acts as the central coordinator for:
All active transactions
- Undo logs
- Purge operations
- Rollback segments
- Access to concurrency-related structures
```



### Replication

![https://alibaba-cloud.medium.com/mysql-engine-features-innodb-based-physical-replication-a345990bd266](img_9.png)
