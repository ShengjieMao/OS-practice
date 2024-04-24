#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARRAY_SIZE 10 // may change later for other instance

int unsortedArray[ARRAY_SIZE] = {7, 2, 1, 6, 8, 5, 3, 4, 10, 9}; // may change later for other instance
int sortedArray[ARRAY_SIZE];


typedef struct {
    int start; 
} SortParams;


void* sort(void* param) {
    SortParams* params = (SortParams*)param;

    int start = params->start;
    int end = start + ARRAY_SIZE / 2;

    for (int i = start; i < end - 1; ++i) {
        for (int j = start; j < end - 1 - (i - start); ++j) {
            if (unsortedArray[j] > unsortedArray[j + 1]) {
                int temp = unsortedArray[j];

                unsortedArray[j] = unsortedArray[j + 1];
                unsortedArray[j + 1] = temp;
            }
        }
    }

    pthread_exit(0);
}

void merge() {
    int left = 0;
    int right = ARRAY_SIZE / 2;
    int index = 0;

    while (left < ARRAY_SIZE / 2 && right < ARRAY_SIZE) {
        if (unsortedArray[left] < unsortedArray[right]) {
            sortedArray[index++] = unsortedArray[left++];
        } else {
            sortedArray[index++] = unsortedArray[right++];
        }
    }

    while (left < ARRAY_SIZE / 2) {
        sortedArray[index++] = unsortedArray[left++];
    }

    while (right < ARRAY_SIZE) {
        sortedArray[index++] = unsortedArray[right++];
    }
}

int main() {
    pthread_t threads[2];
    SortParams params1 = {0};
    SortParams params2 = {ARRAY_SIZE / 2};
    
    pthread_create(&threads[0], NULL, sort, &params1);
    pthread_create(&threads[1], NULL, sort, &params2);

    for (int i = 0; i < 2; ++i) {
        pthread_join(threads[i], NULL);
    }

    merge();

    printf("Sorted Array: ");
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        printf("%d ", sortedArray[i]);
    }
    printf("\n");

    return 0;
}
