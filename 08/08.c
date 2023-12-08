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

  if (argc > 2) {
    mode = atoi(argv[2]);
  }

  char path[310];
  fscanf(f, "%309s", path);

  int map[800][3];
  int l_map = 0;

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
      map[l_map][0] = value_0;
      map[l_map][1] = value_l;
      map[l_map][2] = value_r;
      l_map++;
    }
  }

  int curpos = 'A'*256*256 + 'A'*256+'A';
  int steps = 0;
  int len = strlen(path);

  while (1)
  for (int c=0; c<len; c++) {
    for (int j=0; j<l_map; j++) {
      if (map[j][0] == curpos) {
        if (path[c] == 'L') {
          curpos = map[j][1];
        }
        if (path[c] == 'R') {
          curpos = map[j][2];
        }
        steps++;
        if (curpos == 'Z'*256*256 + 'Z'*256 + 'Z') {
          printf("Answer: %d\n", steps);
          return 0;
        }
        break;
      }
    }

  }

  int result = 77777;
  printf("Answer: %i\n", result);

  return 0;
}
