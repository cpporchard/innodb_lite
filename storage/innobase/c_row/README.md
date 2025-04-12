## Concepts

### Write Flow

```text
ha_innobase::write_row()
  └── row_insert_for_mysql()
      └── row_insert_for_mysql_using_ins_graph()
          └── row_ins_step()
              └── row_ins()
                  └── row_ins_index_entry_step()
                      └── row_ins_index_entry()
                          └── row_ins_clust_index_entry()
                              └── row_ins_clust_index_entry_low()....
```

```text
+---------------------------+
| ha_innobase::write_row()  |  <-- Entry point from MySQL Server layer
+---------------------------+
            |
            v
+----------------------------+
| row_insert_for_mysql()     |  <-- Prepares insert tuple, triggers row graph insert
+----------------------------+
            |
            v
+--------------------------------------+
| row_insert_for_mysql_using_ins_graph()| <-- Builds execution graph for insert ops
+--------------------------------------+
            |
            v
+------------------+
| row_ins_step()   |  <-- Executes one insert step (loop over graph)
+------------------+
            |
            v
+-------------+
| row_ins()   |  <-- Main insert function (calls for index insertions)
+-------------+
            |
            v
+-----------------------------+
| row_ins_index_entry_step()  |  <-- Handles insert per index
+-----------------------------+
            |
            v
+------------------------+
| row_ins_index_entry()  |  <-- Delegates to clustered or secondary insert
+------------------------+
            |
            v
+-------------------------------+
| row_ins_clust_index_entry()   |  <-- Clustered index insertion logic
+-------------------------------+
            |
            v
+----------------------------------+
| row_ins_clust_index_entry_low()  |  <-- Does actual B-tree insert
+----------------------------------+


                                                ↓
+-------------------------------------------------------------+
|                  InnoDB Storage Layer (B-Tree)              |
+-------------------------------------------------------------+
| row_ins_clust_index_entry_low()                             |
|   └── btr_cur_pessimistic_insert()  ←-- Lock, Search, Insert|
+-------------------------------------------------------------+
              ↓
+-------------------------------------------------------------+
|                Undo Log / Transaction Subsystem             |
+-------------------------------------------------------------+
| btr_cur_pessimistic_insert()                                |
|   └── trx_undo_report_row_operation() ←-- Log INSERT action |
|         └── trx_undo_add_page() ←-- Add page to undo segment|
+-------------------------------------------------------------+
              ↓
+-------------------------------------------------------------+
|                Tablespace & File Segment Mgmt              |
+-------------------------------------------------------------+
| trx_undo_add_page()                                        |
|   └── fseg_alloc_free_page_general() ←-- Alloc new page    |
|         └── fseg_inode_get() ←-- Get inode for fseg        |
+-------------------------------------------------------------+
              ↓
+-------------------------------------------------------------+
|                    Buffer Pool & Disk I/O                  |
+-------------------------------------------------------------+
| fseg_inode_get()                                           |
|   └── buf_page_get_gen() ←-- Load page into buffer pool    |
+-------------------------------------------------------------+
```


```text

```