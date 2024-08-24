
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define N 2
#define END 100000000

int counter;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *increment() {
    pthread_mutex_lock(&mutex);
    // for (int i = 0; i < __INT_MAX__ / N; i++) {
    for (int i = 0; i < END; i++) {
        counter++;
    }
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t thread[N];

    for (size_t i = 0; i < N; i++) {
        pthread_create(&thread[i], NULL, increment, NULL);
    }
    for (size_t i = 0; i < N; i++) {
        pthread_join(thread[i], NULL);
    }

    // printf("res - %d\tdiff - %d\n", counter, __INT_MAX__ - counter);
    // printf("res - %d\tdiff - %d\n", counter, (END * N) - counter);
    printf("res - %d\tdiff - %d\tpercentDiff - %.2f%%\n", counter,
           (END * N) - counter,
           ((double)((END * N) - counter) / counter) * 100);

    return EXIT_SUCCESS;
}
