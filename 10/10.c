#include <ctype.h>
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

  if (argc > 3) {
    mode = atoi(argv[2]);
  }

  char grid[200][200];
  // int dist[200][200];
  int n = 0;

  // char s[200];
  while (!feof(f)) {
    if (fgets(grid[n], 199, f) == NULL) {
        break;
    }
    n++;
  }

  // for (int i=0; i<n; i++) {
  //   for (int j=0; j<n; j++) {
  //     dist[i][j] = -1;
  //   }
  // }

  int i_start = 0;
  int j_start = 0;
  for (int i=0; i<n; i++) {
    for (int j=0; j<n; j++) {
      if (grid[i][j] == 'S') {
        i_start = i;
        j_start = j;
        // dist[i][j] = 0;
      }
    }
  }

  // printf("%c\n", grid[i_start-1][j_start]);
  // printf("%c\n", grid[i_start][j_start-1]);
  // printf("%c\n", grid[i_start][j_start+1]);
  // printf("%c\n", grid[i_start+1][j_start]);

  int prevdist = 0;

  // example1
  // int i_next = i_start;
  // int j_next = j_start+1;
  // int direction = 2;

  // example2
  // int i_next = i_start;
  // int j_next = j_start+1;
  // int direction = 2;

  // input
  int i_next = i_start + 1;
  int j_next = j_start;
  int direction = 3;

  while(1) {
    // printf("considering grid[%d,%d] = %c, direction = %d\n", i_next, j_next, grid[i_next][j_next], direction);
    if (grid[i_next][j_next] == 'S') break;
    if (direction == 0) {
      if (grid[i_next][j_next] == '|') {
        // dist[i_next][j_next] = prevdist+1;
        prevdist++;
        i_next--;
        direction = 0;
      }
      else if (grid[i_next][j_next] == 'F') {
        // dist[i_next][j_next] = prevdist+1;
        prevdist++;
        j_next++;
        direction = 2;
      }
      else if (grid[i_next][j_next] == '7') {
        // dist[i_next][j_next] = prevdist+1;
        prevdist++;
        j_next--;
        direction = 1;
      }
    }
    else if (direction == 1) {
      if (grid[i_next][j_next] == '-') {
        // dist[i_next][j_next] = prevdist+1;
        prevdist++;
        j_next--;
        direction = 1;
      }
      else if (grid[i_next][j_next] == 'L') {
        // dist[i_next][j_next] = prevdist+1;
        prevdist++;
        i_next--;
        direction = 0;
      }
      else if (grid[i_next][j_next] == 'F') {
        // dist[i_next][j_next] = prevdist+1;
        prevdist++;
        i_next++;
        direction = 3;
      }
    }
    else if (direction == 2) {
      if (grid[i_next][j_next] == '-') {
        // dist[i_next][j_next] = prevdist+1;
        prevdist++;
        j_next++;
        direction = 2;
      }
      else if (grid[i_next][j_next] == '7') {
        // dist[i_next][j_next] = prevdist+1;
        prevdist++;
        i_next++;
        direction = 3;
      }
      else if (grid[i_next][j_next] == 'J') {
        // dist[i_next][j_next] = prevdist+1;
        prevdist++;
        i_next--;
        direction = 0;
      }
    }
    else if (direction == 3) {
      if (grid[i_next][j_next] == '|') {
        // dist[i_next][j_next] = prevdist+1;
        prevdist++;
        i_next++;
        direction = 3;
      }
      else if (grid[i_next][j_next] == 'J') {
        // dist[i_next][j_next] = prevdist+1;
        prevdist++;
        j_next--;
        direction = 1;
      }
      else if (grid[i_next][j_next] == 'L') {
        // dist[i_next][j_next] = prevdist+1;
        prevdist++;
        j_next++;
        direction = 2;
      }
    }
  }


  // output dist map
  // for (int i=0; i<n; i++) {
  //   for (int j=0; j<n; j++) {
  //     printf("%d ", dist[i][j]);
  //   }
  //   printf("\n");
  // }

  printf("Loop dist: %d\n", prevdist+1);
  printf("Answer: %d\n", (prevdist+1)/2);

  return 0;
}
