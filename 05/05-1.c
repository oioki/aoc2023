#include <stdbool.h>
#include <stdio.h>


int main(int argc, const char* argv[]) {
  if (argc < 2) {
    printf("Usage: %s input.txt\n", argv[0]);
    return 1;
  }

  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    printf("Error opening file: %s\n", argv[1]);
    return 2;
  }

  unsigned int seeds[30];
  bool seed_done_on_this_step[30];
  int n_seeds = 0;

  fscanf(f, "seeds: ");
  while (1) {
    int res = fscanf(f, "%u", &seeds[n_seeds]);
    if (!res) break;
    n_seeds++;
  };

  unsigned int lowest_location = 0xffffffff;
  char s[200];
  int steps = 7;
  while (steps-- > 0) {
    fgets(s, 199, f);  // read ".* map:" string
    // printf("### %s", s);

    for (int i=0; i<n_seeds; i++) {
      seed_done_on_this_step[i] = false;
    }

    while (1) {
      unsigned int a, b, c;
      int items_read = fscanf(f, "%u %u %u\n", &a, &b, &c);
      if (items_read < 1) {
        break;
      }
      // printf("%d [%u;%u] -> [%u;%u]\n", items_read, b, b+c-1, a, a+c-1);

      for (int i=0; i<n_seeds; i++) {
        if ((b <= seeds[i]) && (seeds[i] <= b+c-1) && !seed_done_on_this_step[i]) {
          // printf("seed[%d]: %u -> ", i, seeds[i]);
          seeds[i] = seeds[i] - b + a;
          // printf("%u\n", seeds[i]);
          seed_done_on_this_step[i] = true;
          continue;
        }
      }
    }
  }

  for (int i=0; i<n_seeds; i++) {
    if (seeds[i] < lowest_location) {
      lowest_location = seeds[i];
    }
  }

  printf("Answer: %u\n", lowest_location);

  return 0;
}
