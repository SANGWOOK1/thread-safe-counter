# thread-safe-counter

delay Time comparison (MUTEX vs Semaphore)(real , user, sys time )

Mutex : 
![image](https://user-images.githubusercontent.com/81486887/121805538-a9b7a180-cc86-11eb-8967-95b6e0812574.png)

Semaphore :
![image](https://user-images.githubusercontent.com/81486887/121808924-b7c0ee80-cc95-11eb-9a30-6827edb94642.png)

When comparing mutex and semaphore, it can be seen that the speed of semaphore is significantly slower than that of mutex.

Here's the reason why mutex and semaphore are diffenrt from time

first, A semaphore cannot be owned, whereas a mutex can be owned and the owner can be held responsible for it.(In the case of a mutex, it can have a lock because it is a lock with only two states.)

second, In the case of a mutex, the thread that owns the mutex can release the mutex.
However, in the case of a semaphore, a thread that does not own the semaphore can release the semaphore.

third, A semaphore spans system scope and exists as a file on the filesystem.
A mutex, on the other hand, has process scope and is automatically cleaned up when the process terminates.

and here's the definition of mutex and semaphore 

Mutex ) 
Preventing multiple threads from accessing shared resource data
It is a technique that allows the running time of threads with critical section to be executed independently so that they do not overlap with each other. Locking and unlocking are used to coordinate access to shared resources of multiple 

Semaphore )
Preventing multiple processes from accessing shared resource data. A semaphore can be thought of as a simple counter representing the state of a resource. It is usually used for a resource that has been secured for a relatively long time. or synchronization technology.
