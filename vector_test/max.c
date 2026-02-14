#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <riscv_vector.h>
#include "rvv_tests.h"
#include "util.h"

//Variants
//Integer
//vmax.vv
//vmaxu.vv
//vmax.vs
//vmaxu.vs
//vmax.vv_m
//vmaxu.vv_m
//vmax.vs_m
//vmaxu.vs_m

//Floating
//vfmax.vv
//vfmaxu.vv
//vfmax.vs
//vfmaxu.vs
//vfmax.vv_m
//vfmaxu.vv_m
//vfmax.vs_m
//vfmaxu.vs_m

//Mask Support
//LMUL - Length Multiplier
//SEW  - Selected Element Width
//Tail/Mask Policies - to define how inactive elements are handled
static int 
rvv_maxi32_vv(int32_t *a,int32_t *b, int32_t *c,size_t n)
{
    size_t i=0;
    while(i<n) {
        size_t vl = __riscv_vsetvl_e32m1(n - i);
        vint32m1_t va = __riscv_vle32_v_i32m1(&a[i], vl);
        vint32m1_t vb = __riscv_vle32_v_i32m1(&b[i], vl);
        vint32m1_t vc = __riscv_vmax_vv_i32m1(va, vb, vl);
        __riscv_vse32_v_i32m1((unsigned long int *)&c[i], vc, vl);
        i+=vl;
    }
    return 0;

}
#ifndef MAX
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif

static int 
rvv_maxi32_vv_bf(int32_t *a,int32_t *b, int32_t *c,size_t n)
{
    for(int i=0;i<n;i++) {
        c[i] = MAX(a[i],b[i]);

    }
    return 0;
} 
extern bool
test_maxi32_vv(int debug)
{
    int32_t a[MAX_ELEMENTS];
    int32_t b[MAX_ELEMENTS];
    int32_t max[MAX_ELEMENTS];
    int32_t max_bf[MAX_ELEMENTS];

    printf("Testing Vector Vector i32 Max: ");
    init_vectors_i32(a,MAX_ELEMENTS,true);
    init_vectors_i32(b,MAX_ELEMENTS,true);
    rvv_maxi32_vv(a,b,max,MAX_ELEMENTS);
    rvv_maxi32_vv_bf(a,b,max_bf,MAX_ELEMENTS);
    if (compare_array_i(max,max_bf,MAX_ELEMENTS,0)) {
        printf(":-)\n");
        return true;
    }
    printf(":-(\n");
    return false;
}
