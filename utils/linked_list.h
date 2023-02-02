//
// Created by Lluís Merlos Pieri on 12/12/22.
//
#ifndef AOC2022_LINKED_LIST_H
#define AOC2022_LINKED_LIST_H

#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct lkls_node_t {
  struct lkls_node_t * next;
  void * data;
  size_t size;
};

typedef struct lkls_node_t lkls_node_t;

typedef struct {
  lkls_node_t * head, * tail;
} lkls_t;

lkls_t lkls_new();
void lkls_add(lkls_t * list, void * data, size_t size);
void lkls_cut(lkls_t * list);
lkls_node_t * lkls_pop(lkls_t * list);
lkls_t lkls_split_at(lkls_t * list, size_t index);

#endif//AOC2022_LINKED_LIST_H
