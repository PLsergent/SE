// processus.c

#include <unistd.h> // fork(2), getpid(2)
#include <stdio.h> // perror(3), printf(3)
#include <sys/types.h> // getpid(2), wait(2)
#include <sys/wait.h> // wait(2)

int main(void)
{
   pid_t pid; // Process ID (PID) : identifiant de processus unique
   int etat, i;

   // g�n�ration de processus
   for(i=0; i<3; i++)
   {
      pid = fork(); // g�n�ration d'un nouveau processus enfant

      switch(pid)
      {
         case (-1): // erreur de l'appel syst�me fork(2)
            perror("Erreur de l'appel systeme fork(2)\n");
            return 1;
         case 0: // code ex�cut� par le processus enfant
            printf("\tJe suis un processus enfant. Mon PID est %d et i=%d.\n", getpid(), i);
            break;
         default: // code ex�cut� par le processus parent
            printf("Je suis un processus parent. Mon PID est %d et i=%d. PID du processus enfant cree : %d.\n", getpid(), i, pid);
      }
   }

   // fin des processus
   // Un processus parent ne peut pas se temriner si un de ses processus enfant est encore en cours d'ex�cution.
   pid = wait(&etat); // L'appel syst�me wait(2) bloque un processus parent jusqu'� ce qu'un processus enfant se termine puis retourne le PID d'un processus enfant qui s'est termin� ou -1 en cas d'�chec.
   while (pid > 0)
   {
      printf("\t\tJe suis le processus %d. Le processus %d a fini de s'executer.\n", getpid(), pid);
      pid = wait(&etat);
   }

   return 0;
}
