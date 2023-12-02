// #include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int game_output(const char * s, int red_asked, int green_asked, int blue_asked, int mode) {
    int game_number = 0;
    int bytes_read;
    int num;

    const char * cur = s + 5;  // skip len("Game ")

    int red_max = 0, green_max = 0, blue_max = 0;

    sscanf(cur, "%d%n", &game_number, &bytes_read);
    cur += bytes_read + 2;  // skip the number of bytes for the game number and also ": "

    while (1) {
        // reading new tuple at this point
        int red_in_tuple = 0, green_in_tuple = 0, blue_in_tuple = 0;

        while (1) {
            sscanf(cur, "%d%n", &num, &bytes_read);
            cur += bytes_read + 1;  // skip " " after number

            if (*cur == 'r') {
                red_in_tuple = num;
                cur += 3;  // assume it's "red" and skip len("red")
            }
            if (*cur == 'g') {
                green_in_tuple = num;
                cur += 5;  // len("green")
            }
            if (*cur == 'b') {
                blue_in_tuple = num;
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

        // printf("%d %d %d <=> %d %d %d\n", red_in_tuple, green_in_tuple, blue_in_tuple, red_asked, green_asked, blue_asked);

        if (red_in_tuple > red_max) {
            red_max = red_in_tuple;
        }
        if (green_in_tuple > green_max) {
            green_max = green_in_tuple;
        }
        if (blue_in_tuple > blue_max) {
            blue_max = blue_in_tuple;
        }

        if ( mode == 1 )
        {
            if ( (red_in_tuple > red_asked) || (green_in_tuple > green_asked) || (blue_in_tuple > blue_asked) )
            {
                return 0;
            }
        }
        if ((*cur == '\0') || (*cur == '\n')) {
            break;
        }
    }

    // printf("set of cubes = %d %d %d\n", red_max, green_max, blue_max);
    if ( mode == 2 ) return red_max * green_max * blue_max;

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

  int red = atoi(argv[2]);
  int green = atoi(argv[3]);
  int blue = atoi(argv[4]);

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
    result += game_output(s, red, green, blue, mode);
  };

  printf("Answer: %d\n", result);

  return 0;
}
