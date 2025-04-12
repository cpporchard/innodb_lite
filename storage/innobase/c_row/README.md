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