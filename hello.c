#include <unistd.h>
#include <stdio.h>

int main(){
  int write_hello = write(1, "Hello world\n",12);
  if (write_hello != 12){
    perror("Erreur");
    return 1;
  }
  return 0;
}
