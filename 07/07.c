#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int card_power(char c) {
  if ( ('2' <= c) && (c <= '9') ) {
    return c - '2';
  }
  if ( c == 'T' ) return 8;
  if ( c == 'J' ) return 9;
  if ( c == 'Q' ) return 10;
  if ( c == 'K' ) return 11;
  return 12;  // c == 'A'
}

unsigned int hand_power(const char * hand) {
  unsigned int sum = 0;
  for (int i=0; i<5; i++) {
    sum = sum*13 + card_power(hand[i]);
  }
  return sum;
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

  char hands[1000][6];
  int bids[1000];
  int values[1000];
  unsigned int powers[1000];
  int n_hands = 0;
  while (!feof(f)) {
    fscanf(f, "%5s %d\n", (char*)&hands[n_hands], &bids[n_hands]);

    values[n_hands] = 0;
    const char * s = hands[n_hands];

    int a,i;
    int max_matches = 0;
    int cnt_max_matches = 0;
    int pre_max_matches = 0;
    int cnt_pre_max_matches = 0;
    for (i=0; i<5; i++)
    {
      int cnt=0;
      for (a=i+0; a<5; a++)
      {
        if (s[a] == s[i]) cnt++;
      }

      if (cnt > max_matches) {
        pre_max_matches = max_matches;
        cnt_pre_max_matches = cnt_max_matches;

        max_matches = cnt;
        cnt_max_matches = 1;
      }
      else if (cnt == max_matches) {
        cnt_max_matches ++;
      } else if (cnt > pre_max_matches) {
        pre_max_matches = cnt;
        cnt_pre_max_matches = 1;
      } else if (cnt == pre_max_matches) {
        cnt_pre_max_matches ++;
      }
    }
    // printf("max match: %d, num matches: %d;    pre-max match: %d, num: %d\n", max_matches, cnt_max_matches, pre_max_matches, cnt_pre_max_matches);

    printf("%s: ", s);
    if (max_matches == 5) {
      printf("Five of a kind\n");
      values[n_hands] = 6;
    } else if (max_matches == 4) {
      printf("Four of a kind\n");
      values[n_hands] = 5;
    } else if ( (max_matches == 3) && (pre_max_matches == 2) && (cnt_pre_max_matches == 2) ) {
      printf("Full house\n");
      values[n_hands] = 4;
    } else if (max_matches == 3) {
      printf("Three of a kind\n");
      values[n_hands] = 3;
    } else if ( (max_matches == 2) && (cnt_max_matches == 2) ) {
      printf("Two pair\n");
      values[n_hands] = 2;
    } else if (max_matches == 2) {
      printf("One pair\n");
      values[n_hands] = 1;
    } else {
      printf("High card\n");
      values[n_hands] = 0;
    }
    powers[n_hands] = hand_power(s);

    n_hands++;
  }

  int i;
  for (i=0; i<n_hands; i++) {
    printf("[%s]: value %d, power %u\n", hands[i], values[i], powers[i]);
  }


  unsigned int result = 0;

  // bubble sort
  int j;
  for (i=0; i<n_hands; i++) {
    result += bids[i];
    for (j=0; j<n_hands; j++) {
      if ( (values[i] > values[j]) ||
           ( (values[i] == values[j]) && (powers[i] > powers[j]) ) ) {
          // swap i and j
          result += bids[i];
      }
    }
  }

  printf("Answer: %u\n", result);

  return 0;
}
