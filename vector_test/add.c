#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <riscv_vector.h>
#include "rvv_tests.h"
#include "util.h"
// Should be expanded to test variants
//vadd.vv
//vadd.vx
//vadd.vi
//vaddw.vv
//vaddw.wv
//vadd.vs
//vsadd
//vadc
//vmadc
//vfadd.vv
//vfadd.vf

//Mask Support
//LMUL - Length Multiplier
//SEW  - Selected Element Width
//Tail/Mask Policies - to define how inactive elements are handled

//Using RVV
static int 
rvv_addi32_v(int32_t *a,int32_t *b, int32_t *c,size_t n)
{
    size_t i=0;
    while(i<n) {
        size_t vl = __riscv_vsetvl_e32m1(n - i);
        vint32m1_t va = __riscv_vle32_v_i32m1(&a[i], vl);
        vint32m1_t vb = __riscv_vle32_v_i32m1(&b[i], vl);
        vint32m1_t vc = __riscv_vadd_vv_i32m1(va, vb, vl);
        __riscv_vse32_v_i32m1((unsigned long int *)&c[i], vc, vl);
        i+=vl;
    }
    return 0;
}
// Using Brute Force
static int 
rvv_addi32_bf(int32_t *a,int32_t *b, int32_t *c,size_t n)
{
    int i;
    for(i=0;i<n;i++) {
        c[i]=a[i]+b[i];
    }
    return 0;
}
extern bool
test_addi32_vv(int debug)
{
    int32_t a[MAX_ELEMENTS];
    int32_t b[MAX_ELEMENTS];
    int32_t sum_v[MAX_ELEMENTS];
    int32_t sum_bf[MAX_ELEMENTS];

    printf("Testing Vector Vector i32 Addition: ");
    init_vectors_i32(a,MAX_ELEMENTS,true);
    init_vectors_i32(b,MAX_ELEMENTS,true);
    rvv_addi32_v(a,b,sum_v,MAX_ELEMENTS);
    rvv_addi32_bf(a,b,sum_bf,MAX_ELEMENTS);
    if (compare_array_i(sum_v,sum_bf,MAX_ELEMENTS,0)) {
        printf(":-)\n");
        return true;
    }
    printf(":-(\n");
    return false;
}


//Test the  floating point addition
static int
rvv_addf32_v( float *a,float *b, float *c,size_t n)
{
    size_t i=0;
    while(i<n) {
        size_t vl = __riscv_vsetvl_e32m1(n - i);
        vfloat32m1_t va = __riscv_vle32_v_f32m1(&a[i], vl);
        vfloat32m1_t vb = __riscv_vle32_v_f32m1(&b[i], vl);
        vfloat32m1_t vc = __riscv_vfadd_vv_f32m1(va, vb, vl);
        __riscv_vse32_v_f32m1(&c[i], vc, vl);
        i+=vl;
    }
    return 0;
}
static int
rvv_addf32_bf(float *a,float *b, float *c,size_t n)
{
    int i;
    for(i=0;i<n;i++) {
        c[i]=a[i]+b[i];
    }
    return 0;
}
extern bool
test_addf32_vv(int debug)
{
    float a[MAX_ELEMENTS];
    float b[MAX_ELEMENTS];
    float sum_v[MAX_ELEMENTS];
    float sum_bf[MAX_ELEMENTS];

    printf("Testing Vector Vector f32 Addition: ");
    init_vectors_f32(a,MAX_ELEMENTS,true);
    init_vectors_f32(b,MAX_ELEMENTS,true);
    rvv_addf32_v(a,b,sum_v,MAX_ELEMENTS);
    rvv_addf32_bf(a,b,sum_bf,MAX_ELEMENTS);
    if (compare_array_f(sum_v,sum_bf,MAX_ELEMENTS,0)) {
        printf(":-)\n");
        return true;
    }
    printf(":-(\n");
    return false;
}
