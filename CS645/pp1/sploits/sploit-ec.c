#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target-ec"

int main(void)
{
  char *args[4];
  char *env[1];

  args[0] = TARGET; args[1] = "hi"; args[2] = "there"; args[3] = NULL;
  env[0] = NULL;

  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}
