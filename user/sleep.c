#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if(argc <= 1){
    fprintf(2, "usage: sleep pattern [seconds ...]\n");
    exit(1);
  }

  char *seconds;
  seconds = argv[1];
  int sec = atoi(seconds);
  sleep(sec);
  exit(0);
}