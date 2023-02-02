//
// Created by Lluís Merlos Pieri on 2/12/22.
//
#include "file_reader.h"

#include "cvec.h"

int main_a(file_t *f) {


  cvec_t fst = cvec_new(0, sizeof(int), NULL);

  int a = 0;
  while (load_line(f)) {
    cvec_add(&fst, &a);
    a++;

    CVEC_PRINTF(fst, int, "%02d", -1)
  }

  return 0;
}


//
// PART B
//

int main_b(file_t *f) {
  
  while (load_line(f)) {

  }

  return 0;
}
