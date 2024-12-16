#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 4
#define NUM_INCREMENTS 100000

int counter = 0; // Shared variable

void *increment(void *arg) {
    for (int i = 0; i < NUM_INCREMENTS; i++) {
        counter++; // This operation is not thread-safe
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, increment, NULL) != 0) {
            perror("pthread_create failed");
            return 1;
        }
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join failed");
            return 1;
        }
    }

    printf("Final counter value: %d\n", counter);
    printf("Expected counter value: %d\n", NUM_THREADS * NUM_INCREMENTS);

    return 0;
}