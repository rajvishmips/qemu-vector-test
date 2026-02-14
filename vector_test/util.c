#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>
#include <riscv_vector.h>
//#include "rvv_tests.h"
#include "util.h"



//Initialize Integer types
// int8_t
// int16_t 
// int32_t
// int64_t
void
init_vectors_i8(int8_t *a,int n, bool random)
{
    for(int i=0;i<n;i++) {
        a[i]=(random)?(int8_t)(rand()%255):i%255;
    }
    return;
}
void
init_vectors_i16(int16_t *a,int n, bool random)
{
    for(int i=0;i<n;i++) {
        a[i]=random?(int16_t)rand():(int16_t)i;
    }
    return;
}
void
init_vectors_i32(int32_t *a,int n, bool random)
{
    for(int i=0;i<n;i++) {
        a[i]=random?(int32_t)(rand()):(int32_t)i;
    }
    return;
}
void
init_vectors_i64(int32_t *a,int n, bool random)
{
    for(int i=0;i<n;i++) {
        a[i]=random?(int64_t)rand():i;
    }
    return;
}
//
//Initialize Floating Points
//
void
init_vectors_f16(_Float16 *a,int n, bool random)
{
    for(int i=0;i<n;i++) {
        a[i]=random?(_Float16)rand():(_Float16)i;
    }
    return;
}
void
init_vectors_f32(float *a,int n, bool random)
{
    for(int i=0;i<n;i++) {
        a[i]=random?(float)rand():(float)i;
    }
    return;
}
void
init_vectors_f64(double *a,int n, bool random)
{
    for(int i=0;i<n;i++) {
        a[i]=random?(double)rand():(double)i;
    }
    return;
}
bool
compare_array_i(int32_t *a1,int32_t *a2, int n,int debug)
{
    int i=0;
    for ( i=0; i<n;i++) {
        if (debug) printf("%02d: %04d %04d \n",i,a1[i],a2[i]);
        if (a1[i] !=a2[i]) return false;
    }
    return true;
}
bool
compare_array_im(int32_t *a1,int32_t *a2, int32_t *mask, int n,int debug)
{
    int i=0;
    for ( i=0; i<n;i++) {
        if (debug) printf("%02d: %0d %0d \n",i,a1[i],a2[i]);
        if (mask[i])
            if (a1[i] !=a2[i]) return false;
    }
    return true;
}

bool
compare_array_f(float a1[], float a2[], int n,int debug)
{
    int i;
    for (i=0;i<n;i++) {
        if (debug) printf("%02d: %010.4f %010.4f \n",i,a1[i],a2[i]);
        if (!FLOAT_EQ_ABS(a1[i],a2[i])) return false;
    }
    return true;
}
bool
init_mask(int32_t  mask[],int n)
{
     for(int i=0;i<n;i++) {
        mask[i]=rand()%2;
    }
    return true;
}
void
print_vector_i(int32_t *a,int32_t n)
{
    for ( int i=0; i<n;i++) {
        printf("%02d: %0d \n",i,a[i]);
    }
}
