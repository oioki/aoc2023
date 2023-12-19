#include <stdio.h>
#include "bubble.h"
#include "lib.h"

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

  FILE * f2 = fopen(argv[2], "r");
  if (f2 == NULL) {
    fclose(f);
    printf("Error opening ranges file: %s\n", argv[2]);
    return 3;
  }


  while (!feof(f)) {
    char s[200];

    if (fgets(s, 199, f) == NULL) {
        break;
    }
    if (s[0] == '\n') break;
  }

  int result = 0;
  unsigned long long int result2 = 0;
  while (!feof(f)) {
    int x, m, a, s;
    fscanf(f, "{x=%d,m=%d,a=%d,s=%d}\n", &x, &m, &a, &s);
    result += in(x,m,a,s) * (x+m+a+s);
  }
  fclose(f);
  printf("Answer 1: %d\n", result);



  int ixmas;
  int n_ranges[4] = {0,0,0,0};
  int ranges[4][500];
  int num;

  while(!feof(f2)) {
    fscanf(f2, "%d %d\n", &ixmas, &num);
    ranges[ixmas][n_ranges[ixmas]] = num;
    n_ranges[ixmas]++;
  }
  fclose(f2);

  for (int ii=0; ii<4; ii++)
    bubbleSort(ranges[ii], n_ranges[ii]);

  ranges[0][n_ranges[0]] = 4001;
  ranges[1][n_ranges[1]] = 4001;
  ranges[2][n_ranges[2]] = 4001;
  ranges[3][n_ranges[3]] = 4001;

  for (int ix=0; ix<n_ranges[0]; ix++) {
    if (ix % 10 == 9) printf("progress: %d / %d\n", ix, n_ranges[0]);
    for (int im=0; im<n_ranges[1]; im++)
    for (int ia=0; ia<n_ranges[2]; ia++)
    for (int is=0; is<n_ranges[3]; is++)
    {
      int out = in(ranges[0][ix], ranges[1][im], ranges[2][ia], ranges[3][is]);
      if (out == 1)
        result2 += (unsigned long long int)(ranges[0][ix+1] - ranges[0][ix]) * (ranges[1][im+1] - ranges[1][im]) * (ranges[2][ia+1] - ranges[2][ia]) * (ranges[3][is+1] - ranges[3][is]);
    }
  }
  printf("Answer 2: %llu\n", result2);
}
