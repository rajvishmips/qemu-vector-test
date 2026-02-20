#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <riscv_vector.h>
#include "rvv_tests.h"
#include "util.h"

int 
main(void) 
{
    int debug=0;
    srand(time(NULL));
    test_addi32_vv(debug);
    test_addf32_vv(debug);
    test_cmpf32_vv(debug);
    test_cmpi32_vv(debug);
    test_cmpi32_vs(debug);
    test_cmpf32_vs(debug);
    test_muli32_vv(debug);
    test_muli32_vs(debug);
    test_divi32_vv(debug);
    test_divi32_vv_m(debug);
    test_divf32_vv(debug);
    test_maxi32_vv(debug);
    test_mulf32_vf(debug);
    test_vfredmax(debug);
    test_vfmacc_vv(debug);
    test_vredsum(debug);
    test_vslideup(debug);
    test_vrgather(debug);
}
