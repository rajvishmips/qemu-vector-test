#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <riscv_vector.h>
#include "rvv_tests.h"
#include "util.h"

int
static rvv_mulf_vv( float a[], float b[], float c[],int n)
{
    size_t vl=0;
    size_t i=0;
    while(n>0) {
        size_t vl = __riscv_vsetvl_e32m1(MAX_ELEMENTS - i);
        vfloat32m1_t va = __riscv_vle32_v_f32m1(&a[i], vl);
        vfloat32m1_t vb = __riscv_vle32_v_f32m1(&b[i], vl); 
        vfloat32m1_t vc = __riscv_vfmul_vv_f32m1(va, vb, vl);
        __riscv_vse32_v_f32m1(&c[i], vc, vl);                      
        n-=vl;
        i+=vl;
    }
    return 0;
}
int
static rvv_mulf_vc( float a[], float factor, float c[],int n)
{
    size_t vl=0;
    size_t i=0;
    while(n>0) {
        size_t vl = __riscv_vsetvl_e32m1(MAX_ELEMENTS - i);
        vfloat32m1_t va = __riscv_vle32_v_f32m1(&a[i], vl); 
        vfloat32m1_t vc = __riscv_vfmul_vf_f32m1(va, factor, vl);
        __riscv_vse32_v_f32m1(&c[i], vc, vl);                      
        n-=vl;
        i+=vl;
    }
    return 0;
}
static int
rvv_mulf_svv(float a[], float b[], float c[],int n)
{
    int i;
    for(i=0;i<n;i++) {
        c[i]=a[i]*b[i];
    }
    return 0;
}
static int
rvv_mulf_svc(float a[],float factor , float c[],int n)
{
    int i;
    for(i=0;i<n;i++) {
        c[i]=a[i]*factor;
    }
    return 0;
}


static bool
check_mulf_vv(float c_v[], float c_s[], int n)
{
    int i;
    for(i=0;i<n;i++) {
        if (c_v[i] != c_s[i]) return false;
    }
    return true;
}

bool 
test_mulf(void) 
{
    float a[MAX_ELEMENTS], b[MAX_ELEMENTS], c_v[MAX_ELEMENTS],c_s[MAX_ELEMENTS];
    float factor = 0.5;
    init_vectorsf(a,b,MAX_ELEMENTS);
    rvv_mulf_vv(a,b,c_v,MAX_ELEMENTS);
    rvv_mulf_svv(a,b,c_s,MAX_ELEMENTS);
    if (!check_mulf_vv(c_v,c_s,MAX_ELEMENTS)) {
        printf("Float Vector-vector Failed. \n");
        print_result_f(c_v,c_s,MAX_ELEMENTS);
        return false;
    }
    printf("Float Vector -Vector Multiplication succesful \n");
    rvv_mulf_vc(a, factor,c_v,MAX_ELEMENTS);
    rvv_mulf_svc(a, factor,c_s,MAX_ELEMENTS);
    if (!check_mulf_vv(c_v,c_s,MAX_ELEMENTS)) {
        printf("Float Vector-Constant Failed. \n");
        print_result_f(c_v,c_s,MAX_ELEMENTS);
        return false;
    }
    
    return true;
}
