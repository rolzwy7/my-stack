create table t1(a int not null, b int, unique(a, b));
insert into t1 values(1, 1); /* ok - unique together */
insert into t1 values(2, 2); /* ok - unique together */
insert into t1 values(2, 1); /* ok - unique together */
insert into t1 values(2, 2);/* ko - duplicate */
/* ERROR 1062 (23000): Duplicate entry '2-2' for key 'a' */
