#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mode = 1;

#define UP 0
#define LEFT 1
#define RIGHT 2
#define DOWN 3


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

  int loop_length = 1;

  // all inputs have valid tile down from the start.
  // let's cut the corner here but it's possible to add
  // checks for other cases
  int i_next = i_start + 1;
  int j_next = j_start;
  int direction = DOWN;

  while(1) {
    // printf("considering grid[%d,%d] = %c, direction = %d\n", i_next, j_next, grid[i_next][j_next], direction);
    if (grid[i_next][j_next] == 'S') break;

    part_of_loop[i_next][j_next] = true;
    loop_length++;

    if (direction == UP) {
      if (grid[i_next][j_next] == '|') {
        i_next--;
      }
      else if (grid[i_next][j_next] == 'F') {
        j_next++;
        direction = RIGHT;
      }
      else if (grid[i_next][j_next] == '7') {
        j_next--;
        direction = LEFT;
      }
    }
    else if (direction == LEFT) {
      if (grid[i_next][j_next] == '-') {
        j_next--;
      }
      else if (grid[i_next][j_next] == 'L') {
        i_next--;
        direction = UP;
      }
      else if (grid[i_next][j_next] == 'F') {
        i_next++;
        direction = DOWN;
      }
    }
    else if (direction == RIGHT) {
      if (grid[i_next][j_next] == '-') {
        j_next++;
      }
      else if (grid[i_next][j_next] == '7') {
        i_next++;
        direction = DOWN;
      }
      else if (grid[i_next][j_next] == 'J') {
        i_next--;
        direction = UP;
      }
    }
    else if (direction == DOWN) {
      if (grid[i_next][j_next] == '|') {
        i_next++;
      }
      else if (grid[i_next][j_next] == 'J') {
        j_next--;
        direction = LEFT;
      }
      else if (grid[i_next][j_next] == 'L') {
        j_next++;
        direction = RIGHT;
      }
    }
  }


  printf("Max distance: %d\n", loop_length/2);

  // grid[i_start][j_start] = 'F';  // example1, example2, example3
  grid[i_start][j_start] = '7';  // input, example4


  int area = 0;
  for (int i=0; i<n; i++) {
    bool inside = false;
    char prev_symbol = '.';

    for (int j=0; j<m; j++) {
      if (!part_of_loop[i][j]) {
        if (inside) area++;
      }

      if (part_of_loop[i][j]) {
        char c = grid[i][j];

        if (c == '|') {
          inside = !inside;
        } else if (c == 'F') {
          if (prev_symbol == 'J') {
            inside = !inside;
          } else {
            prev_symbol = c;
          }
        } else if (c == 'L') {
          if (prev_symbol == '7') {
            inside = !inside;
          } else {
            prev_symbol = c;
          }
        } else if (c == '7') {
          if (prev_symbol == 'L') {
            inside = !inside;
          } else if (prev_symbol != 'F') {
            prev_symbol = c;
          }
        } else if (c == 'J') {
          if (prev_symbol == 'F') {
            inside = !inside;
          } else if (prev_symbol != 'L') {
            prev_symbol = c;
          }
        }
      }
    }
  }

  printf("Area: %d\n", area);

  return 0;
}
