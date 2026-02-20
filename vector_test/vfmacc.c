#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <riscv_vector.h>
#include "rvv_tests.h"
#include "util.h"

// vfmsac.vv vd = (vs1 × vs2) − vd
//XXX TBD
// vfnmacc.vv  vd = −(vs1 × vs2) + vd
// vfnmsac.vv vd = −(vs1 × vs2) − vd

static void
rvv_vfmacc_vv(float vd[], float vs1[], float vs2[], int n)
{
    size_t i=0;
    while(i<n) {
        size_t vl = __riscv_vsetvl_e32m1(MAX_ELEMENTS - i);
        vfloat32m1_t vvs1 = __riscv_vle32_v_f32m1((const float *)&vs1[i], vl);
        vfloat32m1_t vvs2 = __riscv_vle32_v_f32m1((const float *)&vs2[i], vl);
        vfloat32m1_t vvd = __riscv_vle32_v_f32m1((const  float *)&vd[i], vl);
        vvd = __riscv_vfmacc_vv_f32m1(vvd,vvs1,vvs2,vl);
        __riscv_vse32_v_f32m1((float *)&vd[i], vvd, vl);
        i+=vl;
    }
}
static void
rvv_vfmacc_vv_bf(float vd[],float vs1[], float vs2[], int n)
{
    int i;
    for (i=0;i<n;i++) {
        vd[i] += (vs1[i] * vs2[i]);
    }
}

extern bool
test_vfmacc_vv(int debug)
{
    float vs1[MAX_ELEMENTS], vs2[MAX_ELEMENTS];
    float vd1[MAX_ELEMENTS], vd2[MAX_ELEMENTS];
    int i;

    init_vectors_f32(vs1,MAX_ELEMENTS,true);
    init_vectors_f32(vs2,MAX_ELEMENTS,true);

    for(i=0;i<MAX_ELEMENTS;i++) {
        vd1[i]=vd2[i]=0.0;
    }
    
    rvv_vfmacc_vv(vd1,vs1,vs2,MAX_ELEMENTS);
    rvv_vfmacc_vv_bf(vd2,vs1,vs2,MAX_ELEMENTS);

    printf("Testing vector Floating Point Multiply Accumulate:");
    if (compare_array_f(vd1,vd2,MAX_ELEMENTS,false)) {
        printf(":-)\n");
    } else {
        printf(":-(\n");
    }
}
