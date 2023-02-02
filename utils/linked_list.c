//
// Created by Lluís Merlos Pieri on 12/12/22.
//
#include "linked_list.h"





lkls_node_t lkls_new_node(void * data, size_t size) {
  lkls_node_t n = (lkls_node_t) {
    .next = NULL,
    .data = NULL,
    .size = 0
  };

  n.data = malloc(size);
  n.size = size;

  memcpy(n.data, data, size);

  return n;
}

bool lkls_get_next(lkls_node_t * node, lkls_node_t  ** next) {
  assert(node != NULL);

  if ( node->next == NULL ) {
    return false;
  } else {
    *next = node->next;
    return true;
  }
}

