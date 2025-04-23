

```text
CREATE table t1(a int, b int);

BEGIN;

INSERT into t1 values(1, 2);
INSERT into t1 values(3, 4);

COMMIT ;

SELECT * from t1;
```