/* Group Info:
 *   abpatwar Aditya B Patwardhan
 *   smnaik Sanskruti M Naik
 *   slbist Saurabh L Bist
*/
 
About the Library:
-----------------
The library provides APIs defined in the mythread.h file.
The Thread library is in compliance with the POSIX standard.
The library uses clone() function to create light-weight processes. 
The number of active threads is controlled with the use of FUTEX(Fast-User-Level-Mutex).


How to Build:
------------
Our Makefile provides a bunch of targets; each one builds a particular part 
of the project.
Refer to the following commands for building ->

Compiling:
     $ make
# This is equivalent to "make all".
# It compiles all the code files, creates the corresponding object files and builds 
# the library file "mythread.a". It also builds the test.c file - a sample
# test program provided - which tests out all the mythread_ functions.
		     
Library Compilation:
     $ make lib

Cleaning:
     $ make clean

Test file:
     $ make test


