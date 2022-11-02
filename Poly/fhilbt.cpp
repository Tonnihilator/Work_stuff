#include <stdio.h>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>
#include <math.h>
#include <string.h>
#include <string>

#include "fhilbt.h"


#define PI             3.141592653589793
#define TWOPI          6.283185307179586
#define ONE_ON_PI      0.3183098861837907
#define TWO_ON_PI      0.6366197723675814
#define FOUR_ON_PI     1.273239544735163
#define PI_ON_TWO      1.570796326794897
#define SQRT_PI        1.772453850905516
#define ONE_ON_SQRT_PI 0.5641895835477563
#define LOG_10         2.302585092994046

#ifndef FFT_UNIT_STRIDE
    #define FFT_UNIT_STRIDE 0
#endif

#ifndef L1_CACHE_BYTES
    #define L1_CACHE_BYTES  0x8000
#endif

#if (L1_CACHE_BYTES == 0)
    #define MEM_SMALL 0x8000
#else
    #define MEM_SMALL L1_CACHE_BYTES
#endif

namespace Hilbert_Transform
{
    static void ifft_dit_rec(double *z, unsigned long n, int nbranch);
    static void ifft_dit_iter(double *z, unsigned long n);
    static void ifft_dit_iter_seq(double *z, unsigned long n);
    static void fft_dif_iter_seq(double *z, unsigned long n);
    static void fft_dif_iter(double *z, unsigned long n);
    void ifft_dit(double *z, unsigned long n);
    void fft_dif(double *z, unsigned long n);


    void hilbert(double *z, unsigned long n)
    {
        double x;
        unsigned long i, n2;

        n2 = n << 1;

        fft_dif(z, n);

        for (i = 6; i < n2; i += 4)
        {
            z[i] = 0.;
            z[i+1] = 0.;
        }

        z[0] *= 0.5;
        z[1] *= 0.5;
        if (n > 1)
        {
            z[2] *= 0.5;
            z[3] *= 0.5;
        }

        ifft_dit(z, n);

        x = 2. / (double)n;
        for (i = 0; i < n2; ++i)
            z[i] *= x;
        return;
    }   /* hilbert() */


    static void fft_dif_rec(double *z, unsigned long n, int nbranch)
    {
        double a, b, c, s, t;
        unsigned long nh, kr;

        if (n == 1)
            return;
        if (n <= (unsigned long)(L1_CACHE_BYTES / (2 * sizeof(double))))
        {
            if (FFT_UNIT_STRIDE)
                fft_dif_iter_seq(z, n);
            else
                fft_dif_iter(z, n);
            return;
        }
        t = TWOPI / (double)n;
        a = sin(0.5 * t);
        a *= 2.0 * a;
        b = sin(t);
        c = 1.0;
        s = 0.0;
        for (kr = 0; kr < n; kr += 2)
        {
            double ur, ui, tmp;
            unsigned long ki, mr, mi;
            ki = kr + 1;
            mr = kr + n;
            mi = mr + 1;
            ur = z[kr];
            ui = z[ki];
            z[kr] = ur + z[mr];
            z[ki] = ui + z[mi];
            ur -= z[mr];
            ui -= z[mi];
            z[mr] = ur * c - ui * s;
            z[mi] = ur * s + ui * c;
            tmp = c;
            c -= a * c + b * s;
            s -= a * s - b * tmp;
        }
        nh = n >> 1;
        nbranch <<= 1;
        #if (_OPENMP >= 200203)
        #pragma omp parallel sections if (nbranch <= omp_get_max_threads()) num_threads(2)
        #endif
        {
            #if (_OPENMP >= 200203)
            #pragma omp section
            #endif
            fft_dif_rec(z, nh, nbranch);
            #if (_OPENMP >= 200203)
            #pragma omp section
            #endif
            fft_dif_rec(z + n, nh, nbranch);
        }
        return;
    }


    static void ifft_dit_iter(double *z, unsigned long n)
    {
        unsigned long i, n2;

        n2 = n << 1;
        for (i = 2; i <= n; i <<= 1)
        {
            double a, b, c, s, t;
            unsigned long i2, j;
            i2 = i << 1;
            t = -TWOPI / (double)i;
            a = sin(0.5 * t);
            a *= 2.0 * a;
            b = sin(t);
            c = 1.0;
            s = 0.0;
            for (j = 0; j < i; j += 2)
            {
                double tmp;
                unsigned long kr, kmax;
                kmax = n2 + j;
                for (kr = j; kr < kmax; kr += i2)
                {
                    double vr, vi;
                    unsigned long ki, mr, mi;
                    ki = kr + 1;
                    mr = kr + i;
                    mi = mr + 1;
                    vr = z[mr] * c - z[mi] * s;
                    vi = z[mr] * s + z[mi] * c;
                    z[mr] = z[kr] - vr;
                    z[mi] = z[ki] - vi;
                    z[kr] += vr;
                    z[ki] += vi;
                }
                tmp = c;
                c -= a * c + b * s;
                s -= a * s - b * tmp;
            }
        }
        return;
    }   /* ifft_dit_iter() */


