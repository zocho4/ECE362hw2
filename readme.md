Zoe Schmertzler
ilanaz@pdx.edu
ECE 362 HW2
1/31/20

Unfortunately I was not able to finish this assignment.
Here I will outline what I was able to do.

Twist:
------
This program had some functionality but had some weirdness I was not able to fix.
Right now it only runs some test code I was trying to use to fix the bug but I 
was not able to finish that.
I also couldn't get it to compile with the file permission bits specified in the
calls to open() so they are commented out.

Xor:
----
I was not able to write this program.
The pseudocode for the high level algorithm is in pseudocode.txt
Much of it is very similar to twist but with different input arguments.
I copied twist.c into xor.c with the intention of modifying it but was
not able to.


TX:
---
Since I did not finish twist or xor I wrote a version of tx that has the
intended function but carries it out for two programs that are not twist and xor.
In other words, I wrote two very simple programs called firstProg and secondProg
that involve file IO and tx creates a pipe from firstProg to secondProg.
 
My intention in this was to demonstrate that I do know how to use syscalls for 
file IO and I know how to create a pipe,
fork a process, exec a new program and pipe output from one program to input of 
another, even if all this is done on a small/simple scale only.

firstProg: Takes one character from stdin, adds 1 to the ascii code and writes it
            back to stdout. In tx, stdout will be replaced with the pipe. 


secondProg: Takes one character from stdin, adds 1 to the ascii code and writes it
            back to stdout. In tx, stdin will be replaced with the pipe.

When tx is run, the user must type and enter one ascii character onto the console.
The overall result will be a printed ascii character that has an ascii code of two
more than the original character.


Additional files:
-----------------
Makefile:
 - This is the makefile for the whole module.
 - There are targets for twist, xor and tx all named as such.
 - The target for tx is what I would have used if tx were written for twist 
    and xor
 - The target that should be used is "pipe", which has depency upon 
    firstProg and secondProg (it shouldn't actually make a difference 
    because they both run the same gcc command)
 - There is also an "all" target that runs all of them.

TestFileIN: file used for testing input to twist and xor (or firstProg/secondProg)

TestFileOUT: file used for testing output from twist and xor (or firstProg/secondProg)

Pseudocode.txt: algorithm outlining high level process for all three programs


