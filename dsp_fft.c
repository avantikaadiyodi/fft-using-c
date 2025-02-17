#include <stdlib.h>
#include <stdio.h>

// takes input sequence from text files and performs n-point FFT and prints output

void display_output(int sequence[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d", sequence[i]);
        if (i < n - 1) {
            printf(" ");
        }
    }
    printf("\n");
}

int n_point_fft(int *sequence, int n) { 
    int l = n/2; // number of rows
    int m = n/2; // number of columns
    int p = n/2;
    int q = n/2;
    int i = 0, j = 0;

    int **twiddle_factor_matrix = (int **)malloc(l * sizeof(int *));
    for (int i = 0; i < l; i++) {
        twiddle_factor_matrix[i] = (int *)malloc(m * sizeof(int));
    }

    int **column_matrix = (int **)malloc(l * sizeof(int *));
    for (int i = 0; i < l; i++) {
        column_matrix[i] = (int *)malloc(m * sizeof(int));
    }

    int **row_matrix = (int **)malloc(l * sizeof(int *));
    for (int i = 0; i < l; i++) {
        row_matrix[i] = (int *)malloc(m * sizeof(int));
    }
    
    // making column matrix
    while (i < m) { // k is number of columns
        while (j < l) {
            column_matrix[j][i] = sequence[j];
            j++; // next row
        }
        i++; // next column
        // k++;
    }

    



    return 0;

}

int main() {
    int n = 0, i = 0, sequence_length = 0;
    
    FILE *file = fopen("E:\\avantika\\a_projects\\misc_projects\\sequence_in.txt", "r");
    if (file == NULL) { // to overcome file not found error
        printf("Error opening file.\n");
        return 1;
    }
    // to print contents of file
    // int value;
    // while (fscanf(file, "%d", &value) != EOF) {
    //     printf("%d \n", value);
    // }
    // rewind(file);

    printf("Enter N: ");
    scanf("%d", &n);

    if (n > 1024) {
        printf("N larger than 1024. Going to perform 1024-point FFT.");
        n = 1024;
    }
    
    if (n % 2 != 0)
    {
        printf("N not an even number. Rounding up to nearest even number.");
        n = n + 1;
    }
    
    int sequence[1024]; // max 1024-fft possible
    // int *sequence = (int *)malloc(n * sizeof(int));

    while (fscanf(file, "%d", &sequence[i]) != EOF) { // read contents and store to array
        i++;
    }
    sequence_length = i;

    fclose(file);

    n_point_fft(sequence, n); 
    return 0;
}








