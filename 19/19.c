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


  printf("#include <stdio.h>\n");
  printf("#include \"1.h\"\n");

  while (!feof(f)) {
    char s[200];
    char function_name[5];
    char condition[10];
    char call[10];
    char final[10];

    if (fgets(s, 199, f) == NULL) {
        break;
    }
    if (strlen(s) == 1) break;

    int i = 0;
    int pi;

    while(s[i++] != '{');
    strncpy(function_name, s, i-1);
    function_name[i-1] = '\0';
    printf("int %s(int x, int m, int a, int s) {\n", function_name);
    fprintf(stderr, "int %s(int x, int m, int a, int s);\n", function_name);
    pi = i;

    while(true) {
      if (s[i] == ':') {
        strncpy(condition, &s[pi], i-pi);
        condition[i-pi] = '\0';
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
        printf("}\n\n");
        break;
      }
      i++;
    }
  };


  printf("int main(int argc, char* argv[]) {\n");
  printf("  int result = 0;\n");
  while (!feof(f)) {
    int x, m, a, s;
    fscanf(f, "{x=%d,m=%d,a=%d,s=%d}\n", &x, &m, &a, &s);
    printf("  result += in(%d,%d,%d,%d) * (%d+%d+%d+%d);\n", x,m,a,s, x,m,a,s);
  }
  printf("  printf(\"Answer: %%d\\n\", result);\n");
  printf("}\n");

  return 0;
}
