#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#define M_PI 3.14159265358979323846

// define complex number structure
typedef struct {
    double real;
    double imag;
} Complex;

void n_point_fft(Complex *x, int n) {
    if (n <= 1) return;

    Complex *even_x = malloc(n/2 * sizeof(Complex));
    Complex *odd_x = malloc(n/2 * sizeof(Complex));

    for (int i = 0; i < n/2; i++) {
        even_x[i] = x[2 * i];
        odd_x[i] = x[2 * i + 1];
    }

    n_point_fft(even_x, n/2);
    n_point_fft(odd_x, n/2);

    for (int k = 0; k < n/2; k++) {
        double theta = -2 * M_PI * k/n;
        Complex w = {cos(theta), sin(theta)};  // twiddle factor

        Complex even_k = even_x[k]; 
        Complex odd_k = odd_x[k];
        
        /* only considering odd powers of twiddle factor 
        since even powers of twiddle factors are always 1 */
        Complex twiddle; 
        twiddle.real = w.real * odd_k.real - w.imag * odd_k.imag;
        twiddle.imag = w.real * odd_k.imag + w.imag * odd_k.real;

        x[k].real = even_k.real + twiddle.real;
        x[k].imag = even_k.imag + twiddle.imag;

        x[k + n/2].real = even_k.real - twiddle.real;
        x[k + n/2].imag = even_k.imag - twiddle.imag;
    }
    // free space used due to dynamic memory allocation
    free(even_x);
    free(odd_x);
}


int main() {
    int n;
    printf("Enter the N (must be a power of 2): ");
    scanf("%d", &n);
    
    Complex *x = malloc(n * sizeof(Complex));

    double x_real[] = {1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0};
    double x_imag[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    
    for (int i = 0; i < n; i++) {
        x[i].real = x_real[i];
        x[i].imag = x_imag[i];
    }

    printf("Input:\n");
     for (int i = 0; i < n; i++) {
        printf("%.2f + %.2fi\n", x[i].real, x[i].imag);
    }
    printf("\n");

    n_point_fft(x, n);

    printf("FFT output:\n");
    for (int i = 0; i < n; i++) {
        printf("%.2f + %.2fi\n", x[i].real, x[i].imag);
    }

    free(x);
    return 0;
}