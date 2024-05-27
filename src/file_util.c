#include "file_util.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "debug.h"

/**
 * create_lexer - Creates and initializes the lexer object.
 *
 * @buf: Pointer to the buffer of raw chars from input file.
 *
 * @return: Pointer to the Lexer object.
 */
char* createBufFromFile(char* fileName) {
  char *src = NULL;
  int fd = open(fileName, O_RDONLY);
  long bufSize = 0;
  struct stat filestat;

  if (fd != -1) {
    fstat(fd, &filestat);
    
    #if DEBUG
    printf("%s: [%s]: %d: File size is %lld\n", 
      __FILE__, __FUNCTION__, __LINE__, filestat.st_size);
    #endif

    bufSize = (long)filestat.st_size;

    /* TODO: Error check this buffer size... fine for now */
    src = (char*)calloc(bufSize+1, sizeof(char));

    ssize_t fileRead = read(fd, src, (ssize_t)bufSize);

    #if DEBUG
    printf("%s: [%s]: %d: Read %ld bytes\n", 
      __FILE__, __FUNCTION__, __LINE__, fileRead);
    #endif

    if (fileRead == 0) {
      printf("%s: [%s]: %d: 0 bytes read from file!\n", 
        __FILE__, __FUNCTION__, __LINE__);
    }

    close(fd);
  }

  return src;
}