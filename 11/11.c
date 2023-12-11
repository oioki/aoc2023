#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int expansion = 1;

unsigned long int diff(unsigned long int a, unsigned long int b) {
  return a > b ? a-b : b-a;
}

int main(int argc, const char* argv[]) {
  if (argc < 2) {
    printf("Usage: %s input.txt [expansion]\n", argv[0]);
    return 1;
  }

  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    printf("Error opening file: %s\n", argv[1]);
    return 2;
  }

  if (argc > 2) {
    expansion = atoi(argv[2]);
  }

  char grid[200][200];
  unsigned long int n = 0;
  unsigned long int m = 0;

  unsigned long int i_galaxy[500];
  unsigned long int j_galaxy[500];
  int n_galaxies = 0;

  while (!feof(f)) {
    if (fgets(grid[n], 199, f) == NULL) {
        break;
    }
    m = strlen(grid[n]) - 1;
    n++;
  }

  // find all galaxies
  for (unsigned long int i=0; i<n; i++) {
    for (unsigned long int j=0; j<m; j++) {
      if (grid[i][j] == '#') {
        i_galaxy[n_galaxies] = i;
        j_galaxy[n_galaxies] = j;
        n_galaxies++;
      }
    }
  }

  // find i's with no galaxies
  for (unsigned long int i=0; i<n; i++) {
    bool any_galaxies_here = false;
    for (int k=0; k<n_galaxies; k++) {
      if (i_galaxy[k] == i) {
        any_galaxies_here = true;
        break;
      }
    }

    if (!any_galaxies_here) {
      for (int k=0; k<n_galaxies; k++) {
        if (i_galaxy[k]>i) {
          i_galaxy[k] += (expansion-1);
        }
      }
      i += (expansion-1);
      n += (expansion-1);
    }
  }

  // find j's with no galaxies
  for (unsigned long int j=0; j<m; j++) {
    bool any_galaxies_here = false;
    for (int k=0; k<n_galaxies; k++) {
      if (j_galaxy[k] == j) {
        any_galaxies_here = true;
        break;
      }
    }
    if (!any_galaxies_here) {
      for (int k=0; k<n_galaxies; k++) {
        if (j_galaxy[k]>j) {
          j_galaxy[k] += (expansion-1);
        }
      }
      j += (expansion-1);
      m += (expansion-1);
    }
  }

  unsigned long int result = 0;
  for(int k=0; k<n_galaxies; k++) {
    for(int l=k+1; l<n_galaxies; l++) {
      unsigned long int d = diff(i_galaxy[k], i_galaxy[l]) + diff(j_galaxy[k], j_galaxy[l]);
      result += d;
      // printf("dist between #%d and #%d is %lu\n", k, l, d);
    }
  }

  printf("Answer: %lu\n", result);

  return 0;
}
