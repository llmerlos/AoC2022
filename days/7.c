//
// Created by Lluís Merlos Pieri on 7/12/22.
//
#include "file_reader.h"

#define MAX_DIRS 15
#define ABOVE_LIM 100000

typedef struct dir dir_t;

struct dir {
  dir_t *parent;
  dir_t *dirs[MAX_DIRS];
  size_t n_dirs;
  size_t file_sizes;
};

dir_t *new_dir(dir_t *parent) {
  dir_t *directory = (dir_t *) malloc(sizeof(dir_t));

  directory->parent = parent;
  if (directory->parent != NULL)
    directory->parent->dirs[directory->parent->n_dirs++] = directory;
  directory->n_dirs = 0;
  directory->file_sizes = 0;

  return directory;
}

size_t get_dir_size(dir_t *dir) {
  size_t size = dir->file_sizes;

  for (int i = 0; i < dir->n_dirs; i++)
    size += get_dir_size(dir->dirs[i]);

  return size;
}

void free_dirs(dir_t *dir) {
  for (int i = 0; dir->n_dirs < 0; i++) {
    free_dirs(dir->dirs[i]);
  }

  free(dir);
}

size_t above_lim(dir_t *dir, size_t lim) {
  size_t dir_size = get_dir_size(dir);
  size_t size = dir_size <= lim ? dir_size : 0;

  for (int i = 0; i < dir->n_dirs; i++)
    size += above_lim(dir->dirs[i], lim);

  return size;
}

int main_a(file_t *f) {
  dir_t *root = new_dir(NULL);
  dir_t *cur_dir = root;

  while (load_line(f)) {
    // Command
    if (f->line[0] == '$') {
      // CD IN
      if (f->line[2] == 'c' && f->line[5] != '.') {
        cur_dir = new_dir(cur_dir);
      }
      // CD OUT
      else if (f->line[2] == 'c' && f->line[5] == '.') {
        cur_dir = cur_dir->parent;
      }
      // Ignore ls
    } else if (f->line[0] == 'd') {
      continue;
    } else {
      size_t size = (size_t) strtol(f->line, NULL, 10);
      cur_dir->file_sizes += size;
    }
  }

  size_t result = above_lim(root, ABOVE_LIM);

  free_dirs(root);

  return (int) result;
}


//
// PART B
//

#define UPSIZE 30000000
#define MXSIZE 70000000


size_t get_dir_size_and_compare(dir_t *dir, size_t needed, size_t *closest) {
  size_t size = dir->file_sizes;

  for (int i = 0; i < dir->n_dirs; i++)
    size += get_dir_size_and_compare(dir->dirs[i], needed, closest);

  if (size >= needed && size < (*closest)) {
    *closest = size;
  }

  return size;
}

int main_b(file_t *f) {
  dir_t *root = new_dir(NULL);
  dir_t *cur_dir = root;

  while (load_line(f)) {
    // Command
    if (f->line[0] == '$') {
      // CD IN
      if (f->line[2] == 'c' && f->line[5] != '.') {
        cur_dir = new_dir(cur_dir);
      }
      // CD OUT
      else if (f->line[2] == 'c' && f->line[5] == '.') {
        cur_dir = cur_dir->parent;
      }
      // Ignore ls
    } else if (f->line[0] == 'd') {
      continue;
    } else {
      size_t size = (size_t) strtol(f->line, NULL, 10);
      cur_dir->file_sizes += size;
    }
  }

  size_t available = MXSIZE - get_dir_size(root);
  size_t needed = UPSIZE - available;
  size_t closest = MXSIZE;
  get_dir_size_and_compare(root, needed, &closest);

  free_dirs(root);

  return (int) closest;
}
