//
// Created by Lluís Merlos Pieri on 10/12/22.
//
#include "file_reader.h"

typedef struct {
  int x;
  int cycle;
} cpu_t;

int clock_up_and_get_interesting(cpu_t *cpu) {
  cpu->cycle++;

  int interesting_factor = 0;
  switch (cpu->cycle) {
    case 20:
    case 60:
    case 100:
    case 140:
    case 180:
    case 220:
      interesting_factor = cpu->cycle * cpu->x;
  }
  //printf("C: %03d\tX: %03d\tI: %03d\n", cpu->cycle, cpu->x, interesting_factor);
  return interesting_factor;
}

int main_a(file_t *f) {
  cpu_t cpu = (cpu_t){.x = 1, .cycle = 0};
  int signal_str = 0;

  while (load_line(f)) {
    // noop
    if (f->line[0] == 'n') {
      signal_str += clock_up_and_get_interesting(&cpu);
    } else {
      char *line_num = &f->line[sizeof("addx") / sizeof(char)];
      int add = atoi(line_num);

      signal_str += clock_up_and_get_interesting(&cpu);
      signal_str += clock_up_and_get_interesting(&cpu);
      cpu.x += add;
    }
  }

  return signal_str;
}


//
// PART B
//
#define CRT_WIDTH 40
#define CRT_HEIGHT 6

typedef struct {
  bool pixels[CRT_WIDTH][CRT_HEIGHT];
} crt_t;

void clock_up_update_screen(cpu_t *cpu, crt_t *crt) {
  cpu->cycle++;

  int col = cpu->cycle % CRT_WIDTH;
  int row = cpu->cycle / CRT_WIDTH;

  if (abs(col - cpu->x) <= 1) {
    crt->pixels[col][row] = true;
  } else {
    crt->pixels[col][row] = false;
  }
}

int main_b(file_t *f) {
  cpu_t cpu = (cpu_t){.x = 1, .cycle = -1};
  crt_t crt = (crt_t){.pixels = {0}};

  while (load_line(f)) {
    if (f->line[0] == 'n') {
      clock_up_update_screen(&cpu, &crt);
    } else {
      char *line_num = &f->line[sizeof("addx") / sizeof(char)];
      int add = atoi(line_num);

      clock_up_update_screen(&cpu, &crt);
      clock_up_update_screen(&cpu, &crt);
      cpu.x += add;
    }
  }


  printf("B: \n");
  for (int y = 0; y < CRT_HEIGHT; y++) {
    for (int x = 0; x < CRT_WIDTH; x++) {
      if (crt.pixels[x][y])
        printf("#");
      else
        printf(".");
    }
    printf("\n");
  }

  return 0;
}
