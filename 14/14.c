#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mode = 1;

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

  char grid[200][200];
  unsigned long int n = 0;
  unsigned long int m = 0;

  while (!feof(f)) {
    if (fgets(grid[n], 199, f) == NULL) {
        break;
    }
    m = strlen(grid[n]) - 1;
    n++;
  }

  unsigned int result = 0;

  for (unsigned int j=0; j<n; j++) {
    unsigned int j_rock = n;
    for (unsigned int i=0; i<m; i++) {
      if (grid[i][j] == 'O') {
        // printf("%u,%u -> %u\n", i,j, j_rock);
        result += j_rock;
        j_rock--;
      } else if (grid[i][j] == '#') {
        j_rock = n-1-i;
      }
    }
  }

  printf("Answer: %u\n", result);

  return 0;
}
