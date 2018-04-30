/* verrou_fichier_vide.c */

#include <stdio.h> // fprintf(3), fgets(3), fgetc(3)
#include <string.h> // strch(3), strtol(3)
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define NB_ELEMENTS 32 // 30 caract�res + \n + \0

typedef struct
{
   char nom[NB_ELEMENTS];
   char prenom[NB_ELEMENTS];
   int age; // -2147483648 <= int cod� sur 4 octets <= 2147483647
}Identite;

void saisie_chaine(char*,int);
int saisie_entier();
void saisie_personne(Identite*);
Identite lecture_personne(int);
void affichage(char*);
void affichage_personne(char*);
void ajout_personne(char*);
void modification_personne(char*);
int verrouillage(int,int,int);
void deverrouillage(int,int);

int main(int argn,char** argv)
{
   int choix;

   if(argn<2)
   {
      fprintf(stderr,"usage : %s nom_fichier\n",argv[0]);
      return 1;
   }

   do
   {
      fprintf(stdout,"=======================\n0-quitter\n1-affichage de l'ensemble des personnes\n2-affichage d'une personne\n3-ajout d'une personne\n4-modification d'une personne\n=======================\nchoix :");
      choix=saisie_entier();

      switch(choix)
      {
         case 0: fprintf(stdout,"fin du programme\n");
                 break;
         case 1: affichage(argv[1]);
                 break;
         case 2: affichage_personne(argv[1]);
                 break;
         case 3: ajout_personne(argv[1]);
                 break;
         case 4: modification_personne(argv[1]);
                 break;

         default: fprintf(stderr,"choix incorrect\n");
      }
   }while(choix!=0);

   return 0;
}

/* proc�dure qui contr�le la saisie au clavier d'une cha�ne de caract�res */
void saisie_chaine(char* chaine,int taille)
{
   char* position_entree=NULL;
   int c;

   fgets(chaine,taille,stdin);
   position_entree=strchr(chaine,'\n');
   if(position_entree!=NULL)
      *position_entree='\0'; // on remplace \n par \0
   else
      while((c=fgetc(stdin))!='\n' && c!=EOF);
}

/* fonction qui renvoie un entier converti � partir d'une cha�ne de caract�res saisie au clavier */
int saisie_entier()
{
   char chaine[12]; // 10 caract�res + \n + \0
   char* p_chaine;
   int entier;

   do
   {
      saisie_chaine(chaine,sizeof(chaine));
      entier=(int)strtol(chaine,&p_chaine,10); // conversion d'une chaine en long, en base 10
                                // pour stocker l'adresse du premier caract�re qui n'est pas un nombre
   }while(p_chaine==chaine);
   return entier;
}

/* proc�dure qui demande la saisie au clavier de l'identit� d'une personne */
void saisie_personne(Identite* personne)
{
   fprintf(stdout,"nom de famille (trente caracteres au maximum) : ");
   saisie_chaine(personne->nom,sizeof(personne->nom));
   fprintf(stdout,"prenom         (trente caracteres au maximum) : ");
   saisie_chaine(personne->prenom,sizeof(personne->prenom));
   fprintf(stdout,"age                                           : ");
   do
      personne->age=saisie_entier();
   while(personne->age<0);
}

/* fonction qui a en param�tre un descripteur de fichier
 * et qui renvoie une variable de type Identite, lue dans le fichier si elle existe, sinon la variable a un age �gal a -1.
 */
/* La fonction lecture_personne utilise l'appel syst�me read(2). */
Identite lecture_personne(int fd)
{
   Identite personne;
   int nb_car;
   nb_car = read(fd, &personne, sizeof(personne));
   if (nb_car == 0){
        personne.age = -1;
   }else{
        if (nb_car != sizeof(Identite)){
            perror("erreur lecture");
        }
   }
   return personne;
}

/* proc�dure qui a en param�tre un nom de fichier
 * et qui affiche l'identit� de l'ensemble des personnes contenues dans le fichier
 */
/* La proc�dure affichage utilise la fonction lecture_personne et les appels syst�me open(2) et close(2). */
void affichage(char* filename)
{
   Identite personne;
   int fd;
   fd = open(filename, O_RDONLY);
   if (fd > 0){
     while(((personne = lecture_personne(fd)).age != -1)) {
       fprintf(stdout, "nom: %s prenom: %s age: %d\n", personne.nom, personne.prenom, personne.age);
       //write(1, personne.nom, sizeof(personne.nom));
       //write(1, personne.prenom, sizeof(personne.prenom));
       //write(1, (char*)personne.age, sizeof((char*)personne.age));
     }
     close(fd);
   }
   else{
     perror("erreur d'ouverture en lecture");
   }
}

