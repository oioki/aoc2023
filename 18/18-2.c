#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

unsigned char hex(char h) {
  if ( ('0' <= h) && (h <= '9') ) return h - '0';
  return 10 + h - 'a';
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

  long long int iprev = 0;
  long long int jprev = 0;
  long long int area = 0;

  long long int perimeter = 0;
  while (!feof(f)) {
    char rgb[7];
    char direction;
    long long int l;

    if (mode == 1) {
      fscanf(f, "%c %lld (#%6s)\n", &direction, &l, rgb);
    } else {
      fscanf(f, "%*c %*d (#%6s)\n", rgb);

      l = hex(rgb[0])*16*16*16*16 + hex(rgb[1])*16*16*16 + hex(rgb[2])*16*16 + hex(rgb[3])*16 + hex(rgb[4]);
      if (rgb[5] == '0') direction = 'R';
      if (rgb[5] == '1') direction = 'D';
      if (rgb[5] == '2') direction = 'L';
      if (rgb[5] == '3') direction = 'U';
    }

    long long int i;
    long long int j;

    if (direction == 'R') {
      i = iprev;
      j = jprev + l;
    }
    if (direction == 'D') {
      i = iprev + l;
      j = jprev;
    }
    if (direction == 'L') {
      i = iprev;
      j = jprev - l;
    }
    if (direction == 'U') {
      i = iprev - l;
      j = jprev;
    }

    // https://en.wikipedia.org/wiki/Shoelace_formula
    area += (iprev + i) * (jprev - j);
    perimeter += llabs(iprev-i) + llabs(jprev-j);

    iprev = i;
    jprev = j;
  };

  // i = 0, j = 0
  // (iprev + 0) * (jprev - 0) == iprev * jprev
  area += iprev * jprev;

  // printf("Perimeter: %lld\n", perimeter);
  printf("Answer: %lld\n", llabs(area / 2) + perimeter / 2 + 1);

  return 0;
}
