#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mode = 1;
char grid[200][200];

#define UP    0x01
#define LEFT  0x02
#define RIGHT 0x04
#define DOWN  0x08

typedef struct beam {
    int i;
    int j;
    unsigned char direction;
} beam;

#define MAX_BEAMS 2000
beam beams[MAX_BEAMS];
unsigned int nbeams;

unsigned char energize[200][200] = {0};

void print(const unsigned char (*g)[200], unsigned int n, unsigned int m) {
  for (unsigned int i=0; i<n; i++) {
    for (unsigned int j=0; j<m; j++) {
      printf("%c", g[i][j] + '0');
    }
    printf("\n");
  }
  printf("------------------------------------\n");
}

int solve(const char (*g)[200], int n, int m) {
  for(int i=0; i<n; i++)
  for(int j=0; j<m; j++)
    energize[i][j] = 0;

  for (unsigned int k=0; k<nbeams; k++) {
    if (nbeams > MAX_BEAMS) {
      printf("Max number of beams reached!\n");
      return 0;
    }
    beam b = beams[k];
    int i = b.i;
    int j = b.j;

    // printf("processing beam [%d,%d,%c]\n", i, j, b.direction+'0');
    if ( (i<0) || (i>n-1) || (j<0) || (j>m-1) ) continue;

    while (1) {
      // break if the tile was already energized in that direction
      if (energize[i][j] & b.direction) break;

      energize[i][j] |= b.direction;

      if ((b.direction & (LEFT|RIGHT)) && (g[i][j] == '|')) {
        beams[nbeams++] = (beam){i-1, j, UP};
        beams[nbeams++] = (beam){i+1, j, DOWN};
        break;
      } else
      if ((b.direction & (DOWN|UP)) && (g[i][j] == '-')) {
        beams[nbeams++] = (beam){i, j-1, LEFT};
        beams[nbeams++] = (beam){i, j+1, RIGHT};
        break;
      } else
      if ((b.direction == RIGHT) && (g[i][j] == '/')) {
        beams[nbeams++] = (beam){i-1, j, UP};
        break;
      } else
      if ((b.direction == UP) && (g[i][j] == '/')) {
        beams[nbeams++] = (beam){i, j+1, RIGHT};
        break;
      } else
      if ((b.direction == LEFT) && (g[i][j] == '/')) {
        beams[nbeams++] = (beam){i+1, j, DOWN};
        break;
      } else
      if ((b.direction == DOWN) && (g[i][j] == '/')) {
        beams[nbeams++] = (beam){i, j-1, LEFT};
        break;
      } else
      if ((b.direction == RIGHT) && (g[i][j] == '\\')) {
        beams[nbeams++] = (beam){i+1, j, DOWN};
        break;
      } else
      if ((b.direction == UP) && (g[i][j] == '\\')) {
        beams[nbeams++] = (beam){i, j-1, LEFT};
        break;
      } else
      if ((b.direction == LEFT) && (g[i][j] == '\\')) {
        beams[nbeams++] = (beam){i-1, j, UP};
        break;
      } else
      if ((b.direction == DOWN) && (g[i][j] == '\\')) {
        beams[nbeams++] = (beam){i, j+1, RIGHT};
        break;
      }

      if (b.direction == RIGHT) {
        j++;
      }
      else if (b.direction == DOWN) {
        i++;
      }
      else if (b.direction == LEFT) {
        j--;
      }
      else if (b.direction == UP) {
        i--;
      }
      if ( (i<0) || (i>n-1) || (j<0) || (j>m-1) ) break;
    }
  }

  // print(energize, n, m);

  int result = 0;
  for (int i=0; i<n; i++)
  for (int j=0; j<m; j++)
    if (energize[i][j]) result++;
  return result;
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

  int n = 0;
  int m = 0;

  while (!feof(f)) {
    if (fgets(grid[n], 199, f) == NULL) {
        break;
    }
    m = strlen(grid[n]) - 1;
    n++;
  }

  int result = 0;
  if (mode == 1) {
    nbeams = 1;
    beams[0] = (beam){0, 0, RIGHT};
    result = solve(grid, n, m);
  } else {
    nbeams = 1;
    int result_candidate;
    for (int i=0; i<n; i++) {
      nbeams = 1;
      beams[0] = (beam){i, 0, RIGHT};
      result_candidate = solve(grid, n, m);
      if (result_candidate > result) result = result_candidate;

      nbeams = 1;
      beams[0] = (beam){i, m-1, LEFT};
      result_candidate = solve(grid, n, m);
      if (result_candidate > result) result = result_candidate;
    }

    for (int j=0; j<m; j++) {
      nbeams = 1;
      beams[0] = (beam){0, j, DOWN};
      result_candidate = solve(grid, n, m);
      if (result_candidate > result) result = result_candidate;

      nbeams = 1;
      beams[0] = (beam){n-1, j, UP};
      result_candidate = solve(grid, n, m);
      if (result_candidate > result) result = result_candidate;
    }
  }

  printf("Answer: %d\n", result);

  return 0;
}
