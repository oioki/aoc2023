#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mode = 1;

char s[30000];
int len;

typedef struct boxitem {
    bool enabled;
    char label[7];  // max 6 + \0
    unsigned char focal_length; // between 0 and 9
} boxitem;

boxitem box[256][256];
unsigned int lbox[256] = {0}; // array of hash lengths

void put(int hash, const char * label, unsigned char focal_length) {
  // printf("I am going to put lense ('%s',%d) into box %d\n", label, focal_length, hash);

  // update existing lens
  unsigned int l = strlen(label);
  for (unsigned int j=0; j<lbox[hash]; j++) {
    if ( (box[hash][j].enabled) && (strncmp(box[hash][j].label, label, l) == 0) ) {
      box[hash][j].focal_length = focal_length;
      return;
    }
  }

  // otherwise insert a new one
  strncpy(box[hash][lbox[hash]].label, label, strlen(label));
  box[hash][lbox[hash]].focal_length = focal_length;
  box[hash][lbox[hash]].enabled = true;
  lbox[hash]++;
}

void delete(int hash, const char * label) {
  // printf("I am going to delete lense ('%s') from box %d\n", label, hash);

  unsigned int l = strlen(label);
  for (unsigned int j=0; j<lbox[hash]; j++) {
    if ( (box[hash][j].enabled) && (strncmp(box[hash][j].label, label, l) == 0) ) {
      box[hash][j].enabled = false;
      return;
    }
  }
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

  fgets(s, 29999, f);

  unsigned int result1 = 0;
  unsigned int result2 = 0;

  unsigned int l = strlen(s);
  unsigned char current_value = 0;
  unsigned char hash;
  unsigned char focal_length = 0;
  char * label = &s[0];
  for (unsigned int i=0; i<l; i++) {
    if (mode == 2)
    if ( (s[i] == '=') || (s[i] == '-') ) {
      hash = current_value;
      if (s[i] == '=') {
        focal_length = s[i+1] - '0';
        s[i] = '\0';
        put(hash, label, focal_length);
        i+=2;
      } else { // '-'
        s[i] = '\0';
        delete(hash, label);
        i++;
      }
      label = &s[i+1];
    }
    if ((s[i] == ',') || (s[i] == '\n')) {
      result1 += current_value;
      current_value = 0;
      continue;
    }

    current_value += s[i];
    current_value *= 17;
    current_value %= 256;
  }

  for (unsigned int h=0; h<256; h++) {
    int hashvalue = 0;
    int jj = 1;
    for (unsigned int j=0; j<lbox[h]; j++) {
      if (box[h][j].enabled) {
        // printf("('%s', %d), ", box[hash][j].label, box[hash][j].focal_length);
        hashvalue += jj * box[h][j].focal_length;
        jj++;
      }
    }
    result2 += (h+1) * hashvalue;
    // printf("\n");
  }

  if (mode == 1) {
    printf("Answer: %u\n", result1);
  } else {
    printf("Answer: %u\n", result2);
  }

  return 0;
}
