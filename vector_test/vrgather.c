#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <riscv_vector.h>
#include "rvv_tests.h"
#include "util.h"

static int
rvv_vrgather_vv(int32_t *dest, int32_t *src, uint32_t *idx,size_t vl)
{
    vint32m1_t vsrc = __riscv_vle32_v_i32m1(src, vl);
    vuint32m1_t vidx = __riscv_vle32_v_u32m1(idx, vl);
    vint32m1_t vdest = __riscv_vrgather_vv_i32m1(vsrc,vidx,vl);
    __riscv_vse32_v_i32m1(dest, vdest, vl);
    return 0;
}
static int32_t
rvv_vrgather_bf(int32_t *dest, int32_t *src, uint32_t *idx,size_t vl)
{
    for(int i=0;i<vl;i++) {
        idx[i]<vl?dest[i] =src[idx[i]]:0;
    }
}
extern bool
test_vrgather(int debug)
{
    int32_t src[MAX_ELEMENTS];
    uint32_t idx[MAX_ELEMENTS];
    int32_t dest[MAX_ELEMENTS];
    int32_t dest_bf[MAX_ELEMENTS];
    size_t vl = __riscv_vsetvl_e32m1(MAX_ELEMENTS);
    init_vectors_i32(src,vl,true);
    
    //Let us reverse the order
    int j=0;
    for(int i=vl-1;i>=0;i--){
        idx[j++]=i;
    }
    rvv_vrgather_vv(dest,src,idx,vl);
    rvv_vrgather_vv(dest_bf,src,idx,vl);
    
    for(int i=0;i<vl;i++) {
        printf("%2d %d %d %d \n",i,src[i],dest[i],dest_bf[i]);
    }
    printf("%d %d %d \n",src[vl-1],dest[0],dest_bf[0]);
}

