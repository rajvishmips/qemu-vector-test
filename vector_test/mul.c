#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <riscv_vector.h>
#include "rvv_tests.h"
#include "util.h"

//Variants
//Integer
//vmul.vv
//vmul.vx
//vmul.vi
//vmulh.vv
//vmulh.vx
//vmulhsu.vv
//vmulhsu.vx

//Float
//vfmul.vv
//vfmul.vf
//vwmul
//vgmul.vv

static int 
rvv_muli32_vv(int32_t *a,int32_t *b, int32_t *c,size_t n)
{
    size_t i=0;
    while(i<n) {
        size_t vl = __riscv_vsetvl_e32m1(n - i);
        vint32m1_t va = __riscv_vle32_v_i32m1(&a[i], vl);
        vint32m1_t vb = __riscv_vle32_v_i32m1(&b[i], vl);
        vint32m1_t vc = __riscv_vmul_vv_i32m1(va, vb, vl);
        __riscv_vse32_v_i32m1((unsigned long int *)&c[i], vc, vl);
        i+=vl;
    }
    return 0;
}
static int 
rvv_muli32_vv_bf(int32_t *a,int32_t *b, int32_t *c,size_t n)
{
    for(int i=0;i<n;i++)
        c[i] = a[i]*b[i];
    return 0;
}
extern bool
test_muli32_vv(int debug)
{
    int32_t a[MAX_ELEMENTS];
    int32_t b[MAX_ELEMENTS];
    int32_t prod[MAX_ELEMENTS];
    int32_t prod_bf[MAX_ELEMENTS];

    printf("Testing Vector Vector i32 Multiplication: ");
    init_vectors_i32(a,MAX_ELEMENTS,true);
    init_vectors_i32(b,MAX_ELEMENTS,true);
    rvv_muli32_vv(a,b,prod,MAX_ELEMENTS);
    rvv_muli32_vv_bf(a,b,prod_bf,MAX_ELEMENTS);
    if (compare_array_i(prod,prod_bf,MAX_ELEMENTS,0)) {
        printf(":-)\n");
        return true;
    }
    printf(":-(\n");
    return false;
}
static int 
rvv_muli32_vs(int32_t *a,int32_t scalar , int32_t *c,size_t n)
{
    size_t i=0;
    while(i<n) {
        size_t vl = __riscv_vsetvl_e32m1(n - i);
        vint32m1_t va = __riscv_vle32_v_i32m1(&a[i], vl);
        vint32m1_t vc = __riscv_vmul_vx_i32m1(va, scalar, vl);
        __riscv_vse32_v_i32m1((unsigned long int *)&c[i], vc, vl);
        i+=vl;
    }
    return 0;
}
static int 
rvv_muli32_vs_bf(int32_t *a,int32_t scalar, int32_t *c,size_t n)
{
    for(int i=0;i<n;i++)
        c[i] = a[i]*scalar;
    return 0;
}
extern bool
test_muli32_vs(int debug)
{
    int32_t a[MAX_ELEMENTS];
    int32_t prod[MAX_ELEMENTS];
    int32_t prod_bf[MAX_ELEMENTS];
    int scalar = SCALAR_I;

    printf("Testing Vector Scalar i32 Multiplication: ");
    init_vectors_i32(a,MAX_ELEMENTS,true);
    rvv_muli32_vs(a,scalar,prod,MAX_ELEMENTS);
    rvv_muli32_vs_bf(a,scalar,prod_bf,MAX_ELEMENTS);
    if (compare_array_i(prod,prod_bf,MAX_ELEMENTS,0)) {
        printf(":-)\n");
        return true;
    }
    printf(":-(\n");
    return false;
}
static int 
rvv_mulf32_vf(float *a,float scalar , float *c,size_t n)
{
    size_t i=0;
    while(i<n) {
        size_t vl = __riscv_vsetvl_e32m1(n - i);
        vfloat32m1_t va = __riscv_vle32_v_f32m1(&a[i], vl);
        vfloat32m1_t vc = __riscv_vfmul_vf_f32m1(va, scalar, vl);
        __riscv_vse32_v_f32m1(&c[i], vc, vl);
        i+=vl;
    }
    return 0;
}
static int 
rvv_mulf32_vf_bf(float *a,float scalar , float *c,size_t n)
{
    for(int i=0;i<n;i++)
        c[i] = a[i]*scalar;
    return 0;
}
extern bool
test_mulf32_vf(int debug)
{
    float a[MAX_ELEMENTS];
    float prod[MAX_ELEMENTS];
    float prod_bf[MAX_ELEMENTS];
    float scalar = SCALAR_F;
    int i=rand()%MAX_ELEMENTS;

    printf("Testing Vector Scalar f32 Multiplication: ");
    init_vectors_f32(a,MAX_ELEMENTS,true);
    rvv_mulf32_vf(a,scalar,prod,MAX_ELEMENTS);
    rvv_mulf32_vf_bf(a,scalar,prod_bf,MAX_ELEMENTS);
    
    if (compare_array_f(prod,prod_bf,MAX_ELEMENTS,0)) {
        printf(":-)\n");
        return true;
    }
    printf(":-(\n");
    return false;
}
