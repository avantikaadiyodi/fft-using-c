// C Program to return an array in C using Pointers
#include <stdio.h>
#include <stdlib.h>

// Function to create and return an array using dynamic
// memory allocation
int* createArray(int size)
{
    // Allocate memory for the array
    int* array = (int*)malloc(size * sizeof(int));

    // Check if memory allocation was successful
    if (array == NULL) {
        printf("Memory allocation failed!\n");
        exit(1); // Exit the program if allocation fails
    }

    // Initialize the array with example values
    for (int i = 0; i < size; i++) {
        array[i] = i * 2;
    }

    // Return the pointer to the allocated array
    return array;
}

int main()
{
    // Define the size of the array
    int size = 5;
    // Call the function to create the array and store the
    // returned pointer
    int* myArray = createArray(size);

    // Print the elements of the array
    printf("Array Elements: ");
    for (int i = 0; i < size; i++) {

        printf("%d ", myArray[i]);
    }
    printf("\n");

    // Free the allocated memory to avoid memory leaks
    free(myArray);

    return 0;
}
