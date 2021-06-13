#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>
#include <pthread.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

#define PATH "/mnt/c/Users/owners/Hw2/key"

typedef struct __counter_t{
        int value;
        key_t key;
        union semun arg;
        struct sembuf s;
} counter_t;

unsigned int loop_cnt;
counter_t counter;

void init(counter_t *c) {
        int semid;
        c->value = 0;
        key_t key;
        key = ftok(PATH, 'z');
        semid = semget(key, 1, 0600 | IPC_CREAT);
}

void increment(counter_t *c){

        int semid;
        struct sembuf s;
        s.sem_num = 0;
        s.sem_op = -1;
        s.sem_flg = 0;
        semop(semid, &s, 1);

        c->value++;

        s.sem_num = 0;
        s.sem_op = 1;
        s.sem_flg = 0;
        semop(semid, &s, 1);

}

void decrement(counter_t *c){

        int semid;
        struct sembuf s;
        s.sem_num = 0;
        s.sem_op = -1;
        s.sem_flg = 0;
        semop(semid, &s, 1);

        c -> value--;

        s.sem_num = 0;
        s.sem_op = 1;
        s.sem_flg = 0;
        semop(semid, &s, 1);

}

int get(counter_t *c){
        int semid;
        struct sembuf s;
        s.sem_num = 0;
        s.sem_op = -1;
        s.sem_flg = 0;
        semop(semid, &s, 1);

        int rc = c->value;
        s.sem_num = 0;
        s.sem_op = 1;
        s.sem_flg = 0;
        semop(semid, &s, 1);
        return rc;
}

void *mythread(void *arg)
{
        char *letter = arg;
        int i;

        printf("%s: begin\n", letter);
        for(i=0;i<loop_cnt; i++){
                increment(&counter);
        }
        printf("%s: done\n", letter);
        return NULL;
}

int main(int argc, char *argv[])
{
    key_t key;
    int semid;
    union semun arg;

    key = ftok(PATH, 'z');
    if (key < 0) {
        perror(argv[0]);
        exit(1);
    }
    semid = semget(key, 1, 0600 | IPC_CREAT);
    if (semid < 0) {
        perror(argv[0]);
        exit(1);
    }

    printf("semid = %d\n", semid);

    arg.val = 1;
    semctl(semid, 0, SETVAL, arg);

    loop_cnt = atoi(argv[1]);

    init(&counter);

    pthread_t p1, p2;
    printf("main: begin [counter = %d]\n", get(&counter));
    pthread_create(&p1, NULL, mythread, "A");
    pthread_create(&p2, NULL, mythread, "B");
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    printf("main: done [counter: %d] [should be: %d]\n", get(&counter), loop_cnt * 2);
    return 0;
}
                               
                               
