/* verrou_fichier_vide.c */

#include <stdio.h> // fprintf(3), stderr(3), printf(3), scanf(3)
#include <stdlib.h> // exit(3)

#define NB_ELEMENTS 30

typedef struct
{
   char nom[NB_ELEMENTS];
   char prenom[NB_ELEMENTS];
   int age;
}Identite;

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
      fprintf(stderr,"Usage:%s nom_fichier\n",argv[0]);
      return 1;
   }

   do
   {
      printf("0-Quitter\n1-Affichage de l'ensemble des personnes\n2-Affichage d'une personne\n3-Ajout d'une personne\n4-Modification d'une personne\n");
      printf("Choix: ");
      scanf("%d",&choix);

      switch(choix)
      {
         case 0: printf("fin du programme\n");
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

/* proc?dure qui demande la saisie au clavier de l'identit? d'une personne */
void saisie_personne(Identite* personne)
{
   printf("nom de famille (trente caracteres au maximum) : ");
   scanf("%s",personne->nom);
   printf("prenom         (trente caracteres au maximum) : ");
   scanf("%s",personne->prenom);
   do
   {
      printf("age                                           : ");
      scanf("%d",&personne->age);
   }while(personne->age<0 || personne->age>150);
}

/* fonction qui a en param?tre un descripteur de fichier
 * et qui renvoie une variable de type Identite, lue dans le fichier si elle existe, sinon la variable a un age ?gal a -1.
 */
/* La fonction lecture_personne utilise l'appel syst?me read(2). */
Identite lecture_personne(int fd)
{
   Identite personne;
   int nb_car_lu;
}

/* proc?dure qui a en param?tre un nom de fichier
 * et qui affiche l'identit? de l'ensemble des personnes contenues dans le fichier
 */
/* La proc?dure affichage utilise la fonction lecture_personne et les appels syst?me open(2) et close(2). */
void affichage(char* filename)
{
   Identite personne;
   int fd;

}

/* proc?dure qui a en param?tre un nom de fichier,
 * qui demande la saisie au clavier du num?ro d'une personne (num?rot?e ? partir de 1)
 * puis qui affiche l'identit? de cette personne
 */
/* La proc?dure affichage_personne utilise la fonction lecture_personne et les appels syst?me open(2) et close(2). */
void affichage_personne(char* filename)
{
   Identite personne;
   int num_personne,i,fd;
}

/* proc?dure qui a en param?tre un nom de fichier
 * et qui ajoute l'identit? d'une personne en fin de fichier
 */
/* La proc?dure ajout_personne utilise la proc?dure saisie_personne et les appels syst?me open(2), write(2) et close(2). */
void ajout_personne(char* filename)
{
   Identite personne;
   int nb_car_ecrit,fd;
}

/* proc?dure qui a en param?tre un nom de fichier
 * et qui modifie toute l'identit? d'une personne dans le fichier
 */
/* La proc?dure modification_personne utilise la fonction lecture_personne, la proc?dure saisie_personne et les appels syst?me open(2), write(2) et close(2). */
void modification_personne(char* filename)
{
   Identite personne;
   int num_personne,i,nb_car_ecrit,fd;
}

/* fonction qui a en param?tre un descripteur de fichier,
 * qui verrouille le fichier en utilisant la fonction lockf(3)
 * et qui renvoie la valeur 1 si un verrou a ?t? pos?, 0 sinon
 * variante=1 : verrouillage bloquant
 * variante=2 : verrouillage non bloquant
 */
int verrouillage(int fd, int offset, int variante)
{
}

/* proc?dure qui a en param?tre un descripteur de fichier
 * et qui deverrouille un fichier en utilisant la fonction lockf(3)
 */
void deverrouillage(int fd, int offset)
{
}
