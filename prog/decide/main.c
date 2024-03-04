#include <stdio.h>
#include <stdlib.h>
#include "dtime.h"

int rnd_range(int min, int max) {
  return (rand() % (max - min)) + min;
}

int main(int argc, char** argv) {
  if (argc == 1) {
    printf("./decide \"option1\" \"option2\" ... \"optionN\"\n");
    return 0;
  }

  srand(t_get_time());

  int rnd = rnd_range(1, argc);
  printf("%s\n", argv[rnd]);

  return 0;
}
