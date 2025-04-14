## Concepts

### TODO
- [ ] https://www.mydbops.com/blog/innodb-physical-files-on-mysql-80
- [ ] https://breachdirectory.com/blog/innodb-from-the-inside-ibdata1-and-the-log-files/



### Table Space

![img.png](../f_page/img.png)

![img_4.png](img_4.png)

### Segment

![img_2.png](img_2.png)

![img_3.png](img_3.png)


### Tablespace etc Class defenition
```c++
class Row {
public:
    uint64_t trx_id;             // Last modifying transaction ID
    uint64_t roll_ptr;           // Undo log pointer
    std::vector<Field> fields;   // Field data
};

class Page {
public:
    uint32_t page_no;            // Page number in tablespace
    std::vector<Row> rows;       // Records stored in the page
};

class Extent {
public:
    static const int PAGE_COUNT = 64;
    std::array<Page, PAGE_COUNT> pages; // 64 contiguous pages
};

class SegmentInode {
public:
    uint64_t seg_id;             // Segment ID
    std::vector<Extent*> extents; // Extents owned by this segment
};

class Segment {
public:
    SegmentInode* inode;         // Tracks allocated extents
};

class Tablespace {
public:
    std::string name;
    std::vector<Segment> segments; // One segment per index/tree
    std::vector<Extent> free_extents; // Extents not yet assigned
};

```

Original Code

```c++
class Tablespace {
public:
    uint32_t space_id;           // Unique identifier for the tablespace
    uint32_t size;               // Size of the tablespace in pages
    uint32_t free_limit;         // Page number up to which pages have been initialized
    List<SegmentInode> segment_inodes; // List of segment inodes
    List<ExtentDescriptor> free_extents; // List of free extents
    // ... other metadata fields
};

//--------------------
class SegmentInode {
public:
    uint64_t segment_id;         // Unique identifier for the segment
    List<ExtentDescriptor> full_extents; // Extents fully used by the segment
    List<ExtentDescriptor> free_extents; // Extents with free pages
    List<ExtentDescriptor> free_frag_extents; // Extents partially used
    // ... other metadata fields
};
class ExtentDescriptor {
public:
    uint64_t segment_id;         // ID of the owning segment
    uint8_t state;               // State of the extent (e.g., free, full, fragment)
    Bitset<2 * 64> page_bitmap;  // Bitmap indicating the usage of each page
    // ... other metadata fields
};

//--------------------

class Page {
public:
    uint32_t page_number;        // Page number within the tablespace
    PageHeader header;           // Metadata about the page
    std::vector<Row> rows;       // Records stored in the page
    PageTrailer trailer;         // Checksum and other trailer info
};
class Row {
public:
    uint64_t trx_id;             // Transaction ID of the last modification
    uint64_t roll_ptr;           // Pointer to the undo log record
    std::vector<Field> fields;   // User-defined fields
};


```


### Segments can be BTree or Undo Log etc.

![img.png](img.png)

Note: Extend and Chunk(allocated by Buffer Pool) are same conceptually.

![img_1.png](img_1.png)

### ibd file layout

![img_5.png](img_5.png)

![https://blog.jcole.us/2013/01/03/the-basics-of-innodb-space-file-layout/](img_6.png)


### Other Files in MySQL data directory

![https://www.mydbops.com/blog/innodb-physical-files-on-mysql-80](img_7.png)


![https://breachdirectory.com/blog/innodb-from-the-inside-ibdata1-and-the-log-files/](img_8.png)

### What is FSeg?

![img_9.png](img_9.png)

![img_10.png](img_10.png)

![img_11.png](img_11.png)

![img_12.png](img_12.png)