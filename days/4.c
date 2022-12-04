//
// Created by Lluís Merlos Pieri on 4/12/22.
//
#include "file_reader.h"

typedef struct {
  ssize_t min;
  ssize_t max;
} range_t;

ssize_t find_char_and_replace_in(char *str, size_t len, char token, char replacement) {
  for (size_t i = 0; i < len; i++) {
    if (str[i] == token) {
      str[i] = replacement;
      return i;
    }
  }
  return -1;
}

range_t get_range_from(char *str, size_t len) {
  ssize_t separator_loc = find_char_and_replace_in(str, len, '-', '\n');
  range_t range = {
    .min = atoi(str),
    .max = atoi(&str[separator_loc + 1])};

  return range;
}

bool is_range_total_overlapping(range_t fst, range_t scd) {
  if (fst.min <= scd.min && fst.max >= scd.max) return true;
  if (scd.min <= fst.min && scd.max >= fst.max) return true;

  return false;
}

int main_a(file_t *f) {
  int count = 0;

  while (load_line(f)) {
    ssize_t comma_loc = find_char_and_replace_in(f->line, f->read, ',', '\n');

    range_t fst = get_range_from(f->line, comma_loc);
    range_t scd = get_range_from(&f->line[comma_loc + 1], f->read - comma_loc - 1);

    if (is_range_total_overlapping(fst, scd)) count++;
  }

  return count;
}


//
// PART B
//

bool is_in_range(ssize_t value, range_t range) {
  return (value >= range.min && value <= range.max);
}

bool is_range_partial_overlapping(range_t fst, range_t scd) {
  return is_in_range(fst.min, scd) || is_in_range(fst.max, scd);
}

int main_b(file_t *f) {
  int count = 0;

  while (load_line(f)) {
    ssize_t comma_loc = find_char_and_replace_in(f->line, f->read, ',', '\n');

    range_t fst = get_range_from(f->line, comma_loc);
    range_t scd = get_range_from(&f->line[comma_loc + 1], f->read - comma_loc - 1);

    if (is_range_partial_overlapping(fst, scd) || is_range_total_overlapping(fst, scd)) count++;
  }

  return count;
}
