Circular Doubly Linked List
===========================
(c) Brian Lynch September, 2015
-------------------------------

This software was written for educational purposes. I wrote/hacked this 
code while teaching myself how a circular doubly linked list and self implemented
iterators work. There may be errors. Please let me know if you encounter
any. This code is most likely not STL compliant -- meaning that it is
unlikely to work with the STL <algorithm> header routines.

You may need to install cmake. To install cmake, execute the command

-"sudo apt-get install cmake"

This software works on Ubuntu 12.04 & 14.04 and has not been verified on
other operating systems.

   possible cmake options are (will put the executables in build/bin):
   
      -"mkdir build"
      -"cd build"
      -"cmake -DCMAKE_BUILD_TYPE=Debug ../"
      -"make"
      -"cd ../"
      
   Now you have done and out of source build, which leaves the original
   source directories clean. Example calling command:
   
      -"build/bin/cdlList_test"

To-Do:
######

* Work on STL <algorithm> compliance
* Doxygen documentation
