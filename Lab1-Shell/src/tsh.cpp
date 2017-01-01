#include "tsh.h"

using namespace std;

void simple_shell::parse_command(char *cmd, char **cmdTokens){
	// TODO: tokenize the command string into arguments
	char *p = strtok(cmd, " \n");
	int x = 0;
	while(x < 20){
    	cmdTokens[x] = p;
    	x++;
    	p = strtok(NULL, " \n");
	}
}

void simple_shell::exec_command(char **argv){
	// TODO: fork a child process to execute the command. 
	// 		 parent process should wait for the child process to complete and reap it
    int rc = fork();
    if(rc < 0){
         // fork failed; exit
        printf("fork failed\n");
        exit(1);
    }else if(rc == 0){
        // child (new process)
        execvp(*argv, argv);
        exit(0);
    }else{
        // parent goes down this path (original process)
        wait(NULL);
    }
}

bool simple_shell::isQuit(char *cmd){
	// TODO: check for the command "quit" that terminates the shell
	if(strcmp(cmd,"quit\n") == 0 || strcmp(cmd, "quit") == 0)
		return true;
	return false;
}