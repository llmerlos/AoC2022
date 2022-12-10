//
// Created by Lluís Merlos Pieri on 9/12/22.
//
#include "file_reader.h"

#define MAX_DIM 200
#define TOT_DIM (MAX_DIM + 1 + MAX_DIM)
#define ZER_DIM (MAX_DIM + 1)

typedef struct {
  int x;
  int y;
} point_t;

point_t move_head(point_t prv_head, char dir) {
  switch (dir) {
    case 'U':
      prv_head.y++;
      break;
    case 'D':
      prv_head.y--;
      break;
    case 'L':
      prv_head.x--;
      break;
    case 'R':
      prv_head.x++;
      break;
  }

  return prv_head;
}

int distance(point_t p1, point_t p2) {
  int x = abs(p1.x - p2.x);
  int y = abs(p1.y - p2.y);

  return (x > y ? x : y);
}

int sign(int a) {
  if (a == 0) {
    return 0;
  } else if (a > 0) {
    return 1;
  } else {
    return -1;
  }
}

point_t move_tail(point_t prv_tail, point_t nxt_head) {
  if (distance(prv_tail, nxt_head) < 2) {
    return prv_tail;
  }

  point_t d = (point_t){.x = nxt_head.x - prv_tail.x, .y = nxt_head.y - prv_tail.y};

  prv_tail.x += sign(d.x);
  prv_tail.y += sign(d.y);

  return prv_tail;
}

int main_a(file_t *f) {
  bool visited[TOT_DIM][TOT_DIM] = {false};

  point_t head = (point_t){.x = 0, .y = 0};
  point_t tail = (point_t){.x = 0, .y = 0};

  while (load_line(f)) {
    char dir = f->line[0];
    int qty = atoi(&f->line[2]);

    for (int i = 0; i < qty; i++) {
      point_t prv_head = head;
      head = move_head(prv_head, dir);
      tail = move_tail(tail, head);

      visited[ZER_DIM + tail.x][ZER_DIM + tail.y] = true;
    }
  }

  int total = 0;
  for (int y = TOT_DIM - 1; y >= 0; y--)
    for (int x = 0; x < TOT_DIM; x++)
      if (visited[x][y]) total++;

  return total;
}


//
// PART B
//
#define ROPE_SIZE 10

int main_b(file_t *f) {
  bool visited[TOT_DIM][TOT_DIM] = {false};

  point_t rope[ROPE_SIZE];
  for (int i = 0; i < ROPE_SIZE; i++) {
    rope[i] = (point_t){.x = 0, .y = 0};
  }

  while (load_line(f)) {
    char dir = f->line[0];
    int qty = atoi(&f->line[2]);

    for (int i = 0; i < qty; i++) {
      rope[0] = move_head(rope[0], dir);

      for (int k = 1; k < ROPE_SIZE; k++) {
        rope[k] = move_tail(rope[k], rope[k - 1]);
      }

      visited[ZER_DIM + rope[ROPE_SIZE - 1].x][ZER_DIM + rope[ROPE_SIZE - 1].y] = true;
    }
  }

  int total = 0;
  for (int y = TOT_DIM - 1; y >= 0; y--)
    for (int x = 0; x < TOT_DIM; x++)
      if (visited[x][y]) total++;

  return total;
}
