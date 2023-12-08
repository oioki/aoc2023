#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mode = 1;
int map[800][3];
int l_map = 0;

char path[310];
int len;

int steps_to_reach_z(int pos) {
  int steps = 0;
  while (1)
  for (int c=0; c<len; c++) {
    for (int j=0; j<l_map; j++) {
      if (map[j][0] == pos) {
        if (path[c] == 'L') {
          pos = map[j][1];
        }
        if (path[c] == 'R') {
          pos = map[j][2];
        }
        steps++;
        if (pos%256 == 'Z') {
          return steps;
        }
        break;
      }
    }
  }
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

  fscanf(f, "%309s", path);

  int curpos[10];
  int n_ghosts = 0;

  while (!feof(f)) {
    char node_0[4];
    char node_l[4];
    char node_r[4];
    fscanf(f, "%3s = (%3s, %3s)\n", node_0, node_l, node_r);
    int value_0 = node_0[0] * 256 * 256 + node_0[1] * 256 + node_0[2];
    int value_l = node_l[0] * 256 * 256 + node_l[1] * 256 + node_l[2];
    int value_r = node_r[0] * 256 * 256 + node_r[1] * 256 + node_r[2];

    bool found = false;
    for (int i=0; i<l_map; i++) {
      if ( path[i] == value_0 ) {
        found = true;
        break;
      }
    }

    if (!found) {
      if (node_0[2] == 'A') {
        curpos[n_ghosts] = node_0[0]*256*256 + node_0[1]*256 + node_0[2];
        n_ghosts++;
      }
      map[l_map][0] = value_0;
      map[l_map][1] = value_l;
      map[l_map][2] = value_r;
      l_map++;
    }
  }

  int steps = 0;
  len = strlen(path);

  for(int g=0; g<n_ghosts; g++) {
    printf("steps for %d ghost: %d\n", g, steps_to_reach_z(curpos[g]));
  }

  return 0;
}
