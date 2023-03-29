#include <pthread.h>
#include "locktests.h"

int x = 0;

// shared lock
pthread_mutex_t *lock;

int lockfun()
{
    printf("Trying out locks\n");

    lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(lock, NULL); // sets it to "unlocked" state
    printf("I have initialized the lock to unlocked\n");

    // Creating threads
    pthread_t t1, t2;
    pthread_create(&t1, NULL, doStuff, NULL);
    pthread_create(&t2, NULL, doStuff, NULL);

    // (joining threads)
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Value of x is %d\n", x);
    pthread_mutex_destroy(lock);
    return 0;
}

void *doStuff(void *args)
{
    int i;
    for (i = 0; i < 100000; i++)
    {
        pthread_mutex_lock(lock); // try to acquire the lock
        /////////////////////////////////////////
        // << critical section >>
        x++;
        /////////////////////////////////////////
        pthread_mutex_unlock(lock); // release
    }
    return NULL;
}
