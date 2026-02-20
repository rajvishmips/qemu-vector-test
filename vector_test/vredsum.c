#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <riscv_vector.h>
#include "rvv_tests.h"
#include "util.h"
//
// TODO: XXX
//      FP32: __riscv_vfredsum_vs_f32m1_f32m1_m
//      FP64: __riscv_vfredsum_vs_f64m1_f64m1_m
//      FP32 ordered: __riscv_vfredosum_vs_f32m1_f32m1_m

static int
rvv_vredsumi32_vv(int32_t init,int32_t vs[], size_t n)
{
    int32_t sum = init;
    size_t i=0;
    while(i<n) {
        size_t vl = __riscv_vsetvl_e32m1(n - i);
        vint32m1_t vsum = __riscv_vmv_v_x_i32m1(sum, vl);
        vint32m1_t vvs = __riscv_vle32_v_i32m1(&vs[i], vl);
        vsum = __riscv_vredsum_vs_i32m1_i32m1(vvs, vsum, vl);
        sum = __riscv_vmv_x_s_i32m1_i32(vsum);
        i+=vl;
    }
    return sum;
}
static int32_t
rvv_vredsumi32_bf(int32_t init,int32_t vs[],size_t n)
{
    int i;
    int32_t sum = init;
    for (i=0;i<n;i++) {
        sum+=vs[i];
    }
    return sum;
}
extern bool
test_vredsum(int debug)
{
    int32_t init= SCALAR_I;
    int32_t vs[MAX_ELEMENTS];
    int sum= 0;
    int sum_bf=0;
    init_vectors_i32(vs,MAX_ELEMENTS,true);
    printf("Testing Vector Redsum i32 ");
    sum = rvv_vredsumi32_vv(init,vs,MAX_ELEMENTS);
    sum_bf = rvv_vredsumi32_bf(init,vs,MAX_ELEMENTS);
    if ( sum == sum_bf) {
        printf(" :-) \n");
    } else {
        printf(" :-( \n");
    }
}

