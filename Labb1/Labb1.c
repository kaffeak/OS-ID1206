#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(void){
    int fd[2];          //fileDiscription 
    pipe(fd);
    pid_t pid = fork();
    char *arg2 = "/";
   	char *programName = "ls";
    char *arg3 = "wc";
    char *arg4 = "-l";

		if (pid == 0)           //om fork() är 0 så är vi i child
		{
            dup2(fd[1], STDOUT_FILENO); //skickar in i pipe fd[1], skickar ut stdout_fileno
            close(fd[1]); /* fd[0] will be the fd(file descriptor) for the 
                            read end of pipe.
                            fd[1] will be the fd for the write end of pipe.
                            Returns : 0 on Success.
                            -1 on error.*/
            close(fd[0]);
            execlp(programName, programName, arg2, NULL);
            exit(1);
		} else{ 
            wait(NULL); //När vi returnar från child kommer det att börja skrivas. (Dvs kör först parent till wait sen direkt child sen fortsätta på parent)
            dup2(fd[0], STDIN_FILENO); //Tar emot
                      //Duplicatear in det i child till parent och vill skriva ut 
            close(fd[0]);
            close(fd[1]);
            execlp(arg3, arg3, arg4, (char*) NULL);
            exit(2);
        }
	return 0;
}