#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "qsort.h"


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

  int result = 0;

  char s[120];
  while (!feof(f)) {
    if (fgets(s, 119, f) == NULL) {
        break;
    }

    char * cur;
    int num;
    int bytes_read;
    cur = s + 5;

    sscanf(cur, "%d%n", &num, &bytes_read);
    cur += bytes_read + 2;  // skip "Card X: "

    int winning_numbers[10];
    int numbers_you_have[50];
    int i_wn = 0;
    int i_nyh = 0;

    int res;
    while ((res = sscanf(cur, "%d%n", &num, &bytes_read)) == 1) {
      winning_numbers[i_wn++] = num;
      cur += bytes_read + 1;
    };

    cur += 2;
    while ((res = sscanf(cur, "%d%n", &num, &bytes_read)) == 1) {
      numbers_you_have[i_nyh++] = num;
      cur += bytes_read + 1;
    };

    quickSort(winning_numbers, 0, i_wn-1);
    quickSort(numbers_you_have, 0, i_nyh-1);

    int i = 0;
    int j = 0;
    int value = 0;
    while ( (i<i_wn) && (j<i_nyh)) {
        if (winning_numbers[i] == numbers_you_have[j]) {
            value = (value == 0) ? 1 : 2*value;
            i++;
            j++;
            continue;
        } else if (winning_numbers[i] < numbers_you_have[j]) {
            i++;
        } else {
            j++;
        }
    }
    // printf("Value: %d\n", value);
    result += value;
  }

  printf("Answer: %d\n", result);

  return 0;
}
