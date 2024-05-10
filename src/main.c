#include <stdlib.h>
#include <stdio.h>
#include "lexer.h"
#include "file_util.h"

int main(int argc, char**argv) {

  char* str;

  /* TODO: More checks.. check the file extension */
  if (argc < 3 || argc > 4) {
      fprintf(stderr, "[cord]: Usage: cord -f <filename>.crd\n");
      return -1;
  }

  str = createBufFromFile(argv[2]);

  printf("%s\n", str);

  lexer_exec(str);

  free(str);
  str = NULL;

  return 0;
}