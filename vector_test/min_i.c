#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <riscv_vector.h>
#include "rvv_tests.h"
#include "util.h"

static int
rvv_mini_v( int a[], int b[], int c[],int n)
{
    size_t vl=0;
    size_t i=0;
    while(n>0) {
        size_t vl = __riscv_vsetvl_e32m1(MAX_ELEMENTS - i);
        vint32m1_t va = __riscv_vle32_v_i32m1((const long int *)&a[i], vl);
        vint32m1_t vb = __riscv_vle32_v_i32m1((const long int *)&b[i], vl); 
        vint32m1_t vc = __riscv_vmin_vv_i32m1(va, vb, vl);
        __riscv_vse32_v_i32m1((unsigned long int *)&c[i], vc, vl);                      
        n-=vl;
        i+=vl;
    }
    return 0;
}
#ifndef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

static int
rvv_mini_s(int a[],int b[],int c_s[],int n)
{
    int i;
    for(i=0;i<n;i++) {
        c_s[i] = MIN(a[i],b[i]);
    }
    return 0;
}
bool
test_mini(void) 
{
    int a[MAX_ELEMENTS], b[MAX_ELEMENTS], c_v[MAX_ELEMENTS],c_s[MAX_ELEMENTS];
    init_vectorsi(a,b,MAX_ELEMENTS);
    rvv_mini_v(a,b,c_v,MAX_ELEMENTS);
    rvv_mini_s(a,b,c_s,MAX_ELEMENTS);
    if (!check_array_i(c_v,c_s,MAX_ELEMENTS)) {
        printf("Integer Sum Failed. \n");
        return false;
    }
    printf("Integer Minimum succesful \n");
    return true;
}
