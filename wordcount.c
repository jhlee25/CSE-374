// Copyright [2023] <Junhyoung Lee>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define IN 1
#define OUT 0

// code reference from a textbook "The C programming language"
// counting the word in the file
// for each file, count the number of lines, words, and characters
void counter(FILE *file, int *sum_lines, int *sum_words, int *sum_chars) {
  int new, numl, numw, numc, state;
  state = OUT;
  // set initial 0
  numl = numw = numc =0;
// looping until the end of the file
  while ((new = fgetc(file))!= EOF) {
    ++numc;
    if (new == '\n') {
        ++numl;
    }
    if (new == ' ' || new == '\n' || new == '\t') {
      state = OUT;
    } else if (state == OUT) {
      state = IN;
      ++numw;
    }
  }
  *sum_lines = numl;
  *sum_words = numw;
  *sum_chars = numc;
}

int main(int argc, char** argv) {
    // Check if there argc is in the input file
    if (argc < 2) {
        fprintf(stderr, "Usage: ./wordcount requires an input file.\n");
        return EXIT_FAILURE;
    }
    // strncmp(const char *str1, const char *str2, size_t n)
    // compares at most the first n bytes of str1 and str2.
    // n=500 maximum
    if (strncmp(argv[1], "-l", 500) == 0 ||
        strncmp(argv[1], "-w", 500) == 0 ||
        strncmp(argv[1], "-c", 500) == 0) {
        // it should not go in if there is no input file,
        // but one option is detected
        if (argc < 3) {
            fprintf(stderr, "Usage: ./wordcount requires an input file.\n");
            return EXIT_FAILURE;
        }
        // read the input file
        for (int i = 2; i < argc; i++) {
            FILE *file = fopen(argv[i], "r");
            // if file is not available, skip
            if (!file) {
                fprintf(stderr,  "%s will not open. Skipping.\n", argv[i]);
            } else {
                int sum_lines;
                int sum_words;
                int sum_chars;
                counter(file, &sum_lines, &sum_words, &sum_chars);
                printf("%d %d %d %s\n", sum_lines, sum_words, sum_chars,
                        argv[i]);
            }
            fclose(file);
        }
    } else {
        // If input has no option matches (-l, -w, -c), print 'Total lines'
        int sum = 0;
        for (int i = 1; i < argc; i++) {
            FILE *file = fopen(argv[i], "r");
            if (!file) {
                fprintf(stderr,  "%s will not open. Skipping.\n", argv[i]);
            } else {
                int sum_lines;
                int sum_words;
                int sum_chars;
                counter(file, &sum_lines, &sum_words, &sum_chars);
                sum = sum + sum_lines;
                printf("%d %d %d %s\n", sum_lines, sum_words, sum_chars,
                        argv[i]);
            }
            if (sum > 0) {
              printf("Total Lines = %d\n", sum);
            }
        }
    }
    return EXIT_SUCCESS;
}
