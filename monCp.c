#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argn, char* argv[]){
  if (argn != 3){
    perror ("Erreur number of arguments.");
    return 1;
  }
  int fd = open (argv[1], O_RDONLY);
  if (fd == -1){
    perror("Error no file de copy.");
    return 1;
  }
  int fd1 = open (argv[2], O_WRONLY|O_CREAT|O_TRUNC, S_IWUSR|S_IRUSR);
  if (fd1 == -1){
    perror("Error on dest file");
    close(fd);
    return 1;
  }

  char buf[100000];
  int readfd,write_cp;
  do{
    readfd = read(fd, buf, 100000);

    write_cp = write(fd1, buf, readfd);

    if (write_cp == -1){
      perror("Error write");
      close(fd);
      close(fd1);
      return 1;
    }
  }while(readfd>0);
  close(fd);
  close(fd1);
  return 0;
}
