#include <stdbool.h>
#include <stdio.h>

int debug = 0;

void print_ranges(int n_ranges, const unsigned int ranges[], const unsigned int lengths[]) {
  if (!debug) return;
  int j=0;
  for (j=0; j<n_ranges; j++) {
    printf("range #%d = [%u;%u]\n", j, ranges[j], ranges[j] + lengths[j] - 1);
  }
  printf("\n");
}

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

  unsigned int rs[2][200];  // range starts
  unsigned int rl[2][200];  // range lengths
  bool range_done_on_this_step[200];
  int n_ranges = 0;

  fscanf(f, "seeds: ");
  while (1) {
    int res;
    fscanf(f, "%u", &rs[0][n_ranges]);
    res = fscanf(f, "%u", &rl[0][n_ranges]);
    if (!res) break;
    n_ranges++;
  };

  print_ranges(n_ranges, rs[0], rl[0]);

  unsigned int lowest_location = 1000000000;
  char s[200];
  int steps = 7;
  while (steps-- > 0) {
    unsigned int * range_starts = rs[steps%2];
    unsigned int * lengths = rl[steps%2];
    unsigned int * new_range_starts = rs[(steps+1)%2];
    unsigned int * new_range_lengths = rl[(steps+1)%2];
    int n_new_ranges = 0;

    fgets(s, 199, f);  // read ".* map:" string

    for (int i=0; i<n_ranges; i++) {
      range_done_on_this_step[i] = false;
    }

    print_ranges(n_ranges, range_starts, lengths);

    while (1) {
      unsigned int a, b, c;
      int items_read = fscanf(f, "%u %u %u\n", &a, &b, &c);
      if (items_read < 1) {
        break;
      }

      int i;
      for (i=0; i<n_ranges; i++) {
        // check for empty intersection
        if ((b > range_starts[i] + lengths[i] - 1) || (range_starts[i] > b+c-1))
        {
          continue;
        }

        if (range_done_on_this_step[i]) {
          continue;
        }

        unsigned int new_start = (range_starts[i] > b) ? range_starts[i] : b;
        unsigned int new_end   = (range_starts[i] + lengths[i] - 1 < b+c-1) ? range_starts[i] + lengths[i] - 1 : b+c-1;
        new_range_starts[n_new_ranges] = new_start - b + a;
        new_range_lengths[n_new_ranges] = new_end - new_start + 1;
        n_new_ranges++;

        if (range_starts[i] < b) {
          // printf("keep left interval: [%u;%u]\n", range_starts[i], b-1);
          range_starts[n_ranges] = range_starts[i];
          lengths[n_ranges] = (b) - (range_starts[i]);
          range_done_on_this_step[n_ranges] = false;
          n_ranges++;

          print_ranges(n_ranges, range_starts, lengths);
        }

        if (b+c-1 < range_starts[i] + lengths[i] -1) {
          // printf("keep right interval: [%u;%u]\n", b+c-1+1, range_starts[i]+lengths[i]-1);
          range_starts[n_ranges] = (b+c-1) + 1;
          lengths[n_ranges] = (range_starts[i]+lengths[i]-1) - (b+c-1);
          range_done_on_this_step[n_ranges] = false;
          n_ranges++;

          print_ranges(n_ranges, range_starts, lengths);
        }

        range_done_on_this_step[i] = true;
      }
    }

    for (int i=0; i<n_ranges; i++) {
      if (!range_done_on_this_step[i]) {
        // just copy the ranges without change
        new_range_starts[n_new_ranges] = range_starts[i];
        new_range_lengths[n_new_ranges] = lengths[i];
        n_new_ranges++;
      }
    }

    n_ranges = n_new_ranges;

    print_ranges(n_new_ranges, new_range_starts, new_range_lengths);
  }


  for (int i=0; i<n_ranges; i++) {
    if (rs[1][i] < lowest_location) {
      if (rs[1][i] > 0 )
      lowest_location = rs[1][i];
    }
  }

  printf("Answer: %u\n", lowest_location);

  return 0;
}
