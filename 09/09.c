#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mode = 1;

int solve_one_history(int n, const int values[]) {
  int middle[40][40];
  for (int i=0; i<n; i++) {
    middle[0][i] = values[i+1] - values[i];
  }

  int depth;
  for (depth = 1; depth<n; depth++) {
    bool all_zeros = true;
    for (int i=0; i<n-depth-1; i++) {
      middle[depth][i] = middle[depth-1][i+1] - middle[depth-1][i];
      if (middle[depth][i] != 0) {
        all_zeros = false;
      }
    }

    if (all_zeros) break;
  }

  if (mode == 2) {
    int tmp = 0;
    for (int j=depth; j>=0; j--) {
      tmp = middle[j][0] - tmp;
    }
    return values[0] - tmp;
  }

  middle[depth][n-depth-1] = 0;
  for (int j=depth-1; j>=0; j--) {
    middle[j][n-j-1] = middle[j+1][n-j-1-1] + middle[j][n-j-1-1];
  }

  // printf("Answer: %d\n", values[n-1] + middle[0][n-1]);

  return values[n-1] + middle[0][n-1];
}

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

  if (argc > 2) {
    mode = atoi(argv[2]);
  }

  long long int result = 0;
  char s[200];
  while (!feof(f)) {
    if (fgets(s, 199, f) == NULL) {
        break;
    }

    char * cur = s;

    int n_elements = 0;
    int values[40];
    int bytes_read;
    while (1) {
      int r = sscanf(cur, "%d%n", &values[n_elements], &bytes_read);
      cur += bytes_read;
      if (r == -1) break;
      n_elements++;
    }
    if (n_elements==0) break;

    result += solve_one_history(n_elements, values);
  }

  printf("Final Answer: %lld\n", result);

  return 0;
}
