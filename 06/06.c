#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char* argv[]) {
  if (argc < 2) {
    printf("Usage: %s input.txt [mode]\n", argv[0]);
    return 1;
  }

  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    printf("Error opening file: %s\n", argv[1]);
    return 2;
  }

  int mode = 1;
  if (argc > 2) {
    mode = atoi(argv[2]);
  }

  unsigned long long int times[10];
  unsigned long long int distances[10];

  int n_races = 0;
  fscanf(f, "Time:     ");
  while (1) {
    int res;
    res = fscanf(f, "%llu", &times[n_races]);
    if (res != 1) break;
    n_races++;
  };
  n_races = 0;
  fscanf(f, "Distance: ");
  while (1) {
    int res;
    res = fscanf(f, "%llu", &distances[n_races]);
    if (res != 1) break;
    n_races++;
  };

  unsigned long int result = 1;

  if (mode == 1) {
    int i;
    unsigned long long t;
    for (i=0; i<n_races; i++) {
      unsigned int number_of_ways_to_win = 0;

      // naively try all times
      for (t=0; t<=times[i]; t++) {
        unsigned long long int dist = t * (times[i] - t);
        if (dist > distances[i]) {
          number_of_ways_to_win++;
        }
      }

      if (number_of_ways_to_win > 0)
      result *= number_of_ways_to_win;
    }
  }
  else {
    double discr = sqrt(times[0]*times[0] - 4*distances[0]);
    double t1 = (times[0] - discr)/2;
    double t2 = (times[0] + discr)/2;

    result = floor(t2) - floor(t1);
  }

  printf("Answer: %lu\n", result);

  return 0;
}
