#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void){
    int fd[2];    
    pipe(fd);
    pid_t pid = fork();
    char *arg2 = "/";
   	char *programName = "ls";
    char *arg3 = "wc";
    char *arg4 = "-l";

		if (pid == 0)         
		{
            dup2(fd[1], STDOUT_FILENO); 
            close(fd[1]); 
            close(fd[0]);
            execlp(programName, programName, arg2, NULL);
            exit(1);
		} else{ 
            wait(NULL);
            dup2(fd[0], STDIN_FILENO); 
            close(fd[0]);
            close(fd[1]);
            execlp(arg3, arg3, arg4, (char*) NULL);
            exit(2);
        }
	return 0;
}