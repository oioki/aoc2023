#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char ss[20000];
int rows;
int cols;

int is_adjacent_to_symbol(int i0, int j0, int l) {
    int i, j;
    for (i=i0-1; i<=i0+1; i++) {
        if ( i == -1 ) continue;
        if ( i == rows ) continue;
        for (j=j0-1; j<=j0+l; j++) {
            if ( j == -1 ) continue;
            if ( j == cols ) continue;
            char c = ss[i*(cols+1)+j];
            if ( !isdigit(c) && (c != '.') ) {
                return 1;
            }
        }
    }
    return 0;
}

typedef struct gear {
    int i;
    int j;
    int num;
} gear;

# define MAX_GEARS 500
gear gears[MAX_GEARS];
int num_gears = 0;

int specific_gear_ratio(int num, int i, int j) {
    // try to find the same gear
    // O(num_gears) is suboptimal but works fine so far
    for (int k=0; k<num_gears; k++) {
        if ((gears[k].i == i) && (gears[k].j == j)) {
            // return product once the second number for the gear is found
            // it is guaranteed that there are only 2 max numbers for a gear
            return gears[k].num * num;
        }
    }

    gear g = {i, j, num};
    gears[num_gears] = g;
    num_gears++;

    if (num_gears > MAX_GEARS) {
        return -1;
    }

    return 0;
}

int gear_ratio_if_second_adjacent_number(int i0, int j0, int l, int num) {
    int i, j;
    for (i=i0-1; i<=i0+1; i++) {
        if ( i == -1 ) continue;
        if ( i == rows ) continue;
        for (j=j0-1; j<=j0+l; j++) {
            if ( j == -1 ) continue;
            if ( j == cols ) continue;
            char c = ss[i*(cols+1)+j];
            if ( c == '*' ) {
                // printf("number (%d = %d,%d,%d) is adjacent to gear (%d,%d)\n", num, i0, j0, l, i, j);
                return specific_gear_ratio(num, i, j);
            }
        }
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

  int mode = 1;
  if (argc > 2) {
    mode = atoi(argv[2]);
  }

  int bytes_read = fread(ss, 1, 19999, f);
  fclose(f);

  const char * eol_position = strchr(ss, '\n');
  if (eol_position == NULL) {
    printf("Could not find the end of the line.\n");
    return 3;
  }
  cols = eol_position - ss;
  rows = bytes_read / (cols + 1);

  int result = 0;

  int i, j;
  for (i=0; i<rows; i++) {
    int jstart = -1;
    int num = 0;
    for (j=0; j<cols+1; j++) {  // take '\n' into account
        char c = ss[i*(cols+1)+j];
        if (isdigit(c)) {
            if (jstart == -1) {
                jstart = j;
            }
            num = 10*num + (c - '0');
        }
        else
        {
            if (num != 0) {
                // printf("check number %d at (%d, %d), len = %d\n", num, i, jstart, j-jstart);
                if (mode == 1) {
                    if (is_adjacent_to_symbol(i, jstart, j-jstart)) result += num;
                } else {
                    int gear_ratio = gear_ratio_if_second_adjacent_number(i, jstart, j-jstart, num);
                    if (gear_ratio == -1) {
                        printf("Gear storage overflow!\n");
                        return 4;
                    }
                    result += gear_ratio;
                }

                jstart = -1;
            }

            num = 0;
        }
    }
  }

  printf("Answer: %d\n", result);

  return 0;
}
