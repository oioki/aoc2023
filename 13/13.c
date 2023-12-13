#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mode = 1;

int solve(const char * grid, int n, int m) {
  // for (int i=0; i<n; i++) {
  //   for (int j=0; j<m; j++) {
  //     printf("%c", grid[i*100+j]);
  //   }
  //   printf("\n");
  // }


  for (int ii=1; ii<n; ii++) {
    bool perfect_mirror = true;
    bool smudge_found = false;
    if (ii<=n/2) {
      // printf("%d should iterate over top part only\n", ii);
      for (int i=0; i<ii; i++) {
        for (int j=0; j<m; j++) {
          if (grid[i*100+j] != grid[((2*ii-i-1)*100+j)]) {
            if (!smudge_found && (mode==2)) {
              smudge_found = true;
            } else {
              perfect_mirror = false;
              break;
            }
          }
        }
      }
    } else {
      // printf("%d should iterate over bottom part only\n", ii);
      for (int i=ii; i<n; i++) {
        for (int j=0; j<m; j++) {
          if (grid[i*100+j] != grid[((2*ii-i-1)*100+j)]) {
            if (!smudge_found && (mode==2)) {
              smudge_found = true;
            } else {
              perfect_mirror = false;
              break;
            }
          }
        }
      }
    }
    if (perfect_mirror && (smudge_found || (mode==1))) return 100*ii;
  }


  for (int jj=1; jj<m; jj++) {
    bool perfect_mirror = true;
    bool smudge_found = false;
    if (jj<=m/2) {
      // printf("%d should iterate over left part only\n", jj);
      for (int i=0; i<n; i++) {
        for (int j=0; j<jj; j++) {
          if (grid[i*100+j] != grid[(i*100+((2*jj-j-1)))]) {
            if (!smudge_found && (mode==2)) {
              smudge_found = true;
            } else {
              perfect_mirror = false;
              break;
            }
          }
        }
      }
    } else {
      // printf("%d should iterate over right part only\n", jj);
      for (int i=0; i<n; i++) {
        for (int j=jj; j<m; j++) {
          if (grid[i*100+j] != grid[(i*100+((2*jj-j-1)))]) {
            if (!smudge_found && (mode==2)) {
              smudge_found = true;
            } else {
              perfect_mirror = false;
              break;
            }
          }
        }
      }
    }
    if (perfect_mirror && (smudge_found || mode==1)) return jj;
  }

  return 0;
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

  int result = 0;

  int n = 0;
  int m = 0;
  char grid[100][100];
  while (!feof(f)) {
    if (fgets(grid[n], 99, f) == NULL) {
      result += solve(&grid[0][0], n, m);
      break;
    }

    int l = strlen(grid[n]);
    if (l == 1) {
      result += solve(&grid[0][0], n, m);
      n = 0;
      m = 0;
    } else {
      n++;
      m = l - 1;
    }
  };

  printf("Answer: %d\n", result);

  return 0;
}
