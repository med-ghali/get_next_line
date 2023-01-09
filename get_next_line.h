#ifndef GET_NEXT_LINE
#define GET_NEXT_LINE

#include "stdlib.h"
#include "unistd.h"
#include "limits.h"

char *get_next_line(int fd);

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

#endif