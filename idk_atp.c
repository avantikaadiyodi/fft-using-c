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
        double angle = -2 * M_PI * k / n;
        Complex w = {cos(angle), sin(angle)};  // twiddle factor

        Complex even_k = even_x[k];
        Complex odd_k = odd_x[k];

        Complex twiddle_odd;
        twiddle_odd.real = w.real * odd_k.real - w.imag * odd_k.imag;
        twiddle_odd.imag = w.real * odd_k.imag + w.imag * odd_k.real;

        x[k].real = even_k.real + twiddle_odd.real;
        x[k].imag = even_k.imag + twiddle_odd.imag;

        x[k + n/2].real = even_k.real - twiddle_odd.real;
        x[k + n/2].imag = even_k.imag - twiddle_odd.imag;
    }

    free(even_x);
    free(odd_x);
}


int main() {
    int n = 8;
    Complex *x = malloc(n * sizeof(Complex));

    double x_real[] = {1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0};
    double x_imag[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

    for (int i = 0; i < n; i++) {
        x[i].real = x_real[i];
        x[i].imag = x_imag[i];
    }

    n_point_fft(x, n);

    printf("FFT output:\n");
    for (int i = 0; i < n; i++) {
        printf("%.2f + %.2fi\n", x[i].real, x[i].imag);
    }

    free(x);
    return 0;
}