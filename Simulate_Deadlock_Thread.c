#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex1;
pthread_mutex_t mutex2;

void* threadFunc1(void* arg) {
    pthread_mutex_lock(&mutex1);
    printf("Thread 1: locked mutex1\n");

    // Simulate some work
    sleep(1);

    printf("Thread 1: trying to lock mutex2\n");
    pthread_mutex_lock(&mutex2);  // Will deadlock here
    printf("Thread 1: locked mutex2\n");

    pthread_mutex_unlock(&mutex2);
    pthread_mutex_unlock(&mutex1);

    return NULL;
}

void* threadFunc2(void* arg) {
    pthread_mutex_lock(&mutex2);
    printf("Thread 2: locked mutex2\n");

    // Simulate some work
    sleep(1);

    printf("Thread 2: trying to lock mutex1\n");
    pthread_mutex_lock(&mutex1);  // Will deadlock here
    printf("Thread 2: locked mutex1\n");

    pthread_mutex_unlock(&mutex1);
    pthread_mutex_unlock(&mutex2);

    return NULL;
}

int main() {
    pthread_t t1, t2;

    // Initialize the mutexes
    pthread_mutex_init(&mutex1, NULL);
    pthread_mutex_init(&mutex2, NULL);

    // Create the threads
    pthread_create(&t1, NULL, threadFunc1, NULL);
    pthread_create(&t2, NULL, threadFunc2, NULL);

    // Wait for both threads (won't happen due to deadlock)
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // Cleanup
    pthread_mutex_destroy(&mutex1);
    pthread_mutex_destroy(&mutex2);

    printf("Main: This line will never be reached due to deadlock.\n");
    return 0;
}
