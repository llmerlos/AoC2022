//
// Created by Lluís Merlos Pieri on 2/12/22.
//

#include "file_reader.h"

file_t load_file(const char *filename)
{
  file_t f = {NULL, NULL, 0, 0};


  f.fp = fopen(filename, "r");

  if (f.fp == NULL) {
    exit(EXIT_FAILURE);
  }

  return f;
};

void free_file(file_t *f)
{
  if (f->line != NULL)
  {
    free(f->line);
  }

  fclose(f->fp);
}

bool load_line(file_t *f)
{
  f->read = getline(&f->line, &f->len, f->fp);

  return f->read != -1;
}