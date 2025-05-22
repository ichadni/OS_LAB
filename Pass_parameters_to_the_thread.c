#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Define a struct to hold two integers
typedef struct {
    int a;
    int b;
} Numbers;

// Thread function that receives a pointer to a Numbers struct
void* threadFunction(void* arg) {
    Numbers* nums = (Numbers*)arg;  // Cast the void pointer to Numbers pointer

    int sum = nums->a + nums->b;
    printf("Thread: Sum of %d and %d is %d\n", nums->a, nums->b, sum);

    pthread_exit(NULL);
}

int main() {
    pthread_t thread;

    // Create and fill the struct
    Numbers* nums = malloc(sizeof(Numbers));
    nums->a = 10;
    nums->b = 20;

    // Create thread and pass the struct
    if (pthread_create(&thread, NULL, threadFunction, (void*)nums)) {
        fprintf(stderr, "Error creating thread\n");
        free(nums);
        return 1;
    }

    // Wait for the thread to complete
    if (pthread_join(thread, NULL)) {
        fprintf(stderr, "Error joining thread\n");
        free(nums);
        return 2;
    }

    // Free the allocated memory
    free(nums);

    printf("Main: Thread has finished.\n");
    return 0;
}
