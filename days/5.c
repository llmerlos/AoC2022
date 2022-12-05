//
// Created by Lluís Merlos Pieri on 5/12/22.
//
#include "file_reader.h"
#include <string.h>

#define MAX_COLS 10

struct crate_t {
  char cargo;
  struct crate_t *child;
};

typedef struct crate_t crate_t;

crate_t *crate_new(char cargo) {
  crate_t *crate = malloc(sizeof(crate_t));
  crate->cargo = cargo;
  crate->child = NULL;

  return crate;
}

void add_crate_to_column(crate_t **column, crate_t *crate) {
  crate_t *parent_crate = column;
  while (parent_crate->child != NULL) {
    parent_crate = parent_crate->child;
  }

  parent_crate->child = crate;
}

typedef struct {
  int qty, src, dst;
} crane_movement_t;

crane_movement_t get_movement_from(char *line) {
  crane_movement_t mvt = {0, 0, 0};

  line = &line[sizeof("move") / sizeof(char)];
  mvt.qty = (int) strtol(line, &line, 10);
  line = &line[sizeof(" from") / sizeof(char)];
  mvt.src = (int) strtol(line, &line, 10);
  line = &line[sizeof(" to") / sizeof(char)];
  mvt.dst = (int) strtol(line, &line, 10);

  return mvt;
}

void apply_movement_to_a(crate_t *crane[MAX_COLS], crane_movement_t mvt) {
  for (int i = 0; i < mvt.qty; i++) {
    crate_t *crate_to_move = crane[mvt.src]->child;
    crane[mvt.src]->child = crate_to_move->child;

    crate_to_move->child = crane[mvt.dst]->child;
    crane[mvt.dst]->child = crate_to_move;
  }
}

void free_crane(crate_t *crane[MAX_COLS]) {
  for (int i = 0; i < MAX_COLS; i++) {
    crate_t *crate = crane[i];

    while (crate != NULL) {
      crate_t *crate_to_free = crate;
      crate = crate->child;
      free(crate_to_free);
    }
  }
}


int main_a(file_t *f) {
  crate_t *crane[MAX_COLS];
  for (int i = 0; i < MAX_COLS; i++) {
    crane[i] = crate_new('x');
  }

  while (load_line(f)) {
    // parsing initial state
    if (f->line[0] != 'm' && f->line[1] != '1' && f->line[0] != '\n') {
      for (int i = 1; i < f->read; i += 4) {
        int cargo = f->line[i];

        if (cargo != ' ') add_crate_to_column(&crane[(i - 1) / 4], crate_new(cargo));
      }
    }
    // move shenanigans
    else if (f->line[0] == 'm') {
      crane_movement_t mvt = get_movement_from(f->line);

      apply_movement_to_a(crane, mvt);
      for (int i = 0; i < MAX_COLS; i++) {
        crate_t *crate = crane[i];
        while (crate->child != NULL) {
          crate = crate->child;
        }
      }
    }
  }

  for (int i = 0; i < MAX_COLS; i++) {
    if (crane[i]->child != NULL)
      printf("%c", crane[i]->child->cargo);
  }
  printf("\n");

  free_crane(crane);

  return 0;
}


//
// PART B
//

void apply_movement_to_b(crate_t *crane[MAX_COLS], crane_movement_t mvt) {
  crate_t *top_to_move = crane[mvt.src]->child;
  crate_t *bot_to_move = top_to_move;
  for (int i = 1; i < mvt.qty; i++) {
    bot_to_move = bot_to_move->child;
  }

  crane[mvt.src]->child = bot_to_move->child;

  bot_to_move->child = crane[mvt.dst]->child;
  crane[mvt.dst]->child = top_to_move;
}

int main_b(file_t *f) {
  crate_t *crane[MAX_COLS];
  for (int i = 0; i < MAX_COLS; i++) {
    crane[i] = crate_new('x');
  }

  while (load_line(f)) {
    // parsing initial state
    if (f->line[0] != 'm' && f->line[1] != '1' && f->line[0] != '\n') {
      for (int i = 1; i < f->read; i += 4) {
        int cargo = f->line[i];

        if (cargo != ' ') add_crate_to_column(&crane[(i - 1) / 4], crate_new(cargo));
      }
    }
    // move shenanigans
    else if (f->line[0] == 'm') {
      crane_movement_t mvt = get_movement_from(f->line);

      apply_movement_to_b(crane, mvt);
      for (int i = 0; i < MAX_COLS; i++) {
        crate_t *crate = crane[i];
        while (crate->child != NULL) {
          crate = crate->child;
        }
      }
    }
  }

  for (int i = 0; i < MAX_COLS; i++) {
    if (crane[i]->child != NULL)
      printf("%c", crane[i]->child->cargo);
  }
  printf("\n");

  free_crane(crane);

  return 0;
}
