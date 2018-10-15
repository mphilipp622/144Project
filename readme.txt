Mark Philipp
CSCI 144
10/13/18

This program should be run in Cygwin64 on Windows. Cygwin will need to have G++ compiler and the GNU Make packages installed. This program should also be able to run in a Unix environment as long as G++ and GNU Make are installed, however, I have only tested it in Cygwin64.

This stackoverflow post describes how to get the make package installed in a cygwin environment if it is not installed already: https://stackoverflow.com/questions/17710209/how-to-run-make-from-cygwin-environment

Additionally, C++11 must be available in the Cygwin environment. This should be standard with the G++ installation, to my knowledge.

To compile and run the program, you can use the CompileAndRun.sh file by executing the following command within the root directory of the project:

./CompileAndRun.sh TP TC

where TP is the max time interval for producers and TC is the max time interval for consumers. The script will run a make command to compile the program and then execute it with the arguments you passed to the shell script.