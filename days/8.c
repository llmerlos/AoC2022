//
// Created by Lluís Merlos Pieri on 8/12/22.
//
#include "file_reader.h"

#define MAX_ROW 100
#define MAX_COL 100

bool is_visible(size_t x, size_t y, uint8_t forest[MAX_ROW][MAX_COL], size_t nc, size_t nr) {
  if (x == 0 || x == (nc-1) || y == 0 || y == (nr-1))
    return  true;

  uint8_t height = forest[x][y];

  bool left = true;
  for (size_t i = 0; i < x; i++){
    if (forest[i][y] >= height) {
      left = false;
    }
  }

  bool right = true;
  for (size_t i = x+1; i < nc; i++){
    if (forest[i][y] >= height) {
      right = false;
    }
  }

  bool up = true;
  for (size_t i = 0; i < y; i++){
    if (forest[x][i] >= height) {
      up = false;
    }
  }

  bool down = true;
  for (size_t i = y+1; i < nr; i++){
    if (forest[x][i] >= height) {
      down = false;
    }
  }

  return left || right || up || down;
}

int main_a(file_t *f) {
  uint8_t forest [MAX_ROW][MAX_COL] = {0};
  size_t n_rows = 0;
  size_t n_cols = 0;

  while (load_line(f)) {
    n_cols = f->read-1;

    for (size_t i=0; i < n_cols; i++){
      forest[i][n_rows] = f->line[i] - '0';
    }

    n_rows++;
  }

  int visible = 0;
  for (size_t r = 0; r < n_rows; r++) {
    for (size_t c = 0; c < n_cols; c++) {
      if (is_visible(c,r, forest,n_rows,n_cols)){
        visible += 1;
      }
    }
  }

  return visible;
}


//
// PART B
//

int scenic_score(size_t x, size_t y, uint8_t forest[MAX_ROW][MAX_COL], size_t nc, size_t nr) {
  if (x == 0 || x == (nc-1) || y == 0 || y == (nr-1))
    return 0;

  uint8_t height = forest[x][y];

  int left = 0;
  for (int i = x-1; i >= 0; i--){
    left++;
    if (forest[i][y] >= height) {
      break;
    }
  }

  int right = 0;
  for (int i = x+1; i < nc; i++){
    right++;
    if (forest[i][y] >= height) {
      break;
    }
  }

  int up = 0;
  for (int i = y-1; i >= 0; i--){
    up++;
    if (forest[x][i] >= height) {
      break;
    }
  }

  int down = 0;
  for (int i = y+1; i < nr; i++){
    down++;
    if (forest[x][i] >= height) {
      break;
    }
  }

  return left * right * up * down;
}

int main_b(file_t *f) {
  uint8_t forest [MAX_ROW][MAX_COL] = {0};
  size_t n_rows = 0;
  size_t n_cols = 0;

  while (load_line(f)) {
    n_cols = f->read-1;

    for (size_t i=0; i < n_cols; i++){
      forest[i][n_rows] = f->line[i] - '0';
    }

    n_rows++;
  }

  int max_scenic = 0;
  for (size_t r = 0; r < n_rows; r++) {
    for (size_t c = 0; c < n_cols; c++) {
      int score = scenic_score(c, r, forest, n_cols, n_rows);

      if (score > max_scenic)
        max_scenic = score;
    }
  }

  return max_scenic;
}
