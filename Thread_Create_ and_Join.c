#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Function that will run in the thread
void* myThreadFunction(void* arg) {
    printf("Hello from the thread! Argument: %s\n", (char*)arg);
    pthread_exit(NULL);
}

int main() {
    pthread_t thread;
    const char* message = "chadni_sust";

    // Create the thread
    if (pthread_create(&thread, NULL, myThreadFunction, (void*)message)) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }

    // Wait for the thread to finish
    if (pthread_join(thread, NULL)) {
        fprintf(stderr, "Error joining thread\n");
        return 2;
    }

    printf("Thread has finished executing.\n");
    return 0;
}
