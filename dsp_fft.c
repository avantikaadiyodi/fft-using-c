// code doesnt work. either logic is wrong or it's implemented wrong. need to fix in future

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#define M_PI 3.14159265358979323846

// takes input sequence from text files and performs n-point FFT and prints output

typedef struct {
    double real;
    double imag;
} Complex;

void n_point_fft(Complex *x, int n) {
    if (n <=1 ) {return;}

    int i = 0, j = 0, k = 0, W = 0;

    Complex *column_matrix = malloc(n/2 * sizeof(Complex));
    Complex *row_matrix = malloc(n/2 * sizeof(Complex));
    
    Complex *real_W_matrix = malloc(n/2 * sizeof(Complex));
    Complex *imag_W_matrix = malloc(n/2 * sizeof(Complex));
    
    Complex *real_output_matrix = malloc(n/2 * sizeof(Complex));
    Complex *imag_output_matrix = malloc(n/2 * sizeof(Complex));
    
    Complex *x_matrix = malloc(n/2 * sizeof(Complex));

    i = 0; j = 0;
    // making column matrix
    while (i < n/2) {
        while (j < n/2) {
            column_matrix[j][i] = x[j];
            j++; // next row
        }
        i++; // next column
    }
    // need to free memory

    if (n == 1) { return column_matrix; }
   
    for (int k = 0; k < n/2; k++){
        x_matrix = n_point_fft(column_matrix[k], (n/2));
        real_W_matrix, imag_W_matrix = make_twiddle_factor_matrix(n/2, n/2, n);
        real_output_matrix, imag_output_matrix = dft_multiply(x_matrix, real_W_matrix, imag_W_matrix, n);
    }

    return real_output_matrix, imag_output_matrix;
}

double _Complex** make_twiddle_factor_matrix(int k, int n, int N) { // do we want this to return a pointer or like rn
    float W_real, W_imag; 
    // will this work?
    double angle = 0;
   
    double _Complex **real_twiddle_factor_matrix = (double _Complex **)malloc(k * sizeof(double _Complex *));
    for (int i = 0; i < k; i++) { real_twiddle_factor_matrix[i] = (double _Complex *)malloc(n * sizeof(double _Complex)); }
    
    double _Complex **imag_twiddle_factor_matrix = (double _Complex **)malloc(k * sizeof(double _Complex *));
    for (int i = 0; i < k; i++) { imag_twiddle_factor_matrix[i] = (double _Complex *)malloc(n * sizeof(double _Complex)); }
   
    
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < n; j++){
            angle = (-2.0 * M_PI * (i*j)) / N;
            W_real = cos(angle);
            real_twiddle_factor_matrix[i][j] = W_real;
            W_imag = -1 * sin(angle);
            imag_twiddle_factor_matrix[i][j] = W_imag;
        }
    }

    return real_twiddle_factor_matrix, imag_twiddle_factor_matrix;
}

double _Complex** dft_multiply(double _Complex** x_matrix, double _Complex** real_W_matrix,  double _Complex** imag_W_matrix, int n) { // do we want this to return a matrix or like rn
    double _Complex** real_dft_matrix = (double _Complex**)malloc(n * sizeof(double _Complex*));
    for (int i = 0; i < n; i++) { real_dft_matrix[i] = (double _Complex*)malloc(n * sizeof(double _Complex)); }

    double _Complex** imag_dft_matrix = (double _Complex**)malloc(n * sizeof(double _Complex*));
    for (int i = 0; i < n; i++) { imag_dft_matrix[i] = (double _Complex*)malloc(n * sizeof(double _Complex)); }
    
    // matrix multiplication
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            real_dft_matrix[i][j] = x_matrix[i][j] * real_W_matrix[i][j];
            imag_dft_matrix[i][j] = x_matrix[i][j] * imag_W_matrix[i][j];
        }
    }
    
    return real_dft_matrix, imag_dft_matrix;
}




void display_output(int real_matrix, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d", sequence[i]);
        if (i < n - 1) {
            printf(" ");
        }
    }
    printf("\n");
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