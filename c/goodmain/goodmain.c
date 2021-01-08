/* How to write a good C main function */
/* https://opensource.com/article/19/5/how-write-good-c-main-function */

/* main.c - the complete listing */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#ifdef _WIN32
#include <stdint.h>   /* For uint32_t */
#else
#include <unistd.h>   /* For uint32_t */
#include <libgen.h>   /* For basename */
#include <getopt.h>
#endif

#define OPTSTR "vi:o:f:h"
#define USAGE_FMT  "%s [-v] [-f hexflag] [-i inputfile] [-o outputfile] [-h]"
#define ERR_FOPEN_INPUT  "fopen(input, r)"
#define ERR_FOPEN_OUTPUT "fopen(output, w)"
#define ERR_DO_THE_NEEDFUL "do_the_needful blew up"
#define DEFAULT_PROGNAME "george"

#ifndef _WIN32
extern int errno;
#endif
extern char* optarg;
extern int opterr, optind;

typedef struct {
  int           verbose;
  uint32_t      flags;
  FILE* input;
  FILE* output;
} options_t;

int dumb_global_variable = -11;

void usage(char* progname, int opt);
int  do_the_needful(options_t* options);

int main(int argc, char* argv[]) {
  int opt;
  options_t options = { 0, 0x0, stdin, stdout };

  opterr = 0;

  while ((opt = getopt(argc, argv, OPTSTR)) != EOF)
    switch (opt) {
    case 'i':
      if (!(options.input = fopen(optarg, "r"))) {
        perror(ERR_FOPEN_INPUT);
        exit(EXIT_FAILURE);
        /* NOTREACHED */
      }
      break;

    case 'o':
      if (!(options.output = fopen(optarg, "w"))) {
        perror(ERR_FOPEN_OUTPUT);
        exit(EXIT_FAILURE);
        /* NOTREACHED */
      }
      break;

    case 'f':
      options.flags = (uint32_t)strtoul(optarg, NULL, 16);
      break;

    case 'v':
      options.verbose += 1;
      break;

    case 'h':
    default:
#ifdef _WIN32
      usage(NULL, opt);
#else
      usage(basename(argv[0]), opt);
#endif
      /* NOTREACHED */
      break;
    }

  if (do_the_needful(&options) != EXIT_SUCCESS) {
    perror(ERR_DO_THE_NEEDFUL);
    exit(EXIT_FAILURE);
    /* NOTREACHED */
  }

  return EXIT_SUCCESS;
}

void usage(char* progname, int opt) {
  fprintf(stderr, USAGE_FMT, progname ? progname : DEFAULT_PROGNAME);
  exit(EXIT_FAILURE);
  /* NOTREACHED */
}

int do_the_needful(options_t* options) {

  if (!options) {
    errno = EINVAL;
    return EXIT_FAILURE;
  }

  if (!options->input || !options->output) {
    errno = ENOENT;
    return EXIT_FAILURE;
  }

  /* XXX do needful stuff */

  return EXIT_SUCCESS;
}
