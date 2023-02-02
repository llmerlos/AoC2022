//
// Created by Lluís Merlos Pieri on 13/12/22.
//

#ifndef AOC2022_CVEC_H
#define AOC2022_CVEC_H

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum cvec_err {
  CVECERR_OK = 0,
  CVECERR_ERR = 1
};

typedef struct {
  size_t element_capacity;
  size_t element_count;
  size_t element_size;
  bool is_static;
  void *raw;
} cvec_t;

cvec_t cvec_new(size_t element_count, size_t element_size, void *buff);
cvec_t cvec_cpy(cvec_t *v, void *buff);
void cvec_free(cvec_t *v);

enum cvec_err cvec_add(cvec_t *v, void *src);
enum cvec_err cvec_add_n(cvec_t *v, void *src, size_t n);

enum cvec_err cvec_insert_nth(cvec_t *v, size_t nth, void *src);
enum cvec_err cvec_insert_n_nth(cvec_t *v, size_t nth, void *src, size_t n);

enum cvec_err cvec_set_nth(cvec_t *v, size_t nth, void *src);
enum cvec_err cvec_set_nth_to_mth(cvec_t *v, size_t nth, size_t mth, void *src);

enum cvec_err cvec_get_nth(cvec_t *v, size_t nth, void *dst);
enum cvec_err cvec_get_nth_to_mth(cvec_t *v, size_t nth, size_t mth, void *dst);
enum cvec_err cvec_get_last(cvec_t *v, void *dst);

enum cvec_err cvec_del_nth(cvec_t *v, size_t nth, void *dst);
enum cvec_err cvec_del_nth_to_mth(cvec_t *v, size_t nth, size_t mth, void *dst);
enum cvec_err cvec_del_last(cvec_t *v, void *dst);

#define CVEC_PRINTF(v, typ, fmt, max)                 \
  size_t ___elements = (size_t) max;                  \
  if (max < 0) {                                      \
    ___elements = v.element_count;                    \
  }                                                   \
                                                      \
  printf("V:[ ");                                     \
  for (size_t ___i = 0; ___i < ___elements; ___i++) { \
    typ ___v;                                         \
    cvec_get_nth(&v, ___i, &___v);                    \
    printf(fmt, ___v);                                \
    printf(" , ");                                    \
  }                                                   \
  printf("]\n");

#endif//AOC2022_CVEC_H
