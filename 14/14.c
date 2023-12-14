#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://github.com/Zunawe/md5-c
#include "md5.h"

int mode = 1;
char grid[200][200];
char grid2[200][200];

unsigned int get_load(char ** p, unsigned int n, unsigned int m) {
  char (*grid)[200] = (char (*)[200])p;

  int result = 0;
  for (unsigned int j=0; j<m; j++) {
    for (unsigned int i=0; i<n; i++) {
      if (grid[i][j] == 'O') {
        result += n-i;
      }
    }
  }
  return result;
}

void print(char ** p, unsigned int n, unsigned int m) {
  char (*grid)[200] = (char (*)[200])p;

  for (unsigned int i=0; i<n; i++) {
    for (unsigned int j=0; j<m; j++) {
      printf("%c", grid[i][j]);
    }
    printf("\n");
  }
  printf("------------------------------------\n");
}

void reset(char ** p, unsigned int n, unsigned int m) {
  char (*grid)[200] = (char (*)[200])p;

  for (unsigned int i=0; i<n; i++) {
    for (unsigned int j=0; j<m; j++) {
      grid[i][j] = '.';
    }
  }
}

unsigned int roll_north(char ** p, char ** q, unsigned int n, unsigned int m) {
  char (*grid)[200] = (char (*)[200])p;
  char (*grid2)[200] = (char (*)[200])q;

  reset(q, n, m);

  int result = 0;
  for (unsigned int j=0; j<m; j++) {
    unsigned int i_rock = 0;
    for (unsigned int i=0; i<n; i++) {
      if (grid[i][j] == 'O') {
        grid2[i_rock][j] = 'O';
        i_rock++;
      } else if (grid[i][j] == '#') {
        grid2[i][j] = '#';
        i_rock = i+1;
      }
    }
  }
}

unsigned int roll_west(char ** p, char ** q, unsigned int n, unsigned int m) {
  char (*grid)[200] = (char (*)[200])p;
  char (*grid2)[200] = (char (*)[200])q;

  reset(q, n, m);

  int result = 0;
  for (unsigned int i=0; i<n; i++) {
    unsigned int j_rock = 0;
    for (unsigned int j=0; j<n; j++) {
      if (grid[i][j] == 'O') {
        grid2[i][j_rock] = 'O';
        j_rock++;
      } else if (grid[i][j] == '#') {
        grid2[i][j] = '#';
        j_rock = j+1;
      }
    }
  }
}

unsigned int roll_south(char ** p, char ** q, unsigned int n, unsigned int m) {
  char (*grid)[200] = (char (*)[200])p;
  char (*grid2)[200] = (char (*)[200])q;

  reset(q, n, m);

  int result = 0;
  for (unsigned int j=0; j<m; j++) {
    unsigned int i_rock = n-1;
    for (int i=n-1; i>=0; i--) {
      if (grid[i][j] == 'O') {
        grid2[i_rock][j] = 'O';
        i_rock--;
      } else if (grid[i][j] == '#') {
        grid2[i][j] = '#';
        i_rock = i-1;
      }
    }
  }
}

unsigned int roll_east(char ** p, char ** q, unsigned int n, unsigned int m) {
  char (*grid)[200] = (char (*)[200])p;
  char (*grid2)[200] = (char (*)[200])q;

  reset(q, n, m);

  int result = 0;
  for (unsigned int i=0; i<n; i++) {
    unsigned int j_rock = m-1;
    for (int j=m-1; j>=0; j--) {
      if (grid[i][j] == 'O') {
        grid2[i][j_rock] = 'O';
        j_rock--;
      } else if (grid[i][j] == '#') {
        grid2[i][j] = '#';
        j_rock = j-1;
      }
    }
  }
}

void print_hash(uint8_t *p){
    for(unsigned int i = 0; i < 16; ++i){
        printf("%02x", p[i]);
    }
    printf("\n");
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

  unsigned long int n = 0;
  unsigned long int m = 0;

  while (!feof(f)) {
    if (fgets(grid[n], 199, f) == NULL) {
        break;
    }
    m = strlen(grid[n]) - 1;
    n++;
  }

  if (mode == 1) {
    // print(grid, n,m);
    roll_north(grid, grid2, n, m);
    printf("Answer: %u\n", get_load(grid2, n, m));
    return 0;
  }

  for (unsigned int step=0; step<1000000000; step++) {
    if (step == 85) {
      step += 93*10752687;
    }

    roll_north(grid, grid2, n, m);
    roll_west(grid2, grid, n, m);
    roll_south(grid, grid2, n, m);
    roll_east(grid2, grid, n, m);

    MD5Context ctx;
    md5Init(&ctx);
    for (int i=0; i<n; i++) {
      md5Update(&ctx, &grid[i], m);
    }
    md5Finalize(&ctx);
    // print_hash(ctx.digest);
  }
  printf("Answer: %u\n", get_load(grid, n, m));

  return 0;
}
