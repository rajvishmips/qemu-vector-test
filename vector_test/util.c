#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <riscv_vector.h>
#include "rvv_tests.h"
#include "util.h"
int
init_vectorsf(float a[],float b[], int n)
{
    for (int i = 0; i < MAX_ELEMENTS; ++i) { 
        a[i] = (float)i; 
        b[i] = (float)(i * 10); 
    }
    return 0;
}
int
init_vectorsi(int a[],int b[], int n)
{
    for (int i = 0; i < MAX_ELEMENTS; ++i) { 
        a[i] = i; 
        b[i] = (i * 10); 
    }
    return 0;
}
void 
print_result_f( float c_v[], float c_s[], int n)
{
    int i;
    for(i=0;i<n;i++) {
        printf("d->%d:%.1f, %.1f \n",i,c_v[i],c_s[i]);
    }   
}
void 
print_result_i( int c_v[], int c_s[], int n)
{
    int i;
    for(i=0;i<n;i++) {
        printf("d->%d:%d, %d\n",i,c_v[i],c_s[i]);
    }   
}
bool
check_array_i(int c_v[], int c_s[], int n)
{
    int i;
    for(i=0;i<n;i++) {
        if (c_v[i] != c_s[i]) return false;
    }
    return true;
}
bool
check_array_f(float c_v[], float c_s[], int n)
{
    int i;
    for(i=0;i<n;i++) {
        if (c_v[i] != c_s[i]) return false;
    }
    return true;
}
