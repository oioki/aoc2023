#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int calibration_value_mode1(const char * s) {
  int l = strlen(s);

  int i = 0;
  int j = l-1;

  while ( !isdigit(s[i]) ) i++;
  while ( !isdigit(s[j]) ) j--;

  return 10 * (s[i] - '0') + (s[j] - '0');
}


const char * NUMBERS[] = {
  "one",
  "two",
  "three",
  "four",
  "five",
  "six",
  "seven",
  "eight",
  "nine",
};


int str_digit(const char * s) {
  for(int i=0; i<9; i++) {
    if ( strncmp(NUMBERS[i], s, strlen(NUMBERS[i])) == 0 ) {
      return i + 1;
    }
  }

  return -1;
}


int calibration_value_mode2(const char * s) {
  int l = strlen(s);

  int i = 0;
  int d1 = 0;
  int d2 = 0;
  int tmp;

  while ( i < l ) {
    if ( isdigit(s[i]) ) {
      d1 = s[i] - '0';
      break;
    }
    else {
      d1 = str_digit(&s[i]);
      if (d1 != -1) break;
    }

    i++;
  }

  while ( i < l ) {
    if ( isdigit(s[i]) ) {
      d2 = s[i] - '0';
    }
    else {
      tmp = str_digit(&s[i]);
      if (tmp != -1) {
        d2 = tmp;
      }
    }

    i++;
  }

  return 10 * d1 + d2;
}


int main(int argc, const char* argv[]) {
  if (argc < 2) {
    printf("Usage: %s input.txt\n", argv[0]);
    return 1;
  }

  int mode = 1;
  if (argc > 2) {
    mode = atoi(argv[2]);
  }

  FILE * f = fopen(argv[1], "r");
  char s[100];

  int result = 0;
  do {
    fscanf(f, "%99s\n", s);
    result += (mode == 1) ? calibration_value_mode1(s) : calibration_value_mode2(s);
  } while (!feof(f));

  printf("Answer: %d\n", result);

  return 0;
}
