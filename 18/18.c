#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 500

void print(const char (*g)[SIZE], unsigned int n, unsigned int m) {
  for (unsigned int i=0; i<n; i++) {
    for (unsigned int j=0; j<m; j++) {
      printf("%c", g[i][j]);
    }
    printf("\n");
  }
  printf("------------------------------------\n");
}


int main(int argc, const char* argv[]) {
  if (argc < 2) {
    printf("Usage: %s input.txt\n", argv[0]);
    return 1;
  }

  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    printf("Error opening file: %s\n", argv[1]);
    return 2;
  }

  char g[SIZE][SIZE];
  for (unsigned int i=0; i<SIZE; i++)
  for (unsigned int j=0; j<SIZE; j++)
    g[i][j] = '.';

  int icur = SIZE / 2;
  int jcur = SIZE / 2;
  g[icur][jcur] = '#';

  while (!feof(f)) {
    char direction;
    int l;
    char rgb[7];
    fscanf(f, "%c %d (#%6s)\n", &direction, &l, rgb);

    if (direction == 'L') {
      if (jcur - l < 0) {
        printf("Canvas is too small, attempted overflow at %d,%d.\n", icur, jcur - l);
        return 4;
      }

      for(int dj=1; dj<=l; dj++)
        g[icur][jcur--] = '#';
    }
    if (direction == 'R') {
      if (jcur + l >= SIZE) {
        printf("Canvas is too small, attempted overflow at %d,%d.\n", icur, jcur + l);
        return 4;
      }

      for(int dj=1; dj<=l; dj++)
        g[icur][jcur++] = '#';
    }
    if (direction == 'D') {
      if (icur + l >= SIZE) {
        printf("Canvas is too small, attempted overflow at %d,%d.\n", icur + l, jcur);
        return 4;
      }

      for(int di=1; di<=l; di++)
        g[icur++][jcur] = '#';
    }
    if (direction == 'U') {
      if (icur - l < 0) {
        printf("Canvas is too small, attempted overflow at %d,%d.\n", icur - l, jcur);
        return 4;
      }

      for(int di=1; di<=l; di++)
        g[icur--][jcur] = '#';
    }
  };


  // find the inside
  bool found_interior = false;
  for(int i=1; i<SIZE-2; i++) {
    for(int j=1; j<SIZE-2; j++) {
      if ( (g[i][j] == '.') && (g[i][j+1] == '#') && (g[i][j+2] == '.') )
      {
        g[i][j+2] = 'p';
        found_interior = true;
        break;
      }
    }

    if (found_interior) break;
  }


  // paint iteratively
  while(true) {
    bool painted_something = false;
    for(int i=1; i<SIZE-1; i++) {
      for(int j=1; j<SIZE-1; j++) {
        if ( g[i][j] == 'p' ) {
          if ( g[i-1][j] == '.' ) {
            painted_something = true;
            g[i-1][j] = 'p';
          }

          if ( g[i+1][j] == '.' ) {
            painted_something = true;
            g[i+1][j] = 'p';
          }

          if ( g[i][j-1] == '.' ) {
            painted_something = true;
            g[i][j-1] = 'p';
          }

          if ( g[i][j+1] == '.' ) {
            painted_something = true;
            g[i][j+1] = 'p';
          }
        }
      }
    }

    if (!painted_something) break;
  }

  // print(g, SIZE, SIZE);

  int painted = 0;
  for(int i=0; i<SIZE; i++)
  for(int j=0; j<SIZE; j++)
    if ( (g[i][j] == '#') || (g[i][j] == 'p') ) painted++;
  printf("Answer: %d\n", painted);

  return 0;
}
