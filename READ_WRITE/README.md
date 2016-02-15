# Read-Write-Lock
It demonstrates the functionality of READ-WRITE LOCK using the pthread library.

It takes work item form work queue. Work queue is a queue which contains the work item as
1 - read operation, 0 - write operation.

It also takes a number of threads which you want to create and process work queue based on the work item. It performs
independently read-write operation. Pthread read-write lock protects the shared file resource from the inconsistent result.



-Jitendra
