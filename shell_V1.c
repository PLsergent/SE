#include "ligne_commande.h"

#include <stdio.h> // perror(3), printf(3)
#include <sys/types.h> // getpid(2), wait(2)
#include <sys/wait.h> // wait(2)
#include <string.h>
#include <unistd.h>


int main(void){

  char ** cmd;
  pid_t pid;
  int etat;

  while (1){
    fprintf(stdout, "> ");
    cmd = lis_ligne();

    if (fin_de_fichier(cmd)){
      fprintf(stdout, "fin du programe\n");
      return 0;
    }else{
      if (!ligne_vide(cmd)){
        if (!strcmp(cmd[0], "exit")){
          fprintf(stdout, "fin du programe\n");
          return 0;
        }else{
          pid = fork();

          if (pid == 0){
            if (execvp(cmd[0],cmd) == -1){
              fprintf(stdout, "Error : unknow command\n");
              return 0;
            }
          }

          wait (&etat);
        }
      }
    }
  }
  return 0;
}