/* procèdure qui a en param�tre un nom de fichier,
 * qui demande la saisie au clavier du num�ro d'une personne (num�rot�e � partir de 1)
 * puis qui affiche l'identit� de cette personne
 */
/* La proc�dure affichage_personne utilise la fonction lecture_personne et les appels syst�me open(2) et close(2). */
void affichage_personne(char* filename)
{
   Identite personne;
   int num_personne,fd = open(filename , O_RDONLY);

   if (fd>0){
     do{
       printf("Veuillez saisir le numero de la personne à afficher: ");
       num_personne=saisie_entier();
     }while(num_personne<1);

     lseek(fd,(num_personne -1) * sizeof(Identite), SEEK_SET);

     if ((personne = lecture_personne(fd)).age!=-1){
       fprintf(stdout, "nom: %s prenom: %s age: %d\n", personne.nom, personne.prenom, personne.age);
     }else{
       fprintf(stdout, "impossible d'afficher la personne: %d\n", num_personne);
     }
     close(fd);
   }else{
     perror("Erreur d'ouverture\n");
   }
}

/* proc�dure qui a en param�tre un nom de fichier
 * et qui ajoute l'identit� d'une personne en fin de fichier
 */
/* La proc�dure ajout_personne utilise la proc�dure saisie_personne et les appels syst�me open(2), write(2) et close(2). */
void ajout_personne(char* filename)
{
   Identite personne;
   int nb_car_ecrit,fd;
   fd = open(filename, O_CREAT| O_WRONLY| O_APPEND,00600);
   if (fd > 0){
      saisie_personne(&personne);
      if (personne.age != -1){
        nb_car_ecrit = write(fd,&personne,sizeof(Identite));
        if (nb_car_ecrit != sizeof(personne)){
          perror("erreur ecriture");
          close(fd);
        }
      }
    }else{
      perror("erreur ouverture");
    }
}

/* proc�dure qui a en param�tre un nom de fichier
 * et qui modifie toute l'identit� d'une personne dans le fichier
 */
/* La proc�dure modification_personne utilise la fonction lecture_personne, la proc�dure saisie_personne et les appels syst�me open(2), write(2) et close(2). */
void modification_personne(char* filename)
{
   Identite personne;
   int num_personne,i,nb_car_ecrit,fd;
   fd = open(filename, O_RDWR);
   if(fd > 0){
     do{
       printf("Veuillez saisir le numero de la personne à modifier: ");
       num_personne=saisie_entier();
     }while(num_personne<1);

     lseek(fd,(num_personne -1) * sizeof(Identite), SEEK_SET);

     do{
       fprintf(stdout, "Veuillez saisir le type de verrouillage");
       i = saisie_entier();
     }while(i<1 || i>2);

     if(verrouillage(fd, sizeof(Identite),i)){
       saisie_personne(&personne);
       nb_car_ecrit = write(fd, &personne, sizeof(Identite));
       if (nb_car_ecrit != sizeof(Identite)){
         perror("erreur de l'appel systeme write(2)");
       }
       deverrouillage(fd, -sizeof(Identite));
     }
     close(fd);
   }else{
     perror("erreur ouverture en lecture et en écriture");
   }
}

/* fonction qui a en param�tre un descripteur de fichier,
 * qui verrouille le fichier en utilisant la fonction lockf(3)
 * et qui renvoie la valeur 1 si un verrou a �t� pos�, 0 sinon
 * variante=1 : verrouillage bloquant
 * variante=2 : verrouillage non bloquant
 */
int verrouillage(int fd, int offset, int variante)
{
  if(variante == 1){
    if(lockf(fd, F_LOCK, offset)== -1){
      perror("erreur de la fonction lock");
    }
  }

  if (variante == 2){
    if (lockf(fd, F_TLOCK, offset)== -1){
      perror("erreur de la fonction lock");
    }else{
    fprintf(stdout,"zone verrouille et pas de pose de nouveau verrou\n");
    return 0;
    }
  }
  return 1;
}

/* proc�dure qui a en param�tre un descripteur de fichier
 * et qui deverrouille un fichier en utilisant la fonction lockf(3)
 */
void deverrouillage(int fd, int offset)
{
  if (lockf(fd, F_ULOCK, offset)== -1){
    perror("erreur de la fonction unlock")
  }
}
