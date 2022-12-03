//
// Created by Lluís Merlos Pieri on 1/12/22.
//
#include "file_reader.h"

int main_a(file_t *f) {
  int max_calories = 0;
  int cur_calories = 0;

  while (load_line(f)) {
    if (f->read > 1) {
      cur_calories += atoi(f->line);
    } else {
      if (cur_calories > max_calories) {
        max_calories = cur_calories;
      }
      cur_calories = 0;
    }
  }

  return max_calories;
}

//
//  PART B
//

int min(int *top, int n_elem) {
  int ind = 0;
  int min = top[0];

  for (int i = 1; i < n_elem; i++) {
    if (top[i] < min) {
      min = top[i];
      ind = i;
    }
  }

  return ind;
}

int main_b(file_t *f) {
  int max_calories[3] = {0};
  int cur_calories = 0;

  while (load_line(f)) {
    if (f->read > 1) {
      cur_calories += atoi(f->line);
    } else {
      int ind_min = min(max_calories, 3);
      if (cur_calories > max_calories[ind_min]) {
        max_calories[ind_min] = cur_calories;
      }
      cur_calories = 0;
    }
  }

  int top3_cal = max_calories[0] + max_calories[1] + max_calories[2];
  return top3_cal;
}
