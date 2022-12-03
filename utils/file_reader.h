//
// Created by Lluís Merlos Pieri on 2/12/22.
//

#ifndef AOC2022_FILE_READER_H
#define AOC2022_FILE_READER_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  FILE *fp;
  char *line;
  size_t len;
  ssize_t read;
} file_t;


file_t load_file(const char *filename);
void free_file(file_t *f);
bool load_line(file_t *f);


#endif//AOC2022_FILE_READER_H
