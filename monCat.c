#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(void){
  
  char buf [1];
  int read_char = 0;
  int write_char;

  do { 
    read_char = read(0 ,buf , 1);
    if(read_char == 0){
      write(1, "\n", strlen("\n"));
      return 0;
    }
    write_char = write (1, buf, read_char);
    if (write_char != read_char){
      perror("Erreur dans la matrix");
      return 1;
    }
  }while (*buf != '\n');

  return 0;
}
