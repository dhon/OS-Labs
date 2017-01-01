Request Scheduling using Threads and Synchronization
In this assignment, we will use threads and synchronization to implement
the Producer Consumer and the Bounded Buffer problem studied in class.
This lab needs to be completed in C/C++ using the pthreads library with the
overall goal of exposing you to threading and synchronization concepts.


The goal of the lab is to first implement a bounded buffer class and then use
it to implement the producer consumer problem. The first step is to implement a
bounded buffer using synchronization. First review lecture 9 slides (specifically
page 25 that describes the Bounded buffer implementation). Using these concepts,
implement a bounded buffer class using pthreads mutex (i.e., locks) and condition
variables. The constructor for your bounded buffer class should take N as an input
and instantiate an integer array of size N. Assume that the bounded buffer contains
integer data items.

As shown in the lecture slides, the bounded buffer is a circular buffer.
Upon reaching the end of the buffer array, your code should cycle back to
the start of the array to add new data items to the circular buffer. Items are
always added to the tail of the buffer and removed from the head of the buffer

Keep in mind that page 25 of lecture 9 showed a Hoare-style monitor
implementation, while pthreads condition variables use Mesa-style implementation.

Next implement a ProducerConsumer class that uses this Bounded Buffer
to produce and consumer data. Your class should have two main methods:
a producer() method where a producer thread sits in a loop and in each
iteration, it first sleeps for a specified duration, then produces a
data item (the data item in this case is a integer with a random value),
and calls the add method of the bounded buffer to add the data item to the buffer.

In the consumer() method, a consumer thread sits in a loop, and first
sleeps for a specified duration and then calls the remove method of the
bounded buffer to remove an item from the circular buffer.

The constructor for the ProducerConsumer class takes several inputs:

p: the number of producer thread to create, p should be at least 1
c: the number of consuemer threads to create, c should be at least 1
psleep: the time duration in milliseconds that a producer threads sleeps in each iteration
csleep: the time duration in milliseconds that a consumer threads sleeps in each iteration
items: the total number of data items that should be produced by all the producer threads
Given these inputs, the constructer method should create p producer threads,
each of which start in the producer() method, and c consumer threads, each of
which start in the consumer() method. After producer a data item, a producer
thread should increment a shared integer variable. When this variable reaches
item, all producer and consumer threads should quit (of course the consumer
threads should consume all items in the buffer as well before quitting).

Note that the bulk of the syncronization is done in the bounded buffer class,
while the bulk of thread management is done in the producer consumer class
(if you use any shared variables in producers and consumers, be sure to use
syncronization to protect those variables as well).

Your producer and consumer methods should print the following messages to a
file called "output.txt"
Producer #i, time = current time, producing data item #j, item value=foo
Consumer #k, time = current time, consuming data item with value=foo
