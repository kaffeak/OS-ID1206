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
    attr.mq_maxmsg = MAX_MSG;
    attr.mq_msgsize = MAX_SIZE; 

    pid_t pid = fork();

    if (pid == 0){
        char file[MAX_SIZE];
        FILE *fp;
        fp = fopen("varfinatext.txt", "r");
        fgets(file, MAX_SIZE, fp);

        mqd_t mqd = mq_open(mqName,  O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP, &attr);
    
        mq_send(mqd, file, strlen(file), 0);
        mq_close(mqd);
    } else{
        wait(NULL);
        char file[MAX_SIZE];
        mqd_t mq = mq_open(mqName, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP, &attr);
        mq_receive(mq, file, MAX_SIZE, NULL);

        mq_unlink(mqName);
        mq_close(mq);
         
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