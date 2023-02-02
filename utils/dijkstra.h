//
// Created by Lluís Merlos Pieri on 12/12/22.
//

#ifndef AOC2022_DIJKSTRA_H
#define AOC2022_DIJKSTRA_H

#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

// 1 function Dijkstra(Graph, source):
// 2
// 3      for each vertex v in Graph.Vertices:
// 4          dist[v] ← INFINITY
// 5          prev[v] ← UNDEFINED
// 6          add v to Q
// 7      dist[source] ← 0
// 8
// 9      while Q is not empty:
//10          u ← vertex in Q with min dist[u]
//11          remove u from Q
//12
//13          for each neighbor v of u still in Q:
//14              alt ← dist[u] + Graph.Edges(u, v)
//15              if alt < dist[v]:
//16                  dist[v] ← alt
//17                  prev[v] ← u
//18
//19      return dist[], prev[]

int dijkstra(size_t src, size_t dst, size_t n, int cost[n][n]){
  int dist[n];
  size_t prev[n][1+n];

  for (size_t i = 0; i < n; i++) {
    dist[i] = INT_MAX;
    prev[i][0] = 0;
  }
}

#endif//AOC2022_DIJKSTRA_H
