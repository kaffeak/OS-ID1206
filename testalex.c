#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <mqueue.h>

const int MAX_MSG = 10;
const int MAX_SIZE = 1024;
const char QUENAME = "/queue";

int main(void){
	char msg_fd[MAX_SIZE];
    struct mq_attr attr;                
        /*respectively retrieve and modify attributes of the message
        queue referred to by the message queue descriptor mqdes*/
int status = mq_unlink(QUENAME);
if (status < 0)
{
	perror("Error when unlinking queue");
}
	
    attr.mq_maxmsg = MAX_MSG;
    attr.mq_msgsize = MAX_SIZE;          
        /*The  mq_maxmsg  and  mq_msgsize  fields  are  set  when  the  message  queue is created by
        mq_open(3).  The mq_maxmsg field is an upper limit on the number of messages that  may  be
        placed  on the queue using mq_send(3).  The mq_msgsize field is an upper limit on the size
        of messages that may be placed on the queue.  Both of  these  fields  must  have  a  value
        greater than zero. https://manpages.ubuntu.com/manpages/bionic/man3/mq_getattr.3.html */
    mqd_t mqd = mq_open(QUENAME,  O_RDWR | O_CREAT,(S_IRUSR | S_IWUSR), &attr);              
		if (mqd == -1)
		{
			perror("Error when creating the queue");
			exit(0);
		}
		
    pid_t pid = fork();

    if (pid == 0){ //child process

		mqd = mq_open(QUENAME,  O_RDWR);  
		if (mqd == -1)
		{
			perror("Error when opening child queue");
			exit(0);
		}
		FILE *fd;

		fd = fopen("context.txt", "r");    
		if (fd == NULL)
		{
			perror("Error when opening file");
			exit(-1);
		}
		while (fread(&msg_fd, sizeof(char), MAX_SIZE, fd))
		{
			if (mq_send(mqd, msg_fd, strlen(msg_fd)-1, 0) == -1)
			{
				perror("Error when trying to send message");
				exit(-1);
			}
			else
				memset(msg_fd, 0, sizeof msg_fd);
		}
		fclose(fd);
		mq_close(mqd);
    } else if (pid > 0) //parent
	{
		wait(NULL);
        char buffer[MAX_SIZE];
		mqd = mq_open(QUENAME, O_RDWR);
		if (mqd == -1)
		{
			perror("Error when opening parent queue");
			exit(0);
		}
		mq_receive(mqd, msg_fd, sizeof msg_fd, 0);
		mq_close(mqd);
		mq_unlink(QUENAME);
		char *token = strtok(msg_fd, "");
		int i = 0;
		while (token != NULL)
		{
			i++;
			token = strtok(NULL, " ");
		}
		printf("%d\n", i);
	}


}