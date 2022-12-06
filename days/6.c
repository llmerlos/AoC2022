//
// Created by Lluís Merlos Pieri on 6/12/22.
//
#include "file_reader.h"

bool is_message(char *p, int len) {
  unsigned int status = 0;

  for (int i = 1 - len; i <= 0; i++) {
    if (status & (1u << (p[i] - 'a'))) {
      return false;
    } else {
      status |= (1u << (p[i] - 'a'));
    }
  }

  return true;
}

int main_a(file_t *f) {
  int len = 4;

  while (load_line(f)) {
    for (int i = len - 1; i < f->read; i++)
      if (is_message(&f->line[i], len)) {
        return i + 1;
      }
  }

  return -1;
}


//
// PART B
//

int main_b(file_t *f) {
  int len = 14;

  while (load_line(f)) {
    for (int i = len - 1; i < f->read; i++)
      if (is_message(&f->line[i], len)) {
        return i + 1;
      }
  }

  return -1;
}
