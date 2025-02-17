#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>
#define pi 3.14159265358979323846

typedef struct{
    double real;
    double imag;
} Complex;

void n_point_fft(Complex *sequence, int n) {
    if (n<=1) {return;}

    Complex column[512][512];

    for (int i = 0; i < n; i++) { 
        for (int j = 0; j < n; j++) {
            column[j][i] = sequence[i+j]; 
        }
    }
    for (int i = 0; i<n/2; i++) {
        n_point_fft(column[i], n/2);
    }
    
    for (int k = 0; k < n/2; k++) {
        double angle = -2 * pi * k/n;
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
}