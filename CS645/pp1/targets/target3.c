#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * NB.  target3 compiled -ggdb -fomit-frame-pointer -O2 ...
 *      ebp is not used and not pushed on the stack
 */

int nstrcpy(char *out, int outl, char *in)
{
  int i, len;

  len = strlen(in);
  if (len > outl)
    len = outl;

  for (i = 0; i <= len; i++)
    out[i] = in[i];
}

int bar(char *arg)
{
  char buf[136];

  nstrcpy(buf, sizeof buf, arg);
}

int foo(char *argv[])
{
  bar(argv[1]);
}

int main(int argc, char *argv[])
{
  if (argc != 2)
    {
      fprintf(stderr, "target3: argc != 2\n");
      exit(EXIT_FAILURE);
    }
  foo(argv);
  return 0;
}
