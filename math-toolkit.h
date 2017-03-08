#ifndef __RAY_MATH_TOOLKIT_H
#define __RAY_MATH_TOOLKIT_H

#define ADDRESS_HI 0xffffffffffffffff
#define ADDRESS_LOW 0x0000000000000000

#include <math.h>
#include <stdio.h>
#include <assert.h>
#include <immintrin.h>

static inline __attribute__ ((always_inline))
void normalize(double *v)
{
    double d = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    assert(d != 0.0 && "Error calculating normal");

    v[0] /= d;
    v[1] /= d;
    v[2] /= d;
}

static inline __attribute__ ((always_inline))
double length(const double *v)
{
    return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

static inline __attribute__ ((always_inline))
void add_vector(const double *a, const double *b, double *out)
{
    __m256i mask = _mm256_set_epi64x(ADDRESS_LOW, ADDRESS_HI, ADDRESS_HI, ADDRESS_HI);
    __m256d c = _mm256_loadu_pd(a);
    __m256d d = _mm256_loadu_pd(b);
    __m256d dst = _mm256_add_pd(c, d);
    _mm256_maskstore_pd(out, mask, dst);
}

static inline __attribute__ ((always_inline))
void subtract_vector(const double *a, const double *b, double *out)
{
    __m256i mask = _mm256_set_epi64x(ADDRESS_LOW, ADDRESS_HI, ADDRESS_HI, ADDRESS_HI);
    __m256d c = _mm256_loadu_pd(a);
    __m256d d = _mm256_loadu_pd(b);
    __m256d dst = _mm256_sub_pd(c, d);
    _mm256_maskstore_pd(out, mask, dst);
}

static inline __attribute__ ((always_inline))
void multiply_vectors(const double *a, const double *b, double *out)
{
    __m256i mask = _mm256_set_epi64x(ADDRESS_LOW, ADDRESS_HI, ADDRESS_HI, ADDRESS_HI);
    __m256d c = _mm256_loadu_pd(a);
    __m256d d = _mm256_loadu_pd(b);
    __m256d dst = _mm256_mul_pd(c, d);
    _mm256_maskstore_pd(out, mask, dst);
}

static inline __attribute__ ((always_inline))
void multiply_vector(const double *a, double b, double *out)
{
    __m256i mask = _mm256_set_epi64x(ADDRESS_LOW, ADDRESS_HI, ADDRESS_HI, ADDRESS_HI);
    __m256d c = _mm256_loadu_pd(a);
    __m256d d = _mm256_set_pd(b, b, b, b);
    __m256d dst = _mm256_mul_pd(c, d);
    _mm256_maskstore_pd(out, mask, dst);
}

static inline __attribute__ ((always_inline))
void cross_product(const double *v1, const double *v2, double *out)
{
    __m256i mask = _mm256_set_epi64x(ADDRESS_LOW, ADDRESS_HI, ADDRESS_HI, ADDRESS_HI);
    __m256d c = _mm256_set_pd(0.0, v1[0], v1[2], v1[1]);
    __m256d d = _mm256_set_pd(0.0, v2[1], v2[0], v2[2]);
    __m256d dst_1 = _mm256_mul_pd(c, d);

    __m256d e = _mm256_set_pd(0.0, v1[1], v1[0], v1[2]);
    __m256d f = _mm256_set_pd(0.0, v2[0], v2[2], v2[1]);
    __m256d dst_2 = _mm256_mul_pd(e, f);

    __m256d dst_3 = _mm256_sub_pd(dst_1, dst_2);
    _mm256_maskstore_pd(out, mask, dst_3);
}

static inline __attribute__ ((always_inline))
double dot_product(const double *v1, const double *v2)
{
    double out[4];
    __m256i mask = _mm256_set_epi64x(ADDRESS_LOW, ADDRESS_HI, ADDRESS_HI, ADDRESS_HI);
    __m256d c = _mm256_loadu_pd(v1);
    __m256d d = _mm256_loadu_pd(v2);
    __m256d dst = _mm256_mul_pd(c, d);
    _mm256_maskstore_pd(&out[0], mask, dst);

    return out[0] + out[1] + out[2];
}

static inline __attribute__ ((always_inline))
void scalar_triple_product(const double *u, const double *v, const double *w,
                           double *out)
{
    cross_product(v, w, out);
    multiply_vectors(u, out, out);
}

static inline __attribute__ ((always_inline))
double scalar_triple(const double *u, const double *v, const double *w)
{
    double tmp[3];
    cross_product(w, u, tmp);
    return dot_product(v, tmp);
}

#endif
