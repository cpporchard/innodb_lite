## Concepts

### SDI

![img.png](img.png)

![img_1.png](img_1.png)

```text
+-------------------------+
|     InnoDB Tablespace   |
|         (.ibd file)     |
+-------------------------+
|                         |
|  +-------------------+  |
|  |   Table Data      |  |
|  +-------------------+  |
|                         |
|  +-------------------+  |
|  |   Index Data      |  |
|  +-------------------+  |
|                         |
|  +-------------------+  |
|  |   SDI (JSON)      |  | <-- Serialized metadata
|  +-------------------+  |
+-------------------------+

+-------------------------+
|   InnoDB Data Dictionary|
|     (System Tables)     |
+-------------------------+
|                         |
|  +-------------------+  |
|  |   Tables Metadata |  |
|  +-------------------+  |
|                         |
|  +-------------------+  |
|  |   Indexes Metadata|  |
|  +-------------------+  |
+-------------------------+


```


### Sample Code

```cpp

class Table_impl : public Abstract_table_impl, virtual public Table {
  Object_id m_se_private_id;
  String_type m_engine;
  String_type m_comment;
  enum_partition_type m_partition_type;
  String_type m_partition_expression;
  Index_collection m_indexes;
  Foreign_key_collection m_foreign_keys;
  Partition_collection m_partitions;
  Trigger_collection m_triggers;
  Check_constraint_collection m_check_constraints;
};


class Column_impl : public Entity_object_impl, public Column {
  enum_column_types m_type;
  bool m_is_nullable;
  bool m_is_auto_increment;
  String_type m_default_value;
};


class Index_impl : public Entity_object_impl, public Index {
  enum_index_type m_type;
  bool m_is_unique;
  Column_collection m_columns;
};

```

![img_2.png](img_2.png)

### Interaction

```plantuml
@startuml
actor User
participant "SQL Layer" as SQL
participant "InnoDB Engine" as InnoDB
participant "Transaction (trx)" as TRX
participant "Mini-Transaction (mtr)" as MTR
participant "Data Dictionary (dict)" as DICT
participant "Undo Log" as UNDO
participant "Redo Log" as REDO
participant "Buffer Pool" as BUFFER

User -> SQL : Executes INSERT statement
SQL -> InnoDB : Parses and plans INSERT
InnoDB -> DICT : Retrieves table and index metadata
InnoDB -> TRX : Begins transaction
InnoDB -> MTR : Starts mini-transaction
InnoDB -> UNDO : Writes undo log entry
InnoDB -> BUFFER : Modifies page in buffer pool
InnoDB -> REDO : Writes redo log entry
InnoDB -> MTR : Commits mini-transaction
InnoDB -> TRX : Commits transaction
@enduml

```


### Constraints

- Unique Key Constraints: `n_uniq /*!<number of fields from the begining which are enough to determine an index entry uniquely*/` 
- Foreign Key Constraints