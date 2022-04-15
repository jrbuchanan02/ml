# ML

ML, which stands for "Machine Learning" is my angered response to Python's lack
of portability. It started something like this: I wanted to run these awesome
StyleGANx (where x is a number) neural networks because I find the research
into deep learning for image manipulation amazing (whenever it's done for a
productive cause, like imagining a person say, with a beard or as another
gender). However, to run these networks, each one requires this **very specific**
python 3.x install with Anaconda 3 and this **one specific** version of
Tensorflow. That's infuriating as, I'm sure these researchers would agree,
this research deserves to run anywhere.

In response: make my own library. While that's a daunting task for anyone, I
feel like I'm making progress with ML. Even if ML does not turn out to be a
powerful deep-learning tool, ML already knows how to manipulate matrices:
capable of performing scalar multiplication, vector multiplication, matrix
multiplication, and reducing to RREF form. ML also intends to be portable and
can run either as a source library (which requires running from a C++ program)
or as a shared library (which can run from anything which can bind to C
functions).

## Requirements

ML currently only requires C++ 11 or higher.

## Possible Issues

Because of how computers deal with matrices, A * A<sup>-1</sup> may not equal
the identity matrix. However, the result should be agonizingly close to the
identity matrix, for example, in the unittest for finding the inverses of
matrices, ml finds the inverse of the 3x3 matrix \[1, 2, 3; 4, 5, 6; 7, 8, 8 \]
which is \[-8/3, 8/3, -1; 10/3, -13/3, 2; -1, 2, -1\]. ML gets the correct
matrix within the rounding for the standard C++ double to string conversion.
However, multiplying these two matrices in double precision yields
\[1, -8.88178 \* 10<sup>-16</sup>, 0; 0, 1, 0; -8.88178 \* 10<sup>-16</sup>,
2 \* -8.88178 \* 10<sup>-16</sup>, 1\] instead of the identity matrix. However,
considering how small anything with the exponent 10<sup>-16</sup> or
10<sup>-15</sup> is relative to 1, this result is close enough to declare that
the matrix lost some precision due to not being able to store intermediate
values exactly while calculating. Most likely, representing the numbers as
fractions would fix this issue (and also significantly complicate and slow down
the library). This floating point precision issue exists in ***all***
computer calculations unless they operate with arbitrary size numbers or
use string manipulation to do their bidding. *As a result, this is not an issue*.
