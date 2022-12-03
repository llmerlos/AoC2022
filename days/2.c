//
// Created by Lluís Merlos Pieri on 2/12/22.
//
#include "file_reader.h"

enum plays {
  ROCK = 1,
  PAPER = 2,
  SCISSORS = 3,
};

#define WIN 6
#define DRAW 3
#define LOSE 0

enum plays convert_a(char play) {

  switch (play) {
    case 'A':
    case 'X':
      return ROCK;
    case 'B':
    case 'Y':
      return PAPER;
    default:
      return SCISSORS;
  }
}

int get_score_a(enum plays elf, enum plays you) {
  if (elf == you) {
    return DRAW + you;
  }

  if ((you == ROCK && elf == SCISSORS) || (you == SCISSORS && elf == PAPER) || (you == PAPER && elf == ROCK)) {
    return WIN + you;
  }

  //if ((you == SCISSORS && elf == ROCK) || (you == PAPER && elf == SCISSORS) || (you == ROCK && elf == PAPER))
  return LOSE + you;
}


int main_a(file_t *f) {
  int score = 0;

  while (load_line(f)) {
    enum plays elf = convert_a(f->line[0]);
    enum plays you = convert_a(f->line[2]);

    score += get_score_a(elf, you);
  }

  return score;
}

//
//  B PART
//

enum plays convert_b(char play, enum plays elf) {
  switch (play) {
    case 'X':// LOSE
      switch (elf) {
        case ROCK:
          return SCISSORS;
        case PAPER:
          return ROCK;
        default:
          return PAPER;
      }
    case 'Y':// DRAW
      return elf;
    default:// WIN
      switch (elf) {
        case ROCK:
          return PAPER;
        case PAPER:
          return SCISSORS;
        default:
          return ROCK;
      }
  }
}

int main_b(file_t *f) {
  int score = 0;

  while (load_line(f)) {
    enum plays elf = convert_a(f->line[0]);
    enum plays you = convert_b(f->line[2], elf);

    score += get_score_a(elf, you);
  }

  return score;
}
