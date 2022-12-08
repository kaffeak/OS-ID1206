#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int buffer = 0;
pthread_mutex_t mutex;
void *thread_func() {
    int *mod = malloc(sizeof(int));
    *mod = 0;
    while (1)
    {
        pthread_mutex_lock(&mutex);
        if (buffer < 15)
        {
            pid_t pid = getpid();
            long tid = (long) pthread_self();
            printf("TID: %ld PID: %d Buffer: %d\n", tid, pid, buffer++);
            (*mod)++;
            pthread_mutex_unlock(&mutex);
        }
        else
        {
            pthread_mutex_unlock(&mutex);
            return (void *)mod;
        }
    }
}

int main() {
    pthread_t t[3];
    pthread_mutex_init(&mutex, NULL);
    for (int i = 0; i < 3; i++)
    {
        pthread_create(&t[i], NULL, thread_func, NULL);
    }
        
    for (int i = 0, *mod; i < 3; i++)
        {
        pthread_join(t[i], (void **)&mod);
        printf("TID %ld worked on the buffer %d times\n", (long)t[i], *mod);
        }
    return 0;
}