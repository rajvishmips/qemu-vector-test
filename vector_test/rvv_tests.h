#ifndef _RVV_TESTS_H
#define _RVV_TESTS_H
#include <stdbool.h>
#ifndef _MAX_ELEMENTS
#define MAX_ELEMENTS 64 // Can be changed later depending on vlen and dlen
#endif
#ifndef SCALAR_I
#define SCALAR_I 10
#endif
#ifndef SCALAR_F
#define SCALAR_F 10.0
#endif
// Functions
extern bool test_addi32_vv(int debug);
extern bool test_addf32_vv(int debug);
extern bool test_cmpf32_vv(int debug);
extern bool test_cmpi32_vv(int debug);
extern bool test_cmpi32_vs(int debug);
extern bool test_cmpf32_vs(int debug);
extern bool test_muli32_vv(int debug);
extern bool test_muli32_vs(int debug);
extern bool test_divi32_vv(int debug);
extern bool test_divi32_vv_m(int debug);
extern bool test_divf32_vv(int debug);
extern bool test_maxi32_vv(int debug);
extern bool test_mulf32_vf(int debug);
extern bool test_vfredmax(int debug);
extern bool test_vfmacc_vv(int debug);
extern bool test_vredsum(int debug);
extern bool test_vslideup(int debug);
extern bool test_vrgather(int debug);

#endif
