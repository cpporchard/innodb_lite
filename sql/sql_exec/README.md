

```text
CREATE table t1(a int, b int);

BEGIN;

INSERT into t1 values(1, 2);
INSERT into t1 values(3, 4);

COMMIT ;

SELECT * from t1;
```

Main logic is here
```c++
bool dispatch_command(THD *thd, const COM_DATA *com_data, enum enum_server_command command);
```
