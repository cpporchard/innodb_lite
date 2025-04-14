## Concepts

### Purge Thread

```text

+---------------------------------------------+
|      InnoDB Server Initialization Phase     |
|   (after crash or DDL recovery is complete) |
+---------------------------------------------+
| srv_start()                                 |
|   └── ddl_recovery()                        |
|       └── complete_recovery()               |
|           └── srv_start_thread_after_ddl_recovery()  ← [YOU ARE HERE] 
|                 ├── start page cleaner      |
|                 ├── start purge thread      |
|                 └── start background tasks  |
+---------------------------------------------+
                          |
                          v
+--------------------------------+
| srv_start_purge_thread()       |  ← Starts the purge thread
+--------------------------------+
           |
           v
+------------------------------------+
| purge_coordinator_thread()         |  ← Main loop that drives purge
|   └── trx_purge()                  |  ← Purges old undo logs / history
|       └── trx_purge_run()         |
|           └── trx_purge_truncate_undo_logs()
+------------------------------------+

```

### Operations


#### Checkpoint

3 Types
- Sharp checkpoint
- Fuzzy checkpoint
- Adaptive flushing

![img.png](img.png)

![img_1.png](img_1.png)

![img_2.png](img_2.png)

![img_3.png](img_3.png)

![img_8.png](img_8.png)

![img_9.png](img_9.png)

![img_10.png](img_10.png)

![img_11.png](img_11.png)

![img_12.png](img_12.png)

#### Purge

![img_4.png](img_4.png)

![img_5.png](img_5.png)

![img_6.png](img_6.png)

![img_7.png](img_7.png)