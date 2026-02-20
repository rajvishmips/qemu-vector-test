#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <riscv_vector.h>
#include "rvv_tests.h"
#include "util.h"

//Variants
//vslideup.vi - immediate
//vslideup.vx - scalar
//vslide1up.vx - Shifts up by 1 and inserts a value from an integer register (x) at index 0.
//vslide1up.vf vfslide1up.vf (Floating-Point): Shifts up by 1 and inserts a value from a floating-point register (f) at index 0.


static void
rvv_vslideup_vx(int32_t *rslt, int32_t *src,int32_t *dst, size_t vl ,size_t offset)
{
    vint32m1_t vsrc = __riscv_vle32_v_i32m1(src, vl);
    vint32m1_t vdst = __riscv_vle32_v_i32m1(dst, vl);
    vint32m1_t vrslt = __riscv_vslideup_vx_i32m1(vdst, vsrc, offset, vl);
    __riscv_vse32_v_i32m1(rslt, vrslt, vl);
}
static void
rvv_vslideup_vx_bf(int32_t *rslt, int32_t *src,int32_t *dst, size_t vl ,size_t offset)
{
    int i;
    for(i=0;i<offset;i++)rslt[i]= dst[i];
    for(i=offset;i<vl;i++) rslt[i] = src[i-offset];
}

extern bool
test_vslideup(int debug)
{
    int32_t src[MAX_ELEMENTS];
    int32_t dst[MAX_ELEMENTS] = { 0 };
    int32_t rslt[MAX_ELEMENTS] = { 0 };
    int32_t rslt_bf[MAX_ELEMENTS] = { 0 };
    int i;
    int offset;
    
    size_t vl = __riscv_vsetvl_e32m1(MAX_ELEMENTS);
    
    init_vectors_i32(src,MAX_ELEMENTS,true);
    init_vectors_i32(dst,MAX_ELEMENTS,false);

    offset=3;
    printf("Testing vslideup wth offset = %d and vlen = %d", offset,vl);
    for(i=0; i<MAX_ELEMENTS;i=i+vl) {
        rvv_vslideup_vx_bf(&rslt_bf[i], &src[i],&dst[i],vl,offset);
        rvv_vslideup_vx(&rslt[i], &src[i],&dst[i],vl,offset);
        i+=vl;
    }
    if(compare_array_i(rslt,rslt_bf,MAX_ELEMENTS,false))
        printf(":-)\n");
    else
        printf(":-(\n");

    offset=0;
    printf("Testing vslideup wth offset = %d and vlen = %d", offset,vl);
    for(i=0; i<MAX_ELEMENTS;i=i+vl) {
        rvv_vslideup_vx_bf(&rslt_bf[i], &src[i],&dst[i],vl,offset);
        rvv_vslideup_vx(&rslt[i], &src[i],&dst[i],vl,offset);
        i+=vl;
    }
    if(compare_array_i(rslt,rslt_bf,MAX_ELEMENTS,false))
        printf(":-)\n");
    else
        printf(":-(\n");

    offset=2;
    printf("Testing vslideup wth offset = %d and vlen = %d", offset,vl);
    for(i=0; i<MAX_ELEMENTS;i=i+vl) {
        rvv_vslideup_vx_bf(&rslt_bf[i], &src[i],&dst[i],vl,offset);
        rvv_vslideup_vx(&rslt[i], &src[i],&dst[i],vl,offset);
        i+=vl;
    }
    if(compare_array_i(rslt,rslt_bf,MAX_ELEMENTS,false))
        printf(":-)\n");
    else
        printf(":-(\n");

    offset=1;
    printf("Testing vslideup wth offset = %d and vlen = %d", offset,vl);
    for(i=0; i<MAX_ELEMENTS;i=i+vl) {
        rvv_vslideup_vx_bf(&rslt_bf[i], &src[i],&dst[i],vl,offset);
        rvv_vslideup_vx(&rslt[i], &src[i],&dst[i],vl,offset);
        i+=vl;
    }
    if(compare_array_i(rslt,rslt_bf,MAX_ELEMENTS,false))
        printf(":-)\n");
    else
        printf(":-(\n");
}
