#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mode = 1;

char * current_s;

void print_debug(char c, const char * s, bool in_progress, int a, const int b[], bool cacheable) {
  printf("Solving [%c]", c);
  if (c != '\0') {
    printf("[");
    int l = strlen(s);
    for(int i=0; i<l; i++) {
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
  int offset_s = s - current_s;
  printf(" (%d extra nums, in progress = %d)\n", nums, in_progress);
  if (cacheable)
  printf("cacheable with key(%d, %d, %d)\n", a+1, offset_s, nums);

}

char input1[200];
char input2[200];
unsigned long long int cache[100][100][100];

// #define return_cache(X) result=X;if (cacheable) {cache[a+1][offset_s][nums] = result;printf("set cache %d,%d,%d to %llu\n", a+1,offset_s, nums, result);}return result;
#define return_cache(X) result=X;if (cacheable) {cache[a+1][offset_s][nums] = result;}return result;

unsigned long long int solve(char c, char * s, bool in_progress, int a, int b[], bool cacheable) {
  // print_debug(c, s, in_progress, a, b, cacheable);

  int nums=0;
  if (a != -1)
  while(true) {
    if (b[nums] == -1) {
      break;
    }
    nums++;
  }

  unsigned long long int result;
  int offset_s = s - current_s;
  if (cacheable) {
    if (cache[a+1][offset_s][nums] == 0xffffffffffffffff) {
      // printf("no cache found tho\n");
    } else {
      // printf("using cached result: %llu\n", cache[a+1][offset_s][nums]);
      return cache[a+1][offset_s][nums];
    }
  }


  if (c == '\0') {
    if (((a == 0) || (a==-1)) && (nums == 0)) {
      return_cache(1);
    }
    return_cache(0);
  }

  if ( a == -1 ) {
    if ((c == '.') || (c=='?')) {
      return_cache(solve(s[0], &s[1], false, -1, 0, false));
    }
    return_cache(0);
  }

  if (c == '#') {
    if (a == 0) {
      return_cache(0);
    } else {
      return_cache(solve(s[0], &s[1], true, a-1, b, false));
    }
  } else
  if (c == '.') {
    if (a == 0) {
      return_cache(solve(s[0], &s[1], false, b[0], &b[1], true));
    } else {
      if (in_progress) {
        return_cache(0);
      } else {
        return_cache(solve(s[0], &s[1], false, a, b, false));
      }
    }
  }

  // assuming c == '?'
  return_cache(solve('#', s, in_progress, a, b, false) + solve('.', s, in_progress, a, b, false));
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

  unsigned long long int result = 0;
  int a1[200];
  int a2[200];

  while (!feof(f)) {
    if (fgets(input1, 199, f) == NULL) {
        break;
    }
      
    int nums = 0;
    char * s_rest = strchr(input1, ' ');
    if (!s_rest) {
      printf("invalid input, separating ' ' not found.\n");
      return 3;
    }
    s_rest[0] = '\0';

    char * cur = &s_rest[1];
    while (true) {
      int num;
      int bytes_read;
      int res = sscanf(cur, "%d%n", &num, &bytes_read);
      if (res == -1) {
        a1[nums] = -1;
        nums++;
        break;
      }
      a1[nums] = num;
      nums++;
      cur += bytes_read;
      if (*cur == ',') cur++;
    }

    for (int i=0; i<100; i++)
    for (int j=0; j<100; j++)
    for (int k=0; k<100; k++)
      cache[i][j][k] = 0xffffffffffffffff;

    if (mode == 2) {
      int l = s_rest - input1;
      for (int i=0; i<5; i++) {
        strncpy(&input2[i*(l+1)], input1, l);
      }
      input2[l] = '?';
      input2[2*l+1] = '?';
      input2[3*l+2] = '?';
      input2[4*l+3] = '?';
      input2[5*l+4] = '\0';

      for (int i=0; i<5*(nums-1); i++) {
        a2[i] = a1[i%(nums-1)];
      }
      a2[5*(nums-1)] = -1;
    }

    unsigned long long int local;
    if (mode == 1) {
      current_s = &input1[0];
      local = solve(input1[0], &input1[1], false, a1[0], &a1[1], false);
    } else {
      current_s = &input2[0];
      local = solve(input2[0], &input2[1], false, a2[0], &a2[1], false);
    }
    
    // printf("local = %llu\n", local);
    result += local;
  };

  printf("Answer: %llu\n", result);

  return 0;
}
