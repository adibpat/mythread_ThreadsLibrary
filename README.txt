/* Single Author Info:
 *   smnaik Sanskruti M Naik
 * Group Info:
 *   abpatwar Aditya B Patwardhan
 *   smnaik Sanskruti M Naik
 *   slbist Saurabh L Bist
 */

How to Build:
------------
Our Makefile provides a bunch of targets; each one builds a particular part 
of the project.
Refer to the following commands for building ->

Compiling:
     $ make
# This is equivalent to "make all" and "make a5" which can also be alternatively used.
# It compiles all the code files, creates the corresponding object files and builds 
# the library file "libmythread.a". It also builds the mythread_test file - a sample
# test program provided - which tests out all the mythread_ functions.
		     
Library Compilation:
     $ make lib

Cleaning:
     $ make clean

Test file:
     $ make test


Display archive contents:
     $ ar t libmythread.a
