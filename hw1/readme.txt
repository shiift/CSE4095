This homework had us use integers, however this limits the results to
2147483647. This is not ideal when computing large numbers such as in this
assignment. I added an error to the ex2.c program, but left ex1.c and ex3.c
alone since it would require the exact same steps.

An email chain between myself and  Professor Michel:

-- Original --
Hello Professor Michel,
What do you want us to do about cases where we get results larger or smaller
than what int(4 bytes) allows us to use? Should we print an error or just
leave it alone?

-- Response --
It is already good that you realized there was an issue. We do not want you to
take specific measures (except _maybe_ preventing inputs that cause overflows).
But do make a note of your observation in the read me file. 