    static void ifft_dit_iter_seq(double *z, unsigned long n)
    {
        unsigned long i, n2;

        n2 = n << 1;
        for (i = 2; i <= n; i <<= 1)
        {
            double a, b, t;
            unsigned long i2, k;
            i2 = i << 1;
            t = -TWOPI / (double)i;
            a = sin(0.5 * t);
            a *= 2.0 * a;
            b = sin(t);
            for (k = 0; k < n2; k += i2)
            {
                double c, s;
                unsigned long j;
                c = 1.0;
                s = 0.0;
                for (j = 0; j < i; j += 2)
                {
                    double vr, vi, tmp;
                    unsigned long kr, ki, mr, mi;
                    kr = k + j;
                    ki = kr + 1;
                    mr = kr + i;
                    mi = mr + 1;
                    vr = z[mr] * c - z[mi] * s;
                    vi = z[mr] * s + z[mi] * c;
                    z[mr] = z[kr] - vr;
                    z[mi] = z[ki] - vi;
                    z[kr] += vr;
                    z[ki] += vi;
                    tmp = c;
                    c -= a * c + b * s;
                    s -= a * s - b * tmp;
                }
            }
        }
        return;
    }   /* ifft_dit_iter_seq() */


    void ifft_dit(double *z, unsigned long n)
    {
        ifft_dit_rec(z, n, 1);
        return;
    }   /* ifft_dit() */


    void fft_dif(double *z, unsigned long n)
    {
        fft_dif_rec(z, n, 1);
        return;
    }   /* fft_dif() */


    static void ifft_dit_rec(double *z, unsigned long n, int nbranch)
    {
        double a, b, c, s, t;
        unsigned long  nh, kr;

        if (n == 1)
            return;
        if (n <= (unsigned long)(L1_CACHE_BYTES / (2 * sizeof(double))))
        {
            if (FFT_UNIT_STRIDE)
                ifft_dit_iter_seq(z, n);
            else
                ifft_dit_iter(z, n);
            return;
        }
        nh = n >> 1;
        nbranch <<= 1;
        #if (_OPENMP >= 200203)
        #pragma omp parallel sections if (nbranch <= omp_get_max_threads()) num_threads(2)
        #endif
        {
            #if (_OPENMP >= 200203)
            #pragma omp section
            #endif
            ifft_dit_rec(z, nh, nbranch);
            #if (_OPENMP >= 200203)
            #pragma omp section
            #endif
            ifft_dit_rec(z + n, nh, nbranch);
        }
        t = -TWOPI / (double)n;
        a = sin(0.5 * t);
        a *= 2.0 * a;
        b = sin(t);
        c = 1.0;
        s = 0.0;
        for (kr = 0; kr < n; kr += 2)
        {
            double vr, vi, tmp;
            unsigned long ki, mr, mi;
            ki = kr + 1;
            mr = kr + n;
            mi = mr + 1;
            vr = z[mr] * c - z[mi] * s;
            vi = z[mr] * s + z[mi] * c;
            z[mr] = z[kr] - vr;
            z[mi] = z[ki] - vi;
            z[kr] += vr;
            z[ki] += vi;
            tmp = c;
            c -= a * c + b * s;
            s -= a * s - b * tmp;
        }
        return;
    }   /* ifft_dit_rec() */


    static void fft_dif_iter_seq(double *z, unsigned long n)
    {
        unsigned long i, n2;

        n2 = n << 1;
        for (i = n; i > 1; i >>= 1) {
            double a, b, t;
            unsigned long i2, k;
            i2 = i << 1;
            t = TWOPI / (double)i;
            a = sin(0.5 * t);
            a *= 2.0 * a;
            b = sin(t);
            for (k = 0; k < n2; k += i2) {
                double c, s;
                unsigned long j;
                c = 1.0;
                s = 0.0;
                for (j = 0; j < i; j += 2) {
                    double ur, ui, tmp;
                    unsigned long kr, ki, mr, mi;
                    kr = k + j;
                    ki = kr + 1;
                    mr = kr + i;
                    mi = mr + 1;
                    ur = z[kr];
                    ui = z[ki];
                    z[kr] = ur + z[mr];
                    z[ki] = ui + z[mi];
                    ur -= z[mr];
                    ui -= z[mi];
                    z[mr] = ur * c - ui * s;
                    z[mi] = ur * s + ui * c;
                    tmp = c;
                    c -= a * c + b * s;
                    s -= a * s - b * tmp;
                }
            }
        }
        return;
    }   /* fft_dif_iter_seq() */


    static void fft_dif_iter(double *z, unsigned long n)
    {
        unsigned long i, n2;

        n2 = n << 1;
        for (i = n; i > 1; i >>= 1) {
            double a, b, c, s, t;
            unsigned long i2, j;
            i2 = i << 1;
            t = TWOPI / (double)i;
            a = sin(0.5 * t);
            a *= 2.0 * a;
            b = sin(t);
            c = 1.0;
            s = 0.0;
            for (j = 0; j < i; j += 2) {
                double tmp;
                unsigned long kr, kmax;
                kmax = n2 + j;
                for (kr = j; kr < kmax; kr += i2) {
                    double ur, ui;
                    unsigned long ki, mr, mi;
                    ki = kr + 1;
                    mr = kr + i;
                    mi = mr + 1;
                    ur = z[kr];
                    ui = z[ki];
                    z[kr] = ur + z[mr];
                    z[ki] = ui + z[mi];
                    ur -= z[mr];
                    ui -= z[mi];
                    z[mr] = ur * c - ui * s;
                    z[mi] = ur * s + ui * c;
                }
                tmp = c;
                c -= a * c + b * s;
                s -= a * s - b * tmp;
            }
        }
        return;
    }   /* fft_dif_iter() */
}
