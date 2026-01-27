#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <riscv_vector.h>
#include "rvv_tests.h"
#include "util.h"

int
static rvv_addf_v( float a[], float b[], float c[],int n)
{
    size_t vl=0;
    size_t i=0;
    while(n>0) {
        size_t vl = __riscv_vsetvl_e32m1(MAX_ELEMENTS - i);
        vfloat32m1_t va = __riscv_vle32_v_f32m1(&a[i], vl);
        vfloat32m1_t vb = __riscv_vle32_v_f32m1(&b[i], vl); 
        vfloat32m1_t vc = __riscv_vfadd_vv_f32m1(va, vb, vl);
        __riscv_vse32_v_f32m1(&c[i], vc, vl);                      
        n-=vl;
        i+=vl;
    }
    return 0;
}
static int
rvv_addf_s(float a[], float b[], float c[],int n)
{
    int i;
    for(i=0;i<n;i++) {
        c[i]=a[i]+b[i];
    }
    return 0;
}


bool 
test_addf(void) 
{
    float a[MAX_ELEMENTS], b[MAX_ELEMENTS], c_v[MAX_ELEMENTS],c_s[MAX_ELEMENTS];
    init_vectorsf(a,b,MAX_ELEMENTS);
    rvv_addf_v(a,b,c_v,MAX_ELEMENTS);
    rvv_addf_s(a,b,c_s,MAX_ELEMENTS);
    if (!check_array_f(c_v,c_s,MAX_ELEMENTS)) {
        printf("Float Sum Failed. \n");
        print_result_f(c_v,c_s,MAX_ELEMENTS);
        return false;
    }
    printf("Float Addition succesful \n");
    return true;
}
