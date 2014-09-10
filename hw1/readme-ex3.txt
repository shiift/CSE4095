We seem to run into issues with very large values of n. After this point printf
displays a value of infinity. Because of the way doubles are stored in memory
you lose precision around n = 23 (for base 10). This is because double precision
values are stored as decimals and exponents and when the numbers get too high
the decimal part of the number (which determines the lower digits of the number)
loses accuracy and gets "cut off".

The function power is the original power function and power2 is the power
function that runs in logarithmic time.
