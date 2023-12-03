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
  cols = strchr(ss, '\n') - ss;
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
                if (is_adjacent_to_symbol(i, jstart, j-jstart)) result += num;
                jstart = -1;
            }

            num = 0;
        }
    }
  }

  printf("Answer: %d\n", result);

  return 0;
}
