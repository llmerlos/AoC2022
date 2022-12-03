//
// Created by Lluís Merlos Pieri on 2/12/22.
//
#include "file_reader.h"
#include <stdio.h>

extern int main_a(file_t *f);
extern int main_b(file_t *f);

int main() {
  file_t f = load_file(INPUT_PATH);
  int result_a = main_a(&f);
  free_file(&f);
  printf("A: %d\n", result_a);


  f = load_file(INPUT_PATH);
  int result_b = main_b(&f);
  free_file(&f);
  printf("B: %d\n", result_b);

  return 0;
}