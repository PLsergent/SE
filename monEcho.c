#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main (int argn, char* argv[]){
  int i = 1;
  while (i<=argn-1){
    int write_echo = write (1, argv[i],strlen(argv[i]));
    if (i!=argn-1){
      write (1," ",1);
    }
    if (write_echo != strlen(argv[i])){
      perror("Erreur");
      return 1;
    }
    i++;
  }
  write(1, "\n",1);
  return 0;
}
