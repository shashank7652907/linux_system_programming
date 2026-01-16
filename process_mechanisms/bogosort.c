#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>

// Check if array is sorted
bool isSorted(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
}

// Shuffle the array randomly
void shuffle(int arr[], int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        // Swap arr[i] and arr[j]
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

// Print the array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Bogosort algorithm
void bogosort(int arr[], int n) {
    int attempts = 0;
    
    while (!isSorted(arr, n)) {
        shuffle(arr, n);
        attempts++;
    }
    
    printf("Sorted in %d attempts (PID: %d): ", attempts, getpid());
}

int main(int argc, char* argv[]) {
    
    if (argc < 2) {
        printf("Usage: %s <number1> <number2> ... <numberN>\n", argv[0]);
        printf("Example: %s 4 3 5 1 2\n", argv[0]);
        return 1;
    }
    
    int n = argc - 1;
    int* arr = (int*)malloc(n * sizeof(int));
    
    if (arr == NULL) {
        perror("Memory allocation failed");
        return 1;
    }
    
    // Convert command line arguments to integers
    for (int i = 0; i < n; i++) {
        arr[i] = atoi(argv[i + 1]);
    }
    
    // Seed random number generator
    srand(time(NULL));
    
    // Perform bogosort
    bogosort(arr, n);
    
    // Print sorted array
    printArray(arr, n);
    
    free(arr);
    
    return 0;
}