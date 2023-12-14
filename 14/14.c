#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://github.com/Zunawe/md5-c
#include "md5.h"

int mode = 1;
char grid[200][200];
char grid2[200][200];

unsigned int get_load(const char (*g)[200], unsigned int n, unsigned int m) {
  int result = 0;
  for (unsigned int j=0; j<m; j++) {
    for (unsigned int i=0; i<n; i++) {
      if (g[i][j] == 'O') {
        result += n-i;
      }
    }
  }
  return result;
}

void print(const char (*g)[200], unsigned int n, unsigned int m) {
  for (unsigned int i=0; i<n; i++) {
    for (unsigned int j=0; j<m; j++) {
      printf("%c", g[i][j]);
    }
    printf("\n");
  }
  printf("------------------------------------\n");
}

void reset(char (*g)[200], unsigned int n, unsigned int m) {
  for (unsigned int i=0; i<n; i++) {
    for (unsigned int j=0; j<m; j++) {
      g[i][j] = '.';
    }
  }
}

void roll_north(char (*p)[200], char (*q)[200], unsigned int n, unsigned int m) {
  reset(q, n, m);

  for (unsigned int j=0; j<m; j++) {
    unsigned int i_rock = 0;
    for (unsigned int i=0; i<n; i++) {
      if (p[i][j] == 'O') {
        q[i_rock][j] = 'O';
        i_rock++;
      } else if (p[i][j] == '#') {
        q[i][j] = '#';
        i_rock = i+1;
      }
    }
  }
}

void roll_west(char (*p)[200], char (*q)[200], unsigned int n, unsigned int m) {
  reset(q, n, m);

  for (unsigned int i=0; i<n; i++) {
    unsigned int j_rock = 0;
    for (unsigned int j=0; j<n; j++) {
      if (p[i][j] == 'O') {
        q[i][j_rock] = 'O';
        j_rock++;
      } else if (p[i][j] == '#') {
        q[i][j] = '#';
        j_rock = j+1;
      }
    }
  }
}

void roll_south(char (*p)[200], char (*q)[200], unsigned int n, unsigned int m) {
  reset(q, n, m);

  for (unsigned int j=0; j<m; j++) {
    unsigned int i_rock = n-1;
    for (int i=n-1; i>=0; i--) {
      if (p[i][j] == 'O') {
        q[i_rock][j] = 'O';
        i_rock--;
      } else if (p[i][j] == '#') {
        q[i][j] = '#';
        i_rock = i-1;
      }
    }
  }
}

void roll_east(char (*p)[200], char (*q)[200], unsigned int n, unsigned int m) {
  reset(q, n, m);

  for (unsigned int i=0; i<n; i++) {
    unsigned int j_rock = m-1;
    for (int j=m-1; j>=0; j--) {
      if (p[i][j] == 'O') {
        q[i][j_rock] = 'O';
        j_rock--;
      } else if (p[i][j] == '#') {
        q[i][j] = '#';
        j_rock = j-1;
      }
    }
  }
}

void print_hash(const uint8_t *p){
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

  uint8_t hash[1000][16];

  unsigned int cycle_length = 0;
  unsigned int total_steps = 1000000000;
  for (unsigned int step=0; step<total_steps; step++) {
    if (cycle_length > 0) {
      step += cycle_length * ((total_steps-step)/cycle_length);
    }
    // printf("step: %u\n", step);

    roll_north(grid, grid2, n, m);
    roll_west(grid2, grid, n, m);
    roll_south(grid, grid2, n, m);
    roll_east(grid2, grid, n, m);

    if (cycle_length == 0) {
      MD5Context ctx;
      md5Init(&ctx);
      for (unsigned int i=0; i<n; i++) {
        md5Update(&ctx, (uint8_t*)&grid[i], m);
      }
      md5Finalize(&ctx);
      // print_hash(ctx.digest);
      memcpy(hash[step], ctx.digest, 16);

      for (unsigned int k=0; k<step; k++) {
        if (memcmp(ctx.digest, hash[k], 16) == 0) {
          // printf("%d matches %d\n", step, k);
          cycle_length = step - k;
        }
      }
    }
  }
  printf("Answer: %u\n", get_load(grid, n, m));

  return 0;
}
