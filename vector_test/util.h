#ifndef _UTIL_H
#define UTIL_H
#include <stdbool.h>
#include <stdint.h>
extern int init_vectorsf(float a[],float b[], int n);
extern int init_vectorsi(int a[],int b[], int n);
extern bool init_mask(int32_t mask[],int n);
extern int print_result_f( float c_v[], float c_s[], int n);
extern int print_result_i( int c_v[], int c_s[], int n);
extern bool check_array_i(int c_v[], int c_s[], int n);
extern bool check_array_im(int c_v[], int c_s[], int n);
extern bool check_array_f(float c_v[], float c_s[], int n);
extern void print_vector_i(int32_t *a, int32_t n);

#define EPSILON 1e-6f
#define FLOAT_EQ_ABS(a, b) \
    (fabs((a) - (b)) <= (EPSILON))

void init_vectors_i8(int8_t *a,int n, bool random);
void init_vectors_i16(int16_t *a,int n, bool random);
void init_vectors_i32(int32_t *a,int n, bool random);
void init_vectors_i64(int32_t *a,int n, bool random);
void init_vectors_f16(_Float16 *a,int n, bool random);
void init_vectors_f32(float *a,int n, bool random);
void init_vectors_f64(double *a,int n, bool random);

bool compare_array_i(int32_t *a1,int32_t *a2, int n,int debug);
bool compare_array_im(int32_t *a1,int32_t *a2, int32_t *mask,int n,int debug);
bool compare_array_f(float a1[], float a2[], int n,int debug);
#endif
