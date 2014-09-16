Run 1:

Upon first run of the program using gdb I found the following error:

Program received signal SIGSEGV, Segmentation fault.
0x00000000004005c9 in main (argc=1, argv=0x7fffffffe448) at ex1.c:8
8                       x[i] = i;

This error states that there was a segfault on line 8 of the program.

After looking at the for loop surrounding line 8 I found the following:

for(i = 0; i < 10000; ++i){
    x[i] = i;
}

Since x[1000] is defined on line 5, the loop goes beyond the allocated
memory for the array. This can be easily fixed by changing line 5 to read:

x[10000];

===============================================================================
Run 2:

Running the program for the second time (with the first error fixed we get the
following message displayed:

Enter integer in 0..9999:

I decided to enter the value 0 as a starting value.

This time we get another segmentation fault:

Program received signal SIGSEGV, Segmentation fault.
0x00007ffff7a75882 in __GI__IO_vfscanf () from /lib64/libc.so.6

This issue appears to come from the scanf call. From examples in class I get
the feeling that it's because the value stored location is not a pointer.
Lo and behold that is exactly the problem. The original line looks like this:

scanf("%d", k);

but it should look like this:

scanf("%d", &k);

===============================================================================
Run 3:

With the first two errors fixed I run the program for a third time. This time I
input 0 again and we seem to get a passing test! To make sure that this works for
other numbers I tried a few more values:
1, 2, 10, 20, 100, and 9999

All of these tests passed. Ship it!
