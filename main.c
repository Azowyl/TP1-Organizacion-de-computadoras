#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <errno.h>
#include <limits.h>

#define SUCCESS 0
#define ERROR 1
#define VERSION 1.0
#define MIN_USER_INPUT 2
#define MAX_USER_INPUT 1073741823

extern int mcd(int, int);

extern int mcm(int, int);

void print_info() {
  printf("%s\n%s\n%s\n%s\n",
         "Usage:",
         "  common -h",
         "  common -V",
         "  common [options] M N");
  printf("%s\n%s\n%s\n%s\n%s\n%s\n",
         "Options:",
         "  -h, --help     Prints usage information",
         "  -V, --version  Prints version information",
         "  -o, --output   Path to output file",
         "  -d, --divisor  Just the divisor",
         "  -m, --multiple Just the multiple");
  printf("%s\n%s\n",
         "Examples:",
         "  common -o - 256 192");
}

void print_version() {
  printf("%s%.2f\n", "Version: ", VERSION);
}

void print_out_of_range_error() {
  fprintf(stderr, "The number is out of range (%d to %d)\n", MIN_USER_INPUT,
          MAX_USER_INPUT);
}

int _main(int argc, char **argv,
          FILE** output, char** filename, bool* recievedFilename){
  int argument;
  char *lastChar;
  bool returnMultiple = true;
  bool returnDivisor = true;
  int argumentsRecievedByGetopt = 0;

  static struct option options[] =
      {
          {"help",     no_argument,       NULL, 'h'},
          {"version",  no_argument,       NULL, 'V'},
          {"output",   required_argument, NULL, 'o'},
          {"divisor",  no_argument,       NULL, 'd'},
          {"multiple", no_argument,       NULL, 'm'},
          {NULL,       no_argument,       NULL, 0}
      };

  while ((argument = getopt_long(argc, argv, "hVo:dm", options, NULL)) != -1) {
    switch (argument) {
      case 'd':
        argumentsRecievedByGetopt++;
        returnMultiple = false;
        break;
      case 'm':
        argumentsRecievedByGetopt++;
        returnDivisor = false;
        break;
      case 'h':
        print_info();
        return SUCCESS;
      case 'V':
        print_version();
        return SUCCESS;
      case 'o':
        argumentsRecievedByGetopt += 2;
        if (strcmp(optarg, "-") != 0) {
          *output = fopen(optarg, "wb");
          if (!*output) {
            fprintf(stderr,
                    "The file '%s' could not be created/opened\n",
                    optarg);
            return ERROR;
          }
          size_t filenameLength = strlen(optarg);
          *filename = malloc(filenameLength + 1);
          *recievedFilename = true;
          strncpy(*filename, optarg, filenameLength);
        }
        break;
      case '?':
        return ERROR;
      default:
        break;
    }
  }
  if (argc < argumentsRecievedByGetopt + 3) {
    fprintf(stderr, "Program arguments missing\n");
    return ERROR;
  }
  long numbers[2];
  bool strtolError;
  bool resultWillBeValid;
  for (int i = 0; i < 2; i++) {
    numbers[i] = strtol(argv[argumentsRecievedByGetopt + 1 + i], &lastChar, 10);
    strtolError = errno == ERANGE &&
                  (numbers[i] == LONG_MIN || numbers[i] == LONG_MAX);
    resultWillBeValid =
        numbers[i] >= MIN_USER_INPUT && numbers[i] <= MAX_USER_INPUT;
    if (strtolError || (!resultWillBeValid)) {
      print_out_of_range_error();
      return ERROR;
    }
  }

  if (returnDivisor) {
    fprintf(*output ? *output : stdout, "%d\n",
            mcd((int) numbers[0], (int) numbers[1]));
  }

  if (returnMultiple) {
    fprintf(*output ? *output : stdout, "%d\n",
            mcm((int) numbers[0], (int) numbers[1]));
  }

  if (*output) { fclose(*output); }
  return SUCCESS;
}

int main(int argc, char **argv) {
  FILE *output = NULL;
  char* filename;
  bool recievedFilename = false;
  int returnValue = _main(argc, argv, &output, &filename, &recievedFilename);
  if (returnValue != SUCCESS && output) {
    remove(filename);
  }
  if (recievedFilename) { free(filename); }
  return returnValue;
}
