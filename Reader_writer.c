#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex;      // Controls access to read_count
sem_t wrt;        // Controls write access
int read_count = 0;

void* writer(void* wno) {
    sem_wait(&wrt); // Wait for writing
    printf("Writer %d is writing...\n", *((int*)wno));
    sleep(1);
    printf("Writer %d has finished writing.\n", *((int*)wno));
    sem_post(&wrt); // Release write lock
    return NULL;
}

void* reader(void* rno) {
    sem_wait(&mutex);  // Lock to update read_count
    read_count++;
    if(read_count == 1)
        sem_wait(&wrt);  // First reader locks the writer
    sem_post(&mutex);  // Unlock after updating count

    printf("Reader %d is reading...\n", *((int*)rno));
    sleep(1);
    printf("Reader %d has finished reading.\n", *((int*)rno));

    sem_wait(&mutex);
    read_count--;
    if(read_count == 0)
        sem_post(&wrt); // Last reader releases writer lock
    sem_post(&mutex);
    return NULL;
}

int main() {
    pthread_t read[5], write[5];
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    int i;
    int a[5] = {1, 2, 3, 4, 5};

    // Create 5 reader and 5 writer threads
    for(i = 0; i < 5; i++) {
        pthread_create(&write[i], NULL, writer, &a[i]);
        pthread_create(&read[i], NULL, reader, &a[i]);
    }

    for(i = 0; i < 5; i++) {
        pthread_join(write[i], NULL);
        pthread_join(read[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&wrt);
    
    return 0;
}
