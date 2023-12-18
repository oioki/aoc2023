#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int mode = 1;

void print(const char (*g)[350], unsigned int n, unsigned int m) {
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

  char g[275][350];
  for (unsigned int i=0; i<275; i++)
  for (unsigned int j=0; j<350; j++)
    g[i][j] = '.';

  int i = 250;
  int j = 130;
  g[250][130] = '#';

  int imin = 0;
  int imax = 0;
  int jmin = 0;
  int jmax = 0;

  int result = 0;
  while (!feof(f)) {
    char direction;
    int l;
    char rgb[7];
    fscanf(f, "%c %d (#%6s)\n", &direction, &l, rgb);
    printf("[%c][%d][%s]\n", direction, l, rgb);

    if (direction == 'L') {
      for(int dj=1; dj<=l; dj++)
        j--;
        // g[i][j--] = '#';
      if (j<jmin) jmin = j;
    }
    if (direction == 'R') {
      for(int dj=1; dj<=l; dj++)
        // g[i][j++] = '#';
        j++;
      if (j>jmax) jmax = j;
    }
    if (direction == 'D') {
      for(int di=1; di<=l; di++)
        // g[i++][j] = '#';
      i++;
      if (i>imax) imax=i;
    }
    if (direction == 'U') {
      for(int di=1; di<=l; di++)
        // g[i--][j] = '#';
        i--;
      if (i<imin) imin = i;
    }


    result += 1;
  };

  bool found_interior = false;
  for(int i=0; i<275; i++) {
    for(int j=0; j<350; j++) {
      if ( (g[i][j] == '.') && (g[i][j+1] == '#') && (g[i][j+2] == '.') )
      {
        g[i][j+2] = 'p';
        found_interior = true;
        break;
      }
    }

    if (found_interior) break;
  }

  while(true) {
    bool painted_something = false;
    for(int i=0; i<275; i++) {
      for(int j=0; j<350; j++) {
        if ( g[i][j] == 'p' ) {
          if ( (i>0) && (g[i-1][j] == '.') ) {
            painted_something = true;
            g[i-1][j] = 'p';
          }
          if ( (i<500) && (g[i+1][j] == '.') ) {
            painted_something = true;
            g[i+1][j] = 'p';
          }
          if ( (j>0) && (g[i][j-1] == '.') ) {
            painted_something = true;
            g[i][j-1] = 'p';
          }
          if ( (j<500) && (g[i][j+1] == '.') ) {
            painted_something = true;
            g[i][j+1] = 'p';
          }
        }
      }
    }

    if (!painted_something) break;
  }


  // g[250][130] = 'X';
  // printf("i = [%d,%d]\nj = [%d,%d]\n", imin, imax, jmin, jmax);
  print(g, 275, 350);

  int painted = 0;
  for(int i=0; i<275; i++)
  for(int j=0; j<350; j++)
    if ( (g[i][j] == '#') || (g[i][j] == 'p') ) painted++;
  printf("Answer: %d\n", painted);

  return 0;
}
