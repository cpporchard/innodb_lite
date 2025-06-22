## Concepts

### Locking

```plantuml
@startuml
title InnoDB Write Path – Detailed (MTR, BTree, Lock, Redo, Buffer Pool)

actor client
participant mysqld
participant "MTR (Mini-Transaction)" as mtr
participant "Lock Manager" as lock
participant "BTree Page" as btr
participant "Buffer Pool" as buf_pool
participant "Redo Log" as redo
participant disk

client -> mysqld : write command (e.g. INSERT)

mysqld -> mtr : begin_mtr()

alt page not in buffer pool
  mtr -> buf_pool : request page
  buf_pool -> disk : fetch page from disk
  disk --> buf_pool : return page
end

mtr -> lock : acquire necessary row/page locks
lock --> mtr : lock granted

mtr -> btr : modify B-tree page
btr -> buf_pool : write page to memory

mtr -> redo : log changes (redo log)
redo -> disk : persist redo log

mtr -> mysqld : commit_mtr()
mysqld -> client : ACK

... later (checkpoint) ...
buf_pool -> disk : flush dirty pages to disk (checkpoint)

@enduml

```

### Isolation Levels

![img.png](img.png)

![img_1.png](img_1.png)

![img_2.png](img_2.png)

> This is when `innodb_lock_timeout` comes into picture

![img_3.png](img_3.png)

![img_4.png](img_4.png)


```plantuml
@startuml
title InnoDB Isolation Levels: Repeatable Read vs Read Committed

actor client

== Repeatable Read ==
box "Repeatable Read Transaction" #LightBlue
participant "TX_RR" as tx_rr
participant "Undo Log" as undo_rr
participant "Lock Manager" as lock_rr
end box

== Read Committed ==
box "Read Committed Transaction" #LightGreen
participant "TX_RC" as tx_rc
participant "Undo Log" as undo_rc
participant "Lock Manager" as lock_rc
end box

== Repeatable Read Flow ==
client -> tx_rr : START TRANSACTION
tx_rr -> undo_rr : Create snapshot (read_view at TX start)

client -> tx_rr : SELECT ... WHERE condition
tx_rr -> undo_rr : Traverse undo log (consistent snapshot)
tx_rr -> lock_rr : Acquire next-key lock
lock_rr --> tx_rr : Lock granted

client -> tx_rr : SELECT again
tx_rr -> undo_rr : Reuse same snapshot (Repeatable read!)

== Read Committed Flow ==
client -> tx_rc : START TRANSACTION

client -> tx_rc : SELECT ... WHERE condition
tx_rc -> undo_rc : Create snapshot (statement-level)
tx_rc -> undo_rc : Read latest committed row
tx_rc -> lock_rc : Acquire row lock only
lock_rc --> tx_rc : Lock granted

@enduml

```

![img_5.png](img_5.png)

![img_6.png](img_6.png)

> No wonder why `SELECT ... FOR UPDATE;` timed out.

```text
[5]----[10]----[15]----[20]----[25]
   ^                 ^
   Range: 10 to 20
   Locks:
     - Record lock on [10], [15], [20]
     - Gap locks: before 10, between 10–15, 15–20

  Prevents inserts at: 7, 12, 18

```
