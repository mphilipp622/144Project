Mark Philipp
CSCI 144
11/22/18

----------------------------------------------
Compilation Requirements
----------------------------------------------

This program should be run in Cygwin64 on Windows. Cygwin will need to have G++ compiler and the GNU Make packages installed. This program should also be able to run in a Unix environment as long as G++ and GNU Make are installed, however, I have only tested it in Cygwin64.

This Stackoverflow post describes how to get the make package installed in a cygwin environment if it is not installed already: https://stackoverflow.com/questions/17710209/how-to-run-make-from-cygwin-environment

Additionally, C++11 must be available in the Cygwin environment. This should be standard with the G++ installation, to my knowledge.

If you cannot get make to install or work properly, instructions will be provided for compiling with only G++

----------------------------------------------
How to Compile and Run Using Script
----------------------------------------------

To compile and run the program, you can use the CompileAndRun.sh file by executing the following command within the root directory of the project:

./CompileAndRun.sh TP TC

where TP is the max time interval for producers and TC is the max time interval for consumers. TP and TC must be non-negative. The script will run a make command to compile the program and then execute it with the arguments you passed to the shell script.

----------------------------------------------
How to Compile and Run Without Using Script
----------------------------------------------

If the script fails for any reason, you can compile the project using G++ by itself.

First, make sure your cygwin terminal is navigated to the root of the project.

Run The following command:

g++ ./headers/BlockingQueue.h ./headers/Consumer.h ./headers/Producer.h ./headers/Worker.h ./source/BlockingQueue.cpp ./source/Consumer.cpp ./source/Producer.cpp ./source/Worker.cpp main.cpp -std=c++11 -w

Once it's done compiling, you can run the program using this command:

./a.exe TP TC

where TP is the max time interval for producers and TC is the max time interval for consumers. TP and TC must be non-negative

----------------------------------------------
Change Queue Size
----------------------------------------------

To change the size of the queue, open the "source" folder and open "BlockingQueue.cpp". At the top of the file, you'll see a line

const int BlockingQueue::maxItems = 25;

Change the value of this variable and then run the CompileAndRun.sh script to re-compile and run using the new buffer size.

----------------------------------------------
Where to Find the Code
----------------------------------------------

All header files can be found in the "headers" folder. All cpp files can be found in the "source" folder.