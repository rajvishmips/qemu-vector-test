#ifndef _UTIL_H
#define UTIL_H
#include <stdbool.h>
extern int init_vectorsf(float a[],float b[], int n);
extern int init_vectorsi(int a[],int b[], int n);
extern void print_result_f( float c_v[], float c_s[], int n);
extern void print_result_i( int c_v[], int c_s[], int n);
extern bool check_array_i(int c_v[], int c_s[], int n);
extern bool check_array_f(float c_v[], float c_s[], int n);
#endif
