#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

using namespace std;

#define BUFFER_SIZE 5
#define TOTAL_ITEMS 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0;
int producedCount = 0;
int consumedCount = 0;

sem_t emptySlots; // how many empty slots
sem_t fullSlots;  // how many full slots
sem_t accessSem;  // acts as mutex for critical section

void* producer(void* arg) {
    int id = *((int*)arg);
    while (true) {
        sem_wait(&accessSem);
        if (producedCount >= TOTAL_ITEMS) {
            sem_post(&accessSem);
            break;
        }
        int item = producedCount + 1;
        producedCount++;
        sem_post(&accessSem);

        sem_wait(&emptySlots); // wait for empty buffer slot
        sem_wait(&accessSem);  // critical section

        buffer[in] = item;
        cout << "Producer " << id << " produced: " << item << " at index " << in << endl;
        in = (in + 1) % BUFFER_SIZE;

        sem_post(&accessSem);  // release critical section
        sem_post(&fullSlots);  // one more full slot

        sleep(1);
    }
    return nullptr;
}

void* consumer(void* arg) {
    int id = *((int*)arg);
    while (true) {
        sem_wait(&accessSem);
        if (consumedCount >= TOTAL_ITEMS) {
            sem_post(&accessSem);
            break;
        }
        sem_post(&accessSem);

        sem_wait(&fullSlots); // wait for full slot
        sem_wait(&accessSem); // critical section

        if (consumedCount >= TOTAL_ITEMS) {
            sem_post(&accessSem);
            sem_post(&fullSlots);
            break;
        }

        int item = buffer[out];
        cout << "\tConsumer " << id << " consumed: " << item << " from index " << out << endl;
        out = (out + 1) % BUFFER_SIZE;
        consumedCount++;

        sem_post(&accessSem); // release critical section
        sem_post(&emptySlots); // one more empty slot

        sleep(2);
    }
    return nullptr;
}

int main() {
    pthread_t producerThread, consumerThread;
    int prod_id = 1, cons_id = 1;

    sem_init(&emptySlots, 0, BUFFER_SIZE);
    sem_init(&fullSlots, 0, 0);
    sem_init(&accessSem, 0, 1); // acts like a mutex

    pthread_create(&producerThread, nullptr, producer, &prod_id);
    pthread_create(&consumerThread, nullptr, consumer, &cons_id);

    pthread_join(producerThread, nullptr);
    pthread_join(consumerThread, nullptr);

    sem_destroy(&emptySlots);
    sem_destroy(&fullSlots);
    sem_destroy(&accessSem);

    cout << "\nAll items produced and consumed using only semaphores.\n";
    return 0;
}
