#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <riscv_vector.h>
#include "rvv_tests.h"
#include "util.h"

int 
main(void) 
{
    test_addf();
    test_addi();
    test_subf();
    test_subi();
    test_mulf();
    test_muli();
    test_mini();
    test_cmpf();
}
