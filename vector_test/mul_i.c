#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <riscv_vector.h>
#include "rvv_tests.h"
#include "util.h"

int
static rvv_muli_vv( int a[], int b[], int c[],int n)
{
    size_t vl=0;
    size_t i=0;
    while(n>0) {
        size_t vl = __riscv_vsetvl_e32m1(MAX_ELEMENTS - i);
        vint32m1_t va = __riscv_vle32_v_i32m1((const long int *)&a[i], vl);
        vint32m1_t vb = __riscv_vle32_v_i32m1((const long int *)&b[i], vl);
        vint32m1_t vc = __riscv_vmul_vv_i32m1(va, vb, vl);
        __riscv_vse32_v_i32m1((unsigned long int *)&c[i], vc, vl);                      
        n-=vl;
        i+=vl;
    }
    return 0;
}
int
static rvv_muli_vc( int a[], int factor, int c[],int n)
{
    size_t vl=0;
    size_t i=0;
    while(n>0) {
        size_t vl = __riscv_vsetvl_e32m1(MAX_ELEMENTS - i);
        vint32m1_t va = __riscv_vle32_v_i32m1((const long int *)&a[i], vl);
        vint32m1_t vc = __riscv_vmul_vx_i32m1(va, factor, vl);
        __riscv_vse32_v_i32m1((unsigned long int *)&c[i], vc, vl);                      
        n-=vl;
        i+=vl;
    }
    return 0;
}
static int
rvv_muli_svv(int a[], int b[], int c[],int n)
{
    int i;
    for(i=0;i<n;i++) {
        c[i]=a[i]*b[i];
    }
    return 0;
}
static int
rvv_muli_svc(int a[],int factor , int c[],int n)
{
    int i;
    for(i=0;i<n;i++) {
        c[i]=a[i]*factor;
    }
    return 0;
}


static bool
check_muli_vv(int c_v[], int c_s[], int n)
{
    int i;
    for(i=0;i<n;i++) {
        if (c_v[i] != c_s[i]) return false;
    }
    return true;
}

bool 
test_muli(void) 
{
    int a[MAX_ELEMENTS], b[MAX_ELEMENTS], c_v[MAX_ELEMENTS],c_s[MAX_ELEMENTS];
    int factor = 0.5;
    init_vectorsi(a,b,MAX_ELEMENTS);
    rvv_muli_vv(a,b,c_v,MAX_ELEMENTS);
    rvv_muli_svv(a,b,c_s,MAX_ELEMENTS);
    if (!check_muli_vv(c_v,c_s,MAX_ELEMENTS)) {
        printf("Int Vector-vector Failed. \n");
        print_result_i(c_v,c_s,MAX_ELEMENTS);
        return false;
    }
    printf("Int Vector -Vector Multiplication succesful \n");
    rvv_muli_vc(a, factor,c_v,MAX_ELEMENTS);
    rvv_muli_svc(a, factor,c_s,MAX_ELEMENTS);
    if (!check_muli_vv(c_v,c_s,MAX_ELEMENTS)) {
        printf("Int Vector-Constant Failed. \n");
        print_result_i(c_v,c_s,MAX_ELEMENTS);
        return false;
    }
    
    return true;
}
