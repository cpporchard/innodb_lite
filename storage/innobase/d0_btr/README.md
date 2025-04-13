## Resources

### Todo
-  [ ] https://www.percona.com/blog/innodb-page-merging-and-page-splitting/
-  [ ] http://mysql.taobao.org/monthly/2019/10/01/
- 

## Concepts

### File Layout

![https://liuyangming.tech/07-2019/InnoDB-overview.html](img.png)

![https://liuyangming.tech/07-2019/InnoDB-overview.html](img_2.png)


### BTree Lock
![https://baotiao.github.io/2024/06/09/english-btree.html](img_1.png)


### Questions regarding Page Splitting

```text
💾 So the Answer to Your Core Doubt:
“What if the page split, and older transactions only saw the original page?”

They don’t just see the old page.

InnoDB uses cursor-based navigation: row_search_mvcc() can and will scan both original and split pages.

But it only returns records visible to that transaction, even if they are now in new pages.

InnoDB does not attempt to preserve the old physical page layout for older transactions — that would be too costly.



```

![GPT](img_3.png)