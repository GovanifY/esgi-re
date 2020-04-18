#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdbool.h>

#define BUFSIZE 16

char *test[20];


void win_function1() {
  strcat(test,"Gagn"); 
}

void win_function2(unsigned int arg_check1) {
  if (arg_check1 == 0xABCDEF11) {
    strcat(test,"é!!"); 
  }
}

void flag(unsigned int arg_check2, unsigned int arg_check3) {
  if (arg_check2 == 0xCAFEEFCA &&arg_check3 == 0xDEADBABE) {
      printf(test);
      return;
  }
}

void vuln() {
  char buf[16];
  printf("ROP ME:");
  return gets(buf);
}

int main(int argc, char **argv){

  setvbuf(stdout, NULL, _IONBF, 0);
  
  // Set the gid to the effective gid
  // this prevents /bin/sh from dropping the privileges
  gid_t gid = getegid();
  setresgid(gid, gid, gid);
  vuln();
}

