#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int foo(char *arg, short arglen)
{
  int maxlen = 4000;
  char buf[4000];

  if (arglen < maxlen) 
    memcpy(buf, arg, strlen(arg));

  return 0;
}

int main(int argc, char *argv[])
{
  if (argc != 2)
    {
      fprintf(stderr, "target4: argc != 2\n");
      exit(EXIT_FAILURE);
    }

  foo(argv[1], strlen(argv[1]));

  return 0;
}
