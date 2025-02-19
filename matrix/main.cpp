#include <stdio.h>
#include "blockmatr.hpp"
#include <string>
#include <x86intrin.h>

using namespace std;


int main(int argc, char **argv) {
    const int ay = argc > 1 ? std::stoi(argv[1]) : 1000,
            ax = argc > 2 ? std::stoi(argv[2]) : 900,
            by = ax,
            bx = argc > 3 ? std::stoi(argv[3]) : 1200,
            cy = ay, cx = bx;

    blockmatrix<double> a(ay,ax), b(by, bx), c(cy, cx);

    for (int i = 0; i < ay; i++) {
        for (int j = 0; j < ax; j++) {
            *a(i,j) = i*j;
        }
    }

    for (int i = 0; i < by; i++) {
        for (int j = 0; j < bx; j++) {
            *b(i,j) = i*j;
        }
    }

    //к коду, который нельзя менять, добавим часть с блочным перемножением, чтобы показать ускорение
    long long start = __rdtsc();
    c.fast_mul(a,b);
    long long end   = __rdtsc();
    double sum = 0;
    for (int i = 0; i < cy; i++) {
        for (int j = 0; j < cx; j++) {
            //printf("%f ", *c(i,j));
            sum += *c(i,j);
        }
    }

    printf("mul_t sum = %.0lf time=%.6f\n", sum, (end - start)/1000000000.);

    start = __rdtsc();
    c.mul(a,b);
    end   = __rdtsc();
    sum = 0;
    for (int i = 0; i < cy; i++) {
        for (int j = 0; j < cx; j++) {
            sum += *c(i,j);
        }
    }
    printf("sum       = %.0lf time=%.6f\n", sum, (end - start)/1000000000.);
}