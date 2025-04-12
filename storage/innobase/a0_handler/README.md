
## Resources

### Done
- https://github.com/yangtau/example-engine/tree/master
- https://github.com/takatoshiono/mysql-mycsv/tree/master
- https://github.com/aboev/smalldb/blob/master/ha_smalldb.cc
- https://pmem.io/blog/2015/06/implementing-simple-mysql-storage-engine-with-libpmemobj/
- https://github.com/laysakura/mysql-YetAnotherSkeletonEngine/blob/master/src/ha_skeleton.cc


## Concepts

### Overall Flow

![https://www.oreilly.com/library/view/understanding-mysql-internals/0596009577/ch01.html](img.png)


### DS - MRR

```markdown
Simple Breakdown:
- MRR (Multi-Range Read): This is an optimization to read multiple row ranges more efficiently — especially helpful when using non-clustered indexes.
- Disk-Sweep: Instead of reading rows one by one in index order (which can jump all over the disk), it collects all the row locations first, sorts them, and reads them in disk order — this reduces random disk access and improves performance.

```