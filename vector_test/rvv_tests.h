#ifndef _RVV_TESTS_H
#define _RVV_TESTS_H
#include <stdbool.h>
#ifndef _MAX_ELEMENTS
#define MAX_ELEMENTS 16 // Can be changed later depending on vlen and dlen
#endif

bool test_addf(void);
bool test_addi(void);

bool test_subf(void);
bool test_subi(void);

bool test_mulf(void);
bool test_muli(void);

bool test_mini(void);
bool test_maxi(void);
bool test_cmpf(void);


#endif
