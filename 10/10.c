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
  bool part_of_loop[200][200];
  int n = 0;
  int m = 0;

  while (!feof(f)) {
    if (fgets(grid[n], 199, f) == NULL) {
        break;
    }
    m = strlen(grid[n]) - 1;
    n++;
  }

  for (int i=0; i<n; i++) {
    for (int j=0; j<m; j++) {
      part_of_loop[i][j] = false;
    }
  }

  int i_start = 0;
  int j_start = 0;
  for (int i=0; i<n; i++) {
    for (int j=0; j<m; j++) {
      if (grid[i][j] == 'S') {
        i_start = i;
        j_start = j;
        part_of_loop[i][j] = true;
      }
    }
  }

  // printf("%c\n", grid[i_start-1][j_start]);
  // printf("%c\n", grid[i_start][j_start-1]);
  // printf("%c\n", grid[i_start][j_start+1]);
  // printf("%c\n", grid[i_start+1][j_start]);

  int loop_length = 1;

  // example1, example2, example3
  // int i_next = i_start;
  // int j_next = j_start+1;
  // int direction = 2;

  // input, example4
  int i_next = i_start + 1;
  int j_next = j_start;
  int direction = 3;

  while(1) {
    // printf("considering grid[%d,%d] = %c, direction = %d\n", i_next, j_next, grid[i_next][j_next], direction);
    if (grid[i_next][j_next] == 'S') break;
    if (direction == 0) {
      if (grid[i_next][j_next] == '|') {
        part_of_loop[i_next][j_next] = true;
        loop_length++;
        i_next--;
        direction = 0;
      }
      else if (grid[i_next][j_next] == 'F') {
        part_of_loop[i_next][j_next] = true;
        loop_length++;
        j_next++;
        direction = 2;
      }
      else if (grid[i_next][j_next] == '7') {
        part_of_loop[i_next][j_next] = true;
        loop_length++;
        j_next--;
        direction = 1;
      }
    }
    else if (direction == 1) {
      if (grid[i_next][j_next] == '-') {
        part_of_loop[i_next][j_next] = true;
        loop_length++;
        j_next--;
        direction = 1;
      }
      else if (grid[i_next][j_next] == 'L') {
        part_of_loop[i_next][j_next] = true;
        loop_length++;
        i_next--;
        direction = 0;
      }
      else if (grid[i_next][j_next] == 'F') {
        part_of_loop[i_next][j_next] = true;
        loop_length++;
        i_next++;
        direction = 3;
      }
    }
    else if (direction == 2) {
      if (grid[i_next][j_next] == '-') {
        part_of_loop[i_next][j_next] = true;
        loop_length++;
        j_next++;
        direction = 2;
      }
      else if (grid[i_next][j_next] == '7') {
        part_of_loop[i_next][j_next] = true;
        loop_length++;
        i_next++;
        direction = 3;
      }
      else if (grid[i_next][j_next] == 'J') {
        part_of_loop[i_next][j_next] = true;
        loop_length++;
        i_next--;
        direction = 0;
      }
    }
    else if (direction == 3) {
      if (grid[i_next][j_next] == '|') {
        part_of_loop[i_next][j_next] = true;
        loop_length++;
        i_next++;
        direction = 3;
      }
      else if (grid[i_next][j_next] == 'J') {
        part_of_loop[i_next][j_next] = true;
        loop_length++;
        j_next--;
        direction = 1;
      }
      else if (grid[i_next][j_next] == 'L') {
        part_of_loop[i_next][j_next] = true;
        loop_length++;
        j_next++;
        direction = 2;
      }
    }
  }


  printf("Max distance: %d\n", loop_length/2);

  // grid[i_start][j_start] = 'F';  // example1, example2, example3
  grid[i_start][j_start] = '7';  // input, example4


  bool inside = false;
  int num_inside = 0;
  char prev_symbol = '.';
  for (int i=0; i<n; i++) {
    inside = false;
    prev_symbol = '.';
    for (int j=0; j<m; j++) {
      if (!part_of_loop[i][j]) {
        if (inside) {
          num_inside++;
          // printf("[%d %d]\n", i, j);
        } else {
                  prev_symbol = '.';
        }
      }
      if (part_of_loop[i][j]) {
        char c = grid[i][j];

        if (c == '|') {
          inside = !inside;
            // printf("{%d %d} %d\n", i, j, inside);
            prev_symbol = '.';
        } else
        if (c == 'F') {
          if (prev_symbol == 'J') {
            inside = !inside;
            // printf("{%d %d} %d\n", i, j, inside);
            prev_symbol = '.';
          } else
          {
            prev_symbol = c;
          }
        } else if (c=='L') {
          if (prev_symbol == '7') {
            inside = !inside;
            // printf("{%d %d} %d\n", i, j, inside);
            prev_symbol = '.';
          }
          else
          {
            prev_symbol = c;
          }
        } else if (c=='7') {
          if (prev_symbol == 'L') {
            inside = !inside;
            // printf("{%d %d} %d\n", i, j, inside);
            prev_symbol = '.';
          } else if (prev_symbol == 'F') {
            prev_symbol = '.';
          }
          else
          {
            prev_symbol = c;
          }
        } else         if (c == 'J') {
          if (prev_symbol == 'F') {
            inside = !inside;
            // printf("{%d %d} %d\n", i, j, inside);
            prev_symbol = '.';
          } else if (prev_symbol == 'L') {
            prev_symbol = '.';
          } else
          {
            prev_symbol = c;
          }
        }
      }
    }
  }

  printf("Area: %d\n", num_inside);

  return 0;
}
