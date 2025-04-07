<!-- TOC -->
  * [Resources](#resources)
    * [Done](#done)
    * [To Do](#to-do)
  * [Concepts](#concepts)
    * [Chunk, Block, Page](#chunk-block-page-)
    * [Read/Write Path](#readwrite-path)
    * [Buffer Pool Structure](#buffer-pool-structure)
    * [LRU](#lru)
    * [Buddy Memory Management](#buddy-memory-management)
    * [Flushing](#flushing)
<!-- TOC -->

## Resources

### Done

- [x] Page Fix/Unfix, LRU List, Free List, and Flush List, Batch Flush, Lock Order (LRU list → hash map → block mutex →
  frame
  lock) https://www.alibabacloud.com/blog/an-in-depth-analysis-of-buffer-pool-in-innodb_601216?spm=a2c65.11461447.0.0.7748441aH4tpmJ
- [x] How Chunk, Block and Page are allocated https://genexdbs.com/how-to-verify-the-innodb-buffer-distribution/
- [x] Basics https://dev.mysql.com/doc/refman/8.0/en/innodb-buffer-pool.html
- [x] Code Flow https://www.leviathan.vip/2018/12/18/InnoDB%E7%9A%84BufferPool%E5%88%86%E6%9E%90/
- [x] All full forms , Buddy Memory Management https://juejin.cn/post/6844903507414220814

### To Do

- [ ] Read/Write Path https://docs.netapp.com/us-en/ontap-apps-dbs/mysql/mysql-file-structure.html
- [ ] Buffer pool concurrency control https://baotiao.github.io/2020/04/13/innodb-bp-coucurrency.html
- [ ] https://hidetatz.medium.com/how-innodb-writes-data-on-the-disk-1b109a8a8d14
- [ ] https://deepakmysqldba.wordpress.com/2021/05/09/innodb-mysql-8-architecture/
- [ ] Page Flushing https://hackmysql.com/book-6/
- [ ] Flushing https://lefred.be/content/a-graph-a-day-keeps-the-doctor-away-mysql-checkpoint-age/


## Concepts

### Chunk, Block, Page 

![https://www.leviathan.vip/2018/12/18/InnoDB%E7%9A%84BufferPool%E5%88%86%E6%9E%90/](img_2.png)

### Read/Write Path

![https://docs.netapp.com/us-en/ontap-apps-dbs/mysql/mysql-file-structure.html](img.png)

### Buffer Pool Structure

![https://dbadiaryy.wordpress.com/2018/01/26/innodb-buffer-pool/](img_3.png)

### LRU

![https://dev.mysql.com/doc/refman/8.0/en/innodb-buffer-pool.html](img_1.png)

### Buddy Memory Management
![https://blog.naver.com/kseo712/220883220425?viewType=pc](img_6.png)

### Flushing
![https://hackmysql.com/book-6/](img_4.png)

![img_5.png](img_5.png)




