//
// Created by Lluís Merlos Pieri on 13/12/22.
//
#include "cvec.h"


void *_cvec_ptr_to_nth(cvec_t *v, size_t nth) {
  return (void *) ((uint8_t *) v->raw + (nth * v->element_size));
}

void _cvec_resize(cvec_t *v, size_t element_capacity) {
  assert(v != NULL);
  assert(v->raw != NULL);
  assert(v->is_static == false);

  v->element_capacity = element_capacity;

  v->raw = realloc(v->raw, v->element_capacity * v->element_size);
}

cvec_t cvec_new(size_t element_count, size_t element_size, void *buff) {
  cvec_t v = (cvec_t){
    .element_capacity = element_count,
    .element_count = 0,
    .element_size = element_size,
    .is_static = true,
    .raw = NULL};

  if (buff != NULL) {
    v.raw = buff;
  } else {
    v.is_static = false;
    v.raw = malloc(element_count * element_size);
  }

  return v;
}

cvec_t cvec_cpy(cvec_t *v, void *buff) {
  assert(v != NULL);

  cvec_t b = cvec_new(v->element_count, v->element_size, buff);
  cvec_set_nth_to_mth(&b, 0, v->element_count, v->raw);

  return b;
}

void cvec_free(cvec_t *v) {
  assert(v != NULL);

  if (!v->is_static && v->raw != NULL) {
    free(v->raw);
  }
}

enum cvec_err cvec_add(cvec_t *v, void *src) {
  return cvec_add_n(v, src, 1);
}

enum cvec_err cvec_add_n(cvec_t *v, void *src, size_t n) {
  return cvec_insert_n_nth(v, v->element_count, src, n);
}

enum cvec_err cvec_insert_nth(cvec_t *v, size_t nth, void *src) {
  return cvec_insert_n_nth(v, nth, src, 1);
}

enum cvec_err cvec_insert_n_nth(cvec_t *v, size_t nth, void *src, size_t n) {
  assert(v != NULL);
  assert(src != NULL);

  if ((v->element_count + n) > v->element_capacity) {
    if (v->is_static) {
      return CVECERR_ERR;
    } else {
      _cvec_resize(v, v->element_capacity + n);
    }
  }

  void *cvec_src = _cvec_ptr_to_nth(v, nth);
  void *cvec_dst = _cvec_ptr_to_nth(v, nth + n);

  memmove(cvec_dst, cvec_src, n * v->element_size);

  void *dst = cvec_src;
  memcpy(dst, src, n * v->element_size);
  v->element_count += n;

  return CVECERR_OK;
}

enum cvec_err cvec_set_nth(cvec_t *v, size_t nth, void *src) {
  return cvec_set_nth_to_mth(v, nth, nth + 1, src);
}

enum cvec_err cvec_set_nth_to_mth(cvec_t *v, size_t nth, size_t mth, void *src) {
  assert(v != NULL);
  assert(src != NULL);

  if (nth >= mth) {
    return CVECERR_ERR;
  }

  if ((mth - 1) >= v->element_capacity) {
    if (v->is_static) {
      return CVECERR_ERR;
    } else {
      _cvec_resize(v, mth);
    }
  }

  void *dst = _cvec_ptr_to_nth(v, nth);
  memmove(dst, src, (mth - nth) * v->element_size);
  if (mth > v->element_count) {
    v->element_count = mth;
  }

  return CVECERR_OK;
}

enum cvec_err cvec_get_nth(cvec_t *v, size_t nth, void *dst) {
  return cvec_get_nth_to_mth(v, nth, nth + 1, dst);
}

enum cvec_err cvec_get_nth_to_mth(cvec_t *v, size_t nth, size_t mth, void *dst) {
  assert(v != NULL);
  assert(dst != NULL);

  if (nth >= mth) {
    return CVECERR_ERR;
  }

  if ((mth - 1) >= v->element_capacity) {
    return CVECERR_ERR;
  }

  void *src = _cvec_ptr_to_nth(v, nth);
  memmove(dst, src, (mth - nth) * v->element_size);

  return CVECERR_OK;
}
enum cvec_err cvec_get_last(cvec_t *v, void *dst) {
  return cvec_get_nth(v, v->element_count - 1, dst);
}

enum cvec_err cvec_del_nth(cvec_t *v, size_t nth, void *dst) {
  return cvec_del_nth_to_mth(v, nth, nth + 1, dst);
}

enum cvec_err cvec_del_nth_to_mth(cvec_t *v, size_t nth, size_t mth, void *dst) {
  assert(v != NULL);

  if (nth >= mth) {
    return CVECERR_ERR;
  }

  if ((mth - 1) >= v->element_capacity) {
    return CVECERR_ERR;
  }

  if (dst != NULL) {
    cvec_get_nth_to_mth(v, nth, mth, dst);
  }

  if (mth < v->element_capacity) {
    void *cvec_dst = _cvec_ptr_to_nth(v, nth);
    void *cvec_src = _cvec_ptr_to_nth(v, mth);

    memmove(cvec_dst, cvec_src, (mth - nth) * v->element_size);
  }

  v->element_count -= mth - nth;

  return CVECERR_OK;
}

enum cvec_err cvec_del_last(cvec_t *v, void *dst) {
  return cvec_del_nth(v, v->element_count - 1, dst);
}
