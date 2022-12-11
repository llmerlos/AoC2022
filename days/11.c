//
// Created by Lluís Merlos Pieri on 11/12/22.
//
#include "file_reader.h"

#include <string.h>
#include <stdint.h>


#define MAX_ITEMS 1000
#define MAX_MONKEYS 10

typedef struct {
  __uint128_t items[MAX_ITEMS];
  size_t n_items;
  char op;
  __uint128_t operand;
  __uint128_t test_condition;
  size_t true_monkey;
  size_t false_monkey;
  size_t n_inspections;
} monkey_t;

typedef struct {
  size_t monkey;
  __uint128_t item;
} monkey_packet_t;

monkey_packet_t inspect_item_from(monkey_t * m, size_t i, bool reduce, __uint128_t factor) {
  __uint128_t new = m->items[i];
  switch (m->op) {
    case '+':
      new += m->operand;
      break ;
    case '*':
      new *= m->operand;
      break;
    case 's':
      new *= new;
      break;
  }

  //printf("Inspecting %d that converts to %d\n", m->items[i], new);
  if(reduce) {
    new /= 3;
    //printf("Bored to %d\n", new);
  } else {
    new %= factor;
  }

  memmove(&m->items[0], &m->items[1], (MAX_ITEMS - 1) * sizeof(__uint128_t));
  m->n_items--;
  m->n_inspections++;

  monkey_packet_t res = (monkey_packet_t) {.monkey = 0, .item = new};
  if ((new % m->test_condition) == 0) {
    res.monkey = m->true_monkey;
  } else {
    res.monkey = m->false_monkey;
  }

  //printf("To monkey %d\n", res.monkey);

  return res;
}

void add_item(monkey_t * m, __uint128_t item) {
  m->items[m->n_items++] = item;
}


int main_a(file_t *f) {
  monkey_t monkeys[MAX_MONKEYS];
  for (int i = 0; i < MAX_MONKEYS; i++)
    monkeys[i] = (monkey_t) {
      .items = {0},
      .n_items = 0,
      .op = ' ',
      .operand = 0,
      .test_condition = 0,
      .true_monkey = 0,
      .false_monkey = 0,
      .n_inspections = 0
    };
  int current_monkey = -1;

  while (load_line(f)) {
    if (f->line[0] == 'M') {
      current_monkey++;

      // Starting items
      load_line(f);
      char * num = &f->line[sizeof("  Starting items:") / sizeof (char)];
      char * token = strtok(num, ",");

      while (token != NULL) {
        __uint128_t item = atoi(token);
        add_item(&monkeys[current_monkey], item);
        token = strtok(NULL, ",");
      }
      //Operation
      load_line(f);
      char * op_line = &f->line[sizeof("  Operation: new = old") / sizeof(char)];
      char op = op_line[0];
      __uint128_t operand = 0;

      if (op_line[2] == 'o') {
        op = 's';
      } else {
        operand = atoi(&op_line[2]);
      }
      monkeys[current_monkey].op = op;
      monkeys[current_monkey].operand = operand;


      // Test Condition
      load_line(f);
      monkeys[current_monkey].test_condition = atoi(&f->line[sizeof("  Test: divisible by")/sizeof (char)]);

      // True Monkey
      load_line(f);
      monkeys[current_monkey].true_monkey = atoi(&f->line[sizeof("    If true: throw to monkey")/sizeof (char)]);
      // False Monkey
      load_line(f);
      monkeys[current_monkey].false_monkey = atoi(&f->line[sizeof("    If false: throw to monkey")/sizeof (char)]);
      // Newline
      load_line(f);

    }
  }

  for (int round = 0; round < 20; round++) {

    for(int mi = 0; mi <= current_monkey; mi++){
      while (monkeys[mi].n_items > 0) {
        monkey_packet_t res = inspect_item_from(&monkeys[mi], 0, true, 0);
        add_item(&monkeys[res.monkey], res.item);
      }
    }
  }

  size_t top2[2] = {0, 0};
  for(int i=0; i <= current_monkey; i++){
    int ni = monkeys[i].n_inspections;

    if (ni > top2[0]) {
      if (top2[0] > top2[1])
        top2[1] = top2[0];
      top2[0] = ni;
    } else if (ni > top2[1]) {
      if (top2[1] > top2[0])
        top2[0] = top2[1];
      top2[1] = ni;
    }
  }

  uint64_t res = (uint64_t) top2[0] * (uint64_t) top2[1];
  //printf("Unsigned: %llu\n", res);

  return res;
}



//
// PART B
//

int main_b(file_t *f) {
  monkey_t monkeys[MAX_MONKEYS];
  for (int i = 0; i < MAX_MONKEYS; i++)
    monkeys[i] = (monkey_t) {
      .items = {0},
      .n_items = 0,
      .op = ' ',
      .operand = 0,
      .test_condition = 0,
      .true_monkey = 0,
      .false_monkey = 0,
      .n_inspections = 0
    };
  int current_monkey = -1;

  while (load_line(f)) {
    if (f->line[0] == 'M') {
      current_monkey++;

      // Starting items
      load_line(f);
      char * num = &f->line[sizeof("  Starting items:") / sizeof (char)];
      char * token = strtok(num, ",");

      while (token != NULL) {
        __uint128_t item = atoi(token);
        add_item(&monkeys[current_monkey], item);
        token = strtok(NULL, ",");
      }
      //Operation
      load_line(f);
      char * op_line = &f->line[sizeof("  Operation: new = old") / sizeof(char)];
      char op = op_line[0];
      __uint128_t operand = 0;

      if (op_line[2] == 'o') {
        op = 's';
      } else {
        operand = atoi(&op_line[2]);
      }
      monkeys[current_monkey].op = op;
      monkeys[current_monkey].operand = operand;


      // Test Condition
      load_line(f);
      monkeys[current_monkey].test_condition = atoi(&f->line[sizeof("  Test: divisible by")/sizeof (char)]);

      // True Monkey
      load_line(f);
      monkeys[current_monkey].true_monkey = atoi(&f->line[sizeof("    If true: throw to monkey")/sizeof (char)]);
      // False Monkey
      load_line(f);
      monkeys[current_monkey].false_monkey = atoi(&f->line[sizeof("    If false: throw to monkey")/sizeof (char)]);
      // Newline
      load_line(f);

    }
  }

  __uint128_t mcm = 1;
  for(int mi = 0; mi <= current_monkey; mi++){
    mcm *= monkeys[mi].test_condition;
  }

  for (int round = 0; round < 10000; round++) {

    for(int mi = 0; mi <= current_monkey; mi++){
      while (monkeys[mi].n_items > 0) {
        monkey_packet_t res = inspect_item_from(&monkeys[mi], 0, false, mcm);
        add_item(&monkeys[res.monkey], res.item);
      }
    }
  }

  size_t top2[2] = {0, 0};
  for(int i=0; i <= current_monkey; i++){
    int ni = monkeys[i].n_inspections;

    if (ni > top2[0]) {
      if (top2[0] > top2[1])
        top2[1] = top2[0];
      top2[0] = ni;
    } else if (ni > top2[1]) {
      if (top2[1] > top2[0])
        top2[0] = top2[1];
      top2[1] = ni;
    }
  }

  uint64_t res = (uint64_t) top2[0] * (uint64_t) top2[1];
  printf("B: (u64) %llu\n", res);

  return 0;
}
