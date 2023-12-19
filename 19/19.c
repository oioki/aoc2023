#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ixmas(char c) {
  if (c=='x') return 0;
  if (c=='m') return 1;
  if (c=='a') return 2;
  return 3;  // 's'
}

int main(int argc, const char* argv[]) {
  if (argc < 3) {
    printf("Usage: %s input.txt ranges.txt\n", argv[0]);
    return 1;
  }

  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    printf("Error opening input file: %s\n", argv[1]);
    return 2;
  }

  FILE * fr = fopen("ranges.txt", "w");
  if (fr == NULL) {
    fclose(f);
    printf("Error opening ranges file: %s\n", argv[1]);
    return 3;
  }

  // 4 indices are: x m a s
  int n_ranges[4] = {1,1,1,1};
  int ranges[4][500];
  ranges[0][0] = 1;
  ranges[1][0] = 1;
  ranges[2][0] = 1;
  ranges[3][0] = 1;

  printf("#include \"lib.h\"\n\n");

  while (!feof(f)) {
    char s[200];
    char function_name[5];
    char condition[10];
    char call[10];
    char final[10];

    if (fgets(s, 199, f) == NULL) {
        break;
    }
    if (s[0] == '\n') break;

    int i = 0;
    int pi;

    while(s[i++] != '{');
    strncpy(function_name, s, i-1);
    function_name[i-1] = '\0';
    printf("int %s(int x, int m, int a, int s) {\n", function_name);
    fprintf(stderr, "int %s(int x, int m, int a, int s);\n", function_name);
    pi = i;

    while(1) {
      if (s[i] == ':') {
        strncpy(condition, &s[pi], i-pi);
        condition[i-pi] = '\0';

        int ix = ixmas(condition[0]);
        int number = atoi(&condition[2]);
        int in = n_ranges[ix];
        if (condition[1] == '>') {
          ranges[ix][in] = number + 1;
        } else { // '<'
          ranges[ix][in] = number;
        }
        n_ranges[ix]++;

        printf("  if (%s) return ", condition);
        pi = ++i;
      } else if (s[i] == ',') {
        strncpy(call, &s[pi], i-pi);
        call[i-pi] = '\0';
        if (call[0] == 'A') {
          printf("1;\n");
        } else if (call[0] == 'R') {
          printf("0;\n");
        } else {
          printf("%s(x,m,a,s);\n", call);
        }
        pi = ++i;
      } else if (s[i] == '}') {
        strncpy(final, &s[pi], i-pi);
        final[i-pi] = '\0';
        printf("  return ");
        if (final[0] == 'A') {
          printf("1;\n");
        } else if (final[0] == 'R') {
          printf("0;\n");
        } else {
          printf("%s(x,m,a,s);\n", final);
        }
        printf("}\n");
        break;
      }
      i++;
    }
  };


  for (int ii=0; ii<4; ii++)
  for (int ix=0; ix<n_ranges[ii]; ix++)
    fprintf(fr, "%d %d\n", ii, ranges[ii][ix]);
  fclose(fr);

  return 0;
}
