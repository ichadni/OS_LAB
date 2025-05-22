#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

#define BUFFER_SIZE 5
int buffer[BUFFER_SIZE];
int in = 0, out = 0;
int count = 0; // number of items in the buffer

pthread_mutex_t mutex;

void* producer(void* arg) {
    int item = 0;
    while (true) {
        item++;

        pthread_mutex_lock(&mutex);
        if (count < BUFFER_SIZE) {
            buffer[in] = item;
            cout << "Producer produced: " << item << " at index " << in << endl;
            in = (in + 1) % BUFFER_SIZE;
            count++;
        } else {
            cout << "Buffer full. Producer waiting..." << endl;
        }
        pthread_mutex_unlock(&mutex);

        sleep(1);
    }
    return nullptr;
}

void* consumer(void* arg) {
    while (true) {
        pthread_mutex_lock(&mutex);
        if (count > 0) {
            int item = buffer[out];
            cout << "\tConsumer consumed: " << item << " from index " << out << endl;
            out = (out + 1) % BUFFER_SIZE;
            count--;
        } else {
            cout << "\tBuffer empty. Consumer waiting..." << endl;
        }
        pthread_mutex_unlock(&mutex);

        sleep(2);
    }
    return nullptr;
}

int main() {
    pthread_t producerThread, consumerThread;

    pthread_mutex_init(&mutex, nullptr);

    pthread_create(&producerThread, nullptr, producer, nullptr);
    pthread_create(&consumerThread, nullptr, consumer, nullptr);

    pthread_join(producerThread, nullptr);
    pthread_join(consumerThread, nullptr);

    pthread_mutex_destroy(&mutex);
    return 0;
}
