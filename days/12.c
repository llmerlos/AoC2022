//
// Created by Lluís Merlos Pieri on 12/12/22.
//
#include "file_reader.h"
#include "string.h"

#define MAX_ROWS 50

typedef struct {
  char * rows[MAX_ROWS];
  int nr, nc;
} mountain_t;

mountain_t new_mountain() {
  mountain_t m = (mountain_t) {
    .rows = {0},
    .nr = 0,
    .nc = 0
  };

  return m;
}

void free_mountain(mountain_t * m) {
  for (int i = 0; i < m->nr; i++) {
    free(m->rows[i]);
  }
}

void add_row(mountain_t * m, char * row) {
   char * internal_row = malloc(sizeof (char) * m->nc);
   memcpy(internal_row, row, sizeof (char) * m->nc);
   m->rows[m->nr++] = internal_row;
}

char get_from(mountain_t * m, int x, int y) {
  char res = 0;
  if (y >= 0 && y < m->nr && x >= 0 && x <= m->nc) {
    res = m->rows[y][x];
  }

  return res;
}


int main_a(file_t *f) {
  mountain_t m = new_mountain();

  load_line(f);
  m.nc = f->read - 1;
  add_row(&m, f->line);

  while (load_line(f)) {
    add_row(&m, f->line);
  }

  for(int y = 0; y < m.nr; y++) {
    for (int x = 0; x < m.nc; x++) {
      printf("%c", get_from(&m, x, y));
    }
    printf("\n");
  }


  free_mountain(&m);
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
