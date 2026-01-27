#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <riscv_vector.h>
#include "rvv_tests.h"
#include "util.h"

static int
rvv_cmpf_v( float a[], float b[], float c[],int n)
{
    size_t vl=0;
    size_t i=0;
    uint32_t bits=0;
    while(n>0) {
        size_t vl = __riscv_vsetvl_e32m1(MAX_ELEMENTS - i);
        vfloat32m1_t va = __riscv_vle32_v_f32m1(&a[i], vl);
        vfloat32m1_t vb = __riscv_vle32_v_f32m1(&b[i], vl); 
        vbool32_t m = __riscv_vmflt_vv_f32m1_b32(va, vb, vl);  // A < B ?
        bits += __riscv_vcpop_m_b32(m, vl); // popcount true lanes (opti
        n-=vl;
        i+=vl;
    }
    return bits;
}
static int
rvv_cmpf_s( float a[], float b[], float c[],int n)
{
    int i;
    uint32_t bits=0;
    for(i=0;i<n;i++) {
        if (a[i] < b[i]) bits++;
    }
    return bits;
}
bool
test_cmpf(void) 
{
    float a[MAX_ELEMENTS], b[MAX_ELEMENTS], c_v[MAX_ELEMENTS],c_s[MAX_ELEMENTS];
    init_vectorsf(a,b,MAX_ELEMENTS);
    uint32_t bits_v = rvv_cmpf_v(a,b,c_v,MAX_ELEMENTS);
    uint32_t bits_s = rvv_cmpf_s(a,b,c_v,MAX_ELEMENTS);
    printf("Total Bits: Total: %d Vector: %d Static: %d \n", MAX_ELEMENTS,bits_v,bits_s);
    return (bits_v == bits_s)? true:false;
}
