#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <riscv_vector.h>
#include "rvv_tests.h"
#include "util.h"

// Primitives available
//Integer
// vmseq.vv - Equal 
// vmslt.vv - Less than
// vmsgt.vv - Greater than
// vmslt.vx - Vector to Scalar
//Floating
// vmfeq.vv - Equal 
// vmflt.vv - Less than
// vmfgt.vv - Greater than
// vmflt.vx - Vector to Scalar


//Doing Compare test Vector Floating
static int
rvv_cmpf32_v(float a[], float b[],size_t n)
{
    size_t i=0;
    uint32_t bits=0;
    while(i<n) {
        size_t vl = __riscv_vsetvl_e32m1(n - i);
        vfloat32m1_t va = __riscv_vle32_v_f32m1(&a[i], vl);
        vfloat32m1_t vb = __riscv_vle32_v_f32m1(&b[i], vl);
        vbool32_t m = __riscv_vmflt_vv_f32m1_b32(va, vb, vl);  // A < B ?
        bits += __riscv_vcpop_m_b32(m, vl); 
        i+=vl;
    }
    return bits;
}
static int 
rvv_cmpf32_bf(float a[], float b[],size_t n)
{
    uint32_t bits=0;
    for(int i=0;i<n;i++) { 
        if (a[i] < b[i]) bits++;
    }
    return bits;
}
extern bool
test_cmpf32_vv(int debug)
{
    float a[MAX_ELEMENTS];
    float b[MAX_ELEMENTS];
    uint32_t bits1,bits2;
    
    printf("Testing Vector Vector f32 Comparison: ");
    init_vectors_f32(a,MAX_ELEMENTS,true);
    init_vectors_f32(b,MAX_ELEMENTS,true);

    bits1=rvv_cmpf32_v(a,b,MAX_ELEMENTS);
    bits2=rvv_cmpf32_bf(a,b,MAX_ELEMENTS);
    
    if (bits1!=bits2) {
        printf(":-( \n");
        return false;
    }
    printf(":-) \n");
    return true;
}
//Doing Compare test Integer Vector
static int
rvv_cmpi32_v(int32_t a[], int32_t b[],size_t n)
{
    size_t i=0;
    uint32_t bits=0;
    while(i<n) {
        size_t vl = __riscv_vsetvl_e32m1(n - i);
        vint32m1_t va = __riscv_vle32_v_i32m1(&a[i], vl);
        vint32m1_t vb = __riscv_vle32_v_i32m1(&b[i], vl);
        vbool32_t m = __riscv_vmseq_vv_i32m1_b32(va, va, vl);  // A < B ?
        bits += __riscv_vcpop_m_b32(m, vl); 
        i+=vl;
    }
    return bits;
}
static int 
rvv_cmpi32_bf(int32_t a[], int32_t b[],size_t n)
{
    uint32_t bits=0;
    for(int i=0;i<n;i++) { 
        if (a[i] == a[i]) bits++;
    }
    return bits;
}
extern bool
test_cmpi32_vv(int debug)
{
    int32_t a[MAX_ELEMENTS];
    int32_t b[MAX_ELEMENTS];
    uint32_t bits1,bits2;
    
    printf("Testing Vector Vector i32 Comparison: ");
    init_vectors_i32(a,MAX_ELEMENTS,true);
    init_vectors_i32(b,MAX_ELEMENTS,true);

    bits1=rvv_cmpi32_v(a,a,MAX_ELEMENTS);
    bits2=rvv_cmpi32_bf(a,a,MAX_ELEMENTS);
    
    if (bits1!=bits2) {
        printf(":-( \n");
        return false;
    }
    printf(":-) \n");
    return true;
}
//Doing Compare test Integer Vector and Scalar
static int
rvv_cmpi32_vs(int32_t a[], int32_t scalar ,size_t n)
{
    size_t i=0;
    uint32_t bits=0;
    while(i<n) {
        size_t vl = __riscv_vsetvl_e32m1(n - i);
        vint32m1_t va = __riscv_vle32_v_i32m1(&a[i], vl);
        vbool32_t m = __riscv_vmslt_vx_i32m1_b32(va, scalar, vl);  // A < B ?
        bits += __riscv_vcpop_m_b32(m, vl); 
        i+=vl;
    }
    return bits;
}
static int 
rvv_cmpi32_vs_bf(int32_t a[], int32_t scalar,size_t n)
{
    uint32_t bits=0;
    for(int i=0;i<n;i++) { 
        if (a[i] < scalar) bits++;
    }
    return bits;
}
extern bool
test_cmpi32_vs(int debug)
{
    int32_t a[MAX_ELEMENTS];
    uint32_t bits1,bits2;
    int32_t scalar = SCALAR_I;
    
    printf("Testing Vector Scalar i32 Comparison: ");
    init_vectors_i32(a,MAX_ELEMENTS,true);

    bits1=rvv_cmpi32_vs(a,scalar,MAX_ELEMENTS);
    bits2=rvv_cmpi32_vs_bf(a,scalar,MAX_ELEMENTS);
    
    if (bits1!=bits2) {
        printf(":-( \n");
        return false;
    }
    printf(":-) \n");
    return true;
}
//Doing Compare test Float Vector and Scalar
static int
rvv_cmpf32_vs(float a[], float scalar ,size_t n)
{
    size_t i=0;
    uint32_t bits=0;
    while(i<n) {
        size_t vl = __riscv_vsetvl_e32m1(n - i);
        vfloat32m1_t va = __riscv_vle32_v_f32m1(&a[i], vl);
        vbool32_t m = __riscv_vmflt_vf_f32m1_b32(va, scalar, vl);  // A < B ?
        bits += __riscv_vcpop_m_b32(m, vl); 
        i+=vl;
    }
    return bits;
}
static int 
rvv_cmpf32_vs_bf(float a[], int32_t scalar,size_t n)
{
    uint32_t bits=0;
    for(int i=0;i<n;i++) { 
        if (a[i] < scalar) bits++;
    }
    return bits;
}
extern bool
test_cmpf32_vs(int debug)
{
    float a[MAX_ELEMENTS];
    uint32_t bits1,bits2;
    int32_t scalar = SCALAR_F;
    
    printf("Testing Vector Scalar f32 Comparison: ");
    init_vectors_f32(a,MAX_ELEMENTS,true);

    bits1=rvv_cmpf32_vs(a,scalar,MAX_ELEMENTS);
    bits2=rvv_cmpf32_vs_bf(a,scalar,MAX_ELEMENTS);
    
    if (bits1!=bits2) {
        printf(":-( \n");
        return false;
    }
    printf(":-) \n");
    return true;
}
