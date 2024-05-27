#include <stdlib.h>
#include <stdio.h>
#include "cord.h"
#include "lexer.h"
#include "file_util.h"
#include "debug.h"

int main(int argc, char**argv) {

  /* TODO:
    - More checks.. check the file extension
    - Allow -d debug flag
   */
  if (argc < 3 || argc > 4) {
      fprintf(stderr, "[cord]: Usage: cord -f <filename>.crd\n");
      return -1;
  }

  compile_cord_file(argv[2]);

  return 0;
}