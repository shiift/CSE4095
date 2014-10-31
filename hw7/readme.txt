William Dickson - CSE 4095: Homework 7 - README

Using the time command with the program yielded the following results
(on average) for various input sizes:

-------------------------------------------------------------

time ./threads -t 1 -d 100
Matrix sum =  990000.000000

real    0m0.011s
user    0m0.011s
sys     0m0.000s

time ./threads -t 10 -d 100
Matrix sum =  990000.000000

real    0m0.006s
user    0m0.010s
sys     0m0.000s

time ./threads -t 30 -d 100
Matrix sum =  990000.000000

real    0m0.009s
user    0m0.015s
sys     0m0.002s

-------------------------------------------------------------

time ./threads -t 1 -d 500
Matrix sum =  124750000.000000

real    0m1.412s
user    0m1.411s
sys     0m0.002s

time ./threads -t 10 -d 500
Matrix sum =  124750000.000000

real    0m0.595s
user    0m1.181s
sys     0m0.005s

time ./threads -t 30 -d 500
Matrix sum =  124750000.000000

real    0m0.592s
user    0m1.179s
sys     0m0.001s

-------------------------------------------------------------

From these results we can see that by using multiple threads we can cut the real
time needed to execute the function down by half or more. As expected larger
data sets gives us more improvement. The reason for this is that the larger data
sets will have more time where thread operations overlap due to the larger
number of operations each thread needs to run through. With a smaller set of
data (100x100 matrix) we see a large improvement between 1 thread and 10
threads, however 30 threads actually worsens the run time. This is due to the
large overhead in creating threads. With larger data sets (500x500) we do not
see the same issue because the time cost in creating threads is made up for by
the improvement due to having multiple threads. This tells me that the optimal
number of threads is dependent on the number of operations/size of the data set.

Aside: My first version of this program actually ran slower than the original
program. The reason is because it was designed closer to the original program in
that it computed through all of the sums, then all of the products separately. A
problem here is that I was re-creating each thread used which doubled the impact
of the thread creation overhead. I solved this by creating a run_threads
procedure that runs both the sum and square functions using the threads. Another
benefit to using this method is that threads can begin work on the squaring
operations before the last thread is done summing.
