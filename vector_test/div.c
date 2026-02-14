#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <riscv_vector.h>
#include "rvv_tests.h"
#include "util.h"

//Variants
//Integer
//vdiv.vv
//vdiv.vx
//vrem.vv
//vrem.vx
//vdivu.vv
//vdivu.vx

//Floating
//vfdiv.vv
//vfdiv.vx

//Mask Support
//LMUL - Length Multiplier
//SEW  - Selected Element Width
//Tail/Mask Policies - to define how inactive elements are handled
static int 
rvv_divi32_vv(int32_t *a,int32_t *b, int32_t *c,size_t n)
{
    size_t i=0;
    while(i<n) {
        size_t vl = __riscv_vsetvl_e32m1(n - i);
        vint32m1_t va = __riscv_vle32_v_i32m1(&a[i], vl);
        vint32m1_t vb = __riscv_vle32_v_i32m1(&b[i], vl);
        vint32m1_t vc = __riscv_vdiv_vv_i32m1(va, vb, vl);
        __riscv_vse32_v_i32m1((unsigned long int *)&c[i], vc, vl);
        i+=vl;
    }
    return 0;

}
static int 
rvv_divi32_vv_bf(int32_t *a,int32_t *b, int32_t *c,size_t n)
{
   for(int i=0;i<n;i++) {
        c[i]=a[i]/b[i];
    }
    return 0;
} 
extern bool
test_divi32_vv(int debug)
{
    int32_t a[MAX_ELEMENTS];
    int32_t b[MAX_ELEMENTS];
    int32_t div[MAX_ELEMENTS];
    int32_t div_bf[MAX_ELEMENTS];

    printf("Testing Vector Vector i32 Division: ");
    init_vectors_i32(a,MAX_ELEMENTS,true);
    init_vectors_i32(b,MAX_ELEMENTS,true);
    rvv_divi32_vv(a,b,div,MAX_ELEMENTS);
    rvv_divi32_vv_bf(a,b,div_bf,MAX_ELEMENTS);
    if (compare_array_i(div,div_bf,MAX_ELEMENTS,0)) {
        printf(":-)\n");
        return true;
    }
    printf(":-(\n");
    return false;
}


//Let us do a masked division
static int 
rvv_divi32_vv_m(int32_t *a,int32_t *b, int32_t *c,uint32_t *mask,size_t n)
{
    size_t i=0;
    while(i<n) {
        size_t vl = __riscv_vsetvl_e32m1(n - i);
        vint32m1_t va = __riscv_vle32_v_i32m1(&a[i], vl);
        vint32m1_t vb = __riscv_vle32_v_i32m1(&b[i], vl);
        vuint32m1_t v = __riscv_vle32_v_u32m1(&mask[i], vl);
        vbool32_t vmask = __riscv_vmsne_vx_u32m1_b32(v, 0, vl);
        vint32m1_t vc = __riscv_vdiv_vv_i32m1_m(
                                vmask,
                                va, 
                                vb, 
                                vl);
        __riscv_vse32_v_i32m1((unsigned long int *)&c[i], vc, vl);
        i+=vl;
    }
    return 0;
}
static int 
rvv_divi32_vv_bf_m(int32_t *a,int32_t *b, int32_t *c,uint32_t *mask,size_t n)
{
   for(int i=0;i<n;i++) {
        if(mask[i])c[i]=a[i]/b[i];
    }
    return 0;
} 
extern bool
test_divi32_vv_m(int debug)
{
    int32_t a[MAX_ELEMENTS];
    int32_t b[MAX_ELEMENTS];
    int32_t div[MAX_ELEMENTS];
    int32_t div_bf[MAX_ELEMENTS];
    int32_t mask[MAX_ELEMENTS] = {1};

    printf("Testing Vector Vector i32 Masked Division: ");
    init_vectors_i32(a,MAX_ELEMENTS,true);
    init_vectors_i32(b,MAX_ELEMENTS,true);
    init_mask(mask,MAX_ELEMENTS);
    rvv_divi32_vv_m(a,b,div,mask,MAX_ELEMENTS);
    rvv_divi32_vv_bf_m(a,b,div_bf,mask,MAX_ELEMENTS);
    if (compare_array_im(div,div_bf,mask,MAX_ELEMENTS,0)) {
        printf(":-)\n");
        return true;
    }
    printf(":-(\n");
    return false;
}

