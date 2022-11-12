#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <mqueue.h>
#include <sys/fcntl.h>

const int MAX_MSG = 10;
const int MAX_SIZE = 1024;
const char *mqName = "/queue";

int main(void){

    struct mq_attr attr;                
        /*respectively retrieve and modify attributes of the message
        queue referred to by the message queue descriptor mqdes*/
    attr.mq_maxmsg = MAX_MSG;
    attr.mq_msgsize = MAX_SIZE; 
             
        /*The  mq_maxmsg  and  mq_msgsize  fields  are  set  when  the  message  queue is created by
        mq_open(3).  The mq_maxmsg field is an upper limit on the number of messages that  may  be
        placed  on the queue using mq_send(3).  The mq_msgsize field is an upper limit on the size
        of messages that may be placed on the queue.  Both of  these  fields  must  have  a  value
        greater than zero. https://manpages.ubuntu.com/manpages/bionic/man3/mq_getattr.3.html */
           
    pid_t pid = fork();

    if (pid == 0){
        char file[MAX_SIZE];
        FILE *fp;
        fp = fopen("varfinatext.txt", "r");
        fgets(file, MAX_SIZE, fp);

        mqd_t mqd = mq_open(mqName,  O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP, &attr);
        /* The <mqueue.h> header defines the mqd_t type, which is used for message queue descriptors.
        The mq_open() function establishes the connection between a process and a message queue with a message queue descriptor.
        It creates a open message queue description that refers to the message queue, and a message queue descriptor that refers to that open message queue description.
        O_CREAT, This option is used to create a message queue, and it requires two additional arguments: mode, which is of type mode_t, and attr, which is a pointer to a mq_attr structure. 
        If the pathname, name, has already been used to create a message queue that still exists, then this flag has no effect, except as noted under O_EXCL. Otherwise, a message queue is created without any messages in it.
        O_RDWR Open the queue for both receiving and sending messages. The process can use any of the functions allowed for O_RDONLY and O_WRONLY.
        A message queue may be open multiple times in the same or different processes for sending messages.
        https://pubs.opengroup.org/onlinepubs/7908799/xsh/mq_open.html
        S_ olika premissions
        */

        mq_send(mqd, file, strlen(file), 0);
        mq_close(mqd);
    } else{
        wait(NULL);
        char file[MAX_SIZE];
        mqd_t mq = mq_open(mqName, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP, &attr);
        mq_receive(mq, file, MAX_SIZE, NULL);

        mq_unlink(mqName);
        mq_close(mq);
         

        /* https://www.tutorialspoint.com/c_standard_library/c_function_strtok.htm
        */
        char *token = strtok(file, " ");
        int x = 0;
        while (token != NULL)
        {
            x++;
            token = strtok(NULL, " ");
        }
        printf("%d\n", x);        
    }


}