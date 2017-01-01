The goal of this lab is to implement a simple shell in C++.
This requires you to use system calls directly in your code.
In class, we touched upon how a few system calls, (notably fork
and exec) can be used to implement a command shell. In this
exercise, you will implement tsh (trivial shell), a simple shell.

Like a real shell, tsh will take as input the name of a program
as argument. The program can be the name of any executable in the
current directory where your shell program resides. The shell
should run the specified program with the arguments before prompting
for a new user command. The command "quit" should terminate your shell.

Here is a simple example:

elnux25$ ./tsh 
  tsh> add 2 3 // calls the add binary which should be present
  5 
  tsh> quit 
elnux25$