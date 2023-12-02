#include <stdio.h>
#include <stdlib.h>


int game_output(const char * s, const int * colors_asked, int mode) {
    int game_number = 0;
    int bytes_read;
    int num;

    const char * cur = s + 5;  // skip len("Game ")

    int colors_max[3] = {0, 0, 0};

    sscanf(cur, "%d%n", &game_number, &bytes_read);
    cur += bytes_read + 2;  // skip the number of bytes for the game number and also ": "

    while (1) {
        // reading new tuple at this point
        int colors_in_tuple[3] = {0, 0, 0};

        while (1) {
            sscanf(cur, "%d%n", &num, &bytes_read);
            cur += bytes_read + 1;  // skip " " after number

            if (*cur == 'r') {
                colors_in_tuple[0] = num;
                cur += 3;  // assume it's "red" and skip len("red")
            }
            if (*cur == 'g') {
                colors_in_tuple[1] = num;
                cur += 5;  // len("green")
            }
            if (*cur == 'b') {
                colors_in_tuple[2] = num;
                cur += 4;  // len("blue")
            }
            if ((*cur == '\0') || (*cur == '\n')) {
                break;
            }
            if (*cur == ';') {
                cur += 2;
                break;
            }
            if (*cur == ',') {
                cur += 2;
            }
        }

        // printf("%d %d %d <=> %d %d %d\n", colors_in_tuple[0], colors_in_tuple[1], colors_in_tuple[2], colors_asked[0], colors_asked[1], colors_asked[2]);

        if ( mode == 1 ) {
            for (int i=0; i<3; i++) {
                if ( colors_in_tuple[i] > colors_asked[i] ) return 0;
            }
        }

        if ( mode == 2 ) {
            for (int i=0; i<3; i++) {
                if (colors_in_tuple[i] > colors_max[i]) {
                    colors_max[i] = colors_in_tuple[i];
                }
            }
        }

        if ((*cur == '\0') || (*cur == '\n')) {
            break;
        }
    }

    // printf("set of cubes = %d %d %d\n", colors_max[0], colors_max[1], colors_max[2]);
    if ( mode == 2 ) return colors_max[0] * colors_max[1] * colors_max[2];

    return game_number;
}


int main(int argc, const char* argv[]) {
  if (argc < 5) {
    printf("Usage: %s input.txt red green blue [mode]\n", argv[0]);
    return 1;
  }

  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    printf("Error opening file: %s\n", argv[1]);
    return 2;
  }

  const int colors_asked[3] = {
    atoi(argv[2]),
    atoi(argv[3]),
    atoi(argv[4])
  };

  int mode = 1;
  if (argc > 5) {
    mode = atoi(argv[5]);
  }

  char s[200];

  int result = 0;
  while (!feof(f)) {
    if (fgets(s, 199, f) == NULL) {
        break;
    }
    result += game_output(s, colors_asked, mode);
  };

  printf("Answer: %d\n", result);

  return 0;
}
