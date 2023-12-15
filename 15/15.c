#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mode = 1;

char s[30000];
int len;


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

  fgets(s, 29999, f);

  unsigned int result = 0;

  int l = strlen(s);
  int current_value = 0;
  for (int i=0; i<l; i++) {
    if ((s[i] == ',') || (s[i] == '\n')) {
      result += current_value;
      current_value = 0;
      continue;
    }

    current_value += s[i];
    current_value *= 17;
    current_value %= 256;
  }

  printf("Answer: %u\n", result);

  return 0;
}
