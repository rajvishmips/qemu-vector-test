#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <riscv_vector.h>
#include "rvv_tests.h"
#include "util.h"

static int 
rvv_vfredmax_vs(float init,float vs1[],uint32_t  mask[], size_t n)
{
    float max=init;
    size_t i=0;
    while(i<n) {
        size_t vl = __riscv_vsetvl_e32m1(n - i);
        vfloat32m1_t  vmax = __riscv_vfmv_v_f_f32m1(max, vl);
        vfloat32m1_t vvs1 = __riscv_vle32_v_f32m1(&vs1[i], vl);
        vuint32m1_t v = __riscv_vle32_v_u32m1(&mask[i], vl);
        vbool32_t vmask = __riscv_vmsne_vx_u32m1_b32(v, 0, vl);
        vmax = __riscv_vfredmax_vs_f32m1_f32m1_m(vmask,vvs1, vmax, vl);
        max  = __riscv_vfmv_f_s_f32m1_f32(vmax);
        i+=vl;
    }
    return max;

}
static int
rvv_vfredmax_bf(float init,float vs1[],uint32_t  mask[], size_t n)
{
    float max=init;
    int i;
    for (i=0;i<n;i++)
        if ( mask[i]) max = fmax(max,vs1[i]);
    return max;
}
bool
test_vfredmax(int debug)
{
    int i;
    float init= -INFINITY;
    float  max,max1;
    float  vs1[MAX_ELEMENTS], vs2[MAX_ELEMENTS];
    uint32_t mask[MAX_ELEMENTS];

    init_vectors_f32(vs1,MAX_ELEMENTS,true);
    init_mask(mask,MAX_ELEMENTS);
    max = rvv_vfredmax_vs(init,vs1,mask,MAX_ELEMENTS);
    max1 = rvv_vfredmax_bf(init,vs1,mask,MAX_ELEMENTS);
    //for(i=0;i<MAX_ELEMENTS;i++)
        //printf("%2d %f %d \n",i,vs1[i],mask[i]);
    //printf("test_vfredmax: mask : %10.4f %10.4f \n",max,max1);
    printf("Testing Vector Floating Point Reduction: Mask: ");
    if ( max == max1) 
        printf(":-)\n");
    else
        printf(":-(\n");


    printf("Testing Vector Floating Point Reduction: Without  Mask: ");
    for(i=0;i<MAX_ELEMENTS;i++) mask[i]=1;
    max = rvv_vfredmax_vs(init,vs1,mask,MAX_ELEMENTS);
    max1 = rvv_vfredmax_bf(init,vs1,mask,MAX_ELEMENTS);
    if ( max == max1) 
        printf(":-)\n");
    else
        printf(":-(\n");
}