//Floating Point Division
static int 
rvv_divf32_vv(float *a,float *b, float *c,size_t n)
{
    size_t i=0;
    while(i<n) {
        size_t vl = __riscv_vsetvl_e32m1(n - i);
        vfloat32m1_t va = __riscv_vle32_v_f32m1(&a[i], vl);
        vfloat32m1_t vb = __riscv_vle32_v_f32m1(&b[i], vl);
        vfloat32m1_t vc = __riscv_vfdiv_vv_f32m1(va, vb, vl);
        __riscv_vse32_v_f32m1(&c[i], vc, vl);
        i+=vl;
    }
    return 0;

}
static int 
rvv_divf32_vv_bf(float *a,float *b, float *c,size_t n)
{
   for(int i=0;i<n;i++) {
        c[i]=a[i]/b[i];
    }
    return 0;
} 
extern bool
test_divf32_vv(int debug)
{
    float a[MAX_ELEMENTS];
    float b[MAX_ELEMENTS];
    float div[MAX_ELEMENTS];
    float div_bf[MAX_ELEMENTS];

    printf("Testing Vector Vector f32 Division: ");
    init_vectors_f32(a,MAX_ELEMENTS,true);
    init_vectors_f32(b,MAX_ELEMENTS,true);
    rvv_divf32_vv(a,b,div,MAX_ELEMENTS);
    rvv_divf32_vv_bf(a,b,div_bf,MAX_ELEMENTS);
    if (compare_array_f(div,div_bf,MAX_ELEMENTS,0)) {
        printf(":-)\n");
        return true;
    }
    printf(":-(\n");
    return false;
}


#if 0
//Let us do a masked division
static int 
rvv_divi32_vv_m(int32_t *a,int32_t *b, int32_t *c,uint32_t *mask,size_t n)
{
    size_t i=0;
    while(i<n) {
        size_t vl = __riscv_vsetvl_e32m1(n - i);
        vint32m1_t va = __riscv_vle32_v_i32m1(&a[i], vl);
        vint32m1_t vb = __riscv_vle32_v_i32m1(&b[i], vl);
        vuint32m1_t v = __riscv_vle32_v_u32m1(&mask[i], vl);
        vbool32_t vmask = __riscv_vmsne_vx_u32m1_b32(v, 0, vl);
        vint32m1_t vc = __riscv_vdiv_vv_i32m1_m(
                                vmask,
                                va, 
                                vb, 
                                vl);
        __riscv_vse32_v_i32m1((unsigned long int *)&c[i], vc, vl);
        i+=vl;
    }
    return 0;
}
static int 
rvv_divf32_vv_bf_m(int32_t *a,int32_t *b, int32_t *c,uint32_t *mask,size_t n)
{
   for(int i=0;i<n;i++) {
        if(mask[i])c[i]=a[i]/b[i];
    }
    return 0;
} 
extern bool
test_divi32_vv_m(int debug)
{
    int32_t a[MAX_ELEMENTS];
    int32_t b[MAX_ELEMENTS];
    int32_t div[MAX_ELEMENTS];
    int32_t div_bf[MAX_ELEMENTS];
    int32_t mask[MAX_ELEMENTS] = {1};

    printf("Testing Vector Vector i32 Masked Division: ");
    init_vectors_i32(a,MAX_ELEMENTS,true);
    init_vectors_i32(b,MAX_ELEMENTS,true);
    init_mask(mask,MAX_ELEMENTS);
    rvv_divi32_vv_m(a,b,div,mask,MAX_ELEMENTS);
    rvv_divi32_vv_bf_m(a,b,div_bf,mask,MAX_ELEMENTS);
    if (compare_array_im(div,div_bf,mask,MAX_ELEMENTS,0)) {
        printf(":-)\n");
        return true;
    }
    printf(":-(\n");
    return false;
}
#endif
