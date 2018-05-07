// processus.c

#include <unistd.h> // fork(2), getpid(2)
#include <stdio.h> // perror(3), printf(3)
#include <sys/types.h> // getpid(2), wait(2)
#include <sys/wait.h> // wait(2)

int main(void)
{
   pid_t pid; // Process ID (PID) : identifiant de processus unique
   int i;

   // génération de processus
   for(i=0; i<3; i++)
   {
      pid = fork(); // génération d'un nouveau processus enfant

      switch(pid)
      {
         case (-1): // erreur de l'appel système fork(2)
            perror("Erreur de l'appel systeme fork(2)\n");
            return 1;
         case 0: // code exécuté par le processus enfant
            printf("\tJe suis un processus enfant. Mon PID est %d et i=%d.\n", getpid(), i);
            break;
         default: // code exécuté par le processus parent
            printf("Je suis un processus parent. Mon PID est %d et i=%d. PID du processus enfant cree : %d.\n", getpid(), i, pid);
            sleep(15);
      }
   }

   // fin des processus
   // Un processus parent ne peut pas se terminer si un de ses processus enfant est encore en cours d'exécution.
   printf("\t\tJe suis le processus %d. Le processus %d a fini de s'executer.\n", getpid(), pid);

   return 0;
}
