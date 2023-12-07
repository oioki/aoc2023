#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mode = 1;

unsigned int card_power(char c) {
  if (mode == 1) {
    if ( ('2' <= c) && (c <= '9') ) {
      return c - '2';
    }
    if ( c == 'T' ) return 8;
    if ( c == 'J' ) return 9;
  }

  if (mode == 2) {
    if ( c == 'J' ) return 0;
    if ( ('2' <= c) && (c <= '9') ) {
      return c - '2' + 1;
    }
    if ( c == 'T' ) return 9;
  }

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

#define FIVE_OF_A_KIND  6
#define FOUR_OF_A_KIND  5
#define FULL_HOUSE      4
#define THREE_OF_A_KIND 3
#define TWO_PAIR        2
#define ONE_PAIR        1
#define HIGH_CARD       0

int get_hand_type(int max_matches, int cnt_max_matches, int pre_max_matches, int cnt_pre_max_matches, int n_jokers) {
  if (mode == 1) n_jokers = 0;

  if (n_jokers == 5) return FIVE_OF_A_KIND;

  if (max_matches == 5) return FIVE_OF_A_KIND;

  if (max_matches == 4) {
    if (n_jokers == 1) return FIVE_OF_A_KIND;
    return FOUR_OF_A_KIND;
  }

  if ( (max_matches == 3) && (pre_max_matches == 2) && (cnt_pre_max_matches == 2) ) {
    return FULL_HOUSE;
  }

  if (max_matches == 3) {
    if (n_jokers == 2) return FIVE_OF_A_KIND;
    if (n_jokers == 1) return FOUR_OF_A_KIND;
    return THREE_OF_A_KIND;
  }

  if ( (max_matches == 2) && (cnt_max_matches == 2) ) {
      if (n_jokers == 1) return FULL_HOUSE;
      return TWO_PAIR;
  }

  if (max_matches == 2) {
    if (n_jokers == 3) return FIVE_OF_A_KIND;
    if (n_jokers == 2) return FOUR_OF_A_KIND;
    if (n_jokers == 1) return THREE_OF_A_KIND;
    return ONE_PAIR;
  }

  // High card
  if (n_jokers == 4) return FIVE_OF_A_KIND;
  if (n_jokers == 3) return FOUR_OF_A_KIND;
  if (n_jokers == 2) return THREE_OF_A_KIND;
  if (n_jokers == 1) return ONE_PAIR;
  return HIGH_CARD;
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
    int n_jokers = 0;
    for (i=0; i<5; i++)
    {
      if (s[i] == 'J') n_jokers++;

      int cnt=0;
      for (a=i+0; a<5; a++)
      {
        if (mode == 1) {
          if ( s[a] == s[i] )
          {
            cnt++;
          }
        } else
        {  // mode == 2
          if ( (s[a] == s[i]) && (s[i] != 'J') )
          {
            cnt++;
          }
        }
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
    // printf("n jokers: %d\n", n_jokers);
    // printf("max match: %d, num matches: %d;    pre-max match: %d, num: %d\n", max_matches, cnt_max_matches, pre_max_matches, cnt_pre_max_matches);

    // printf("%s: ", s);
    values[n_hands] = get_hand_type(max_matches, cnt_max_matches, pre_max_matches, cnt_pre_max_matches, n_jokers);
    // switch(values[n_hands]) {
    //   case FIVE_OF_A_KIND: printf("Five of a kind");break;
    //   case FOUR_OF_A_KIND: printf("Four of a kind");break;
    //   case FULL_HOUSE    : printf("Full house");break;
    //   case THREE_OF_A_KIND: printf("Three of a kind");break;
    //   case TWO_PAIR      : printf("Two pair");break;
    //   case ONE_PAIR      : printf("One pair");break;
    //   case HIGH_CARD     : printf("High card");break;
    // }
    // printf("\n");

    powers[n_hands] = hand_power(s);

    n_hands++;
  }

  int i;
  for (i=0; i<n_hands; i++) {
    // printf("[%s]: value %d, power %u\n", hands[i], values[i], powers[i]);
  }


  unsigned int result = 0;

  // bubble sort
  int j;
  int rank;
  for (i=0; i<n_hands; i++) {
    rank = 1;
    for (j=0; j<n_hands; j++) {
      if ( (values[i] > values[j]) ||
           ( (values[i] == values[j]) && (powers[i] > powers[j]) ) ) {
          rank++;
      }
    }
    // printf("rank %s %d %d\n", hands[i], values[i], rank);
    result += rank * bids[i];
  }

  printf("Answer: %u\n", result);

  return 0;
}
