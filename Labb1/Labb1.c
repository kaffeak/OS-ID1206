#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(void){
		int fd[2];

		pipe(fd);

		if (fork() == 0)
		{
			close(fd[0]);
			char *binaryPath = "/bin";
			char *args[2] = {"ls", NULL};
			execl(binaryPath, binaryPath, args[0], args[1], NULL); 
			//write(fd[1], )
		}
	return 0;
}