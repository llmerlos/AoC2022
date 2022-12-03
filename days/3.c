//
// Created by Lluís Merlos Pieri on 3/12/22.
//
#include "file_reader.h"

#define UPPER_OFFSET ('Z' - 'A' + 1)

typedef unsigned long compartment_t;

int get_index_from(char type) {
  bool is_lower = (type >= 'a' && type <= 'z');
  return (is_lower ? type - 'a' : type - 'A' + UPPER_OFFSET) + 1;
}

compartment_t get_compartment_elements_from(char *types, int length) {
  compartment_t c = 0;

  for (int i = 0; i < length; i++) {
    c |= ((compartment_t) 1 << get_index_from(types[i]));
  }

  return c;
}

int get_priority_from(compartment_t combined) {

  for (int i = 1; i <= UPPER_OFFSET * 2; i++) {
    if (combined & ((compartment_t) 1 << i)) {
      return i;
    }
  }

  return 0;
}

int main_a(file_t *f) {
  int priority_sum = 0;

  while (load_line(f)) {
    int compartment_size = (f->read - 1) / 2;

    compartment_t fst_half = get_compartment_elements_from(f->line, compartment_size);
    compartment_t scd_half = get_compartment_elements_from(&f->line[compartment_size], compartment_size);

    priority_sum += get_priority_from(fst_half & scd_half);
  }

  return priority_sum;
}


//
// PART B
//

#define GROUP_SIZE 3

int main_b(file_t *f) {
  int priority_sum = 0;

  int group_member = 0;
  compartment_t rolling_compartment = (compartment_t) ~0;
  while (load_line(f)) {

    rolling_compartment &= get_compartment_elements_from(f->line, f->read - 1);

    if (group_member++ % GROUP_SIZE == GROUP_SIZE - 1) {
      priority_sum += get_priority_from(rolling_compartment);
      rolling_compartment = (compartment_t) ~0;
    }
  }

  return priority_sum;
}
