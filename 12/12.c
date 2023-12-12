#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int expansion = 1;

// '?' could be '.' or '#'

// ???.###   1,1,3  (1)
// ? + ??.###
// . + ??.###  => ??.###  1,1,3  (2)
// # + ??.###  => ??.###  0,1,3  (10)

// (2):
// ? + ?.### could be
// . + ?.###  => ?.###  1,1,3  (3)
// # + ?.###  => ?.###  0,1,3  (8)

// (3):
// ? + .### could be
// . + .###   => .###  1,1,3  (4)
// # + .###   => .###  0,1,3  (5)

// (4):
// . + ###  1,1,3   => no options because left number should be 0 when .

// (5):
// .### 0,1,3  => ### 1,3 (6)

// (6)
// ### 1,3 => ## 0,3 (7)

// (7)
// ## 0,3 => no options because when left number is 0 the left symbol should be .

// (8)
// ? + .### could be
// . + .###  0,1,3  => .### 1,3  (9)
// # + .###  0,1,3  => no options because when the left number is 0 the left symbol should be .

// (9)
// .### 1,3 => no options  => left number is not 0, should be 0 when .

// (10)
// ? + ?.###  0,1,3  could be
// . + ?.###  0,1,3  => ?.###  1,3  (11)
// # + ?.###  0,1,3  => no options because no . when 0

// (11)
// ?.### 1,3 could be
// . + .###  1,3  => no options
// # + .###  1,3  => .### 0,3 (12)

// (12)
// .### 0,3 => ### 3 (13)

// (13)
// ### 3 => ## 2 (14)

// (14)
// ## 2 => # 1 (15)

// (15)
// # 1 => '' 0  (success)


void print_debug(char c, char * s, int a, int b[]) {
  printf("Solving [%c]", c);
  if (c != '\0') {
    printf("[");
    for(int i=0; i<strlen(s); i++) {
      printf("%c", s[i]);
    }
    printf("]");
  }
  printf(" with %d, ", a);
  int nums=0;
  if (a != -1)
  while(true) {
    if (b[nums] == -1) {
      break;
    }
    printf("%d,", b[nums]);
    nums++;
  }
  printf(" (%d extra nums)\n", nums);
}

int solve(char c, char * s, bool in_progress, int a, int b[]) {
  print_debug(c, s, a, b);
  // printf("Solving [%c]", c);
  // if (c != '\0') {
  //   printf("[");
  //   for(int i=0; i<strlen(s); i++) {
  //     printf("%c", s[i]);
  //   }
  //   printf("]");
  // }
  // printf(" with %d, ", a);
  int nums=0;
  if (a != -1)
  while(true) {
    if (b[nums] == -1) {
      break;
    }
    // printf("%d,", b[nums]);
    nums++;
  }
  // printf("\n");
  // printf("nums = %d\n", nums);



  if (c == '\0') {
    if (((a == 0) || (a==-1)) && (nums == 0)) {
      printf("Solution found!\n");
      return 1;
    }
    return 0;
  }

  if ( a == -1 ) {
    return 0;
  }

  if (c == '#') {
    if (a == 0) {
      return 0;
    } else {
      return solve(s[0], &s[1], true, a-1, b);
    }
  } else
  if (c == '.') {
    if (a == 0) {
      return solve(s[0], &s[1], false, b[0], &b[1]);
    } else {
      if (in_progress) {
        return 0;
      } else {
        return solve(s[0], &s[1], false, a, b);
      }
    }
  } else if (c == '?') {
      return solve('#', s, false, a, b) + solve('.', s, false, a, b);
    
  }
}

int main(int argc, const char* argv[]) {
  if (argc < 2) {
    printf("Usage: %s input.txt [expansion]\n", argv[0]);
    return 1;
  }

  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    printf("Error opening file: %s\n", argv[1]);
    return 2;
  }

  if (argc > 2) {
    expansion = atoi(argv[2]);
  }

  int result = 0;
  int a[200];

  char s[200];
  while (!feof(f)) {
    if (fgets(s, 199, f) == NULL) {
        break;
    }
      
    int nums = 0;
    char c = s[0];
    char * s_rest = strchr(s, ' ');
    s_rest[0] = '\0';

    printf("%s\n", &s_rest[1]);
    char * cur = &s_rest[1];
    while (true) {
      int num;
      int bytes_read;
      int res = sscanf(cur, "%d%n", &num, &bytes_read);
      if (res == -1) {
        a[nums] = -1;
        nums++;
        break;
      }
      a[nums] = num;
      nums++;
      cur += bytes_read;
      if (*cur == ',') cur++;
    }

    printf("Solving topmost [%c][%s]\n", c, &s[1]);
    int local = solve(c, &s[1], false, a[0], &a[1]);
    printf("local = %d\n", local);
    result += local;
  };


  // int a[] = {1,1,3, -1};
  // unsigned long int result = solve('?', "??.###", false, a[0], &a[1]);
  // int a[] = {3,2,1,-1};
  // unsigned long int result = solve('?', "###????????", false, a[0], &a[1]);


  printf("Answer: %d\n", result);

  return 0;
}
